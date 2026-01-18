#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VoiceTest {
public:
 static bool bQuit = false;
 static ByteBuffer serverBuf = ByteBuffer.allocate(500000);
 static ByteBuffer clientBuf = ByteBuffer.allocate(500000);
 static RakNetPeerInterface rnclientPeer;
 static RakNetPeerInterface rnserverPeer;

 static void rakNetServer(int int0) {
 uint8_t byte0 = 2;
 std::string string = "test";
 rnserverPeer = std::make_unique<RakNetPeerInterface>();
 DebugLog.log("Initialising RakNet...");
 rnserverPeer.Init(false);
 rnserverPeer.SetMaximumIncomingConnections(byte0);
 if (GameServer.IPCommandline != nullptr) {
 rnserverPeer.SetServerIP(GameServer.IPCommandline);
 }

 rnserverPeer.SetServerPort(int0, int0 + 1);
 rnserverPeer.SetIncomingPassword(string);
 rnserverPeer.SetOccasionalPing(true);
 int int1 = rnserverPeer.Startup(byte0);
 System.out.println("RakNet.Startup() return code: " + int1 + " (0 means success)");
 }

 static ByteBuffer rakNetServerReceive() {
 bool boolean0 = false;

 do {
 try {
 Thread.sleep(1L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }

 boolean0 = rnserverPeer.Receive(serverBuf);
 } while (!bQuit && !boolean0);

 return serverBuf;
 }

 static void rakNetServerDecode(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.get() & 255;
 switch (int0) {
 case 0:
 case 1:
 System.out.println("PING");
 break;
 case 16:
 System.out.println("Connection Request Accepted");
 int int2 = byteBuffer.get() & 255;
 long long1 = rnserverPeer.getGuidOfPacket();
 VoiceManager.instance.VoiceConnectReq(long1);
 break;
 case 19:
 System.out.println("ID_NEW_INCOMING_CONNECTION");
 int int1 = byteBuffer.get() & 255;
 long long0 = rnserverPeer.getGuidOfPacket();
 System.out.println("id=" + int1 + " guid=" + long0);
 VoiceManager.instance.VoiceConnectReq(long0);
 break;
 default:
 System.out.println("Received: " + int0);
 }
 }

 static void rakNetClient() {
 uint8_t byte0 = 2;
 std::string string = "test";
 rnclientPeer = std::make_unique<RakNetPeerInterface>();
 DebugLog.log("Initialising RakNet...");
 rnclientPeer.Init(false);
 rnclientPeer.SetMaximumIncomingConnections(byte0);
 rnclientPeer.SetClientPort(GameServer.DEFAULT_PORT + Rand.Next(10000) + 1234);
 rnclientPeer.SetOccasionalPing(true);
 int int0 = rnclientPeer.Startup(byte0);
 System.out.println("RakNet.Startup() return code: " + int0 + " (0 means success)");
 }

 static ByteBuffer rakNetClientReceive() {
 bool boolean0 = false;

 do {
 try {
 Thread.sleep(1L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }

 boolean0 = rnclientPeer.Receive(clientBuf);
 } while (!bQuit && !boolean0);

 return clientBuf;
 }

 static void rakNetClientDecode(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.get() & 255;
 switch (int0) {
 case 0:
 case 1:
 System.out.println("PING");
 break;
 case 16:
 System.out.println("Connection Request Accepted");
 int int2 = byteBuffer.get() & 255;
 long long1 = rnclientPeer.getGuidOfPacket();
 VoiceManager.instance.VoiceConnectReq(long1);
 break;
 case 19:
 System.out.println("ID_NEW_INCOMING_CONNECTION");
 int int1 = byteBuffer.get() & 255;
 long long0 = rnclientPeer.getGuidOfPacket();
 System.out.println("id=" + int1 + " guid=" + long0);
 VoiceManager.instance.VoiceConnectReq(long0);
 break;
 default:
 System.out.println("Received: " + int0);
 }
 }

 static void main(String[] var0) {
 DebugLog.log("VoiceTest: START");
 DebugLog.log("version=" + Core.getInstance().getVersion() + " demo=false");
 DebugLog.log("VoiceTest: SteamUtils.init - EXEC");
 SteamUtils.init();
 DebugLog.log("VoiceTest: SteamUtils.init - OK");
 DebugLog.log("VoiceTest: RakNetPeerInterface - EXEC");
 RakNetPeerInterface.init();
 DebugLog.log("VoiceTest: RakNetPeerInterface - OK");
 DebugLog.log("VoiceTest: VoiceManager.InitVMServer - EXEC");
 VoiceManager.instance.InitVMServer();
 DebugLog.log("VoiceTest: VoiceManager.InitVMServer - OK");
 DebugLog.log("VoiceTest: rakNetServer - EXEC");
 rakNetServer(16000);
 DebugLog.log("VoiceTest: rakNetServer - OK");
 DebugLog.log("VoiceTest: rakNetClient - EXEC");
 rakNetClient();
 DebugLog.log("VoiceTest: rakNetClient - OK");
 DebugLog.log("VoiceTest: rnclientPeer.Connect - EXEC");
 rnclientPeer.Connect("127.0.0.1", 16000, "test", false);
 DebugLog.log("VoiceTest: rnclientPeer.Connect - OK");
 Thread thread0 = std::make_unique<Thread>() {
 void run() {
 while (!VoiceTest.bQuit && !VoiceTest.bQuit) {
 ByteBuffer byteBuffer = VoiceTest.rakNetServerReceive();

 try {
 VoiceTest.rakNetServerDecode(byteBuffer);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }
 };
 thread0.setName("serverThread");
 thread0.start();
 Thread thread1 = std::make_unique<Thread>() {
 void run() {
 while (!VoiceTest.bQuit && !VoiceTest.bQuit) {
 ByteBuffer byteBuffer = VoiceTest.rakNetClientReceive();

 try {
 VoiceTest.rakNetClientDecode(byteBuffer);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }
 };
 thread1.setName("clientThread");
 thread1.start();
 DebugLog.log("VoiceTest: sleep 10 sec");

 try {
 Thread.sleep(10000L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }
}
} // namespace raknet
} // namespace core
} // namespace zombie
