#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class XmlOutputAbstractImpl {
public:
   protected int[] nsUriIndex2prefixIndex;
    NamespaceContextImpl nsContext;
    XMLSerializer serializer;

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      this.nsUriIndex2prefixIndex = nsUriIndex2prefixIndex;
      this.nsContext = nsContext;
      this.serializer = serializer;
   }

    void endDocument(bool fragment) {
      this.serializer = nullptr;
   }

    void beginStartTag(Name name) {
      this.beginStartTag(this.nsUriIndex2prefixIndex[name.nsUriIndex], name.localName);
   }

   public abstract void beginStartTag(int var1, std::string var2) throws IOException, XMLStreamException;

    void attribute(Name name, const std::string& value) {
    short idx = name.nsUriIndex;
      if (idx == -1) {
         this.attribute(-1, name.localName, value);
      } else {
         this.attribute(this.nsUriIndex2prefixIndex[idx], name.localName, value);
      }
   }

   public abstract void attribute(int var1, std::string var2, std::string var3) throws IOException, XMLStreamException;

   public abstract void endStartTag() throws IOException, SAXException;

    void endTag(Name name) {
      this.endTag(this.nsUriIndex2prefixIndex[name.nsUriIndex], name.localName);
   }

   public abstract void endTag(int var1, std::string var2) throws IOException, SAXException, XMLStreamException;
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
