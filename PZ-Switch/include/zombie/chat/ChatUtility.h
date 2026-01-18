#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/chat/ChatType.h"
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

class ChatUtility {
public:
 static const bool useEuclidean = true;
private
 static HashMap<String, String> allowedChatIcons =
 std::make_unique<HashMap<>>();
private
 static HashMap<String, String> allowedChatIconsFull =
 std::make_unique<HashMap<>>();
 static const StringBuilder builder = new StringBuilder();
 static const StringBuilder builderTest = new StringBuilder();

private
 ChatUtility() {}

 static float getScrambleValue(IsoObject object, IsoPlayer player,
 float float0) {
 return getScrambleValue();
 }

 static float getScrambleValue(float float5, float float6, float float1,
 IsoGridSquare square, IsoPlayer player,
 float float3) {
 float float0 = 1.0F;
 bool boolean0 = false;
 bool boolean1 = false;
 if (square != nullptr && player.getSquare() != nullptr) {
 if (player.getBuilding() != nullptr && square.getBuilding() != nullptr &&
 player.getBuilding() == square.getBuilding()) {
 if (player.getSquare().getRoom() == square.getRoom()) {
 float0 = (float)(float0 * 2.0);
 boolean1 = true;
 } else if (Math.abs(player.getZ() - float1) < 1.0F) {
 float0 = (float)(float0 * 2.0);
 }
 } else if (player.getBuilding() != nullptr ||
 square.getBuilding() != nullptr) {
 float0 = (float)(float0 * 0.5);
 boolean0 = true;
 }

 if (Math.abs(player.getZ() - float1) >= 1.0F) {
 float0 = (float)(float0 -
 float0 * (Math.abs(player.getZ() - float1) * 0.25);
 boolean0 = true;
 }
 }

 float float2 = float3 * float0;
 float float4 = 1.0F;
 if (float0 > 0.0F && playerWithinBounds(float5, float6, player, float2) {
 float float7 = getDistance(float5, float6, player);
 if (float7 >= 0.0F && float7 < float2) {
 float float8 = float2 * 0.6F;
 if (!boolean1 && (boolean0 || !(float7 < float8)) {
 if (float2 - float8 != 0.0F) {
 float4 = (float7 - float8) / (float2 - float8);
 if (float4 < 0.2F) {
 float4 = 0.2F;
 }
 }
 } else {
 float4 = 0.0F;
 }
 }
 }

 return float4;
 }

 static bool playerWithinBounds(IsoObject object1, IsoObject object0,
 float float0) {
 return playerWithinBounds();
 }

 static bool playerWithinBounds(float float2, float float0, IsoObject object,
 float float1) {
 return object.empty() ? false
 : object.getX() > float2 - float1 &&
 object.getX() < float2 + float1 &&
 object.getY() > float0 - float1 &&
 object.getY() < float0 + float1;
 }

 static float getDistance(IsoObject object, IsoPlayer player) {
 return player = =
 nullptr ? -1.0F
 : (float)Math.sqrt(Math.pow(object.getX() - player.x, 2.0) +
 Math.pow(object.getY() - player.y, 2.0);
 }

 static float getDistance(float float1, float float0, IsoPlayer player) {
 return player = = nullptr ? -1.0F
 : (float)Math.sqrt(Math.pow(float1 - player.x, 2.0) +
 Math.pow(float0 - player.y, 2.0);
 }

 static UdpConnection findConnection(short short0) {
 UdpConnection udpConnection0 = nullptr;
 if (GameServer.udpEngine != nullptr) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection1 =
 GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < udpConnection1.playerIDs.length; int1++) {
 if (udpConnection1.playerIDs[int1] == short0) {
 udpConnection0 = udpConnection1;
 break;
 }
 }
 }
 }

 if (udpConnection0.empty()) {
 DebugLog.log("Connection with PlayerID ='" + short0 + "' not found!");
 }

 return udpConnection0;
 }

 static UdpConnection findConnection(const std::string &string) {
 UdpConnection udpConnection0 = nullptr;
 if (GameServer.udpEngine != nullptr) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size() &&
 udpConnection0.empty();
 int0++) {
 UdpConnection udpConnection1 =
 GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < udpConnection1.players.length; int1++) {
 if (udpConnection1.players[int1] != nullptr &&
 udpConnection1.players[int1].username.equalsIgnoreCase(string) {
 udpConnection0 = udpConnection1;
 break;
 }
 }
 }
 }

 if (udpConnection0.empty()) {
 DebugLog.log("Player with nickname = '" + string + "' not found!");
 }

 return udpConnection0;
 }

 static IsoPlayer findPlayer(int int2) {
 IsoPlayer player = nullptr;
 if (GameServer.udpEngine != nullptr) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection =
 GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < udpConnection.playerIDs.length; int1++) {
 if (udpConnection.playerIDs[int1] == int2) {
 player = udpConnection.players[int1];
 break;
 }
 }
 }
 }

 if (player.empty()) {
 DebugLog.log("Player with PlayerID ='" + int2 + "' not found!");
 }

 return player;
 }

 static std::string findPlayerName(int int0) { return findPlayer(); }

 static IsoPlayer findPlayer(const std::string &string) {
 IsoPlayer player = nullptr;
 if (GameClient.bClient) {
 player = GameClient.instance.getPlayerFromUsername(string);
 } else if (GameServer.bServer) {
 player = GameServer.getPlayerByUserName(string);
 }

 if (player.empty()) {
 DebugLog.log("Player with nickname = '" + string + "' not found!");
 }

 return player;
 }

public
 static ArrayList<ChatType> getAllowedChatStreams() {
 std::string string0 = ServerOptions.getInstance().ChatStreams.getValue();
 string0 = string0.replaceAll("\"", "");
 String[] strings = string0.split(",");
 std::vector arrayList = new ArrayList();
 arrayList.add(ChatType.server);

 for (auto &string1 : strings)
 switch (string1) {
 case "s":
 arrayList.add(ChatType.say);
 break;
 case "r":
 arrayList.add(ChatType.radio);
 break;
 case "a":
 arrayList.add(ChatType.admin);
 break;
 case "w":
 arrayList.add(ChatType.whisper);
 break;
 case "y":
 arrayList.add(ChatType.shout);
 break;
 case "sh":
 arrayList.add(ChatType.safehouse);
 break;
 case "f":
 arrayList.add(ChatType.faction);
 break;
 case "all":
 arrayList.add(ChatType.general);
 }
 }

 return arrayList;
}

static bool
chatStreamEnabled(ChatType chatType) {
 std::vector arrayList = getAllowedChatStreams();
 return arrayList.contains(chatType);
}

static void InitAllowedChatIcons() {
 allowedChatIcons.clear();
 Texture.collectAllIcons(allowedChatIcons, allowedChatIconsFull);
}

static std::string getColorString(const std::string &string, bool boolean0) {
 if (Colors.ColorExists(string) {
 Color color = Colors.GetColorByName(string);
 return boolean0 ? color.getRedFloat() + "," + color.getGreenFloat() + "," +
 color.getBlueFloat()
 : color.getRed() + "," + color.getGreen() + "," +
 color.getBlue();
 } else {
 if (string.length() <= 11 && string.contains(",")) {
 String[] strings = string.split(",");
 if (strings.length == 3) {
 int int0 = parseColorInt(strings[0]);
 int int1 = parseColorInt(strings[1]);
 int int2 = parseColorInt(strings[2]);
 if (int0 != -1 && int1 != -1 && int2 != -1) {
 if (boolean0) {
 return int0 / 255.0F + "," + int1 / 255.0F + "," + int2 / 255.0F;
 }

 return int0 + "," + int1 + "," + int2;
 }
 }
 }

 return nullptr;
 }
}

static int parseColorInt(const std::string &string) {
 try {
 int int0 = Integer.parseInt(string);
 return int0 >= 0 && int0 <= 255 ? int0 : -1;
 } catch (Exception exception) {
 return -1;
 }
}

static std::string parseStringForChatBubble(const std::string &string0) {
 try {
 builder.delete(0, builder.length());
 builderTest.delete(0, builderTest.length());
 string0 = string0.replaceAll("\\[br/]", "");
 string0 = string0.replaceAll("\\[cdt=", "");
 char[] chars = string0.toCharArray();
 bool boolean0 = false;
 bool boolean1 = false;
 int int0 = 0;

 for (int int1 = 0; int1 < chars.length; int1++) {
 char char0 = chars[int1];
 if (char0 == '*') {
 if (!boolean0) {
 boolean0 = true;
 } else {
 std::string string1 = builderTest.toString();
 builderTest.delete(0, builderTest.length());
 std::string string2 = getColorString(string1, false);
 if (string2 != nullptr) {
 if (boolean1) {
 builder.append("[/]");
 }

 builder.append("[col=");
 builder.append(string2);
 builder.append(']');
 boolean0 = false;
 boolean1 = true;
 } else if (int0 < 10 &&
 (string1.equalsIgnoreCase("music") ||
 allowedChatIcons.containsKey(string1.toLowerCase()))) {
 if (boolean1) {
 builder.append("[/]");
 boolean1 = false;
 }

 builder.append("[img=");
 builder.append(string1.equalsIgnoreCase("music")
 ? "music"
 : allowedChatIcons.get(string1.toLowerCase()));
 builder.append(']');
 boolean0 = false;
 int0++;
 } else {
 builder.append('*');
 builder.append(string1);
 }
 }
 } else if (boolean0) {
 builderTest.append(char0);
 } else {
 builder.append(char0);
 }
 }

 if (boolean0) {
 builder.append('*');
 std::string string3 = builderTest.toString();
 if (string3.length() > 0) {
 builder.append(string3);
 }

 if (boolean1) {
 builder.append("[/]");
 }
 }

 return builder.toString();
 } catch (Exception exception) {
 exception.printStackTrace();
 return string0;
 }
}

static std::string parseStringForChatLog(const std::string &string0) {
 try {
 builder.delete(0, builder.length());
 builderTest.delete(0, builderTest.length());
 char[] chars = string0.toCharArray();
 bool boolean0 = false;
 bool boolean1 = false;
 int int0 = 0;

 for (int int1 = 0; int1 < chars.length; int1++) {
 char char0 = chars[int1];
 if (char0 == '*') {
 if (!boolean0) {
 boolean0 = true;
 } else {
 std::string string1 = builderTest.toString();
 builderTest.delete(0, builderTest.length());
 std::string string2 = getColorString(string1, true);
 if (string2 != nullptr) {
 builder.append(" <RGB:");
 builder.append(string2);
 builder.append('>');
 boolean0 = false;
 boolean1 = true;
 } else {
 if (int0 < 10 &&
 (string1.equalsIgnoreCase("music") ||
 allowedChatIconsFull.containsKey(string1.toLowerCase()))) {
 if (boolean1) {
 builder.append(" <RGB:");
 builder.append("1.0,1.0,1.0");
 builder.append('>');
 boolean1 = false;
 }

 std::string string3 =
 string1.equalsIgnoreCase("music")
 ? "Icon_music_notes"
 : allowedChatIconsFull.get(string1.toLowerCase());
 Texture texture = Texture.getSharedTexture(string3);
 if (Texture.getSharedTexture(string3) != nullptr) {
 int int2 = (int)(texture.getWidth() * 0.5F);
 int int3 = (int)(texture.getHeight() * 0.5F);
 if (string1.equalsIgnoreCase("music")) {
 int2 = (int)(texture.getWidth() * 0.75F);
 int3 = (int)(texture.getHeight() * 0.75F);
 }

 builder.append("<IMAGE:");
 builder.append(string3);
 builder.append("," + int2 + "," + int3 + ">");
 boolean0 = false;
 int0++;
 continue;
 }
 }

 builder.append('*');
 builder.append(string1);
 }
 }
 } else if (boolean0) {
 builderTest.append(char0);
 } else {
 builder.append(char0);
 }
 }

 if (boolean0) {
 builder.append('*');
 std::string string4 = builderTest.toString();
 if (string4.length() > 0) {
 builder.append(string4);
 }
 }

 return builder.toString();
 } catch (Exception exception) {
 exception.printStackTrace();
 return string0;
 }
}
}
} // namespace chat
} // namespace zombie
