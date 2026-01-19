package zombie.core.utils;

import zombie.core.utils.HashMap.Bucket;

public class HashMap$Iterator {
   private HashMap hashMap;
   private int bucketIdx;
   private int keyValuePairIdx;
   private int elementIdx;
   private Object currentKey;
   private Object currentValue;

   public HashMap$Iterator(HashMap var1) {
      this.hashMap = var1;
      this.reset();
   }

   public HashMap$Iterator reset() {
      this.bucketIdx = 0;
      this.keyValuePairIdx = 0;
      this.elementIdx = 0;
      this.currentKey = null;
      this.currentValue = null;
      return this;
   }

   public boolean hasNext() {
      return this.elementIdx < this.hashMap.elements;
   }

   public boolean advance() {
      while (this.bucketIdx < this.hashMap.buckets.length) {
         Bucket var1 = this.hashMap.buckets[this.bucketIdx];
         if (this.keyValuePairIdx == var1.size()) {
            this.keyValuePairIdx = 0;
            this.bucketIdx++;
         } else {
            while (this.keyValuePairIdx < var1.size()) {
               if (var1.keys[this.keyValuePairIdx] != null) {
                  this.currentKey = var1.keys[this.keyValuePairIdx];
                  this.currentValue = var1.values[this.keyValuePairIdx];
                  this.keyValuePairIdx++;
                  this.elementIdx++;
                  return true;
               }

               this.keyValuePairIdx++;
            }

            this.keyValuePairIdx = 0;
            this.bucketIdx++;
         }
      }

      return false;
   }

   public Object getKey() {
      return this.currentKey;
   }

   public Object getValue() {
      return this.currentValue;
   }
}
