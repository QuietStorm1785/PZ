#include "zombie/chat/ChatManager.h"

namespace zombie {
namespace chat {

private
ChatManager::ChatManager() {
 // TODO: Implement ChatManager
 return nullptr;
}

ChatManager ChatManager::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

bool ChatManager::isSinglePlayerMode() {
 // TODO: Implement isSinglePlayerMode
 return false;
}

bool ChatManager::isWorking() {
 // TODO: Implement isWorking
 return false;
}

void ChatManager::init(bool boolean0, IsoPlayer playerx) {
 // TODO: Implement init
}

void ChatManager::processInitPlayerChatPacket(ByteBuffer byteBuffer) {
 // TODO: Implement processInitPlayerChatPacket
}

void ChatManager::setFullyConnected() {
 // TODO: Implement setFullyConnected
}

void ChatManager::processAddTabPacket(ByteBuffer byteBuffer) {
 // TODO: Implement processAddTabPacket
}

void ChatManager::processRemoveTabPacket(ByteBuffer byteBuffer) {
 // TODO: Implement processRemoveTabPacket
}

void ChatManager::processJoinChatPacket(ByteBuffer byteBuffer) {
 // TODO: Implement processJoinChatPacket
}

void ChatManager::processLeaveChatPacket(ByteBuffer byteBuffer) {
 // TODO: Implement processLeaveChatPacket
}

void ChatManager::processPlayerNotFound(const std::string &string) {
 // TODO: Implement processPlayerNotFound
}

ChatMessage ChatManager::unpackMessage(ByteBuffer byteBuffer) {
 // TODO: Implement unpackMessage
 return nullptr;
}

void ChatManager::processChatMessagePacket(ByteBuffer byteBuffer) {
 // TODO: Implement processChatMessagePacket
}

void ChatManager::updateChatSettings(const std::string &string, bool boolean0,
 bool boolean1) {
 // TODO: Implement updateChatSettings
}

void ChatManager::showInfoMessage(const std::string &string) {
 // TODO: Implement showInfoMessage
}

void ChatManager::showInfoMessage(const std::string &string1,
 const std::string &string0) {
 // TODO: Implement showInfoMessage
}

void ChatManager::sendMessageToChat(const std::string &string1,
 ChatType chatType,
 const std::string &string0) {
 // TODO: Implement sendMessageToChat
}

void ChatManager::sendMessageToChat(ChatType chatType,
 const std::string &string) {
 // TODO: Implement sendMessageToChat
}

bool ChatManager::isPlayerCanUseChat(ChatType chatType) {
 // TODO: Implement isPlayerCanUseChat
 return false;
}

void ChatManager::focusOnTab(short short0) {
 // TODO: Implement focusOnTab
}

std::string ChatManager::getTabName(short short0) {
 // TODO: Implement getTabName
 return "";
}

ChatTab ChatManager::getFocusTab() {
 // TODO: Implement getFocusTab
 return nullptr;
}

void ChatManager::showRadioMessage(ChatMessage chatMessage) {
 // TODO: Implement showRadioMessage
}

void ChatManager::showRadioMessage(const std::string &string, int int0) {
 // TODO: Implement showRadioMessage
}

void ChatManager::showStaticRadioSound(const std::string &string) {
 // TODO: Implement showStaticRadioSound
}

ChatMessage ChatManager::createRadiostationMessage(const std::string &string,
 int int0) {
 // TODO: Implement createRadiostationMessage
 return nullptr;
}

void ChatManager::showServerChatMessage(const std::string &string) {
 // TODO: Implement showServerChatMessage
}

void ChatManager::addMessage(int int0, const std::string &string1,
 const std::string &string0) {
 // TODO: Implement addMessage
}

void ChatManager::addMessage(const std::string &string0,
 const std::string &string1) {
 // TODO: Implement addMessage
}

void ChatManager::sendMessageToChat(ChatBase chatBase,
 ChatMessage chatMessage0) {
 // TODO: Implement sendMessageToChat
}

ChatBase ChatManager::getChat(ChatType chatType) {
 // TODO: Implement getChat
 return nullptr;
}

void ChatManager::addTab(short short0) {
 // TODO: Implement addTab
}

void ChatManager::removeTab(short short0) {
 // TODO: Implement removeTab
}

WhisperChatCreation ChatManager::createWhisperChat(const std::string &string) {
 // TODO: Implement createWhisperChat
 return nullptr;
}

void ChatManager::UpdateClient() {
 // TODO: Implement UpdateClient
}

void ChatManager::updateClient() {
 // TODO: Implement updateClient
}

void ChatManager::updateWhisperChat() {
 // TODO: Implement updateWhisperChat
}

void ChatManager::showChatDisabledMessage(ChatType chatType0) {
 // TODO: Implement showChatDisabledMessage
}

bool ChatManager::isPlayerCanUseRadioChat() {
 // TODO: Implement isPlayerCanUseRadioChat
 return false;
}

DeviceData ChatManager::getTransmittingRadio() {
 // TODO: Implement getTransmittingRadio
 return nullptr;
}

} // namespace chat
} // namespace zombie
