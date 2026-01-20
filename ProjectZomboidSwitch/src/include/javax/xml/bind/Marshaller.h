#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/Marshaller/Listener.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/stream/XMLEventWriter.h"
#include "javax/xml/stream/XMLStreamWriter.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/validation/Schema.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/ContentHandler.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class Marshaller {
public:
    virtual ~Marshaller() = default;
    std::string JAXB_ENCODING = "jaxb.encoding";
    std::string JAXB_FORMATTED_OUTPUT = "jaxb.formatted.output";
    std::string JAXB_SCHEMA_LOCATION = "jaxb.schemaLocation";
    std::string JAXB_NO_NAMESPACE_SCHEMA_LOCATION = "jaxb.noNamespaceSchemaLocation";
    std::string JAXB_FRAGMENT = "jaxb.fragment";

    void marshal(void* var1, Result var2);

    void marshal(void* var1, OutputStream var2);

    void marshal(void* var1, File var2);

    void marshal(void* var1, Writer var2);

    void marshal(void* var1, ContentHandler var2);

    void marshal(void* var1, Node var2);

    void marshal(void* var1, XMLStreamWriter var2);

    void marshal(void* var1, XMLEventWriter var2);

    Node getNode(void* var1);

    void setProperty(const std::string& var1, void* var2);

    void* getProperty(const std::string& var1);

    void setEventHandler(ValidationEventHandler var1);

    ValidationEventHandler getEventHandler();

    void setAdapter(XmlAdapter var1);

   <A : public XmlAdapter> void setAdapter(Class<A> var1, A var2);

   <A : public XmlAdapter> A getAdapter(Class<A> var1);

    void setAttachmentMarshaller(AttachmentMarshaller var1);

    AttachmentMarshaller getAttachmentMarshaller();

    void setSchema(Schema var1);

    Schema getSchema();

    void setListener(Listener var1);

    Listener getListener();
}
} // namespace bind
} // namespace xml
} // namespace javax
