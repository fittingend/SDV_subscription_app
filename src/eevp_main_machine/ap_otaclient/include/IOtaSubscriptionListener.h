#ifndef IOTA_SUBSCRIPTION_LISTENER_H
#define IOTA_SUBSCRIPTION_LISTENER_H

#include "eevp/ota/subscription/type/impl_type_requestappinfomap.h"

namespace eevp {
namespace ota {

class IOtaSubscriptionListener {
public:
    virtual ~IOtaSubscriptionListener() {};

    virtual void requestAppInstall(const ara::core::String& appName) = 0;
    virtual void requestAppUpdate(const ara::core::String& appName) = 0;
    virtual void requestVersionInfo(eevp::ota::subscription::type::RequestAppInfoMap& requestAppInfoMap) = 0;
};

} /// namespace ota
} /// namespace eevp

#endif /* IOTA_SUBSCRIPTION_LISTENER_H */