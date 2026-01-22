#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatMode.h"
#include "zombie/chat/ChatSettings.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/core/Color.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/ui/UIFont.h"
#include <filesystem>

namespace zombie {
namespace chat {
namespace defaultChats {


class RadioChat : public RangeBasedChat {
public:
    public RadioChat(ByteBuffer var1, ChatTab var2, IsoPlayer var3) {
      super(var1, ChatType.radio, var2, var3);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }

      this.customTag = "radio";
   }

    public RadioChat(int var1, ChatTab var2) {
      super(var1, ChatType.radio, var2);
      if (!this.isCustomSettings()) {
         this.setSettings(getDefaultSettings());
      }

      this.customTag = "radio";
   }

    public RadioChat() {
      super(ChatType.radio);
      this.setSettings(getDefaultSettings());
      this.customTag = "radio";
   }

    static ChatSettings getDefaultSettings() {
    ChatSettings var0 = std::make_shared<ChatSettings>();
      var0.setBold(true);
      var0.setFontColor(Color.lightGray);
      var0.setShowAuthor(false);
      var0.setShowChatTitle(true);
      var0.setShowTimestamp(true);
      var0.setUnique(true);
      var0.setAllowColors(true);
      var0.setAllowFonts(false);
      var0.setAllowBBcode(true);
      var0.setAllowImages(false);
      var0.setAllowChatIcons(true);
    return var0;
   }

    ChatMessage createMessage(const std::string& var1) {
    ChatMessage var2 = super.createMessage(var1);
      if (this.getMode() == ChatMode.SinglePlayer) {
         var2.setOverHeadSpeech(true);
         var2.setShowInChat(false);
      }

      var2.setShouldAttractZombies(true);
    return var2;
   }

    ChatMessage createBroadcastingMessage(const std::string& var1, int var2) {
    ChatMessage var3 = super.createBubbleMessage(var1);
      var3.setAuthor("");
      var3.setShouldAttractZombies(false);
      var3.setRadioChannel(var2);
    return var3;
   }

    ChatMessage createStaticSoundMessage(const std::string& var1) {
    ChatMessage var2 = super.createBubbleMessage(var1);
      var2.setAuthor("");
      var2.setShouldAttractZombies(false);
    return var2;
   }

    void showInSpeechBubble(ChatMessage var1) {
    Color var2 = this.getColor();
      this.getSpeechBubble()
         .addChatLine(
            var1.getText(),
            var2.r,
            var2.g,
            var2.b,
            UIFont.Dialogue,
            this.getRange(),
            this.customTag,
            this.isAllowBBcode(),
            this.isAllowImages(),
            this.isAllowChatIcons(),
            this.isAllowColors(),
            this.isAllowFonts(),
            this.isEqualizeLineHeights()
         );
   }

    void showMessage(ChatMessage var1) {
      if (this.isEnabled() && var1.isShowInChat() && this.hasChatTab()) {
         LuaEventManager.triggerEvent("OnAddMessage", var1, this.getTabID());
      }
   }

    void sendToServer(ChatMessage var1, DeviceData var2) {
      if (var2 != nullptr) {
    int var3 = PZMath.fastfloor(this.getChatOwner().getX());
    int var4 = PZMath.fastfloor(this.getChatOwner().getY());
    int var5 = var2.getTransmitRange();
         ZomboidRadio.getInstance().SendTransmission(var3, var4, var1, var5);
      }
   }

    ChatMessage unpackMessage(ByteBuffer var1) {
    ChatMessage var2 = super.unpackMessage(var1);
      var2.setRadioChannel(var1.getInt());
      var2.setOverHeadSpeech(var1.get() == 1);
      var2.setShowInChat(var1.get() == 1);
      var2.setShouldAttractZombies(var1.get() == 1);
    return var2;
   }

    void packMessage(ByteBufferWriter var1, ChatMessage var2) {
      super.packMessage(var1, var2);
      var1.putInt(var2.getRadioChannel());
      var1.putBoolean(var2.isOverHeadSpeech());
      var1.putBoolean(var2.isShowInChat());
      var1.putBoolean(var2.isShouldAttractZombies());
   }

    std::string getMessagePrefix(ChatMessage var1) {
    std::stringstream var2 = new std::stringstream(this.getChatSettingsTags());
      if (this.isShowTimestamp()) {
         var2.append("[").append(LuaManager.getHourMinuteJava()).append("]");
      }

      if (this.isShowTitle()) {
         var2.append("[").append(this.getTitle()).append("]");
      }

      if (this.isShowAuthor() && var1.getAuthor() != nullptr && !var1.getAuthor() == "")) {
         var2.append(" ").append(var1.getAuthor()).append(" ");
      } else {
         var2.append(" ").append("Radio").append(" ");
      }

      var2.append(" (").append(this.getRadioChannelStr(var1)).append("): ");
      return var2;
   }

    std::string getRadioChannelStr(ChatMessage var1) {
    std::stringstream var2 = new std::stringstream();
    int var3 = var1.getRadioChannel();
    int var4 = var3 % 1000;

      while (var4 % 10 == 0 && var4 != 0) {
         var4 /= 10;
      }

    int var5 = var3 / 1000;
      var2.append(var5).append(".").append(var4).append(" MHz");
      return var2;
   }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
