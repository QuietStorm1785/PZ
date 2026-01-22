#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace voicechannel {


class VoiceChannelChangeNameListener {
public:
    virtual ~VoiceChannelChangeNameListener() = default;
    void onVoiceChannelChangeName(DiscordAPI var1, VoiceChannel var2, const std::string& var3);
}
} // namespace voicechannel
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
