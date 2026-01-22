#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace user {


class UserChangeNicknameListener {
public:
    virtual ~UserChangeNicknameListener() = default;
    void onUserChangeNickname(DiscordAPI var1, Server var2, User var3, const std::string& var4);
}
} // namespace user
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
