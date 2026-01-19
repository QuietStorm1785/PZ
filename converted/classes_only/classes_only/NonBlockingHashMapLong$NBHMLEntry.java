package zombie.core.Collections;

class NonBlockingHashMapLong$NBHMLEntry extends AbstractEntry<Long, TypeV> {
   NonBlockingHashMapLong$NBHMLEntry(Long var1, TypeV var2, Object var3) {
      super(var2, var3);
      this.this$0 = var1;
   }

   public TypeV setValue(TypeV var1) {
      if (var1 == null) {
         throw new NullPointerException();
      } else {
         this._val = var1;
         return (TypeV)this.this$0.put((Long)this._key, var1);
      }
   }
}
