#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace role {


class RoleChangeOverwrittenPermissionsListener {
public:
    virtual ~RoleChangeOverwrittenPermissionsListener() = default;
    void onRoleChangeOverwrittenPermissions(DiscordAPI var1, Role var2, Channel var3, Permissions var4);

    void onRoleChangeOverwrittenPermissions(DiscordAPI var1, Role var2, VoiceChannel var3, Permissions var4);
}
} // namespace role
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
