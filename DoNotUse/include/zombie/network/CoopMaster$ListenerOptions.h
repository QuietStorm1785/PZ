#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class CoopMaster {
public:
    std::string tag;
    std::string cookie;
    bool autoRemove;

   public CoopMaster$ListenerOptions(CoopMaster var1, std::string var2, std::string var3, boolean var4) {
      this.this$0 = var1;
      this.tag = nullptr;
      this.cookie = nullptr;
      this.autoRemove = false;
      this.tag = var2;
      this.cookie = var3;
      this.autoRemove = var4;
   }

   public CoopMaster$ListenerOptions(CoopMaster var1, std::string var2, std::string var3) {
      this(var1, var2, var3, false);
   }

   public CoopMaster$ListenerOptions(CoopMaster var1, std::string var2) {
      this(var1, var2, nullptr, false);
   }
}
} // namespace network
} // namespace zombie
