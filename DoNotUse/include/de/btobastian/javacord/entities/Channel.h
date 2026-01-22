#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageReceiver.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {


class Channel {
public:
    virtual ~Channel() = default;
    std::string getId();

    Calendar getCreationDate();

    std::string getName();

    std::string getTopic();

    int getPosition();

    Server getServer();

   Future<Void> delete();

    InviteBuilder getInviteBuilder();

    Permissions getOverwrittenPermissions(User var1);

    Permissions getOverwrittenPermissions(Role var1);

   Future<Void> updateOverwrittenPermissions(Role var1, Permissions var2);

   Future<Void> updateOverwrittenPermissions(User var1, Permissions var2);

   Future<Void> deleteOverwrittenPermissions(Role var1);

   Future<Void> deleteOverwrittenPermissions(User var1);

   Future<Void> updateName(std::string var1);

   Future<Void> updateTopic(std::string var1);

   Future<Void> updatePosition(int var1);

   Future<Void> update(std::string var1, std::string var2, int var3);

    std::string getMentionTag();

   Future<Void> bulkDelete(std::string... var1);

   Future<Void> bulkDelete(Message... var1);

   Future<Message> getMessageById(std::string var1);

    std::string getParentId();
}
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
