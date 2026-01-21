#include <string>
#include <vector>
#include "zombie/chat/ChatBase.h"

namespace zombie {
namespace chat {

protected ChatBase::ChatBase(ChatType var1) {
    // TODO: Implement ChatBase
    return nullptr;
}

public ChatBase::ChatBase(ByteBuffer var1, ChatType var2, ChatTab var3, IsoPlayer var4) {
    // TODO: Implement ChatBase
    return nullptr;
}

public ChatBase::ChatBase(int var1, ChatType var2, ChatTab var3) {
    // TODO: Implement ChatBase
    return nullptr;
}

bool ChatBase::isEnabled() {
    // TODO: Implement isEnabled
    return false;
}

std::string ChatBase::getChatOwnerName() {
    // TODO: Implement getChatOwnerName
    return "";
}

IsoPlayer ChatBase::getChatOwner() {
    // TODO: Implement getChatOwner
    return nullptr;
}

ChatMode ChatBase::getMode() {
    // TODO: Implement getMode
    return nullptr;
}

ChatType ChatBase::getType() {
    // TODO: Implement getType
    return nullptr;
}

int ChatBase::getID() {
    // TODO: Implement getID
    return 0;
}

std::string ChatBase::getTitleID() {
    // TODO: Implement getTitleID
    return "";
}

Color ChatBase::getColor() {
    // TODO: Implement getColor
    return nullptr;
}

short ChatBase::getTabID() {
    // TODO: Implement getTabID
    return 0;
}

float ChatBase::getRange() {
    // TODO: Implement getRange
    return 0;
}

bool ChatBase::isSendingToRadio() {
    // TODO: Implement isSendingToRadio
    return false;
}

float ChatBase::getZombieAttractionRange() {
    // TODO: Implement getZombieAttractionRange
    return 0;
}

void ChatBase::setSettings(ChatSettings var1) {
    // TODO: Implement setSettings
}

void ChatBase::setFontSize(const std::string& var1) {
    // TODO: Implement setFontSize
}

void ChatBase::setShowTimestamp(bool var1) {
    // TODO: Implement setShowTimestamp
}

void ChatBase::setShowTitle(bool var1) {
    // TODO: Implement setShowTitle
}

bool ChatBase::isCustomSettings() {
    // TODO: Implement isCustomSettings
    return false;
}

bool ChatBase::isAllowImages() {
    // TODO: Implement isAllowImages
    return false;
}

bool ChatBase::isAllowChatIcons() {
    // TODO: Implement isAllowChatIcons
    return false;
}

bool ChatBase::isAllowColors() {
    // TODO: Implement isAllowColors
    return false;
}

bool ChatBase::isAllowFonts() {
    // TODO: Implement isAllowFonts
    return false;
}

bool ChatBase::isAllowBBcode() {
    // TODO: Implement isAllowBBcode
    return false;
}

bool ChatBase::isEqualizeLineHeights() {
    // TODO: Implement isEqualizeLineHeights
    return false;
}

bool ChatBase::isShowAuthor() {
    // TODO: Implement isShowAuthor
    return false;
}

bool ChatBase::isShowTimestamp() {
    // TODO: Implement isShowTimestamp
    return false;
}

bool ChatBase::isShowTitle() {
    // TODO: Implement isShowTitle
    return false;
}

std::string ChatBase::getFontSize() {
    // TODO: Implement getFontSize
    return "";
}

std::string ChatBase::getTitle() {
    // TODO: Implement getTitle
    return "";
}

void ChatBase::close() {
    // TODO: Implement close
}

void ChatBase::packChat(ByteBufferWriter var1) {
    // TODO: Implement packChat
}

ChatMessage ChatBase::unpackMessage(ByteBuffer var1) {
    // TODO: Implement unpackMessage
    return nullptr;
}

void ChatBase::packMessage(ByteBufferWriter var1, ChatMessage var2) {
    // TODO: Implement packMessage
}

ChatMessage ChatBase::createMessage(const std::string& var1) {
    // TODO: Implement createMessage
    return nullptr;
}

ChatMessage ChatBase::createMessage(const std::string& var1, const std::string& var2) {
    // TODO: Implement createMessage
    return nullptr;
}

ServerChatMessage ChatBase::createServerMessage(const std::string& var1) {
    // TODO: Implement createServerMessage
    return nullptr;
}

void ChatBase::showMessage(const std::string& var1, const std::string& var2) {
    // TODO: Implement showMessage
}

void ChatBase::showMessage(ChatMessage var1) {
    // TODO: Implement showMessage
}

std::string ChatBase::getMessageTextWithPrefix(ChatMessage var1) {
    // TODO: Implement getMessageTextWithPrefix
    return "";
}

void ChatBase::sendMessageToChatMembers(ChatMessage var1) {
    // TODO: Implement sendMessageToChatMembers
}

void ChatBase::sendMessageToChatMembers(ServerChatMessage var1) {
    // TODO: Implement sendMessageToChatMembers
}

void ChatBase::sendMessageToPlayer(UdpConnection var1, ChatMessage var2) {
    // TODO: Implement sendMessageToPlayer
}

void ChatBase::sendMessageToPlayer(short var1, ChatMessage var2) {
    // TODO: Implement sendMessageToPlayer
}

std::string ChatBase::getMessagePrefix(ChatMessage var1) {
    // TODO: Implement getMessagePrefix
    return "";
}

std::string ChatBase::getColorTag() {
    // TODO: Implement getColorTag
    return "";
}

std::string ChatBase::getColorTag(Color var1) {
    // TODO: Implement getColorTag
    return "";
}

std::string ChatBase::getFontSizeTag() {
    // TODO: Implement getFontSizeTag
    return "";
}

std::string ChatBase::getChatSettingsTags() {
    // TODO: Implement getChatSettingsTags
    return "";
}

void ChatBase::addMember(short var1) {
    // TODO: Implement addMember
}

void ChatBase::leaveMember(short var1) {
    // TODO: Implement leaveMember
}

bool ChatBase::hasMember(short var1) {
    // TODO: Implement hasMember
    return false;
}

void ChatBase::removeMember(short var1) {
    // TODO: Implement removeMember
}

void ChatBase::syncMembersByUsernames(std::vector<std::string> var1) {
    // TODO: Implement syncMembersByUsernames
}

void ChatBase::syncMembers(std::vector<int16_t> var1) {
    // TODO: Implement syncMembers
}

void ChatBase::sendPlayerJoinChatPacket(UdpConnection var1) {
    // TODO: Implement sendPlayerJoinChatPacket
}

void ChatBase::sendPlayerLeaveChatPacket(short var1) {
    // TODO: Implement sendPlayerLeaveChatPacket
}

void ChatBase::sendPlayerLeaveChatPacket(UdpConnection var1) {
    // TODO: Implement sendPlayerLeaveChatPacket
}

void ChatBase::sendToServer(ChatMessage var1, DeviceData var2) {
    // TODO: Implement sendToServer
}

void ChatBase::sendChatMessageToPlayer(UdpConnection var1, ChatMessage var2) {
    // TODO: Implement sendChatMessageToPlayer
}

void ChatBase::sendChatMessageFromPlayer(UdpConnection var1, ChatMessage var2) {
    // TODO: Implement sendChatMessageFromPlayer
}

bool ChatBase::hasChatTab() {
    // TODO: Implement hasChatTab
    return false;
}

} // namespace chat
} // namespace zombie
