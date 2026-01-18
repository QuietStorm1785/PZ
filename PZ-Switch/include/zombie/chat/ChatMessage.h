#pragma once
#include "java/time/LocalDateTime.h"
#include "java/time/format/DateTimeFormatter.h"
#include "zombie/core/Color.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

public
 ChatMessage(ChatBase _chat, const std::string &_text) {
 this(_chat, LocalDateTime.now(), _text);
 }

public
 ChatMessage(ChatBase _chat, LocalDateTime _datetime,
 const std::string &_text) {
 this->chat = _chat;
 this->datetime = _datetime;
 this->text = _text;
 this->textColor = _chat.getColor();
 this->customColor = false;
 }

 bool isShouldAttractZombies() { return this->shouldAttractZombies; }

 void setShouldAttractZombies(bool _shouldAttractZombies) {
 this->shouldAttractZombies = _shouldAttractZombies;
 }

 bool isLocal() { return this->local; }

 void setLocal(bool __local__) { this->local = __local__; }

 std::string getTextWithReplacedParentheses() {
 return this->text != nullptr
 ? this->text.replaceAll("<", "&lt;").replaceAll(">", "&gt;")
 : nullptr;
 }

 void setScrambledText(const std::string &_text) {
 this->scramble = true;
 this->text = _text;
 }

 int getRadioChannel() { return this->radioChannel; }

 void setRadioChannel(int _radioChannel) { this->radioChannel = _radioChannel; }

 bool isServerAuthor() { return this->serverAuthor; }

 void setServerAuthor(bool _serverAuthor) {
 this->serverAuthor = _serverAuthor;
 }

 bool isFromDiscord() { return this->fromDiscord; }

 void makeFromDiscord() { this->fromDiscord = true; }

 bool isOverHeadSpeech() { return this->overHeadSpeech; }

 void setOverHeadSpeech(bool _overHeadSpeech) {
 this->overHeadSpeech = _overHeadSpeech;
 }

 bool isShowInChat() { return this->showInChat; }

 void setShowInChat(bool _showInChat) { this->showInChat = _showInChat; }

 LocalDateTime getDatetime() { return this->datetime; }

 std::string getDatetimeStr() {
 return this->datetime.format(DateTimeFormatter.ofPattern("h:m"));
 }

 void setDatetime(LocalDateTime _datetime) { this->datetime = _datetime; }

 bool isShowAuthor() { return this->getChat().isShowAuthor(); }

 std::string getAuthor() { return this->author; }

 void setAuthor(const std::string &_author) { this->author = _author; }

 ChatBase getChat() { return this->chat; }

 int getChatID() { return this->chat.getID(); }

 std::string getText() { return this->text; }

 void setText(const std::string &_text) { this->text = _text; }

 std::string getTextWithPrefix() {
 return this->chat.getMessageTextWithPrefix(this);
 }

 bool isScramble() { return this->scramble; }

 std::string getCustomTag() { return this->customTag; }

 void setCustomTag(const std::string &_customTag) {
 this->customTag = _customTag;
 }

 Color getTextColor() { return this->textColor; }

 void setTextColor(Color _textColor) {
 this->customColor = true;
 this->textColor = _textColor;
 }

 bool isCustomColor() { return this->customColor; }

 void pack(ByteBufferWriter b) { this->chat.packMessage(b, this); }

 ChatMessage clone() {
 ChatMessage chatMessage0;
 try {
 chatMessage0 = (ChatMessage)super.clone();
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<RuntimeException>();
 }

 chatMessage0.datetime = this->datetime;
 chatMessage0.chat = this->chat;
 chatMessage0.author = this->author;
 chatMessage0.text = this->text;
 chatMessage0.scramble = this->scramble;
 chatMessage0.customTag = this->customTag;
 chatMessage0.textColor = this->textColor;
 chatMessage0.customColor = this->customColor;
 chatMessage0.overHeadSpeech = this->overHeadSpeech;
 return chatMessage0;
 }

 bool isServerAlert() { return this->serverAlert; }

 void setServerAlert(bool _serverAlert) { this->serverAlert = _serverAlert; }

 std::string toString() {
 return "ChatMessage{chat=" + this->chat.getTitle() + ", author='" +
 this->author + "', text='" + this->text + "'}";
 }
}
} // namespace chat
} // namespace zombie
