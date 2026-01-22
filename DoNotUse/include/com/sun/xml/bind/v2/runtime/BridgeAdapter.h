#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/api/TypeReference.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallerImpl.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/MarshalException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/UnmarshalException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
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


class BridgeAdapter {
public:
   private const InternalBridge<OnWire> core;
   private const Class<? : public XmlAdapter<OnWire, InMemory>> adapter;

    public BridgeAdapter(InternalBridge<OnWire> core, Class<? extends, InMemory>> adapter) {
      super(core.getContext());
      this.core = core;
      this.adapter = adapter;
   }

    void marshal(Marshaller m, InMemory inMemory, XMLStreamWriter output) {
      this.core.marshal(m, this.adaptM(m, inMemory), output);
   }

    void marshal(Marshaller m, InMemory inMemory, OutputStream output, NamespaceContext nsc) {
      this.core.marshal(m, this.adaptM(m, inMemory), output, nsc);
   }

    void marshal(Marshaller m, InMemory inMemory, Node output) {
      this.core.marshal(m, this.adaptM(m, inMemory), output);
   }

    void marshal(Marshaller context, InMemory inMemory, ContentHandler contentHandler) {
      this.core.marshal(context, this.adaptM(context, inMemory), contentHandler);
   }

    void marshal(Marshaller context, InMemory inMemory, Result result) {
      this.core.marshal(context, this.adaptM(context, inMemory), result);
   }

    OnWire adaptM(Marshaller m, InMemory v) {
    XMLSerializer serializer = ((MarshallerImpl)m).serializer;
      serializer.pushCoordinator();

    void* var4;
      try {
         var4 = this._adaptM(serializer, v);
      } finally {
         serializer.popCoordinator();
      }

      return (OnWire)var4;
   }

    OnWire _adaptM(XMLSerializer serializer, InMemory v) {
      XmlAdapter<OnWire, InMemory> a = serializer.getAdapter(this.adapter);

      try {
         return (OnWire)a.marshal(v);
      } catch (Exception var5) {
         serializer.handleError(var5, v, nullptr);
         throw MarshalException(var5);
      }
   }

    InMemory unmarshal(Unmarshaller u, XMLStreamReader in) {
      return this.adaptU(u, (OnWire)this.core.unmarshal(u, in));
   }

    InMemory unmarshal(Unmarshaller u, Source in) {
      return this.adaptU(u, (OnWire)this.core.unmarshal(u, in));
   }

    InMemory unmarshal(Unmarshaller u, InputStream in) {
      return this.adaptU(u, (OnWire)this.core.unmarshal(u, in));
   }

    InMemory unmarshal(Unmarshaller u, Node n) {
      return this.adaptU(u, (OnWire)this.core.unmarshal(u, n));
   }

    TypeReference getTypeReference() {
      return this.core.getTypeReference();
   }

    InMemory adaptU(Unmarshaller _u, OnWire v) {
    UnmarshallerImpl u = (UnmarshallerImpl)_u;
      XmlAdapter<OnWire, InMemory> a = u.coordinator.getAdapter(this.adapter);
      u.coordinator.pushCoordinator();

    void* e;
      try {
         e = a.unmarshal(v);
      } catch (Exception var9) {
         throw UnmarshalException(var9);
      } finally {
         u.coordinator.popCoordinator();
      }

      return (InMemory)e;
   }

    void marshal(InMemory o, XMLSerializer out) {
      try {
         this.core.marshal(this._adaptM(XMLSerializer.getInstance(), o), out);
      } catch (MarshalException var4) {
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
