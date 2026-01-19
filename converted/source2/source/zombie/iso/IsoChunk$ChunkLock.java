package zombie.iso;

import java.util.concurrent.locks.ReentrantReadWriteLock;

class IsoChunk$ChunkLock {
   public int wx;
   public int wy;
   public int count;
   public ReentrantReadWriteLock rw = new ReentrantReadWriteLock(true);

   public IsoChunk$ChunkLock(int var1, int var2) {
      this.wx = var1;
      this.wy = var2;
   }

   public IsoChunk$ChunkLock set(int var1, int var2) {
      if (!$assertionsDisabled && this.count != 0) {
         throw new AssertionError();
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

   public int deref() {
      if (!$assertionsDisabled && this.count <= 0) {
         throw new AssertionError();
      } else {
         return --this.count;
      }
   }

   public void lockForReading() {
      this.rw.readLock().lock();
   }

   public void unlockForReading() {
      this.rw.readLock().unlock();
   }

   public void lockForWriting() {
      this.rw.writeLock().lock();
   }

   public void unlockForWriting() {
      this.rw.writeLock().unlock();
   }
}
