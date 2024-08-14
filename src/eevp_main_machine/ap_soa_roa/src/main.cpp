#include <Common.h>
#include <thread>
#include <atomic>
#include <csignal>

#include <ManagerBase.hpp>
#include <MessageQueue.hpp>
#include <VehicleContext.hpp>
#include <PaconSetting.hpp>

using namespace std;

extern void DevicesInit(void);

static std::atomic<bool> s_running;
static MessageQueue<int> s_queueForStopping;

static void stopApp(void)
{
    s_running = false;
    s_queueForStopping.Push(0);
}

static void signalHandler(std::int32_t signal)
{
    stopApp();
}

int main(int argc, char *argv[])
{
    s_running = true;

    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    if (!PaconSetting::GetInstance()->StartPacon())
    {
        (void)PaconSetting::RemoveInstance();
        return 1;
    }

    // TODO: your code here
    VehicleContext *context = VehicleContext::GetInstance();
    DevicesInit();

    while (s_running)
    {
        (void)s_queueForStopping.Pop();
    }

    ManagerBase::StopAllManagers();

    (void)PaconSetting::RemoveInstance();
    return 0;
}
