package zombie.core.Collections;

import java.util.Map.Entry;

class ZomboidHashMap$Entry<K, V> implements Entry<K, V> {
   K key;
   V value;
   ZomboidHashMap$Entry<K, V> next;
   int hash;

   ZomboidHashMap$Entry(int var1, K var2, V var3, ZomboidHashMap$Entry<K, V> var4) {
      this.value = (V)var3;
      this.next = var4;
      this.key = (K)var2;
      this.hash = var1;
   }

   @Override
   public final K getKey() {
      return this.key;
   }

   @Override
   public final V getValue() {
      return this.value;
   }

   @Override
   public final V setValue(V var1) {
      Object var2 = this.value;
      this.value = (V)var1;
      return (V)var2;
   }

   @Override
   public final boolean equals(Object var1) {
      if (!(var1 instanceof Entry var2)) {
         return false;
      } else {
         Object var3 = this.getKey();
         Object var4 = var2.getKey();
         if (var3 == var4 || var3 != null && var3.equals(var4)) {
            Object var5 = this.getValue();
            Object var6 = var2.getValue();
            if (var5 == var6 || var5 != null && var5.equals(var6)) {
               return true;
            }
         }

         return false;
      }
   }

   @Override
   public final int hashCode() {
      return (this.key == null ? 0 : this.key.hashCode()) ^ (this.value == null ? 0 : this.value.hashCode());
   }

   @Override
   public final String toString() {
      return this.getKey() + "=" + this.getValue();
   }

   void recordAccess(ZomboidHashMap<K, V> var1) {
   }

   void recordRemoval(ZomboidHashMap<K, V> var1) {
   }
}
