#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class ServerChat : public ChatBase {
public:
    public ServerChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.server, var2, var3);
      this.setSettings(getDefaultSettings());
   }

    public ServerChat(int var1, ChatTab var2) {
      super(var1, ChatType.server, var2);
      this.setSettings(getDefaultSettings());
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(std::make_shared<Color>(0, 128, 255, 255));
      var0.setShowAuthor(false);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(false);
      var0.setAllowColors(true);
      var0.setAllowFonts(false);
      var0.setAllowBBcode(false);
    return var0;
   }

    ChatMessage createMessage(const std::string& var1, const std::string& var2, bool var3) {
    ChatMessage var4 = this.createMessage(var2);
      var4.setAuthor(var1);
      if (var3) {
         var4.setServerAlert(true);
      }

    return var4;
   }

    ServerChatMessage createServerMessage(const std::string& var1, bool var2) {
    ServerChatMessage var3 = this.createServerMessage(var1);
      var3.setServerAlert(var2);
    return var3;
   }

    short getTabID() {
      return !GameClient.bClient ? super.getTabID() : ChatManager.getInstance().getFocusTab().getID();
   }

    ChatMessage unpackMessage(ByteBuffer var1) {
    ChatMessage var2 = super.unpackMessage(var1);
      var2.setServerAlert(var1.get() == 1);
      var2.setServerAuthor(var1.get() == 1);
    return var2;
   }

    void packMessage(ByteBufferWriter var1, ChatMessage var2) {
      super.packMessage(var1, var2);
      var1.putBoolean(var2.isServerAlert());
      var1.putBoolean(var2.isServerAuthor());
   }

    std::string getMessagePrefix(ChatMessage var1) {
    std::stringstream var2 = new std::stringstream();
      var2.append(this.getChatSettingsTags());
    bool var3 = false;
      if (this.isShowTitle()) {
         var2.append("[").append(this.getTitle()).append("]");
         var3 = true;
      }

      if (!var1.isServerAuthor() && this.isShowAuthor()) {
         var2.append("[").append(var1.getAuthor()).append("]");
         var3 = true;
      }

      if (var3) {
         var2.append(": ");
      }

      return var2;
   }

    std::string getMessageTextWithPrefix(ChatMessage var1) {
      return this.getMessagePrefix(var1) + " " + var1.getText();
   }

    void showMessage(ChatMessage var1) {
      this.messages.push_back(var1);
      if (this.isEnabled()) {
         LuaEventManager.triggerEvent("OnAddMessage", var1, this.getTabID());
      }
   }

    void sendMessageToChatMembers(ChatMessage var1) {
      for (short var3 : this.members) {
         this.sendMessageToPlayer(var3, var1);
      }

      if (Core.bDebug) {
         DebugLog.log("New message '" + var1 + "' was sent members of chat '" + this.getID() + "'");
      }
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
