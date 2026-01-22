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


class ServerMemberUnbanListener {
public:
    virtual ~ServerMemberUnbanListener() = default;
    void onServerMemberUnban(DiscordAPI var1, const std::string& var2, Server var3);
}
} // namespace server
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
