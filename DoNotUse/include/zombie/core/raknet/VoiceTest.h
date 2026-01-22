#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/raknet/VoiceTest/1.h"
#include "zombie/core/raknet/VoiceTest/2.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {


class VoiceTest {
public:
    static bool bQuit = false;
    static ByteBuffer serverBuf = ByteBuffer.allocate(500000);
    static ByteBuffer clientBuf = ByteBuffer.allocate(500000);
    static RakNetPeerInterface rnclientPeer;
    static RakNetPeerInterface rnserverPeer;

    static void rakNetServer(int var0) {
    uint8_t var1 = 2;
    std::string var2 = "test";
      rnserverPeer = std::make_unique<RakNetPeerInterface>();
      DebugLog.log("Initialising RakNet...");
      rnserverPeer.Init(false);
      rnserverPeer.SetMaximumIncomingConnections(var1);
      if (GameServer.IPCommandline != nullptr) {
         rnserverPeer.SetServerIP(GameServer.IPCommandline);
      }

      rnserverPeer.SetServerPort(var0, var0 + 1);
      rnserverPeer.SetIncomingPassword(var2);
      rnserverPeer.SetOccasionalPing(true);
    int var3 = rnserverPeer.Startup(var1);
      System.out.println("RakNet.Startup() return code: " + var3 + " (0 means success)");
   }

    static ByteBuffer rakNetServerReceive() {
    bool var0 = false;

      do {
         try {
            Thread.sleep(1L);
         } catch (InterruptedException var2) {
            var2.printStackTrace();
         }

         var0 = rnserverPeer.Receive(serverBuf);
      } while (!bQuit && !var0);

    return serverBuf;
   }

    static void rakNetServerDecode(ByteBuffer var0) {
    int var1 = var0.get() & 255;
      switch (var1) {
         case 0:
         case 1:
            System.out.println("PING");
            break;
         case 16:
            System.out.println("Connection Request Accepted");
    int var5 = var0.get() & 255;
    long var6 = rnserverPeer.getGuidOfPacket();
            VoiceManager.instance.VoiceConnectReq(var6);
            break;
         case 19:
            System.out.println("ID_NEW_INCOMING_CONNECTION");
    int var2 = var0.get() & 255;
    long var3 = rnserverPeer.getGuidOfPacket();
            System.out.println("id=" + var2 + " guid=" + var3);
            VoiceManager.instance.VoiceConnectReq(var3);
            break;
         default:
            System.out.println("Received: " + var1);
      }
   }

    static void rakNetClient() {
    uint8_t var0 = 2;
    std::string var1 = "test";
      rnclientPeer = std::make_unique<RakNetPeerInterface>();
      DebugLog.log("Initialising RakNet...");
      rnclientPeer.Init(false);
      rnclientPeer.SetMaximumIncomingConnections(var0);
      rnclientPeer.SetClientPort(GameServer.DEFAULT_PORT + Rand.Next(10000) + 1234);
      rnclientPeer.SetOccasionalPing(true);
    int var2 = rnclientPeer.Startup(var0);
      System.out.println("RakNet.Startup() return code: " + var2 + " (0 means success)");
   }

    static ByteBuffer rakNetClientReceive() {
    bool var0 = false;

      do {
         try {
            Thread.sleep(1L);
         } catch (InterruptedException var2) {
            var2.printStackTrace();
         }

         var0 = rnclientPeer.Receive(clientBuf);
      } while (!bQuit && !var0);

    return clientBuf;
   }

    static void rakNetClientDecode(ByteBuffer var0) {
    int var1 = var0.get() & 255;
      switch (var1) {
         case 0:
         case 1:
            System.out.println("PING");
            break;
         case 16:
            System.out.println("Connection Request Accepted");
    int var5 = var0.get() & 255;
    long var6 = rnclientPeer.getGuidOfPacket();
            VoiceManager.instance.VoiceConnectReq(var6);
            break;
         case 19:
            System.out.println("ID_NEW_INCOMING_CONNECTION");
    int var2 = var0.get() & 255;
    long var3 = rnclientPeer.getGuidOfPacket();
            System.out.println("id=" + var2 + " guid=" + var3);
            VoiceManager.instance.VoiceConnectReq(var3);
            break;
         default:
            System.out.println("Received: " + var1);
      }
   }

    static void main(std::string[] var0) {
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
    1 var1 = std::make_shared<1>();
      var1.setName("serverThread");
      var1.start();
    2 var2 = std::make_shared<2>();
      var2.setName("clientThread");
      var2.start();
      DebugLog.log("VoiceTest: sleep 10 sec");

      try {
         Thread.sleep(10000L);
      } catch (InterruptedException var4) {
         var4.printStackTrace();
      }
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
