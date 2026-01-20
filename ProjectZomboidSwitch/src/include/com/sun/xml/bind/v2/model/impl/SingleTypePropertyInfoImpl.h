#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeClassInfoImpl/RuntimePropertySeed.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElementRef.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "javax/xml/bind/annotation/XmlList.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class SingleTypePropertyInfoImpl {
public:
   private NonElement<T, C> type;
    const Accessor acc;
    Transducer xducer;

    public SingleTypePropertyInfoImpl(M> classInfo, M> seed) {
      super(classInfo, seed);
      if (dynamic_cast<RuntimePropertyInfo*>(this) != nullptr) {
    Accessor rawAcc = ((RuntimePropertySeed)seed).getAccessor();
         if (this.getAdapter() != nullptr && !this.isCollection()) {
            rawAcc = rawAcc.adapt(((RuntimePropertyInfo)this).getAdapter());
         }

         this.acc = rawAcc;
      } else {
         this.acc = nullptr;
      }
   }

   public List<? : public NonElement<T, C>> ref() {
      return Collections.singletonList(this.getTarget());
   }

   public NonElement<T, C> getTarget() {
      if (this.type == nullptr) {
         assert this.parent.builder != nullptr : "this method must be called during the build stage";

         this.type = this.parent.builder.getTypeInfo(this.getIndividualType(), this);
      }

      return this.type;
   }

   public PropertyInfo<T, C> getSource() {
    return this;
   }

    void link() {
      super.link();
      if (!NonElement.ANYTYPE_NAME == this.type.getTypeName()) && !this.type.isSimpleType() && this.id() != ID.IDREF) {
         this.parent.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.SIMPLE_TYPE_IS_REQUIRED.format(new Object[0]), this.seed));
      }

      if (!this.isCollection() && this.seed.hasAnnotation(XmlList.class)) {
         this.parent.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.XMLLIST_ON_SINGLE_PROPERTY.format(new Object[0]), this));
      }
   }

    Accessor getAccessor() {
      return this.acc;
   }

    Transducer getTransducer() {
      if (this.xducer == nullptr) {
         this.xducer = RuntimeModelBuilder.createTransducer((RuntimeNonElementRef)this);
         if (this.xducer == nullptr) {
            this.xducer = RuntimeBuiltinLeafInfoImpl.STRING;
         }
      }

      return this.xducer;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
