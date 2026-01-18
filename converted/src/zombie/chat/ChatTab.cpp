#include "zombie/chat/ChatTab.h"

namespace zombie {
namespace chat {

public ChatTab::ChatTab(short tabID, const std::string& _titleID) {
 // TODO: Implement ChatTab
 return nullptr;
}

public ChatTab::ChatTab(short tabID, const std::string& _titleID, int chatID) {
 // TODO: Implement ChatTab
 return nullptr;
}

void ChatTab::RemoveChat(int chatID) {
 // TODO: Implement RemoveChat
}

std::string ChatTab::getTitleID() {
 // TODO: Implement getTitleID
 return "";
}

std::string ChatTab::getTitle() {
 // TODO: Implement getTitle
 return "";
}

short ChatTab::getID() {
 // TODO: Implement getID
 return 0;
}

bool ChatTab::isEnabled() {
 // TODO: Implement isEnabled
 return false;
}

void ChatTab::setEnabled(bool _enabled) {
 // TODO: Implement setEnabled
}

void ChatTab::sendAddTabPacket(UdpConnection connection) {
 // TODO: Implement sendAddTabPacket
}

void ChatTab::sendRemoveTabPacket(UdpConnection connection) {
 // TODO: Implement sendRemoveTabPacket
}

} // namespace chat
} // namespace zombie
