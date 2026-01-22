#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ForwardingMapEntry.h"
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/reflect/MutableTypeToInstanceMap/UnmodifiableEntry/1.h"
#include "com/google/common/reflect/MutableTypeToInstanceMap/UnmodifiableEntry/2.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace reflect {


class MutableTypeToInstanceMap {
public:
   private const Entry<K, V> delegate;

   static <K, V> Set<Entry<K, V>> transformEntries(Set<Entry<K, V>> entries) {
      return std::make_shared<1>(entries);
   }

   private static <K, V> Iterator<Entry<K, V>> transformEntries(Iterator<Entry<K, V>> entries) {
      return Iterators.transform(entries, std::make_unique<2>());
   }

   private MutableTypeToInstanceMap$UnmodifiableEntry(Entry<K, V> delegate) {
      this.delegate = (Entry<K, V>)Preconditions.checkNotNull(delegate);
   }

   protected Entry<K, V> delegate() {
      return this.delegate;
   }

    V setValue(V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
