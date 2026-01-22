#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace voice {


class UserJoinVoiceChannelListener {
public:
    virtual ~UserJoinVoiceChannelListener() = default;
    void onUserJoinVoiceChannel(DiscordAPI var1, User var2, VoiceChannel var3);
}
} // namespace voice
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
