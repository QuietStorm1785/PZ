package zombie.core.Collections;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.NoSuchElementException;
import zombie.core.Collections.NonBlockingHashtable.CHM;

class NonBlockingHashtable$SnapshotV implements Iterator<TypeV>, Enumeration<TypeV> {
   final Object[] _sskvs;
   private int _idx;
   private Object _nextK;
   private Object _prevK;
   private TypeV _nextV;
   private TypeV _prevV;

   public NonBlockingHashtable$SnapshotV(NonBlockingHashtable var1) {
      this.this$0 = var1;

      while (true) {
         Object[] var2 = var1._kvs;
         CHM var3 = NonBlockingHashtable.chm(var2);
         if (var3._newkvs == null) {
            this._sskvs = var2;
            this.next();
            return;
         }

         var3.help_copy_impl(var1, var2, true);
      }
   }

   int length() {
      return NonBlockingHashtable.len(this._sskvs);
   }

   Object key(int var1) {
      return NonBlockingHashtable.key(this._sskvs, var1);
   }

   @Override
   public boolean hasNext() {
      return this._nextV != null;
   }

   @Override
   public TypeV next() {
      if (this._idx != 0 && this._nextV == null) {
         throw new NoSuchElementException();
      } else {
         this._prevK = this._nextK;
         this._prevV = this._nextV;
         this._nextV = null;

         while (this._idx < this.length()) {
            this._nextK = this.key(this._idx++);
            if (this._nextK != null && this._nextK != NonBlockingHashtable.TOMBSTONE && (this._nextV = (TypeV)this.this$0.get(this._nextK)) != null) {
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
         NonBlockingHashtable.putIfMatch(this.this$0, this._sskvs, this._prevK, NonBlockingHashtable.TOMBSTONE, this._prevV);
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
