package zombie.core.utils;

import zombie.core.utils.HashMap.Bucket;
import zombie.core.utils.HashMap.Iterator;

public class HashMap {
   private int capacity = 2;
   private int elements = 0;
   private Bucket[] buckets = new Bucket[this.capacity];

   public HashMap() {
      for (int var1 = 0; var1 < this.capacity; var1++) {
         this.buckets[var1] = new Bucket();
      }
   }

   public void clear() {
      this.elements = 0;

      for (int var1 = 0; var1 < this.capacity; var1++) {
         this.buckets[var1].clear();
      }
   }

   private void grow() {
      Bucket[] var1 = this.buckets;
      this.capacity *= 2;
      this.elements = 0;
      this.buckets = new Bucket[this.capacity];

      for (int var2 = 0; var2 < this.capacity; var2++) {
         this.buckets[var2] = new Bucket();
      }

      for (int var5 = 0; var5 < var1.length; var5++) {
         Bucket var3 = var1[var5];

         for (int var4 = 0; var4 < var3.size(); var4++) {
            if (var3.keys[var4] != null) {
               this.put(var3.keys[var4], var3.values[var4]);
            }
         }
      }
   }

   public Object get(Object var1) {
      Bucket var2 = this.buckets[Math.abs(var1.hashCode()) % this.capacity];

      for (int var3 = 0; var3 < var2.size(); var3++) {
         if (var2.keys[var3] != null && var2.keys[var3].equals(var1)) {
            return var2.values[var3];
         }
      }

      return null;
   }

   public Object remove(Object var1) {
      Bucket var2 = this.buckets[Math.abs(var1.hashCode()) % this.capacity];
      Object var3 = var2.remove(var1);
      if (var3 != null) {
         this.elements--;
         return var3;
      } else {
         return null;
      }
   }

   public Object put(Object var1, Object var2) {
      if (this.elements + 1 >= this.buckets.length) {
         this.grow();
      }

      Object var3 = this.remove(var1);
      Bucket var4 = this.buckets[Math.abs(var1.hashCode()) % this.capacity];
      var4.put(var1, var2);
      this.elements++;
      return var3;
   }

   public int size() {
      return this.elements;
   }

   public boolean isEmpty() {
      return this.size() == 0;
   }

   public Iterator iterator() {
      return new Iterator(this);
   }

   @Override
   public String toString() {
      Object var1 = new String();

      for (int var2 = 0; var2 < this.buckets.length; var2++) {
         Bucket var3 = this.buckets[var2];

         for (int var4 = 0; var4 < var3.size(); var4++) {
            if (var3.keys[var4] != null) {
               if (var1.length() > 0) {
                  var1 = var1 + ", ";
               }

               var1 = var1 + var3.keys[var4] + "=" + var3.values[var4];
            }
         }
      }

      return "HashMap[" + var1 + "]";
   }
}
