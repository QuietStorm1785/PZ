#include <string>
#include "de\btobastian\javacord\entities\impl/ImplChannel.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {

public ImplChannel::ImplChannel(JSONObject data, ImplServer server, ImplDiscordAPI api) {
    // TODO: Implement ImplChannel
    return nullptr;
}

std::string ImplChannel::getId() {
    // TODO: Implement getId
    return "";
}

Calendar ImplChannel::getCreationDate() {
    // TODO: Implement getCreationDate
    return nullptr;
}

std::string ImplChannel::getName() {
    // TODO: Implement getName
    return "";
}

std::string ImplChannel::getTopic() {
    // TODO: Implement getTopic
    return "";
}

int ImplChannel::getPosition() {
    // TODO: Implement getPosition
    return 0;
}

Server ImplChannel::getServer() {
    // TODO: Implement getServer
    return nullptr;
}

void ImplChannel::type() {
    // TODO: Implement type
}

InviteBuilder ImplChannel::getInviteBuilder() {
    // TODO: Implement getInviteBuilder
    return nullptr;
}

Permissions ImplChannel::getOverwrittenPermissions(User user) {
    // TODO: Implement getOverwrittenPermissions
    return nullptr;
}

Permissions ImplChannel::getOverwrittenPermissions(Role role) {
    // TODO: Implement getOverwrittenPermissions
    return nullptr;
}

std::string ImplChannel::getMentionTag() {
    // TODO: Implement getMentionTag
    return "";
}

void ImplChannel::setName(const std::string& name) {
    // TODO: Implement setName
}

void ImplChannel::setTopic(const std::string& topic) {
    // TODO: Implement setTopic
}

void ImplChannel::setPosition(int position) {
    // TODO: Implement setPosition
}

void ImplChannel::setOverwrittenPermissions(User user, Permissions permissions) {
    // TODO: Implement setOverwrittenPermissions
}

void ImplChannel::removeOverwrittenPermissions(User user) {
    // TODO: Implement removeOverwrittenPermissions
}

std::string ImplChannel::getParentId() {
    // TODO: Implement getParentId
    return "";
}

void ImplChannel::setParentId(const std::string& parentId) {
    // TODO: Implement setParentId
}

std::string ImplChannel::toString() {
    // TODO: Implement toString
    return "";
}

int ImplChannel::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
