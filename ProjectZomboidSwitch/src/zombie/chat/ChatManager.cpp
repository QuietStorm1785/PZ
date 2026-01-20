#include <string>
#include "zombie\chat/ChatManager.h"

namespace zombie {
namespace chat {

private ChatManager::ChatManager() {
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

void ChatManager::init(bool var1, IsoPlayer var2) {
    // TODO: Implement init
}

void ChatManager::processInitPlayerChatPacket(ByteBuffer var1) {
    // TODO: Implement processInitPlayerChatPacket
}

void ChatManager::setFullyConnected() {
    // TODO: Implement setFullyConnected
}

void ChatManager::processAddTabPacket(ByteBuffer var1) {
    // TODO: Implement processAddTabPacket
}

void ChatManager::processRemoveTabPacket(ByteBuffer var1) {
    // TODO: Implement processRemoveTabPacket
}

void ChatManager::processJoinChatPacket(ByteBuffer var1) {
    // TODO: Implement processJoinChatPacket
}

void ChatManager::processLeaveChatPacket(ByteBuffer var1) {
    // TODO: Implement processLeaveChatPacket
}

void ChatManager::processPlayerNotFound(const std::string& var1) {
    // TODO: Implement processPlayerNotFound
}

ChatMessage ChatManager::unpackMessage(ByteBuffer var1) {
    // TODO: Implement unpackMessage
    return nullptr;
}

void ChatManager::processChatMessagePacket(ByteBuffer var1) {
    // TODO: Implement processChatMessagePacket
}

void ChatManager::updateChatSettings(const std::string& var1, bool var2, bool var3) {
    // TODO: Implement updateChatSettings
}

void ChatManager::showInfoMessage(const std::string& var1) {
    // TODO: Implement showInfoMessage
}

void ChatManager::showInfoMessage(const std::string& var1, const std::string& var2) {
    // TODO: Implement showInfoMessage
}

void ChatManager::sendMessageToChat(const std::string& var1, ChatType var2, const std::string& var3) {
    // TODO: Implement sendMessageToChat
}

void ChatManager::sendMessageToChat(ChatType var1, const std::string& var2) {
    // TODO: Implement sendMessageToChat
}

bool ChatManager::isPlayerCanUseChat(ChatType var1) {
    // TODO: Implement isPlayerCanUseChat
    return false;
}

void ChatManager::focusOnTab(short var1) {
    // TODO: Implement focusOnTab
}

std::string ChatManager::getTabName(short var1) {
    // TODO: Implement getTabName
    return "";
}

ChatTab ChatManager::getFocusTab() {
    // TODO: Implement getFocusTab
    return nullptr;
}

void ChatManager::showRadioMessage(ChatMessage var1) {
    // TODO: Implement showRadioMessage
}

void ChatManager::showRadioMessage(const std::string& var1, int var2) {
    // TODO: Implement showRadioMessage
}

void ChatManager::showStaticRadioSound(const std::string& var1) {
    // TODO: Implement showStaticRadioSound
}

ChatMessage ChatManager::createRadiostationMessage(const std::string& var1, int var2) {
    // TODO: Implement createRadiostationMessage
    return nullptr;
}

void ChatManager::showServerChatMessage(const std::string& var1) {
    // TODO: Implement showServerChatMessage
}

void ChatManager::addMessage(int var1, const std::string& var2, const std::string& var3) {
    // TODO: Implement addMessage
}

void ChatManager::addMessage(const std::string& var1, const std::string& var2) {
    // TODO: Implement addMessage
}

void ChatManager::sendMessageToChat(ChatBase var1, ChatMessage var2) {
    // TODO: Implement sendMessageToChat
}

ChatBase ChatManager::getChat(ChatType var1) {
    // TODO: Implement getChat
    return nullptr;
}

void ChatManager::addTab(short var1) {
    // TODO: Implement addTab
}

void ChatManager::removeTab(short var1) {
    // TODO: Implement removeTab
}

WhisperChatCreation ChatManager::createWhisperChat(const std::string& var1) {
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

void ChatManager::showChatDisabledMessage(ChatType var1) {
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
