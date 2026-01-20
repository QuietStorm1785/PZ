#include <string>
#include "zombie\chat\defaultChats/ServerChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

public ServerChat::ServerChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
    // TODO: Implement ServerChat
    return nullptr;
}

public ServerChat::ServerChat(int var1, ChatTab var2) {
    // TODO: Implement ServerChat
    return nullptr;
}

ChatSettings ServerChat::getDefaultSettings() {
    // TODO: Implement getDefaultSettings
    return nullptr;
}

ChatMessage ServerChat::createMessage(const std::string& var1, const std::string& var2, bool var3) {
    // TODO: Implement createMessage
    return nullptr;
}

ServerChatMessage ServerChat::createServerMessage(const std::string& var1, bool var2) {
    // TODO: Implement createServerMessage
    return nullptr;
}

short ServerChat::getTabID() {
    // TODO: Implement getTabID
    return 0;
}

ChatMessage ServerChat::unpackMessage(ByteBuffer var1) {
    // TODO: Implement unpackMessage
    return nullptr;
}

void ServerChat::packMessage(ByteBufferWriter var1, ChatMessage var2) {
    // TODO: Implement packMessage
}

std::string ServerChat::getMessagePrefix(ChatMessage var1) {
    // TODO: Implement getMessagePrefix
    return "";
}

std::string ServerChat::getMessageTextWithPrefix(ChatMessage var1) {
    // TODO: Implement getMessageTextWithPrefix
    return "";
}

void ServerChat::showMessage(ChatMessage var1) {
    // TODO: Implement showMessage
}

void ServerChat::sendMessageToChatMembers(ChatMessage var1) {
    // TODO: Implement sendMessageToChatMembers
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
