#pragma once
#include <mutex>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/logger/ZipLogs.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CoopMaster {
public:

 // Mutexes for synchronized blocks
 std::mutex incomingMessages_mutex;
 std::mutex listeners_mutex;
 Process serverProcess;
 Thread serverThread;
 PrintStream serverCommandStream;
private
 List<String> incomingMessages;
 Pattern serverMessageParser;
private
 CoopMaster.TerminationReason serverTerminationReason;
 Thread timeoutWatchThread;
 bool serverResponded;
 static const CoopMaster instance = new CoopMaster();
 std::string adminUsername = nullptr;
 std::string adminPassword = nullptr;
 std::string serverName = nullptr;
 long serverSteamID = nullptr;
 std::string serverIP = nullptr;
 int serverPort = nullptr;
 int autoCookie = 0;
 static const int autoCookieOffset = 1000000;
 static const int maxAutoCookie = 1000000;
private
 List<
 CoopMaster.Pair<ICoopServerMessageListener, CoopMaster.ListenerOptions>>
 listeners;

private
 CoopMaster() {
 this->incomingMessages = std::make_unique<LinkedList<>>();
 this->listeners = std::make_unique<LinkedList<>>();
 this->serverMessageParser =
 Pattern.compile("^([\\-\\w]+)(\\[(\\d+)\\])?@(.*)$");
 this->adminPassword = UUID.randomUUID().toString();
 }

 int getServerPort() { return this->serverPort; }

 void launchServer(const std::string &string0, const std::string &string1,
 int int0) {
 this->launchServer(string0, string1, int0, false);
 }

 void softreset(const std::string &string0, const std::string &string1,
 int int0) {
 this->launchServer(string0, string1, int0, true);
 }

 void launchServer(const std::string &string3, const std::string &string1,
 int int0, bool boolean0) {
 std::string string0 =
 Paths.get(System.getProperty("java.home"), "bin", "java")
 .toAbsolutePath()
 .toString();
 if (SteamUtils.isSteamModeEnabled()) {
 string1 = "admin";
 }

 std::vector arrayList = new ArrayList();
 arrayList.add(string0);
 arrayList.add("-Xms" + int0 + "m");
 arrayList.add("-Xmx" + int0 + "m");
 arrayList.add("-Djava.library.path=" +
 System.getProperty("java.library.path"));
 arrayList.add("-Djava.class.path=" + System.getProperty("java.class.path"));
 arrayList.add("-Duser.dir=" + System.getProperty("user.dir"));
 arrayList.add("-Duser.home=" + System.getProperty("user.home"));
 arrayList.add("-Dzomboid.znetlog=2");
 arrayList.add("-Dzomboid.steam=" +
 (SteamUtils.isSteamModeEnabled() ? "1" : "0"));
 arrayList.add("-Djava.awt.headless=true");
 arrayList.add("-XX:-OmitStackTraceInFastThrow");
 std::string string2 = this->getGarbageCollector();
 if (string2 != nullptr) {
 arrayList.add(string2);
 }

 if (boolean0) {
 arrayList.add("-Dsoftreset");
 }

 if (Core.bDebug) {
 arrayList.add("-Ddebug");
 }

 arrayList.add("zombie.network.GameServer");
 arrayList.add("-coop");
 arrayList.add("-servername");
 arrayList.add(this->serverName = string3);
 arrayList.add("-adminusername");
 arrayList.add(this->adminUsername = string1);
 arrayList.add("-adminpassword");
 arrayList.add(this->adminPassword);
 arrayList.add("-cachedir=" + ZomboidFileSystem.instance.getCacheDir());
 ProcessBuilder processBuilder = new ProcessBuilder(arrayList);
 ZipLogs.addZipFile(false);
 this->serverTerminationReason =
 CoopMaster.TerminationReason.NormalTermination;
 this->serverResponded = false;
 this->serverProcess = processBuilder.start();
 this->serverCommandStream =
 new PrintStream(this->serverProcess.getOutputStream());
 this->serverThread = new Thread(ThreadGroups.Workers, this ::readServer);
 this->serverThread.setUncaughtExceptionHandler(
 GameWindow::uncaughtException);
 this->serverThread.start();
 this->timeoutWatchThread =
 new Thread(ThreadGroups.Workers, this ::watchServer);
 this->timeoutWatchThread.setUncaughtExceptionHandler(
 GameWindow::uncaughtException);
 this->timeoutWatchThread.start();
 }

 std::string getGarbageCollector() {
 try {
 RuntimeMXBean runtimeMXBean = ManagementFactory.getRuntimeMXBean();
 std::vector list = runtimeMXBean.getInputArguments();
 bool boolean0 = false;
 bool boolean1 = false;

 for (auto &string : list)
 if ("-XX:+UseZGC" == string) {
 boolean0 = true;
 }

 if ("-XX:-UseZGC" == string) {
 boolean0 = false;
 }

 if ("-XX:+UseG1GC" == string) {
 boolean1 = true;
 }

 if ("-XX:-UseG1GC" == string) {
 boolean1 = false;
 }
 }

 if (boolean0) {
 return "-XX:+UseZGC";
 }

 if (boolean1) {
 return "-XX:+UseG1GC";
 }
 }
 catch (Throwable throwable) {
 }

 return nullptr;
}

 void readServer() {
 BufferedReader bufferedReader = new BufferedReader(
 new InputStreamReader(this->serverProcess.getInputStream()));

 while (true) {
 try {
 int int0 = this->serverProcess.exitValue();
 break;
 } catch (IllegalThreadStateException illegalThreadStateException) {
 std::string string = nullptr;

 try {
 string = bufferedReader.readLine();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 if (string != nullptr) {
 this->storeMessage(string);
 this->serverResponded = true;
 }
 }
 }

 this->storeMessage("process-status@terminated");
 ZipLogs.addZipFile(true);
}

void abortServer() { this->serverProcess.destroy(); }

void watchServer() {
 uint8_t byte0 = 20;

 try {
 Thread.sleep(1000 * byte0);
 if (!this->serverResponded) {
 this->serverTerminationReason = CoopMaster.TerminationReason.Timeout;
 this->abortServer();
 }
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
}

bool isRunning() {
 return this->serverThread != nullptr && this->serverThread.isAlive();
}

public
CoopMaster.TerminationReason terminationReason() {
 return this->serverTerminationReason;
}

void storeMessage(const std::string &string) {
 { std::lock_guard<std::mutex> __sync_lock__(incomingMessages_mutex); this->incomingMessages.add(string); }
}

public
void sendMessage(String string0, String string1, String string2) {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append(string0);
 if (string1.empty()) {
 stringBuilder.append("@");
 } else {
 stringBuilder.append("[");
 stringBuilder.append(string1);
 stringBuilder.append("]@");
 }

 stringBuilder.append(string2);
 std::string string3 = stringBuilder.toString();
 if (this->serverCommandStream != nullptr) {
 this->serverCommandStream.println(string3);
 this->serverCommandStream.flush();
 }
}

void sendMessage(const std::string &string0, const std::string &string1) {
 this->sendMessage(string0, nullptr, string1);
}

public
void
invokeServer(String string1, String string2,
 ICoopServerMessageListener iCoopServerMessageListener) {
 this->autoCookie = (this->autoCookie + 1) % 1000000;
 std::string string0 = Integer.toString(1000000 + this->autoCookie);
 this->addListener(iCoopServerMessageListener,
 new CoopMaster.ListenerOptions(string1, string0, true);
 this->sendMessage(string1, string0, string2);
}

std::string getMessage() {
 std::string string = nullptr;
 { std::lock_guard<std::mutex> __sync_lock__(incomingMessages_mutex);
 if (this->incomingMessages.size() != 0) {
 string = this->incomingMessages.get(0);
 this->incomingMessages.remove(0);
 if (!"ping@ping" == string) {
 System.out.println("SERVER: " + string);
 }
 }

 return string;
 }
}

void update() {
 std::string string0;
 while ((string0 = this->getMessage()) != nullptr) {
 Matcher matcher = this->serverMessageParser.matcher(string0);
 if (matcher.find()) {
 std::string string1 = matcher.group(1);
 std::string string2 = matcher.group(3);
 std::string string3 = matcher.group(4);
 LuaEventManager.triggerEvent("OnCoopServerMessage", string1, string2,
 string3);
 this->handleMessage(string1, string2, string3);
 } else {
 DebugLog.log(
 DebugType.Network,
 "[CoopMaster] Unknown message incoming from the slave server: " +
 string0);
 }
 }
}

void handleMessage(const std::string &string0, const std::string &string1,
 const std::string &string2) {
 if (Objects == string0, "ping")) {
 this->sendMessage("ping", string1, "pong");
 }
 else if (Objects == string0, "steam-id")) {
 if (Objects == string2, "nullptr")) {
 this->serverSteamID = nullptr;
 }
 else {
 this->serverSteamID = SteamUtils.convertStringToSteamID(string2);
 }
 }
 else if (Objects == string0, "server-address")) {
 DebugLog.log("Got server-address: " + string2);
 std::string string3 = "^(\\d+\\.\\d+\\.\\d+\\.\\d+):(\\d+)$";
 Pattern pattern = Pattern.compile(string3);
 Matcher matcher = pattern.matcher(string2);
 if (matcher.find()) {
 std::string string4 = matcher.group(1);
 std::string string5 = matcher.group(2);
 this->serverIP = string4;
 this->serverPort = Integer.valueOf(string5);
 DebugLog.log("Successfully parsed: address = " + this->serverIP +
 ", port = " + this->serverPort);
 } else {
 DebugLog.log("Failed to parse server address");
 }
 }

 this->invokeListeners(string0, string1, string2);
}

void register(Platform platform, KahluaTable table1) {
 KahluaTable table0 = platform.newTable();
 table0.rawset("launch", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int int0) {
 bool boolean0 = false;
 if (int0 == 4) {
 void *object0 = luaCallFrame.get(1);
 void *object1 = luaCallFrame.get(2);
 void *object2 = luaCallFrame.get(3);
 if (!(object0 instanceof String) || !(object1 instanceof String) ||
 !(object2 instanceof Double) {
 return 0;
 }

 try {
 CoopMaster.this->launchServer((String)object0, (String)object1,
 ((Double)object2).intValue());
 boolean0 = true;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 } else {
 DebugLog.log(DebugType.Network,
 "[CoopMaster] wrong number of arguments: " + int0);
 }

 luaCallFrame.push(boolean0);
 return 1;
}
});
 table0.rawset("softreset", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int int0) {
 bool boolean0 = false;
 if (int0 == 4) {
 void *object0 = luaCallFrame.get(1);
 void *object1 = luaCallFrame.get(2);
 void *object2 = luaCallFrame.get(3);
 if (!(object0 instanceof String) || !(object1 instanceof String) ||
 !(object2 instanceof Double) {
 return 0;
 }

 try {
 CoopMaster.this->softreset((String)object0, (String)object1,
 ((Double)object2).intValue());
 boolean0 = true;
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 } else {
 DebugLog.log(DebugType.Network,
 "[CoopMaster] wrong number of arguments: " + int0);
 }

 luaCallFrame.push(boolean0);
 return 1;
 }
 });
 table0.rawset("isRunning", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 luaCallFrame.push(CoopMaster.this->isRunning());
 return 1;
 }
 });
 table0.rawset("sendMessage", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int int0) {
 if (int0 == 4) {
 void* object0 = luaCallFrame.get(1);
 void* object1 = luaCallFrame.get(2);
 void* object2 = luaCallFrame.get(3);
 if (object0 instanceof String && object1 instanceof String && object2 instanceof String) {
 CoopMaster.this->sendMessage((String)object0, (String)object1,
 (String)object2);
 }
 }
 else if (int0 == 3) {
 void *object3 = luaCallFrame.get(1);
 void *object4 = luaCallFrame.get(2);
 if (object3 instanceof String && object4 instanceof String) {
 CoopMaster.this->sendMessage((String)object3, (String)object4);
 }
 }

 return 0;
 }
 });
 table0.rawset("getAdminPassword", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 luaCallFrame.push(CoopMaster.this->adminPassword);
 return 1;
 }
 });
 table0.rawset("getTerminationReason", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 luaCallFrame.push(CoopMaster.this->serverTerminationReason.toString());
 return 1;
 }
 });
 table0.rawset("getSteamID", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 if (CoopMaster.this->serverSteamID != nullptr) {
 luaCallFrame.push(SteamUtils.convertSteamIDToString(CoopMaster.this->serverSteamID);
 return 1;
 }
 else {
 return 0;
 }
 }
 });
 table0.rawset("getAddress", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 luaCallFrame.push(CoopMaster.this->serverIP);
 return 1;
 }
 });
 table0.rawset("getPort", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 luaCallFrame.push(CoopMaster.this->serverPort);
 return 1;
 }
 });
 table0.rawset("abort", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame var1, int var2) {
 CoopMaster.this->abortServer();
 return 0;
 }
 });
 table0.rawset("getServerSaveFolder", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 void* object = luaCallFrame.get(1);
 luaCallFrame.push(CoopMaster.this->getServerSaveFolder((String)object);
 return 1;
 }
 });
 table0.rawset("getPlayerSaveFolder", std::make_unique<JavaFunction>() {
 int call(LuaCallFrame luaCallFrame, int var2) {
 void* object = luaCallFrame.get(1);
 luaCallFrame.push(CoopMaster.this->getPlayerSaveFolder((String)object);
 return 1;
 }
 });
 table1.rawset("CoopServer", table0);
 }

 void addListener(ICoopServerMessageListener iCoopServerMessageListener,
 CoopMaster.ListenerOptions listenerOptions) {
 { std::lock_guard<std::mutex> __sync_lock__(listeners_mutex);
 this->listeners.add(new CoopMaster.Pair<>(iCoopServerMessageListener,
 listenerOptions);
 }
 }

 void
 addListener(ICoopServerMessageListener iCoopServerMessageListener) {
 this->addListener(iCoopServerMessageListener, nullptr);
 }

 void
 removeListener(ICoopServerMessageListener iCoopServerMessageListener) {
 { std::lock_guard<std::mutex> __sync_lock__(listeners_mutex);
 int int0 = 0;

 while (int0 < this->listeners.size() &&
 this->listeners.get(int0).first !=
 iCoopServerMessageListener) {
 int0++;
 }

 if (int0 < this->listeners.size()) {
 this->listeners.remove(int0);
 }
 }
 }

 void invokeListeners(const std::string &string0,
 const std::string &string1,
 const std::string &string2) {
 { std::lock_guard<std::mutex> __sync_lock__(listeners_mutex);
 Iterator iterator = this->listeners.iterator();

 while (iterator.hasNext()) {
 CoopMaster.Pair pair = (CoopMaster.Pair)iterator.next();
 ICoopServerMessageListener iCoopServerMessageListener =
 (ICoopServerMessageListener)pair.first;
 CoopMaster.ListenerOptions listenerOptions =
 (CoopMaster.ListenerOptions)pair.second;
 if (iCoopServerMessageListener != nullptr) {
 if (listenerOptions.empty()) {
 iCoopServerMessageListener.OnCoopServerMessage(
 string0, string1, string2);
 } else if ((listenerOptions.tag.empty() ||
 listenerOptions.tag == string0)
 && (listenerOptions.cookie.empty() || listenerOptions.cookie == string1)) {
 if (listenerOptions.autoRemove) {
 iterator.remove();
 }

 iCoopServerMessageListener.OnCoopServerMessage(
 string0, string1, string2);
 }
 }
 }
 }
 }

 std::string getServerName() { return this->serverName; }

 std::string getServerSaveFolder(const std::string &string) {
 return LuaManager.GlobalObject.sanitizeWorldName(string);
 }

 std::string getPlayerSaveFolder(const std::string &string) {
 return LuaManager.GlobalObject.sanitizeWorldName(string + "_player");
 }

 class ListenerOptions {
 std::string tag = nullptr;
 std::string cookie = nullptr;
 bool autoRemove = false;

 public
 ListenerOptions(const std::string &string0,
 const std::string &string1, bool boolean0) {
 this->tag = string0;
 this->cookie = string1;
 this->autoRemove = boolean0;
 }

 public
 ListenerOptions(const std::string &string0,
 const std::string &string1) {
 this(string0, string1, false);
 }

 public
 ListenerOptions(const std::string &string) {
 this(string, nullptr, false);
 }
 }

 class Pair<K, V> {
 const K first;
 const V second;

 public
 Pair(K object0, V object1) {
 this->first = (K)object0;
 this->second = (V)object1;
 }

 K getFirst() { return this->first; }

 V getSecond() { return this->second; }
 }

 public static enum TerminationReason {
 NormalTermination, Timeout;
 }
 }
 } // namespace network
 } // namespace zombie
