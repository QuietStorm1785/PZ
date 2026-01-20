#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "java/text/MessageFormat.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/Locator.h"
#include "org/xml/sax/SAXParseException.h"

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class ValidationEventLocatorImpl {
public:
    URL url = nullptr;
    int offset = -1;
    int lineNumber = -1;
    int columnNumber = -1;
    void* object = nullptr;
    Node node = nullptr;

    public ValidationEventLocatorImpl() {
   }

    public ValidationEventLocatorImpl(Locator loc) {
      if (loc == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "loc"));
      } else {
         this.url = toURL(loc.getSystemId());
         this.columnNumber = loc.getColumnNumber();
         this.lineNumber = loc.getLineNumber();
      }
   }

    public ValidationEventLocatorImpl(SAXParseException e) {
      if (e == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "e"));
      } else {
         this.url = toURL(e.getSystemId());
         this.columnNumber = e.getColumnNumber();
         this.lineNumber = e.getLineNumber();
      }
   }

    public ValidationEventLocatorImpl(Node _node) {
      if (_node == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "_node"));
      } else {
         this.node = _node;
      }
   }

    public ValidationEventLocatorImpl(void* _object) {
      if (_object == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "_object"));
      } else {
         this.object = _object;
      }
   }

    static URL toURL(const std::string& systemId) {
      try {
         return std::make_shared<URL>(systemId);
      } catch (MalformedURLException var2) {
    return nullptr;
      }
   }

    URL getURL() {
      return this.url;
   }

    void setURL(URL _url) {
      this.url = _url;
   }

    int getOffset() {
      return this.offset;
   }

    void setOffset(int _offset) {
      this.offset = _offset;
   }

    int getLineNumber() {
      return this.lineNumber;
   }

    void setLineNumber(int _lineNumber) {
      this.lineNumber = _lineNumber;
   }

    int getColumnNumber() {
      return this.columnNumber;
   }

    void setColumnNumber(int _columnNumber) {
      this.columnNumber = _columnNumber;
   }

    void* getObject() {
      return this.object;
   }

    void setObject(void* _object) {
      this.object = _object;
   }

    Node getNode() {
      return this.node;
   }

    void setNode(Node _node) {
      this.node = _node;
   }

    std::string toString() {
      return MessageFormat.format(
         "[node={0},object={1},url={2},line={3},col={4},offset={5}]",
         this.getNode(),
         this.getObject(),
         this.getURL(),
         std::string.valueOf(this.getLineNumber()),
         std::string.valueOf(this.getColumnNumber()),
         std::string.valueOf(this.getOffset())
      );
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
