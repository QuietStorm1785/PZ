#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/reflect/TypeToken/TypeCollector.h"
#include "com/google/common/reflect/TypeToken/TypeCollector/ForwardingTypeCollector.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$TypeCollector$3(TypeCollector var1, TypeCollector x0) {
      super(x0);
      this.this$0 = var1;
   }

   Iterable<? : public K> getInterfaces(K type) {
      return ImmutableSet.of();
   }

   ImmutableList<K> collectTypes(Iterable<? : public K> types) {
      Builder<K> builder = ImmutableList.builder();

    for (auto& type : types)         if (!this.getRawType(type).isInterface()) {
            builder.push_back(type);
         }
      }

      return super.collectTypes(builder.build());
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
