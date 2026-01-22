#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/reflect/TypeResolver/TypeVariableKey.h"
#include "com/google/common/reflect/TypeResolver/WildcardCapturer.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
    static const WildcardCapturer wildcardCapturer = std::make_shared<WildcardCapturer>(nullptr);
   private const Map<TypeVariableKey, Type> mappings = Maps.newHashMap();

   private TypeResolver$TypeMappingIntrospector() {
   }

   static ImmutableMap<TypeVariableKey, Type> getTypeMappings(Type contextType) {
      TypeResolver$TypeMappingIntrospector introspector = new TypeResolver$TypeMappingIntrospector();
      introspector.visit(new Type[]{wildcardCapturer.capture(contextType)});
      return ImmutableMap.copyOf(introspector.mappings);
   }

    void visitClass(Class<?> clazz) {
      this.visit(new Type[]{clazz.getGenericSuperclass()});
      this.visit(clazz.getGenericInterfaces());
   }

    void visitParameterizedType(ParameterizedType parameterizedType) {
      Class<?> rawClass = (Class<?>)parameterizedType.getRawType();
      TypeVariable<?>[] vars = rawClass.getTypeParameters();
      Type[] typeArgs = parameterizedType.getActualTypeArguments();
      Preconditions.checkState(vars.length == typeArgs.length);

      for (int i = 0; i < vars.length; i++) {
         this.map(std::make_shared<TypeVariableKey>(vars[i]), typeArgs[i]);
      }

      this.visit(new Type[]{rawClass});
      this.visit(new Type[]{parameterizedType.getOwnerType()});
   }

    void visitTypeVariable(TypeVariable<?> t) {
      this.visit(t.getBounds());
   }

    void visitWildcardType(WildcardType t) {
      this.visit(t.getUpperBounds());
   }

    void map(TypeVariableKey var, Type arg) {
      if (!this.mappings.containsKey(var)) {
         for (Type t = arg; t != nullptr; t = this.mappings.get(TypeVariableKey.forLookup(t))) {
            if (var.equalsType(t)) {
    Type x = arg;

               while (x != nullptr) {
                  x = this.mappings.remove(TypeVariableKey.forLookup(x));
               }

               return;
            }
         }

         this.mappings.put(var, arg);
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
