#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBException.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/DTDHandler.h"
#include "org/xml/sax/EntityResolver.h"
#include "org/xml/sax/ErrorHandler.h"
#include "org/xml/sax/InputSource.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/SAXNotRecognizedException.h"
#include "org/xml/sax/SAXParseException.h"
#include "org/xml/sax/XMLFilter.h"
#include "org/xml/sax/XMLReader.h"
#include "org/xml/sax/ext/LexicalHandler.h"
#include "org/xml/sax/helpers/XMLFilterImpl.h"

namespace javax {
namespace xml {
namespace bind {
namespace util {


class JAXBSource {
public:
    LexicalHandler lexicalHandler;
    EntityResolver entityResolver;
    DTDHandler dtdHandler;
    XMLFilter repeater;
    ErrorHandler errorHandler;

   JAXBSource$1(JAXBSource this$0) {
      this.this$0 = this$0;
      this.repeater = std::make_unique<XMLFilterImpl>();
   }

    bool getFeature(const std::string& name) {
      if (name == "http://xml.org/sax/features/namespaces")) {
    return true;
      } else if (name == "http://xml.org/sax/features/namespace-prefixes")) {
    return false;
      } else {
         throw SAXNotRecognizedException(name);
      }
   }

    void setFeature(const std::string& name, bool value) {
      if (!name == "http://xml.org/sax/features/namespaces") || !value) {
         if (!name == "http://xml.org/sax/features/namespace-prefixes") || value) {
            throw SAXNotRecognizedException(name);
         }
      }
   }

    void* getProperty(const std::string& name) {
      if ("http://xml.org/sax/properties/lexical-handler" == name)) {
         return this.lexicalHandler;
      } else {
         throw SAXNotRecognizedException(name);
      }
   }

    void setProperty(const std::string& name, void* value) {
      if ("http://xml.org/sax/properties/lexical-handler" == name)) {
         this.lexicalHandler = (LexicalHandler)value;
      } else {
         throw SAXNotRecognizedException(name);
      }
   }

    void setEntityResolver(EntityResolver resolver) {
      this.entityResolver = resolver;
   }

    EntityResolver getEntityResolver() {
      return this.entityResolver;
   }

    void setDTDHandler(DTDHandler handler) {
      this.dtdHandler = handler;
   }

    DTDHandler getDTDHandler() {
      return this.dtdHandler;
   }

    void setContentHandler(ContentHandler handler) {
      this.repeater.setContentHandler(handler);
   }

    ContentHandler getContentHandler() {
      return this.repeater.getContentHandler();
   }

    void setErrorHandler(ErrorHandler handler) {
      this.errorHandler = handler;
   }

    ErrorHandler getErrorHandler() {
      return this.errorHandler;
   }

    void parse(InputSource input) {
      this.parse();
   }

    void parse(const std::string& systemId) {
      this.parse();
   }

    void parse() {
      try {
         JAXBSource.access$100(this.this$0).marshal(JAXBSource.access$000(this.this$0), (XMLFilterImpl)this.repeater);
      } catch (JAXBException var3) {
    SAXParseException se = std::make_shared<SAXParseException>(var3.getMessage(), nullptr, nullptr, -1, -1, var3);
         if (this.errorHandler != nullptr) {
            this.errorHandler.fatalError(se);
         }

    throw se;
      }
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace javax
