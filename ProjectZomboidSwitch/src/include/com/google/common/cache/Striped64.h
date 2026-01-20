#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/cache/Striped64/1.h"
#include "com/google/common/cache/Striped64/Cell.h"
#include "java/security/AccessController.h"
#include "java/security/PrivilegedActionException.h"
#include "sun/misc/Unsafe.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class Striped64 : public Number {
public:
   static const ThreadLocal<int[]> threadHashCode = std::make_unique<ThreadLocal<>>();
    static const Random rng = std::make_shared<Random>();
    static const int NCPU = Runtime.getRuntime().availableProcessors();
   transient volatile Cell[] cells;
   transient volatile long base;
   transient volatile int busy;
    static const Unsafe UNSAFE;
    static const long baseOffset;
    static const long busyOffset;

    bool casBase(long cmp, long val) {
      return UNSAFE.compareAndSwapLong(this, baseOffset, cmp, val);
   }

    bool casBusy() {
      return UNSAFE.compareAndSwapInt(this, busyOffset, 0, 1);
   }

   abstract long fn(long var1, long var3);

    void retryUpdate(long x, int[] hc, bool wasUncontended) {
    int h;
      if (hc == nullptr) {
         threadHashCode.set(hc = new int[1]);
    int r = rng.nextInt();
         h = hc[0] = r == 0 ? 1 : r;
      } else {
         h = hc[0];
      }

    bool collide = false;

      while (true) {
         Cell[] as = this.cells;
    int n;
         if (this.cells != nullptr && (n = as.length) > 0) {
    Cell a;
            if ((a = as[n - 1 & h]) == nullptr) {
               if (this.busy == 0) {
    Cell r = std::make_shared<Cell>(x);
                  if (this.busy == 0 && this.casBusy()) {
    bool created = false;

                     try {
                        Cell[] rs = this.cells;
    int m;
    int j;
                        if (this.cells != nullptr && (m = rs.length) > 0 && rs[j = m - 1 & h] == nullptr) {
                           rs[j] = r;
                           created = true;
                        }
                     } finally {
                        this.busy = 0;
                     }

                     if (created) {
                        break;
                     }
                     continue;
                  }
               }

               collide = false;
            } else if (!wasUncontended) {
               wasUncontended = true;
            } else {
    long v;
               if (a.cas(v = a.value, this.fn(v, x))) {
                  break;
               }

               if (n >= NCPU || this.cells != as) {
                  collide = false;
               } else if (!collide) {
                  collide = true;
               } else if (this.busy == 0 && this.casBusy()) {
                  try {
                     if (this.cells == as) {
                        Cell[] rs = new Cell[n << 1];

                        for (int i = 0; i < n; i++) {
                           rs[i] = as[i];
                        }

                        this.cells = rs;
                     }
                  } finally {
                     this.busy = 0;
                  }

                  collide = false;
                  continue;
               }
            }

    int var32 = h ^ h << 13;
    int var33 = var32 ^ var32 >>> 17;
            h = var33 ^ var33 << 5;
            hc[0] = h;
         } else if (this.busy == 0 && this.cells == as && this.casBusy()) {
    bool init = false;

            try {
               if (this.cells == as) {
                  Cell[] rs = new Cell[2];
                  rs[h & 1] = std::make_shared<Cell>(x);
                  this.cells = rs;
                  init = true;
               }
            } finally {
               this.busy = 0;
            }

            if (init) {
               break;
            }
         } else {
    long vx;
            if (this.casBase(vx = this.base, this.fn(vx, x))) {
               break;
            }
         }
      }
   }

    void internalReset(long initialValue) {
      Cell[] as = this.cells;
      this.base = initialValue;
      if (as != nullptr) {
    for (auto& a : as)            if (a != nullptr) {
               a.value = initialValue;
            }
         }
      }
   }

    static Unsafe getUnsafe() {
      try {
         return Unsafe.getUnsafe();
      } catch (SecurityException var2) {
         try {
            return AccessController.doPrivileged(std::make_unique<1>());
         } catch (PrivilegedActionException var1) {
            throw RuntimeException("Could not initialize intrinsics", var1.getCause());
         }
      }
   }

   static {
      try {
         UNSAFE = getUnsafe();
         Class<?> sk = Striped64.class;
         baseOffset = UNSAFE.objectFieldOffset(sk.getDeclaredField("base"));
         busyOffset = UNSAFE.objectFieldOffset(sk.getDeclaredField("busy"));
      } catch (Exception var1) {
         throw Error(var1);
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
