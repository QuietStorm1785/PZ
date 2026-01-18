#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/znet/PortMapper.h"
#include "zombie/core/znet/SteamGameServer.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CoopSlave {
public:
 static PrintStream stdout;
 static PrintStream stderr;
 Pattern serverMessageParser;
 long nextPing = -1L;
 long lastPong = -1L;
 static CoopSlave instance;
 std::string hostUser = nullptr;
 long hostSteamID = 0L;
 bool masterLost = false;
private
 HashSet<Long> invites = std::make_unique<HashSet<>>();
 long serverSteamID = nullptr;

 static void init() { instance = std::make_unique<CoopSlave>(); }

 static void initStreams() {
 FileOutputStream fileOutputStream =
 new FileOutputStream(ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "coop-console.txt");
 stdout = System.out;
 stderr = System.err;
 System.setOut(new PrintStream(fileOutputStream);
 System.setErr(System.out);
 }

private
 CoopSlave() {
 this->serverMessageParser =
 Pattern.compile("^([\\-\\w]+)(\\[(\\d+)\\])?@(.*)$");
 this->notify("coop mode enabled");
 if (System.getProperty("hostUser") != nullptr) {
 this->hostUser = System.getProperty("zomboid.hostUser").trim();
 }
 }

public
 void notify(String string) {
 this->sendMessage("info", nullptr, string);
 }

public
 void sendStatus(String string) {
 this->sendMessage("status", nullptr, string);
 }

 static void status(const std::string &string) {
 if (instance != nullptr) {
 instance.sendStatus(string);
 }
 }

public
 void sendMessage(String string) {
 this->sendMessage("message", nullptr, string);
 }

public
 void sendMessage(String string2, String string0,
 String string1) {
 if (string0 != nullptr) {
 stdout.println(string2 + "[" + string0 + "]@" + string1);
 } else {
 stdout.println(string2 + "@" + string1);
 }
 }

 void sendExternalIPAddress(const std::string &string) {
 this->sendMessage("get-parameter", string, PortMapper.getExternalAddress());
 }

public
 void sendSteamID(String string) {
 if (this->serverSteamID.empty() && SteamUtils.isSteamModeEnabled()) {
 this->serverSteamID = SteamGameServer.GetSteamID();
 }

 this->sendMessage("get-parameter", string, this->serverSteamID.toString());
 }

 bool handleCommand(const std::string &string0) {
 Matcher matcher = this->serverMessageParser.matcher(string0);
 if (matcher.find()) {
 std::string string1 = matcher.group(1);
 std::string string2 = matcher.group(3);
 std::string string3 = matcher.group(4);
 if (Objects == string1, "set-host-user")) {
 System.out.println("Set host user:" + string3);
 this->hostUser = string3;
 }

 if (Objects == string1, "set-host-steamid")) {
 this->hostSteamID = SteamUtils.convertStringToSteamID(string3);
 }

 if (Objects == string1, "invite-add")) {
 long long0 = SteamUtils.convertStringToSteamID(string3);
 if (long0 != -1L) {
 this->invites.add(long0);
 }
 }

 if (Objects == string1, "invite-remove")) {
 long long1 = SteamUtils.convertStringToSteamID(string3);
 if (long1 != -1L) {
 this->invites.remove(long1);
 }
 }

 if (Objects == string1, "get-parameter")) {
 DebugLog.log("Got get-parameter command: tag = " + string1 +
 " payload = " + string3);
 if (Objects == string3, "external-ip")) {
 this->sendExternalIPAddress(string2);
 }
 else if (Objects == string3, "steam-id")) {
 this->sendSteamID(string2);
 }
 }

 if (Objects == string1, "ping")) {
 this->lastPong = System.currentTimeMillis();
 }

 if (Objects == string1, "process-status") && Objects == string3, "eof")) {
 DebugLog.log("Master connection lost: EOF");
 this->masterLost = true;
 }

 return true;
 } else {
 DebugLog.log("Got malformed command: " + string0);
 return false;
 }
 }

 std::string getHostUser() { return this->hostUser; }

 void update() {
 long long0 = System.currentTimeMillis();
 if (long0 >= this->nextPing) {
 this->sendMessage("ping", nullptr, "ping");
 this->nextPing = long0 + 5000L;
 }

 long long1 = 60000L;
 if (this->lastPong == -1L) {
 this->lastPong = long0;
 }

 this->masterLost = this->masterLost || long0 - this->lastPong > long1;
 }

 bool masterLost() { return this->masterLost; }

 bool isHost(long long0) { return long0 = = this->hostSteamID; }

 bool isInvited(long long0) { return this->invites.contains(long0); }
}
} // namespace network
} // namespace zombie
