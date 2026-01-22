#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace server {


class ServerJoinListener {
public:
    virtual ~ServerJoinListener() = default;
    void onServerJoin(DiscordAPI var1, Server var2);
}
} // namespace server
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
