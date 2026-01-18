#include "zombie/chat/defaultChats/GeneralChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

public
GeneralChat::GeneralChat(ByteBuffer byteBuffer, ChatTab chatTab,
                         IsoPlayer player) {
  // TODO: Implement GeneralChat
  return nullptr;
}

public
GeneralChat::GeneralChat(int int0, ChatTab chatTab, bool boolean0) {
  // TODO: Implement GeneralChat
  return nullptr;
}

public
GeneralChat::GeneralChat() {
  // TODO: Implement GeneralChat
  return nullptr;
}

ChatSettings GeneralChat::getDefaultSettings() {
  // TODO: Implement getDefaultSettings
  return nullptr;
}

void GeneralChat::sendMessageToChatMembers(ChatMessage chatMessage) {
  // TODO: Implement sendMessageToChatMembers
}

void GeneralChat::sendToDiscordGeneralChatDisabled() {
  // TODO: Implement sendToDiscordGeneralChatDisabled
}

std::string GeneralChat::getMessagePrefix(ChatMessage chatMessage) {
  // TODO: Implement getMessagePrefix
  return "";
}

void GeneralChat::packMessage(ByteBufferWriter byteBufferWriter,
                              ChatMessage chatMessage) {
  // TODO: Implement packMessage
}

ChatMessage GeneralChat::unpackMessage(ByteBuffer byteBuffer) {
  // TODO: Implement unpackMessage
  return nullptr;
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
