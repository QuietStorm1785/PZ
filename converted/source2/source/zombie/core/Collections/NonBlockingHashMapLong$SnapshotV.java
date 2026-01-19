package zombie.core.Collections;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.NoSuchElementException;
import zombie.core.Collections.NonBlockingHashMapLong.CHM;

class NonBlockingHashMapLong$SnapshotV implements Iterator<TypeV>, Enumeration<TypeV> {
   final CHM _sschm;
   private int _idx;
   private long _nextK;
   private long _prevK;
   private TypeV _nextV;
   private TypeV _prevV;

   public NonBlockingHashMapLong$SnapshotV(NonBlockingHashMapLong var1) {
      this.this$0 = var1;

      while (true) {
         CHM var2 = var1._chm;
         if (var2._newchm == null) {
            this._sschm = var2;
            this._idx = -1;
            this.next();
            return;
         }

         var2.help_copy_impl(true);
      }
   }

   int length() {
      return this._sschm._keys.length;
   }

   long key(int var1) {
      return this._sschm._keys[var1];
   }

   @Override
   public boolean hasNext() {
      return this._nextV != null;
   }

   @Override
   public TypeV next() {
      if (this._idx != -1 && this._nextV == null) {
         throw new NoSuchElementException();
      } else {
         this._prevK = this._nextK;
         this._prevV = this._nextV;
         this._nextV = null;
         if (this._idx == -1) {
            this._idx = 0;
            this._nextK = 0L;
            if ((this._nextV = (TypeV)this.this$0.get(this._nextK)) != null) {
               return this._prevV;
            }
         }

         while (this._idx < this.length()) {
            this._nextK = this.key(this._idx++);
            if (this._nextK != 0L && (this._nextV = (TypeV)this.this$0.get(this._nextK)) != null) {
               break;
            }
         }

         return this._prevV;
      }
   }

   @Override
   public void remove() {
      if (this._prevV == null) {
         throw new IllegalStateException();
      } else {
         this._sschm.putIfMatch(this._prevK, NonBlockingHashMapLong.TOMBSTONE, this._prevV);
         this._prevV = null;
      }
   }

   @Override
   public TypeV nextElement() {
      return (TypeV)this.next();
   }

   @Override
   public boolean hasMoreElements() {
      return this.hasNext();
   }
}
