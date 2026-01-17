#include "zombie/chat/defaultChats/RangeBasedChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

void RangeBasedChat::Init() {
  // TODO: Implement Init
}

bool RangeBasedChat::isSendingToRadio() {
  // TODO: Implement isSendingToRadio
  return false;
}

ChatMessage RangeBasedChat::createMessage(const std::string &string) {
  // TODO: Implement createMessage
  return nullptr;
}

ChatMessage RangeBasedChat::createBubbleMessage(const std::string &string) {
  // TODO: Implement createBubbleMessage
  return nullptr;
}

void RangeBasedChat::sendMessageToChatMembers(ChatMessage chatMessage) {
  // TODO: Implement sendMessageToChatMembers
}

void RangeBasedChat::showMessage(ChatMessage chatMessage) {
  // TODO: Implement showMessage
}

ChatElement RangeBasedChat::getSpeechBubble() {
  // TODO: Implement getSpeechBubble
  return nullptr;
}

UIFont RangeBasedChat::selectFont(const std::string &string) {
  // TODO: Implement selectFont
  return nullptr;
}

void RangeBasedChat::showInSpeechBubble(ChatMessage chatMessage) {
  // TODO: Implement showInSpeechBubble
}

IsoPlayer RangeBasedChat::getPlayer(const std::string &string) {
  // TODO: Implement getPlayer
  return nullptr;
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
