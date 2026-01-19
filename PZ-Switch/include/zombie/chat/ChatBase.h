#pragma once
#include <mutex>
#include "java/time/LocalDateTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/radio/devices/DeviceData.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ChatBase {
public:

 // Mutexes for synchronized blocks
 std::mutex memberLock_mutex;
 static const int ID_NOT_SET = -29048394;
 int id;
 const std::string titleID;
 const ChatType type;
 ChatSettings settings;
 bool customSettings = false;
 ChatTab chatTab = nullptr;
 std::string translatedTitle;
protected
 ArrayList<Short> members;
private
 ArrayList<Short> justAddedMembers = std::make_unique<ArrayList<>>();
private
 ArrayList<Short> justRemovedMembers = std::make_unique<ArrayList<>>();
protected
 ArrayList<ChatMessage> messages;
 UdpConnection serverConnection;
 ChatMode mode;
 IsoPlayer chatOwner;
 const Lock memberLock = new ReentrantLock();

protected
 ChatBase(ChatType chatType) {
 this->settings = std::make_unique<ChatSettings>();
 this->customSettings = false;
 this->messages = std::make_unique<ArrayList<>>();
 this->id = -29048394;
 this->titleID = chatType.getTitleID();
 this->type = chatType;
 this->members = std::make_unique<ArrayList<>>();
 this->mode = ChatMode.SinglePlayer;
 this->serverConnection = nullptr;
 this->chatOwner = IsoPlayer.getInstance();
 }

 /**
 * Should called only on client side of chat system
 *
 * @param bb package from server that describe how chat should look and work
 * @param _type meta information about chat. Many parameters depends on that
 * @param tab tab where chat should show their info
 * @param owner actual player instance
 */
public
 ChatBase(ByteBuffer bb, ChatType _type, ChatTab tab, IsoPlayer owner) {
 this(_type);
 this->id = bb.getInt();
 this->customSettings = bb.get() == 1;
 if (this->customSettings) {
 this->settings = new ChatSettings(bb);
 }

 this->chatTab = tab;
 this->mode = ChatMode.ClientMultiPlayer;
 this->serverConnection = GameClient.connection;
 this->chatOwner = owner;
 }

 /**
 * Should be called only on server side of chat system
 *
 * @param _id unique id of chat. It will be used to identify chat in
 * client-server communication
 * @param _type meta information about chat. Many parameters depends on that
 * @param tab this tab will transferred to clients when it will connecting
 */
public
 ChatBase(int _id, ChatType _type, ChatTab tab) {
 this(_type);
 this->id = _id;
 this->chatTab = tab;
 this->mode = ChatMode.ServerMultiPlayer;
 }

 bool isEnabled() { return ChatUtility.chatStreamEnabled(this->type); }

 std::string getChatOwnerName() {
 if (this->chatOwner.empty()) {
 if (this->mode != ChatMode.ServerMultiPlayer) {
 if (Core.bDebug) {
 throw NullPointerException(
 "chat owner is nullptr but name quired");
 }

 DebugLog.log("chat owner is nullptr but name quired. Chat: " +
 this->getType());
 }

 return "";
 } else {
 return this->chatOwner.username;
 }
 }

 IsoPlayer getChatOwner() {
 if (this->chatOwner != nullptr || this->mode == ChatMode.ServerMultiPlayer) {
 return this->chatOwner;
 } else if (Core.bDebug) {
 throw NullPointerException("chat owner is nullptr");
 } else {
 DebugLog.log("chat owner is nullptr. Chat: " + this->getType());
 return nullptr;
 }
 }

 ChatMode getMode() { return this->mode; }

 ChatType getType() { return this->type; }

 int getID() { return this->id; }

 std::string getTitleID() { return this->titleID; }

 Color getColor() { return this->settings.getFontColor(); }

 short getTabID() { return this->chatTab.getID(); }

 float getRange() { return this->settings.getRange(); }

 bool isSendingToRadio() { return false; }

 float getZombieAttractionRange() {
 return this->settings.getZombieAttractionRange();
 }

 void setSettings(ChatSettings _settings) {
 this->settings = _settings;
 this->customSettings = true;
 }

 void setFontSize(std::string_view fontSize) {
 this->settings.setFontSize(fontSize.toLowerCase());
 }

 void setShowTimestamp(bool showTimestamp) {
 this->settings.setShowTimestamp(showTimestamp);
 }

 void setShowTitle(bool showTitle) {
 this->settings.setShowChatTitle(showTitle);
 }

 bool isCustomSettings() { return this->customSettings; }

 bool isAllowImages() { return this->settings.isAllowImages(); }

 bool isAllowChatIcons() { return this->settings.isAllowChatIcons(); }

 bool isAllowColors() { return this->settings.isAllowColors(); }

 bool isAllowFonts() { return this->settings.isAllowFonts(); }

 bool isAllowBBcode() { return this->settings.isAllowBBcode(); }

 bool isEqualizeLineHeights() { return this->settings.isEqualizeLineHeights(); }

 bool isShowAuthor() { return this->settings.isShowAuthor(); }

 bool isShowTimestamp() { return this->settings.isShowTimestamp(); }

 bool isShowTitle() { return this->settings.isShowChatTitle(); }

 std::string getFontSize() noexcept{ return this->settings.getFontSize().toString(); }

 std::string getTitle() {
 if (this->translatedTitle.empty()) {
 this->translatedTitle = Translator.getText(this->titleID);
 }

 return this->translatedTitle;
 }

 void close() {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 for (Short short0 : new ArrayList<>(this->members) {
 this->leaveMember(short0);
 }

 this->members.clear();
 }
 }

 void packChat(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putInt(this->type.getValue());
 byteBufferWriter.putShort(this->getTabID());
 byteBufferWriter.putInt(this->id);
 byteBufferWriter.putBoolean(this->customSettings);
 if (this->customSettings) {
 this->settings.pack(byteBufferWriter);
 }
 }

 ChatMessage unpackMessage(ByteBuffer bb) {
 std::string string0 = GameWindow.ReadString(bb);
 std::string string1 = GameWindow.ReadString(bb);
 ChatMessage chatMessage = this->createMessage(string1);
 chatMessage.setAuthor(string0);
 return chatMessage;
 }

 void packMessage(ByteBufferWriter b, ChatMessage msg) {
 b.putInt(this->id);
 b.putUTF(msg.getAuthor());
 b.putUTF(msg.getText());
 }

 /**
 * Message creator. Every chat know how to create its own message
 *
 * @param text text of the message
 * @return corresponding object to message
 */
 ChatMessage createMessage(std::string_view text) {
 return this->createMessage(this->getChatOwnerName(), text);
 }

 ChatMessage createMessage(std::string_view string1,
 std::string_view string0) {
 ChatMessage chatMessage = new ChatMessage(this, string0);
 chatMessage.setAuthor(string1);
 chatMessage.setServerAuthor(false);
 return chatMessage;
 }

 ServerChatMessage createServerMessage(std::string_view text) {
 ServerChatMessage serverChatMessage = new ServerChatMessage(this, text);
 serverChatMessage.setServerAuthor(true);
 return serverChatMessage;
 }

 void showMessage(std::string_view text, std::string_view author) {
 ChatMessage chatMessage = new ChatMessage(this, LocalDateTime.now(), text);
 chatMessage.setAuthor(author);
 this->showMessage(chatMessage);
 }

 void showMessage(ChatMessage msg) {
 this->messages.add(msg);
 if (this->isEnabled() && msg.isShowInChat() && this->chatTab != nullptr) {
 LuaEventManager.triggerEvent("OnAddMessage", msg, this->getTabID());
 }
 }

 std::string getMessageTextWithPrefix(ChatMessage msg) {
 return this->getMessagePrefix(msg) + " " +
 msg.getTextWithReplacedParentheses();
 }

 void sendMessageToChatMembers(ChatMessage msg) {
 IsoPlayer player0 = ChatUtility.findPlayer(msg.getAuthor());
 if (player0.empty()) {
 DebugLog.log("Author '" + msg.getAuthor() + "' not found");
 } else {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 for (short short0 : this->members) {
 IsoPlayer player1 = ChatUtility.findPlayer(short0);
 if (player1 != nullptr && player0.getOnlineID() != short0) {
 this->sendMessageToPlayer(short0, msg);
 }
 }
 }

 if (Core.bDebug) {
 DebugLog.log("New message '" + msg + "' was sent members of chat '" +
 this->getID() + "'");
 }
 }
 }

 void sendMessageToChatMembers(ServerChatMessage msg) {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 for (short short0 : this->members) {
 IsoPlayer player = ChatUtility.findPlayer(short0);
 if (player != nullptr) {
 this->sendMessageToPlayer(short0, msg);
 }
 }
 }

 if (Core.bDebug) {
 DebugLog.log("New message '" + msg + "' was sent members of chat '" +
 this->getID() + "'");
 }
 }

 void sendMessageToPlayer(UdpConnection connection, ChatMessage msg) {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 bool boolean0 = false;
 short[] shorts = connection.playerIDs;
 int int0 = shorts.length;

 for (int int1 = 0; int1 < int0; int1++) {
 short short0 = shorts[int1];
 if (boolean0) {
 break;
 }

 boolean0 = this->members.contains(short0);
 }

 if (!boolean0) {
 throw RuntimeException(
 "Passed connection didn't contained member of chat");
 } else {
 this->sendChatMessageToPlayer(connection, msg);
 }
 }
 }

 void sendMessageToPlayer(short playerID, ChatMessage msg) {
 UdpConnection udpConnection = ChatUtility.findConnection(playerID);
 if (udpConnection != nullptr) {
 this->sendChatMessageToPlayer(udpConnection, msg);
 DebugLog.log("Message '" + msg + "' was sent to player with id '" +
 playerID + "' of chat '" + this->getID() + "'");
 }
 }

 std::string getMessagePrefix(ChatMessage msg) {
 StringBuilder stringBuilder = new StringBuilder(this->getChatSettingsTags());
 if (this->isShowTimestamp()) {
 stringBuilder.append("[")
 .append(LuaManager.getHourMinuteJava())
 .append("]");
 }

 if (this->isShowTitle()) {
 stringBuilder.append("[").append(this->getTitle()).append("]");
 }

 if (this->isShowAuthor()) {
 stringBuilder.append("[").append(msg.getAuthor()).append("]");
 }

 stringBuilder.append(": ");
 return stringBuilder.toString();
 }

 std::string getColorTag() {
 Color color = this->getColor();
 return this->getColorTag(color);
 }

 std::string getColorTag(Color color) {
 return "<RGB:" + color.r + "," + color.g + "," + color.b + ">";
 }

 std::string getFontSizeTag() noexcept{
 return "<SIZE:" + this->settings.getFontSize() + ">";
 }

 std::string getChatSettingsTags() {
 return this->getColorTag() + " " + this->getFontSizeTag() + " ";
 }

 void addMember(short playerID) {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 if (!this->hasMember(playerID) {
 this->members.add(playerID);
 this->justAddedMembers.add(playerID);
 UdpConnection udpConnection = ChatUtility.findConnection(playerID);
 if (udpConnection != nullptr) {
 this->sendPlayerJoinChatPacket(udpConnection);
 this->chatTab.sendAddTabPacket(udpConnection);
 } else if (Core.bDebug) {
 throw RuntimeException("Connection should exist!");
 }
 }
 }
 }

 void leaveMember(short playerID) {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 if (this->hasMember(playerID) {
 this->justRemovedMembers.add(playerID);
 UdpConnection udpConnection = ChatUtility.findConnection(playerID);
 if (udpConnection != nullptr) {
 this->sendPlayerLeaveChatPacket(udpConnection);
 }

 this->members.remove(playerID);
 }
 }
 }

 bool hasMember(short short0) { return this->members.contains(short0); }

 void removeMember(short playerID) {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 if (this->hasMember(playerID) {
 this->members.remove(playerID);
 }
 }
 }

 void syncMembersByUsernames(ArrayList<String> players) {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 this->justAddedMembers.clear();
 this->justRemovedMembers.clear();
 std::vector arrayList = new ArrayList(players.size());
 void *object = nullptr;

 for (auto &string : players)
 object = ChatUtility.findPlayer(string);
 if (object != nullptr) {
 arrayList.add(((IsoPlayer)object).getOnlineID());
 }
 }

 this->syncMembers(arrayList);
 }
}

public ArrayList<Short>
getJustAddedMembers() {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex); return this->justAddedMembers; }
}

public
ArrayList<Short> getJustRemovedMembers() {
 { std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex); return this->justRemovedMembers; }
}

void syncMembers(ArrayList<Short> arrayList0) {
 for (auto &short0 : arrayList0)
 this->addMember(short0);
}

std::vector arrayList1 = new ArrayList();
{ std::lock_guard<std::mutex> __sync_lock__(memberLock_mutex);
 for (Short short1 : this->members) {
 if (!arrayList0.contains(short1) {
 arrayList1.add(short1);
 }
 }

 for (auto &short2 : arrayList1)
 this->leaveMember(short2);
}
}
}

void sendPlayerJoinChatPacket(UdpConnection playerConnection) {
 ByteBufferWriter byteBufferWriter = playerConnection.startPacket();
 PacketTypes.PacketType.PlayerJoinChat.doPacket(byteBufferWriter);
 this->packChat(byteBufferWriter);
 PacketTypes.PacketType.PlayerJoinChat.send(playerConnection);
}

void sendPlayerLeaveChatPacket(short playerID) {
 UdpConnection udpConnection = ChatUtility.findConnection(playerID);
 this->sendPlayerLeaveChatPacket(udpConnection);
}

void sendPlayerLeaveChatPacket(UdpConnection connection) {
 ByteBufferWriter byteBufferWriter = connection.startPacket();
 PacketTypes.PacketType.PlayerLeaveChat.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(this->getID());
 byteBufferWriter.putInt(this->getType().getValue());
 PacketTypes.PacketType.PlayerLeaveChat.send(connection);
}

void sendToServer(ChatMessage msg, DeviceData deviceData) {
 if (this->serverConnection.empty()) {
 DebugLog.log("Connection to server is nullptr in client chat");
 }

 this->sendChatMessageFromPlayer(this->serverConnection, msg);
}

void sendChatMessageToPlayer(UdpConnection udpConnection,
 ChatMessage chatMessage) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ChatMessageToPlayer.doPacket(byteBufferWriter);
 this->packMessage(byteBufferWriter, chatMessage);
 PacketTypes.PacketType.ChatMessageToPlayer.send(udpConnection);
}

void sendChatMessageFromPlayer(UdpConnection udpConnection,
 ChatMessage chatMessage) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.ChatMessageFromPlayer.doPacket(byteBufferWriter);
 this->packMessage(byteBufferWriter, chatMessage);
 PacketTypes.PacketType.ChatMessageFromPlayer.send(udpConnection);
}

bool hasChatTab() { return this->chatTab != nullptr; }
}
} // namespace chat
} // namespace zombie
