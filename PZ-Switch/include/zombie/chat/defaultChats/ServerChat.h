#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/chat/ServerChatMessage.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/chat/ChatType.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
namespace defaultChats {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerChat : public ChatBase {
public:
public
 ServerChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
 super(byteBuffer, ChatType.server, chatTab, player);
 this->setSettings(getDefaultSettings());
 }

public
 ServerChat(int int0, ChatTab chatTab) {
 super(int0, ChatType.server, chatTab);
 this->setSettings(getDefaultSettings());
 }

 static ChatSettings getDefaultSettings() {
 ChatSettings chatSettings = new ChatSettings();
 chatSettings.setBold(true);
 chatSettings.setFontColor(new Color(0, 128, 255, 255);
 chatSettings.setShowAuthor(false);
 chatSettings.setShowChatTitle(true);
 chatSettings.setShowTimestamp(false);
 chatSettings.setAllowColors(true);
 chatSettings.setAllowFonts(false);
 chatSettings.setAllowBBcode(false);
 return chatSettings;
 }

 ChatMessage createMessage(const std::string &string1,
 const std::string &string0, bool boolean0) {
 ChatMessage chatMessage = this->createMessage(string0);
 chatMessage.setAuthor(string1);
 if (boolean0) {
 chatMessage.setServerAlert(true);
 }

 return chatMessage;
 }

 ServerChatMessage createServerMessage(const std::string &string,
 bool boolean0) {
 ServerChatMessage serverChatMessage = this->createServerMessage(string);
 serverChatMessage.setServerAlert(boolean0);
 return serverChatMessage;
 }

 short getTabID() {
 return !GameClient.bClient
 ? super.getTabID()
 : ChatManager.getInstance().getFocusTab().getID();
 }

 ChatMessage unpackMessage(ByteBuffer byteBuffer) {
 ChatMessage chatMessage = super.unpackMessage(byteBuffer);
 chatMessage.setServerAlert(byteBuffer.get() == 1);
 chatMessage.setServerAuthor(byteBuffer.get() == 1);
 return chatMessage;
 }

 void packMessage(ByteBufferWriter byteBufferWriter, ChatMessage chatMessage) {
 super.packMessage(byteBufferWriter, chatMessage);
 byteBufferWriter.putBoolean(chatMessage.isServerAlert());
 byteBufferWriter.putBoolean(chatMessage.isServerAuthor());
 }

 std::string getMessagePrefix(ChatMessage chatMessage) {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append(this->getChatSettingsTags());
 bool boolean0 = false;
 if (this->isShowTitle()) {
 stringBuilder.append("[").append(this->getTitle()).append("]");
 boolean0 = true;
 }

 if (!chatMessage.isServerAuthor() && this->isShowAuthor()) {
 stringBuilder.append("[").append(chatMessage.getAuthor()).append("]");
 boolean0 = true;
 }

 if (boolean0) {
 stringBuilder.append(": ");
 }

 return stringBuilder.toString();
 }

 std::string getMessageTextWithPrefix(ChatMessage chatMessage) {
 return this->getMessagePrefix(chatMessage) + " " + chatMessage.getText();
 }

 void showMessage(ChatMessage chatMessage) {
 this->messages.add(chatMessage);
 if (this->isEnabled()) {
 LuaEventManager.triggerEvent("OnAddMessage", chatMessage,
 this->getTabID());
 }
 }

 void sendMessageToChatMembers(ChatMessage chatMessage) {
 for (short short0 : this->members) {
 this->sendMessageToPlayer(short0, chatMessage);
 }

 if (Core.bDebug) {
 DebugLog.log("New message '" + chatMessage +
 "' was sent members of chat '" + this->getID() + "'");
 }
 }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
