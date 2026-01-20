#include <string>
#include "de\btobastian\javacord\entities\permissions\impl/ImplRole.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {

public ImplRole::ImplRole(JSONObject data, ImplServer server, ImplDiscordAPI api) {
    // TODO: Implement ImplRole
    return nullptr;
}

std::string ImplRole::getId() {
    // TODO: Implement getId
    return "";
}

std::string ImplRole::getName() {
    // TODO: Implement getName
    return "";
}

Server ImplRole::getServer() {
    // TODO: Implement getServer
    return nullptr;
}

Permissions ImplRole::getPermissions() {
    // TODO: Implement getPermissions
    return nullptr;
}

Permissions ImplRole::getOverwrittenPermissions(Channel channel) {
    // TODO: Implement getOverwrittenPermissions
    return nullptr;
}

Permissions ImplRole::getOverwrittenPermissions(VoiceChannel channel) {
    // TODO: Implement getOverwrittenPermissions
    return nullptr;
}

int ImplRole::getPosition() {
    // TODO: Implement getPosition
    return 0;
}

bool ImplRole::getHoist() {
    // TODO: Implement getHoist
    return false;
}

Color ImplRole::getColor() {
    // TODO: Implement getColor
    return nullptr;
}

bool ImplRole::isMentionable() {
    // TODO: Implement isMentionable
    return false;
}

bool ImplRole::isManaged() {
    // TODO: Implement isManaged
    return false;
}

std::string ImplRole::getMentionTag() {
    // TODO: Implement getMentionTag
    return "";
}

void ImplRole::addUserNoUpdate(User user) {
    // TODO: Implement addUserNoUpdate
}

void ImplRole::removeUserNoUpdate(User user) {
    // TODO: Implement removeUserNoUpdate
}

void ImplRole::setName(const std::string& name) {
    // TODO: Implement setName
}

void ImplRole::setPermissions(ImplPermissions permissions) {
    // TODO: Implement setPermissions
}

void ImplRole::setPosition(int position) {
    // TODO: Implement setPosition
}

void ImplRole::setOverwrittenPermissions(Channel channel, Permissions permissions) {
    // TODO: Implement setOverwrittenPermissions
}

void ImplRole::setOverwrittenPermissions(VoiceChannel channel, Permissions permissions) {
    // TODO: Implement setOverwrittenPermissions
}

void ImplRole::setColor(Color color) {
    // TODO: Implement setColor
}

void ImplRole::setHoist(bool hoist) {
    // TODO: Implement setHoist
}

void ImplRole::setMentionable(bool mentionable) {
    // TODO: Implement setMentionable
}

void ImplRole::setManaged(bool managed) {
    // TODO: Implement setManaged
}

std::string ImplRole::toString() {
    // TODO: Implement toString
    return "";
}

} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
