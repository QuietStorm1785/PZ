#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/marshaller/CharacterEscapeHandler.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
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


class UTF8XmlOutput : public XmlOutputAbstractImpl {
public:
    const OutputStream out;
   private Encoded[] prefixes = new Encoded[8];
    int prefixCount;
   private const Encoded[] localNames;
    const Encoded textBuffer = std::make_shared<Encoded>();
   protected const byte[] octetBuffer = new byte[1024];
    int octetBufferIndex;
    bool closeStartTagPending = false;
    std::string header;
    CharacterEscapeHandler escapeHandler = nullptr;
   private const byte[] XMLNS_EQUALS;
   private const byte[] XMLNS_COLON;
   private const byte[] EQUALS;
   private const byte[] CLOSE_TAG;
   private const byte[] EMPTY_TAG;
   private const byte[] XML_DECL;
   private static const byte[] _XMLNS_EQUALS = toBytes(" xmlns=\"");
   private static const byte[] _XMLNS_COLON = toBytes(" xmlns:");
   private static const byte[] _EQUALS = toBytes("=\"");
   private static const byte[] _CLOSE_TAG = toBytes("</");
   private static const byte[] _EMPTY_TAG = toBytes("/>");
   private static const byte[] _XML_DECL = toBytes("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>");
   private static const byte[] EMPTY_BYTE_ARRAY = new byte[0];

    public UTF8XmlOutput(OutputStream out, Encoded[] localNames, CharacterEscapeHandler escapeHandler) {
      this.XMLNS_EQUALS = (byte[])_XMLNS_EQUALS.clone();
      this.XMLNS_COLON = (byte[])_XMLNS_COLON.clone();
      this.EQUALS = (byte[])_EQUALS.clone();
      this.CLOSE_TAG = (byte[])_CLOSE_TAG.clone();
      this.EMPTY_TAG = (byte[])_EMPTY_TAG.clone();
      this.XML_DECL = (byte[])_XML_DECL.clone();
      this.out = out;
      this.localNames = localNames;

      for (int i = 0; i < this.prefixes.length; i++) {
         this.prefixes[i] = std::make_unique<Encoded>();
      }

      this.escapeHandler = escapeHandler;
   }

    void setHeader(const std::string& header) {
      this.header = header;
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      this.octetBufferIndex = 0;
      if (!fragment) {
         this.write(this.XML_DECL);
      }

      if (this.header != nullptr) {
         this.textBuffer.set(this.header);
         this.textBuffer.write(this);
      }
   }

    void endDocument(bool fragment) {
      this.flushBuffer();
      super.endDocument(fragment);
   }

    void closeStartTag() {
      if (this.closeStartTagPending) {
         this.write(62);
         this.closeStartTagPending = false;
      }
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.closeStartTag();
    int base = this.pushNsDecls();
      this.write(60);
      this.writeName(prefix, localName);
      this.writeNsDecls(base);
   }

    void beginStartTag(Name name) {
      this.closeStartTag();
    int base = this.pushNsDecls();
      this.write(60);
      this.writeName(name);
      this.writeNsDecls(base);
   }

    int pushNsDecls() {
    int total = this.nsContext.count();
    Element ns = this.nsContext.getCurrent();
      if (total > this.prefixes.length) {
    int m = Math.max(total, this.prefixes.length * 2);
         Encoded[] buf = new Encoded[m];
         System.arraycopy(this.prefixes, 0, buf, 0, this.prefixes.length);

         for (int i = this.prefixes.length; i < buf.length; i++) {
            buf[i] = std::make_unique<Encoded>();
         }

         this.prefixes = buf;
      }

    int base = Math.min(this.prefixCount, ns.getBase());
    int size = this.nsContext.count();

      for (int i = base; i < size; i++) {
    std::string p = this.nsContext.getPrefix(i);
    Encoded e = this.prefixes[i];
         if (p.length() == 0) {
            e.buf = EMPTY_BYTE_ARRAY;
            e.len = 0;
         } else {
            e.set(p);
            e.append(':');
         }
      }

      this.prefixCount = size;
    return base;
   }

    void writeNsDecls(int base) {
    Element ns = this.nsContext.getCurrent();
    int size = this.nsContext.count();

      for (int i = ns.getBase(); i < size; i++) {
         this.writeNsDecl(i);
      }
   }

    void writeNsDecl(int prefixIndex) {
    std::string p = this.nsContext.getPrefix(prefixIndex);
      if (p.length() == 0) {
         if (this.nsContext.getCurrent().isRootElement() && this.nsContext.getNamespaceURI(prefixIndex).length() == 0) {
            return;
         }

         this.write(this.XMLNS_EQUALS);
      } else {
    Encoded e = this.prefixes[prefixIndex];
         this.write(this.XMLNS_COLON);
         this.write(e.buf, 0, e.len - 1);
         this.write(this.EQUALS);
      }

      this.doText(this.nsContext.getNamespaceURI(prefixIndex), true);
      this.write(34);
   }

    void writePrefix(int prefix) {
      this.prefixes[prefix].write(this);
   }

    void writeName(Name name) {
      this.writePrefix(this.nsUriIndex2prefixIndex[name.nsUriIndex]);
      this.localNames[name.localNameIndex].write(this);
   }

    void writeName(int prefix, const std::string& localName) {
      this.writePrefix(prefix);
      this.textBuffer.set(localName);
      this.textBuffer.write(this);
   }

    void attribute(Name name, const std::string& value) {
      this.write(32);
      if (name.nsUriIndex == -1) {
         this.localNames[name.localNameIndex].write(this);
      } else {
         this.writeName(name);
      }

      this.write(this.EQUALS);
      this.doText(value, true);
      this.write(34);
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
      this.write(32);
      if (prefix == -1) {
         this.textBuffer.set(localName);
         this.textBuffer.write(this);
      } else {
         this.writeName(prefix, localName);
      }

      this.write(this.EQUALS);
      this.doText(value, true);
      this.write(34);
   }

    void endStartTag() {
      this.closeStartTagPending = true;
   }

    void endTag(Name name) {
      if (this.closeStartTagPending) {
         this.write(this.EMPTY_TAG);
         this.closeStartTagPending = false;
      } else {
         this.write(this.CLOSE_TAG);
         this.writeName(name);
         this.write(62);
      }
   }

    void endTag(int prefix, const std::string& localName) {
      if (this.closeStartTagPending) {
         this.write(this.EMPTY_TAG);
         this.closeStartTagPending = false;
      } else {
         this.write(this.CLOSE_TAG);
         this.writeName(prefix, localName);
         this.write(62);
      }
   }

    void text(const std::string& value, bool needSP) {
      this.closeStartTag();
      if (needSP) {
         this.write(32);
      }

      this.doText(value, false);
   }

    void text(Pcdata value, bool needSP) {
      this.closeStartTag();
      if (needSP) {
         this.write(32);
      }

      value.writeTo(this);
   }

    void doText(const std::string& value, bool isAttribute) {
      if (this.escapeHandler != nullptr) {
    StringWriter sw = std::make_shared<StringWriter>();
         this.escapeHandler.escape(value.toCharArray(), 0, value.length(), isAttribute, sw);
         this.textBuffer.set(sw);
      } else {
         this.textBuffer.setEscape(value, isAttribute);
      }

      this.textBuffer.write(this);
   }

    void text(int value) {
      this.closeStartTag();
    bool minus = value < 0;
      this.textBuffer.ensureSize(11);
      byte[] buf = this.textBuffer.buf;
    int idx = 11;

      do {
    int r = value % 10;
         if (r < 0) {
            r = -r;
         }

         buf[--idx] = (byte)(48 | r);
         value /= 10;
      } while (value != 0);

      if (minus) {
         buf[--idx] = 45;
      }

      this.write(buf, idx, 11 - idx);
   }

    void text(byte[] data, int dataLen) {
      this.closeStartTag();
    int start = 0;

      while (dataLen > 0) {
    int batchSize = Math.min((this.octetBuffer.length - this.octetBufferIndex) / 4 * 3, dataLen);
         this.octetBufferIndex = DatatypeConverterImpl._printBase64Binary(data, start, batchSize, this.octetBuffer, this.octetBufferIndex);
         if (batchSize < dataLen) {
            this.flushBuffer();
         }

         start += batchSize;
         dataLen -= batchSize;
      }
   }

    void write(int i) {
      if (this.octetBufferIndex < this.octetBuffer.length) {
         this.octetBuffer[this.octetBufferIndex++] = (byte)i;
      } else {
         this.out.write(this.octetBuffer);
         this.octetBufferIndex = 1;
         this.octetBuffer[0] = (byte)i;
      }
   }

    void write(byte[] b) {
      this.write(b, 0, b.length);
   }

    void write(byte[] b, int start, int length) {
      if (this.octetBufferIndex + length < this.octetBuffer.length) {
         System.arraycopy(b, start, this.octetBuffer, this.octetBufferIndex, length);
         this.octetBufferIndex += length;
      } else {
         this.out.write(this.octetBuffer, 0, this.octetBufferIndex);
         this.out.write(b, start, length);
         this.octetBufferIndex = 0;
      }
   }

    void flushBuffer() {
      this.out.write(this.octetBuffer, 0, this.octetBufferIndex);
      this.octetBufferIndex = 0;
   }

   static byte[] toBytes(std::string s) {
      byte[] buf = new byte[s.length()];

      for (int i = s.length() - 1; i >= 0; i--) {
         buf[i] = (byte)s.charAt(i);
      }

    return buf;
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
