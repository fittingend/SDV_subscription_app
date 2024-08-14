#include "test/dummy/dummytest_proxy.h"
#include <random>
#include <thread>
#include <chrono>
#include <csignal>
#include <ara/log/logger.h>
using namespace test::dummy::proxy;
namespace swc 
{

class Consumer
{
public:
    /// @brief Constructor
    Consumer();
    /// @brief Destructor
    ~Consumer();
    /// @brief Start S/W Component
    bool Start();
    /// @brief Run S/W Component
    void Run();
    /// @brief Terminate S/W Component
    void Terminate();
private:
    /// @brief Signal Handler
    static void SignalHandler(std::int32_t signal);
    /// @brief Request method
    void MethodRequest();
    /// @brief Request field get
    void FieldGetter();
    /// @brief Request field set
    void FieldSetter();
    /// @brief Subscribe Event
    void SubscribeEvent();
    /// @brief Subscribe Field
    void SubscribeField();
    /// @brief Process received event data 
    void GetEventData();
    /// @brief Process received field value 
    void GetFieldValue();
    /// @brief Find handler
    void StartFindCallback(ara::com::ServiceHandleContainer<DummyTestProxy::HandleType> services, ara::com::FindServiceHandle handle);
    /// @brief SubscriptionState handler
    void StateChangeCallback(ara::core::String callsign, ara::com::SubscriptionState state) ;
    /// @brief Flag of Running
    static std::atomic_bool mRunning;
    /// @brief Logger
    ara::log::Logger& mLogger;
    /// @brief Service Proxy
    std::unique_ptr<DummyTestProxy> mRPort{nullptr};
    /// @brief FindServiceHandle
    ara::com::FindServiceHandle* mFindHandle{nullptr};
    /// @brief Current ProxyHandle
    DummyTestProxy::HandleType mProxyHandle;
};

}