#include <string>
#include "de/btobastian/javacord/entities/impl/ImplServer.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {

public ImplServer::ImplServer(JSONObject data, ImplDiscordAPI api) {
    // TODO: Implement ImplServer
    return nullptr;
}

new ImplServer::ImplRole() {
    // TODO: Implement ImplRole
    return nullptr;
}

new ImplServer::ImplCustomEmoji() {
    // TODO: Implement ImplCustomEmoji
    return nullptr;
}

new ImplServer::ImplChannel() {
    // TODO: Implement ImplChannel
    return nullptr;
}

new ImplServer::ImplVoiceChannel() {
    // TODO: Implement ImplVoiceChannel
    return nullptr;
}

std::string ImplServer::getId() {
    // TODO: Implement getId
    return "";
}

Calendar ImplServer::getCreationDate() {
    // TODO: Implement getCreationDate
    return nullptr;
}

std::string ImplServer::getName() {
    // TODO: Implement getName
    return "";
}

Channel ImplServer::getChannelById(const std::string& id) {
    // TODO: Implement getChannelById
    return nullptr;
}

VoiceChannel ImplServer::getVoiceChannelById(const std::string& id) {
    // TODO: Implement getVoiceChannelById
    return nullptr;
}

User ImplServer::getMemberById(const std::string& id) {
    // TODO: Implement getMemberById
    return nullptr;
}

bool ImplServer::isMember(User user) {
    // TODO: Implement isMember
    return false;
}

bool ImplServer::isMember(const std::string& userId) {
    // TODO: Implement isMember
    return false;
}

Role ImplServer::getRoleById(const std::string& id) {
    // TODO: Implement getRoleById
    return nullptr;
}

Region ImplServer::getRegion() {
    // TODO: Implement getRegion
    return nullptr;
}

int ImplServer::getMemberCount() {
    // TODO: Implement getMemberCount
    return 0;
}

bool ImplServer::isLarge() {
    // TODO: Implement isLarge
    return false;
}

std::string ImplServer::getOwnerId() {
    // TODO: Implement getOwnerId
    return "";
}

CustomEmoji ImplServer::getCustomEmojiById(const std::string& id) {
    // TODO: Implement getCustomEmojiById
    return nullptr;
}

CustomEmoji ImplServer::getCustomEmojiByName(const std::string& name) {
    // TODO: Implement getCustomEmojiByName
    return nullptr;
}

std::string ImplServer::getNickname(User user) {
    // TODO: Implement getNickname
    return "";
}

bool ImplServer::hasNickname(User user) {
    // TODO: Implement hasNickname
    return false;
}

URL ImplServer::getIconUrl() {
    // TODO: Implement getIconUrl
    return nullptr;
}

void ImplServer::setName(const std::string& name) {
    // TODO: Implement setName
}

void ImplServer::setRegion(Region region) {
    // TODO: Implement setRegion
}

void ImplServer::addMember(User user) {
    // TODO: Implement addMember
}

void ImplServer::addMembers(JSONArray members) {
    // TODO: Implement addMembers
}

void ImplServer::removeMember(User user) {
    // TODO: Implement removeMember
}

void ImplServer::incrementMemberCount() {
    // TODO: Implement incrementMemberCount
}

void ImplServer::decrementMemberCount() {
    // TODO: Implement decrementMemberCount
}

void ImplServer::setMemberCount(int memberCount) {
    // TODO: Implement setMemberCount
}

void ImplServer::addChannel(Channel channel) {
    // TODO: Implement addChannel
}

void ImplServer::addVoiceChannel(VoiceChannel channel) {
    // TODO: Implement addVoiceChannel
}

void ImplServer::addRole(Role role) {
    // TODO: Implement addRole
}

void ImplServer::removeRole(Role role) {
    // TODO: Implement removeRole
}

void ImplServer::removeChannel(Channel channel) {
    // TODO: Implement removeChannel
}

void ImplServer::removeVoiceChannel(VoiceChannel channel) {
    // TODO: Implement removeVoiceChannel
}

void ImplServer::addCustomEmoji(CustomEmoji emoji) {
    // TODO: Implement addCustomEmoji
}

void ImplServer::removeCustomEmoji(CustomEmoji emoji) {
    // TODO: Implement removeCustomEmoji
}

void ImplServer::setOwnerId(const std::string& ownerId) {
    // TODO: Implement setOwnerId
}

void ImplServer::setNickname(User user, const std::string& nickname) {
    // TODO: Implement setNickname
}

std::string ImplServer::getIconHash() {
    // TODO: Implement getIconHash
    return "";
}

void ImplServer::setIconHash(const std::string& hash) {
    // TODO: Implement setIconHash
}

void* ImplServer::createChannelBlocking(const std::string& name, bool voice) {
    // TODO: Implement createChannelBlocking
    return nullptr;
}

std::string ImplServer::toString() {
    // TODO: Implement toString
    return "";
}

int ImplServer::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
