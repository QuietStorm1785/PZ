#include <string>
#include "de\btobastian\javacord\entities\message\impl/ImplReaction.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {

public ImplReaction::ImplReaction(ImplDiscordAPI api, Message message, JSONObject data) {
    // TODO: Implement ImplReaction
    return nullptr;
}

public ImplReaction::ImplReaction(ImplDiscordAPI api, Message message, bool usedByYou, int count, const std::string& unicodeEmoji, CustomEmoji customEmoji) {
    // TODO: Implement ImplReaction
    return nullptr;
}

Message ImplReaction::getMessage() {
    // TODO: Implement getMessage
    return nullptr;
}

int ImplReaction::getCount() {
    // TODO: Implement getCount
    return 0;
}

bool ImplReaction::isUsedByYou() {
    // TODO: Implement isUsedByYou
    return false;
}

bool ImplReaction::isCustomEmoji() {
    // TODO: Implement isCustomEmoji
    return false;
}

bool ImplReaction::isUnicodeEmoji() {
    // TODO: Implement isUnicodeEmoji
    return false;
}

CustomEmoji ImplReaction::getCustomEmoji() {
    // TODO: Implement getCustomEmoji
    return nullptr;
}

std::string ImplReaction::getUnicodeEmoji() {
    // TODO: Implement getUnicodeEmoji
    return "";
}

void ImplReaction::incrementCount(bool you) {
    // TODO: Implement incrementCount
}

void ImplReaction::decrementCount(bool you) {
    // TODO: Implement decrementCount
}

std::string ImplReaction::toString() {
    // TODO: Implement toString
    return "";
}

} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
