#include <string>
#include "de\btobastian\javacord\entities\message\impl/ImplMessageHistory.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {

public ImplMessageHistory::ImplMessageHistory(ImplDiscordAPI api, const std::string& channelId, int limit) {
    // TODO: Implement ImplMessageHistory
    return nullptr;
}

public ImplMessageHistory::ImplMessageHistory(ImplDiscordAPI api, const std::string& channelId, const std::string& messageId, bool before, int limit) {
    // TODO: Implement ImplMessageHistory
    return nullptr;
}

int ImplMessageHistory::request(ImplDiscordAPI api, const std::string& channelId, const std::string& messageId, bool before, int limit) {
    // TODO: Implement request
    return 0;
}

Message ImplMessageHistory::getMessageById(const std::string& id) {
    // TODO: Implement getMessageById
    return nullptr;
}

Message ImplMessageHistory::getNewestMessage() {
    // TODO: Implement getNewestMessage
    return nullptr;
}

Message ImplMessageHistory::getOldestMessage() {
    // TODO: Implement getOldestMessage
    return nullptr;
}

void ImplMessageHistory::removeMessage(const std::string& id) {
    // TODO: Implement removeMessage
}

} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
