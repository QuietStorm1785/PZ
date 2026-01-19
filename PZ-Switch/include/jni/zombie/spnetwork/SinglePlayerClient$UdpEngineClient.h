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


class SinglePlayerClient {
:
   private SinglePlayerClient$UdpEngineClient() {
   }

    void Send(ByteBuffer var1) {
      SinglePlayerServer.udpEngine.Receive(var1);
   }

    void Receive(ByteBuffer var1) {
    int var2 = var1.get() & 255;
    short var3 = var1.getShort();
      SinglePlayerClient.addIncoming(var3, var1);
   }
}
} // namespace spnetwork
} // namespace zombie
