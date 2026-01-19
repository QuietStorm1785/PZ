package zombie.core.Collections;

final class ZomboidHashMap$KeyIterator extends ZomboidHashMap<K, V>.HashIterator<K> {
   private ZomboidHashMap$KeyIterator(ZomboidHashMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public K next() {
      return (K)this.nextEntry().getKey();
   }
}
