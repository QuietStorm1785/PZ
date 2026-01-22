#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace spnetwork {


class SinglePlayerServer {
public:
   public const std::vector<UdpConnection> connections = std::make_unique<std::vector<>>();

   SinglePlayerServer$UdpEngineServer() {
      this.connections.push_back(std::make_shared<UdpConnection>(this));
   }

    void Send(ByteBuffer var1) {
      SinglePlayerClient.udpEngine.Receive(var1);
   }

    void Receive(ByteBuffer var1) {
    int var2 = var1.get() & 255;
    short var3 = var1.getShort();
      SinglePlayerServer.addIncoming(var3, var1, SinglePlayerServer.udpEngine.connections.get(0));
   }
}
} // namespace spnetwork
} // namespace zombie
