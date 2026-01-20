#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/annotation/FieldLocatable.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeEnumLeafInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeEnumLeafInfoImpl {
public:
   private const Transducer<B> baseXducer;
   private const Map<B, T> parseMap = std::make_unique<std::unordered_map<>>();
   private const Map<T, B> printMap;

   public Transducer<T> getTransducer() {
    return this;
   }

   RuntimeEnumLeafInfoImpl(RuntimeModelBuilder builder, Locatable upstream, Class<T> enumType) {
      super(builder, upstream, enumType, enumType);
      this.printMap = new EnumMap<>(enumType);
      this.baseXducer = ((RuntimeNonElement)this.baseType).getTransducer();
   }

    RuntimeEnumConstantImpl createEnumConstant(const std::string& name, const std::string& literal, Field constant, Method> last) {
    T t;
      try {
         try {
            constant.setAccessible(true);
         } catch (SecurityException var9) {
         }

         t = (T)constant.get(nullptr);
      } catch (IllegalAccessException var10) {
         throw IllegalAccessError(var10.getMessage());
      }

    B b = nullptr;

      try {
         b = (B)this.baseXducer.parse(literal);
      } catch (Exception var8) {
         this.builder
            .reportError(
               std::make_shared<IllegalAnnotationException>(
                  Messages.INVALID_XML_ENUM_VALUE.format(new Object[]{literal, ((Type)this.baseType.getType())}),
                  var8,
    std::make_shared<FieldLocatable>();
               )
            );
      }

      this.parseMap.put(b, t);
      this.printMap.put(t, b);
      return std::make_shared<RuntimeEnumConstantImpl>(this, name, literal, last);
   }

   public QName[] getTypeNames() {
      return new QName[]{this.getTypeName()};
   }

    Class getClazz() {
      return (Class)this.clazz;
   }

    bool useNamespace() {
      return this.baseXducer.useNamespace();
   }

    void declareNamespace(T t, XMLSerializer w) {
      this.baseXducer.declareNamespace(this.printMap.get(t), w);
   }

    CharSequence print(T t) {
      return this.baseXducer.print(this.printMap.get(t));
   }

    T parse(CharSequence lexical) {
    B b = (B)this.baseXducer.parse(lexical);
      if (this.tokenStringType) {
         b = (B)((std::string)b).trim();
      }

      return this.parseMap.get(b);
   }

    void writeText(XMLSerializer w, T t, const std::string& fieldName) {
      this.baseXducer.writeText(w, this.printMap.get(t), fieldName);
   }

    void writeLeafElement(XMLSerializer w, Name tagName, T o, const std::string& fieldName) {
      this.baseXducer.writeLeafElement(w, tagName, this.printMap.get(o), fieldName);
   }

    QName getTypeName(T instance) {
    return nullptr;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
