
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_SERVICE_INTERFACE_DUMMYTEST_SKELETON_IMPL_H_
#define PARA_ARA_COM_GEN_SERVICE_INTERFACE_DUMMYTEST_SKELETON_IMPL_H_
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "test/dummy/dummytest_skeleton.h"
#include "ara/log/logger.h"

namespace test
{
namespace dummy
{
namespace skeleton
{
class DummyTestSkeletonImpl : public DummyTestSkeleton
{

private:
    /// @brief Logger
    ara::log::Logger& mLogger;
    fields::DeviceField::FieldType dField{0, true};
public:
explicit DummyTestSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
    : DummyTestSkeleton(instanceSpec, mode), mLogger(ara::log::CreateLogger("TPRV", "SWC", ara::log::LogLevel::kInfo))
{
    auto devicefield_get_handler = [this]() {
        return DeviceFieldGetter();
    };
    DeviceField.RegisterGetHandler(devicefield_get_handler);
    auto devicefield_set_handler = [this](const fields::DeviceField::FieldType& value) {
        return DeviceFieldSetter(value);
    };
    DeviceField.RegisterSetHandler(devicefield_set_handler);
}

void E2EErrorHandler(const ara::com::e2e::E2EErrorDomain& errorCode,
                     ara::com::e2e::DataID dataID,
                     ara::com::e2e::MessageCounter messageCounter) override
{
}

ara::core::Future<DeviceMethodOutput> DeviceMethod(const std::int16_t& DeviceNumber) override
{
    DeviceMethodOutput response;
    ara::core::Promise<DeviceMethodOutput> promise;

    response.DeviceState = true;
    mLogger.LogInfo() << "[DEVICE EVENT] : " << response.DeviceState;

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<fields::DeviceField::FieldType> DeviceFieldGetter(void)
{
    ara::core::Promise<fields::DeviceField::FieldType> promise;
    mLogger.LogInfo() << "[DEVICE FIELD GETTER] ("<<dField.DeviceNum<<":"
        <<dField.DeviceState<<")";
    promise.set_value(dField);
    return promise.get_future();
}
ara::core::Future<fields::DeviceField::FieldType> DeviceFieldSetter(const fields::DeviceField::FieldType& value)
{
    ara::core::Promise<fields::DeviceField::FieldType> promise;
    dField = value;
    mLogger.LogInfo() << "[DEVICE FIELD SETTER] ("<<dField.DeviceNum<<":"
        <<dField.DeviceState<<")";
    promise.set_value(dField);
    return promise.get_future();
}


};
} /// skeleton
} /// namespace dummy
} /// namespace test
#endif /// PARA_ARA_COM_GEN_SERVICE_INTERFACE_DUMMYTEST_SKELETON_IMPL_H_
