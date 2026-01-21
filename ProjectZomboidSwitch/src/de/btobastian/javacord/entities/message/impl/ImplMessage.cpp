#include <string>
#include "de/btobastian/javacord/entities/message/impl/ImplMessage.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {

public ImplMessage::ImplMessage(JSONObject data, ImplDiscordAPI api, MessageReceiver receiver) {
    // TODO: Implement ImplMessage
    return nullptr;
}

std::string ImplMessage::getId() {
    // TODO: Implement getId
    return "";
}

std::string ImplMessage::getContent() {
    // TODO: Implement getContent
    return "";
}

Channel ImplMessage::getChannelReceiver() {
    // TODO: Implement getChannelReceiver
    return nullptr;
}

User ImplMessage::getUserReceiver() {
    // TODO: Implement getUserReceiver
    return nullptr;
}

MessageReceiver ImplMessage::getReceiver() {
    // TODO: Implement getReceiver
    return nullptr;
}

User ImplMessage::getAuthor() {
    // TODO: Implement getAuthor
    return nullptr;
}

bool ImplMessage::isPrivateMessage() {
    // TODO: Implement isPrivateMessage
    return false;
}

bool ImplMessage::isTts() {
    // TODO: Implement isTts
    return false;
}

std::string ImplMessage::getNonce() {
    // TODO: Implement getNonce
    return "";
}

bool ImplMessage::isMentioningEveryone() {
    // TODO: Implement isMentioningEveryone
    return false;
}

bool ImplMessage::isPinned() {
    // TODO: Implement isPinned
    return false;
}

bool ImplMessage::isDeleted() {
    // TODO: Implement isDeleted
    return false;
}

Calendar ImplMessage::getCreationDate() {
    // TODO: Implement getCreationDate
    return nullptr;
}

int ImplMessage::compareTo(Message other) {
    // TODO: Implement compareTo
    return 0;
}

void ImplMessage::setContent(const std::string& content) {
    // TODO: Implement setContent
}

void ImplMessage::setDeleted(bool deleted) {
    // TODO: Implement setDeleted
}

Reaction ImplMessage::addUnicodeReactionToCache(const std::string& unicodeReaction, bool you) {
    // TODO: Implement addUnicodeReactionToCache
    return nullptr;
}

Reaction ImplMessage::addCustomEmojiReactionToCache(CustomEmoji customEmoji, bool you) {
    // TODO: Implement addCustomEmojiReactionToCache
    return nullptr;
}

Reaction ImplMessage::removeUnicodeReactionToCache(const std::string& unicodeReaction, bool you) {
    // TODO: Implement removeUnicodeReactionToCache
    return nullptr;
}

Reaction ImplMessage::removeCustomEmojiReactionToCache(CustomEmoji customEmoji, bool you) {
    // TODO: Implement removeCustomEmojiReactionToCache
    return nullptr;
}

void ImplMessage::removeAllReactionsFromCache() {
    // TODO: Implement removeAllReactionsFromCache
}

std::string ImplMessage::getChannelId() {
    // TODO: Implement getChannelId
    return "";
}

MessageReceiver ImplMessage::findReceiver(const std::string& channelId) {
    // TODO: Implement findReceiver
    return nullptr;
}

std::string ImplMessage::toString() {
    // TODO: Implement toString
    return "";
}

int ImplMessage::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
