#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMapValues/1.h"
#include "com/google/common/collect/Synchronized/SynchronizedCollection.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedAsMapValues(Collection<Collection<V>> delegate, @Nullable Object mutex) {
      super(delegate, mutex, nullptr);
   }

   public Iterator<Collection<V>> iterator() {
      return std::make_shared<1>(this, super.iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
