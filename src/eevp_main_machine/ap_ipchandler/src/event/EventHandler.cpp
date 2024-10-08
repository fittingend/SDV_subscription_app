/* Copyright 2024 Hyundai Mobis Co., Ltd. All rights reserved */

#include <event.h>
#include <event2/util.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <csignal>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <deque>

#include <Log.hpp>
#include <ipc/IPCIntf.hpp>
#include <event/EventHandler.hpp>

static std::atomic<bool> isSignaled{false};
static std::mutex eventLock{};
static std::condition_variable cv{};

static std::int32_t eventFd{-1};
static event_base* eventBase{nullptr};

static void SignalFunction(int signum) {
    if (signum == SIGTERM) {
        if (eventBase != nullptr) {
            event_base_loopbreak(eventBase);
        }
    }
}

class EventReceived : public aa_event::EventNotifer {
    public:
        EventReceived() = default;
        ~EventReceived() = default;

        virtual void EventArrived(aa_event::Event eventKind) override {
            std::uint64_t msg = static_cast<std::uint64_t>(eventKind);

            int written = write(eventFd, &msg, sizeof(msg));
            if (written != sizeof(msg)) {
                logger().LogError() << "Failed to send message to loop";
            }
        }
};

#ifdef ENABLE_TEST
void SendTestEvent(std::uint32_t event)
{
    (void) event;   // TBD

    event_base_loopbreak(eventBase);
}
#endif

namespace aa_event
{

AAEventHandler::AAEventHandler()
    : routingIPCSkeleton_{nullptr}
{
}

void AAEventHandler::OnEvent(evutil_socket_t fd, short event, void* arg)
{
    (void) event;
    aa_event::AAEventHandler* eventHandler = static_cast<aa_event::AAEventHandler*>(arg);
    if (eventHandler == nullptr) {
        logger().LogError() << "AAEventHandler is null";
    } else {
        uint64_t msg;
        ssize_t sz = read(fd, &msg, sizeof(msg));
        if (sz != sizeof(msg)) {
            logger().LogWarn() << "Received msg, but size is different";
        } else {
            aa_event::Event eventMessage = static_cast<aa_event::Event>(msg);
            switch (eventMessage) {
                case kNone:
                    break;
                case kIPCRx:
                    {
                        CpInfo cpInfo;
                        while (ipc::IPCIntf::getInstance().PopCpInfo(cpInfo)) {
                            if (eventHandler->routingIPCSkeleton_ != nullptr) {
                                eventHandler->routingIPCSkeleton_->UpdateCpInfo(cpInfo);
                            }
                        }
                    }
                    break;
                default:
                    logger().LogWarn() << "Invalid Event" << static_cast<std::uint64_t>(eventMessage);
                    break;
            }
        }
    }
}

void AAEventHandler::OnTimeoutEvent(evutil_socket_t fd, short event, void* arg)
{
    (void) fd;
    (void) event;
    aa_event::TimeoutEventInfo* timeoutEvent = static_cast<aa_event::TimeoutEventInfo*>(arg);
    if (timeoutEvent == nullptr || timeoutEvent->evnetHandler == nullptr) {
        logger().LogError() << "AAEventHandler or TimeoutEvent is null";
    } else {
        switch (timeoutEvent->eventKind) {
            case kPeriodicTimer1Secs:
                logger().LogInfo() << "Test 1 second periodic Event for ap_ipchandler";
                break;
            default:
                logger().LogWarn() << "Invalid TimeoutEvent" << static_cast<std::uint64_t>(timeoutEvent->eventKind);
                break;
        }
    }
}

void AAEventHandler::Run()
{
    // event initialization
    eventFd = eventfd(0, EFD_NONBLOCK);
    if (eventFd == -1) {
        logger().LogError() << "Failed to create eventfd";
        return;
    }

    eventBase = event_base_new();
    struct event* ev = event_new(eventBase, eventFd, EV_READ | EV_PERSIST, AAEventHandler::OnEvent, this);
    if (event_add(ev, nullptr) == -1) {
        logger().LogError() << "Failed to event_add for event";
        return;
    }

    // test timer, will be delete if not necessary
    struct timeval timeout1SecInterval{1, 0};
    struct TimeoutEventInfo timeoutEventInfo{this, TimeoutEvent::kPeriodicTimer1Secs};
    struct event* timeoutEv = event_new(eventBase, -1, EV_TIMEOUT | EV_PERSIST, AAEventHandler::OnTimeoutEvent, &timeoutEventInfo);
    if (event_add(timeoutEv, &timeout1SecInterval) == -1) {
        logger().LogError() << "Failed to event_add for timer event";
        return;
    }

    EventReceived eventReceived;
    ipc::IPCIntf::getInstance().RegisterEventHandler(eventReceived);

    // proxy/skeketon initialization
    routingIPCSkeleton_ = std::make_shared<routingipc::IPCRoutingIPCSkeleton>();
    routingIPCSkeleton_->OfferService();

    // signal
    signal(SIGTERM, SignalFunction);

    // in loop
    event_base_dispatch(eventBase);

    routingIPCSkeleton_->StopOfferService();
    routingIPCSkeleton_ = nullptr;
    event_free(timeoutEv);
    event_free(ev);
    event_base_free(eventBase);
    close(eventFd);

    logger().LogInfo() << "Good bye";
}

} // aa_event
