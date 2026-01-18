#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RadioChat : public RangeBasedChat {
public:
 public RadioChat(ByteBuffer byteBuffer, ChatTab chatTab, IsoPlayer player) {
 super(byteBuffer, ChatType.radio, chatTab, player);
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }

 this->customTag = "radio";
 }

 public RadioChat(int int0, ChatTab chatTab) {
 super(int0, ChatType.radio, chatTab);
 if (!this->isCustomSettings()) {
 this->setSettings(getDefaultSettings());
 }

 this->customTag = "radio";
 }

 public RadioChat() {
 super(ChatType.radio);
 this->setSettings(getDefaultSettings());
 this->customTag = "radio";
 }

 static ChatSettings getDefaultSettings() {
 ChatSettings chatSettings = new ChatSettings();
 chatSettings.setBold(true);
 chatSettings.setFontColor(Color.lightGray);
 chatSettings.setShowAuthor(false);
 chatSettings.setShowChatTitle(true);
 chatSettings.setShowTimestamp(true);
 chatSettings.setUnique(true);
 chatSettings.setAllowColors(true);
 chatSettings.setAllowFonts(false);
 chatSettings.setAllowBBcode(true);
 chatSettings.setAllowImages(false);
 chatSettings.setAllowChatIcons(true);
 return chatSettings;
 }

 ChatMessage createMessage(const std::string& string) {
 ChatMessage chatMessage = super.createMessage(string);
 if (this->getMode() == ChatMode.SinglePlayer) {
 chatMessage.setOverHeadSpeech(true);
 chatMessage.setShowInChat(false);
 }

 chatMessage.setShouldAttractZombies(true);
 return chatMessage;
 }

 ChatMessage createBroadcastingMessage(const std::string& string, int int0) {
 ChatMessage chatMessage = super.createBubbleMessage(string);
 chatMessage.setAuthor("");
 chatMessage.setShouldAttractZombies(false);
 chatMessage.setRadioChannel(int0);
 return chatMessage;
 }

 ChatMessage createStaticSoundMessage(const std::string& string) {
 ChatMessage chatMessage = super.createBubbleMessage(string);
 chatMessage.setAuthor("");
 chatMessage.setShouldAttractZombies(false);
 return chatMessage;
 }

 void showInSpeechBubble(ChatMessage chatMessage) {
 Color color = this->getColor();
 this->getSpeechBubble()
 .addChatLine(
 chatMessage.getText(),
 color.r,
 color.g,
 color.b,
 UIFont.Dialogue,
 this->getRange(),
 this->customTag,
 this->isAllowBBcode(),
 this->isAllowImages(),
 this->isAllowChatIcons(),
 this->isAllowColors(),
 this->isAllowFonts(),
 this->isEqualizeLineHeights()
 );
 }

 void showMessage(ChatMessage chatMessage) {
 if (this->isEnabled() && chatMessage.isShowInChat() && this->hasChatTab()) {
 LuaEventManager.triggerEvent("OnAddMessage", chatMessage, this->getTabID());
 }
 }

 void sendToServer(ChatMessage chatMessage, DeviceData deviceData) {
 if (deviceData != nullptr) {
 int int0 = PZMath.fastfloor(this->getChatOwner().getX());
 int int1 = PZMath.fastfloor(this->getChatOwner().getY());
 int int2 = deviceData.getTransmitRange();
 ZomboidRadio.getInstance().SendTransmission(int0, int1, chatMessage, int2);
 }
 }

 ChatMessage unpackMessage(ByteBuffer byteBuffer) {
 ChatMessage chatMessage = super.unpackMessage(byteBuffer);
 chatMessage.setRadioChannel(byteBuffer.getInt());
 chatMessage.setOverHeadSpeech(byteBuffer.get() == 1);
 chatMessage.setShowInChat(byteBuffer.get() == 1);
 chatMessage.setShouldAttractZombies(byteBuffer.get() == 1);
 return chatMessage;
 }

 void packMessage(ByteBufferWriter byteBufferWriter, ChatMessage chatMessage) {
 super.packMessage(byteBufferWriter, chatMessage);
 byteBufferWriter.putInt(chatMessage.getRadioChannel());
 byteBufferWriter.putBoolean(chatMessage.isOverHeadSpeech());
 byteBufferWriter.putBoolean(chatMessage.isShowInChat());
 byteBufferWriter.putBoolean(chatMessage.isShouldAttractZombies());
 }

 std::string getMessagePrefix(ChatMessage chatMessage) {
 StringBuilder stringBuilder = new StringBuilder(this->getChatSettingsTags());
 if (this->isShowTimestamp()) {
 stringBuilder.append("[").append(LuaManager.getHourMinuteJava()).append("]");
 }

 if (this->isShowTitle()) {
 stringBuilder.append("[").append(this->getTitle()).append("]");
 }

 if (this->isShowAuthor() && chatMessage.getAuthor() != nullptr && !chatMessage.getAuthor() == "")) {
 stringBuilder.append(" ").append(chatMessage.getAuthor()).append(" ");
 } else {
 stringBuilder.append(" ").append("Radio").append(" ");
 }

 stringBuilder.append(" (").append(this->getRadioChannelStr(chatMessage).append("): ");
 return stringBuilder.toString();
 }

 std::string getRadioChannelStr(ChatMessage chatMessage) {
 StringBuilder stringBuilder = new StringBuilder();
 int int0 = chatMessage.getRadioChannel();
 int int1 = int0 % 1000;

 while (int1 % 10 == 0 && int1 != 0) {
 int1 /= 10;
 }

 int int2 = int0 / 1000;
 stringBuilder.append(int2).append(".").append(int1).append(" MHz");
 return stringBuilder.toString();
 }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
