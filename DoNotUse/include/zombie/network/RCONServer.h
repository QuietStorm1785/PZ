#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/InetSocketAddress.h"
#include "java/net/ServerSocket.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/RCONServer/ExecCommand.h"
#include "zombie/network/RCONServer/ServerThread.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class RCONServer {
public:
    static const int SERVERDATA_RESPONSE_VALUE = 0;
    static const int SERVERDATA_AUTH_RESPONSE = 2;
    static const int SERVERDATA_EXECCOMMAND = 2;
    static const int SERVERDATA_AUTH = 3;
    static RCONServer instance;
    ServerSocket welcomeSocket;
    ServerThread thread;
    std::string password;
   private ConcurrentLinkedQueue<ExecCommand> toMain = std::make_unique<ConcurrentLinkedQueue<>>();

    private RCONServer(int var1, const std::string& var2, bool var3) {
      this.password = var2;

      try {
         this.welcomeSocket = std::make_unique<ServerSocket>();
         if (var3) {
            this.welcomeSocket.bind(std::make_shared<InetSocketAddress>("127.0.0.1", var1));
         } else if (GameServer.IPCommandline != nullptr) {
            this.welcomeSocket.bind(std::make_shared<InetSocketAddress>(GameServer.IPCommandline, var1));
         } else {
            this.welcomeSocket.bind(std::make_shared<InetSocketAddress>(var1));
         }

         DebugLog.log("RCON: listening on port " + var1);
      } catch (IOException var7) {
         DebugLog.log("RCON: error creating socket on port " + var1);
         var7.printStackTrace();

         try {
            this.welcomeSocket.close();
            this.welcomeSocket = nullptr;
         } catch (IOException var6) {
            var6.printStackTrace();
         }

         return;
      }

      this.thread = std::make_shared<ServerThread>(this);
      this.thread.start();
   }

    void updateMain() {
      for (ExecCommand var1 = this.toMain.poll(); var1 != nullptr; var1 = this.toMain.poll()) {
         var1.update();
      }
   }

    void quit() {
      if (this.welcomeSocket != nullptr) {
         try {
            this.welcomeSocket.close();
         } catch (IOException var2) {
         }

         this.welcomeSocket = nullptr;
         this.thread.quit();
         this.thread = nullptr;
      }
   }

    static void init(int var0, const std::string& var1, bool var2) {
      instance = std::make_shared<RCONServer>(var0, var1, var2);
   }

    static void update() {
      if (instance != nullptr) {
         instance.updateMain();
      }
   }

    static void shutdown() {
      if (instance != nullptr) {
         instance.quit();
      }
   }
}
} // namespace network
} // namespace zombie
