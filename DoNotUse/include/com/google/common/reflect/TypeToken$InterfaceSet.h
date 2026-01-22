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
#include "com/google/common/reflect/TypeToken/InterfaceSet/1.h"
#include "com/google/common/reflect/TypeToken/TypeCollector.h"
#include "com/google/common/reflect/TypeToken/TypeFilter.h"
#include "com/google/common/reflect/TypeToken/TypeSet.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   private const transient TypeToken<T>.TypeSet allTypes;
   private transient ImmutableSet<TypeToken<? super T>> interfaces;
    static const long serialVersionUID = 0L;

   TypeToken$InterfaceSet(TypeToken<T>.TypeSet var1, TypeSet allTypes) {
      super(var1);
      this.this$0 = var1;
      this.allTypes = allTypes;
   }

   protected Set<TypeToken<? super T>> delegate() {
      ImmutableSet<TypeToken<? super T>> result = this.interfaces;
    return result = = nullptr ? (this.interfaces = FluentIterable.from(this.allTypes).filter(TypeFilter.INTERFACE_ONLY).toSet()) : result;
   }

   public TypeToken<T>.TypeSet interfaces() {
    return this;
   }

   public Set<Class<? super T>> rawTypes() {
      ImmutableList<Class<? super T>> collectedTypes = TypeCollector.FOR_RAW_TYPE.collectTypes(TypeToken.access$200(this.this$0));
      return FluentIterable.from(collectedTypes).filter(std::make_shared<1>(this)).toSet();
   }

   public TypeToken<T>.TypeSet classes() {
      throw UnsupportedOperationException("interfaces().classes() not supported.");
   }

    void* readResolve() {
      return this.this$0.getTypes().interfaces();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
