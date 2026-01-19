#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatBase.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/chat/ChatMode.h"
#include "zombie/chat/ChatTab.h"
#include "zombie/chat/ChatUtility.h"
#include "zombie/core/Color.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace chat {
namespace defaultChats {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RangeBasedChat : public ChatBase {
public:
 static ChatElement overHeadChat = nullptr;
private
 static HashMap<String, IsoPlayer> players = nullptr;
 static std::string currentPlayerName = nullptr;
 std::string customTag = "default";

 RangeBasedChat(ByteBuffer byteBuffer, ChatType chatType, ChatTab chatTab,
 IsoPlayer player) {
 super(byteBuffer, chatType, chatTab, player);
 }

 RangeBasedChat(ChatType chatType) { super(chatType); }

 RangeBasedChat(int int0, ChatType chatType, ChatTab chatTab) {
 super(int0, chatType, chatTab);
 }

 void Init() {
 currentPlayerName = this->getChatOwnerName();
 if (players != nullptr) {
 players.clear();
 }

 overHeadChat = this->getChatOwner().getChatElement();
 }

 bool isSendingToRadio() { return true; }

 ChatMessage createMessage(std::string_view string) {
 ChatMessage chatMessage = super.createMessage(string);
 if (this->getMode() == ChatMode.SinglePlayer) {
 chatMessage.setShowInChat(false);
 }

 chatMessage.setOverHeadSpeech(true);
 chatMessage.setShouldAttractZombies(true);
 return chatMessage;
 }

 ChatMessage createBubbleMessage(std::string_view string) {
 ChatMessage chatMessage = super.createMessage(string);
 chatMessage.setOverHeadSpeech(true);
 chatMessage.setShowInChat(false);
 return chatMessage;
 }

 void sendMessageToChatMembers(ChatMessage chatMessage) {
 IsoPlayer player0 = ChatUtility.findPlayer(chatMessage.getAuthor());
 if (this->getRange() == -1.0F) {
 DebugLog.log("Range not set for '" + this->getTitle() +
 "' chat. Message '" + chatMessage.getText() + "' ignored");
 } else {
 for (short short0 : this->members) {
 IsoPlayer player1 = ChatUtility.findPlayer(short0);
 if (player1 != nullptr && player0.getOnlineID() != short0 &&
 ChatUtility.getDistance(player0, player1) < this->getRange()) {
 this->sendMessageToPlayer(short0, chatMessage);
 }
 }
 }
 }

 void showMessage(ChatMessage chatMessage) {
 super.showMessage(chatMessage);
 if (chatMessage.isOverHeadSpeech()) {
 this->showInSpeechBubble(chatMessage);
 }
 }

 ChatElement getSpeechBubble() { return overHeadChat; }

 UIFont selectFont(std::string_view string) {
 char[] chars = string.toCharArray();
 UIFont uIFont = UIFont.Dialogue;
 AngelCodeFont angelCodeFont = TextManager.instance.getFontFromEnum(uIFont);

 for (int int0 = 0; int0 < chars.length; int0++) {
 if (chars[int0] > angelCodeFont.chars.length) {
 uIFont = UIFont.Medium;
 break;
 }
 }

 return uIFont;
 }

 void showInSpeechBubble(ChatMessage chatMessage) {
 Color color = this->getColor();
 std::string string0 = chatMessage.getAuthor();
 IsoPlayer player0 = this->getPlayer(string0);
 float float0 = color.r;
 float float1 = color.g;
 float float2 = color.b;
 if (player0 != nullptr) {
 float0 = player0.getSpeakColour().r;
 float1 = player0.getSpeakColour().g;
 float2 = player0.getSpeakColour().b;
 }

 std::string string1 =
 ChatUtility.parseStringForChatBubble(chatMessage.getText());
 if (string0 != nullptr && !"".equalsIgnoreCase(string0) &&
 !string0.equalsIgnoreCase(currentPlayerName) {
 if (!players.containsKey(string0) {
 players.put(string0, this->getPlayer(string0);
 }

 IsoPlayer player1 = players.get(string0);
 if (player1 != nullptr) {
 if (player1.isDead()) {
 player1 = this->getPlayer(string0);
 players.replace(string0, player1);
 }

 player1.getChatElement().addChatLine(
 string1, float0, float1, float2, this->selectFont(string1),
 this->getRange(), this->customTag, this->isAllowBBcode(),
 this->isAllowImages(), this->isAllowChatIcons(), this->isAllowColors(),
 this->isAllowFonts(), this->isEqualizeLineHeights());
 }
 } else {
 overHeadChat.addChatLine(
 string1, float0, float1, float2, this->selectFont(string1),
 this->getRange(), this->customTag, this->isAllowBBcode(),
 this->isAllowImages(), this->isAllowChatIcons(), this->isAllowColors(),
 this->isAllowFonts(), this->isEqualizeLineHeights());
 }
 }

 IsoPlayer getPlayer(std::string_view string) {
 IsoPlayer player = GameClient.bClient
 ? GameClient.instance.getPlayerFromUsername(string)
 : nullptr;
 if (player != nullptr) {
 return player;
 } else {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 player = IsoPlayer.players[int0];
 if (player != nullptr && player.getUsername() == string) {
 return player;
 }
 }

 return nullptr;
 }
 }

 static { players = std::make_unique<HashMap<>>(); }
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
