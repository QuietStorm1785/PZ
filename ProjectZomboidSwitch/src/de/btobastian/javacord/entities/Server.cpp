#include <string>
#include "de/btobastian/javacord/entities/Server.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {

std::string Server::getId() {
    // TODO: Implement getId
    return "";
}

Calendar Server::getCreationDate() {
    // TODO: Implement getCreationDate
    return nullptr;
}

std::string Server::getName() {
    // TODO: Implement getName
    return "";
}

Channel Server::getChannelById(const std::string& var1) {
    // TODO: Implement getChannelById
    return nullptr;
}

VoiceChannel Server::getVoiceChannelById(const std::string& var1) {
    // TODO: Implement getVoiceChannelById
    return nullptr;
}

User Server::getMemberById(const std::string& var1) {
    // TODO: Implement getMemberById
    return nullptr;
}

bool Server::isMember(User var1) {
    // TODO: Implement isMember
    return false;
}

bool Server::isMember(const std::string& var1) {
    // TODO: Implement isMember
    return false;
}

Role Server::getRoleById(const std::string& var1) {
    // TODO: Implement getRoleById
    return nullptr;
}

Region Server::getRegion() {
    // TODO: Implement getRegion
    return nullptr;
}

int Server::getMemberCount() {
    // TODO: Implement getMemberCount
    return 0;
}

bool Server::isLarge() {
    // TODO: Implement isLarge
    return false;
}

std::string Server::getOwnerId() {
    // TODO: Implement getOwnerId
    return "";
}

CustomEmoji Server::getCustomEmojiById(const std::string& var1) {
    // TODO: Implement getCustomEmojiById
    return nullptr;
}

CustomEmoji Server::getCustomEmojiByName(const std::string& var1) {
    // TODO: Implement getCustomEmojiByName
    return nullptr;
}

std::string Server::getNickname(User var1) {
    // TODO: Implement getNickname
    return "";
}

bool Server::hasNickname(User var1) {
    // TODO: Implement hasNickname
    return false;
}

URL Server::getIconUrl() {
    // TODO: Implement getIconUrl
    return nullptr;
}

} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
