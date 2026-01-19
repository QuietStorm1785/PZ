package zombie.core.utils;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import zombie.core.utils.FibonacciHeap.Entry;
import zombie.iso.IsoGridSquare;

public final class FibonacciHeap<T> {
   private Entry<T> mMin = null;
   private int mSize = 0;
   List<Entry<T>> treeTable = new ArrayList<>(300);
   List<Entry<T>> toVisit = new ArrayList<>(300);

   public void empty() {
      this.mMin = null;
      this.mSize = 0;
   }

   public Entry<T> enqueue(T var1, double var2) {
      this.checkPriority(var2);
      Entry var4 = new Entry(var1, var2);
      this.mMin = mergeLists(this.mMin, var4);
      this.mSize++;
      return var4;
   }

   public Entry<T> min() {
      if (this.isEmpty()) {
         throw new NoSuchElementException("Heap is empty.");
      } else {
         return this.mMin;
      }
   }

   public boolean isEmpty() {
      return this.mMin == null;
   }

   public int size() {
      return this.mSize;
   }

   public static <T> FibonacciHeap<T> merge(FibonacciHeap<T> var0, FibonacciHeap<T> var1) {
      FibonacciHeap var2 = new FibonacciHeap();
      var2.mMin = mergeLists(var0.mMin, var1.mMin);
      var2.mSize = var0.mSize + var1.mSize;
      var0.mSize = var1.mSize = 0;
      var0.mMin = null;
      var1.mMin = null;
      return var2;
   }

   public Entry<T> dequeueMin() {
      if (this.isEmpty()) {
         throw new NoSuchElementException("Heap is empty.");
      } else {
         this.mSize--;
         Entry var1 = this.mMin;
         if (this.mMin.mNext == this.mMin) {
            this.mMin = null;
         } else {
            this.mMin.mPrev.mNext = this.mMin.mNext;
            this.mMin.mNext.mPrev = this.mMin.mPrev;
            this.mMin = this.mMin.mNext;
         }

         if (var1.mChild != null) {
            Entry var2 = var1.mChild;

            do {
               var2.mParent = null;
               var2 = var2.mNext;
            } while (var2 != var1.mChild);
         }

         this.mMin = mergeLists(this.mMin, var1.mChild);
         if (this.mMin == null) {
            return var1;
         } else {
            this.treeTable.clear();
            this.toVisit.clear();

            for (Entry var7 = this.mMin; this.toVisit.isEmpty() || this.toVisit.get(0) != var7; var7 = var7.mNext) {
               this.toVisit.add(var7);
            }

            label57:
            for (Entry var3 : this.toVisit) {
               while (true) {
                  while (var3.mDegree < this.treeTable.size()) {
                     if (this.treeTable.get(var3.mDegree) == null) {
                        this.treeTable.set(var3.mDegree, var3);
                        if (var3.mPriority <= this.mMin.mPriority) {
                           this.mMin = var3;
                        }
                        continue label57;
                     }

                     Entry var4 = this.treeTable.get(var3.mDegree);
                     this.treeTable.set(var3.mDegree, null);
                     Entry var5 = var4.mPriority < var3.mPriority ? var4 : var3;
                     Entry var6 = var4.mPriority < var3.mPriority ? var3 : var4;
                     var6.mNext.mPrev = var6.mPrev;
                     var6.mPrev.mNext = var6.mNext;
                     var6.mNext = var6.mPrev = var6;
                     var5.mChild = mergeLists(var5.mChild, var6);
                     var6.mParent = var5;
                     var6.mIsMarked = false;
                     var5.mDegree++;
                     var3 = var5;
                  }

                  this.treeTable.add(null);
               }
            }

            return var1;
         }
      }
   }

   public void decreaseKey(Entry<T> var1, double var2) {
      this.checkPriority(var2);
      if (var2 > var1.mPriority) {
         throw new IllegalArgumentException("New priority exceeds old.");
      } else {
         this.decreaseKeyUnchecked(var1, var2);
      }
   }

   public void delete(Entry<T> var1) {
      this.decreaseKeyUnchecked(var1, Double.NEGATIVE_INFINITY);
      this.dequeueMin();
   }

   public void delete(int var1, IsoGridSquare var2) {
   }

   private void checkPriority(double var1) {
      if (Double.isNaN(var1)) {
         throw new IllegalArgumentException(var1 + " is invalid.");
      }
   }

   private static <T> Entry<T> mergeLists(Entry<T> var0, Entry<T> var1) {
      if (var0 == null && var1 == null) {
         return null;
      } else if (var0 != null && var1 == null) {
         return var0;
      } else if (var0 == null && var1 != null) {
         return var1;
      } else {
         Entry var2 = var0.mNext;
         var0.mNext = var1.mNext;
         var0.mNext.mPrev = var0;
         var1.mNext = var2;
         var1.mNext.mPrev = var1;
         return var0.mPriority < var1.mPriority ? var0 : var1;
      }
   }

   private void decreaseKeyUnchecked(Entry<T> var1, double var2) {
      var1.mPriority = var2;
      if (var1.mParent != null && var1.mPriority <= var1.mParent.mPriority) {
         this.cutNode(var1);
      }

      if (var1.mPriority <= this.mMin.mPriority) {
         this.mMin = var1;
      }
   }

   private void decreaseKeyUncheckedNode(Entry<IsoGridSquare> var1, double var2) {
      var1.mPriority = var2;
      if (var1.mParent != null && var1.mPriority <= var1.mParent.mPriority) {
         this.cutNodeNode(var1);
      }

      if (var1.mPriority <= this.mMin.mPriority) {
         this.mMin = var1;
      }
   }

   private void cutNode(Entry<T> var1) {
      var1.mIsMarked = false;
      if (var1.mParent != null) {
         if (var1.mNext != var1) {
            var1.mNext.mPrev = var1.mPrev;
            var1.mPrev.mNext = var1.mNext;
         }

         if (var1.mParent.mChild == var1) {
            if (var1.mNext != var1) {
               var1.mParent.mChild = var1.mNext;
            } else {
               var1.mParent.mChild = null;
            }
         }

         var1.mParent.mDegree--;
         var1.mPrev = var1.mNext = var1;
         this.mMin = mergeLists(this.mMin, var1);
         if (var1.mParent.mIsMarked) {
            this.cutNode(var1.mParent);
         } else {
            var1.mParent.mIsMarked = true;
         }

         var1.mParent = null;
      }
   }

   private void cutNodeNode(Entry<IsoGridSquare> var1) {
      var1.mIsMarked = false;
      if (var1.mParent != null) {
         if (var1.mNext != var1) {
            var1.mNext.mPrev = var1.mPrev;
            var1.mPrev.mNext = var1.mNext;
         }

         if (var1.mParent.mChild == var1) {
            if (var1.mNext != var1) {
               var1.mParent.mChild = var1.mNext;
            } else {
               var1.mParent.mChild = null;
            }
         }

         var1.mParent.mDegree--;
         var1.mPrev = var1.mNext = var1;
         this.mMin = mergeLists(this.mMin, var1);
         if (var1.mParent.mIsMarked) {
            this.cutNode(var1.mParent);
         } else {
            var1.mParent.mIsMarked = true;
         }

         var1.mParent = null;
      }
   }
}
