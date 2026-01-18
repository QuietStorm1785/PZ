#pragma once
#include <mutex>
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/defaultChats/AdminChat.h"
#include "zombie/chat/defaultChats/FactionChat.h"
#include "zombie/chat/defaultChats/GeneralChat.h"
#include "zombie/chat/defaultChats/RadioChat.h"
#include "zombie/chat/defaultChats/SafehouseChat.h"
#include "zombie/chat/defaultChats/SayChat.h"
#include "zombie/chat/defaultChats/ServerChat.h"
#include "zombie/chat/defaultChats/ShoutChat.h"
#include "zombie/chat/defaultChats/WhisperChat.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManagerData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/radio/devices/DeviceData.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ChatManager {
public:
 static ChatManager instance = nullptr;
 UdpConnection serverConnection = nullptr;
private
 HashMap<Integer, ChatBase> mpChats;
private
 HashMap<String, WhisperChat> whisperChats;
private
 HashMap<String, WhisperChatCreation> whisperChatCreation =
 std::make_unique<HashMap<>>();
private
 HashMap<Short, ChatTab> tabs;
 ChatTab focusTab;
 IsoPlayer player;
 std::string myNickname;
 bool singlePlayerMode = false;
 GeneralChat generalChat = nullptr;
 SayChat sayChat = nullptr;
 ShoutChat shoutChat = nullptr;
 FactionChat factionChat = nullptr;
 SafehouseChat safehouseChat = nullptr;
 RadioChat radioChat = nullptr;
 AdminChat adminChat = nullptr;
 ServerChat serverChat = nullptr;
private
 ChatManager.Stage chatManagerStage = ChatManager.Stage.notStarted;
private
 static ZLogger logger;
 static const std::string logNamePrefix = "client chat";

private
 ChatManager() {
 this->mpChats = std::make_unique<HashMap<>>();
 this->tabs = std::make_unique<HashMap<>>();
 this->whisperChats = std::make_unique<HashMap<>>();
 }

 static ChatManager getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<ChatManager>();
 }

 return instance;
 }

 bool isSinglePlayerMode() { return this->singlePlayerMode; }

 bool isWorking() {
 return this->chatManagerStage == ChatManager.Stage.working;
 }

 void init(bool boolean0, IsoPlayer playerx) {
 LoggerManager.init();
 LoggerManager.createLogger("client chat " + playerx.getDisplayName(),
 Core.bDebug);
 logger = LoggerManager.getLogger("client chat " + playerx.getDisplayName());
 logger.write("Init chat system...", "info");
 logger.write("Mode: " + (boolean0 ? "single player" : "multiplayer"),
 "info");
 logger.write("Chat owner: " + playerx.getDisplayName(), "info");
 this->chatManagerStage = ChatManager.Stage.starting;
 this->singlePlayerMode = boolean0;
 this->generalChat = nullptr;
 this->sayChat = nullptr;
 this->shoutChat = nullptr;
 this->factionChat = nullptr;
 this->safehouseChat = nullptr;
 this->radioChat = nullptr;
 this->adminChat = nullptr;
 this->serverChat = nullptr;
 this->mpChats.clear();
 this->tabs.clear();
 this->focusTab = nullptr;
 this->whisperChats.clear();
 this->player = playerx;
 this->myNickname = this->player.username;
 if (boolean0) {
 this->serverConnection = nullptr;
 this->sayChat = std::make_unique<SayChat>();
 this->sayChat.Init();
 this->generalChat = std::make_unique<GeneralChat>();
 this->shoutChat = std::make_unique<ShoutChat>();
 this->shoutChat.Init();
 this->radioChat = std::make_unique<RadioChat>();
 this->radioChat.Init();
 this->adminChat = std::make_unique<AdminChat>();
 } else {
 this->serverConnection = GameClient.connection;
 LuaEventManager.triggerEvent("OnChatWindowInit");
 }
 }

 void processInitPlayerChatPacket(ByteBuffer byteBuffer) {
 this->init(false, IsoPlayer.getInstance());
 short short0 = byteBuffer.getShort();

 for (int int0 = 0; int0 < short0; int0++) {
 ChatTab chatTab =
 new ChatTab(byteBuffer.getShort(), GameWindow.ReadString(byteBuffer);
 this->tabs.put(chatTab.getID(), chatTab);
 }

 this->addTab((short)0);
 this->focusOnTab(this->tabs.get((short)0).getID());
 LuaEventManager.triggerEvent("OnSetDefaultTab",
 this->tabs.get((short)0).getTitle());
 }

 void setFullyConnected() {
 this->chatManagerStage = ChatManager.Stage.working;
 }

 void processAddTabPacket(ByteBuffer byteBuffer) {
 this->addTab(byteBuffer.getShort());
 }

 void processRemoveTabPacket(ByteBuffer byteBuffer) {
 this->removeTab(byteBuffer.getShort());
 }

 void processJoinChatPacket(ByteBuffer byteBuffer) {
 ChatType chatType = ChatType.valueOf(byteBuffer.getInt());
 ChatTab chatTab = this->tabs.get(byteBuffer.getShort());
 void *object = nullptr;
 switch (chatType) {
 case general:
 this->generalChat = new GeneralChat(byteBuffer, chatTab, this->player);
 object = this->generalChat;
 break;
 case say:
 this->sayChat = new SayChat(byteBuffer, chatTab, this->player);
 this->sayChat.Init();
 object = this->sayChat;
 break;
 case shout:
 this->shoutChat = new ShoutChat(byteBuffer, chatTab, this->player);
 this->shoutChat.Init();
 object = this->shoutChat;
 break;
 case whisper:
 WhisperChat whisperChat =
 new WhisperChat(byteBuffer, chatTab, this->player);
 whisperChat.init();
 this->whisperChats.put(whisperChat.getCompanionName(), whisperChat);
 object = whisperChat;
 break;
 case faction:
 this->factionChat = new FactionChat(byteBuffer, chatTab, this->player);
 object = this->factionChat;
 break;
 case safehouse:
 this->safehouseChat = new SafehouseChat(byteBuffer, chatTab, this->player);
 object = this->safehouseChat;
 break;
 case radio:
 this->radioChat = new RadioChat(byteBuffer, chatTab, this->player);
 this->radioChat.Init();
 object = this->radioChat;
 break;
 case admin:
 this->adminChat = new AdminChat(byteBuffer, chatTab, this->player);
 object = this->adminChat;
 break;
 case server:
 this->serverChat = new ServerChat(byteBuffer, chatTab, this->player);
 object = this->serverChat;
 break;
 default:
 DebugLog.log("Chat of type '" + chatType.toString() +
 "' is not supported to join to");
 return;
 }

 this->mpChats.put(((ChatBase)object).getID(), (ChatBase)object);
 ((ChatBase)object).setFontSize(Core.getInstance().getOptionChatFontSize());
 ((ChatBase)object)
 .setShowTimestamp(Core.getInstance().isOptionShowChatTimestamp());
 ((ChatBase)object).setShowTitle(Core.getInstance().isOptionShowChatTitle());
 }

 void processLeaveChatPacket(ByteBuffer byteBuffer) {
 int integer = byteBuffer.getInt();
 ChatType chatType = ChatType.valueOf(byteBuffer.getInt());
 switch (chatType) {
 case general:
 case say:
 case shout:
 case radio:
 case server:
 DebugLog.log("Chat type is '" + chatType.toString() +
 "'. Can't leave it. Ignored.");
 break;
 case whisper:
 this->whisperChats.remove(
 ((WhisperChat)this->mpChats.get(integer).getCompanionName());
 this->mpChats.remove(integer);
 break;
 case faction:
 this->mpChats.remove(integer);
 this->factionChat = nullptr;
 DebugLog.log("You leaved faction chat");
 break;
 case safehouse:
 this->mpChats.remove(integer);
 this->safehouseChat = nullptr;
 DebugLog.log("You leaved safehouse chat");
 break;
 case admin:
 this->mpChats.remove(integer);
 this->removeTab(this->adminChat.getTabID());
 this->adminChat = nullptr;
 DebugLog.log("You leaved admin chat");
 break;
 default:
 DebugLog.log("Chat of type '" + chatType.toString() +
 "' is not supported to leave to");
 }
 }

 void processPlayerNotFound(const std::string &string) {
 logger.write("Got player not found packet", "info");
 WhisperChatCreation whisperChatCreationx =
 this->whisperChatCreation.get(string);
 if (whisperChatCreationx != nullptr) {
 whisperChatCreationx.status = WhisperChat.ChatStatus.PlayerNotFound;
 }
 }

 ChatMessage unpackMessage(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.getInt();
 ChatBase chatBase = this->mpChats.get(int0);
 return chatBase.unpackMessage(byteBuffer);
 }

 void processChatMessagePacket(ByteBuffer byteBuffer) {
 ChatMessage chatMessage = this->unpackMessage(byteBuffer);
 ChatBase chatBase = chatMessage.getChat();
 if (ChatUtility.chatStreamEnabled(chatBase.getType())) {
 chatBase.showMessage(chatMessage);
 logger.write("Got message from server: " + chatMessage, "info");
 } else {
 DebugLog.log("Can't process message '" + chatMessage.getText() +
 "' because '" + chatBase.getType() + "' chat is disabled");
 logger.write("Can't process message '" + chatMessage.getText() +
 "' because '" + chatBase.getType() +
 "' chat is disabled",
 "warning");
 }
 }

 void updateChatSettings(const std::string &string, bool boolean0,
 bool boolean1) {
 Core.getInstance().setOptionChatFontSize(string);
 Core.getInstance().setOptionShowChatTimestamp(boolean0);
 Core.getInstance().setOptionShowChatTitle(boolean1);

 for (ChatBase chatBase : this->mpChats.values()) {
 chatBase.setFontSize(string);
 chatBase.setShowTimestamp(boolean0);
 chatBase.setShowTitle(boolean1);
 }
 }

 void showInfoMessage(const std::string &string) {
 ChatMessage chatMessage = this->sayChat.createInfoMessage(string);
 this->sayChat.showMessage(chatMessage);
 }

 void showInfoMessage(const std::string &string1, const std::string &string0) {
 if (this->sayChat != nullptr) {
 ChatMessage chatMessage = this->sayChat.createInfoMessage(string0);
 chatMessage.setAuthor(string1);
 this->sayChat.showMessage(chatMessage);
 }
 }

 void sendMessageToChat(const std::string &string1, ChatType chatType,
 const std::string &string0) {
 string0 = string0.trim();
 if (!string0.empty()) {
 ChatBase chatBase = this->getChat(chatType);
 if (chatBase.empty()) {
 if (Core.bDebug) {
 throw IllegalArgumentException(
 "Chat '" + chatType +
 "' is nullptr. Chat should be init before use!");
 } else {
 this->showChatDisabledMessage(chatType);
 }
 } else {
 ChatMessage chatMessage = chatBase.createMessage(string0);
 chatMessage.setAuthor(string1);
 this->sendMessageToChat(chatBase, chatMessage);
 }
 }
 }

 void sendMessageToChat(ChatType chatType, const std::string &string) {
 this->sendMessageToChat(this->player.getUsername(), chatType, string);
 }

public
 void sendWhisperMessage(String string0, String string1) {
 logger.write("Send message '" + string1 + "' for player '" + string0 +
 "' in whisper chat",
 "info");
 if (ChatUtility.chatStreamEnabled(ChatType.whisper) {
 if (string0.empty() || string0.equalsIgnoreCase(this->myNickname) {
 logger.write("Message can't be send to yourself");
 this->showServerChatMessage(
 Translator.getText("UI_chat_whisper_message_to_yourself_error"));
 return;
 }

 if (this->whisperChats.containsKey(string0) {
 WhisperChat whisperChat = this->whisperChats.get(string0);
 this->sendMessageToChat(whisperChat, whisperChat.createMessage(string1);
 return;
 }

 if (this->whisperChatCreation.containsKey(string0) {
 WhisperChatCreation whisperChatCreation0 =
 this->whisperChatCreation.get(string0);
 whisperChatCreation0.messages.add(string1);
 return;
 }

 WhisperChatCreation whisperChatCreation1 =
 this->createWhisperChat(string0);
 whisperChatCreation1.messages.add(string1);
 } else {
 logger.write("Whisper chat is disabled", "info");
 this->showChatDisabledMessage(ChatType.whisper);
 }
 }

 bool isPlayerCanUseChat(ChatType chatType) {
 if (!ChatUtility.chatStreamEnabled(chatType) {
 return false;
 } else {
 switch (chatType) {
 case faction:
 return Faction.isAlreadyInFaction(this->player);
 case safehouse:
 return SafeHouse.hasSafehouse(this->player) != nullptr;
 case radio:
 return this->isPlayerCanUseRadioChat();
 case admin:
 return this->player.isAccessLevel("admin");
 default:
 return true;
 }
 }
 }

 void focusOnTab(short short0) {
 for (ChatTab chatTab : this->tabs.values()) {
 if (chatTab.getID() == short0) {
 this->focusTab = chatTab;
 return;
 }
 }

 throw RuntimeException("Tab with id = '" + short0 + "' not found");
 }

 std::string getTabName(short short0) {
 return this->tabs.containsKey(short0) ? this->tabs.get(short0).getTitle()
 : Short.toString(short0);
 }

 ChatTab getFocusTab() { return this->focusTab; }

 void showRadioMessage(ChatMessage chatMessage) {
 this->radioChat.showMessage(chatMessage);
 }

 void showRadioMessage(const std::string &string, int int0) {
 ChatMessage chatMessage = this->radioChat.createMessage(string);
 if (int0 != 0) {
 chatMessage.setRadioChannel(int0);
 }

 this->radioChat.showMessage(chatMessage);
 }

 void showStaticRadioSound(const std::string &string) {
 this->radioChat.showMessage(this->radioChat.createStaticSoundMessage(string);
 }

 ChatMessage createRadiostationMessage(const std::string &string, int int0) {
 return this->radioChat.createBroadcastingMessage(string, int0);
 }

 void showServerChatMessage(const std::string &string) {
 ServerChatMessage serverChatMessage =
 this->serverChat.createServerMessage(string);
 this->serverChat.showMessage(serverChatMessage);
 }

 void addMessage(int int0, const std::string &string1,
 const std::string &string0) {
 ChatBase chatBase = this->mpChats.get(int0);
 chatBase.showMessage(string0, string1);
 }

 void addMessage(const std::string &string0, const std::string &string1) {
 if (this->generalChat.empty()) {
 throw std::make_unique<RuntimeException>();
 } else {
 this->addMessage(this->generalChat.getID(), string0, string1);
 }
 }

 void sendMessageToChat(ChatBase chatBase, ChatMessage chatMessage0) {
 if (chatBase.getType() == ChatType.radio) {
 if (Core.bDebug) {
 throw IllegalArgumentException(
 "You can't send message to radio directly. Use radio and send say "
 "message");
 } else {
 DebugLog.log("You try to use radio chat directly. It's restricted. Try "
 "to use say chat");
 }
 } else {
 chatBase.showMessage(chatMessage0);
 if (chatBase.isEnabled()) {
 if (!this->isSinglePlayerMode() && !chatMessage0.isLocal()) {
 DeviceData deviceData = this->getTransmittingRadio();
 chatBase.sendToServer(chatMessage0, deviceData);
 if (deviceData != nullptr && chatBase.isSendingToRadio()) {
 ChatMessage chatMessage1 =
 this->radioChat.createMessage(chatMessage0.getText());
 chatMessage1.setRadioChannel(deviceData.getChannel());
 this->radioChat.sendToServer(chatMessage1, deviceData);
 }
 }
 } else {
 this->showChatDisabledMessage(chatBase.getType());
 }
 }
 }

 ChatBase getChat(ChatType chatType) {
 if (chatType == ChatType.whisper) {
 throw IllegalArgumentException("Whisper not unique chat");
 } else {
 switch (chatType) {
 case general:
 return this->generalChat;
 case say:
 return this->sayChat;
 case shout:
 return this->shoutChat;
 case whisper:
 default:
 throw IllegalArgumentException("Chat type is undefined");
 case faction:
 return this->factionChat;
 case safehouse:
 return this->safehouseChat;
 case radio:
 return this->radioChat;
 case admin:
 return this->adminChat;
 case server:
 return this->serverChat;
 }
 }
 }

 void addTab(short short0) {
 ChatTab chatTab = this->tabs.get(short0);
 if (!chatTab.isEnabled()) {
 chatTab.setEnabled(true);
 LuaEventManager.triggerEvent("OnTabAdded", chatTab.getTitle(),
 chatTab.getID());
 }
 }

 void removeTab(short short0) {
 ChatTab chatTab = this->tabs.get(short0);
 if (chatTab.isEnabled()) {
 LuaEventManager.triggerEvent("OnTabRemoved", chatTab.getTitle(),
 chatTab.getID());
 chatTab.setEnabled(false);
 }
 }

 WhisperChatCreation createWhisperChat(const std::string &string) {
 logger.write("Whisper chat is not created for '" + string + "'", "info");
 WhisperChatCreation whisperChatCreationx = new WhisperChatCreation();
 whisperChatCreationx.destPlayerName = string;
 whisperChatCreationx.status = WhisperChat.ChatStatus.Creating;
 whisperChatCreationx.createTime = System.currentTimeMillis();
 this->whisperChatCreation.put(string, whisperChatCreationx);
 ByteBufferWriter byteBufferWriter = this->serverConnection.startPacket();
 PacketTypes.PacketType.PlayerStartPMChat.doPacket(byteBufferWriter);
 byteBufferWriter.putUTF(this->myNickname);
 byteBufferWriter.putUTF(string);
 PacketTypes.PacketType.PlayerStartPMChat.send(this->serverConnection);
 logger.write("'Start PM chat' package sent. Waiting for a creating whisper "
 "chat by server...",
 "info");
 return whisperChatCreationx;
 }

 static void UpdateClient() {
 if (instance != nullptr) {
 try {
 instance.updateClient();
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }
 }

 void updateClient() {
 if (this->isWorking()) {
 this->updateWhisperChat();
 }
 }

 void updateWhisperChat() {
 if (!this->whisperChatCreation.empty()) {
 long long0 = System.currentTimeMillis();

 for (WhisperChatCreation whisperChatCreationx :
 new ArrayList<>(this->whisperChatCreation.values())) {
 if (this->whisperChats.containsKey(
 whisperChatCreationx.destPlayerName) {
 WhisperChat whisperChat =
 this->whisperChats.get(whisperChatCreationx.destPlayerName);
 logger.write("Whisper chat created between '" + this->myNickname +
 "' and '" + whisperChatCreationx.destPlayerName +
 "' and has id = " + whisperChat.getID(),
 "info");
 this->whisperChatCreation.remove(whisperChatCreationx.destPlayerName);

 for (String string : whisperChatCreationx.messages) {
 this->sendMessageToChat(whisperChat,
 whisperChat.createMessage(string);
 }
 } else if (whisperChatCreationx.status ==
 WhisperChat.ChatStatus.PlayerNotFound) {
 logger.write("Player '" + whisperChatCreationx.destPlayerName +
 "' is not found. Chat is not created",
 "info");
 this->whisperChatCreation.remove(whisperChatCreationx.destPlayerName);
 this->showServerChatMessage(
 Translator.getText("UI_chat_whisper_player_not_found_error",
 whisperChatCreationx.destPlayerName);
 } else if (whisperChatCreationx.status ==
 WhisperChat.ChatStatus.Creating &&
 long0 - whisperChatCreationx.createTime >= 10000L) {
 logger.write(
 "Whisper chat is not created by timeout. See server chat logs",
 "error");
 this->whisperChatCreation.remove(whisperChatCreationx.destPlayerName);
 }
 }
 }
 }

 void showChatDisabledMessage(ChatType chatType0) {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append(
 Translator.getText("UI_chat_chat_disabled_msg",
 Translator.getText(chatType0.getTitleID())));

 for (ChatType chatType1 : ChatUtility.getAllowedChatStreams()) {
 if (this->isPlayerCanUseChat(chatType1) {
 stringBuilder.append(" * ")
 .append(Translator.getText(chatType1.getTitleID()))
 .append(" <LINE> ");
 }
 }

 this->showServerChatMessage(stringBuilder.toString());
 }

 bool isPlayerCanUseRadioChat() {
 Radio radio = this->player.getEquipedRadio();
 if (radio != nullptr && radio.getDeviceData() != nullptr) {
 bool boolean0 = radio.getDeviceData().getIsTurnedOn();
 boolean0 &= radio.getDeviceData().getIsTwoWay();
 boolean0 &= radio.getDeviceData().getIsPortable();
 return boolean0 & !radio.getDeviceData().getMicIsMuted();
 } else {
 return false;
 }
 }

 DeviceData getTransmittingRadio() {
 if (this->player.getOnlineID() == -1) {
 return nullptr;
 } else {
 VoiceManagerData voiceManagerData =
 VoiceManagerData.get(this->player.getOnlineID());
 { std::lock_guard<std::mutex> __sync_lock__(voiceManagerData.radioData_mutex);
 return voiceManagerData.radioData.stream()
 .filter(VoiceManagerData.RadioData::isTransmissionAvailable)
 .findFirst()
 .map(VoiceManagerData.RadioData::getDeviceData)
 .orElse(nullptr);
 }
 }
 }

private
 static enum Stage { notStarted, starting, working; }
}
} // namespace chat
} // namespace zombie
