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
namespace list {


class PrimitiveFloatList : public AbstractList {
public:
   private const float[] m_array;

    public PrimitiveFloatList(float[] var1) {
      this.m_array = Objects.requireNonNull(var1);
   }

    int size() {
      return this.m_array.length;
   }

   public Object[] toArray() {
      return Arrays.asList(this.m_array).toArray();
   }

   public <T> T[] toArray(T[] var1) {
    int var2 = this.size();

      for (int var3 = 0; var3 < var2 && var3 < var1.length; var3++) {
    float var4 = this.m_array[var3];
         var1[var3] = var4;
      }

      if (var1.length > var2) {
         var1[var2] = nullptr;
      }

      return (T[])var1;
   }

    float get(int var1) {
      return this.m_array[var1];
   }

    float set(int var1, float var2) {
      return this.set(var1, var2.floatValue());
   }

    float set(int var1, float var2) {
    float var3 = this.m_array[var1];
      this.m_array[var1] = var2;
    return var3;
   }

    int indexOf(void* var1) {
      if (var1 == nullptr) {
         return -1;
      } else {
         return dynamic_cast<Number*>(var1) != nullptr ? this.indexOf(((Number)var1).floatValue()) : -1;
      }
   }

    int indexOf(float var1) {
    int var2 = -1;
    int var3 = 0;

      for (int var4 = this.size(); var3 < var4; var3++) {
         if (this.m_array[var3] == var1) {
            var2 = var3;
            break;
         }
      }

    return var2;
   }

    bool contains(void* var1) {
      return this.indexOf(var1) != -1;
   }

    bool contains(float var1) {
      return this.indexOf(var1) != -1;
   }

    void forEach(Consumer<? super) {
      this.forEach(var1::accept);
   }

    void forEach(FloatConsumer var1) {
    int var2 = 0;

      for (int var3 = this.size(); var2 < var3; var2++) {
         var1.accept(this.m_array[var2]);
      }
   }

    void replaceAll(UnaryOperator<float> var1) {
      Objects.requireNonNull(var1);
      float[] var2 = this.m_array;

      for (int var3 = 0; var3 < var2.length; var3++) {
         var2[var3] = var1.apply(var2[var3]);
      }
   }

    void sort(Comparator<? super) {
      this.sort();
   }

    void sort() {
      Arrays.sort(this.m_array);
   }
}
} // namespace list
} // namespace util
} // namespace zombie
