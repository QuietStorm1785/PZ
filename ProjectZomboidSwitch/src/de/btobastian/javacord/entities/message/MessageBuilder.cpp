#include <sstream>
#include <string>
#include "de\btobastian\javacord\entities\message/MessageBuilder.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {

MessageBuilder MessageBuilder::append(const std::string& message) {
    // TODO: Implement append
    return nullptr;
}

MessageBuilder MessageBuilder::appendDecoration(const std::string& message, MessageDecoration... decorations) {
    // TODO: Implement appendDecoration
    return nullptr;
}

MessageBuilder MessageBuilder::appendCode(const std::string& language, const std::string& message) {
    // TODO: Implement appendCode
    return nullptr;
}

MessageBuilder MessageBuilder::appendMention(User user) {
    // TODO: Implement appendMention
    return nullptr;
}

MessageBuilder MessageBuilder::appendUser(User user) {
    // TODO: Implement appendUser
    return nullptr;
}

MessageBuilder MessageBuilder::appendNewLine() {
    // TODO: Implement appendNewLine
    return nullptr;
}

MessageBuilder MessageBuilder::appendChannel(Channel channel) {
    // TODO: Implement appendChannel
    return nullptr;
}

MessageBuilder MessageBuilder::appendRole(Role role) {
    // TODO: Implement appendRole
    return nullptr;
}

std::stringstream MessageBuilder::getStringBuilder() {
    // TODO: Implement getStringBuilder
    return nullptr;
}

std::string MessageBuilder::build() {
    // TODO: Implement build
    return "";
}

std::string MessageBuilder::toString() {
    // TODO: Implement toString
    return "";
}

} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
