#ifndef IVI_STATEMANAGER_LISTENER_H
#define IVI_STATEMANAGER_LISTENER_H

#include "ivi/info/statemanager/type/impl_type_state.h"

namespace ivi {
namespace info {
namespace statemanager {

class IStateManagerListener {
public:
    virtual ~IStateManagerListener() {};
    virtual void notifyNotifySystemState(const ivi::info::statemanager::type::State& state) = 0;
    virtual void notifyNotifyTime(const std::uint8_t& notifyTime) = 0;
    virtual void notifySystemState(const ivi::info::statemanager::type::State& state) = 0;
};

} /// namespace statemanager
} /// namespace info
} /// namespace ivi


#endif /* IVI_STATEMANAGER_LISTENER_H */