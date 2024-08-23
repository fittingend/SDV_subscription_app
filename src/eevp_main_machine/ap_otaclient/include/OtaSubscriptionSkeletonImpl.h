#ifndef EEVP_OTA_SUBSCRIPTION_SKELETON_IMPL_H_
#define EEVP_OTA_SUBSCRIPTION_SKELETON_IMPL_H_

#include "eevp/ota/subscription/service/otasubscription_skeleton.h"
#include "ara/log/logger.h"

#include "IOtaSubscriptionListener.h"

namespace eevp {
namespace ota {
namespace subscription {

class OtaSubscriptionSkeletonImpl : public eevp::ota::subscription::service::skeleton::OtaSubscriptionSkeleton {
public:
    OtaSubscriptionSkeletonImpl(
            ara::core::InstanceSpecifier instanceSpec,
            ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEventSingleThread);

    ~OtaSubscriptionSkeletonImpl();

    void setEventListener(std::shared_ptr<eevp::ota::IOtaSubscriptionListener> _listener);

    ara::core::Future<requestAppInstallOutput> requestAppInstall(const eevp::type::String& appName) override;
    ara::core::Future<requestAppUpdateOutput> requestAppUpdate(const eevp::type::String& appName) override;
    ara::core::Future<requestVersionInfoOutput> requestVersionInfo() override;

    void sendNotifyAppEvent(eevp::ota::subscription::type::RequestAppInfo& info);
    void sendNotifyUpdatableApp(eevp::ota::subscription::type::UpdatableAppInfo& appInfo);

private:
    ara::log::Logger& mLogger;
    std::shared_ptr<eevp::ota::IOtaSubscriptionListener> listener;
};

} /// namespace subscription
} /// namespace ota
} /// namespace eevp

#endif /// EEVP_OTA_SUBSCRIPTION_SKELETON_IMPL_H_
