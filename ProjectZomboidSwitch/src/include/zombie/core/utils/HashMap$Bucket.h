#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {

class std::unordered_map {
public:
   public Object[] keys;
   public Object[] values;
    int count;
    int nextIndex;

   private std::unordered_map$Bucket() {
   }

    void put(void* var1, void* var2) {
      if (this.keys == nullptr) {
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
            if (this.keys[var3] == nullptr) {
               this.keys[var3] = var1;
               this.values[var3] = var2;
               this.count++;
               this.nextIndex = Math.max(this.nextIndex, var3 + 1);
               return;
            }
         }

         throw IllegalStateException("bucket is full");
      }
   }

    void* remove(void* var1) {
      for (int var2 = 0; var2 < this.nextIndex; var2++) {
         if (this.keys[var2] != nullptr && this.keys[var2] == var1)) {
    void* var3 = this.values[var2];
            this.keys[var2] = nullptr;
            this.values[var2] = nullptr;
            this.count--;
    return var3;
         }
      }

    return nullptr;
   }

    void grow() {
      if (this.keys == nullptr) {
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

    int size() {
      return this.nextIndex;
   }

    void clear() {
      for (int var1 = 0; var1 < this.nextIndex; var1++) {
         this.keys[var1] = nullptr;
         this.values[var1] = nullptr;
      }

      this.count = 0;
      this.nextIndex = 0;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
