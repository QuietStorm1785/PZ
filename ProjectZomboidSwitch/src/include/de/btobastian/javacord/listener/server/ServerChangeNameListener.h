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


class ServerChangeNameListener {
public:
    virtual ~ServerChangeNameListener() = default;
    void onServerChangeName(DiscordAPI var1, Server var2, const std::string& var3);
}
} // namespace server
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
