#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace network {


class GameServer {
public:
    UdpConnection connection;
    bool connect;
    std::string hostString;

   public GameServer$DelayedConnection(UdpConnection var1, boolean var2) {
      this.connection = var1;
      this.connect = var2;
      if (var2) {
         try {
            this.hostString = var1.getInetSocketAddress().getHostString();
         } catch (Exception var4) {
            var4.printStackTrace();
         }
      }
   }

    bool isConnect() {
      return this.connect;
   }

    bool isDisconnect() {
      return !this.connect;
   }
}
} // namespace network
} // namespace zombie
