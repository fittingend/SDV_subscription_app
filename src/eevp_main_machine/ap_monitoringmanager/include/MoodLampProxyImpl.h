#ifndef EEVP_CONTROL_MOODLAMP_PROXY_IMPL_H_
#define EEVP_CONTROL_MOODLAMP_PROXY_IMPL_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "eevp/control/soamlm_proxy.h"
#include "ara/log/logger.h"

#include "IMoodLampListener.h"

namespace eevp {
namespace control {
namespace moodlamp {

class MoodLampProxyImpl {
public:
    MoodLampProxyImpl();
    ~MoodLampProxyImpl();

    void setEventListener(const std::shared_ptr<eevp::control::moodlamp::IMoodLampListener> _listener);
    bool init();

    // method
    bool requestMlmSetRGBColor(const std::uint8_t& colorTableIndex);
    void requestMlmSetMode(const eevp::control::SoaMlmMoodMode& mood);
    void requestMlmSetBrightness(const std::int16_t& brightness);

    // field getter
    bool getterSoaMlmStatus(eevp::control::SoaMlmStatus& soaMlmStatus);

private:
    void FindServiceCallback(
        ara::com::ServiceHandleContainer<eevp::control::proxy::SoaMlmProxy::HandleType> container,
        ara::com::FindServiceHandle findHandle);

    /// @brief Subscribe Event
    void SubscribeEvent();
    /// @brief Subscribe Field
    void SubscribeField();

    /// @brief Unsubscribe Event
    void UnsubscribeEvent();
    /// @brief Unsubscribe Field
    void UnsubscribeField();

    // callback func
    void cbSoaMlmStatus();

    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::control::moodlamp::IMoodLampListener> listener;
    std::shared_ptr<eevp::control::proxy::SoaMlmProxy> mProxy;
    std::shared_ptr<ara::com::FindServiceHandle> mFindHandle;

    std::mutex mHandle;
    std::condition_variable cvHandle;
};

} // namespace moodlamp
} // namespace control
} // namespace eevp

#endif /// EEVP_CONTROL_MOODLAMP_PROXY_IMPL_H_