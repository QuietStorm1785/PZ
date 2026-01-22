#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultiset {
public:
   const ImmutableMultiset<E> multiset;

   ImmutableMultiset$EntrySetSerializedForm(ImmutableMultiset<E> multiset) {
      this.multiset = multiset;
   }

    void* readResolve() {
      return this.multiset.entrySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
