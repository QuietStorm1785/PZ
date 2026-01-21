#include <string>
#include "de/btobastian/javacord/entities/message/Message.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {

std::string Message::getId() {
    // TODO: Implement getId
    return "";
}

std::string Message::getContent() {
    // TODO: Implement getContent
    return "";
}

Channel Message::getChannelReceiver() {
    // TODO: Implement getChannelReceiver
    return nullptr;
}

User Message::getUserReceiver() {
    // TODO: Implement getUserReceiver
    return nullptr;
}

MessageReceiver Message::getReceiver() {
    // TODO: Implement getReceiver
    return nullptr;
}

User Message::getAuthor() {
    // TODO: Implement getAuthor
    return nullptr;
}

bool Message::isPrivateMessage() {
    // TODO: Implement isPrivateMessage
    return false;
}

bool Message::isTts() {
    // TODO: Implement isTts
    return false;
}

std::string Message::getNonce() {
    // TODO: Implement getNonce
    return "";
}

bool Message::isMentioningEveryone() {
    // TODO: Implement isMentioningEveryone
    return false;
}

bool Message::isPinned() {
    // TODO: Implement isPinned
    return false;
}

bool Message::isDeleted() {
    // TODO: Implement isDeleted
    return false;
}

Calendar Message::getCreationDate() {
    // TODO: Implement getCreationDate
    return nullptr;
}

} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
