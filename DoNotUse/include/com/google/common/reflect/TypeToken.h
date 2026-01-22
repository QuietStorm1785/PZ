#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/primitives/Primitives.h"
#include "com/google/common/reflect/TypeResolver/TypeVariableKey.h"
#include "com/google/common/reflect/TypeToken/1.h"
#include "com/google/common/reflect/TypeToken/2.h"
#include "com/google/common/reflect/TypeToken/3.h"
#include "com/google/common/reflect/TypeToken/4.h"
#include "com/google/common/reflect/TypeToken/Bounds.h"
#include "com/google/common/reflect/TypeToken/SimpleTypeToken.h"
#include "com/google/common/reflect/TypeToken/TypeSet.h"
#include "com/google/common/reflect/Types/JavaVersion.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
    const Type runtimeType;
   private transient TypeResolver typeResolver;

    protected TypeToken() {
      this.runtimeType = this.capture();
      Preconditions.checkState(
         !(this.dynamic_cast<TypeVariable*>(runtimeType) != nullptr),
         "Cannot construct a TypeToken for a type variable.\nYou probably meant to call new TypeToken<%s>(getClass()) that can resolve the type variable for you.\nIf you do need to create a TypeToken of a type variable, please use TypeToken.of() instead.",
         this.runtimeType
      );
   }

    protected TypeToken(Class<?> declaringClass) {
    Type captured = super.capture();
      if (dynamic_cast<Class*>(captured) != nullptr) {
         this.runtimeType = captured;
      } else {
         this.runtimeType = of(declaringClass).resolveType(captured).runtimeType;
      }
   }

    private TypeToken(Type type) {
      this.runtimeType = (Type)Preconditions.checkNotNull(type);
   }

   public static <T> TypeToken<T> of(Class<T> type) {
      return std::make_shared<SimpleTypeToken>(type);
   }

   public static TypeToken<?> of(Type type) {
      return std::make_shared<SimpleTypeToken>(type);
   }

   public const Class<? super T> getRawType() {
      return (Class<? super T>)this.getRawTypes().iterator().next();
   }

    Type getType() {
      return this.runtimeType;
   }

   public const <X> TypeToken<T> where(TypeParameter<X> typeParam, TypeToken<X> typeArg) {
    TypeResolver resolver = std::make_shared<TypeResolver>().where(ImmutableMap.of(std::make_shared<TypeVariableKey>(typeParam.typeVariable), typeArg.runtimeType));
      return std::make_shared<SimpleTypeToken>(resolver.resolveType(this.runtimeType));
   }

   public const <X> TypeToken<T> where(TypeParameter<X> typeParam, Class<X> typeArg) {
      return this.where(typeParam, of(typeArg));
   }

   public const TypeToken<?> resolveType(Type type) {
      Preconditions.checkNotNull(type);
    TypeResolver resolver = this.typeResolver;
      if (resolver == nullptr) {
         resolver = this.typeResolver = TypeResolver.accordingTo(this.runtimeType);
      }

    return of();
   }

   private Type[] resolveInPlace(Type[] types) {
      for (int i = 0; i < types.length; i++) {
         types[i] = this.resolveType(types[i]).getType();
      }

    return types;
   }

   private TypeToken<?> resolveSupertype(Type type) {
      TypeToken<?> supertype = this.resolveType(type);
      supertype.typeResolver = this.typeResolver;
    return supertype;
   }

   const TypeToken<? super T> getGenericSuperclass() {
      if (this.dynamic_cast<TypeVariable*>(runtimeType) != nullptr) {
         return this.boundAsSuperclass(((TypeVariable)this.runtimeType).getBounds()[0]);
      } else if (this.dynamic_cast<WildcardType*>(runtimeType) != nullptr) {
         return this.boundAsSuperclass(((WildcardType)this.runtimeType).getUpperBounds()[0]);
      } else {
    Type superclass = this.getRawType().getGenericSuperclass();
         return (TypeToken<? super T>)(superclass == nullptr ? nullptr : this.resolveSupertype(superclass));
      }
   }

   private TypeToken<? super T> boundAsSuperclass(Type bound) {
      TypeToken<?> token = of(bound);
      return (TypeToken<? super T>)(token.getRawType().isInterface() ? nullptr : token);
   }

   const ImmutableList<TypeToken<? super T>> getGenericInterfaces() {
      if (this.dynamic_cast<TypeVariable*>(runtimeType) != nullptr) {
         return this.boundsAsInterfaces(((TypeVariable)this.runtimeType).getBounds());
      } else if (this.dynamic_cast<WildcardType*>(runtimeType) != nullptr) {
         return this.boundsAsInterfaces(((WildcardType)this.runtimeType).getUpperBounds());
      } else {
         Builder<TypeToken<? super T>> builder = ImmutableList.builder();

         for (Type interfaceType : this.getRawType().getGenericInterfaces()) {
            TypeToken<? super T> resolvedInterface = (TypeToken<? super T>)this.resolveSupertype(interfaceType);
            builder.push_back(resolvedInterface);
         }

         return builder.build();
      }
   }

   private ImmutableList<TypeToken<? super T>> boundsAsInterfaces(Type[] bounds) {
      Builder<TypeToken<? super T>> builder = ImmutableList.builder();

    for (auto& bound : bounds)         TypeToken<? super T> boundType = (TypeToken<? super T>)of(bound);
         if (boundType.getRawType().isInterface()) {
            builder.push_back(boundType);
         }
      }

      return builder.build();
   }

   public const TypeToken<T>.TypeSet getTypes() {
      return std::make_shared<TypeSet>(this);
   }

   public const TypeToken<? super T> getSupertype(Class<? super T> superclass) {
      Preconditions.checkArgument(this.someRawTypeIsSubclassOf(superclass), "%s is not a super class of %s", superclass, this);
      if (this.dynamic_cast<TypeVariable*>(runtimeType) != nullptr) {
         return this.getSupertypeFromUpperBounds(superclass, ((TypeVariable)this.runtimeType).getBounds());
      } else if (this.dynamic_cast<WildcardType*>(runtimeType) != nullptr) {
         return this.getSupertypeFromUpperBounds(superclass, ((WildcardType)this.runtimeType).getUpperBounds());
      } else {
         return superclass.isArray() ? this.getArraySupertype(superclass) : this.resolveSupertype(toGenericType(superclass).runtimeType);
      }
   }

   public const TypeToken<? : public T> getSubtype(Class<?> subclass) {
      Preconditions.checkArgument(!(this.dynamic_cast<TypeVariable*>(runtimeType) != nullptr), "Cannot get subtype of type variable <%s>", this);
      if (this.dynamic_cast<WildcardType*>(runtimeType) != nullptr) {
         return this.getSubtypeFromLowerBounds(subclass, ((WildcardType)this.runtimeType).getLowerBounds());
      } else if (this.isArray()) {
         return this.getArraySubtype(subclass);
      } else {
         Preconditions.checkArgument(this.getRawType().isAssignableFrom(subclass), "%s isn't a subclass of %s", subclass, this);
    Type resolvedTypeArgs = this.resolveTypeArgsForSubclass(subclass);
         return (TypeToken<? : public T>)of(resolvedTypeArgs);
      }
   }

    bool isSupertypeOf(TypeToken<?> type) {
      return type.isSubtypeOf(this.getType());
   }

    bool isSupertypeOf(Type type) {
    return of();
   }

    bool isSubtypeOf(TypeToken<?> type) {
      return this.isSubtypeOf(type.getType());
   }

    bool isSubtypeOf(Type supertype) {
      Preconditions.checkNotNull(supertype);
      if (dynamic_cast<WildcardType*>(supertype) != nullptr) {
    return any();
      } else if (this.dynamic_cast<WildcardType*>(runtimeType) != nullptr) {
    return any();
      } else if (!(this.dynamic_cast<TypeVariable*>(runtimeType) != nullptr)) {
         if (this.dynamic_cast<GenericArrayType*>(runtimeType) != nullptr) {
    return of();
         } else if (dynamic_cast<Class*>(supertype) != nullptr) {
            return this.someRawTypeIsSubclassOf((Class<?>)supertype);
         } else if (dynamic_cast<ParameterizedType*>(supertype) != nullptr) {
            return this.isSubtypeOfParameterizedType((ParameterizedType)supertype);
         } else {
            return dynamic_cast<GenericArrayType*>(supertype) != nullptr ? this.isSubtypeOfArrayType((GenericArrayType)supertype) : false;
         }
      } else {
         return this.runtimeType == supertype) || any(((TypeVariable)this.runtimeType).getBounds()).isSubtypeOf(supertype);
      }
   }

    bool isArray() {
      return this.getComponentType() != nullptr;
   }

    bool isPrimitive() {
      return this.dynamic_cast<Class*>(runtimeType) != nullptr && ((Class)this.runtimeType).isPrimitive();
   }

   public const TypeToken<T> wrap() {
      if (this.isPrimitive()) {
         Class<T> type = (Class<T>)this.runtimeType;
    return of();
      } else {
    return this;
      }
   }

    bool isWrapper() {
      return Primitives.allWrapperTypes().contains(this.runtimeType);
   }

   public const TypeToken<T> unwrap() {
      if (this.isWrapper()) {
         Class<T> type = (Class<T>)this.runtimeType;
    return of();
      } else {
    return this;
      }
   }

   public const TypeToken<?> getComponentType() {
    Type componentType = Types.getComponentType(this.runtimeType);
    return componentType = = nullptr ? nullptr : of(componentType);
   }

   public const Invokable<T, Object> method(Method method) {
      Preconditions.checkArgument(this.someRawTypeIsSubclassOf(method.getDeclaringClass()), "%s not declared by %s", method, this);
      return std::make_shared<1>(this, method);
   }

   public const Invokable<T, T> constructor(Constructor<?> constructor) {
      Preconditions.checkArgument(constructor.getDeclaringClass() == this.getRawType(), "%s not declared by %s", constructor, this.getRawType());
      return std::make_shared<2>(this, constructor);
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<TypeToken*>(o) != nullptr) {
         TypeToken<?> that = (TypeToken<?>)o;
         return this.runtimeType == that.runtimeType);
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.runtimeType.hashCode();
   }

    std::string toString() {
      return Types.toString(this.runtimeType);
   }

    void* writeReplace() {
    return of(std::make_shared<TypeResolver>();
   }

   const TypeToken<T> rejectTypeVariables() {
    std::make_shared<3>();
    return this;
   }

    bool someRawTypeIsSubclassOf(Class<?> superclass) {
      for (Class<?> rawType : this.getRawTypes()) {
         if (superclass.isAssignableFrom(rawType)) {
    return true;
         }
      }

    return false;
   }

    bool isSubtypeOfParameterizedType(ParameterizedType supertype) {
      Class<?> matchedClass = of(supertype).getRawType();
      if (!this.someRawTypeIsSubclassOf(matchedClass)) {
    return false;
      } else {
         Type[] typeParams = matchedClass.getTypeParameters();
         Type[] toTypeArgs = supertype.getActualTypeArguments();

         for (int i = 0; i < typeParams.length; i++) {
            if (!this.resolveType(typeParams[i]).is(toTypeArgs[i])) {
    return false;
            }
         }

         return Modifier.isStatic(((Class)supertype.getRawType()).getModifiers())
            || supertype.getOwnerType() == nullptr
            || this.isOwnedBySubtypeOf(supertype.getOwnerType());
      }
   }

    bool isSubtypeOfArrayType(GenericArrayType supertype) {
      if (this.dynamic_cast<Class*>(runtimeType) != nullptr) {
         Class<?> fromClass = (Class<?>)this.runtimeType;
         return !fromClass.isArray() ? false : of(fromClass.getComponentType()).isSubtypeOf(supertype.getGenericComponentType());
      } else if (this.dynamic_cast<GenericArrayType*>(runtimeType) != nullptr) {
    GenericArrayType fromArrayType = (GenericArrayType)this.runtimeType;
    return of();
      } else {
    return false;
      }
   }

    bool isSupertypeOfArray(GenericArrayType subtype) {
      if (this.dynamic_cast<Class*>(runtimeType) != nullptr) {
         Class<?> thisClass = (Class<?>)this.runtimeType;
         return !thisClass.isArray()
            ? thisClass.isAssignableFrom(Object[].class)
            : of(subtype.getGenericComponentType()).isSubtypeOf(thisClass.getComponentType());
      } else {
         return this.dynamic_cast<GenericArrayType*>(runtimeType) != nullptr
            ? of(subtype.getGenericComponentType()).isSubtypeOf(((GenericArrayType)this.runtimeType).getGenericComponentType())
            : false;
      }
   }

    bool is(Type formalType) {
      if (this.runtimeType == formalType)) {
    return true;
      } else {
         return !(dynamic_cast<WildcardType*>(formalType) != nullptr)
            ? false
            : every(((WildcardType)formalType).getUpperBounds()).isSupertypeOf(this.runtimeType)
               && every(((WildcardType)formalType).getLowerBounds()).isSubtypeOf(this.runtimeType);
      }
   }

    static Bounds every(Type[] bounds) {
      return std::make_shared<Bounds>(bounds, false);
   }

    static Bounds any(Type[] bounds) {
      return std::make_shared<Bounds>(bounds, true);
   }

   private ImmutableSet<Class<? super T>> getRawTypes() {
      com.google.common.collect.ImmutableSet.Builder<Class<?>> builder = ImmutableSet.builder();
    std::make_shared<4>();
      return builder.build();
   }

    bool isOwnedBySubtypeOf(Type supertype) {
      for (TypeToken<?> type : this.getTypes()) {
    Type ownerType = type.getOwnerTypeIfPresent();
         if (ownerType != nullptr && of(ownerType).isSubtypeOf(supertype)) {
    return true;
         }
      }

    return false;
   }

    Type getOwnerTypeIfPresent() {
      if (this.dynamic_cast<ParameterizedType*>(runtimeType) != nullptr) {
         return ((ParameterizedType)this.runtimeType).getOwnerType();
      } else {
         return this.dynamic_cast<Class*>(runtimeType) != nullptr ? ((Class)this.runtimeType).getEnclosingClass() : nullptr;
      }
   }

   static <T> TypeToken<? : public T> toGenericType(Class<T> cls) {
      if (cls.isArray()) {
    Type arrayOfGenericType = Types.newArrayType(toGenericType(cls.getComponentType()).runtimeType);
         return (TypeToken<? : public T>)of(arrayOfGenericType);
      } else {
         TypeVariable<Class<T>>[] typeParams = cls.getTypeParameters();
    Type ownerType = cls.isMemberClass() && !Modifier.isStatic(cls.getModifiers()) ? toGenericType(cls.getEnclosingClass()).runtimeType : nullptr;
         return typeParams.length <= 0 && (ownerType == nullptr || ownerType == cls.getEnclosingClass())
            ? of(cls)
            : of(Types.newParameterizedTypeWithOwner(ownerType, cls, typeParams));
      }
   }

   private TypeToken<? super T> getSupertypeFromUpperBounds(Class<? super T> supertype, Type[] upperBounds) {
    for (auto& upperBound : upperBounds)         TypeToken<? super T> bound = (TypeToken<? super T>)of(upperBound);
         if (bound.isSubtypeOf(supertype)) {
            return bound.getSupertype(supertype);
         }
      }

      throw IllegalArgumentException(supertype + " isn't a super type of " + this);
   }

   private TypeToken<? : public T> getSubtypeFromLowerBounds(Class<?> subclass, Type[] lowerBounds) {
      int len$ = lowerBounds.length;
      int i$ = 0;
      if (i$ < len$) {
    Type lowerBound = lowerBounds[i$];
         TypeToken<? : public T> bound = (TypeToken<? : public T>)of(lowerBound);
         return bound.getSubtype(subclass);
      } else {
         throw IllegalArgumentException(subclass + " isn't a subclass of " + this);
      }
   }

   private TypeToken<? super T> getArraySupertype(Class<? super T> supertype) {
    TypeToken componentType = (TypeToken)Preconditions.checkNotNull(this.getComponentType(), "%s isn't a super type of %s", supertype, this);
      TypeToken<?> componentSupertype = componentType.getSupertype((Class<? super T>)supertype.getComponentType());
      return (TypeToken<? super T>)of(newArrayClassOrGenericArrayType(componentSupertype.runtimeType));
   }

   private TypeToken<? : public T> getArraySubtype(Class<?> subclass) {
      TypeToken<?> componentSubtype = this.getComponentType().getSubtype(subclass.getComponentType());
      return (TypeToken<? : public T>)of(newArrayClassOrGenericArrayType(componentSubtype.runtimeType));
   }

    Type resolveTypeArgsForSubclass(Class<?> subclass) {
      if (!(this.dynamic_cast<Class*>(runtimeType) != nullptr) || subclass.getTypeParameters().length != 0 && this.getRawType().getTypeParameters().length == 0) {
         TypeToken<?> genericSubtype = toGenericType(subclass);
    Type supertypeWithArgsFromSubtype = genericSubtype.getSupertype(this.getRawType()).runtimeType;
         return std::make_unique<TypeResolver>().where(supertypeWithArgsFromSubtype, this.runtimeType).resolveType(genericSubtype.runtimeType);
      } else {
    return subclass;
      }
   }

    static Type newArrayClassOrGenericArrayType(Type componentType) {
      return JavaVersion.JAVA7.newArrayType(componentType);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
