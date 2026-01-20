#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/message/embed/Embed.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedBuilder.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {


class Message {
public:
    virtual ~Message() = default;
    std::string getId();

    std::string getContent();

    Channel getChannelReceiver();

    User getUserReceiver();

    MessageReceiver getReceiver();

    User getAuthor();

    bool isPrivateMessage();

   List<User> getMentions();

   List<Role> getMentionedRoles();

    bool isTts();

    std::string getNonce();

    bool isMentioningEveryone();

   Future<Void> pin();

    bool isPinned();

   Future<Void> delete();

    bool isDeleted();

   Collection<MessageAttachment> getAttachments();

   Future<Message> reply(std::string var1);

   Future<Message> reply(std::string var1, EmbedBuilder var2);

   Future<Message> reply(std::string var1, FutureCallback<Message> var2);

   Future<Message> reply(std::string var1, EmbedBuilder var2, FutureCallback<Message> var3);

    Calendar getCreationDate();

   Future<Void> edit(std::string var1);

   Collection<Embed> getEmbeds();

   Future<Void> addUnicodeReaction(std::string var1);

   Future<Void> addCustomEmojiReaction(CustomEmoji var1);

   List<Reaction> getReactions();

   Future<Void> removeAllReactions();
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
