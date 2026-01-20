#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace util {


class PooledArrayObject {
public:
   private T[] m_array = nullptr;

   public T[] array() {
      return this.m_array;
   }

    int length() {
      return this.m_array.length;
   }

    T get(int var1) {
      return this.m_array[var1];
   }

    void set(int var1, T var2) {
      this.m_array[var1] = (T)var2;
   }

    void initCapacity(int var1, T[]> var2) {
      if (this.m_array == nullptr || this.m_array.length != var1) {
         this.m_array = (T[])((Object[])var2.apply(var1));
      }
   }

    bool isEmpty() {
      return this.m_array == nullptr || this.m_array.length == 0;
   }
}
} // namespace util
} // namespace zombie
