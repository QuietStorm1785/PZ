package zombie.core.Collections;

final class ZomboidHashMap$ValueIterator extends ZomboidHashMap<K, V>.HashIterator<V> {
   private ZomboidHashMap$ValueIterator(ZomboidHashMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public V next() {
      return (V)this.nextEntry().value;
   }
}
