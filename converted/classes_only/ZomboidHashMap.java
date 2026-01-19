package zombie.core.Collections;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Stack;
import java.util.Map.Entry;
import zombie.core.Collections.ZomboidHashMap.EntryIterator;
import zombie.core.Collections.ZomboidHashMap.EntrySet;
import zombie.core.Collections.ZomboidHashMap.KeyIterator;
import zombie.core.Collections.ZomboidHashMap.KeySet;
import zombie.core.Collections.ZomboidHashMap.ValueIterator;
import zombie.core.Collections.ZomboidHashMap.Values;

public class ZomboidHashMap<K, V> extends ZomboidAbstractMap<K, V> implements Map<K, V>, Cloneable, Serializable {
   static final int DEFAULT_INITIAL_CAPACITY = 16;
   static final int MAXIMUM_CAPACITY = 1073741824;
   static final float DEFAULT_LOAD_FACTOR = 0.75F;
   transient zombie.core.Collections.ZomboidHashMap.Entry[] table;
   transient int size;
   int threshold;
   final float loadFactor;
   transient volatile int modCount;
   Stack<zombie.core.Collections.ZomboidHashMap.Entry<K, V>> entryStore = new Stack<>();
   private transient Set<Entry<K, V>> entrySet = null;
   private static final long serialVersionUID = 362498820763181265L;

   public ZomboidHashMap(int var1, float var2) {
      if (var1 < 0) {
         throw new IllegalArgumentException("Illegal initial capacity: " + var1);
      } else {
         if (var1 > 1073741824) {
            var1 = 1073741824;
         }

         if (!(var2 <= 0.0F) && !Float.isNaN(var2)) {
            byte var3 = 1;

            while (var3 < var1) {
               var3 <<= 1;
            }

            for (int var4 = 0; var4 < 100; var4++) {
               this.entryStore.add(new zombie.core.Collections.ZomboidHashMap.Entry(0, null, null, null));
            }

            this.loadFactor = var2;
            this.threshold = (int)(var3 * var2);
            this.table = new zombie.core.Collections.ZomboidHashMap.Entry[var3];
            this.init();
         } else {
            throw new IllegalArgumentException("Illegal load factor: " + var2);
         }
      }
   }

   public ZomboidHashMap(int var1) {
      this(var1, 0.75F);
   }

   public ZomboidHashMap() {
      this.loadFactor = 0.75F;
      this.threshold = 12;
      this.table = new zombie.core.Collections.ZomboidHashMap.Entry[16];
      this.init();
   }

   public ZomboidHashMap(Map<? extends K, ? extends V> var1) {
      this(Math.max((int)(var1.size() / 0.75F) + 1, 16), 0.75F);
      this.putAllForCreate(var1);
   }

   void init() {
   }

   static int hash(int var0) {
      var0 ^= var0 >>> 20 ^ var0 >>> 12;
      return var0 ^ var0 >>> 7 ^ var0 >>> 4;
   }

   static int indexFor(int var0, int var1) {
      return var0 & var1 - 1;
   }

   @Override
   public int size() {
      return this.size;
   }

   @Override
   public boolean isEmpty() {
      return this.size == 0;
   }

   @Override
   public V get(Object var1) {
      if (var1 == null) {
         return this.getForNullKey();
      } else {
         int var2 = hash(var1.hashCode());

         for (zombie.core.Collections.ZomboidHashMap.Entry var3 = this.table[indexFor(var2, this.table.length)]; var3 != null; var3 = var3.next) {
            if (var3.hash == var2) {
               Object var4 = var3.key;
               if (var3.key == var1 || var1.equals(var4)) {
                  return (V)var3.value;
               }
            }
         }

         return null;
      }
   }

   private V getForNullKey() {
      for (zombie.core.Collections.ZomboidHashMap.Entry var1 = this.table[0]; var1 != null; var1 = var1.next) {
         if (var1.key == null) {
            return (V)var1.value;
         }
      }

      return null;
   }

   @Override
   public boolean containsKey(Object var1) {
      return this.getEntry(var1) != null;
   }

   final zombie.core.Collections.ZomboidHashMap.Entry<K, V> getEntry(Object var1) {
      int var2 = var1 == null ? 0 : hash(var1.hashCode());

      for (zombie.core.Collections.ZomboidHashMap.Entry var3 = this.table[indexFor(var2, this.table.length)]; var3 != null; var3 = var3.next) {
         if (var3.hash == var2) {
            Object var4 = var3.key;
            if (var3.key == var1 || var1 != null && var1.equals(var4)) {
               return var3;
            }
         }
      }

      return null;
   }

   @Override
   public V put(K var1, V var2) {
      if (var1 == null) {
         return this.putForNullKey((V)var2);
      } else {
         int var3 = hash(var1.hashCode());
         int var4 = indexFor(var3, this.table.length);

         for (zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4]; var5 != null; var5 = var5.next) {
            if (var5.hash == var3) {
               Object var6 = var5.key;
               if (var5.key == var1 || var1.equals(var6)) {
                  Object var7 = var5.value;
                  var5.value = var2;
                  var5.recordAccess(this);
                  return (V)var7;
               }
            }
         }

         this.modCount++;
         this.addEntry(var3, (K)var1, (V)var2, var4);
         return null;
      }
   }

   private V putForNullKey(V var1) {
      for (zombie.core.Collections.ZomboidHashMap.Entry var2 = this.table[0]; var2 != null; var2 = var2.next) {
         if (var2.key == null) {
            Object var3 = var2.value;
            var2.value = var1;
            var2.recordAccess(this);
            return (V)var3;
         }
      }

      this.modCount++;
      this.addEntry(0, null, (V)var1, 0);
      return null;
   }

   private void putForCreate(K var1, V var2) {
      int var3 = var1 == null ? 0 : hash(var1.hashCode());
      int var4 = indexFor(var3, this.table.length);

      for (zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4]; var5 != null; var5 = var5.next) {
         if (var5.hash == var3) {
            Object var6 = var5.key;
            if (var5.key == var1 || var1 != null && var1.equals(var6)) {
               var5.value = var2;
               return;
            }
         }
      }

      this.createEntry(var3, (K)var1, (V)var2, var4);
   }

   private void putAllForCreate(Map<? extends K, ? extends V> var1) {
      for (Entry var3 : var1.entrySet()) {
         this.putForCreate((K)var3.getKey(), (V)var3.getValue());
      }
   }

   void resize(int var1) {
      zombie.core.Collections.ZomboidHashMap.Entry[] var2 = this.table;
      int var3 = var2.length;
      if (var3 == 1073741824) {
         this.threshold = Integer.MAX_VALUE;
      } else {
         zombie.core.Collections.ZomboidHashMap.Entry[] var4 = new zombie.core.Collections.ZomboidHashMap.Entry[var1];
         this.transfer(var4);
         this.table = var4;
         this.threshold = (int)(var1 * this.loadFactor);
      }
   }

   void transfer(zombie.core.Collections.ZomboidHashMap.Entry[] var1) {
      zombie.core.Collections.ZomboidHashMap.Entry[] var2 = this.table;
      int var3 = var1.length;

      for (int var4 = 0; var4 < var2.length; var4++) {
         zombie.core.Collections.ZomboidHashMap.Entry var5 = var2[var4];
         if (var5 != null) {
            var2[var4] = null;

            while (true) {
               zombie.core.Collections.ZomboidHashMap.Entry var6 = var5.next;
               int var7 = indexFor(var5.hash, var3);
               var5.next = var1[var7];
               var1[var7] = var5;
               var5 = var6;
               if (var6 == null) {
                  break;
               }
            }
         }
      }
   }

   @Override
   public void putAll(Map<? extends K, ? extends V> var1) {
      int var2 = var1.size();
      if (var2 != 0) {
         if (var2 > this.threshold) {
            int var3 = (int)(var2 / this.loadFactor + 1.0F);
            if (var3 > 1073741824) {
               var3 = 1073741824;
            }

            int var4 = this.table.length;

            while (var4 < var3) {
               var4 <<= 1;
            }

            if (var4 > this.table.length) {
               this.resize(var4);
            }
         }

         for (Entry var6 : var1.entrySet()) {
            this.put((K)var6.getKey(), (V)var6.getValue());
         }
      }
   }

   @Override
   public V remove(Object var1) {
      zombie.core.Collections.ZomboidHashMap.Entry var2 = this.removeEntryForKey(var1);
      return (V)(var2 == null ? null : var2.value);
   }

   final zombie.core.Collections.ZomboidHashMap.Entry<K, V> removeEntryForKey(Object var1) {
      int var2 = var1 == null ? 0 : hash(var1.hashCode());
      int var3 = indexFor(var2, this.table.length);
      zombie.core.Collections.ZomboidHashMap.Entry var4 = this.table[var3];
      zombie.core.Collections.ZomboidHashMap.Entry var5 = var4;

      while (var5 != null) {
         zombie.core.Collections.ZomboidHashMap.Entry var6 = var5.next;
         if (var5.hash == var2) {
            Object var7 = var5.key;
            if (var5.key == var1 || var1 != null && var1.equals(var7)) {
               this.modCount++;
               this.size--;
               if (var4 == var5) {
                  this.table[var3] = var6;
               } else {
                  var4.next = var6;
               }

               var5.recordRemoval(this);
               var5.value = null;
               var5.next = null;
               this.entryStore.push(var5);
               return var5;
            }
         }

         var4 = var5;
         var5 = var6;
      }

      return var5;
   }

   final zombie.core.Collections.ZomboidHashMap.Entry<K, V> removeMapping(Object var1) {
      if (!(var1 instanceof Entry var2)) {
         return null;
      } else {
         Object var3 = var2.getKey();
         int var4 = var3 == null ? 0 : hash(var3.hashCode());
         int var5 = indexFor(var4, this.table.length);
         zombie.core.Collections.ZomboidHashMap.Entry var6 = this.table[var5];
         zombie.core.Collections.ZomboidHashMap.Entry var7 = var6;

         while (var7 != null) {
            zombie.core.Collections.ZomboidHashMap.Entry var8 = var7.next;
            if (var7.hash == var4 && var7.equals(var2)) {
               this.modCount++;
               this.size--;
               if (var6 == var7) {
                  this.table[var5] = var8;
               } else {
                  var6.next = var8;
               }

               var7.recordRemoval(this);
               var7.value = null;
               var7.next = null;
               this.entryStore.push(var7);
               return var7;
            }

            var6 = var7;
            var7 = var8;
         }

         return var7;
      }
   }

   @Override
   public void clear() {
      this.modCount++;
      zombie.core.Collections.ZomboidHashMap.Entry[] var1 = this.table;

      for (int var2 = 0; var2 < var1.length; var2++) {
         if (var1[var2] != null) {
            var1[var2].value = null;
            var1[var2].next = null;
            this.entryStore.push(var1[var2]);
         }

         var1[var2] = null;
      }

      this.size = 0;
   }

   @Override
   public boolean containsValue(Object var1) {
      if (var1 == null) {
         return this.containsNullValue();
      } else {
         zombie.core.Collections.ZomboidHashMap.Entry[] var2 = this.table;

         for (int var3 = 0; var3 < var2.length; var3++) {
            for (zombie.core.Collections.ZomboidHashMap.Entry var4 = var2[var3]; var4 != null; var4 = var4.next) {
               if (var1.equals(var4.value)) {
                  return true;
               }
            }
         }

         return false;
      }
   }

   private boolean containsNullValue() {
      zombie.core.Collections.ZomboidHashMap.Entry[] var1 = this.table;

      for (int var2 = 0; var2 < var1.length; var2++) {
         for (zombie.core.Collections.ZomboidHashMap.Entry var3 = var1[var2]; var3 != null; var3 = var3.next) {
            if (var3.value == null) {
               return true;
            }
         }
      }

      return false;
   }

   @Override
   public Object clone() {
      ZomboidHashMap var1 = null;

      try {
         var1 = (ZomboidHashMap)super.clone();
      } catch (CloneNotSupportedException var3) {
      }

      var1.table = new zombie.core.Collections.ZomboidHashMap.Entry[this.table.length];
      var1.entrySet = null;
      var1.modCount = 0;
      var1.size = 0;
      var1.init();
      var1.putAllForCreate(this);
      return var1;
   }

   void addEntry(int var1, K var2, V var3, int var4) {
      zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4];
      if (this.entryStore.isEmpty()) {
         for (int var6 = 0; var6 < 100; var6++) {
            this.entryStore.add(new zombie.core.Collections.ZomboidHashMap.Entry(0, null, null, null));
         }
      }

      zombie.core.Collections.ZomboidHashMap.Entry var7 = this.entryStore.pop();
      var7.hash = var1;
      var7.key = var2;
      var7.value = var3;
      var7.next = var5;
      this.table[var4] = var7;
      if (this.size++ >= this.threshold) {
         this.resize(2 * this.table.length);
      }
   }

   void createEntry(int var1, K var2, V var3, int var4) {
      zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4];
      if (this.entryStore.isEmpty()) {
         for (int var6 = 0; var6 < 100; var6++) {
            this.entryStore.add(new zombie.core.Collections.ZomboidHashMap.Entry(0, null, null, null));
         }
      }

      zombie.core.Collections.ZomboidHashMap.Entry var7 = this.entryStore.pop();
      var7.hash = var1;
      var7.key = var2;
      var7.value = var3;
      var7.next = var5;
      this.table[var4] = var7;
      this.size++;
   }

   Iterator<K> newKeyIterator() {
      return new KeyIterator(this);
   }

   Iterator<V> newValueIterator() {
      return new ValueIterator(this);
   }

   Iterator<Entry<K, V>> newEntryIterator() {
      return new EntryIterator(this);
   }

   @Override
   public Set<K> keySet() {
      Set var1 = this.keySet;
      return var1 != null ? var1 : (this.keySet = new KeySet(this));
   }

   @Override
   public Collection<V> values() {
      Collection var1 = this.values;
      return var1 != null ? var1 : (this.values = new Values(this));
   }

   @Override
   public Set<Entry<K, V>> entrySet() {
      return this.entrySet0();
   }

   private Set<Entry<K, V>> entrySet0() {
      Set var1 = this.entrySet;
      return var1 != null ? var1 : (this.entrySet = new EntrySet(this));
   }

   private void writeObject(ObjectOutputStream var1) throws IOException {
      Iterator var2 = this.size > 0 ? this.entrySet0().iterator() : null;
      var1.defaultWriteObject();
      var1.writeInt(this.table.length);
      var1.writeInt(this.size);
      if (var2 != null) {
         while (var2.hasNext()) {
            Entry var3 = (Entry)var2.next();
            var1.writeObject(var3.getKey());
            var1.writeObject(var3.getValue());
         }
      }
   }

   private void readObject(ObjectInputStream var1) throws IOException, ClassNotFoundException {
      var1.defaultReadObject();
      int var2 = var1.readInt();
      this.table = new zombie.core.Collections.ZomboidHashMap.Entry[var2];
      this.init();
      int var3 = var1.readInt();

      for (int var4 = 0; var4 < var3; var4++) {
         Object var5 = var1.readObject();
         Object var6 = var1.readObject();
         this.putForCreate((K)var5, (V)var6);
      }
   }

   int capacity() {
      return this.table.length;
   }

   float loadFactor() {
      return this.loadFactor;
   }
}
