#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/annotation/AnnotationSource.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "javax/activation/MimeType.h"
#include "javax/activation/MimeTypeParseException.h"
#include "javax/xml/bind/annotation/XmlMimeType.h"
#include "javax/xml/bind/annotation/XmlSchemaType.h"
#include "javax/xml/bind/annotation/XmlSchemaTypes.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class Util {
public:
   static <T, C, F, M> QName calcSchemaType(
      AnnotationReader<T, C, F, M> reader, AnnotationSource primarySource, C enclosingClass, T individualType, Locatable src
   ) {
    XmlSchemaType xst = (XmlSchemaType)primarySource.readAnnotation(XmlSchemaType.class);
      if (xst != nullptr) {
         return std::make_shared<QName>(xst.namespace(), xst.name());
      } else {
    XmlSchemaTypes xsts = (XmlSchemaTypes)reader.getPackageAnnotation(XmlSchemaTypes.class, enclosingClass, src);
         XmlSchemaType[] values = nullptr;
         if (xsts != nullptr) {
            values = xsts.value();
         } else {
            xst = (XmlSchemaType)reader.getPackageAnnotation(XmlSchemaType.class, enclosingClass, src);
            if (xst != nullptr) {
               values = new XmlSchemaType[]{xst};
            }
         }

         if (values != nullptr) {
    for (auto& item : values)               if (reader.getClassValue(item, "type") == individualType)) {
                  return std::make_shared<QName>(item.namespace(), item.name());
               }
            }
         }

    return nullptr;
      }
   }

    static MimeType calcExpectedMediaType(AnnotationSource primarySource, ModelBuilder builder) {
    XmlMimeType xmt = (XmlMimeType)primarySource.readAnnotation(XmlMimeType.class);
      if (xmt == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<MimeType>(xmt.value());
         } catch (MimeTypeParseException var4) {
            builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.ILLEGAL_MIME_TYPE.format(new Object[]{xmt.value(), var4.getMessage()}), xmt));
    return nullptr;
         }
      }
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
