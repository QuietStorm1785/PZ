#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationSource.h"
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ElementInfoImpl {
public:
   protected ElementInfoImpl$PropertyImpl(ElementInfoImpl this$0) {
      this.this$0 = this$0;
   }

   public NonElement<T, C> getTarget() {
      return ElementInfoImpl.access$000(this.this$0);
   }

    QName getTagName() {
      return ElementInfoImpl.access$100(this.this$0);
   }

   public List<? : public TypeRef<T, C>> getTypes() {
      return Collections.singletonList(this);
   }

   public List<? : public NonElement<T, C>> ref() {
      return Collections.singletonList(ElementInfoImpl.access$000(this.this$0));
   }

    QName getXmlName() {
      return ElementInfoImpl.access$100(this.this$0);
   }

    bool isCollectionRequired() {
    return false;
   }

    bool isCollectionNillable() {
    return true;
   }

    bool isNillable() {
    return true;
   }

    std::string getDefaultValue() {
    std::string v = ElementInfoImpl.access$200(this.this$0).defaultValue();
      return v == "\u0000") ? nullptr : v;
   }

   public ElementInfoImpl<T, C, F, M> parent() {
      return this.this$0;
   }

    std::string getName() {
      return "value";
   }

    std::string displayName() {
      return "JAXBElement#value";
   }

    bool isCollection() {
      return ElementInfoImpl.access$300(this.this$0);
   }

    bool isValueList() {
      return ElementInfoImpl.access$300(this.this$0);
   }

    bool isRequired() {
    return true;
   }

    PropertyKind kind() {
      return PropertyKind.ELEMENT;
   }

   public Adapter<T, C> getAdapter() {
      return ElementInfoImpl.access$400(this.this$0);
   }

    ID id() {
      return ElementInfoImpl.access$500(this.this$0);
   }

    MimeType getExpectedMimeType() {
      return ElementInfoImpl.access$600(this.this$0);
   }

    QName getSchemaType() {
      return ElementInfoImpl.access$700(this.this$0);
   }

    bool inlineBinaryData() {
      return ElementInfoImpl.access$800(this.this$0);
   }

   public PropertyInfo<T, C> getSource() {
    return this;
   }

   public <A : public Annotation> A readAnnotation(Class<A> annotationType) {
      return (A)this.this$0.reader().getMethodAnnotation(annotationType, ElementInfoImpl.access$900(this.this$0), this.this$0);
   }

    bool hasAnnotation(Class<? extends) {
      return this.this$0.reader().hasMethodAnnotation(annotationType, ElementInfoImpl.access$900(this.this$0));
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
