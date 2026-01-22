#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/radio/devices/DeviceData.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace chat {


class ChatBase {
public:
    static const int ID_NOT_SET = -29048394;
    int id;
    const std::string titleID;
    const ChatType type;
    ChatSettings settings;
    bool customSettings = false;
    ChatTab chatTab = nullptr;
    std::string translatedTitle;
   protected const std::vector<int16_t> members;
   private const std::vector<int16_t> justAddedMembers = std::make_unique<std::vector<>>();
   private const std::vector<int16_t> justRemovedMembers = std::make_unique<std::vector<>>();
   protected const std::vector<ChatMessage> messages;
    UdpConnection serverConnection;
    ChatMode mode;
    IsoPlayer chatOwner;
    const Lock memberLock = std::make_shared<ReentrantLock>();

    protected ChatBase(ChatType var1) {
      this.settings = std::make_unique<ChatSettings>();
      this.customSettings = false;
      this.messages = std::make_unique<std::vector<>>();
      this.id = -29048394;
      this.titleID = var1.getTitleID();
      this.type = var1;
      this.members = std::make_unique<std::vector<>>();
      this.mode = ChatMode.SinglePlayer;
      this.serverConnection = nullptr;
      this.chatOwner = IsoPlayer.getInstance();
   }

    public ChatBase(ByteBuffer var1, ChatType var2, ChatTab var3, IsoPlayer var4) {
      this(var2);
      this.id = var1.getInt();
      this.customSettings = var1.get() == 1;
      if (this.customSettings) {
         this.settings = std::make_shared<ChatSettings>(var1);
      }

      this.chatTab = var3;
      this.mode = ChatMode.ClientMultiPlayer;
      this.serverConnection = GameClient.connection;
      this.chatOwner = var4;
   }

    public ChatBase(int var1, ChatType var2, ChatTab var3) {
      this(var2);
      this.id = var1;
      this.chatTab = var3;
      this.mode = ChatMode.ServerMultiPlayer;
   }

    bool isEnabled() {
      return ChatUtility.chatStreamEnabled(this.type);
   }

    std::string getChatOwnerName() {
      if (this.chatOwner == nullptr) {
         if (this.mode != ChatMode.ServerMultiPlayer) {
            if (Core.bDebug) {
               throw NullPointerException("chat owner is nullptr but name quired");
            }

            DebugLog.log("chat owner is nullptr but name quired. Chat: " + this.getType());
         }

         return "";
      } else {
         return this.chatOwner.username;
      }
   }

    IsoPlayer getChatOwner() {
      if (this.chatOwner != nullptr || this.mode == ChatMode.ServerMultiPlayer) {
         return this.chatOwner;
      } else if (Core.bDebug) {
         throw NullPointerException("chat owner is nullptr");
      } else {
         DebugLog.log("chat owner is nullptr. Chat: " + this.getType());
    return nullptr;
      }
   }

    ChatMode getMode() {
      return this.mode;
   }

    ChatType getType() {
      return this.type;
   }

    int getID() {
      return this.id;
   }

    std::string getTitleID() {
      return this.titleID;
   }

    Color getColor() {
      return this.settings.getFontColor();
   }

    short getTabID() {
      return this.chatTab.getID();
   }

    float getRange() {
      return this.settings.getRange();
   }

    bool isSendingToRadio() {
    return false;
   }

    float getZombieAttractionRange() {
      return this.settings.getZombieAttractionRange();
   }

    void setSettings(ChatSettings var1) {
      this.settings = var1;
      this.customSettings = true;
   }

    void setFontSize(const std::string& var1) {
      this.settings.setFontSize(var1.toLowerCase());
   }

    void setShowTimestamp(bool var1) {
      this.settings.setShowTimestamp(var1);
   }

    void setShowTitle(bool var1) {
      this.settings.setShowChatTitle(var1);
   }

    bool isCustomSettings() {
      return this.customSettings;
   }

    bool isAllowImages() {
      return this.settings.isAllowImages();
   }

    bool isAllowChatIcons() {
      return this.settings.isAllowChatIcons();
   }

    bool isAllowColors() {
      return this.settings.isAllowColors();
   }

    bool isAllowFonts() {
      return this.settings.isAllowFonts();
   }

    bool isAllowBBcode() {
      return this.settings.isAllowBBcode();
   }

    bool isEqualizeLineHeights() {
      return this.settings.isEqualizeLineHeights();
   }

    bool isShowAuthor() {
      return this.settings.isShowAuthor();
   }

    bool isShowTimestamp() {
      return this.settings.isShowTimestamp();
   }

    bool isShowTitle() {
      return this.settings.isShowChatTitle();
   }

    std::string getFontSize() {
      return this.settings.getFontSize();
   }

    std::string getTitle() {
      if (this.translatedTitle == nullptr) {
         this.translatedTitle = Translator.getText(this.titleID);
      }

      return this.translatedTitle;
   }

    void close() {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         for (int16_t var4 : new std::vector<>(this.members)) {
            this.leaveMember(var4);
         }

         this.members.clear();
      }
   }

    void packChat(ByteBufferWriter var1) {
      var1.putInt(this.type.getValue());
      var1.putShort(this.getTabID());
      var1.putInt(this.id);
      var1.putBoolean(this.customSettings);
      if (this.customSettings) {
         this.settings.pack(var1);
      }
   }

    ChatMessage unpackMessage(ByteBuffer var1) {
    std::string var2 = GameWindow.ReadString(var1);
    std::string var3 = GameWindow.ReadString(var1);
    ChatMessage var4 = this.createMessage(var3);
      var4.setAuthor(var2);
    return var4;
   }

    void packMessage(ByteBufferWriter var1, ChatMessage var2) {
      var1.putInt(this.id);
      var1.putUTF(var2.getAuthor());
      var1.putUTF(var2.getText());
   }

    ChatMessage createMessage(const std::string& var1) {
      return this.createMessage(this.getChatOwnerName(), var1);
   }

    ChatMessage createMessage(const std::string& var1, const std::string& var2) {
    ChatMessage var3 = std::make_shared<ChatMessage>(this, var2);
      var3.setAuthor(var1);
      var3.setServerAuthor(false);
    return var3;
   }

    ServerChatMessage createServerMessage(const std::string& var1) {
    ServerChatMessage var2 = std::make_shared<ServerChatMessage>(this, var1);
      var2.setServerAuthor(true);
    return var2;
   }

    void showMessage(const std::string& var1, const std::string& var2) {
    ChatMessage var3 = std::make_shared<ChatMessage>(this, LocalDateTime.now(), var1);
      var3.setAuthor(var2);
      this.showMessage(var3);
   }

    void showMessage(ChatMessage var1) {
      this.messages.push_back(var1);
      if (this.isEnabled() && var1.isShowInChat() && this.chatTab != nullptr) {
         LuaEventManager.triggerEvent("OnAddMessage", var1, this.getTabID());
      }
   }

    std::string getMessageTextWithPrefix(ChatMessage var1) {
      return this.getMessagePrefix(var1) + " " + var1.getTextWithReplacedParentheses();
   }

    void sendMessageToChatMembers(ChatMessage var1) {
    IsoPlayer var2 = ChatUtility.findPlayer(var1.getAuthor());
      if (var2 == nullptr) {
         DebugLog.log("Author '" + var1.getAuthor() + "' not found");
      } else {
         /* synchronized - TODO: add std::mutex */ (this.memberLock) {
            for (short var5 : this.members) {
    IsoPlayer var6 = ChatUtility.findPlayer(var5);
               if (var6 != nullptr && var2.getOnlineID() != var5) {
                  this.sendMessageToPlayer(var5, var1);
               }
            }
         }

         if (Core.bDebug) {
            DebugLog.log("New message '" + var1 + "' was sent members of chat '" + this.getID() + "'");
         }
      }
   }

    void sendMessageToChatMembers(ServerChatMessage var1) {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         for (short var4 : this.members) {
    IsoPlayer var5 = ChatUtility.findPlayer(var4);
            if (var5 != nullptr) {
               this.sendMessageToPlayer(var4, var1);
            }
         }
      }

      if (Core.bDebug) {
         DebugLog.log("New message '" + var1 + "' was sent members of chat '" + this.getID() + "'");
      }
   }

    void sendMessageToPlayer(UdpConnection var1, ChatMessage var2) {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
    bool var4 = false;
         short[] var5 = var1.playerIDs;
    int var6 = var5.length;

         for (int var7 = 0; var7 < var6; var7++) {
    short var8 = var5[var7];
            if (var4) {
               break;
            }

            var4 = this.members.contains(var8);
         }

         if (!var4) {
            throw RuntimeException("Passed connection didn't contained member of chat");
         } else {
            this.sendChatMessageToPlayer(var1, var2);
         }
      }
   }

    void sendMessageToPlayer(short var1, ChatMessage var2) {
    UdpConnection var3 = ChatUtility.findConnection(var1);
      if (var3 != nullptr) {
         this.sendChatMessageToPlayer(var3, var2);
         DebugLog.log("Message '" + var2 + "' was sent to player with id '" + var1 + "' of chat '" + this.getID() + "'");
      }
   }

    std::string getMessagePrefix(ChatMessage var1) {
    std::stringstream var2 = new std::stringstream(this.getChatSettingsTags());
      if (this.isShowTimestamp()) {
         var2.append("[").append(LuaManager.getHourMinuteJava()).append("]");
      }

      if (this.isShowTitle()) {
         var2.append("[").append(this.getTitle()).append("]");
      }

      if (this.isShowAuthor()) {
         var2.append("[").append(var1.getAuthor()).append("]");
      }

      var2.append(": ");
      return var2;
   }

    std::string getColorTag() {
    Color var1 = this.getColor();
      return this.getColorTag(var1);
   }

    std::string getColorTag(Color var1) {
      return "<RGB:" + var1.r + "," + var1.g + "," + var1.b + ">";
   }

    std::string getFontSizeTag() {
      return "<SIZE:" + this.settings.getFontSize() + ">";
   }

    std::string getChatSettingsTags() {
      return this.getColorTag() + " " + this.getFontSizeTag() + " ";
   }

    void addMember(short var1) {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         if (!this.hasMember(var1)) {
            this.members.push_back(var1);
            this.justAddedMembers.push_back(var1);
    UdpConnection var3 = ChatUtility.findConnection(var1);
            if (var3 != nullptr) {
               this.sendPlayerJoinChatPacket(var3);
               this.chatTab.sendAddTabPacket(var3);
            } else if (Core.bDebug) {
               throw RuntimeException("Connection should exist!");
            }
         }
      }
   }

    void leaveMember(short var1) {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         if (this.hasMember(var1)) {
            this.justRemovedMembers.push_back(var1);
    UdpConnection var3 = ChatUtility.findConnection(var1);
            if (var3 != nullptr) {
               this.sendPlayerLeaveChatPacket(var3);
            }

            this.members.remove(var1);
         }
      }
   }

    bool hasMember(short var1) {
      return this.members.contains(var1);
   }

    void removeMember(short var1) {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         if (this.hasMember(var1)) {
            this.members.remove(var1);
         }
      }
   }

    void syncMembersByUsernames(std::vector<std::string> var1) {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         this.justAddedMembers.clear();
         this.justRemovedMembers.clear();
    std::vector var3 = new std::vector(var1.size());
    void* var4 = nullptr;

    for (auto& var6 : var1)            var4 = ChatUtility.findPlayer(var6);
            if (var4 != nullptr) {
               var3.push_back(var4.getOnlineID());
            }
         }

         this.syncMembers(var3);
      }
   }

   public std::vector<int16_t> getJustAddedMembers() {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         return this.justAddedMembers;
      }
   }

   public std::vector<int16_t> getJustRemovedMembers() {
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         return this.justRemovedMembers;
      }
   }

    void syncMembers(std::vector<int16_t> var1) {
    for (auto& var3 : var1)         this.addMember(var3);
      }

    std::vector var8 = new std::vector();
      /* synchronized - TODO: add std::mutex */ (this.memberLock) {
         for (int16_t var5 : this.members) {
            if (!var1.contains(var5)) {
               var8.push_back(var5);
            }
         }

    for (auto& var11 : var8)            this.leaveMember(var11);
         }
      }
   }

    void sendPlayerJoinChatPacket(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.PlayerJoinChat.doPacket(var2);
      this.packChat(var2);
      PacketType.PlayerJoinChat.send(var1);
   }

    void sendPlayerLeaveChatPacket(short var1) {
    UdpConnection var2 = ChatUtility.findConnection(var1);
      this.sendPlayerLeaveChatPacket(var2);
   }

    void sendPlayerLeaveChatPacket(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.PlayerLeaveChat.doPacket(var2);
      var2.putInt(this.getID());
      var2.putInt(this.getType().getValue());
      PacketType.PlayerLeaveChat.send(var1);
   }

    void sendToServer(ChatMessage var1, DeviceData var2) {
      if (this.serverConnection == nullptr) {
         DebugLog.log("Connection to server is nullptr in client chat");
      }

      this.sendChatMessageFromPlayer(this.serverConnection, var1);
   }

    void sendChatMessageToPlayer(UdpConnection var1, ChatMessage var2) {
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.ChatMessageToPlayer.doPacket(var3);
      this.packMessage(var3, var2);
      PacketType.ChatMessageToPlayer.send(var1);
   }

    void sendChatMessageFromPlayer(UdpConnection var1, ChatMessage var2) {
    ByteBufferWriter var3 = var1.startPacket();
      PacketType.ChatMessageFromPlayer.doPacket(var3);
      this.packMessage(var3, var2);
      PacketType.ChatMessageFromPlayer.send(var1);
   }

    bool hasChatTab() {
      return this.chatTab != nullptr;
   }
}
} // namespace chat
} // namespace zombie
