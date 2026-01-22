#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {


class DirectBufferAllocator {
public:
    static const void* LOCK = "DirectBufferAllocator.LOCK";
   private static const std::vector<WrappedBuffer> ALL = std::make_unique<std::vector<>>();

    static WrappedBuffer allocate(int var0) {
      /* synchronized - TODO: add std::mutex */ (LOCK) {
         destroyDisposed();
    WrappedBuffer var2 = std::make_shared<WrappedBuffer>(var0);
         ALL.push_back(var2);
    return var2;
      }
   }

    static void destroyDisposed() {
      /* synchronized - TODO: add std::mutex */ (LOCK) {
         for (int var1 = ALL.size() - 1; var1 >= 0; var1--) {
    WrappedBuffer var2 = ALL.get(var1);
            if (var2.isDisposed()) {
               ALL.remove(var1);
            }
         }
      }
   }

    static long getBytesAllocated() {
      /* synchronized - TODO: add std::mutex */ (LOCK) {
         destroyDisposed();
    long var1 = 0L;

         for (int var3 = 0; var3 < ALL.size(); var3++) {
    WrappedBuffer var4 = ALL.get(var3);
            if (!var4.isDisposed()) {
               var1 += var4.capacity();
            }
         }

    return var1;
      }
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
