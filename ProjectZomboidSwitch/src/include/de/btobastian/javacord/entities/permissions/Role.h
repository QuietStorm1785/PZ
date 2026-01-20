#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "java/awt/Color.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {


class Role {
public:
    virtual ~Role() = default;
    std::string getId();

    std::string getName();

    Server getServer();

    Permissions getPermissions();

    Permissions getOverwrittenPermissions(Channel var1);

    Permissions getOverwrittenPermissions(VoiceChannel var1);

   List<User> getUsers();

    int getPosition();

    bool getHoist();

    Color getColor();

    bool isMentionable();

    bool isManaged();

    std::string getMentionTag();

   Future<Void> updatePermissions(Permissions var1);

   Future<Void> updateName(std::string var1);

   Future<Void> updateColor(Color var1);

   Future<Void> updateHoist(boolean var1);

   Future<Void> updateMentionable(boolean var1);

   Future<Void> update(std::string var1, Color var2, boolean var3, Permissions var4, boolean var5);

   Future<Void> delete();

   Future<Void> addUser(User var1);

   Future<Void> removeUser(User var1);
}
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
