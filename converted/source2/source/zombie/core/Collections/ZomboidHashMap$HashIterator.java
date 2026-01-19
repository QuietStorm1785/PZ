package zombie.core.Collections;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;
import zombie.core.Collections.ZomboidHashMap.Entry;

abstract class ZomboidHashMap$HashIterator<E> implements Iterator<E> {
   Entry<K, V> next;
   int expectedModCount;
   int index;
   Entry<K, V> current;

   ZomboidHashMap$HashIterator(ZomboidHashMap var1) {
      this.this$0 = var1;
      this.expectedModCount = var1.modCount;
      if (var1.size > 0) {
         Entry[] var2 = var1.table;

         while (this.index < var2.length && (this.next = var2[this.index++]) == null) {
         }
      }
   }

   @Override
   public final boolean hasNext() {
      return this.next != null;
   }

   final Entry<K, V> nextEntry() {
      if (this.this$0.modCount != this.expectedModCount) {
         throw new ConcurrentModificationException();
      } else {
         Entry var1 = this.next;
         if (var1 == null) {
            throw new NoSuchElementException();
         } else {
            if ((this.next = var1.next) == null) {
               Entry[] var2 = this.this$0.table;

               while (this.index < var2.length && (this.next = var2[this.index++]) == null) {
               }
            }

            this.current = var1;
            return var1;
         }
      }
   }

   @Override
   public void remove() {
      if (this.current == null) {
         throw new IllegalStateException();
      } else if (this.this$0.modCount != this.expectedModCount) {
         throw new ConcurrentModificationException();
      } else {
         Object var1 = this.current.key;
         this.current = null;
         this.this$0.removeEntryForKey(var1);
         this.expectedModCount = this.this$0.modCount;
      }
   }
}
