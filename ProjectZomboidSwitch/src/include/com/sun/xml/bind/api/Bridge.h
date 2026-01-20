#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/v2/runtime/BridgeContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "javax/xml/stream/XMLStreamWriter.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/Source.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/ContentHandler.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {


class Bridge {
public:
    const JAXBContextImpl context;

    protected Bridge(JAXBContextImpl context) {
      this.context = context;
   }

    JAXBRIContext getContext() {
      return this.context;
   }

    void marshal(T object, XMLStreamWriter output) {
      this.marshal(object, output, nullptr);
   }

    void marshal(T object, XMLStreamWriter output, AttachmentMarshaller am) {
    Marshaller m = (Marshaller)this.context.marshallerPool.take();
      m.setAttachmentMarshaller(am);
      this.marshal(m, object, output);
      m.setAttachmentMarshaller(nullptr);
      this.context.marshallerPool.recycle(m);
   }

    void marshal(@NotNull BridgeContext, T object, XMLStreamWriter output) {
      this.marshal(((BridgeContextImpl)context).marshaller, object, output);
   }

   public abstract void marshal(@NotNull Marshaller var1, T var2, XMLStreamWriter var3) throws JAXBException;

    void marshal(T object, OutputStream output, NamespaceContext nsContext) {
      this.marshal(object, output, nsContext, nullptr);
   }

    void marshal(T object, OutputStream output, NamespaceContext nsContext, AttachmentMarshaller am) {
    Marshaller m = (Marshaller)this.context.marshallerPool.take();
      m.setAttachmentMarshaller(am);
      this.marshal(m, object, output, nsContext);
      m.setAttachmentMarshaller(nullptr);
      this.context.marshallerPool.recycle(m);
   }

    void marshal(@NotNull BridgeContext, T object, OutputStream output, NamespaceContext nsContext) {
      this.marshal(((BridgeContextImpl)context).marshaller, object, output, nsContext);
   }

   public abstract void marshal(@NotNull Marshaller var1, T var2, OutputStream var3, NamespaceContext var4) throws JAXBException;

    void marshal(T object, Node output) {
    Marshaller m = (Marshaller)this.context.marshallerPool.take();
      this.marshal(m, object, output);
      this.context.marshallerPool.recycle(m);
   }

    void marshal(@NotNull BridgeContext, T object, Node output) {
      this.marshal(((BridgeContextImpl)context).marshaller, object, output);
   }

   public abstract void marshal(@NotNull Marshaller var1, T var2, Node var3) throws JAXBException;

    void marshal(T object, ContentHandler contentHandler) {
      this.marshal(object, contentHandler, nullptr);
   }

    void marshal(T object, ContentHandler contentHandler, AttachmentMarshaller am) {
    Marshaller m = (Marshaller)this.context.marshallerPool.take();
      m.setAttachmentMarshaller(am);
      this.marshal(m, object, contentHandler);
      m.setAttachmentMarshaller(nullptr);
      this.context.marshallerPool.recycle(m);
   }

    void marshal(@NotNull BridgeContext, T object, ContentHandler contentHandler) {
      this.marshal(((BridgeContextImpl)context).marshaller, object, contentHandler);
   }

   public abstract void marshal(@NotNull Marshaller var1, T var2, ContentHandler var3) throws JAXBException;

    void marshal(T object, Result result) {
    Marshaller m = (Marshaller)this.context.marshallerPool.take();
      this.marshal(m, object, result);
      this.context.marshallerPool.recycle(m);
   }

    void marshal(@NotNull BridgeContext, T object, Result result) {
      this.marshal(((BridgeContextImpl)context).marshaller, object, result);
   }

   public abstract void marshal(@NotNull Marshaller var1, T var2, Result var3) throws JAXBException;

    T exit(T r, Unmarshaller u) {
      u.setAttachmentUnmarshaller(nullptr);
      this.context.unmarshallerPool.recycle(u);
    return r;
   }

    T unmarshal(@NotNull XMLStreamReader) {
      return this.unmarshal(in, nullptr);
   }

    T unmarshal(@NotNull XMLStreamReader, @Nullable AttachmentUnmarshaller) {
    Unmarshaller u = (Unmarshaller)this.context.unmarshallerPool.take();
      u.setAttachmentUnmarshaller(au);
      return this.exit(this.unmarshal(u, in), u);
   }

    T unmarshal(@NotNull BridgeContext, @NotNull XMLStreamReader) {
      return this.unmarshal(((BridgeContextImpl)context).unmarshaller, in);
   }

   public abstract T unmarshal(@NotNull Unmarshaller var1, @NotNull XMLStreamReader var2) throws JAXBException;

    T unmarshal(@NotNull Source) {
      return this.unmarshal(in, nullptr);
   }

    T unmarshal(@NotNull Source, @Nullable AttachmentUnmarshaller) {
    Unmarshaller u = (Unmarshaller)this.context.unmarshallerPool.take();
      u.setAttachmentUnmarshaller(au);
      return this.exit(this.unmarshal(u, in), u);
   }

    T unmarshal(@NotNull BridgeContext, @NotNull Source) {
      return this.unmarshal(((BridgeContextImpl)context).unmarshaller, in);
   }

   public abstract T unmarshal(@NotNull Unmarshaller var1, @NotNull Source var2) throws JAXBException;

    T unmarshal(@NotNull InputStream) {
    Unmarshaller u = (Unmarshaller)this.context.unmarshallerPool.take();
      return this.exit(this.unmarshal(u, in), u);
   }

    T unmarshal(@NotNull BridgeContext, @NotNull InputStream) {
      return this.unmarshal(((BridgeContextImpl)context).unmarshaller, in);
   }

   public abstract T unmarshal(@NotNull Unmarshaller var1, @NotNull InputStream var2) throws JAXBException;

    T unmarshal(@NotNull Node) {
      return this.unmarshal(n, nullptr);
   }

    T unmarshal(@NotNull Node, @Nullable AttachmentUnmarshaller) {
    Unmarshaller u = (Unmarshaller)this.context.unmarshallerPool.take();
      u.setAttachmentUnmarshaller(au);
      return this.exit(this.unmarshal(u, n), u);
   }

    T unmarshal(@NotNull BridgeContext, @NotNull Node) {
      return this.unmarshal(((BridgeContextImpl)context).unmarshaller, n);
   }

   public abstract T unmarshal(@NotNull Unmarshaller var1, @NotNull Node var2) throws JAXBException;

   public abstract TypeReference getTypeReference();
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
