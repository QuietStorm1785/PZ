#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace role {


class RoleDeleteListener {
public:
    virtual ~RoleDeleteListener() = default;
    void onRoleDelete(DiscordAPI var1, Role var2);
}
} // namespace role
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
