#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/chat/ChatUtility.h"
#include "zombie/chat/ServerChatMessage.h"
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
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerOptions.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
namespace chat {


class ChatServer {
public:
    static ChatServer instance = nullptr;
   private static const std::stack<int> availableChatsID = std::make_unique<std::stack<>>();
    static int lastChatId = -1;
   private static const std::unordered_map<ChatType, ChatBase> defaultChats = std::make_unique<std::unordered_map<>>();
   private static const ConcurrentHashMap<int, ChatBase> chats = std::make_unique<ConcurrentHashMap<>>();
   private static const ConcurrentHashMap<std::string, FactionChat> factionChats = std::make_unique<ConcurrentHashMap<>>();
   private static const ConcurrentHashMap<std::string, SafehouseChat> safehouseChats = std::make_unique<ConcurrentHashMap<>>();
    static AdminChat adminChat = nullptr;
    static GeneralChat generalChat = nullptr;
    static ServerChat serverChat = nullptr;
    static RadioChat radioChat = nullptr;
    static bool inited = false;
   private static const std::unordered_set<int16_t> players = std::make_unique<std::unordered_set<>>();
    static const std::string logName = "chat";
    static ZLogger logger;
   private static const std::unordered_map<std::string, ChatTab> tabs = std::make_unique<std::unordered_map<>>();
    static const std::string mainTabID = "main";
    static const std::string adminTabID = "admin";

    static ChatServer getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<ChatServer>();
      }

    return instance;
   }

    static bool isInited() {
    return inited;
   }

    private ChatServer() {
   }

    void init() {
      if (!inited) {
         LoggerManager.createLogger("chat", Core.bDebug);
         logger = LoggerManager.getLogger("chat");
         logger.write("Start chat server initialization...", "info");
    ChatTab var1 = std::make_shared<ChatTab>((short)0, "UI_chat_main_tab_title_id");
    ChatTab var2 = std::make_shared<ChatTab>((short)1, "UI_chat_admin_tab_title_id");
    bool var3 = ServerOptions.getInstance().DiscordEnable.getValue();
    GeneralChat var4 = std::make_shared<GeneralChat>(this.getNextChatID(), var1, var3);
    SayChat var5 = std::make_shared<SayChat>(this.getNextChatID(), var1);
    ShoutChat var6 = std::make_shared<ShoutChat>(this.getNextChatID(), var1);
    RadioChat var7 = std::make_shared<RadioChat>(this.getNextChatID(), var1);
    AdminChat var8 = std::make_shared<AdminChat>(this.getNextChatID(), var2);
    ServerChat var9 = std::make_shared<ServerChat>(this.getNextChatID(), var1);
         chats.put(var4.getID(), var4);
         chats.put(var5.getID(), var5);
         chats.put(var6.getID(), var6);
         chats.put(var7.getID(), var7);
         chats.put(var8.getID(), var8);
         chats.put(var9.getID(), var9);
         defaultChats.put(var4.getType(), var4);
         defaultChats.put(var5.getType(), var5);
         defaultChats.put(var6.getType(), var6);
         defaultChats.put(var9.getType(), var9);
         defaultChats.put(var7.getType(), var7);
         tabs.put("main", var1);
         tabs.put("admin", var2);
         generalChat = var4;
         adminChat = var8;
         serverChat = var9;
         radioChat = var7;
         inited = true;
         logger.write("General chat has id = " + var4.getID(), "info");
         logger.write("Say chat has id = " + var5.getID(), "info");
         logger.write("Shout chat has id = " + var6.getID(), "info");
         logger.write("Radio chat has id = " + var7.getID(), "info");
         logger.write("Admin chat has id = " + var8.getID(), "info");
         logger.write("Server chat has id = " + serverChat.getID(), "info");
         logger.write("Chat server successfully initialized", "info");
      }
   }

    void initPlayer(short var1) {
      logger.write("Player with id = '" + var1 + "' tries to connect", "info");
      /* synchronized - TODO: add std::mutex */ (players) {
         if (players.contains(var1)) {
            logger.write("Player already connected!", "warning");
            return;
         }
      }

      logger.write("Adding player '" + var1 + "' to chat server", "info");
    IsoPlayer var11 = ChatUtility.findPlayer(var1);
    UdpConnection var3 = ChatUtility.findConnection(var1);
      if (var3 != nullptr && var11 != nullptr) {
         this.sendInitPlayerChatPacket(var3);
         this.addDefaultChats(var1);
         logger.write("Player joined to default chats", "info");
         if (var3.accessLevel == 32) {
            this.joinAdminChat(var1);
         }

    Faction var4 = Faction.getPlayerFaction(var11);
         if (var4 != nullptr) {
            this.addMemberToFactionChat(var4.getName(), var1);
         }

    SafeHouse var5 = SafeHouse.hasSafehouse(var11);
         if (var5 != nullptr) {
            this.addMemberToSafehouseChat(var5.getId(), var1);
         }

    ByteBufferWriter var6 = var3.startPacket();
         PacketType.PlayerConnectedToChat.doPacket(var6);
         PacketType.PlayerConnectedToChat.send(var3);
         /* synchronized - TODO: add std::mutex */ (players) {
            players.push_back(var1);
         }

         logger.write("Player " + var11.getUsername() + "(" + var1 + ") joined to chat server successfully", "info");
      } else {
         logger.write("Player or connection is not found on server!", "error");
         logger.write((var3 == nullptr ? "connection = nullptr " : "") + (var11 == nullptr ? "player = nullptr" : ""), "error");
      }
   }

    void processMessageFromPlayerPacket(ByteBuffer var1) {
    int var2 = var1.getInt();
      /* synchronized - TODO: add std::mutex */ (chats) {
    ChatBase var4 = chats.get(var2);
    ChatMessage var5 = var4.unpackMessage(var1);
         logger.write("Got message:" + var5, "info");
         if (!ChatUtility.chatStreamEnabled(var4.getType())) {
            logger.write("Message ignored by server because the chat disabled by server settings", "warning");
         } else {
            this.sendMessage(var5);
            logger.write("Message " + var5 + " sent to chat (id = " + var4.getID() + ") members", "info");
         }
      }
   }

    void processPlayerStartWhisperChatPacket(ByteBuffer var1) {
      logger.write("Whisper chat starting...", "info");
      if (!ChatUtility.chatStreamEnabled(ChatType.whisper)) {
         logger.write("Message for whisper chat is ignored because whisper chat is disabled by server settings", "info");
      } else {
    std::string var2 = GameWindow.ReadString(var1);
    std::string var3 = GameWindow.ReadString(var1);
         logger.write("Player '" + var2 + "' attempt to start whispering with '" + var3 + "'", "info");
    IsoPlayer var4 = ChatUtility.findPlayer(var2);
    IsoPlayer var5 = ChatUtility.findPlayer(var3);
         if (var4 == nullptr) {
            logger.write("Player '" + var2 + "' is not found!", "error");
            throw RuntimeException("Player not found");
         } else if (var5 == nullptr) {
            logger.write("Player '" + var2 + "' attempt to start whisper dialog with '" + var3 + "' but this player not found!", "info");
    UdpConnection var7 = ChatUtility.findConnection(var4.getOnlineID());
            this.sendPlayerNotFoundMessage(var7, var3);
         } else {
            logger.write("Both players found", "info");
    WhisperChat var6 = std::make_shared<WhisperChat>(this.getNextChatID(), tabs.get("main"), var2, var3);
            var6.addMember(var4.getOnlineID());
            var6.addMember(var5.getOnlineID());
            chats.put(var6.getID(), var6);
            logger.write("Whisper chat (id = " + var6.getID() + ") between '" + var4.getUsername() + "' and '" + var5.getUsername() + "' started", "info");
         }
      }
   }

    void sendPlayerNotFoundMessage(UdpConnection var1, const std::string& var2) {
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.PlayerNotFound.doPacket(var3);
      var3.putUTF(var2);
      PacketType.PlayerNotFound.send(var1);
      logger.write("'Player not found' packet was sent", "info");
   }

    ChatMessage unpackChatMessage(ByteBuffer var1) {
    int var2 = var1.getInt();
      return chats.get(var2).unpackMessage(var1);
   }

    void disconnectPlayer(short var1) {
      logger.write("Player " + var1 + " disconnecting...", "info");
      /* synchronized - TODO: add std::mutex */ (chats) {
         for (ChatBase var4 : chats.values()) {
            var4.removeMember(var1);
            if (var4.getType() == ChatType.whisper) {
               this.closeChat(var4.getID());
            }
         }
      }

      /* synchronized - TODO: add std::mutex */ (players) {
         players.remove(var1);
      }

      logger.write("Disconnecting player " + var1 + " finished", "info");
   }

    void closeChat(int var1) {
      /* synchronized - TODO: add std::mutex */ (chats) {
         if (!chats.containsKey(var1)) {
            throw RuntimeException("Chat '" + var1 + "' requested to close but it's not exists.");
         }

    ChatBase var3 = chats.get(var1);
         var3.close();
         chats.remove(var1);
      }

      /* synchronized - TODO: add std::mutex */ (availableChatsID) {
         availableChatsID.push(var1);
      }
   }

    void joinAdminChat(short var1) {
      if (adminChat == nullptr) {
         logger.write("Admin chat is nullptr! Can't add player to it", "warning");
      } else {
         adminChat.addMember(var1);
         logger.write("Player joined admin chat", "info");
      }
   }

    void leaveAdminChat(short var1) {
      logger.write("Player " + var1 + " are leaving admin chat...", "info");
    UdpConnection var2 = ChatUtility.findConnection(var1);
      if (adminChat == nullptr) {
         logger.write("Admin chat is nullptr. Can't leave it! ChatServer", "warning");
      } else if (var2 == nullptr) {
         logger.write("Connection to player is nullptr. Can't leave admin chat! ChatServer.leaveAdminChat", "warning");
      } else {
         adminChat.leaveMember(var1);
         tabs.get("admin").sendRemoveTabPacket(var2);
         logger.write("Player " + var1 + " leaved admin chat", "info");
      }
   }

    FactionChat createFactionChat(const std::string& var1) {
      logger.write("Creating faction chat '" + var1 + "'", "info");
      if (factionChats.containsKey(var1)) {
         logger.write("Faction chat '" + var1 + "' already exists!", "warning");
         return factionChats.get(var1);
      } else {
    FactionChat var2 = std::make_shared<FactionChat>(this.getNextChatID(), tabs.get("main"));
         chats.put(var2.getID(), var2);
         factionChats.put(var1, var2);
         logger.write("Faction chat '" + var1 + "' created", "info");
    return var2;
      }
   }

    SafehouseChat createSafehouseChat(const std::string& var1) {
      logger.write("Creating safehouse chat '" + var1 + "'", "info");
      if (safehouseChats.containsKey(var1)) {
         logger.write("Safehouse chat already has chat with name '" + var1 + "'", "warning");
         return safehouseChats.get(var1);
      } else {
    SafehouseChat var2 = std::make_shared<SafehouseChat>(this.getNextChatID(), tabs.get("main"));
         chats.put(var2.getID(), var2);
         safehouseChats.put(var1, var2);
         logger.write("Safehouse chat '" + var1 + "' created", "info");
    return var2;
      }
   }

    void removeFactionChat(const std::string& var1) {
      logger.write("Removing faction chat '" + var1 + "'...", "info");
    int var2;
      /* synchronized - TODO: add std::mutex */ (factionChats) {
         if (!factionChats.containsKey(var1)) {
    std::string var8 = "Faction chat '" + var1 + "' tried to delete but it's not exists.";
            logger.write(var8, "error");
    std::runtime_error var5 = std::make_shared<RuntimeException>(var8);
            logger.write(var5);
    throw var5;
         }

    FactionChat var4 = factionChats.get(var1);
         var2 = var4.getID();
         factionChats.remove(var1);
      }

      this.closeChat(var2);
      logger.write("Faction chat '" + var1 + "' removed", "info");
   }

    void removeSafehouseChat(const std::string& var1) {
      logger.write("Removing safehouse chat '" + var1 + "'...", "info");
    int var2;
      /* synchronized - TODO: add std::mutex */ (safehouseChats) {
         if (!safehouseChats.containsKey(var1)) {
    std::string var8 = "Safehouse chat '" + var1 + "' tried to delete but it's not exists.";
            logger.write(var8, "error");
    std::runtime_error var5 = std::make_shared<RuntimeException>(var8);
            logger.write(var5);
    throw var5;
         }

    SafehouseChat var4 = safehouseChats.get(var1);
         var2 = var4.getID();
         safehouseChats.remove(var1);
      }

      this.closeChat(var2);
      logger.write("Safehouse chat '" + var1 + "' removed", "info");
   }

    void syncFactionChatMembers(const std::string& var1, const std::string& var2, std::vector<std::string> var3) {
      logger.write("Start syncing faction chat '" + var1 + "'...", "info");
      if (var1 != nullptr && var2 != nullptr && var3 != nullptr) {
         /* synchronized - TODO: add std::mutex */ (factionChats) {
            if (!factionChats.containsKey(var1)) {
               logger.write("Faction chat '" + var1 + "' is not exist", "warning");
               return;
            }

    std::vector var5 = new std::vector(var3);
            var5.push_back(var2);
    FactionChat var6 = factionChats.get(var1);
            var6.syncMembersByUsernames(var5);
    std::stringstream var7 = new std::stringstream("These members were added: ");

            for (short var9 : var6.getJustAddedMembers()) {
               var7.append("'").append(ChatUtility.findPlayerName(var9)).append("', ");
            }

            var7.append(". These members were removed: ");

            for (short var13 : var6.getJustRemovedMembers()) {
               var7.append("'").append(ChatUtility.findPlayerName(var13)).append("', ");
            }

            logger.write(var7, "info");
         }

         logger.write("Syncing faction chat '" + var1 + "' finished", "info");
      } else {
         logger.write("Faction name or faction owner or players is nullptr", "warning");
      }
   }

    void syncSafehouseChatMembers(const std::string& var1, const std::string& var2, std::vector<std::string> var3) {
      logger.write("Start syncing safehouse chat '" + var1 + "'...", "info");
      if (var1 != nullptr && var2 != nullptr && var3 != nullptr) {
         /* synchronized - TODO: add std::mutex */ (safehouseChats) {
            if (!safehouseChats.containsKey(var1)) {
               logger.write("Safehouse chat '" + var1 + "' is not exist", "warning");
               return;
            }

    std::vector var5 = new std::vector(var3);
            var5.push_back(var2);
    SafehouseChat var6 = safehouseChats.get(var1);
            var6.syncMembersByUsernames(var5);
    std::stringstream var7 = new std::stringstream("These members were added: ");

            for (short var9 : var6.getJustAddedMembers()) {
               var7.append("'").append(ChatUtility.findPlayerName(var9)).append("', ");
            }

            var7.append("These members were removed: ");

            for (short var13 : var6.getJustRemovedMembers()) {
               var7.append("'").append(ChatUtility.findPlayerName(var13)).append("', ");
            }

            logger.write(var7, "info");
         }

         logger.write("Syncing safehouse chat '" + var1 + "' finished", "info");
      } else {
         logger.write("Safehouse name or Safehouse owner or players is nullptr", "warning");
      }
   }

    void addMemberToSafehouseChat(const std::string& var1, short var2) {
      if (!safehouseChats.containsKey(var1)) {
         logger.write("Safehouse chat is not initialized!", "warning");
      } else {
         /* synchronized - TODO: add std::mutex */ (safehouseChats) {
    SafehouseChat var4 = safehouseChats.get(var1);
            var4.addMember(var2);
         }

         logger.write("Player joined to chat of safehouse '" + var1 + "'", "info");
      }
   }

    void addMemberToFactionChat(const std::string& var1, short var2) {
      if (!factionChats.containsKey(var1)) {
         logger.write("Faction chat is not initialized!", "warning");
      } else {
         /* synchronized - TODO: add std::mutex */ (factionChats) {
    FactionChat var4 = factionChats.get(var1);
            var4.addMember(var2);
         }

         logger.write("Player joined to chat of faction '" + var1 + "'", "info");
      }
   }

    void sendServerAlertMessageToServerChat(const std::string& var1, const std::string& var2) {
      serverChat.sendMessageToChatMembers(serverChat.createMessage(var1, var2, true));
      logger.write("Server alert message: '" + var2 + "' by '" + var1 + "' sent.");
   }

    void sendServerAlertMessageToServerChat(const std::string& var1) {
      serverChat.sendMessageToChatMembers(serverChat.createServerMessage(var1, true));
      logger.write("Server alert message: '" + var1 + "' sent.");
   }

    ChatMessage createRadiostationMessage(const std::string& var1, int var2) {
      return radioChat.createBroadcastingMessage(var1, var2);
   }

    void sendMessageToServerChat(UdpConnection var1, const std::string& var2) {
    ServerChatMessage var3 = serverChat.createServerMessage(var2, false);
      serverChat.sendMessageToPlayer(var1, var3);
   }

    void sendMessageToServerChat(const std::string& var1) {
    ServerChatMessage var2 = serverChat.createServerMessage(var1, false);
      serverChat.sendMessageToChatMembers(var2);
   }

    void sendMessageFromDiscordToGeneralChat(const std::string& var1, const std::string& var2) {
      if (var1 != nullptr && var2 != nullptr) {
         logger.write("Got message '" + var2 + "' by author '" + var1 + "' from discord");
      }

    ChatMessage var3 = generalChat.createMessage(var2);
      var3.makeFromDiscord();
      var3.setAuthor(var1);
      if (ChatUtility.chatStreamEnabled(ChatType.general)) {
         this.sendMessage(var3);
         logger.write("Message '" + var2 + "' send from discord to general chat members");
      } else {
         generalChat.sendToDiscordGeneralChatDisabled();
         logger.write("General chat disabled so error message sent to discord", "warning");
      }
   }

    int getNextChatID() {
      /* synchronized - TODO: add std::mutex */ (availableChatsID) {
         if (availableChatsID.empty()) {
            lastChatId++;
            availableChatsID.push(lastChatId);
         }

         return availableChatsID.pop();
      }
   }

    void sendMessage(ChatMessage var1) {
      /* synchronized - TODO: add std::mutex */ (chats) {
         if (chats.containsKey(var1.getChatID())) {
    ChatBase var3 = chats.get(var1.getChatID());
            var3.sendMessageToChatMembers(var1);
         }
      }
   }

    void sendInitPlayerChatPacket(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.InitPlayerChat.doPacket(var2);
      var2.putShort((short)tabs.size());

      for (ChatTab var4 : tabs.values()) {
         var2.putShort(var4.getID());
         var2.putUTF(var4.getTitleID());
      }

      PacketType.InitPlayerChat.send(var1);
   }

    void addDefaultChats(short var1) {
      for (Entry var3 : defaultChats.entrySet()) {
    ChatBase var4 = (ChatBase)var3.getValue();
         var4.addMember(var1);
      }
   }

    void sendMessageToAdminChat(const std::string& var1) {
    ServerChatMessage var2 = adminChat.createServerMessage(var1);
      adminChat.sendMessageToChatMembers(var2);
   }
}
} // namespace chat
} // namespace network
} // namespace zombie
