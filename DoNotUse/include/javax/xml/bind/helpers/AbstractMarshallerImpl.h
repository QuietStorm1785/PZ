#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Marshaller/Listener.h"
#include "javax/xml/bind/PropertyException.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/stream/XMLEventWriter.h"
#include "javax/xml/stream/XMLStreamWriter.h"
#include "javax/xml/transform/dom/DOMResult.h"
#include "javax/xml/transform/sax/SAXResult.h"
#include "javax/xml/transform/stream/StreamResult.h"
#include "javax/xml/validation/Schema.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/ContentHandler.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class AbstractMarshallerImpl {
public:
    ValidationEventHandler eventHandler = std::make_shared<DefaultValidationEventHandler>();
    std::string encoding = "UTF-8";
    std::string schemaLocation = nullptr;
    std::string noNSSchemaLocation = nullptr;
    bool formattedOutput = false;
    bool fragment = false;
   static std::string[] aliases = new std::string[]{
      "UTF-8",
      "UTF8",
      "UTF-16",
      "Unicode",
      "UTF-16BE",
      "UnicodeBigUnmarked",
      "UTF-16LE",
      "UnicodeLittleUnmarked",
      "US-ASCII",
      "ASCII",
      "TIS-620",
      "TIS620",
      "ISO-10646-UCS-2",
      "Unicode",
      "EBCDIC-CP-US",
      "cp037",
      "EBCDIC-CP-CA",
      "cp037",
      "EBCDIC-CP-NL",
      "cp037",
      "EBCDIC-CP-WT",
      "cp037",
      "EBCDIC-CP-DK",
      "cp277",
      "EBCDIC-CP-NO",
      "cp277",
      "EBCDIC-CP-FI",
      "cp278",
      "EBCDIC-CP-SE",
      "cp278",
      "EBCDIC-CP-IT",
      "cp280",
      "EBCDIC-CP-ES",
      "cp284",
      "EBCDIC-CP-GB",
      "cp285",
      "EBCDIC-CP-FR",
      "cp297",
      "EBCDIC-CP-AR1",
      "cp420",
      "EBCDIC-CP-HE",
      "cp424",
      "EBCDIC-CP-BE",
      "cp500",
      "EBCDIC-CP-CH",
      "cp500",
      "EBCDIC-CP-ROECE",
      "cp870",
      "EBCDIC-CP-YU",
      "cp870",
      "EBCDIC-CP-IS",
      "cp871",
      "EBCDIC-CP-AR2",
      "cp918"
   };

    void marshal(void* obj, OutputStream os) {
      this.checkNotNull(obj, "obj", os, "os");
      this.marshal(obj, std::make_shared<StreamResult>(os));
   }

    void marshal(void* jaxbElement, File output) {
      this.checkNotNull(jaxbElement, "jaxbElement", output, "output");

      try {
    OutputStream os = std::make_shared<BufferedOutputStream>(std::make_shared<FileOutputStream>(output));

         try {
            this.marshal(jaxbElement, std::make_shared<StreamResult>(os));
         } finally {
            os.close();
         }
      } catch (IOException var8) {
         throw JAXBException(var8);
      }
   }

    void marshal(void* obj, Writer w) {
      this.checkNotNull(obj, "obj", w, "writer");
      this.marshal(obj, std::make_shared<StreamResult>(w));
   }

    void marshal(void* obj, ContentHandler handler) {
      this.checkNotNull(obj, "obj", handler, "handler");
      this.marshal(obj, std::make_shared<SAXResult>(handler));
   }

    void marshal(void* obj, Node node) {
      this.checkNotNull(obj, "obj", node, "node");
      this.marshal(obj, std::make_shared<DOMResult>(node));
   }

    Node getNode(void* obj) {
      this.checkNotNull(obj, "obj", bool.TRUE, "foo");
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string getEncoding() {
      return this.encoding;
   }

    void setEncoding(const std::string& encoding) {
      this.encoding = encoding;
   }

    std::string getSchemaLocation() {
      return this.schemaLocation;
   }

    void setSchemaLocation(const std::string& location) {
      this.schemaLocation = location;
   }

    std::string getNoNSSchemaLocation() {
      return this.noNSSchemaLocation;
   }

    void setNoNSSchemaLocation(const std::string& location) {
      this.noNSSchemaLocation = location;
   }

    bool isFormattedOutput() {
      return this.formattedOutput;
   }

    void setFormattedOutput(bool v) {
      this.formattedOutput = v;
   }

    bool isFragment() {
      return this.fragment;
   }

    void setFragment(bool v) {
      this.fragment = v;
   }

    std::string getJavaEncoding(const std::string& encoding) {
      try {
         "1".getBytes(encoding);
    return encoding;
      } catch (UnsupportedEncodingException var4) {
         for (int i = 0; i < aliases.length; i += 2) {
            if (encoding == aliases[i])) {
               "1".getBytes(aliases[i + 1]);
               return aliases[i + 1];
            }
         }

         throw UnsupportedEncodingException(encoding);
      }
   }

    void setProperty(const std::string& name, void* value) {
      if (name == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "name"));
      } else if ("jaxb.encoding" == name)) {
         this.checkString(name, value);
         this.setEncoding((std::string)value);
      } else if ("jaxb.formatted.output" == name)) {
         this.checkBoolean(name, value);
         this.setFormattedOutput((bool)value);
      } else if ("jaxb.noNamespaceSchemaLocation" == name)) {
         this.checkString(name, value);
         this.setNoNSSchemaLocation((std::string)value);
      } else if ("jaxb.schemaLocation" == name)) {
         this.checkString(name, value);
         this.setSchemaLocation((std::string)value);
      } else if ("jaxb.fragment" == name)) {
         this.checkBoolean(name, value);
         this.setFragment((bool)value);
      } else {
         throw PropertyException(name, value);
      }
   }

    void* getProperty(const std::string& name) {
      if (name == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "name"));
      } else if ("jaxb.encoding" == name)) {
         return this.getEncoding();
      } else if ("jaxb.formatted.output" == name)) {
         return this.isFormattedOutput() ? bool.TRUE : bool.FALSE;
      } else if ("jaxb.noNamespaceSchemaLocation" == name)) {
         return this.getNoNSSchemaLocation();
      } else if ("jaxb.schemaLocation" == name)) {
         return this.getSchemaLocation();
      } else if ("jaxb.fragment" == name)) {
         return this.isFragment() ? bool.TRUE : bool.FALSE;
      } else {
         throw PropertyException(name);
      }
   }

    ValidationEventHandler getEventHandler() {
      return this.eventHandler;
   }

    void setEventHandler(ValidationEventHandler handler) {
      if (handler == nullptr) {
         this.eventHandler = std::make_unique<DefaultValidationEventHandler>();
      } else {
         this.eventHandler = handler;
      }
   }

    void checkBoolean(const std::string& name, void* value) {
      if (!(dynamic_cast<bool*>(value) != nullptr)) {
         throw PropertyException(Messages.format("AbstractMarshallerImpl.MustBeBoolean", name));
      }
   }

    void checkString(const std::string& name, void* value) {
      if (!(dynamic_cast<std*>(value) != nullptr::string)) {
         throw PropertyException(Messages.format("AbstractMarshallerImpl.MustBeString", name));
      }
   }

    void checkNotNull(void* o1, const std::string& o1Name, void* o2, const std::string& o2Name) {
      if (o1 == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", o1Name));
      } else if (o2 == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", o2Name));
      }
   }

    void marshal(void* obj, XMLEventWriter writer) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void marshal(void* obj, XMLStreamWriter writer) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setSchema(Schema schema) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Schema getSchema() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setAdapter(XmlAdapter adapter) {
      if (adapter == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.setAdapter(adapter.getClass(), adapter);
      }
   }

   public <A : public XmlAdapter> void setAdapter(Class<A> type, A adapter) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <A : public XmlAdapter> A getAdapter(Class<A> type) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setAttachmentMarshaller(AttachmentMarshaller am) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    AttachmentMarshaller getAttachmentMarshaller() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setListener(Listener listener) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Listener getListener() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
