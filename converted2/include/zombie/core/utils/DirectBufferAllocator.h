#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DirectBufferAllocator {
public:
  static const void *LOCK = "DirectBufferAllocator.LOCK";
private
  static final ArrayList<WrappedBuffer> ALL = std::make_unique<ArrayList<>>();

  static WrappedBuffer allocate(int int0) {
    synchronized(LOCK) {
      destroyDisposed();
      WrappedBuffer wrappedBuffer = new WrappedBuffer(int0);
      ALL.add(wrappedBuffer);
      return wrappedBuffer;
    }
  }

  static void destroyDisposed() {
    synchronized(LOCK) {
      for (int int0 = ALL.size() - 1; int0 >= 0; int0--) {
        WrappedBuffer wrappedBuffer = ALL.get(int0);
        if (wrappedBuffer.isDisposed()) {
          ALL.remove(int0);
        }
      }
    }
  }

  static long getBytesAllocated() {
    synchronized(LOCK) {
      destroyDisposed();
      long long0 = 0L;

      for (int int0 = 0; int0 < ALL.size(); int0++) {
        WrappedBuffer wrappedBuffer = ALL.get(int0);
        if (!wrappedBuffer.isDisposed()) {
          long0 += wrappedBuffer.capacity();
        }
      }

      return long0;
    }
  }
}
} // namespace utils
} // namespace core
} // namespace zombie
