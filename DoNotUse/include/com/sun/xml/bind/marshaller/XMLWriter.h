#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/AttributesImpl.h"
#include "org/xml/sax/helpers/XMLFilterImpl.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace marshaller {


class XMLWriter : public XMLFilterImpl {
public:
   private const std::unordered_map<std::string, std::string> locallyDeclaredPrefix = std::make_unique<std::unordered_map<>>();
    const Attributes EMPTY_ATTS = std::make_shared<AttributesImpl>();
    int elementLevel = 0;
    Writer output;
    std::string encoding;
    bool writeXmlDecl = true;
    std::string header = nullptr;
    const CharacterEscapeHandler escapeHandler;
    bool startTagIsClosed = true;

    public XMLWriter(Writer writer, const std::string& encoding, CharacterEscapeHandler _escapeHandler) {
      this.init(writer, encoding);
      this.escapeHandler = _escapeHandler;
   }

    public XMLWriter(Writer writer, const std::string& encoding) {
      this(writer, encoding, DumbEscapeHandler.theInstance);
   }

    void init(Writer writer, const std::string& encoding) {
      this.setOutput(writer, encoding);
   }

    void reset() {
      this.elementLevel = 0;
      this.startTagIsClosed = true;
   }

    void flush() {
      this.output.flush();
   }

    void setOutput(Writer writer, const std::string& _encoding) {
      if (writer == nullptr) {
         this.output = std::make_shared<OutputStreamWriter>(System.out);
      } else {
         this.output = writer;
      }

      this.encoding = _encoding;
   }

    void setXmlDecl(bool _writeXmlDecl) {
      this.writeXmlDecl = _writeXmlDecl;
   }

    void setHeader(const std::string& _header) {
      this.header = _header;
   }

    void startPrefixMapping(const std::string& prefix, const std::string& uri) {
      this.locallyDeclaredPrefix.put(prefix, uri);
   }

    void startDocument() {
      try {
         this.reset();
         if (this.writeXmlDecl) {
    std::string e = "";
            if (this.encoding != nullptr) {
               e = " encoding=\"" + this.encoding + '"';
            }

            this.writeXmlDecl("<?xml version=\"1.0\"" + e + " standalone=\"yes\"?>");
         }

         if (this.header != nullptr) {
            this.write(this.header);
         }

         super.startDocument();
      } catch (IOException var2) {
         throw SAXException(var2);
      }
   }

    void writeXmlDecl(const std::string& decl) {
      this.write(decl);
   }

    void endDocument() {
      try {
         super.endDocument();
         this.flush();
      } catch (IOException var2) {
         throw SAXException(var2);
      }
   }

    void startElement(const std::string& uri, const std::string& localName, const std::string& qName, Attributes atts) {
      try {
         if (!this.startTagIsClosed) {
            this.write(">");
         }

         this.elementLevel++;
         this.write('<');
         this.write(qName);
         this.writeAttributes(atts);
         if (!this.locallyDeclaredPrefix.empty()) {
            for (Entry<std::string, std::string> e : this.locallyDeclaredPrefix.entrySet()) {
    std::string p = e.getKey();
    std::string u = e.getValue();
               if (u == nullptr) {
                  u = "";
               }

               this.write(' ');
               if ("" == p)) {
                  this.write("xmlns=\"");
               } else {
                  this.write("xmlns:");
                  this.write(p);
                  this.write("=\"");
               }

               char[] ch = u.toCharArray();
               this.writeEsc(ch, 0, ch.length, true);
               this.write('"');
            }

            this.locallyDeclaredPrefix.clear();
         }

         super.startElement(uri, localName, qName, atts);
         this.startTagIsClosed = false;
      } catch (IOException var10) {
         throw SAXException(var10);
      }
   }

    void endElement(const std::string& uri, const std::string& localName, const std::string& qName) {
      try {
         if (this.startTagIsClosed) {
            this.write("</");
            this.write(qName);
            this.write('>');
         } else {
            this.write("/>");
            this.startTagIsClosed = true;
         }

         super.endElement(uri, localName, qName);
         this.elementLevel--;
      } catch (IOException var5) {
         throw SAXException(var5);
      }
   }

    void characters(char[] ch, int start, int len) {
      try {
         if (!this.startTagIsClosed) {
            this.write('>');
            this.startTagIsClosed = true;
         }

         this.writeEsc(ch, start, len, false);
         super.characters(ch, start, len);
      } catch (IOException var5) {
         throw SAXException(var5);
      }
   }

    void ignorableWhitespace(char[] ch, int start, int length) {
      try {
         this.writeEsc(ch, start, length, false);
         super.ignorableWhitespace(ch, start, length);
      } catch (IOException var5) {
         throw SAXException(var5);
      }
   }

    void processingInstruction(const std::string& target, const std::string& data) {
      try {
         if (!this.startTagIsClosed) {
            this.write('>');
            this.startTagIsClosed = true;
         }

         this.write("<?");
         this.write(target);
         this.write(' ');
         this.write(data);
         this.write("?>");
         if (this.elementLevel < 1) {
            this.write('\n');
         }

         super.processingInstruction(target, data);
      } catch (IOException var4) {
         throw SAXException(var4);
      }
   }

    void startElement(const std::string& uri, const std::string& localName) {
      this.startElement(uri, localName, "", this.EMPTY_ATTS);
   }

    void startElement(const std::string& localName) {
      this.startElement("", localName, "", this.EMPTY_ATTS);
   }

    void endElement(const std::string& uri, const std::string& localName) {
      this.endElement(uri, localName, "");
   }

    void endElement(const std::string& localName) {
      this.endElement("", localName, "");
   }

    void dataElement(const std::string& uri, const std::string& localName, const std::string& qName, Attributes atts, const std::string& content) {
      this.startElement(uri, localName, qName, atts);
      this.characters(content);
      this.endElement(uri, localName, qName);
   }

    void dataElement(const std::string& uri, const std::string& localName, const std::string& content) {
      this.dataElement(uri, localName, "", this.EMPTY_ATTS, content);
   }

    void dataElement(const std::string& localName, const std::string& content) {
      this.dataElement("", localName, "", this.EMPTY_ATTS, content);
   }

    void characters(const std::string& data) {
      try {
         if (!this.startTagIsClosed) {
            this.write('>');
            this.startTagIsClosed = true;
         }

         char[] ch = data.toCharArray();
         this.characters(ch, 0, ch.length);
      } catch (IOException var3) {
         throw SAXException(var3);
      }
   }

    void write(char c) {
      this.output.write(c);
   }

    void write(const std::string& s) {
      this.output.write(s);
   }

    void writeAttributes(Attributes atts) {
    int len = atts.getLength();

      for (int i = 0; i < len; i++) {
         char[] ch = atts.getValue(i).toCharArray();
         this.write(' ');
         this.write(atts.getQName(i));
         this.write("=\"");
         this.writeEsc(ch, 0, ch.length, true);
         this.write('"');
      }
   }

    void writeEsc(char[] ch, int start, int length, bool isAttVal) {
      this.escapeHandler.escape(ch, start, length, isAttVal, this.output);
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
