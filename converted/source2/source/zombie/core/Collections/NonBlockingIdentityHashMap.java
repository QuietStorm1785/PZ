package zombie.core.Collections;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.lang.reflect.Field;
import java.util.AbstractMap;
import java.util.Collection;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentMap;
import sun.misc.Unsafe;
import zombie.core.Collections.NonBlockingIdentityHashMap.1;
import zombie.core.Collections.NonBlockingIdentityHashMap.2;
import zombie.core.Collections.NonBlockingIdentityHashMap.3;
import zombie.core.Collections.NonBlockingIdentityHashMap.CHM;
import zombie.core.Collections.NonBlockingIdentityHashMap.Prime;
import zombie.core.Collections.NonBlockingIdentityHashMap.SnapshotK;
import zombie.core.Collections.NonBlockingIdentityHashMap.SnapshotV;

public class NonBlockingIdentityHashMap<TypeK, TypeV> extends AbstractMap<TypeK, TypeV> implements ConcurrentMap<TypeK, TypeV>, Cloneable, Serializable {
   private static final long serialVersionUID = 1234123412341234123L;
   private static final int REPROBE_LIMIT = 10;
   private static final Unsafe _unsafe = UtilUnsafe.getUnsafe();
   private static final int _Obase = _unsafe.arrayBaseOffset(Object[].class);
   private static final int _Oscale = _unsafe.arrayIndexScale(Object[].class);
   private static final long _kvs_offset;
   private transient Object[] _kvs;
   private transient long _last_resize_milli;
   private static final int MIN_SIZE_LOG = 3;
   private static final int MIN_SIZE = 8;
   private static final Object NO_MATCH_OLD;
   private static final Object MATCH_ANY;
   private static final Object TOMBSTONE;
   private static final Prime TOMBPRIME;
   private transient Counter _reprobes = new Counter();

   private static long rawIndex(Object[] var0, int var1) {
      assert var1 >= 0 && var1 < var0.length;

      return _Obase + var1 * _Oscale;
   }

   private final boolean CAS_kvs(Object[] var1, Object[] var2) {
      return _unsafe.compareAndSwapObject(this, _kvs_offset, var1, var2);
   }

   private static final int hash(Object var0) {
      int var1 = System.identityHashCode(var0);
      var1 ^= var1 >>> 20 ^ var1 >>> 12;
      return var1 ^ var1 >>> 7 ^ var1 >>> 4;
   }

   private static final CHM chm(Object[] var0) {
      return (CHM)var0[0];
   }

   private static final int[] hashes(Object[] var0) {
      return (int[])var0[1];
   }

   private static final int len(Object[] var0) {
      return var0.length - 2 >> 1;
   }

   private static final Object key(Object[] var0, int var1) {
      return var0[(var1 << 1) + 2];
   }

   private static final Object val(Object[] var0, int var1) {
      return var0[(var1 << 1) + 3];
   }

   private static final boolean CAS_key(Object[] var0, int var1, Object var2, Object var3) {
      return _unsafe.compareAndSwapObject(var0, rawIndex(var0, (var1 << 1) + 2), var2, var3);
   }

   private static final boolean CAS_val(Object[] var0, int var1, Object var2, Object var3) {
      return _unsafe.compareAndSwapObject(var0, rawIndex(var0, (var1 << 1) + 3), var2, var3);
   }

   public final void print() {
      System.out.println("=========");
      this.print2(this._kvs);
      System.out.println("=========");
   }

   private final void print(Object[] var1) {
      for (int var2 = 0; var2 < len(var1); var2++) {
         Object var3 = key(var1, var2);
         if (var3 != null) {
            String var4 = var3 == TOMBSTONE ? "XXX" : var3.toString();
            Object var5 = val(var1, var2);
            Object var6 = Prime.unbox(var5);
            String var7 = var5 == var6 ? "" : "prime_";
            String var8 = var6 == TOMBSTONE ? "tombstone" : var6.toString();
            System.out.println(var2 + " (" + var4 + "," + var7 + var8 + ")");
         }
      }

      Object[] var9 = chm(var1)._newkvs;
      if (var9 != null) {
         System.out.println("----");
         this.print(var9);
      }
   }

   private final void print2(Object[] var1) {
      for (int var2 = 0; var2 < len(var1); var2++) {
         Object var3 = key(var1, var2);
         Object var4 = val(var1, var2);
         Object var5 = Prime.unbox(var4);
         if (var3 != null && var3 != TOMBSTONE && var4 != null && var5 != TOMBSTONE) {
            String var6 = var4 == var5 ? "" : "prime_";
            System.out.println(var2 + " (" + var3 + "," + var6 + var4 + ")");
         }
      }

      Object[] var7 = chm(var1)._newkvs;
      if (var7 != null) {
         System.out.println("----");
         this.print2(var7);
      }
   }

   public long reprobes() {
      long var1 = this._reprobes.get();
      this._reprobes = new Counter();
      return var1;
   }

   private static final int reprobe_limit(int var0) {
      return 10 + (var0 >> 2);
   }

   public NonBlockingIdentityHashMap() {
      this(8);
   }

   public NonBlockingIdentityHashMap(int var1) {
      this.initialize(var1);
   }

   private final void initialize(int var1) {
      if (var1 < 0) {
         throw new IllegalArgumentException();
      } else {
         if (var1 > 1048576) {
            var1 = 1048576;
         }

         int var2 = 3;

         while (1 << var2 < var1 << 2) {
            var2++;
         }

         this._kvs = new Object[(1 << var2 << 1) + 2];
         this._kvs[0] = new CHM(new Counter());
         this._kvs[1] = new int[1 << var2];
         this._last_resize_milli = System.currentTimeMillis();
      }
   }

   protected final void initialize() {
      this.initialize(8);
   }

   @Override
   public int size() {
      return chm(this._kvs).size();
   }

   @Override
   public boolean isEmpty() {
      return this.size() == 0;
   }

   @Override
   public boolean containsKey(Object var1) {
      return this.get(var1) != null;
   }

   public boolean contains(Object var1) {
      return this.containsValue(var1);
   }

   @Override
   public TypeV put(TypeK var1, TypeV var2) {
      return this.putIfMatch(var1, var2, NO_MATCH_OLD);
   }

   @Override
   public TypeV putIfAbsent(TypeK var1, TypeV var2) {
      return this.putIfMatch(var1, var2, TOMBSTONE);
   }

   @Override
   public TypeV remove(Object var1) {
      return this.putIfMatch(var1, TOMBSTONE, NO_MATCH_OLD);
   }

   @Override
   public boolean remove(Object var1, Object var2) {
      return this.putIfMatch(var1, TOMBSTONE, var2) == var2;
   }

   @Override
   public TypeV replace(TypeK var1, TypeV var2) {
      return this.putIfMatch(var1, var2, MATCH_ANY);
   }

   @Override
   public boolean replace(TypeK var1, TypeV var2, TypeV var3) {
      return this.putIfMatch(var1, var3, var2) == var2;
   }

   private final TypeV putIfMatch(Object var1, Object var2, Object var3) {
      if (var3 != null && var2 != null) {
         Object var4 = putIfMatch(this, this._kvs, var1, var2, var3);

         assert !(var4 instanceof Prime);

         assert var4 != null;

         return (TypeV)(var4 == TOMBSTONE ? null : var4);
      } else {
         throw new NullPointerException();
      }
   }

   @Override
   public void putAll(Map<? extends TypeK, ? extends TypeV> var1) {
      for (Entry var3 : var1.entrySet()) {
         this.put((TypeK)var3.getKey(), (TypeV)var3.getValue());
      }
   }

   @Override
   public void clear() {
      Object[] var1 = (new NonBlockingIdentityHashMap(8))._kvs;

      while (!this.CAS_kvs(this._kvs, var1)) {
      }
   }

   @Override
   public boolean containsValue(Object var1) {
      if (var1 == null) {
         throw new NullPointerException();
      } else {
         for (Object var3 : this.values()) {
            if (var3 == var1 || var3.equals(var1)) {
               return true;
            }
         }

         return false;
      }
   }

   protected void rehash() {
   }

   @Override
   public Object clone() {
      try {
         NonBlockingIdentityHashMap var1 = (NonBlockingIdentityHashMap)super.clone();
         var1.clear();

         for (Object var3 : this.keySet()) {
            Object var4 = this.get(var3);
            var1.put(var3, var4);
         }

         return var1;
      } catch (CloneNotSupportedException var5) {
         throw new InternalError();
      }
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
   public TypeV get(Object var1) {
      int var2 = hash(var1);
      Object var3 = get_impl(this, this._kvs, var1, var2);

      assert !(var3 instanceof Prime);

      return (TypeV)var3;
   }

   private static final Object get_impl(NonBlockingIdentityHashMap var0, Object[] var1, Object var2, int var3) {
      int var4 = len(var1);
      CHM var5 = chm(var1);
      int var6 = var3 & var4 - 1;
      int var7 = 0;

      while (true) {
         Object var8 = key(var1, var6);
         Object var9 = val(var1, var6);
         if (var8 == null) {
            return null;
         }

         Object[] var10 = var5._newkvs;
         if (var8 == var2) {
            if (!(var9 instanceof Prime)) {
               return var9 == TOMBSTONE ? null : var9;
            }

            return get_impl(var0, var5.copy_slot_and_check(var0, var1, var6, var2), var2, var3);
         }

         if (++var7 >= reprobe_limit(var4) || var2 == TOMBSTONE) {
            return var10 == null ? null : get_impl(var0, var0.help_copy(var10), var2, var3);
         }

         var6 = var6 + 1 & var4 - 1;
      }
   }

   private static final Object putIfMatch(NonBlockingIdentityHashMap var0, Object[] var1, Object var2, Object var3, Object var4) {
      assert var3 != null;

      assert !(var3 instanceof Prime);

      assert !(var4 instanceof Prime);

      int var5 = hash(var2);
      int var6 = len(var1);
      CHM var7 = chm(var1);
      int var8 = var5 & var6 - 1;
      int var9 = 0;
      Object var10 = null;
      Object var11 = null;
      Object[] var12 = null;

      while (true) {
         var11 = val(var1, var8);
         var10 = key(var1, var8);
         if (var10 == null) {
            if (var3 == TOMBSTONE) {
               return var3;
            }

            if (CAS_key(var1, var8, null, var2)) {
               var7._slots.add(1L);
               break;
            }

            var10 = key(var1, var8);

            assert var10 != null;
         }

         var12 = var7._newkvs;
         if (var10 != var2) {
            if (++var9 < reprobe_limit(var6) && var2 != TOMBSTONE) {
               var8 = var8 + 1 & var6 - 1;
               continue;
            }

            var12 = var7.resize(var0, var1);
            if (var4 != null) {
               var0.help_copy(var12);
            }

            return putIfMatch(var0, var12, var2, var3, var4);
         }
         break;
      }

      if (var3 == var11) {
         return var11;
      } else {
         if (var12 == null && (var11 == null && var7.tableFull(var9, var6) || var11 instanceof Prime)) {
            var12 = var7.resize(var0, var1);
         }

         if (var12 != null) {
            return putIfMatch(var0, var7.copy_slot_and_check(var0, var1, var8, var4), var2, var3, var4);
         } else {
            while ($assertionsDisabled || !(var11 instanceof Prime)) {
               if (var4 != NO_MATCH_OLD
                  && var11 != var4
                  && (var4 != MATCH_ANY || var11 == TOMBSTONE || var11 == null)
                  && (var11 != null || var4 != TOMBSTONE)
                  && (var4 == null || !var4.equals(var11))) {
                  return var11;
               }

               if (CAS_val(var1, var8, var11, var3)) {
                  if (var4 != null) {
                     if ((var11 == null || var11 == TOMBSTONE) && var3 != TOMBSTONE) {
                        var7._size.add(1L);
                     }

                     if (var11 != null && var11 != TOMBSTONE && var3 == TOMBSTONE) {
                        var7._size.add(-1L);
                     }
                  }

                  return var11 == null && var4 != null ? TOMBSTONE : var11;
               }

               var11 = val(var1, var8);
               if (var11 instanceof Prime) {
                  return putIfMatch(var0, var7.copy_slot_and_check(var0, var1, var8, var4), var2, var3, var4);
               }
            }

            throw new AssertionError();
         }
      }
   }

   private final Object[] help_copy(Object[] var1) {
      Object[] var2 = this._kvs;
      CHM var3 = chm(var2);
      if (var3._newkvs == null) {
         return var1;
      } else {
         var3.help_copy_impl(this, var2, false);
         return var1;
      }
   }

   public Enumeration<TypeV> elements() {
      return new SnapshotV(this);
   }

   @Override
   public Collection<TypeV> values() {
      return new 1(this);
   }

   public Enumeration<TypeK> keys() {
      return new SnapshotK(this);
   }

   @Override
   public Set<TypeK> keySet() {
      return new 2(this);
   }

   @Override
   public Set<Entry<TypeK, TypeV>> entrySet() {
      return new 3(this);
   }

   private void writeObject(ObjectOutputStream var1) throws IOException {
      var1.defaultWriteObject();

      for (Object var3 : this.keySet()) {
         Object var4 = this.get(var3);
         var1.writeObject(var3);
         var1.writeObject(var4);
      }

      var1.writeObject(null);
      var1.writeObject(null);
   }

   private void readObject(ObjectInputStream var1) throws IOException, ClassNotFoundException {
      var1.defaultReadObject();
      this.initialize(8);

      while (true) {
         Object var2 = var1.readObject();
         Object var3 = var1.readObject();
         if (var2 == null) {
            return;
         }

         this.put((TypeK)var2, (TypeV)var3);
      }
   }

   static {
      Object var0 = null;

      try {
         var0 = NonBlockingHashMap.class.getDeclaredField("_kvs");
      } catch (NoSuchFieldException var2) {
         throw new RuntimeException(var2);
      }

      _kvs_offset = _unsafe.objectFieldOffset((Field)var0);
      NO_MATCH_OLD = new Object();
      MATCH_ANY = new Object();
      TOMBSTONE = new Object();
      TOMBPRIME = new Prime(TOMBSTONE);
   }
}
