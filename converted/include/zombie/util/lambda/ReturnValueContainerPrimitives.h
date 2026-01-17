#pragma once
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace lambda {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ReturnValueContainerPrimitives {
public:
public
  static final class RVBoolean extends PooledObject {
    bool ReturnVal;
  private
    static final Pool<ReturnValueContainerPrimitives.RVBoolean> s_pool =
        new Pool<>(ReturnValueContainerPrimitives.RVBoolean::new);

    void onReleased() { this.ReturnVal = false; }

  public
    static ReturnValueContainerPrimitives.RVBoolean alloc() {
      return s_pool.alloc();
    }
  }

  public static final class RVFloat extends PooledObject {
    float ReturnVal;
  private
    static final Pool<ReturnValueContainerPrimitives.RVFloat> s_pool =
        new Pool<>(ReturnValueContainerPrimitives.RVFloat::new);

    void onReleased() { this.ReturnVal = 0.0F; }

  public
    static ReturnValueContainerPrimitives.RVFloat alloc() {
      return s_pool.alloc();
    }
  }

  public static final class RVInt extends PooledObject {
    int ReturnVal;
  private
    static final Pool<ReturnValueContainerPrimitives.RVInt> s_pool =
        new Pool<>(ReturnValueContainerPrimitives.RVInt::new);

    void onReleased() { this.ReturnVal = 0; }

  public
    static ReturnValueContainerPrimitives.RVInt alloc() {
      return s_pool.alloc();
    }
  }
}
} // namespace lambda
} // namespace util
} // namespace zombie
