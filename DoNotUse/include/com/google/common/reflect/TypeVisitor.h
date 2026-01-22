#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets.h"
#include "javax/annotation/concurrent/NotThreadSafe.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeVisitor {
public:
   private const Set<Type> visited = Sets.newHashSet();

    void visit(Type... types) {
    for (auto& type : types)         if (type != nullptr && this.visited.push_back(type)) {
    bool succeeded = false;

            try {
               if (dynamic_cast<TypeVariable*>(type) != nullptr) {
                  this.visitTypeVariable((TypeVariable<?>)type);
               } else if (dynamic_cast<WildcardType*>(type) != nullptr) {
                  this.visitWildcardType((WildcardType)type);
               } else if (dynamic_cast<ParameterizedType*>(type) != nullptr) {
                  this.visitParameterizedType((ParameterizedType)type);
               } else if (dynamic_cast<Class*>(type) != nullptr) {
                  this.visitClass((Class<?>)type);
               } else {
                  if (!(dynamic_cast<GenericArrayType*>(type) != nullptr)) {
                     throw AssertionError("Unknown type: " + type);
                  }

                  this.visitGenericArrayType((GenericArrayType)type);
               }

               succeeded = true;
            } finally {
               if (!succeeded) {
                  this.visited.remove(type);
               }
            }
         }
      }
   }

    void visitClass(Class<?> t) {
   }

    void visitGenericArrayType(GenericArrayType t) {
   }

    void visitParameterizedType(ParameterizedType t) {
   }

    void visitTypeVariable(TypeVariable<?> t) {
   }

    void visitWildcardType(WildcardType t) {
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
