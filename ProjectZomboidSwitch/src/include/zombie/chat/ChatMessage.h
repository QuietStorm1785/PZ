#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/time/LocalDateTime.h"
#include "java/time/format/DateTimeFormatter.h"
#include "zombie/core/Color.h"
#include "zombie/core/network/ByteBufferWriter.h"

namespace zombie {
namespace chat {


class ChatMessage {
public:
    ChatBase chat;
    LocalDateTime datetime;
    std::string author;
    std::string text;
    bool scramble = false;
    std::string customTag;
    Color textColor;
    bool customColor;
    bool overHeadSpeech = true;
    bool showInChat = true;
    bool fromDiscord = false;
    bool serverAlert = false;
    int radioChannel = -1;
    bool local = false;
    bool shouldAttractZombies = false;
    bool serverAuthor = false;

    public ChatMessage(ChatBase var1, const std::string& var2) {
      this(var1, LocalDateTime.now(), var2);
   }

    public ChatMessage(ChatBase var1, LocalDateTime var2, const std::string& var3) {
      this.chat = var1;
      this.datetime = var2;
      this.text = var3;
      this.textColor = var1.getColor();
      this.customColor = false;
   }

    bool isShouldAttractZombies() {
      return this.shouldAttractZombies;
   }

    void setShouldAttractZombies(bool var1) {
      this.shouldAttractZombies = var1;
   }

    bool isLocal() {
      return this.local;
   }

    void setLocal(bool var1) {
      this.local = var1;
   }

    std::string getTextWithReplacedParentheses() {
      return this.text != nullptr ? this.text.replaceAll("<", "&lt;").replaceAll(">", "&gt;") : nullptr;
   }

    void setScrambledText(const std::string& var1) {
      this.scramble = true;
      this.text = var1;
   }

    int getRadioChannel() {
      return this.radioChannel;
   }

    void setRadioChannel(int var1) {
      this.radioChannel = var1;
   }

    bool isServerAuthor() {
      return this.serverAuthor;
   }

    void setServerAuthor(bool var1) {
      this.serverAuthor = var1;
   }

    bool isFromDiscord() {
      return this.fromDiscord;
   }

    void makeFromDiscord() {
      this.fromDiscord = true;
   }

    bool isOverHeadSpeech() {
      return this.overHeadSpeech;
   }

    void setOverHeadSpeech(bool var1) {
      this.overHeadSpeech = var1;
   }

    bool isShowInChat() {
      return this.showInChat;
   }

    void setShowInChat(bool var1) {
      this.showInChat = var1;
   }

    LocalDateTime getDatetime() {
      return this.datetime;
   }

    std::string getDatetimeStr() {
      return this.datetime.format(DateTimeFormatter.ofPattern("h:m"));
   }

    void setDatetime(LocalDateTime var1) {
      this.datetime = var1;
   }

    bool isShowAuthor() {
      return this.getChat().isShowAuthor();
   }

    std::string getAuthor() {
      return this.author;
   }

    void setAuthor(const std::string& var1) {
      this.author = var1;
   }

    ChatBase getChat() {
      return this.chat;
   }

    int getChatID() {
      return this.chat.getID();
   }

    std::string getText() {
      return this.text;
   }

    void setText(const std::string& var1) {
      this.text = var1;
   }

    std::string getTextWithPrefix() {
      return this.chat.getMessageTextWithPrefix(this);
   }

    bool isScramble() {
      return this.scramble;
   }

    std::string getCustomTag() {
      return this.customTag;
   }

    void setCustomTag(const std::string& var1) {
      this.customTag = var1;
   }

    Color getTextColor() {
      return this.textColor;
   }

    void setTextColor(Color var1) {
      this.customColor = true;
      this.textColor = var1;
   }

    bool isCustomColor() {
      return this.customColor;
   }

    void pack(ByteBufferWriter var1) {
      this.chat.packMessage(var1, this);
   }

    ChatMessage clone() {
    ChatMessage var1;
      try {
         var1 = (ChatMessage)super.clone();
      } catch (CloneNotSupportedException var3) {
         throw std::make_unique<RuntimeException>();
      }

      var1.datetime = this.datetime;
      var1.chat = this.chat;
      var1.author = this.author;
      var1.text = this.text;
      var1.scramble = this.scramble;
      var1.customTag = this.customTag;
      var1.textColor = this.textColor;
      var1.customColor = this.customColor;
      var1.overHeadSpeech = this.overHeadSpeech;
    return var1;
   }

    bool isServerAlert() {
      return this.serverAlert;
   }

    void setServerAlert(bool var1) {
      this.serverAlert = var1;
   }

    std::string toString() {
      return "ChatMessage{chat=" + this.chat.getTitle() + ", author='" + this.author + "', text='" + this.text + "'}";
   }
}
} // namespace chat
} // namespace zombie
