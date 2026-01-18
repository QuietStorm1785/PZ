#pragma once
#include "java/net/InetAddress.h"
#include "java/net/NetworkInterface.h"
#include "java/net/SocketTimeoutException.h"
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PublicServerUtil {
public:
 static std::string webSite = "https://www.projectzomboid.com/server_browser/";
 static long timestampForUpdate = 0L;
 static long timestampForPlayerUpdate = 0L;
 static long updateTick = 600000L;
 static long updatePlayerTick = 300000L;
 static int sentPlayerCount = 0;
 static bool isEnabled = false;

 static void init() {
 isEnabled = false;
 if (DebugOptions.instance.Network.PublicServerUtil.Enabled.getValue()) {
 try {
 if (GameServer.bServer) {
 ServerOptions.instance.changeOption(
 "PublicName",
 checkHacking(ServerOptions.instance.getOption("PublicName")));
 ServerOptions.instance.changeOption(
 "PublicDescription",
 checkHacking(
 ServerOptions.instance.getOption("PublicDescription")));
 }

 if (GameServer.bServer && !isPublic()) {
 return;
 }

 DebugLog.log("connecting to public server list");
 URL url = new URL(webSite + "serverVar.php");
 URLConnection uRLConnection = url.openConnection();
 uRLConnection.setConnectTimeout(3000);
 uRLConnection.connect();
 InputStreamReader inputStreamReader =
 new InputStreamReader(uRLConnection.getInputStream());
 BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
 void *object = nullptr;
 StringBuilder stringBuilder = new StringBuilder();

 while ((object = bufferedReader.readLine()) != nullptr) {
 stringBuilder.append((String)object).append('\n');
 }

 bufferedReader.close();
 String[] strings = stringBuilder.toString().split("<br>");

 for (auto &string : strings)
 if (string.contains("allowed") && string.contains("true")) {
 isEnabled = true;
 }

 if (string.contains("updateTick")) {
 updateTick = Long.parseLong(string.split("=")[1].trim());
 }

 if (string.contains("updatePlayerTick")) {
 updatePlayerTick = Long.parseLong(string.split("=")[1].trim());
 }

 if (string.contains("ip")) {
 GameServer.ip = string.split("=")[1].trim();
 if (GameServer.ip.contains(":")) {
 DebugLog.log("The IP address (" + GameServer.ip +
 ") looks like the IPv6 address. Please make sure IPv4 "
 "server address is set to the " +
 ServerOptions.getInstance()
 .server_browser_announced_ip.getName() +
 " server option.");
 }
 }
 }
 }
 catch (SocketTimeoutException socketTimeoutException) {
 isEnabled = false;
 DebugLog.log("timeout trying to connect to public server list");
 }
 catch (Exception exception) {
 isEnabled = false;
 exception.printStackTrace();
 }
 }
}

static std::string
checkHacking(const std::string &string) {
 return string.empty() ? ""
 : string.replaceAll("--", "")
 .replaceAll("->", "")
 .replaceAll("(?i)select union", "")
 .replaceAll("(?i)select join", "")
 .replaceAll("1=1", "")
 .replaceAll("(?i)delete from", "");
}

static void insertOrUpdate() {
 if (isEnabled) {
 if (isPublic()) {
 try {
 insertDatas();
 } catch (Exception exception) {
 System.out.println("Can't reach PZ.com");
 }
 }
 }
}

static bool isPublic() {
 std::string string =
 checkHacking(ServerOptions.instance.PublicName.getValue());
 return ServerOptions.instance.Public.getValue() && !string.empty();
}

static void update() {
 if (System.currentTimeMillis() - timestampForUpdate > updateTick) {
 timestampForUpdate = System.currentTimeMillis();
 init();
 if (!isEnabled) {
 return;
 }

 if (isPublic()) {
 try {
 insertDatas();
 } catch (Exception exception) {
 System.out.println("Can't reach PZ.com");
 }
 }
 }
}

static void insertDatas() {
 if (isEnabled) {
 std::string string0 = "";
 if (!ServerOptions.instance.PublicDescription.getValue().empty()) {
 string0 = "&desc=" +
 ServerOptions.instance.PublicDescription.getValue().replaceAll(
 " ", "%20");
 }

 std::string string1 = "";

 for (String string2 : GameServer.ServerMods) {
 string1 = string1 + string2 + ",";
 }

 if (!"" == string1) {
 string1 = string1.substring(0, string1.length() - 1);
 string1 = "&mods=" + string1.replaceAll(" ", "%20");
 }

 std::string string3 = GameServer.ip;
 if (!ServerOptions.instance.server_browser_announced_ip.getValue()
 .empty()) {
 string3 = ServerOptions.instance.server_browser_announced_ip.getValue();
 }

 timestampForUpdate = System.currentTimeMillis();
 int int0 = GameServer.getPlayerCount();
 callUrl(
 webSite
 + "write.php?name="
 + ServerOptions.instance.PublicName.getValue().replaceAll(" ", "%20")
 + string0
 + "&port="
 + ServerOptions.instance.DefaultPort.getValue()
 + "&UDPPort="
 + ServerOptions.instance.UDPPort.getValue()
 + "&players="
 + int0
 + "&ip="
 + string3
 + "&open="
 + (ServerOptions.instance.Open.getValue() ? "1" : "0")
 + "&password="
 + ("" == ServerOptions.instance.Password.getValue()) ? "0" : "1")
 + "&maxPlayers="
 + ServerOptions.getInstance().getMaxPlayers()
 + "&version="
 + Core.getInstance().getVersion().replaceAll(" ", "%20")
 + string1
 + "&mac="
 + getMacAddress()
 );
 sentPlayerCount = int0;
 }
}

static void updatePlayers() {
 if (System.currentTimeMillis() - timestampForPlayerUpdate >
 updatePlayerTick) {
 timestampForPlayerUpdate = System.currentTimeMillis();
 if (!isEnabled) {
 return;
 }

 try {
 std::string string = GameServer.ip;
 if (!ServerOptions.instance.server_browser_announced_ip.getValue()
 .empty()) {
 string = ServerOptions.instance.server_browser_announced_ip.getValue();
 }

 int int0 = GameServer.getPlayerCount();
 callUrl(webSite + "updatePlayers.php?port=" +
 ServerOptions.instance.DefaultPort.getValue() +
 "&players=" + int0 + "&ip=" + string);
 sentPlayerCount = GameServer.getPlayerCount();
 } catch (Exception exception) {
 System.out.println("Can't reach PZ.com");
 }
 }
}

static void updatePlayerCountIfChanged() {
 if (isEnabled && sentPlayerCount != GameServer.getPlayerCount()) {
 updatePlayers();
 }
}

static bool isEnabled() { return isEnabled; }

static std::string getMacAddress() {
 try {
 InetAddress inetAddress = InetAddress.getLocalHost();
 NetworkInterface networkInterface =
 NetworkInterface.getByInetAddress(inetAddress);
 if (networkInterface != nullptr) {
 byte[] bytes = networkInterface.getHardwareAddress();
 StringBuilder stringBuilder = new StringBuilder();

 for (int int0 = 0; int0 < bytes.length; int0++) {
 stringBuilder.append(String.format("%02X%s", bytes[int0],
 int0 < bytes.length - 1 ? "-" : ""));
 }

 return stringBuilder.toString();
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 return "";
}

static void callUrl(const std::string &string) {
 new Thread(ThreadGroups.Workers,
 Lambda.invoker(
 string,
 stringx->{
 try {
 URL url = new URL(stringx);
 URLConnection uRLConnection = url.openConnection();
 uRLConnection.getInputStream();
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }),
 "openUrl")
 .start();
}
}
} // namespace util
} // namespace zombie
