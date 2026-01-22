#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Iterables.h"
#include "com/google/common/reflect/Types/1.h"
#include "com/google/common/reflect/Types/2.h"
#include "com/google/common/reflect/Types/ClassOwnership.h"
#include "com/google/common/reflect/Types/JavaVersion.h"
#include "com/google/common/reflect/Types/ParameterizedTypeImpl.h"
#include "com/google/common/reflect/Types/TypeVariableImpl.h"
#include "com/google/common/reflect/Types/TypeVariableInvocationHandler.h"
#include "com/google/common/reflect/Types/WildcardTypeImpl.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
   private static const Function<Type, std::string> TYPE_NAME = std::make_unique<1>();
    static const Joiner COMMA_JOINER = Joiner.on(", ").useForNull("nullptr");

    static Type newArrayType(Type componentType) {
      if (dynamic_cast<WildcardType*>(componentType) != nullptr) {
    WildcardType wildcard = (WildcardType)componentType;
         Type[] lowerBounds = wildcard.getLowerBounds();
         Preconditions.checkArgument(lowerBounds.length <= 1, "Wildcard cannot have more than one lower bounds.");
         if (lowerBounds.length == 1) {
    return supertypeOf();
         } else {
            Type[] upperBounds = wildcard.getUpperBounds();
            Preconditions.checkArgument(upperBounds.length == 1, "Wildcard should have only one upper bound.");
    return subtypeOf();
         }
      } else {
         return JavaVersion.CURRENT.newArrayType(componentType);
      }
   }

    static ParameterizedType newParameterizedTypeWithOwner(@Nullable Type, Class<?> rawType, Type... arguments) {
      if (ownerType == nullptr) {
    return newParameterizedType();
      } else {
         Preconditions.checkNotNull(arguments);
         Preconditions.checkArgument(rawType.getEnclosingClass() != nullptr, "Owner type for unenclosed %s", rawType);
         return std::make_shared<ParameterizedTypeImpl>(ownerType, rawType, arguments);
      }
   }

    static ParameterizedType newParameterizedType(Class<?> rawType, Type... arguments) {
      return std::make_shared<ParameterizedTypeImpl>(ClassOwnership.JVM_BEHAVIOR.getOwnerType(rawType), rawType, arguments);
   }

   static <D : public GenericDeclaration> TypeVariable<D> newArtificialTypeVariable(D declaration, std::string name, Type... bounds) {
    return newTypeVariableImpl(bounds.length ==);
   }

    static WildcardType subtypeOf(Type upperBound) {
      return std::make_shared<WildcardTypeImpl>(new Type[0], new Type[]{upperBound});
   }

    static WildcardType supertypeOf(Type lowerBound) {
      return std::make_shared<WildcardTypeImpl>(new Type[]{lowerBound}, new Type[]{Object.class});
   }

    static std::string toString(Type type) {
      return dynamic_cast<Class*>(type) != nullptr ? ((Class)type).getName() : type;
   }

    static Type getComponentType(Type type) {
      Preconditions.checkNotNull(type);
      AtomicReference<Type> result = std::make_unique<AtomicReference<>>();
    std::make_shared<2>();
      return result.get();
   }

    static Type subtypeOfComponentType(Type[] bounds) {
    for (auto& bound : bounds)    Type componentType = getComponentType(bound);
         if (componentType != nullptr) {
            if (dynamic_cast<Class*>(componentType) != nullptr) {
               Class<?> componentClass = (Class<?>)componentType;
               if (componentClass.isPrimitive()) {
    return componentClass;
               }
            }

    return subtypeOf();
         }
      }

    return nullptr;
   }

   private static <D : public GenericDeclaration> TypeVariable<D> newTypeVariableImpl(D genericDeclaration, std::string name, Type[] bounds) {
      TypeVariableImpl<D> typeVariableImpl = std::make_shared<TypeVariableImpl>(genericDeclaration, name, bounds);
      return (TypeVariable<D>)Reflection.newProxy(TypeVariable.class, std::make_shared<TypeVariableInvocationHandler>(typeVariableImpl));
   }

   private static Type[] toArray(Collection<Type> types) {
      return types.toArray(new Type[types.size()]);
   }

   private static Iterable<Type> filterUpperBounds(Iterable<Type> bounds) {
      return Iterables.filter(bounds, Predicates.not(Predicates.equalTo(Object.class)));
   }

    static void disallowPrimitiveType(Type[] types, const std::string& usedAs) {
    for (auto& type : types)         if (dynamic_cast<Class*>(type) != nullptr) {
            Class<?> cls = (Class<?>)type;
            Preconditions.checkArgument(!cls.isPrimitive(), "Primitive type '%s' used as %s", cls, usedAs);
         }
      }
   }

   static Class<?> getArrayClass(Class<?> componentType) {
      return Array.newInstance(componentType, 0).getClass();
   }

    private Types() {
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
