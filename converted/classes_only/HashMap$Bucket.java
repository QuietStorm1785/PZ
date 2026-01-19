package zombie.core.utils;

class HashMap$Bucket {
   public Object[] keys;
   public Object[] values;
   public int count;
   public int nextIndex;

   private HashMap$Bucket() {
   }

   public void put(Object var1, Object var2) throws IllegalStateException {
      if (this.keys == null) {
         this.grow();
         this.keys[0] = var1;
         this.values[0] = var2;
         this.nextIndex = 1;
         this.count = 1;
      } else {
         if (this.count == this.keys.length) {
            this.grow();
         }

         for (int var3 = 0; var3 < this.keys.length; var3++) {
            if (this.keys[var3] == null) {
               this.keys[var3] = var1;
               this.values[var3] = var2;
               this.count++;
               this.nextIndex = Math.max(this.nextIndex, var3 + 1);
               return;
            }
         }

         throw new IllegalStateException("bucket is full");
      }
   }

   public Object remove(Object var1) {
      for (int var2 = 0; var2 < this.nextIndex; var2++) {
         if (this.keys[var2] != null && this.keys[var2].equals(var1)) {
            Object var3 = this.values[var2];
            this.keys[var2] = null;
            this.values[var2] = null;
            this.count--;
            return var3;
         }
      }

      return null;
   }

   private void grow() {
      if (this.keys == null) {
         this.keys = new Object[2];
         this.values = new Object[2];
      } else {
         Object[] var1 = this.keys;
         Object[] var2 = this.values;
         this.keys = new Object[var1.length * 2];
         this.values = new Object[var2.length * 2];
         System.arraycopy(var1, 0, this.keys, 0, var1.length);
         System.arraycopy(var2, 0, this.values, 0, var2.length);
      }
   }

   public int size() {
      return this.nextIndex;
   }

   public void clear() {
      for (int var1 = 0; var1 < this.nextIndex; var1++) {
         this.keys[var1] = null;
         this.values[var1] = null;
      }

      this.count = 0;
      this.nextIndex = 0;
   }
}
