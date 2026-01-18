#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketTypes.h"

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ChatTab {
public:
 short id;
 std::string titleID;
 std::string translatedTitle;
 private HashSet<Integer> containedChats;
 bool enabled = false;

 public ChatTab(short tabID, const std::string& _titleID) {
 this->id = tabID;
 this->titleID = _titleID;
 this->translatedTitle = Translator.getText(_titleID);
 this->containedChats = std::make_unique<HashSet<>>();
 }

 public ChatTab(short tabID, const std::string& _titleID, int chatID) {
 this(tabID, _titleID);
 this->containedChats.add(chatID);
 }

 void RemoveChat(int chatID) {
 if (!this->containedChats.contains(chatID) {
 throw RuntimeException("Tab '" + this->id + "' doesn't contains a chat id: " + chatID);
 } else {
 this->containedChats.remove(chatID);
 }
 }

 std::string getTitleID() {
 return this->titleID;
 }

 std::string getTitle() {
 return this->translatedTitle;
 }

 short getID() {
 return this->id;
 }

 bool isEnabled() {
 return this->enabled;
 }

 void setEnabled(bool _enabled) {
 this->enabled = _enabled;
 }

 void sendAddTabPacket(UdpConnection connection) {
 ByteBufferWriter byteBufferWriter = connection.startPacket();
 PacketTypes.PacketType.AddChatTab.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(this->getID());
 PacketTypes.PacketType.AddChatTab.send(connection);
 }

 void sendRemoveTabPacket(UdpConnection connection) {
 ByteBufferWriter byteBufferWriter = connection.startPacket();
 PacketTypes.PacketType.RemoveChatTab.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(this->getID());
 PacketTypes.PacketType.RemoveChatTab.send(connection);
 }
}
} // namespace chat
} // namespace zombie
