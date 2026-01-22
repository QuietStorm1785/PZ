#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/std::unordered_map/Bucket.h"
#include "zombie/core/utils/std::unordered_map/Iterator.h"

namespace zombie {
namespace core {
namespace utils {


class std::unordered_map {
public:
    int capacity = 2;
    int elements = 0;
   private Bucket[] buckets = new Bucket[this.capacity];

    public std::unordered_map() {
      for (int var1 = 0; var1 < this.capacity; var1++) {
         this.buckets[var1] = std::make_unique<Bucket>();
      }
   }

    void clear() {
      this.elements = 0;

      for (int var1 = 0; var1 < this.capacity; var1++) {
         this.buckets[var1].clear();
      }
   }

    void grow() {
      Bucket[] var1 = this.buckets;
      this.capacity *= 2;
      this.elements = 0;
      this.buckets = new Bucket[this.capacity];

      for (int var2 = 0; var2 < this.capacity; var2++) {
         this.buckets[var2] = std::make_unique<Bucket>();
      }

      for (int var5 = 0; var5 < var1.length; var5++) {
    Bucket var3 = var1[var5];

         for (int var4 = 0; var4 < var3.size(); var4++) {
            if (var3.keys[var4] != nullptr) {
               this.put(var3.keys[var4], var3.values[var4]);
            }
         }
      }
   }

    void* get(void* var1) {
    Bucket var2 = this.buckets[Math.abs(var1.hashCode()) % this.capacity];

      for (int var3 = 0; var3 < var2.size(); var3++) {
         if (var2.keys[var3] != nullptr && var2.keys[var3] == var1)) {
            return var2.values[var3];
         }
      }

    return nullptr;
   }

    void* remove(void* var1) {
    Bucket var2 = this.buckets[Math.abs(var1.hashCode()) % this.capacity];
    void* var3 = var2.remove(var1);
      if (var3 != nullptr) {
         this.elements--;
    return var3;
      } else {
    return nullptr;
      }
   }

    void* put(void* var1, void* var2) {
      if (this.elements + 1 >= this.buckets.length) {
         this.grow();
      }

    void* var3 = this.remove(var1);
    Bucket var4 = this.buckets[Math.abs(var1.hashCode()) % this.capacity];
      var4.put(var1, var2);
      this.elements++;
    return var3;
   }

    int size() {
      return this.elements;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    Iterator iterator() {
      return std::make_shared<Iterator>(this);
   }

    std::string toString() {
    void* var1 = new std::string();

      for (int var2 = 0; var2 < this.buckets.length; var2++) {
    Bucket var3 = this.buckets[var2];

         for (int var4 = 0; var4 < var3.size(); var4++) {
            if (var3.keys[var4] != nullptr) {
               if (var1.length() > 0) {
                  var1 = var1 + ", ";
               }

               var1 = var1 + var3.keys[var4] + "=" + var3.values[var4];
            }
         }
      }

      return "std::unordered_map[" + var1 + "]";
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
