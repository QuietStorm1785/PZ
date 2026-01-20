#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/CharacterEscapeHandler.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
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


class IndentingUTF8XmlOutput : public UTF8XmlOutput {
public:
    const Encoded indent8;
    const int unitLen;
    int depth = 0;
    bool seenText = false;

    public IndentingUTF8XmlOutput(OutputStream out, const std::string& indentStr, Encoded[] localNames, CharacterEscapeHandler escapeHandler) {
      super(out, localNames, escapeHandler);
      if (indentStr != nullptr) {
    Encoded e = std::make_shared<Encoded>(indentStr);
         this.indent8 = std::make_unique<Encoded>();
         this.indent8.ensureSize(e.len * 8);
         this.unitLen = e.len;

         for (int i = 0; i < 8; i++) {
            System.arraycopy(e.buf, 0, this.indent8.buf, this.unitLen * i, this.unitLen);
         }
      } else {
         this.indent8 = nullptr;
         this.unitLen = 0;
      }
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.indentStartTag();
      super.beginStartTag(prefix, localName);
   }

    void beginStartTag(Name name) {
      this.indentStartTag();
      super.beginStartTag(name);
   }

    void indentStartTag() {
      this.closeStartTag();
      if (!this.seenText) {
         this.printIndent();
      }

      this.depth++;
      this.seenText = false;
   }

    void endTag(Name name) {
      this.indentEndTag();
      super.endTag(name);
   }

    void endTag(int prefix, const std::string& localName) {
      this.indentEndTag();
      super.endTag(prefix, localName);
   }

    void indentEndTag() {
      this.depth--;
      if (!this.closeStartTagPending && !this.seenText) {
         this.printIndent();
      }

      this.seenText = false;
   }

    void printIndent() {
      this.write(10);
    int i = this.depth % 8;
      this.write(this.indent8.buf, 0, i * this.unitLen);

      for (int var2 = i >> 3; var2 > 0; var2--) {
         this.indent8.write(this);
      }
   }

    void text(const std::string& value, bool needSP) {
      this.seenText = true;
      super.text(value, needSP);
   }

    void text(Pcdata value, bool needSP) {
      this.seenText = true;
      super.text(value, needSP);
   }

    void endDocument(bool fragment) {
      this.write(10);
      super.endDocument(fragment);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
