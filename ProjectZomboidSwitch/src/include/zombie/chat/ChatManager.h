#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatManager/1.h"
#include "zombie/chat/ChatManager/Stage.h"
#include "zombie/chat/defaultChats/AdminChat.h"
#include "zombie/chat/defaultChats/FactionChat.h"
#include "zombie/chat/defaultChats/GeneralChat.h"
#include "zombie/chat/defaultChats/RadioChat.h"
#include "zombie/chat/defaultChats/SafehouseChat.h"
#include "zombie/chat/defaultChats/SayChat.h"
#include "zombie/chat/defaultChats/ServerChat.h"
#include "zombie/chat/defaultChats/ShoutChat.h"
#include "zombie/chat/defaultChats/WhisperChat.h"
#include "zombie/chat/defaultChats/WhisperChat/ChatStatus.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManagerData.h"
#include "zombie/core/raknet/VoiceManagerData/RadioData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/radio/devices/DeviceData.h"
#include <filesystem>

namespace zombie {
namespace chat {


class ChatManager {
public:
    static ChatManager instance = nullptr;
    UdpConnection serverConnection = nullptr;
   private const std::unordered_map<int, ChatBase> mpChats;
   private const std::unordered_map<std::string, WhisperChat> whisperChats;
   private const std::unordered_map<std::string, WhisperChatCreation> whisperChatCreation = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<int16_t, ChatTab> tabs;
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
    Stage chatManagerStage = Stage.notStarted;
   private static volatile ZLogger logger;
    static const std::string logNamePrefix = "client chat";

    private ChatManager() {
      this.mpChats = std::make_unique<std::unordered_map<>>();
      this.tabs = std::make_unique<std::unordered_map<>>();
      this.whisperChats = std::make_unique<std::unordered_map<>>();
   }

    static ChatManager getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<ChatManager>();
      }

    return instance;
   }

    bool isSinglePlayerMode() {
      return this.singlePlayerMode;
   }

    bool isWorking() {
      return this.chatManagerStage == Stage.working;
   }

    void init(bool var1, IsoPlayer var2) {
      LoggerManager.init();
      LoggerManager.createLogger("client chat " + var2.getDisplayName(), Core.bDebug);
      logger = LoggerManager.getLogger("client chat " + var2.getDisplayName());
      logger.write("Init chat system...", "info");
      logger.write("Mode: " + (var1 ? "single player" : "multiplayer"), "info");
      logger.write("Chat owner: " + var2.getDisplayName(), "info");
      this.chatManagerStage = Stage.starting;
      this.singlePlayerMode = var1;
      this.generalChat = nullptr;
      this.sayChat = nullptr;
      this.shoutChat = nullptr;
      this.factionChat = nullptr;
      this.safehouseChat = nullptr;
      this.radioChat = nullptr;
      this.adminChat = nullptr;
      this.serverChat = nullptr;
      this.mpChats.clear();
      this.tabs.clear();
      this.focusTab = nullptr;
      this.whisperChats.clear();
      this.player = var2;
      this.myNickname = this.player.username;
      if (var1) {
         this.serverConnection = nullptr;
         this.sayChat = std::make_unique<SayChat>();
         this.sayChat.Init();
         this.generalChat = std::make_unique<GeneralChat>();
         this.shoutChat = std::make_unique<ShoutChat>();
         this.shoutChat.Init();
         this.radioChat = std::make_unique<RadioChat>();
         this.radioChat.Init();
         this.adminChat = std::make_unique<AdminChat>();
      } else {
         this.serverConnection = GameClient.connection;
         LuaEventManager.triggerEvent("OnChatWindowInit");
      }
   }

    void processInitPlayerChatPacket(ByteBuffer var1) {
      this.init(false, IsoPlayer.getInstance());
    short var2 = var1.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
    ChatTab var4 = std::make_shared<ChatTab>(var1.getShort(), GameWindow.ReadString(var1));
         this.tabs.put(var4.getID(), var4);
      }

      this.addTab((short)0);
      this.focusOnTab(this.tabs.get((short)0).getID());
      LuaEventManager.triggerEvent("OnSetDefaultTab", this.tabs.get((short)0).getTitle());
   }

    void setFullyConnected() {
      this.chatManagerStage = Stage.working;
   }

    void processAddTabPacket(ByteBuffer var1) {
      this.addTab(var1.getShort());
   }

    void processRemoveTabPacket(ByteBuffer var1) {
      this.removeTab(var1.getShort());
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void processJoinChatPacket(ByteBuffer var1) {
    ChatType var2 = ChatType.valueOf(var1.getInt());
    ChatTab var3 = this.tabs.get(var1.getShort());
    void* var4 = nullptr;
      switch (1.$SwitchMap$zombie$network$chat$ChatType[var2.ordinal()]) {
         case 1:
            this.generalChat = std::make_shared<GeneralChat>(var1, var3, this.player);
            var4 = this.generalChat;
            break;
         case 2:
            this.sayChat = std::make_shared<SayChat>(var1, var3, this.player);
            this.sayChat.Init();
            var4 = this.sayChat;
            break;
         case 3:
            this.shoutChat = std::make_shared<ShoutChat>(var1, var3, this.player);
            this.shoutChat.Init();
            var4 = this.shoutChat;
            break;
         case 4:
    WhisperChat var5 = std::make_shared<WhisperChat>(var1, var3, this.player);
            var5.init();
            this.whisperChats.put(var5.getCompanionName(), var5);
            var4 = var5;
            break;
         case 5:
            this.factionChat = std::make_shared<FactionChat>(var1, var3, this.player);
            var4 = this.factionChat;
            break;
         case 6:
            this.safehouseChat = std::make_shared<SafehouseChat>(var1, var3, this.player);
            var4 = this.safehouseChat;
            break;
         case 7:
            this.radioChat = std::make_shared<RadioChat>(var1, var3, this.player);
            this.radioChat.Init();
            var4 = this.radioChat;
            break;
         case 8:
            this.adminChat = std::make_shared<AdminChat>(var1, var3, this.player);
            var4 = this.adminChat;
            break;
         case 9:
            this.serverChat = std::make_shared<ServerChat>(var1, var3, this.player);
            var4 = this.serverChat;
            break;
         default:
            DebugLog.log("Chat of type '" + var2 + "' is not supported to join to");
            return;
      }

      this.mpChats.put(var4.getID(), (ChatBase)var4);
      var4.setFontSize(Core.getInstance().getOptionChatFontSize());
      var4.setShowTimestamp(Core.getInstance().isOptionShowChatTimestamp());
      var4.setShowTitle(Core.getInstance().isOptionShowChatTitle());
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void processLeaveChatPacket(ByteBuffer var1) {
    int var2 = var1.getInt();
    ChatType var3 = ChatType.valueOf(var1.getInt());
      switch (1.$SwitchMap$zombie$network$chat$ChatType[var3.ordinal()]) {
         case 1:
         case 2:
         case 3:
         case 7:
         case 9:
            DebugLog.log("Chat type is '" + var3 + "'. Can't leave it. Ignored.");
            break;
         case 4:
            this.whisperChats.remove(((WhisperChat)this.mpChats.get(var2)).getCompanionName());
            this.mpChats.remove(var2);
            break;
         case 5:
            this.mpChats.remove(var2);
            this.factionChat = nullptr;
            DebugLog.log("You leaved faction chat");
            break;
         case 6:
            this.mpChats.remove(var2);
            this.safehouseChat = nullptr;
            DebugLog.log("You leaved safehouse chat");
            break;
         case 8:
            this.mpChats.remove(var2);
            this.removeTab(this.adminChat.getTabID());
            this.adminChat = nullptr;
            DebugLog.log("You leaved admin chat");
            break;
         default:
            DebugLog.log("Chat of type '" + var3 + "' is not supported to leave to");
      }
   }

    void processPlayerNotFound(const std::string& var1) {
      logger.write("Got player not found packet", "info");
    WhisperChatCreation var2 = this.whisperChatCreation.get(var1);
      if (var2 != nullptr) {
         var2.status = ChatStatus.PlayerNotFound;
      }
   }

    ChatMessage unpackMessage(ByteBuffer var1) {
    int var2 = var1.getInt();
    ChatBase var3 = this.mpChats.get(var2);
      return var3.unpackMessage(var1);
   }

    void processChatMessagePacket(ByteBuffer var1) {
    ChatMessage var2 = this.unpackMessage(var1);
    ChatBase var3 = var2.getChat();
      if (ChatUtility.chatStreamEnabled(var3.getType())) {
         var3.showMessage(var2);
         logger.write("Got message from server: " + var2, "info");
      } else {
         DebugLog.log("Can't process message '" + var2.getText() + "' because '" + var3.getType() + "' chat is disabled");
         logger.write("Can't process message '" + var2.getText() + "' because '" + var3.getType() + "' chat is disabled", "warning");
      }
   }

    void updateChatSettings(const std::string& var1, bool var2, bool var3) {
      Core.getInstance().setOptionChatFontSize(var1);
      Core.getInstance().setOptionShowChatTimestamp(var2);
      Core.getInstance().setOptionShowChatTitle(var3);

      for (ChatBase var5 : this.mpChats.values()) {
         var5.setFontSize(var1);
         var5.setShowTimestamp(var2);
         var5.setShowTitle(var3);
      }
   }

    void showInfoMessage(const std::string& var1) {
    ChatMessage var2 = this.sayChat.createInfoMessage(var1);
      this.sayChat.showMessage(var2);
   }

    void showInfoMessage(const std::string& var1, const std::string& var2) {
      if (this.sayChat != nullptr) {
    ChatMessage var3 = this.sayChat.createInfoMessage(var2);
         var3.setAuthor(var1);
         this.sayChat.showMessage(var3);
      }
   }

    void sendMessageToChat(const std::string& var1, ChatType var2, const std::string& var3) {
      var3 = var3.trim();
      if (!var3.empty()) {
    ChatBase var4 = this.getChat(var2);
         if (var4 == nullptr) {
            if (Core.bDebug) {
               throw IllegalArgumentException("Chat '" + var2 + "' is nullptr. Chat should be init before use!");
            } else {
               this.showChatDisabledMessage(var2);
            }
         } else {
    ChatMessage var5 = var4.createMessage(var3);
            var5.setAuthor(var1);
            this.sendMessageToChat(var4, var5);
         }
      }
   }

    void sendMessageToChat(ChatType var1, const std::string& var2) {
      this.sendMessageToChat(this.player.getUsername(), var1, var2);
   }

   public /* synchronized - TODO: add std::mutex */ void sendWhisperMessage(std::string var1, std::string var2) {
      logger.write("Send message '" + var2 + "' for player '" + var1 + "' in whisper chat", "info");
      if (ChatUtility.chatStreamEnabled(ChatType.whisper)) {
         if (var1 == nullptr || var1.equalsIgnoreCase(this.myNickname)) {
            logger.write("Message can't be send to yourself");
            this.showServerChatMessage(Translator.getText("UI_chat_whisper_message_to_yourself_error"));
            return;
         }

         if (this.whisperChats.containsKey(var1)) {
    WhisperChat var5 = this.whisperChats.get(var1);
            this.sendMessageToChat(var5, var5.createMessage(var2));
            return;
         }

         if (this.whisperChatCreation.containsKey(var1)) {
    WhisperChatCreation var4 = this.whisperChatCreation.get(var1);
            var4.messages.push_back(var2);
            return;
         }

    WhisperChatCreation var3 = this.createWhisperChat(var1);
         var3.messages.push_back(var2);
      } else {
         logger.write("Whisper chat is disabled", "info");
         this.showChatDisabledMessage(ChatType.whisper);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool isPlayerCanUseChat(ChatType var1) {
      if (!ChatUtility.chatStreamEnabled(var1)) {
    return false;
      } else {
         switch (1.$SwitchMap$zombie$network$chat$ChatType[var1.ordinal()]) {
            case 5:
               return Faction.isAlreadyInFaction(this.player);
            case 6:
               return SafeHouse.hasSafehouse(this.player) != nullptr;
            case 7:
               return this.isPlayerCanUseRadioChat();
            case 8:
               return this.player.isAccessLevel("admin");
            default:
    return true;
         }
      }
   }

    void focusOnTab(short var1) {
      for (ChatTab var3 : this.tabs.values()) {
         if (var3.getID() == var1) {
            this.focusTab = var3;
            return;
         }
      }

      throw RuntimeException("Tab with id = '" + var1 + "' not found");
   }

    std::string getTabName(short var1) {
      return this.tabs.containsKey(var1) ? this.tabs.get(var1).getTitle() : int16_t.toString(var1);
   }

    ChatTab getFocusTab() {
      return this.focusTab;
   }

    void showRadioMessage(ChatMessage var1) {
      this.radioChat.showMessage(var1);
   }

    void showRadioMessage(const std::string& var1, int var2) {
    ChatMessage var3 = this.radioChat.createMessage(var1);
      if (var2 != 0) {
         var3.setRadioChannel(var2);
      }

      this.radioChat.showMessage(var3);
   }

    void showStaticRadioSound(const std::string& var1) {
      this.radioChat.showMessage(this.radioChat.createStaticSoundMessage(var1));
   }

    ChatMessage createRadiostationMessage(const std::string& var1, int var2) {
      return this.radioChat.createBroadcastingMessage(var1, var2);
   }

    void showServerChatMessage(const std::string& var1) {
    ServerChatMessage var2 = this.serverChat.createServerMessage(var1);
      this.serverChat.showMessage(var2);
   }

    void addMessage(int var1, const std::string& var2, const std::string& var3) {
    ChatBase var4 = this.mpChats.get(var1);
      var4.showMessage(var3, var2);
   }

    void addMessage(const std::string& var1, const std::string& var2) {
      if (this.generalChat == nullptr) {
         throw std::make_unique<RuntimeException>();
      } else {
         this.addMessage(this.generalChat.getID(), var1, var2);
      }
   }

    void sendMessageToChat(ChatBase var1, ChatMessage var2) {
      if (var1.getType() == ChatType.radio) {
         if (Core.bDebug) {
            throw IllegalArgumentException("You can't send message to radio directly. Use radio and send say message");
         } else {
            DebugLog.log("You try to use radio chat directly. It's restricted. Try to use say chat");
         }
      } else {
         var1.showMessage(var2);
         if (var1.isEnabled()) {
            if (!this.isSinglePlayerMode() && !var2.isLocal()) {
    DeviceData var3 = this.getTransmittingRadio();
               var1.sendToServer(var2, var3);
               if (var3 != nullptr && var1.isSendingToRadio()) {
    ChatMessage var4 = this.radioChat.createMessage(var2.getText());
                  var4.setRadioChannel(var3.getChannel());
                  this.radioChat.sendToServer(var4, var3);
               }
            }
         } else {
            this.showChatDisabledMessage(var1.getType());
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    ChatBase getChat(ChatType var1) {
      if (var1 == ChatType.whisper) {
         throw IllegalArgumentException("Whisper not unique chat");
      } else {
         switch (1.$SwitchMap$zombie$network$chat$ChatType[var1.ordinal()]) {
            case 1:
               return this.generalChat;
            case 2:
               return this.sayChat;
            case 3:
               return this.shoutChat;
            case 4:
            default:
               throw IllegalArgumentException("Chat type is undefined");
            case 5:
               return this.factionChat;
            case 6:
               return this.safehouseChat;
            case 7:
               return this.radioChat;
            case 8:
               return this.adminChat;
            case 9:
               return this.serverChat;
         }
      }
   }

    void addTab(short var1) {
    ChatTab var2 = this.tabs.get(var1);
      if (!var2.isEnabled()) {
         var2.setEnabled(true);
         LuaEventManager.triggerEvent("OnTabAdded", var2.getTitle(), var2.getID());
      }
   }

    void removeTab(short var1) {
    ChatTab var2 = this.tabs.get(var1);
      if (var2.isEnabled()) {
         LuaEventManager.triggerEvent("OnTabRemoved", var2.getTitle(), var2.getID());
         var2.setEnabled(false);
      }
   }

    WhisperChatCreation createWhisperChat(const std::string& var1) {
      logger.write("Whisper chat is not created for '" + var1 + "'", "info");
    WhisperChatCreation var2 = std::make_shared<WhisperChatCreation>();
      var2.destPlayerName = var1;
      var2.status = ChatStatus.Creating;
      var2.createTime = System.currentTimeMillis();
      this.whisperChatCreation.put(var1, var2);
    ByteBufferWriter var3 = this.serverConnection.startPacket();
      PacketType.PlayerStartPMChat.doPacket(var3);
      var3.putUTF(this.myNickname);
      var3.putUTF(var1);
      PacketType.PlayerStartPMChat.send(this.serverConnection);
      logger.write("'Start PM chat' package sent. Waiting for a creating whisper chat by server...", "info");
    return var2;
   }

    static void UpdateClient() {
      if (instance != nullptr) {
         try {
            instance.updateClient();
         } catch (Throwable var1) {
            ExceptionLogger.logException(var1);
         }
      }
   }

    void updateClient() {
      if (this.isWorking()) {
         this.updateWhisperChat();
      }
   }

    void updateWhisperChat() {
      if (!this.whisperChatCreation.empty()) {
    long var1 = System.currentTimeMillis();

         for (WhisperChatCreation var5 : new std::vector<>(this.whisperChatCreation.values())) {
            if (this.whisperChats.containsKey(var5.destPlayerName)) {
    WhisperChat var6 = this.whisperChats.get(var5.destPlayerName);
               logger.write("Whisper chat created between '" + this.myNickname + "' and '" + var5.destPlayerName + "' and has id = " + var6.getID(), "info");
               this.whisperChatCreation.remove(var5.destPlayerName);

               for (std::string var8 : var5.messages) {
                  this.sendMessageToChat(var6, var6.createMessage(var8));
               }
            } else if (var5.status == ChatStatus.PlayerNotFound) {
               logger.write("Player '" + var5.destPlayerName + "' is not found. Chat is not created", "info");
               this.whisperChatCreation.remove(var5.destPlayerName);
               this.showServerChatMessage(Translator.getText("UI_chat_whisper_player_not_found_error", var5.destPlayerName));
            } else if (var5.status == ChatStatus.Creating && var1 - var5.createTime >= 10000L) {
               logger.write("Whisper chat is not created by timeout. See server chat logs", "error");
               this.whisperChatCreation.remove(var5.destPlayerName);
            }
         }
      }
   }

    void showChatDisabledMessage(ChatType var1) {
    std::stringstream var2 = new std::stringstream();
      var2.append(Translator.getText("UI_chat_chat_disabled_msg", Translator.getText(var1.getTitleID())));

      for (ChatType var5 : ChatUtility.getAllowedChatStreams()) {
         if (this.isPlayerCanUseChat(var5)) {
            var2.append("    * ").append(Translator.getText(var5.getTitleID())).append(" <LINE> ");
         }
      }

      this.showServerChatMessage(var2);
   }

    bool isPlayerCanUseRadioChat() {
    Radio var1 = this.player.getEquipedRadio();
      if (var1 != nullptr && var1.getDeviceData() != nullptr) {
    bool var2 = var1.getDeviceData().getIsTurnedOn();
         var2 &= var1.getDeviceData().getIsTwoWay();
         var2 &= var1.getDeviceData().getIsPortable();
         return var2 & !var1.getDeviceData().getMicIsMuted();
      } else {
    return false;
      }
   }

    DeviceData getTransmittingRadio() {
      if (this.player.getOnlineID() == -1) {
    return nullptr;
      } else {
    VoiceManagerData var1 = VoiceManagerData.get(this.player.getOnlineID());
         /* synchronized - TODO: add std::mutex */ (var1.radioData) {
            return var1.radioData.stream().filter(RadioData::isTransmissionAvailable).findFirst().<DeviceData>map(RadioData::getDeviceData).orElse(nullptr);
         }
      }
   }
}
} // namespace chat
} // namespace zombie
