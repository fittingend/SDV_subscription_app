#include "KatechSkeletonImpl.hpp"
#include "ara/exec/execution_client.h"

using namespace eevp::control::skeleton;

namespace eevp {
namespace control {

KatechSkeletonImpl::KatechSkeletonImpl(
                InstanceSpecifier instanceSpec,
                ara::com::MethodCallProcessingMode mode) :
        listener{nullptr},
        SoaRcurtainSkeleton(instanceSpec, mode),
    mLogger(ara::log::CreateLogger("KATC", "KATC", ara::log::LogLevel::kInfo)) {
    mLogger.LogInfo() << __func__;

    auto soaRctnStatus_get_handler = [this]() {
        return this->soaRctnStatusGetter();
    };
}

KatechSkeletonImpl::~KatechSkeletonImpl() {
    StopOfferService();
}

bool KatechSkeletonImpl::init()
{
    ara::core::InstanceSpecifier specifier("KATECH/AA/PPortRearCurtain");
    // initialize service skeleton
    //mPPortImpl = std::make_unique<TestSrvSkeletonImpl>(specifier, ara::com::MethodCallProcessingMode::kPoll);
    mPPortImpl = std::make_unique<KatechSkeletonImpl>(specifier, ara::com::MethodCallProcessingMode::kEventSingleThread);
    // offer service
    auto offered = mPPortImpl->OfferService();
    if (offered.HasValue()) {
        mLogger.LogInfo() << " Rearcurtain Offer Service";
        mRunning = true;
        return true;
    } else {
        mLogger.LogInfo() << "Rearcurtain Offer Service Failed";
        return false;
    }
}

void KatechSkeletonImpl::Run()
{
    // loop start
    //ara::exec::ExecutionClient executionClient;
    //auto exec = executionClient.ReportExecutionState(ara::exec::ExecutionState::kRunning);
    // if (exec.HasValue()) {
    //     mLogger.LogInfo() << "Provider Running State";
    // } else {
    //     mLogger.LogInfo() << exec.Error().Message();
    // }
    while (mRunning) {
        SendEvent();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        SendNotification();
        for(auto i = 0; i < 30 ; i++) {
            if (mRunning == false) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

// terminate service instance
void KatechSkeletonImpl::Terminate()
{
    if (mPPortImpl) {
        mPPortImpl->StopOfferService();
        mLogger.LogInfo() << "Rearcurtain Stop Offer Service";
    }
}

void KatechSkeletonImpl::SendEvent()
{
    if (mRunning == false) {
        return;
    }
    if (mPPortImpl == nullptr) {
        return;
    }
    events::DeviceEvent::SampleType ddata;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> NumGen(1, 10);
    ddata.DeviceNum = i++;//NumGen(gen);

    std::bernoulli_distribution boolGen(0.5);
    tf = !tf;
    ddata.DeviceState = tf;//boolGen(gen);

    // mLogger.LogInfo() << "[DEVICE EVENT NOTIFICATION] (" << ddata.DeviceNum << ":"
    //         << ddata.DeviceState << ")";

    mPPortImpl->DeviceEvent.Send(ddata);

}

void KatechSkeletonImpl::SendNotification()
{
    if (mRunning == false) {
        return;
    }
    if (mPPortImpl == nullptr) {
        return;
    }
    fields::DeviceField::FieldType dvalue;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> NumGen(1, 10);
    dvalue.DeviceNum = i;//NumGen(gen);

    std::bernoulli_distribution boolGen(0.5);
    dvalue.DeviceState = tf;//boolGen(gen);

    mLogger.LogInfo() << "[DEVICE FIELD NOTIFICATION] (" << dvalue.DeviceNum << ":"
            << dvalue.DeviceState << ")";

    mPPortImpl->DeviceField.Update(dvalue);
}
// void
// KatechSkeletonImpl::setEventListener(std::shared_ptr<IMonitoringManagementListener> _listener) {
//     listener = _listener;
// }


// Future<skeleton::KatechSkeleton::requestControllerServiceStatusOutput>
// KatechSkeletonImpl::requestControllerServiceStatus(const eevp::type::String& controllerServiceName) {
//     mLogger.LogInfo() << __func__;

//     KatechSkeleton::requestControllerServiceStatusOutput response;
//     Promise<requestControllerServiceStatusOutput> promise;
//     bool retVal;
//     eevp::type::String status;

//     if (listener != nullptr) {
//         retVal = listener->requestControllerServiceStatus(controllerServiceName, status);
//     }

//     response.controllerServiceStatus = status;
//     response.returnValue = retVal;

//     if (controllerServiceName == "RearCurtain" || controllerServiceName == "MoodLamp") {
//         mLogger.LogInfo () << "[requestControllerServiceStatus] ("
//                             << controllerServiceName << ":"
//                             << response.controllerServiceStatus << ":"
//                             << response.returnValue << ")";
//     }

//     promise.set_value(response);
//     return promise.get_future();
// }

//RearCurtain start 

Future<skeleton::KatechSkeletonImpl::RequestRearCurtainOperationOutput>
KatechSkeletonImpl::RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir) {
    mLogger.LogInfo() << __func__;

    MonitoringManagementSkeleton::RequestRearCurtainOperationOutput response;
    Promise<RequestRearCurtainOperationOutput> promise;

    if (listener != nullptr) {
        listener->RequestRearCurtainOperation(motorDir);
    }

    promise.set_value(response);
    return promise.get_future();
}

ara::core::Future<fields::soaRctnStatus::FieldType>
KatechSkeletonImpl::soaRctnStatusGetter()
{
    LOG_DEBUG() << "[KatechSkeletonImpl::soaRctnStatusGetter] (+)\n";
    ara::core::Promise<fields::soaRctnStatus::FieldType> promise;
    promise.set_value(this->rctnStatusField);
    LOG_DEBUG() << "[KatechSkeletonImpl::soaRctnStatusGetter] (-)\n";
    return promise.get_future();
}

ara::core::Future<SoaRcurtainSkeleton::RequestRearCurtainOperationOutput> KatechSkeletonImpl::RequestRearCurtainOperation(const eevp::control::SoaRctnMotorDir& motorDir)
{
    RequestRearCurtainOperationOutput response;
    ara::core::Promise<RequestRearCurtainOperationOutput> promise;

    LOG_DEBUG() << "[KatechSkeletonImpl::RequestRearCurtainOperation] (+)\n";

    RCtnSwitch_e eBtnValue;
    switch (motorDir)
    {
    case eevp::control::SoaRctnMotorDir::kDOWN:
        eBtnValue = eRCtnSwitch_OpenOn;
        break;

    case eevp::control::SoaRctnMotorDir::kUP:
        eBtnValue = eRCtnSwitch_CloseOn;
        break;

    case eevp::control::SoaRctnMotorDir::kSTOP:
    default:
        eBtnValue = eRCtnSwitch_Off;
        break;
    }

    int ret = Api_Rcurtain_Method_RequestRearCurtainOperation(eBtnValue);
    response.err = (ret == 0) ? eevp::control::SoaErrorState::kOK : eevp::control::SoaErrorState::kERROR;
    promise.set_value(response);

    LOG_DEBUG() << "[KatechSkeletonImpl::RequestRearCurtainOperation] (-)\n";
    return promise.get_future();
}
void KatechSkeletonImpl::SetSoaRctnStatus(eevp::control::SoaRctnStatus status)
{
    LOG_DEBUG() << "[KatechSkeletonImpl::SetSoaRctnStatus] (+)\n";
    if ((this->mField.errorState != status.errorState) ||
        (this->mField.curMotorDirection != status.curMotorDirection) ||
        (this->mField.curtainState != status.curtainState) ||
        (this->mField.isNormal != status.isNormal))
    {
        this->mField = status;
        soaRctnStatus.Update(this->mField);
    }
    LOG_DEBUG() << "[KatechSkeletonImpl::SetSoaRctnStatus] (-)\n";
}
} /// namespace monitoring
} /// namespace eevp
