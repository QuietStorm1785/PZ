#include "zombie/chat/ChatMessage.h"

namespace zombie {
namespace chat {

public
ChatMessage::ChatMessage(ChatBase _chat, const std::string &_text) {
 // TODO: Implement ChatMessage
 return nullptr;
}

public
ChatMessage::ChatMessage(ChatBase _chat, LocalDateTime _datetime,
 const std::string &_text) {
 // TODO: Implement ChatMessage
 return nullptr;
}

bool ChatMessage::isShouldAttractZombies() {
 // TODO: Implement isShouldAttractZombies
 return false;
}

void ChatMessage::setShouldAttractZombies(bool _shouldAttractZombies) {
 // TODO: Implement setShouldAttractZombies
}

bool ChatMessage::isLocal() {
 // TODO: Implement isLocal
 return false;
}

void ChatMessage::setLocal(bool __local__) {
 // TODO: Implement setLocal
}

std::string ChatMessage::getTextWithReplacedParentheses() {
 // TODO: Implement getTextWithReplacedParentheses
 return "";
}

void ChatMessage::setScrambledText(const std::string &_text) {
 // TODO: Implement setScrambledText
}

int ChatMessage::getRadioChannel() {
 // TODO: Implement getRadioChannel
 return 0;
}

void ChatMessage::setRadioChannel(int _radioChannel) {
 // TODO: Implement setRadioChannel
}

bool ChatMessage::isServerAuthor() {
 // TODO: Implement isServerAuthor
 return false;
}

void ChatMessage::setServerAuthor(bool _serverAuthor) {
 // TODO: Implement setServerAuthor
}

bool ChatMessage::isFromDiscord() {
 // TODO: Implement isFromDiscord
 return false;
}

void ChatMessage::makeFromDiscord() {
 // TODO: Implement makeFromDiscord
}

bool ChatMessage::isOverHeadSpeech() {
 // TODO: Implement isOverHeadSpeech
 return false;
}

void ChatMessage::setOverHeadSpeech(bool _overHeadSpeech) {
 // TODO: Implement setOverHeadSpeech
}

bool ChatMessage::isShowInChat() {
 // TODO: Implement isShowInChat
 return false;
}

void ChatMessage::setShowInChat(bool _showInChat) {
 // TODO: Implement setShowInChat
}

LocalDateTime ChatMessage::getDatetime() {
 // TODO: Implement getDatetime
 return nullptr;
}

std::string ChatMessage::getDatetimeStr() {
 // TODO: Implement getDatetimeStr
 return "";
}

void ChatMessage::setDatetime(LocalDateTime _datetime) {
 // TODO: Implement setDatetime
}

bool ChatMessage::isShowAuthor() {
 // TODO: Implement isShowAuthor
 return false;
}

std::string ChatMessage::getAuthor() {
 // TODO: Implement getAuthor
 return "";
}

void ChatMessage::setAuthor(const std::string &_author) {
 // TODO: Implement setAuthor
}

ChatBase ChatMessage::getChat() {
 // TODO: Implement getChat
 return nullptr;
}

int ChatMessage::getChatID() {
 // TODO: Implement getChatID
 return 0;
}

std::string ChatMessage::getText() {
 // TODO: Implement getText
 return "";
}

void ChatMessage::setText(const std::string &_text) {
 // TODO: Implement setText
}

std::string ChatMessage::getTextWithPrefix() {
 // TODO: Implement getTextWithPrefix
 return "";
}

bool ChatMessage::isScramble() {
 // TODO: Implement isScramble
 return false;
}

std::string ChatMessage::getCustomTag() {
 // TODO: Implement getCustomTag
 return "";
}

void ChatMessage::setCustomTag(const std::string &_customTag) {
 // TODO: Implement setCustomTag
}

Color ChatMessage::getTextColor() {
 // TODO: Implement getTextColor
 return nullptr;
}

void ChatMessage::setTextColor(Color _textColor) {
 // TODO: Implement setTextColor
}

bool ChatMessage::isCustomColor() {
 // TODO: Implement isCustomColor
 return false;
}

void ChatMessage::pack(ByteBufferWriter b) {
 // TODO: Implement pack
}

ChatMessage ChatMessage::clone() {
 // TODO: Implement clone
 return nullptr;
}

bool ChatMessage::isServerAlert() {
 // TODO: Implement isServerAlert
 return false;
}

void ChatMessage::setServerAlert(bool _serverAlert) {
 // TODO: Implement setServerAlert
}

std::string ChatMessage::toString() {
 // TODO: Implement toString
 return "";
}

} // namespace chat
} // namespace zombie
