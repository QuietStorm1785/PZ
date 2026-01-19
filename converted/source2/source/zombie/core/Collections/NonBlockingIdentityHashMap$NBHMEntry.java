package zombie.core.Collections;

class NonBlockingIdentityHashMap$NBHMEntry extends AbstractEntry<TypeK, TypeV> {
   NonBlockingIdentityHashMap$NBHMEntry(TypeK var1, TypeV var2, Object var3) {
      super(var2, var3);
      this.this$0 = var1;
   }

   public TypeV setValue(TypeV var1) {
      if (var1 == null) {
         throw new NullPointerException();
      } else {
         this._val = var1;
         return (TypeV)this.this$0.put(this._key, var1);
      }
   }
}
