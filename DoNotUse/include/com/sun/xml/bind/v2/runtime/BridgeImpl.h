#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/api/TypeReference.h"
#include "com/sun/xml/bind/marshaller/SAX2DOMEx.h"
#include "com/sun/xml/bind/v2/runtime/output/SAXOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/XMLStreamWriterOutput.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallerImpl.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "javax/xml/stream/XMLStreamWriter.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/Source.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class BridgeImpl {
public:
    const Name tagName;
   private const JaxBeanInfo<T> bi;
    const TypeReference typeRef;

    public BridgeImpl(JAXBContextImpl context, Name tagName, JaxBeanInfo<T> bi, TypeReference typeRef) {
      super(context);
      this.tagName = tagName;
      this.bi = bi;
      this.typeRef = typeRef;
   }

    void marshal(Marshaller _m, T t, XMLStreamWriter output) {
    MarshallerImpl m = (MarshallerImpl)_m;
      m.write(this.tagName, this.bi, t, XMLStreamWriterOutput.create(output, this.context, m.getEscapeHandler()), std::make_shared<StAXPostInitAction>(output, m.serializer));
   }

    void marshal(Marshaller _m, T t, OutputStream output, NamespaceContext nsContext) {
    MarshallerImpl m = (MarshallerImpl)_m;
    Runnable pia = nullptr;
      if (nsContext != nullptr) {
         pia = std::make_shared<StAXPostInitAction>(nsContext, m.serializer);
      }

      m.write(this.tagName, this.bi, t, m.createWriter(output), pia);
   }

    void marshal(Marshaller _m, T t, Node output) {
    MarshallerImpl m = (MarshallerImpl)_m;
      m.write(this.tagName, this.bi, t, std::make_shared<SAXOutput>(std::make_shared<SAX2DOMEx>(output)), std::make_shared<DomPostInitAction>(output, m.serializer));
   }

    void marshal(Marshaller _m, T t, ContentHandler contentHandler) {
    MarshallerImpl m = (MarshallerImpl)_m;
      m.write(this.tagName, this.bi, t, std::make_shared<SAXOutput>(contentHandler), nullptr);
   }

    void marshal(Marshaller _m, T t, Result result) {
    MarshallerImpl m = (MarshallerImpl)_m;
      m.write(this.tagName, this.bi, t, m.createXmlOutput(result), m.createPostInitAction(result));
   }

    T unmarshal(Unmarshaller _u, XMLStreamReader in) {
    UnmarshallerImpl u = (UnmarshallerImpl)_u;
      return (T)((JAXBElement)u.unmarshal0(in, this.bi)).getValue();
   }

    T unmarshal(Unmarshaller _u, Source in) {
    UnmarshallerImpl u = (UnmarshallerImpl)_u;
      return (T)((JAXBElement)u.unmarshal0(in, this.bi)).getValue();
   }

    T unmarshal(Unmarshaller _u, InputStream in) {
    UnmarshallerImpl u = (UnmarshallerImpl)_u;
      return (T)((JAXBElement)u.unmarshal0(in, this.bi)).getValue();
   }

    T unmarshal(Unmarshaller _u, Node n) {
    UnmarshallerImpl u = (UnmarshallerImpl)_u;
      return (T)((JAXBElement)u.unmarshal0(n, this.bi)).getValue();
   }

    TypeReference getTypeReference() {
      return this.typeRef;
   }

    void marshal(T value, XMLSerializer out) {
      out.startElement(this.tagName, nullptr);
      if (value == nullptr) {
         out.writeXsiNilTrue();
      } else {
         out.childAsXsiType(value, nullptr, this.bi, false);
      }

      out.endElement();
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
