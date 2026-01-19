package zombie.popman;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;
import zombie.popman.ObjectPool.1;
import zombie.popman.ObjectPool.Allocator;

public class ObjectPool<T> {
   private final Allocator<T> allocator;
   private final ArrayList<T> pool = new 1(this);

   public ObjectPool() {
      this(null);
   }

   public ObjectPool(Allocator<T> var1) {
      this.allocator = var1;
   }

   public T alloc() {
      return this.pool.isEmpty() ? this.makeObject() : this.pool.remove(this.pool.size() - 1);
   }

   public void release(T var1) {
      assert var1 != null;

      assert !this.pool.contains(var1);

      this.pool.add((T)var1);
   }

   public void release(List<T> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
         if (var1.get(var2) != null) {
            this.release((T)var1.get(var2));
         }
      }
   }

   public void release(Iterable<T> var1) {
      for (Object var3 : var1) {
         if (var3 != null) {
            this.release((T)var3);
         }
      }
   }

   public void release(T[] var1) {
      if (var1 != null) {
         for (int var2 = 0; var2 < var1.length; var2++) {
            if (var1[var2] != null) {
               this.release((T)var1[var2]);
            }
         }
      }
   }

   public void releaseAll(List<T> var1) {
      for (int var2 = 0; var2 < var1.size(); var2++) {
         if (var1.get(var2) != null) {
            this.release((T)var1.get(var2));
         }
      }
   }

   public void clear() {
      this.pool.clear();
   }

   protected T makeObject() {
      if (this.allocator != null) {
         return (T)this.allocator.allocate();
      } else {
         throw new UnsupportedOperationException(
            "Allocator is null. The ObjectPool is intended to be used with an allocator, or with the function makeObject overridden in a subclass."
         );
      }
   }

   public void forEach(Consumer<T> var1) {
      for (int var2 = 0; var2 < this.pool.size(); var2++) {
         var1.accept(this.pool.get(var2));
      }
   }
}
