#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace channel {


class ChannelChangeNameListener {
public:
    virtual ~ChannelChangeNameListener() = default;
    void onChannelChangeName(DiscordAPI var1, Channel var2, const std::string& var3);
}
} // namespace channel
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
