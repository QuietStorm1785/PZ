#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/entities/User.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {


class Reaction {
public:
    virtual ~Reaction() = default;
    Message getMessage();

    int getCount();

    bool isUsedByYou();

    bool isCustomEmoji();

    bool isUnicodeEmoji();

    CustomEmoji getCustomEmoji();

    std::string getUnicodeEmoji();

   Future<List<User>> getUsers();

   Future<List<User>> getUsers(FutureCallback<List<User>> var1);

   Future<Void> removeUser(User var1);
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
