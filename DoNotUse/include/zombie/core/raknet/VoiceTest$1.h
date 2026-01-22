#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {


class VoiceTest {
public:
    void run() {
      while (!VoiceTest.bQuit && !VoiceTest.bQuit) {
    ByteBuffer var1 = VoiceTest.rakNetServerReceive();

         try {
            VoiceTest.rakNetServerDecode(var1);
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
