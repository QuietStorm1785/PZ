package zombie.core.Collections;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.lang.reflect.Field;
import java.util.AbstractMap;
import java.util.Collection;
import java.util.Enumeration;
import java.util.Set;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentMap;
import sun.misc.Unsafe;
import zombie.core.Collections.NonBlockingHashMapLong.1;
import zombie.core.Collections.NonBlockingHashMapLong.2;
import zombie.core.Collections.NonBlockingHashMapLong.3;
import zombie.core.Collections.NonBlockingHashMapLong.CHM;
import zombie.core.Collections.NonBlockingHashMapLong.IteratorLong;
import zombie.core.Collections.NonBlockingHashMapLong.Prime;
import zombie.core.Collections.NonBlockingHashMapLong.SnapshotV;

public class NonBlockingHashMapLong<TypeV> extends AbstractMap<Long, TypeV> implements ConcurrentMap<Long, TypeV>, Serializable {
   private static final long serialVersionUID = 1234123412341234124L;
   private static final int REPROBE_LIMIT = 10;
   private static final Unsafe _unsafe = UtilUnsafe.getUnsafe();
   private static final int _Obase = _unsafe.arrayBaseOffset(Object[].class);
   private static final int _Oscale = _unsafe.arrayIndexScale(Object[].class);
   private static final int _Lbase = _unsafe.arrayBaseOffset(long[].class);
   private static final int _Lscale = _unsafe.arrayIndexScale(long[].class);
   private static final long _chm_offset;
   private static final long _val_1_offset;
   private transient CHM _chm;
   private transient Object _val_1;
   private transient long _last_resize_milli;
   private final boolean _opt_for_space;
   private static final int MIN_SIZE_LOG = 4;
   private static final int MIN_SIZE = 16;
   private static final Object NO_MATCH_OLD;
   private static final Object MATCH_ANY;
   private static final Object TOMBSTONE;
   private static final Prime TOMBPRIME;
   private static final long NO_KEY = 0L;
   private transient Counter _reprobes = new Counter();

   private static long rawIndex(Object[] var0, int var1) {
      assert var1 >= 0 && var1 < var0.length;

      return _Obase + var1 * _Oscale;
   }

   private static long rawIndex(long[] var0, int var1) {
      assert var1 >= 0 && var1 < var0.length;

      return _Lbase + var1 * _Lscale;
   }

   private final boolean CAS(long var1, Object var3, Object var4) {
      return _unsafe.compareAndSwapObject(this, var1, var3, var4);
   }

   public final void print() {
      System.out.println("=========");
      print_impl(-99, 0L, this._val_1);
      this._chm.print();
      System.out.println("=========");
   }

   private static final void print_impl(int var0, long var1, Object var3) {
      String var4 = var3 instanceof Prime ? "prime_" : "";
      Object var5 = Prime.unbox(var3);
      String var6 = var5 == TOMBSTONE ? "tombstone" : var5.toString();
      System.out.println("[" + var0 + "]=(" + var1 + "," + var4 + var6 + ")");
   }

   private final void print2() {
      System.out.println("=========");
      print2_impl(-99, 0L, this._val_1);
      this._chm.print();
      System.out.println("=========");
   }

   private static final void print2_impl(int var0, long var1, Object var3) {
      if (var3 != null && Prime.unbox(var3) != TOMBSTONE) {
         print_impl(var0, var1, var3);
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

   public NonBlockingHashMapLong() {
      this(16, true);
   }

   public NonBlockingHashMapLong(int var1) {
      this(var1, true);
   }

   public NonBlockingHashMapLong(boolean var1) {
      this(1, var1);
   }

   public NonBlockingHashMapLong(int var1, boolean var2) {
      this._opt_for_space = var2;
      this.initialize(var1);
   }

   private final void initialize(int var1) {
      if (var1 < 0) {
         throw new IllegalArgumentException();
      } else {
         int var2 = 4;

         while (1 << var2 < var1) {
            var2++;
         }

         this._chm = new CHM(this, new Counter(), var2);
         this._val_1 = TOMBSTONE;
         this._last_resize_milli = System.currentTimeMillis();
      }
   }

   @Override
   public int size() {
      return (this._val_1 == TOMBSTONE ? 0 : 1) + this._chm.size();
   }

   public boolean containsKey(long var1) {
      return this.get(var1) != null;
   }

   public boolean contains(Object var1) {
      return this.containsValue(var1);
   }

   public TypeV put(long var1, TypeV var3) {
      return this.putIfMatch(var1, var3, NO_MATCH_OLD);
   }

   public TypeV putIfAbsent(long var1, TypeV var3) {
      return this.putIfMatch(var1, var3, TOMBSTONE);
   }

   public TypeV remove(long var1) {
      return this.putIfMatch(var1, TOMBSTONE, NO_MATCH_OLD);
   }

   public boolean remove(long var1, Object var3) {
      return this.putIfMatch(var1, TOMBSTONE, var3) == var3;
   }

   public TypeV replace(long var1, TypeV var3) {
      return this.putIfMatch(var1, var3, MATCH_ANY);
   }

   public boolean replace(long var1, TypeV var3, TypeV var4) {
      return this.putIfMatch(var1, var4, var3) == var3;
   }

   private final TypeV putIfMatch(long var1, Object var3, Object var4) {
      if (var4 == null || var3 == null) {
         throw new NullPointerException();
      } else if (var1 != 0L) {
         Object var6 = this._chm.putIfMatch(var1, var3, var4);

         assert !(var6 instanceof Prime);

         assert var6 != null;

         return (TypeV)(var6 == TOMBSTONE ? null : var6);
      } else {
         Object var5 = this._val_1;
         if (var4 == NO_MATCH_OLD || var5 == var4 || var4 == MATCH_ANY && var5 != TOMBSTONE || var4.equals(var5)) {
            this.CAS(_val_1_offset, var5, var3);
         }

         return (TypeV)(var5 == TOMBSTONE ? null : var5);
      }
   }

   @Override
   public void clear() {
      CHM var1 = new CHM(this, new Counter(), 4);

      while (!this.CAS(_chm_offset, this._chm, var1)) {
      }

      this.CAS(_val_1_offset, this._val_1, TOMBSTONE);
   }

   @Override
   public boolean containsValue(Object var1) {
      if (var1 == null) {
         return false;
      } else if (var1 == this._val_1) {
         return true;
      } else {
         for (Object var3 : this.values()) {
            if (var3 == var1 || var3.equals(var1)) {
               return true;
            }
         }

         return false;
      }
   }

   public final TypeV get(long var1) {
      if (var1 == 0L) {
         Object var4 = this._val_1;
         return (TypeV)(var4 == TOMBSTONE ? null : var4);
      } else {
         Object var3 = this._chm.get_impl(var1);

         assert !(var3 instanceof Prime);

         assert var3 != TOMBSTONE;

         return (TypeV)var3;
      }
   }

   @Override
   public TypeV get(Object var1) {
      return var1 instanceof Long ? this.get(((Long)var1).longValue()) : null;
   }

   @Override
   public TypeV remove(Object var1) {
      return var1 instanceof Long ? this.remove(((Long)var1).longValue()) : null;
   }

   @Override
   public boolean remove(Object var1, Object var2) {
      return var1 instanceof Long ? this.remove(((Long)var1).longValue(), var2) : false;
   }

   @Override
   public boolean containsKey(Object var1) {
      return var1 instanceof Long ? this.containsKey(((Long)var1).longValue()) : false;
   }

   public TypeV putIfAbsent(Long var1, TypeV var2) {
      return this.putIfAbsent(var1.longValue(), (TypeV)var2);
   }

   public TypeV replace(Long var1, TypeV var2) {
      return this.replace(var1.longValue(), (TypeV)var2);
   }

   public TypeV put(Long var1, TypeV var2) {
      return this.put(var1.longValue(), (TypeV)var2);
   }

   public boolean replace(Long var1, TypeV var2, TypeV var3) {
      return this.replace(var1.longValue(), (TypeV)var2, (TypeV)var3);
   }

   private final void help_copy() {
      CHM var1 = this._chm;
      if (var1._newchm != null) {
         var1.help_copy_impl(false);
      }
   }

   public Enumeration<TypeV> elements() {
      return new SnapshotV(this);
   }

   @Override
   public Collection<TypeV> values() {
      return new 1(this);
   }

   public Enumeration<Long> keys() {
      return new IteratorLong(this);
   }

   @Override
   public Set<Long> keySet() {
      return new 2(this);
   }

   @Override
   public Set<Entry<Long, TypeV>> entrySet() {
      return new 3(this);
   }

   private void writeObject(ObjectOutputStream var1) throws IOException {
      var1.defaultWriteObject();

      for (long var3 : this.keySet()) {
         Object var5 = this.get(var3);
         var1.writeLong(var3);
         var1.writeObject(var5);
      }

      var1.writeLong(0L);
      var1.writeObject(null);
   }

   private void readObject(ObjectInputStream var1) throws IOException, ClassNotFoundException {
      var1.defaultReadObject();
      this.initialize(16);

      while (true) {
         long var2 = var1.readLong();
         Object var4 = var1.readObject();
         if (var2 == 0L && var4 == null) {
            return;
         }

         this.put(var2, (TypeV)var4);
      }
   }

   static {
      Object var0 = null;

      try {
         var0 = NonBlockingHashMapLong.class.getDeclaredField("_chm");
      } catch (NoSuchFieldException var3) {
         throw new RuntimeException(var3);
      }

      _chm_offset = _unsafe.objectFieldOffset((Field)var0);

      try {
         var0 = NonBlockingHashMapLong.class.getDeclaredField("_val_1");
      } catch (NoSuchFieldException var2) {
         throw new RuntimeException(var2);
      }

      _val_1_offset = _unsafe.objectFieldOffset((Field)var0);
      NO_MATCH_OLD = new Object();
      MATCH_ANY = new Object();
      TOMBSTONE = new Object();
      TOMBPRIME = new Prime(TOMBSTONE);
   }
}
