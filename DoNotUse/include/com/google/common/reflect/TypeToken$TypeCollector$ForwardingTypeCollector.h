#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/reflect/TypeToken/TypeCollector.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   private const TypeCollector<K> delegate;

   TypeToken$TypeCollector$ForwardingTypeCollector(TypeCollector<K> delegate) {
      super(nullptr);
      this.delegate = delegate;
   }

   Class<?> getRawType(K type) {
      return this.delegate.getRawType(type);
   }

   Iterable<? : public K> getInterfaces(K type) {
      return this.delegate.getInterfaces(type);
   }

    K getSuperclass(K type) {
      return (K)this.delegate.getSuperclass(type);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
