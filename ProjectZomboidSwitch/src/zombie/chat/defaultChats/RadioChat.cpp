#include <string>
#include "zombie/chat/defaultChats/RadioChat.h"

namespace zombie {
namespace chat {
namespace defaultChats {

public RadioChat::RadioChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
    // TODO: Implement RadioChat
    return nullptr;
}

public RadioChat::RadioChat(int var1, ChatTab var2) {
    // TODO: Implement RadioChat
    return nullptr;
}

public RadioChat::RadioChat() {
    // TODO: Implement RadioChat
    return nullptr;
}

ChatSettings RadioChat::getDefaultSettings() {
    // TODO: Implement getDefaultSettings
    return nullptr;
}

ChatMessage RadioChat::createMessage(const std::string& var1) {
    // TODO: Implement createMessage
    return nullptr;
}

ChatMessage RadioChat::createBroadcastingMessage(const std::string& var1, int var2) {
    // TODO: Implement createBroadcastingMessage
    return nullptr;
}

ChatMessage RadioChat::createStaticSoundMessage(const std::string& var1) {
    // TODO: Implement createStaticSoundMessage
    return nullptr;
}

void RadioChat::showInSpeechBubble(ChatMessage var1) {
    // TODO: Implement showInSpeechBubble
}

void RadioChat::showMessage(ChatMessage var1) {
    // TODO: Implement showMessage
}

void RadioChat::sendToServer(ChatMessage var1, DeviceData var2) {
    // TODO: Implement sendToServer
}

ChatMessage RadioChat::unpackMessage(ByteBuffer var1) {
    // TODO: Implement unpackMessage
    return nullptr;
}

void RadioChat::packMessage(ByteBufferWriter var1, ChatMessage var2) {
    // TODO: Implement packMessage
}

std::string RadioChat::getMessagePrefix(ChatMessage var1) {
    // TODO: Implement getMessagePrefix
    return "";
}

std::string RadioChat::getRadioChannelStr(ChatMessage var1) {
    // TODO: Implement getRadioChannelStr
    return "";
}

} // namespace defaultChats
} // namespace chat
} // namespace zombie
