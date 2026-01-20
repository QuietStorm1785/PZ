#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/DiscordAPI.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/UserStatus.h"
#include "de/btobastian/javacord/listener/Listener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace listener {
namespace user {


class UserChangeStatusListener {
public:
    virtual ~UserChangeStatusListener() = default;
    void onUserChangeStatus(DiscordAPI var1, User var2, UserStatus var3);
}
} // namespace user
} // namespace listener
} // namespace javacord
} // namespace btobastian
} // namespace de
