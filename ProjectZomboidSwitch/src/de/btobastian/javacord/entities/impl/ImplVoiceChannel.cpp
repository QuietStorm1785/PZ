#include <string>
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {

public ImplVoiceChannel::ImplVoiceChannel(JSONObject data, ImplServer server, ImplDiscordAPI api) {
    // TODO: Implement ImplVoiceChannel
    return nullptr;
}

std::string ImplVoiceChannel::getId() {
    // TODO: Implement getId
    return "";
}

Calendar ImplVoiceChannel::getCreationDate() {
    // TODO: Implement getCreationDate
    return nullptr;
}

std::string ImplVoiceChannel::getName() {
    // TODO: Implement getName
    return "";
}

int ImplVoiceChannel::getPosition() {
    // TODO: Implement getPosition
    return 0;
}

Server ImplVoiceChannel::getServer() {
    // TODO: Implement getServer
    return nullptr;
}

InviteBuilder ImplVoiceChannel::getInviteBuilder() {
    // TODO: Implement getInviteBuilder
    return nullptr;
}

Permissions ImplVoiceChannel::getOverwrittenPermissions(User user) {
    // TODO: Implement getOverwrittenPermissions
    return nullptr;
}

Permissions ImplVoiceChannel::getOverwrittenPermissions(Role role) {
    // TODO: Implement getOverwrittenPermissions
    return nullptr;
}

void ImplVoiceChannel::setName(const std::string& name) {
    // TODO: Implement setName
}

void ImplVoiceChannel::setPosition(int position) {
    // TODO: Implement setPosition
}

void ImplVoiceChannel::setOverwrittenPermissions(User user, Permissions permissions) {
    // TODO: Implement setOverwrittenPermissions
}

void ImplVoiceChannel::removeOverwrittenPermissions(User user) {
    // TODO: Implement removeOverwrittenPermissions
}

void ImplVoiceChannel::addConnectedUser(User user) {
    // TODO: Implement addConnectedUser
}

void ImplVoiceChannel::removeConnectedUser(User user) {
    // TODO: Implement removeConnectedUser
}

std::string ImplVoiceChannel::getParentId() {
    // TODO: Implement getParentId
    return "";
}

void ImplVoiceChannel::setParentId(const std::string& parentId) {
    // TODO: Implement setParentId
}

std::string ImplVoiceChannel::toString() {
    // TODO: Implement toString
    return "";
}

int ImplVoiceChannel::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
