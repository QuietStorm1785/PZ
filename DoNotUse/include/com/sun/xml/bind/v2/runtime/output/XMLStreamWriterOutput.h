#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/CharacterEscapeHandler.h"
#include "com/sun/xml/bind/marshaller/NoEscapeHandler.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
#include "com/sun/xml/bind/v2/runtime/output/XMLStreamWriterOutput/XmlStreamOutWriterAdapter.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamWriter.h"
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


class XMLStreamWriterOutput : public XmlOutputAbstractImpl {
public:
    const XMLStreamWriter out;
    const CharacterEscapeHandler escapeHandler;
    const XmlStreamOutWriterAdapter writerWrapper;
   protected const char[] buf = new char[256];
    static const Class FI_STAX_WRITER_CLASS = initFIStAXWriterClass();
   private static const Constructor<? : public XmlOutput> FI_OUTPUT_CTOR = initFastInfosetOutputClass();
    static const Class STAXEX_WRITER_CLASS = initStAXExWriterClass();
   private static const Constructor<? : public XmlOutput> STAXEX_OUTPUT_CTOR = initStAXExOutputClass();

    static XmlOutput create(XMLStreamWriter out, JAXBContextImpl context, CharacterEscapeHandler escapeHandler) {
    Class writerClass = out.getClass();
      if (writerClass == FI_STAX_WRITER_CLASS) {
         try {
            return FI_OUTPUT_CTOR.newInstance(out, context);
         } catch (Exception var6) {
         }
      }

      if (STAXEX_WRITER_CLASS != nullptr && STAXEX_WRITER_CLASS.isAssignableFrom(writerClass)) {
         try {
            return STAXEX_OUTPUT_CTOR.newInstance(out);
         } catch (Exception var5) {
         }
      }

    CharacterEscapeHandler xmlStreamEscapeHandler = (CharacterEscapeHandler)(escapeHandler != nullptr ? escapeHandler : NoEscapeHandler.theInstance);
      return std::make_shared<XMLStreamWriterOutput>(out, xmlStreamEscapeHandler);
   }

    protected XMLStreamWriterOutput(XMLStreamWriter out, CharacterEscapeHandler escapeHandler) {
      this.out = out;
      this.escapeHandler = escapeHandler;
      this.writerWrapper = std::make_shared<XmlStreamOutWriterAdapter>(out, nullptr);
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      if (!fragment) {
         this.out.writeStartDocument();
      }
   }

    void endDocument(bool fragment) {
      if (!fragment) {
         this.out.writeEndDocument();
         this.out.flush();
      }

      super.endDocument(fragment);
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.out.writeStartElement(this.nsContext.getPrefix(prefix), localName, this.nsContext.getNamespaceURI(prefix));
    Element nse = this.nsContext.getCurrent();
      if (nse.count() > 0) {
         for (int i = nse.count() - 1; i >= 0; i--) {
    std::string uri = nse.getNsUri(i);
            if (uri.length() != 0 || nse.getBase() != 1) {
               this.out.writeNamespace(nse.getPrefix(i), uri);
            }
         }
      }
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
      if (prefix == -1) {
         this.out.writeAttribute(localName, value);
      } else {
         this.out.writeAttribute(this.nsContext.getPrefix(prefix), this.nsContext.getNamespaceURI(prefix), localName, value);
      }
   }

    void endStartTag() {
   }

    void endTag(int prefix, const std::string& localName) {
      this.out.writeEndElement();
   }

    void text(const std::string& value, bool needsSeparatingWhitespace) {
      if (needsSeparatingWhitespace) {
         this.out.writeCharacters(" ");
      }

      this.escapeHandler.escape(value.toCharArray(), 0, value.length(), false, this.writerWrapper);
   }

    void text(Pcdata value, bool needsSeparatingWhitespace) {
      if (needsSeparatingWhitespace) {
         this.out.writeCharacters(" ");
      }

    int len = value.length();
      if (len < this.buf.length) {
         value.writeTo(this.buf, 0);
         this.out.writeCharacters(this.buf, 0, len);
      } else {
         this.out.writeCharacters(value);
      }
   }

    static Class initFIStAXWriterClass() {
      try {
         Class<?> llfisw = Class.forName("org.jvnet.fastinfoset.stax.LowLevelFastInfosetStreamWriter");
         Class<?> sds = Class.forName("com.sun.xml.fastinfoset.stax.StAXDocumentSerializer");
         return llfisw.isAssignableFrom(sds) ? sds : nullptr;
      } catch (Throwable var2) {
    return nullptr;
      }
   }

   private static Constructor<? : public XmlOutput> initFastInfosetOutputClass() {
      try {
         if (FI_STAX_WRITER_CLASS == nullptr) {
    return nullptr;
         } else {
    Class c = Class.forName("com.sun.xml.bind.v2.runtime.output.FastInfosetStreamWriterOutput");
            return c.getConstructor(FI_STAX_WRITER_CLASS, JAXBContextImpl.class);
         }
      } catch (Throwable var1) {
    return nullptr;
      }
   }

    static Class initStAXExWriterClass() {
      try {
         return Class.forName("org.jvnet.staxex.XMLStreamWriterEx");
      } catch (Throwable var1) {
    return nullptr;
      }
   }

   private static Constructor<? : public XmlOutput> initStAXExOutputClass() {
      try {
    Class c = Class.forName("com.sun.xml.bind.v2.runtime.output.StAXExStreamWriterOutput");
         return c.getConstructor(STAXEX_WRITER_CLASS);
      } catch (Throwable var1) {
    return nullptr;
      }
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
