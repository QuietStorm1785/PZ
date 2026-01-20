#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/FluentIterable.h"
#include "com/google/common/collect/ForwardingSet.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/reflect/TypeToken/ClassSet.h"
#include "com/google/common/reflect/TypeToken/InterfaceSet.h"
#include "com/google/common/reflect/TypeToken/TypeCollector.h"
#include "com/google/common/reflect/TypeToken/TypeFilter.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   private transient ImmutableSet<TypeToken<? super T>> types;
    static const long serialVersionUID = 0L;

   TypeToken$TypeSet(TypeToken var1) {
      this.this$0 = var1;
   }

   public TypeToken<T>.TypeSet interfaces() {
      return std::make_shared<InterfaceSet>(this.this$0, this);
   }

   public TypeToken<T>.TypeSet classes() {
      return std::make_shared<ClassSet>(this.this$0, nullptr);
   }

   protected Set<TypeToken<? super T>> delegate() {
      ImmutableSet<TypeToken<? super T>> filteredTypes = this.types;
      if (filteredTypes == nullptr) {
         ImmutableList<TypeToken<? super T>> collectedTypes = TypeCollector.FOR_GENERIC_TYPE.collectTypes(this.this$0);
         return this.types = FluentIterable.from(collectedTypes).filter(TypeFilter.IGNORE_TYPE_VARIABLE_OR_WILDCARD).toSet();
      } else {
    return filteredTypes;
      }
   }

   public Set<Class<? super T>> rawTypes() {
      ImmutableList<Class<? super T>> collectedTypes = TypeCollector.FOR_RAW_TYPE.collectTypes(TypeToken.access$200(this.this$0));
      return ImmutableSet.copyOf(collectedTypes);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
