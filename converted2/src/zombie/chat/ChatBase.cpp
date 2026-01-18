#include "zombie/chat/ChatBase.h"

namespace zombie {
namespace chat {

protected
ChatBase::ChatBase(ChatType chatType) {
  // TODO: Implement ChatBase
  return nullptr;
}

public
ChatBase::ChatBase(ByteBuffer bb, ChatType _type, ChatTab tab,
                   IsoPlayer owner) {
  // TODO: Implement ChatBase
  return nullptr;
}

public
ChatBase::ChatBase(int _id, ChatType _type, ChatTab tab) {
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

void ChatBase::setSettings(ChatSettings _settings) {
  // TODO: Implement setSettings
}

void ChatBase::setFontSize(const std::string &fontSize) {
  // TODO: Implement setFontSize
}

void ChatBase::setShowTimestamp(bool showTimestamp) {
  // TODO: Implement setShowTimestamp
}

void ChatBase::setShowTitle(bool showTitle) {
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

void ChatBase::packChat(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement packChat
}

ChatMessage ChatBase::unpackMessage(ByteBuffer bb) {
  // TODO: Implement unpackMessage
  return nullptr;
}

void ChatBase::packMessage(ByteBufferWriter b, ChatMessage msg) {
  // TODO: Implement packMessage
}

ChatMessage ChatBase::createMessage(const std::string &text) {
  // TODO: Implement createMessage
  return nullptr;
}

ChatMessage ChatBase::createMessage(const std::string &string1,
                                    const std::string &string0) {
  // TODO: Implement createMessage
  return nullptr;
}

ServerChatMessage ChatBase::createServerMessage(const std::string &text) {
  // TODO: Implement createServerMessage
  return nullptr;
}

void ChatBase::showMessage(const std::string &text, const std::string &author) {
  // TODO: Implement showMessage
}

void ChatBase::showMessage(ChatMessage msg) {
  // TODO: Implement showMessage
}

std::string ChatBase::getMessageTextWithPrefix(ChatMessage msg) {
  // TODO: Implement getMessageTextWithPrefix
  return "";
}

void ChatBase::sendMessageToChatMembers(ChatMessage msg) {
  // TODO: Implement sendMessageToChatMembers
}

void ChatBase::sendMessageToChatMembers(ServerChatMessage msg) {
  // TODO: Implement sendMessageToChatMembers
}

void ChatBase::sendMessageToPlayer(UdpConnection connection, ChatMessage msg) {
  // TODO: Implement sendMessageToPlayer
}

void ChatBase::sendMessageToPlayer(short playerID, ChatMessage msg) {
  // TODO: Implement sendMessageToPlayer
}

std::string ChatBase::getMessagePrefix(ChatMessage msg) {
  // TODO: Implement getMessagePrefix
  return "";
}

std::string ChatBase::getColorTag() {
  // TODO: Implement getColorTag
  return "";
}

std::string ChatBase::getColorTag(Color color) {
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

void ChatBase::addMember(short playerID) {
  // TODO: Implement addMember
}

void ChatBase::leaveMember(short playerID) {
  // TODO: Implement leaveMember
}

bool ChatBase::hasMember(short short0) {
  // TODO: Implement hasMember
  return false;
}

void ChatBase::removeMember(short playerID) {
  // TODO: Implement removeMember
}

void ChatBase::syncMembersByUsernames(ArrayList<String> players) {
  // TODO: Implement syncMembersByUsernames
}

void ChatBase::syncMembers(ArrayList<Short> arrayList0) {
  // TODO: Implement syncMembers
}

void ChatBase::sendPlayerJoinChatPacket(UdpConnection playerConnection) {
  // TODO: Implement sendPlayerJoinChatPacket
}

void ChatBase::sendPlayerLeaveChatPacket(short playerID) {
  // TODO: Implement sendPlayerLeaveChatPacket
}

void ChatBase::sendPlayerLeaveChatPacket(UdpConnection connection) {
  // TODO: Implement sendPlayerLeaveChatPacket
}

void ChatBase::sendToServer(ChatMessage msg, DeviceData deviceData) {
  // TODO: Implement sendToServer
}

void ChatBase::sendChatMessageToPlayer(UdpConnection udpConnection,
                                       ChatMessage chatMessage) {
  // TODO: Implement sendChatMessageToPlayer
}

void ChatBase::sendChatMessageFromPlayer(UdpConnection udpConnection,
                                         ChatMessage chatMessage) {
  // TODO: Implement sendChatMessageFromPlayer
}

bool ChatBase::hasChatTab() {
  // TODO: Implement hasChatTab
  return false;
}

} // namespace chat
} // namespace zombie
