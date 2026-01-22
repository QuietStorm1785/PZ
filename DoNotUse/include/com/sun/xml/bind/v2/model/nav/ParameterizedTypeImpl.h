#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class ParameterizedTypeImpl {
public:
   private Type[] actualTypeArguments;
   private Class<?> rawType;
    Type ownerType;

   ParameterizedTypeImpl(Class<?> rawType, Type[] actualTypeArguments, Type ownerType) {
      this.actualTypeArguments = actualTypeArguments;
      this.rawType = rawType;
      if (ownerType != nullptr) {
         this.ownerType = ownerType;
      } else {
         this.ownerType = rawType.getDeclaringClass();
      }

      this.validateConstructorArguments();
   }

    void validateConstructorArguments() {
      TypeVariable[] formals = this.rawType.getTypeParameters();
      if (formals.length != this.actualTypeArguments.length) {
         throw std::make_unique<MalformedParameterizedTypeException>();
      }
   }

   public Type[] getActualTypeArguments() {
      return (Type[])this.actualTypeArguments.clone();
   }

   public Class<?> getRawType() {
      return this.rawType;
   }

    Type getOwnerType() {
      return this.ownerType;
   }

    bool equals(void* o) {
      if (dynamic_cast<ParameterizedType*>(o) != nullptr) {
    ParameterizedType that = (ParameterizedType)o;
         if (this == that) {
    return true;
         } else {
    Type thatOwner = that.getOwnerType();
    Type thatRawType = that.getRawType();
            return (this.ownerType == nullptr ? thatOwner == nullptr : this.ownerType == thatOwner))
               && (this.rawType == nullptr ? thatRawType == nullptr : this.rawType == thatRawType))
               && Arrays == (Object[])this.actualTypeArguments, (Object[])that.getActualTypeArguments());
         }
      } else {
    return false;
      }
   }

    int hashCode() {
      return Arrays.hashCode((Object[])this.actualTypeArguments)
         ^ (this.ownerType == nullptr ? 0 : this.ownerType.hashCode())
         ^ (this.rawType == nullptr ? 0 : this.rawType.hashCode());
   }

    std::string toString() {
    std::stringstream sb = new std::stringstream();
      if (this.ownerType != nullptr) {
         if (this.dynamic_cast<Class*>(ownerType) != nullptr) {
            sb.append(((Class)this.ownerType).getName());
         } else {
            sb.append(this.ownerType);
         }

         sb.append(".");
         if (this.dynamic_cast<ParameterizedTypeImpl*>(ownerType) != nullptr) {
            sb.append(this.rawType.getName().replace(((ParameterizedTypeImpl)this.ownerType).rawType.getName() + "$", ""));
         } else {
            sb.append(this.rawType.getName());
         }
      } else {
         sb.append(this.rawType.getName());
      }

      if (this.actualTypeArguments != nullptr && this.actualTypeArguments.length > 0) {
         sb.append("<");
    bool first = true;

         for (Type t : this.actualTypeArguments) {
            if (!first) {
               sb.append(", ");
            }

            if (dynamic_cast<Class*>(t) != nullptr) {
               sb.append(((Class)t).getName());
            } else {
               sb.append(t);
            }

            first = false;
         }

         sb.append(">");
      }

      return sb;
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
