#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/MapPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "javax/xml/bind/annotation/XmlElementWrapper.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class MapPropertyInfoImpl {
public:
    const QName xmlName;
    bool nil;
    const T keyType;
    const T valueType;
   private NonElement<T, C> keyTypeInfo;
   private NonElement<T, C> valueTypeInfo;

    public MapPropertyInfoImpl(M> ci, M> seed) {
      super(ci, seed);
    XmlElementWrapper xe = (XmlElementWrapper)seed.readAnnotation(XmlElementWrapper.class);
      this.xmlName = this.calcXmlName(xe);
      this.nil = xe != nullptr && xe.nillable();
    T raw = (T)this.getRawType();
    T bt = (T)this.nav().getBaseClass(raw, this.nav().asDecl(Map.class));

      assert bt != nullptr;

      if (this.nav().isParameterizedType(bt)) {
         this.keyType = (T)this.nav().getTypeArgument(bt, 0);
         this.valueType = (T)this.nav().getTypeArgument(bt, 1);
      } else {
         this.keyType = this.valueType = (T)this.nav().ref(Object.class);
      }
   }

   public Collection<? : public TypeInfo<T, C>> ref() {
      return Arrays.asList(this.getKeyType(), this.getValueType());
   }

    PropertyKind kind() {
      return PropertyKind.MAP;
   }

    QName getXmlName() {
      return this.xmlName;
   }

    bool isCollectionNillable() {
      return this.nil;
   }

   public NonElement<T, C> getKeyType() {
      if (this.keyTypeInfo == nullptr) {
         this.keyTypeInfo = this.getTarget(this.keyType);
      }

      return this.keyTypeInfo;
   }

   public NonElement<T, C> getValueType() {
      if (this.valueTypeInfo == nullptr) {
         this.valueTypeInfo = this.getTarget(this.valueType);
      }

      return this.valueTypeInfo;
   }

   public NonElement<T, C> getTarget(T type) {
      assert this.parent.builder != nullptr : "this method must be called during the build stage";

      return this.parent.builder.getTypeInfo(type, this);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
