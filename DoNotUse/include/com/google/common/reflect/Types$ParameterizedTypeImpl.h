#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/Iterables.h"
#include "com/google/common/reflect/Types/JavaVersion.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
    const Type ownerType;
   private const ImmutableList<Type> argumentsList;
   private const Class<?> rawType;
    static const long serialVersionUID = 0L;

   Types$ParameterizedTypeImpl(@Nullable Type ownerType, Class<?> rawType, Type[] typeArguments) {
      Preconditions.checkNotNull(rawType);
      Preconditions.checkArgument(typeArguments.length == rawType.getTypeParameters().length);
      Types.access$200(typeArguments, "type parameter");
      this.ownerType = ownerType;
      this.rawType = rawType;
      this.argumentsList = JavaVersion.CURRENT.usedInGenericType(typeArguments);
   }

   public Type[] getActualTypeArguments() {
      return Types.access$300(this.argumentsList);
   }

    Type getRawType() {
      return this.rawType;
   }

    Type getOwnerType() {
      return this.ownerType;
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream();
      if (this.ownerType != nullptr) {
         builder.append(JavaVersion.CURRENT.typeName(this.ownerType)).append('.');
      }

      return builder.append(this.rawType.getName())
         .append('<')
         .append(Types.access$500().join(Iterables.transform(this.argumentsList, Types.access$400())))
         .append('>')
         ;
   }

    int hashCode() {
      return (this.ownerType == nullptr ? 0 : this.ownerType.hashCode()) ^ this.argumentsList.hashCode() ^ this.rawType.hashCode();
   }

    bool equals(void* other) {
      if (!(dynamic_cast<ParameterizedType*>(other) != nullptr)) {
    return false;
      } else {
    ParameterizedType that = (ParameterizedType)other;
         return this.getRawType() == that.getRawType())
            && Objects.equal(this.getOwnerType(), that.getOwnerType())
            && Arrays == (Object[])this.getActualTypeArguments(), (Object[])that.getActualTypeArguments());
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
