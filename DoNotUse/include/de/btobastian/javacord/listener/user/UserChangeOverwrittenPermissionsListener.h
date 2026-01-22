#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace user {


class UserChangeOverwrittenPermissionsListener {
public:
    virtual ~UserChangeOverwrittenPermissionsListener() = default;
    void onUserChangeOverwrittenPermissions(DiscordAPI var1, User var2, Channel var3, Permissions var4);

    void onUserChangeOverwrittenPermissions(DiscordAPI var1, User var2, VoiceChannel var3, Permissions var4);
}
} // namespace user
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
