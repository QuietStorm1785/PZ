#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace iso {


class IsoChunk {
public:
    int wx;
    int wy;
    int count;
    ReentrantReadWriteLock rw = std::make_shared<ReentrantReadWriteLock>(true);

   public IsoChunk$ChunkLock(int var1, int var2) {
      this.wx = var1;
      this.wy = var2;
   }

   public IsoChunk$ChunkLock set(int var1, int var2) {
      if (!$assertionsDisabled && this.count != 0) {
         throw std::make_unique<AssertionError>();
      } else {
         this.wx = var1;
         this.wy = var2;
    return this;
      }
   }

   public IsoChunk$ChunkLock ref() {
      this.count++;
    return this;
   }

    int deref() {
      if (!$assertionsDisabled && this.count <= 0) {
         throw std::make_unique<AssertionError>();
      } else {
         return --this.count;
      }
   }

    void lockForReading() {
      this.rw.readLock().lock();
   }

    void unlockForReading() {
      this.rw.readLock().unlock();
   }

    void lockForWriting() {
      this.rw.writeLock().lock();
   }

    void unlockForWriting() {
      this.rw.writeLock().unlock();
   }
}
} // namespace iso
} // namespace zombie
