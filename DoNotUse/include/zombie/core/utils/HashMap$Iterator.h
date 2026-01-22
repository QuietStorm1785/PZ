#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/std::unordered_map/Bucket.h"

namespace zombie {
namespace core {
namespace utils {


class std::unordered_map {
public:
    std::unordered_map hashMap;
    int bucketIdx;
    int keyValuePairIdx;
    int elementIdx;
    void* currentKey;
    void* currentValue;

   public std::unordered_map$Iterator(std::unordered_map var1) {
      this.hashMap = var1;
      this.reset();
   }

   public std::unordered_map$Iterator reset() {
      this.bucketIdx = 0;
      this.keyValuePairIdx = 0;
      this.elementIdx = 0;
      this.currentKey = nullptr;
      this.currentValue = nullptr;
    return this;
   }

    bool hasNext() {
      return this.elementIdx < this.hashMap.elements;
   }

    bool advance() {
      while (this.bucketIdx < this.hashMap.buckets.length) {
    Bucket var1 = this.hashMap.buckets[this.bucketIdx];
         if (this.keyValuePairIdx == var1.size()) {
            this.keyValuePairIdx = 0;
            this.bucketIdx++;
         } else {
            while (this.keyValuePairIdx < var1.size()) {
               if (var1.keys[this.keyValuePairIdx] != nullptr) {
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

    void* getKey() {
      return this.currentKey;
   }

    void* getValue() {
      return this.currentValue;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
