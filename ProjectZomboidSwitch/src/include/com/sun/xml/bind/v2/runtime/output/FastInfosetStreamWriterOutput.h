#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/NoEscapeHandler.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/output/FastInfosetStreamWriterOutput/AppData.h"
#include "com/sun/xml/bind/v2/runtime/output/FastInfosetStreamWriterOutput/TablesPerJAXBContext.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "com/sun/xml/fastinfoset/stax/StAXDocumentSerializer.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/jvnet/fastinfoset/VocabularyApplicationData.h"
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


class FastInfosetStreamWriterOutput : public XMLStreamWriterOutput {
public:
    const StAXDocumentSerializer fiout;
   private const Encoded[] localNames;
    const TablesPerJAXBContext tables;

    public FastInfosetStreamWriterOutput(StAXDocumentSerializer out, JAXBContextImpl context) {
      super(out, NoEscapeHandler.theInstance);
      this.fiout = out;
      this.localNames = context.getUTF8NameTable();
    VocabularyApplicationData vocabAppData = this.fiout.getVocabularyApplicationData();
    AppData appData = nullptr;
      if (vocabAppData != nullptr && dynamic_cast<AppData*>(vocabAppData) != nullptr) {
         appData = (AppData)vocabAppData;
      } else {
         appData = std::make_unique<AppData>();
         this.fiout.setVocabularyApplicationData(appData);
      }

    TablesPerJAXBContext tablesPerContext = (TablesPerJAXBContext)appData.contexts.get(context);
      if (tablesPerContext != nullptr) {
         this.tables = tablesPerContext;
         this.tables.clearOrResetTables(out.getLocalNameIndex());
      } else {
         this.tables = std::make_shared<TablesPerJAXBContext>(context, out.getLocalNameIndex());
         appData.contexts.put(context, this.tables);
      }
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      if (fragment) {
         this.fiout.initiateLowLevelWriting();
      }
   }

    void endDocument(bool fragment) {
      super.endDocument(fragment);
   }

    void beginStartTag(Name name) {
      this.fiout.writeLowLevelTerminationAndMark();
      if (this.nsContext.getCurrent().count() == 0) {
    int qNameIndex = this.tables.elementIndexes[name.qNameIndex] - this.tables.indexOffset;
    int prefixIndex = this.nsUriIndex2prefixIndex[name.nsUriIndex];
         if (qNameIndex >= 0 && this.tables.elementIndexPrefixes[name.qNameIndex] == prefixIndex) {
            this.fiout.writeLowLevelStartElementIndexed(0, qNameIndex);
         } else {
            this.tables.elementIndexes[name.qNameIndex] = this.fiout.getNextElementIndex() + this.tables.indexOffset;
            this.tables.elementIndexPrefixes[name.qNameIndex] = prefixIndex;
            this.writeLiteral(60, name, this.nsContext.getPrefix(prefixIndex), this.nsContext.getNamespaceURI(prefixIndex));
         }
      } else {
         this.beginStartTagWithNamespaces(name);
      }
   }

    void beginStartTagWithNamespaces(Name name) {
    Element nse = this.nsContext.getCurrent();
      this.fiout.writeLowLevelStartNamespaces();

      for (int i = nse.count() - 1; i >= 0; i--) {
    std::string uri = nse.getNsUri(i);
         if (uri.length() != 0 || nse.getBase() != 1) {
            this.fiout.writeLowLevelNamespace(nse.getPrefix(i), uri);
         }
      }

      this.fiout.writeLowLevelEndNamespaces();
    int qNameIndex = this.tables.elementIndexes[name.qNameIndex] - this.tables.indexOffset;
    int prefixIndex = this.nsUriIndex2prefixIndex[name.nsUriIndex];
      if (qNameIndex >= 0 && this.tables.elementIndexPrefixes[name.qNameIndex] == prefixIndex) {
         this.fiout.writeLowLevelStartElementIndexed(0, qNameIndex);
      } else {
         this.tables.elementIndexes[name.qNameIndex] = this.fiout.getNextElementIndex() + this.tables.indexOffset;
         this.tables.elementIndexPrefixes[name.qNameIndex] = prefixIndex;
         this.writeLiteral(60, name, this.nsContext.getPrefix(prefixIndex), this.nsContext.getNamespaceURI(prefixIndex));
      }
   }

    void attribute(Name name, const std::string& value) {
      this.fiout.writeLowLevelStartAttributes();
    int qNameIndex = this.tables.attributeIndexes[name.qNameIndex] - this.tables.indexOffset;
      if (qNameIndex >= 0) {
         this.fiout.writeLowLevelAttributeIndexed(qNameIndex);
      } else {
         this.tables.attributeIndexes[name.qNameIndex] = this.fiout.getNextAttributeIndex() + this.tables.indexOffset;
    int namespaceURIId = name.nsUriIndex;
         if (namespaceURIId == -1) {
            this.writeLiteral(120, name, "", "");
         } else {
    int prefix = this.nsUriIndex2prefixIndex[namespaceURIId];
            this.writeLiteral(120, name, this.nsContext.getPrefix(prefix), this.nsContext.getNamespaceURI(prefix));
         }
      }

      this.fiout.writeLowLevelAttributeValue(value);
   }

    void writeLiteral(int type, Name name, const std::string& prefix, const std::string& namespaceURI) {
    int localNameIndex = this.tables.localNameIndexes[name.localNameIndex] - this.tables.indexOffset;
      if (localNameIndex < 0) {
         this.tables.localNameIndexes[name.localNameIndex] = this.fiout.getNextLocalNameIndex() + this.tables.indexOffset;
         this.fiout.writeLowLevelStartNameLiteral(type, prefix, this.localNames[name.localNameIndex].buf, namespaceURI);
      } else {
         this.fiout.writeLowLevelStartNameLiteral(type, prefix, localNameIndex, namespaceURI);
      }
   }

    void endStartTag() {
      this.fiout.writeLowLevelEndStartElement();
   }

    void endTag(Name name) {
      this.fiout.writeLowLevelEndElement();
   }

    void endTag(int prefix, const std::string& localName) {
      this.fiout.writeLowLevelEndElement();
   }

    void text(Pcdata value, bool needsSeparatingWhitespace) {
      if (needsSeparatingWhitespace) {
         this.fiout.writeLowLevelText(" ");
      }

      if (!(dynamic_cast<Base64Data*>(value) != nullptr)) {
    int len = value.length();
         if (len < this.buf.length) {
            value.writeTo(this.buf, 0);
            this.fiout.writeLowLevelText(this.buf, len);
         } else {
            this.fiout.writeLowLevelText(value);
         }
      } else {
    Base64Data dataValue = (Base64Data)value;
         this.fiout.writeLowLevelOctets(dataValue.get(), dataValue.getDataLen());
      }
   }

    void text(const std::string& value, bool needsSeparatingWhitespace) {
      if (needsSeparatingWhitespace) {
         this.fiout.writeLowLevelText(" ");
      }

      this.fiout.writeLowLevelText(value);
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.fiout.writeLowLevelTerminationAndMark();
    int type = 0;
      if (this.nsContext.getCurrent().count() > 0) {
    Element nse = this.nsContext.getCurrent();
         this.fiout.writeLowLevelStartNamespaces();

         for (int i = nse.count() - 1; i >= 0; i--) {
    std::string uri = nse.getNsUri(i);
            if (uri.length() != 0 || nse.getBase() != 1) {
               this.fiout.writeLowLevelNamespace(nse.getPrefix(i), uri);
            }
         }

         this.fiout.writeLowLevelEndNamespaces();
         type = 0;
      }

    bool isIndexed = this.fiout.writeLowLevelStartElement(type, this.nsContext.getPrefix(prefix), localName, this.nsContext.getNamespaceURI(prefix));
      if (!isIndexed) {
         this.tables.incrementMaxIndexValue();
      }
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
      this.fiout.writeLowLevelStartAttributes();
    bool isIndexed;
      if (prefix == -1) {
         isIndexed = this.fiout.writeLowLevelAttribute("", "", localName);
      } else {
         isIndexed = this.fiout.writeLowLevelAttribute(this.nsContext.getPrefix(prefix), this.nsContext.getNamespaceURI(prefix), localName);
      }

      if (!isIndexed) {
         this.tables.incrementMaxIndexValue();
      }

      this.fiout.writeLowLevelAttributeValue(value);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
