#pragma once
#include <mutex>
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

 // Mutexes for synchronized blocks
 static std::mutex LOCK_mutex;
 static const void *LOCK = "DirectBufferAllocator.LOCK";
private
 static ArrayList<WrappedBuffer> ALL = std::make_unique<ArrayList<>>();

 static WrappedBuffer allocate(int int0) {
 { std::lock_guard<std::mutex> __sync_lock__(LOCK_mutex);
 destroyDisposed();
 WrappedBuffer wrappedBuffer = new WrappedBuffer(int0);
 ALL.add(wrappedBuffer);
 return wrappedBuffer;
 }
 }

 static void destroyDisposed() {
 { std::lock_guard<std::mutex> __sync_lock__(LOCK_mutex);
 for (int int0 = ALL.size() - 1; int0 >= 0; int0--) {
 WrappedBuffer wrappedBuffer = ALL.get(int0);
 if (wrappedBuffer.isDisposed()) {
 ALL.remove(int0);
 }
 }
 }
 }

 static long getBytesAllocated() {
 { std::lock_guard<std::mutex> __sync_lock__(LOCK_mutex);
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
