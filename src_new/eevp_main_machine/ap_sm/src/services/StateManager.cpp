/* Copyright 2024 Hyundai Mobis Co., Ltd. All rights reserved */

#include <ara/core/vector.h>
#include <ara/core/string.h>

#include <Log.hpp>
#include <services/StateManager.hpp>

using namespace ara::core;
using namespace ara::exec;

namespace state_manager
{

static void UndefinedStateCallback(FunctionGroup &fg)
{
    logger().LogError() << "Called UndefeindStateCallback : " << fg.GetName();
}

StateManager::StateManager()
    : lock_{},
      stateClient_{std::make_unique<StateClient>(UndefinedStateCallback)},
      mode_{Mode::kNone}
{
}

bool StateManager::Initialize()
{
    try {
        auto future = stateClient_->GetInitialMachineStateTransitionResult();
        auto fResult = future.GetResult();
        if (!fResult) {
            logger().LogError() << "Failed to initialize Startup state with " << fResult.Error();
            return false;
        }
    } catch (std::exception &e) {
        logger().LogError() << "Failed to initialize Startup state with " << e.what();
        return false;
    } catch (...) {
        logger().LogError() << "Failed to initialize Startup state with unknown reason";
        return false;
    }

    std::vector<String> initialFGs{kFGSC, kFGSS};
    for (const auto& it : initialFGs) {
        if (!ChangeState(it, kOn)) {
            return false;
        }
    }

#if defined ENABLE_OTA_TEST
    if (!ChangeState("OTATestFG", kOn)) {
        return false;
    }
#endif

    return true;
}

void StateManager::Release()
{
    // TBD : need to implement to change function-groups to off
}

bool StateManager::ChangeState(const ara::core::String &group, const ara::core::String &state)
{
    logger().LogInfo() << "Request to change to " << group << "," << state << ")";

    Result<FunctionGroup::CtorToken> fgResult = FunctionGroup::Preconstruct(group);
    FunctionGroup::CtorToken fgToken(fgResult.ValueOrThrow());
    FunctionGroup fg(std::move(fgToken));

    String stateStr = group + "/" + state;
    Result<FunctionGroupState::CtorToken> fgsResult = FunctionGroupState::Preconstruct(fg, stateStr);
    FunctionGroupState::CtorToken fgsToken(fgsResult.ValueOrThrow());
    FunctionGroupState fgs(std::move(fgsToken));

    try {
        auto future = stateClient_->SetState(fgs);
        auto fResult = future.GetResult();
        if (!fResult) {
            logger().LogError() << "Failed to change FG(" << group << "," << stateStr << ")";
            // let's do return true even though Functiongroup change has failed
            // until eevp has a scenario for it.
            return true;
        }
    } catch (std::exception &e) {
        logger().LogError() << "Failed to change FG(" << group << "," << state << ") with " << e.what();
        return false;
    } catch (...) {
        logger().LogError() << "Failed to change FG(" << group << "," << state << ") with unknow reason";
        return false;
    }

    return true;
}

ErrorCode StateManager::RequestMode(const ara::core::String &group, const ara::core::String &state)
{
    std::lock_guard<std::mutex> lock{lock_};

    if (!ChangeState(group, state)) {
        return kFailed;
    }

    return kSuccess;
}

ErrorCode StateManager::RequestModes(const ara::sm::FunctionGroupList &groups, const ara::core::String &state)
{
    std::lock_guard<std::mutex> lock{lock_};
    for (const auto& it : groups) {
        if (!ChangeState(it, state)) {
            return ErrorCode::kFailed;
        }
    }

    return kSuccess;
}

} // namespace state_manager