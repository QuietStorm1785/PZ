#include <string>
#include "zombie/chat/defaultChats/GeneralChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

public GeneralChat::GeneralChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
    // TODO: Implement GeneralChat
    return nullptr;
}

public GeneralChat::GeneralChat(int var1, ChatTab var2, bool var3) {
    // TODO: Implement GeneralChat
    return nullptr;
}

public GeneralChat::GeneralChat() {
    // TODO: Implement GeneralChat
    return nullptr;
}

ChatSettings GeneralChat::getDefaultSettings() {
    // TODO: Implement getDefaultSettings
    return nullptr;
}

void GeneralChat::sendMessageToChatMembers(ChatMessage var1) {
    // TODO: Implement sendMessageToChatMembers
}

void GeneralChat::sendToDiscordGeneralChatDisabled() {
    // TODO: Implement sendToDiscordGeneralChatDisabled
}

std::string GeneralChat::getMessagePrefix(ChatMessage var1) {
    // TODO: Implement getMessagePrefix
    return "";
}

void GeneralChat::packMessage(ByteBufferWriter var1, ChatMessage var2) {
    // TODO: Implement packMessage
}

ChatMessage GeneralChat::unpackMessage(ByteBuffer var1) {
    // TODO: Implement unpackMessage
    return nullptr;
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
