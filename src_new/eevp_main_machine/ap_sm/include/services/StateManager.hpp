/* Copyright 2024 Hyundai Mobis Co., Ltd. All rights reserved */

#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <mutex>
#include <ara/sm/impl_type_functiongrouplist.h>
#include <ara/exec/state_client.h>
#include <ara/exec/function_group.h>
#include <ara/core/error_code.h>
#include <ara/core/vector.h>
#include <ara/core/string.h>

namespace state_manager
{

// State
const ara::core::String kOff{"Off"};
const ara::core::String kOn{"On"};
const ara::core::String kVerify{"Verify"};

const ara::core::String kMachinFg{"MachineFG"};

const ara::core::String kMachineStartup{"Startup"};     // for future
const ara::core::String kMachineShutdown{"Shutdown"};   // for future
const ara::core::String kMachineRestart{"Restart"};     // for future

// Function groups
const ara::core::String kFGSS{"SS"};        // Subsribed Services
const ara::core::String kFGSC{"SC"};        // Standard Controller

enum Mode : std::uint8_t    // for future
{
    kNone,
    kInUpdating
};

enum ErrorCode : std::uint8_t
{
    kSuccess = 0,
    kFailed = 1,
    kRejected = 2,  // for future
};

class StateManager final
{
    public:
        static StateManager& getInstance() {
            static StateManager instance{};
            return instance;
        }

        bool Initialize();
        void Release();

        ErrorCode RequestMode(const ara::core::String &group, const ara::core::String &state);
        ErrorCode RequestModes(const ara::sm::FunctionGroupList &groups, const ara::core::String &state);

    private:
        std::mutex lock_;
        std::unique_ptr<ara::exec::StateClient> stateClient_;
        Mode mode_; // for future

        StateManager();
        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;

        bool ChangeState(const ara::core::String &group, const ara::core::String &state);
};

} // namespace state_manager

#endif // STATE_MANAGER_HPP