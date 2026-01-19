package zombie.core.Collections;

import java.io.Serializable;
import java.util.Map.Entry;

public class ZomboidAbstractMap$SimpleImmutableEntry<K, V> implements Entry<K, V>, Serializable {
   private static final long serialVersionUID = 7138329143949025153L;
   private final K key;
   private final V value;

   public ZomboidAbstractMap$SimpleImmutableEntry(K var1, V var2) {
      this.key = (K)var1;
      this.value = (V)var2;
   }

   public ZomboidAbstractMap$SimpleImmutableEntry(Entry<? extends K, ? extends V> var1) {
      this.key = (K)var1.getKey();
      this.value = (V)var1.getValue();
   }

   @Override
   public K getKey() {
      return this.key;
   }

   @Override
   public V getValue() {
      return this.value;
   }

   @Override
   public V setValue(V var1) {
      throw new UnsupportedOperationException();
   }

   @Override
   public boolean equals(Object var1) {
      return !(var1 instanceof Entry var2) ? false : ZomboidAbstractMap.eq(this.key, var2.getKey()) && ZomboidAbstractMap.eq(this.value, var2.getValue());
   }

   @Override
   public int hashCode() {
      return (this.key == null ? 0 : this.key.hashCode()) ^ (this.value == null ? 0 : this.value.hashCode());
   }

   @Override
   public String toString() {
      return this.key + "=" + this.value;
   }
}
