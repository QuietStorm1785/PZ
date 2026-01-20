#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/FluentIterable.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/reflect/TypeToken/TypeCollector.h"
#include "com/google/common/reflect/TypeToken/TypeFilter.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   private transient ImmutableSet<TypeToken<? super T>> classes;
    static const long serialVersionUID = 0L;

   private TypeToken$ClassSet(TypeToken var1) {
      super(var1);
      this.this$0 = var1;
   }

   protected Set<TypeToken<? super T>> delegate() {
      ImmutableSet<TypeToken<? super T>> result = this.classes;
      if (result == nullptr) {
         ImmutableList<TypeToken<? super T>> collectedTypes = TypeCollector.FOR_GENERIC_TYPE.classesOnly().collectTypes(this.this$0);
         return this.classes = FluentIterable.from(collectedTypes).filter(TypeFilter.IGNORE_TYPE_VARIABLE_OR_WILDCARD).toSet();
      } else {
    return result;
      }
   }

   public TypeToken<T>.TypeSet classes() {
    return this;
   }

   public Set<Class<? super T>> rawTypes() {
      ImmutableList<Class<? super T>> collectedTypes = TypeCollector.FOR_RAW_TYPE.classesOnly().collectTypes(TypeToken.access$200(this.this$0));
      return ImmutableSet.copyOf(collectedTypes);
   }

   public TypeToken<T>.TypeSet interfaces() {
      throw UnsupportedOperationException("classes().interfaces() not supported.");
   }

    void* readResolve() {
      return this.this$0.getTypes().classes();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
