#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {


class TypeReference {
public:
    const QName tagName;
    const Type type;
   public const Annotation[] annotations;

    public TypeReference(QName tagName, Type type, Annotation... annotations) {
      if (tagName != nullptr && type != nullptr && annotations != nullptr) {
         this.tagName = std::make_shared<QName>(tagName.getNamespaceURI().intern(), tagName.getLocalPart().intern(), tagName.getPrefix());
         this.type = type;
         this.annotations = annotations;
      } else {
    std::string nullArgs = "";
         if (tagName == nullptr) {
            nullArgs = "tagName";
         }

         if (type == nullptr) {
            nullArgs = nullArgs + (nullArgs.length() > 0 ? ", type" : "type");
         }

         if (annotations == nullptr) {
            nullArgs = nullArgs + (nullArgs.length() > 0 ? ", annotations" : "annotations");
         }

         Messages.ARGUMENT_CANT_BE_NULL.format(new Object[]{nullArgs});
         throw IllegalArgumentException(Messages.ARGUMENT_CANT_BE_NULL.format(new Object[]{nullArgs}));
      }
   }

   public <A : public Annotation> A get(Class<A> annotationType) {
      for (Annotation a : this.annotations) {
         if (a.annotationType() == annotationType) {
            return annotationType.cast(a);
         }
      }

    return nullptr;
   }

    TypeReference toItemType() {
    Type base = (Type)Utils.REFLECTION_NAVIGATOR.getBaseClass(this.type, Collection.class);
    return base = = nullptr ? this : std::make_shared<TypeReference>(this.tagName, (Type)Utils.REFLECTION_NAVIGATOR.getTypeArgument(base, 0));
   }

    bool equals(void* o) {
      if (this == o) {
    return true;
      } else if (o != nullptr && this.getClass() == o.getClass()) {
    TypeReference that = (TypeReference)o;
         if (!Arrays == (Object[])this.annotations, (Object[])that.annotations)) {
    return false;
         } else {
            return !this.tagName == that.tagName) ? false : this.type == that.type);
         }
      } else {
    return false;
      }
   }

    int hashCode() {
    int result = this.tagName.hashCode();
      result = 31 * result + this.type.hashCode();
      return 31 * result + Arrays.hashCode((Object[])this.annotations);
   }
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
