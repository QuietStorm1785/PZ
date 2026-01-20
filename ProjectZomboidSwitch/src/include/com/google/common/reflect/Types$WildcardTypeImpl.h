#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/reflect/Types/JavaVersion.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
   private const ImmutableList<Type> lowerBounds;
   private const ImmutableList<Type> upperBounds;
    static const long serialVersionUID = 0L;

   Types$WildcardTypeImpl(Type[] lowerBounds, Type[] upperBounds) {
      Types.access$200(lowerBounds, "lower bound for wildcard");
      Types.access$200(upperBounds, "upper bound for wildcard");
      this.lowerBounds = JavaVersion.CURRENT.usedInGenericType(lowerBounds);
      this.upperBounds = JavaVersion.CURRENT.usedInGenericType(upperBounds);
   }

   public Type[] getLowerBounds() {
      return Types.access$300(this.lowerBounds);
   }

   public Type[] getUpperBounds() {
      return Types.access$300(this.upperBounds);
   }

    bool equals(void* obj) {
      if (!(dynamic_cast<WildcardType*>(obj) != nullptr)) {
    return false;
      } else {
    WildcardType that = (WildcardType)obj;
         return this.lowerBounds == Arrays.asList(that.getLowerBounds())) && this.upperBounds == Arrays.asList(that.getUpperBounds()));
      }
   }

    int hashCode() {
      return this.lowerBounds.hashCode() ^ this.upperBounds.hashCode();
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream("?");

      for (Type lowerBound : this.lowerBounds) {
         builder.append(" super ").append(JavaVersion.CURRENT.typeName(lowerBound));
      }

      for (Type upperBound : Types.access$700(this.upperBounds)) {
         builder.append(" : public ").append(JavaVersion.CURRENT.typeName(upperBound));
      }

      return builder;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
