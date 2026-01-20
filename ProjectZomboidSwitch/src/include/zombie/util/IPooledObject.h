#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {


class IPooledObject {
public:
    virtual ~IPooledObject() = default;
   Pool<IPooledObject> getPool();

    void setPool(Pool<IPooledObject> var1);

    void release();

    bool isFree();

    void setFree(bool var1);

   default void onReleased() {
   }

    static void release(IPooledObject[] var0) {
    int var1 = 0;

      for (int var2 = var0.length; var1 < var2; var1++) {
         Pool.tryRelease(var0[var1]);
      }
   }

    static void tryReleaseAndBlank(IPooledObject[] var0) {
      if (var0 != nullptr) {
         releaseAndBlank(var0);
      }
   }

    static void releaseAndBlank(IPooledObject[] var0) {
    int var1 = 0;

      for (int var2 = var0.length; var1 < var2; var1++) {
         var0[var1] = Pool.tryRelease(var0[var1]);
      }
   }

    static void release(List<? extends) {
    int var1 = 0;

      for (int var2 = var0.size(); var1 < var2; var1++) {
         Pool.tryRelease((IPooledObject)var0.get(var1));
      }

      var0.clear();
   }
}
} // namespace util
} // namespace zombie
