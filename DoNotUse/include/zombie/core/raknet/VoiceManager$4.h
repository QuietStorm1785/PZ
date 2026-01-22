#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace raknet {

class VoiceManager {
public:
   VoiceManager$4(VoiceManager var1) {
      this.this$0 = var1;
   }

    void run() {
      while (!this.this$0.bQuit) {
         try {
            this.this$0.UpdateVMClient();
            sleep(VoiceManager.period / 2);
         } catch (Exception var2) {
            var2.printStackTrace();
         }
      }
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
