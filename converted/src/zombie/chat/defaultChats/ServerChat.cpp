#include "zombie/chat/defaultChats/ServerChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

public
ServerChat::ServerChat(ByteBuffer byteBuffer, ChatTab chatTab,
                       IsoPlayer player) {
  // TODO: Implement ServerChat
  return nullptr;
}

public
ServerChat::ServerChat(int int0, ChatTab chatTab) {
  // TODO: Implement ServerChat
  return nullptr;
}

ChatSettings ServerChat::getDefaultSettings() {
  // TODO: Implement getDefaultSettings
  return nullptr;
}

ChatMessage ServerChat::createMessage(const std::string &string1,
                                      const std::string &string0,
                                      bool boolean0) {
  // TODO: Implement createMessage
  return nullptr;
}

ServerChatMessage ServerChat::createServerMessage(const std::string &string,
                                                  bool boolean0) {
  // TODO: Implement createServerMessage
  return nullptr;
}

short ServerChat::getTabID() {
  // TODO: Implement getTabID
  return 0;
}

ChatMessage ServerChat::unpackMessage(ByteBuffer byteBuffer) {
  // TODO: Implement unpackMessage
  return nullptr;
}

void ServerChat::packMessage(ByteBufferWriter byteBufferWriter,
                             ChatMessage chatMessage) {
  // TODO: Implement packMessage
}

std::string ServerChat::getMessagePrefix(ChatMessage chatMessage) {
  // TODO: Implement getMessagePrefix
  return "";
}

std::string ServerChat::getMessageTextWithPrefix(ChatMessage chatMessage) {
  // TODO: Implement getMessageTextWithPrefix
  return "";
}

void ServerChat::showMessage(ChatMessage chatMessage) {
  // TODO: Implement showMessage
}

void ServerChat::sendMessageToChatMembers(ChatMessage chatMessage) {
  // TODO: Implement sendMessageToChatMembers
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
