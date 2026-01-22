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
namespace utils {


class BufferUtils {
public:
   BufferUtils$ClearReferences() {
      this.setDaemon(true);
   }

    void run() {
      try {
         while (true) {
    Reference var1 = BufferUtils.removeCollected.remove();
            BufferUtils.trackedBuffers.remove(var1);
         }
      } catch (InterruptedException var2) {
         var2.printStackTrace();
      }
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
