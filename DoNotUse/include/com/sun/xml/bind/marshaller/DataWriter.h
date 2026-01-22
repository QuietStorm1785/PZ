#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace marshaller {


class DataWriter : public XMLWriter {
public:
    static const void* SEEN_NOTHING = std::make_shared<Object>();
    static const void* SEEN_ELEMENT = std::make_shared<Object>();
    static const void* SEEN_DATA = std::make_shared<Object>();
    void* state = SEEN_NOTHING;
   private std::stack<Object> stateStack = std::make_unique<std::stack<>>();
    std::string indentStep = "";
    int depth = 0;

    public DataWriter(Writer writer, const std::string& encoding, CharacterEscapeHandler _escapeHandler) {
      super(writer, encoding, _escapeHandler);
   }

    public DataWriter(Writer writer, const std::string& encoding) {
      this(writer, encoding, DumbEscapeHandler.theInstance);
   }

   /** @deprecated */
    int getIndentStep() {
      return this.indentStep.length();
   }

   /** @deprecated */
    void setIndentStep(int indentStep) {
    std::stringstream buf = new std::stringstream();

      while (indentStep > 0) {
         buf.append(' ');
         indentStep--;
      }

      this.setIndentStep(buf);
   }

    void setIndentStep(const std::string& s) {
      this.indentStep = s;
   }

    void reset() {
      this.depth = 0;
      this.state = SEEN_NOTHING;
      this.stateStack = std::make_unique<std::stack<>>();
      super.reset();
   }

    void writeXmlDecl(const std::string& decl) {
      super.writeXmlDecl(decl);
      this.write('\n');
   }

    void startElement(const std::string& uri, const std::string& localName, const std::string& qName, Attributes atts) {
      this.stateStack.push(SEEN_ELEMENT);
      this.state = SEEN_NOTHING;
      if (this.depth > 0) {
         super.characters("\n");
      }

      this.doIndent();
      super.startElement(uri, localName, qName, atts);
      this.depth++;
   }

    void endElement(const std::string& uri, const std::string& localName, const std::string& qName) {
      this.depth--;
      if (this.state == SEEN_ELEMENT) {
         super.characters("\n");
         this.doIndent();
      }

      super.endElement(uri, localName, qName);
      this.state = this.stateStack.pop();
   }

    void endDocument() {
      try {
         this.write('\n');
      } catch (IOException var2) {
         throw SAXException(var2);
      }

      super.endDocument();
   }

    void characters(char[] ch, int start, int length) {
      this.state = SEEN_DATA;
      super.characters(ch, start, length);
   }

    void doIndent() {
      if (this.depth > 0) {
         char[] ch = this.indentStep.toCharArray();

         for (int i = 0; i < this.depth; i++) {
            this.characters(ch, 0, ch.length);
         }
      }
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
