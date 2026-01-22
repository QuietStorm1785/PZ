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


class ChannelChangePositionListener {
public:
    virtual ~ChannelChangePositionListener() = default;
    void onChannelChangePosition(DiscordAPI var1, Channel var2, int var3);
}
} // namespace channel
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
