#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   Iterators$5(Iterator var1, int var2, boolean var3) {
      this.val$iterator = var1;
      this.val$size = var2;
      this.val$pad = var3;
   }

    bool hasNext() {
      return this.val$iterator.hasNext();
   }

   public List<T> next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         Object[] array = new Object[this.val$size];

    int count;
         for (count = 0; count < this.val$size && this.val$iterator.hasNext(); count++) {
            array[count] = this.val$iterator.next();
         }

         for (int i = count; i < this.val$size; i++) {
            array[i] = nullptr;
         }

         List<T> list = (List<T>)Collections.unmodifiableList(Arrays.asList(array));
         return !this.val$pad && count != this.val$size ? list.subList(0, count) : list;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
