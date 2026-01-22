#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlAttachmentRef.h"
#include "javax/xml/bind/annotation/XmlElementWrapper.h"
#include "javax/xml/bind/annotation/XmlID.h"
#include "javax/xml/bind/annotation/XmlIDREF.h"
#include "javax/xml/bind/annotation/XmlInlineBinaryData.h"
#include "javax/xml/bind/annotation/XmlList.h"
#include "javax/xml/bind/annotation/XmlMimeType.h"
#include "javax/xml/bind/annotation/XmlSchemaType.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


enum class ClassInfoImpl {
   JAVA_TYPE(1, XmlJavaTypeAdapter.class),
   ID_IDREF(2, XmlID.class, XmlIDREF.class),
   BINARY(4, XmlInlineBinaryData.class, XmlMimeType.class, XmlAttachmentRef.class),
   ELEMENT_WRAPPER(8, XmlElementWrapper.class),
   LIST(16, XmlList.class),
   SCHEMA_TYPE(32, XmlSchemaType.class);

    const int bitMask;
   const Class<? : public Annotation>[] members;

   private ClassInfoImpl$SecondaryAnnotation(int bitMask, Class<? : public Annotation>... members) {
      this.bitMask = bitMask;
      this.members = members;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
