#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Talker.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo shared display of chat lines functionallity for iso objects & players (characters)
 */
class ChatElement {
public:
 protected ChatElement.PlayerLines[] playerLines = new ChatElement.PlayerLines[4];
 ChatElementOwner owner;
 float historyVal = 1.0F;
 bool historyInRange = false;
 float historyRange = 15.0F;
 bool useEuclidean = true;
 bool hasChatToDisplay = false;
 int maxChatLines = -1;
 int maxCharsPerLine = -1;
 std::string sayLine = nullptr;
 std::string sayLineTag = nullptr;
 TextDrawObject sayLineObject = nullptr;
 bool Speaking = false;
 std::string talkerType = "unknown";
 static bool doBackDrop = true;
 static NineGridTexture backdropTexture;
 int bufferX = 0;
 int bufferY = 0;
 private static ChatElement.PlayerLinesList[] renderBatch = new ChatElement.PlayerLinesList[4];
 private static HashSet<String> noLogText = std::make_unique<HashSet<>>();

 public ChatElement(ChatElementOwner chatowner, int numberoflines, const std::string& talkertype) {
 this->owner = chatowner;
 this->setMaxChatLines(numberoflines);
 this->setMaxCharsPerLine(75);
 this->talkerType = talkertype != nullptr ? talkertype : this->talkerType;
 if (backdropTexture == nullptr) {
 backdropTexture = new NineGridTexture("NineGridBlack", 5);
 }
 }

 void setMaxChatLines(int num) {
 num = num < 1 ? 1 : (num > 10 ? 10 : num);
 if (num != this->maxChatLines) {
 this->maxChatLines = num;

 for (int int0 = 0; int0 < this->playerLines.length; int0++) {
 this->playerLines[int0] = new ChatElement.PlayerLines(this->maxChatLines);
 }
 }
 }

 int getMaxChatLines() {
 return this->maxChatLines;
 }

 void setMaxCharsPerLine(int maxChars) {
 for (int int0 = 0; int0 < this->playerLines.length; int0++) {
 this->playerLines[int0].setMaxCharsPerLine(maxChars);
 }

 this->maxCharsPerLine = maxChars;
 }

 bool IsSpeaking() {
 return this->Speaking;
 }

 std::string getTalkerType() {
 return this->talkerType;
 }

 void setTalkerType(const std::string& type) {
 this->talkerType = type == nullptr ? "" : type;
 }

 std::string getSayLine() {
 return this->sayLine;
 }

 std::string getSayLineTag() {
 return this->Speaking && this->sayLineTag != nullptr ? this->sayLineTag : "";
 }

 void setHistoryRange(float range) {
 this->historyRange = range;
 }

 void setUseEuclidean(bool b) {
 this->useEuclidean = b;
 }

 bool getHasChatToDisplay() {
 return this->hasChatToDisplay;
 }

 float getDistance(IsoPlayer player) {
 if (player == nullptr) {
 return -1.0F;
 } else {
 return this->useEuclidean
 ? (float)Math.sqrt(Math.pow(this->owner.getX() - player.x, 2.0) + Math.pow(this->owner.getY() - player.y, 2.0)
 : Math.abs(this->owner.getX() - player.x) + Math.abs(this->owner.getY() - player.y);
 }
 }

 bool playerWithinBounds(IsoPlayer player, float float0) {
 return player == nullptr
 ? false
 : player.getX() > this->owner.getX() - float0
 && player.getX() < this->owner.getX() + float0
 && player.getY() > this->owner.getY() - float0
 && player.getY() < this->owner.getY() + float0;
 }

 void SayDebug(int n, const std::string& text) {
 if (!GameServer.bServer && n >= 0 && n < this->maxChatLines) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 ChatElement.PlayerLines playerLinesx = this->playerLines[int0];
 if (n < playerLinesx.chatLines.length) {
 if (playerLinesx.chatLines[n].getOriginal() != nullptr && playerLinesx.chatLines[n].getOriginal() == text) {
 playerLinesx.chatLines[n].setInternalTickClock(playerLinesx.lineDisplayTime);
 } else {
 playerLinesx.chatLines[n].setSettings(true, true, true, true, true, true);
 playerLinesx.chatLines[n].setInternalTickClock(playerLinesx.lineDisplayTime);
 playerLinesx.chatLines[n].setCustomTag("default");
 playerLinesx.chatLines[n].setDefaultColors(1.0F, 1.0F, 1.0F, 1.0F);
 playerLinesx.chatLines[n].ReadString(UIFont.Medium, text, this->maxCharsPerLine);
 }
 }
 }
 }

 this->sayLine = text;
 this->sayLineTag = "default";
 this->hasChatToDisplay = true;
 }
 }

 void Say(const std::string& line) {
 this->addChatLine(line, 1.0F, 1.0F, 1.0F, UIFont.Dialogue, 25.0F, "default", false, false, false, false, false, true);
 }

 void addChatLine(const std::string& msg, float r, float g, float b, float baseRange) {
 this->addChatLine(msg, r, g, b, UIFont.Dialogue, baseRange, "default", false, false, false, false, false, true);
 }

 void addChatLine(const std::string& msg, float r, float g, float b) {
 this->addChatLine(msg, r, g, b, UIFont.Dialogue, 25.0F, "default", false, false, false, false, false, true);
 }

 public void addChatLine(
 String msg,
 float r,
 float g,
 float b,
 UIFont font,
 float baseRange,
 String customTag,
 boolean bbcode,
 boolean img,
 boolean icons,
 boolean colors,
 boolean fonts,
 boolean equalizeHeights
 ) {
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr
 && (
 !player.Traits.Deaf.isSet()
 || (
 this->owner instanceof IsoTelevision
 ? ((IsoTelevision)this->owner).isFacing(player)
 : !(this->owner instanceof IsoRadio) && !(this->owner instanceof VehiclePart)
 )
 )) {
 float float0 = this->getScrambleValue(player, baseRange);
 if (float0 < 1.0F) {
 ChatElement.PlayerLines playerLinesx = this->playerLines[int0];
 TextDrawObject textDrawObject = playerLinesx.getNewLineObject();
 if (textDrawObject != nullptr) {
 textDrawObject.setSettings(bbcode, img, icons, colors, fonts, equalizeHeights);
 textDrawObject.setInternalTickClock(playerLinesx.lineDisplayTime);
 textDrawObject.setCustomTag(customTag);
 std::string string;
 if (float0 > 0.0F) {
 string = ZomboidRadio.getInstance().scrambleString(msg, (int)(100.0F * float0), true, "...");
 textDrawObject.setDefaultColors(0.5F, 0.5F, 0.5F, 1.0F);
 } else {
 string = msg;
 textDrawObject.setDefaultColors(r, g, b, 1.0F);
 }

 textDrawObject.ReadString(font, string, this->maxCharsPerLine);
 this->sayLine = msg;
 this->sayLineTag = customTag;
 this->hasChatToDisplay = true;
 }
 }
 }
 }
 }
 }

 float getScrambleValue(IsoPlayer player, float float2) {
 if (this->owner == player) {
 return 0.0F;
 } else {
 float float0 = 1.0F;
 bool boolean0 = false;
 bool boolean1 = false;
 if (this->owner.getSquare() != nullptr && player.getSquare() != nullptr) {
 if (player.getBuilding() != nullptr
 && this->owner.getSquare().getBuilding() != nullptr
 && player.getBuilding() == this->owner.getSquare().getBuilding()) {
 if (player.getSquare().getRoom() == this->owner.getSquare().getRoom()) {
 float0 = (float)(float0 * 2.0);
 boolean1 = true;
 } else if (Math.abs(player.getZ() - this->owner.getZ()) < 1.0F) {
 float0 = (float)(float0 * 2.0);
 }
 } else if (player.getBuilding() != nullptr || this->owner.getSquare().getBuilding() != nullptr) {
 float0 = (float)(float0 * 0.5);
 boolean0 = true;
 }

 if (Math.abs(player.getZ() - this->owner.getZ()) >= 1.0F) {
 float0 = (float)(float0 - float0 * (Math.abs(player.getZ() - this->owner.getZ()) * 0.25);
 boolean0 = true;
 }
 }

 float float1 = float2 * float0;
 float float3 = 1.0F;
 if (float0 > 0.0F && this->playerWithinBounds(player, float1) {
 float float4 = this->getDistance(player);
 if (float4 >= 0.0F && float4 < float1) {
 float float5 = float1 * 0.6F;
 if (!boolean1 && (boolean0 || !(float4 < float5) {
 if (float1 - float5 != 0.0F) {
 float3 = (float4 - float5) / (float1 - float5);
 if (float3 < 0.2F) {
 float3 = 0.2F;
 }
 }
 } else {
 float3 = 0.0F;
 }
 }
 }

 return float3;
 }
 }

 void updateChatLines() {
 this->Speaking = false;
 bool boolean0 = false;
 if (this->hasChatToDisplay) {
 this->hasChatToDisplay = false;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 float float0 = 1.25F * GameTime.getInstance().getMultiplier();
 int int1 = this->playerLines[int0].lineDisplayTime;

 for (TextDrawObject textDrawObject : this->playerLines[int0].chatLines) {
 float float1 = textDrawObject.updateInternalTickClock(float0);
 if (!(float1 <= 0.0F) {
 this->hasChatToDisplay = true;
 if (!boolean0 && !textDrawObject.getCustomTag() == "radio")) {
 float float2 = float1 / (int1 / 2.0F);
 if (float2 >= 1.0F) {
 this->Speaking = true;
 }

 boolean0 = true;
 }

 float0 *= 1.2F;
 }
 }
 }
 }

 if (!this->Speaking) {
 this->sayLine = nullptr;
 this->sayLineTag = nullptr;
 }
 }

 void updateHistory() {
 if (this->hasChatToDisplay) {
 this->historyInRange = false;
 IsoPlayer player = IsoPlayer.getInstance();
 if (player != nullptr) {
 if (player == this->owner) {
 this->historyVal = 1.0F;
 } else {
 if (this->playerWithinBounds(player, this->historyRange) {
 this->historyInRange = true;
 } else {
 this->historyInRange = false;
 }

 if (this->historyInRange && this->historyVal != 1.0F) {
 this->historyVal += 0.04F;
 if (this->historyVal > 1.0F) {
 this->historyVal = 1.0F;
 }
 }

 if (!this->historyInRange && this->historyVal != 0.0F) {
 this->historyVal -= 0.04F;
 if (this->historyVal < 0.0F) {
 this->historyVal = 0.0F;
 }
 }
 }
 }
 } else if (this->historyVal != 0.0F) {
 this->historyVal = 0.0F;
 }
 }

 void update() {
 if (!GameServer.bServer) {
 this->updateChatLines();
 this->updateHistory();
 }
 }

 void renderBatched(int playerNum, int x, int y) {
 this->renderBatched(playerNum, x, y, false);
 }

 void renderBatched(int playerNum, int x, int y, bool ignoreRadioLines) {
 if (playerNum < this->playerLines.length && this->hasChatToDisplay && !GameServer.bServer) {
 this->playerLines[playerNum].renderX = x;
 this->playerLines[playerNum].renderY = y;
 this->playerLines[playerNum].ignoreRadioLines = ignoreRadioLines;
 if (renderBatch[playerNum] == nullptr) {
 renderBatch[playerNum] = new ChatElement.PlayerLinesList();
 }

 renderBatch[playerNum].add(this->playerLines[playerNum]);
 }
 }

 void clear(int playerIndex) {
 this->playerLines[playerIndex].clear();
 }

 static void RenderBatch(int playerNum) {
 if (renderBatch[playerNum] != nullptr && renderBatch[playerNum].size() > 0) {
 for (int int0 = 0; int0 < renderBatch[playerNum].size(); int0++) {
 ChatElement.PlayerLines playerLinesx = renderBatch[playerNum].get(int0);
 playerLinesx.render();
 }

 renderBatch[playerNum].clear();
 }
 }

 static void NoRender(int playerNum) {
 if (renderBatch[playerNum] != nullptr) {
 renderBatch[playerNum].clear();
 }
 }

 static void addNoLogText(const std::string& text) {
 if (text != nullptr && !text.empty()) {
 noLogText.add(text);
 }
 }

 class PlayerLines {
 int lineDisplayTime = 314;
 int renderX = 0;
 int renderY = 0;
 bool ignoreRadioLines = false;
 protected TextDrawObject[] chatLines;

 public PlayerLines(int arg1) {
 this->chatLines = new TextDrawObject[arg1];

 for (int int0 = 0; int0 < this->chatLines.length; int0++) {
 this->chatLines[int0] = new TextDrawObject(0, 0, 0, true, true, true, true, true, true);
 this->chatLines[int0].setDefaultFont(UIFont.Medium);
 }
 }

 void setMaxCharsPerLine(int arg0) {
 for (int int0 = 0; int0 < this->chatLines.length; int0++) {
 this->chatLines[int0].setMaxCharsPerLine(arg0);
 }
 }

 TextDrawObject getNewLineObject() {
 if (this->chatLines != nullptr && this->chatLines.length > 0) {
 TextDrawObject textDrawObject = this->chatLines[this->chatLines.length - 1];
 textDrawObject.Clear();

 for (int int0 = this->chatLines.length - 1; int0 > 0; int0--) {
 this->chatLines[int0] = this->chatLines[int0 - 1];
 }

 this->chatLines[0] = textDrawObject;
 return this->chatLines[0];
 } else {
 return nullptr;
 }
 }

 void render() {
 if (!GameServer.bServer) {
 if (ChatElement.this->hasChatToDisplay) {
 int int0 = 0;

 for (TextDrawObject textDrawObject : this->chatLines) {
 if (textDrawObject.getEnabled()) {
 if (textDrawObject.getWidth() > 0 && textDrawObject.getHeight() > 0) {
 float float0 = textDrawObject.getInternalClock();
 if (!(float0 <= 0.0F) && (!textDrawObject.getCustomTag() == "radio") || !this->ignoreRadioLines) {
 float float1 = float0 / (this->lineDisplayTime / 4.0F);
 if (float1 > 1.0F) {
 float1 = 1.0F;
 }

 this->renderY = this->renderY - (textDrawObject.getHeight() + 1);
 bool boolean0 = textDrawObject.getDefaultFontEnum() != UIFont.Dialogue;
 if (ChatElement.doBackDrop && ChatElement.backdropTexture != nullptr) {
 ChatElement.backdropTexture
 .renderInnerBased(
 this->renderX - textDrawObject.getWidth() / 2,
 this->renderY,
 textDrawObject.getWidth(),
 textDrawObject.getHeight(),
 0.0F,
 0.0F,
 0.0F,
 0.4F
 );
 }

 if (int0 == 0) {
 textDrawObject.Draw(this->renderX, this->renderY, boolean0, float1);
 } else if (ChatElement.this->historyVal > 0.0F) {
 textDrawObject.Draw(this->renderX, this->renderY, boolean0, float1 * ChatElement.this->historyVal);
 }

 int0++;
 }
 } else {
 int0++;
 }
 }
 }
 }
 }
 }

 void clear() {
 if (ChatElement.this->hasChatToDisplay) {
 ChatElement.this->hasChatToDisplay = false;

 for (int int0 = 0; int0 < this->chatLines.length; int0++) {
 if (!(this->chatLines[int0].getInternalClock() <= 0.0F) {
 this->chatLines[int0].Clear();
 this->chatLines[int0].updateInternalTickClock(this->chatLines[int0].getInternalClock());
 }
 }

 ChatElement.this->historyInRange = false;
 ChatElement.this->historyVal = 0.0F;
 }
 }
 }

 class PlayerLinesList extends ArrayList<ChatElement.PlayerLines> {
 }
}
} // namespace chat
} // namespace zombie
