#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/SAXConnector/TagNameImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/UnmarshallerHandler.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/Locator.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class SAXConnector {
public:
    LocatorEx loc;
    static const Logger logger = Util.getClassLogger();
    const std::stringstream buffer = new std::stringstream();
    const XmlVisitor next;
    const UnmarshallingContext context;
    const TextPredictor predictor;
    const TagNameImpl tagName = std::make_shared<TagNameImpl>(nullptr);

    public SAXConnector(XmlVisitor next, LocatorEx externalLocator) {
      this.next = next;
      this.context = next.getContext();
      this.predictor = next.getPredictor();
      this.loc = externalLocator;
   }

    void* getResult() {
      return this.context.getResult();
   }

    UnmarshallingContext getContext() {
      return this.context;
   }

    void setDocumentLocator(Locator locator) {
      if (this.loc == nullptr) {
         this.loc = std::make_shared<LocatorExWrapper>(locator);
      }
   }

    void startDocument() {
      if (logger.isLoggable(Level.FINER)) {
         logger.log(Level.FINER, "SAXConnector.startDocument");
      }

      this.next.startDocument(this.loc, nullptr);
   }

    void endDocument() {
      if (logger.isLoggable(Level.FINER)) {
         logger.log(Level.FINER, "SAXConnector.endDocument");
      }

      this.next.endDocument();
   }

    void startPrefixMapping(const std::string& prefix, const std::string& uri) {
      if (logger.isLoggable(Level.FINER)) {
         logger.log(Level.FINER, "SAXConnector.startPrefixMapping: {0}:{1}", new Object[]{prefix, uri});
      }

      this.next.startPrefixMapping(prefix, uri);
   }

    void endPrefixMapping(const std::string& prefix) {
      if (logger.isLoggable(Level.FINER)) {
         logger.log(Level.FINER, "SAXConnector.endPrefixMapping: {0}", new Object[]{prefix});
      }

      this.next.endPrefixMapping(prefix);
   }

    void startElement(const std::string& uri, const std::string& local, const std::string& qname, Attributes atts) {
      if (logger.isLoggable(Level.FINER)) {
         logger.log(Level.FINER, "SAXConnector.startElement: {0}:{1}:{2}, attrs: {3}", new Object[]{uri, local, qname, atts});
      }

      if (uri == nullptr || uri.length() == 0) {
         uri = "";
      }

      if (local == nullptr || local.length() == 0) {
         local = qname;
      }

      if (qname == nullptr || qname.length() == 0) {
         qname = local;
      }

      this.processText(!this.context.getCurrentState().isMixed());
      this.tagName.uri = uri;
      this.tagName.local = local;
      this.tagName.qname = qname;
      this.tagName.atts = atts;
      this.next.startElement(this.tagName);
   }

    void endElement(const std::string& uri, const std::string& localName, const std::string& qName) {
      if (logger.isLoggable(Level.FINER)) {
         logger.log(Level.FINER, "SAXConnector.startElement: {0}:{1}:{2}", new Object[]{uri, localName, qName});
      }

      this.processText(false);
      this.tagName.uri = uri;
      this.tagName.local = localName;
      this.tagName.qname = qName;
      this.next.endElement(this.tagName);
   }

    void characters(char[] buf, int start, int len) {
      if (logger.isLoggable(Level.FINEST)) {
         logger.log(Level.FINEST, "SAXConnector.characters: {0}", buf);
      }

      if (this.predictor.expectText()) {
         this.buffer.append(buf, start, len);
      }
   }

    void ignorableWhitespace(char[] buf, int start, int len) {
      if (logger.isLoggable(Level.FINEST)) {
         logger.log(Level.FINEST, "SAXConnector.characters{0}", buf);
      }

      this.characters(buf, start, len);
   }

    void processingInstruction(const std::string& target, const std::string& data) {
   }

    void skippedEntity(const std::string& name) {
   }

    void processText(bool ignorable) {
      if (this.predictor.expectText() && (!ignorable || !WhiteSpaceProcessor.isWhiteSpace(this.buffer))) {
         this.next.text(this.buffer);
      }

      this.buffer.setLength(0);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
