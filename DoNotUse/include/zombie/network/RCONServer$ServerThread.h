#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/Socket.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/RCONServer/ClientThread.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class RCONServer {
public:
   private std::vector<ClientThread> connections;
    bool bQuit;

   public RCONServer$ServerThread(RCONServer var1) {
      this.this$0 = var1;
      this.connections = std::make_unique<std::vector<>>();
      this.setName("RCONServer");
   }

    void run() {
      while (!this.bQuit) {
         this.runInner();
      }
   }

    void runInner() {
      try {
    Socket var1 = this.this$0.welcomeSocket.accept();

         for (int var2 = 0; var2 < this.connections.size(); var2++) {
    ClientThread var3 = this.connections.get(var2);
            if (!var3.isAlive()) {
               this.connections.remove(var2--);
            }
         }

         if (this.connections.size() >= 5) {
            var1.close();
            return;
         }

         DebugLog.log("RCON: new connection " + var1);
    ClientThread var5 = std::make_shared<ClientThread>(var1, this.this$0.password);
         this.connections.push_back(var5);
         var5.start();
      } catch (IOException var4) {
         if (!this.bQuit) {
            var4.printStackTrace();
         }
      }
   }

    void quit() {
      this.bQuit = true;

      while (this.isAlive()) {
         try {
            Thread.sleep(50L);
         } catch (InterruptedException var3) {
            var3.printStackTrace();
         }
      }

      for (int var1 = 0; var1 < this.connections.size(); var1++) {
    ClientThread var2 = this.connections.get(var1);
         var2.quit();
      }
   }
}
} // namespace network
} // namespace zombie
