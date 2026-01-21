#include <string>
#include "de/btobastian/javacord/entities/message/Reaction.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {

Message Reaction::getMessage() {
    // TODO: Implement getMessage
    return nullptr;
}

int Reaction::getCount() {
    // TODO: Implement getCount
    return 0;
}

bool Reaction::isUsedByYou() {
    // TODO: Implement isUsedByYou
    return false;
}

bool Reaction::isCustomEmoji() {
    // TODO: Implement isCustomEmoji
    return false;
}

bool Reaction::isUnicodeEmoji() {
    // TODO: Implement isUnicodeEmoji
    return false;
}

CustomEmoji Reaction::getCustomEmoji() {
    // TODO: Implement getCustomEmoji
    return nullptr;
}

std::string Reaction::getUnicodeEmoji() {
    // TODO: Implement getUnicodeEmoji
    return "";
}

} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
