#include "zombie/chat/defaultChats/RadioChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

public
RadioChat::RadioChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
  // TODO: Implement RadioChat
  return nullptr;
}

public
RadioChat::RadioChat(int int0, ChatTab chatTab) {
  // TODO: Implement RadioChat
  return nullptr;
}

public
RadioChat::RadioChat() {
  // TODO: Implement RadioChat
  return nullptr;
}

ChatSettings RadioChat::getDefaultSettings() {
  // TODO: Implement getDefaultSettings
  return nullptr;
}

ChatMessage RadioChat::createMessage(const std::string &string) {
  // TODO: Implement createMessage
  return nullptr;
}

ChatMessage RadioChat::createBroadcastingMessage(const std::string &string,
                                                 int int0) {
  // TODO: Implement createBroadcastingMessage
  return nullptr;
}

ChatMessage RadioChat::createStaticSoundMessage(const std::string &string) {
  // TODO: Implement createStaticSoundMessage
  return nullptr;
}

void RadioChat::showInSpeechBubble(ChatMessage chatMessage) {
  // TODO: Implement showInSpeechBubble
}

void RadioChat::showMessage(ChatMessage chatMessage) {
  // TODO: Implement showMessage
}

void RadioChat::sendToServer(ChatMessage chatMessage, DeviceData deviceData) {
  // TODO: Implement sendToServer
}

ChatMessage RadioChat::unpackMessage(ByteBuffer byteBuffer) {
  // TODO: Implement unpackMessage
  return nullptr;
}

void RadioChat::packMessage(ByteBufferWriter byteBufferWriter,
                            ChatMessage chatMessage) {
  // TODO: Implement packMessage
}

std::string RadioChat::getMessagePrefix(ChatMessage chatMessage) {
  // TODO: Implement getMessagePrefix
  return "";
}

std::string RadioChat::getRadioChannelStr(ChatMessage chatMessage) {
  // TODO: Implement getRadioChannelStr
  return "";
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
