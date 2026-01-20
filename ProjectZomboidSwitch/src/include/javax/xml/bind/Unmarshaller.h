#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "javax/xml/bind/Unmarshaller/Listener.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"
#include "javax/xml/stream/XMLEventReader.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/validation/Schema.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/InputSource.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {


class Unmarshaller {
public:
    virtual ~Unmarshaller() = default;
    void* unmarshal(File var1);

    void* unmarshal(InputStream var1);

    void* unmarshal(Reader var1);

    void* unmarshal(URL var1);

    void* unmarshal(InputSource var1);

    void* unmarshal(Node var1);

   <T> JAXBElement<T> unmarshal(Node var1, Class<T> var2) throws JAXBException;

    void* unmarshal(Source var1);

   <T> JAXBElement<T> unmarshal(Source var1, Class<T> var2) throws JAXBException;

    void* unmarshal(XMLStreamReader var1);

   <T> JAXBElement<T> unmarshal(XMLStreamReader var1, Class<T> var2) throws JAXBException;

    void* unmarshal(XMLEventReader var1);

   <T> JAXBElement<T> unmarshal(XMLEventReader var1, Class<T> var2) throws JAXBException;

    UnmarshallerHandler getUnmarshallerHandler();

   /** @deprecated */
    void setValidating(bool var1);

   /** @deprecated */
    bool isValidating();

    void setEventHandler(ValidationEventHandler var1);

    ValidationEventHandler getEventHandler();

    void setProperty(const std::string& var1, void* var2);

    void* getProperty(const std::string& var1);

    void setSchema(Schema var1);

    Schema getSchema();

    void setAdapter(XmlAdapter var1);

   <A : public XmlAdapter> void setAdapter(Class<A> var1, A var2);

   <A : public XmlAdapter> A getAdapter(Class<A> var1);

    void setAttachmentUnmarshaller(AttachmentUnmarshaller var1);

    AttachmentUnmarshaller getAttachmentUnmarshaller();

    void setListener(Listener var1);

    Listener getListener();
}
} // namespace bind
} // namespace xml
} // namespace javax
