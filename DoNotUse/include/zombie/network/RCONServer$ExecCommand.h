#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/RCONServer/ClientThread.h"

namespace zombie {
namespace network {


class RCONServer {
public:
    int ID;
    std::string command;
    std::string response;
    ClientThread thread;

   public RCONServer$ExecCommand(int var1, std::string var2, ClientThread var3) {
      this.ID = var1;
      this.command = var2;
      this.thread = var3;
   }

    void update() {
      this.response = GameServer.rcon(this.command);
      if (this.thread.isAlive()) {
         this.thread.toThread.push_back(this);
      }
   }
}
} // namespace network
} // namespace zombie
