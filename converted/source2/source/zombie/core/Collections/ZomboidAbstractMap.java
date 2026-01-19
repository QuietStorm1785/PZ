package zombie.core.Collections;

import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;
import zombie.core.Collections.ZomboidAbstractMap.1;
import zombie.core.Collections.ZomboidAbstractMap.2;

public abstract class ZomboidAbstractMap<K, V> implements Map<K, V> {
   transient volatile Set<K> keySet = null;
   transient volatile Collection<V> values = null;

   protected ZomboidAbstractMap() {
   }

   @Override
   public int size() {
      return this.entrySet().size();
   }

   @Override
   public boolean isEmpty() {
      return this.size() == 0;
   }

   @Override
   public boolean containsValue(Object var1) {
      Iterator var2 = this.entrySet().iterator();
      if (var1 == null) {
         while (var2.hasNext()) {
            Entry var4 = (Entry)var2.next();
            if (var4.getValue() == null) {
               return true;
            }
         }
      } else {
         while (var2.hasNext()) {
            Entry var3 = (Entry)var2.next();
            if (var1.equals(var3.getValue())) {
               return true;
            }
         }
      }

      return false;
   }

   @Override
   public boolean containsKey(Object var1) {
      Iterator var2 = this.entrySet().iterator();
      if (var1 == null) {
         while (var2.hasNext()) {
            Entry var4 = (Entry)var2.next();
            if (var4.getKey() == null) {
               return true;
            }
         }
      } else {
         while (var2.hasNext()) {
            Entry var3 = (Entry)var2.next();
            if (var1.equals(var3.getKey())) {
               return true;
            }
         }
      }

      return false;
   }

   @Override
   public V get(Object var1) {
      Iterator var2 = this.entrySet().iterator();
      if (var1 == null) {
         while (var2.hasNext()) {
            Entry var4 = (Entry)var2.next();
            if (var4.getKey() == null) {
               return (V)var4.getValue();
            }
         }
      } else {
         while (var2.hasNext()) {
            Entry var3 = (Entry)var2.next();
            if (var1.equals(var3.getKey())) {
               return (V)var3.getValue();
            }
         }
      }

      return null;
   }

   @Override
   public V put(K var1, V var2) {
      throw new UnsupportedOperationException();
   }

   @Override
   public V remove(Object var1) {
      Iterator var2 = this.entrySet().iterator();
      Entry var3 = null;
      if (var1 == null) {
         while (var3 == null && var2.hasNext()) {
            Entry var5 = (Entry)var2.next();
            if (var5.getKey() == null) {
               var3 = var5;
            }
         }
      } else {
         while (var3 == null && var2.hasNext()) {
            Entry var4 = (Entry)var2.next();
            if (var1.equals(var4.getKey())) {
               var3 = var4;
            }
         }
      }

      Object var6 = null;
      if (var3 != null) {
         var6 = var3.getValue();
         var2.remove();
      }

      return (V)var6;
   }

   @Override
   public void putAll(Map<? extends K, ? extends V> var1) {
      for (Entry var3 : var1.entrySet()) {
         this.put((K)var3.getKey(), (V)var3.getValue());
      }
   }

   @Override
   public void clear() {
      this.entrySet().clear();
   }

   @Override
   public Set<K> keySet() {
      if (this.keySet == null) {
         this.keySet = new 1(this);
      }

      return this.keySet;
   }

   @Override
   public Collection<V> values() {
      if (this.values == null) {
         this.values = new 2(this);
      }

      return this.values;
   }

   @Override
   public abstract Set<Entry<K, V>> entrySet();

   @Override
   public boolean equals(Object var1) {
      if (var1 == this) {
         return true;
      } else if (!(var1 instanceof Map var2)) {
         return false;
      } else if (var2.size() != this.size()) {
         return false;
      } else {
         try {
            for (Entry var4 : this.entrySet()) {
               Object var5 = var4.getKey();
               Object var6 = var4.getValue();
               if (var6 == null) {
                  if (var2.get(var5) != null || !var2.containsKey(var5)) {
                     return false;
                  }
               } else if (!var6.equals(var2.get(var5))) {
                  return false;
               }
            }

            return true;
         } catch (ClassCastException var7) {
            return false;
         } catch (NullPointerException var8) {
            return false;
         }
      }
   }

   @Override
   public int hashCode() {
      int var1 = 0;
      Iterator var2 = this.entrySet().iterator();

      while (var2.hasNext()) {
         var1 += ((Entry)var2.next()).hashCode();
      }

      return var1;
   }

   @Override
   public String toString() {
      Iterator var1 = this.entrySet().iterator();
      if (!var1.hasNext()) {
         return "{}";
      } else {
         StringBuilder var2 = new StringBuilder();
         var2.append('{');

         while (true) {
            Entry var3 = (Entry)var1.next();
            Object var4 = var3.getKey();
            Object var5 = var3.getValue();
            var2.append(var4 == this ? "(this Map)" : var4);
            var2.append('=');
            var2.append(var5 == this ? "(this Map)" : var5);
            if (!var1.hasNext()) {
               return var2.append('}').toString();
            }

            var2.append(", ");
         }
      }
   }

   @Override
   protected Object clone() throws CloneNotSupportedException {
      ZomboidAbstractMap var1 = (ZomboidAbstractMap)super.clone();
      var1.keySet = null;
      var1.values = null;
      return var1;
   }

   private static boolean eq(Object var0, Object var1) {
      return var0 == null ? var1 == null : var0.equals(var1);
   }
}
