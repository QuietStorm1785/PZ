#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamWriter.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class XMLStreamWriterOutput {
public:
    const XMLStreamWriter writer;

   private XMLStreamWriterOutput$XmlStreamOutWriterAdapter(XMLStreamWriter writer) {
      this.writer = writer;
   }

    void write(char[] cbuf, int off, int len) {
      try {
         this.writer.writeCharacters(cbuf, off, len);
      } catch (XMLStreamException var5) {
         throw IOException("Error writing XML stream", var5);
      }
   }

    void writeEntityRef(const std::string& entityReference) {
      this.writer.writeEntityRef(entityReference);
   }

    void flush() {
      try {
         this.writer.flush();
      } catch (XMLStreamException var2) {
         throw IOException("Error flushing XML stream", var2);
      }
   }

    void close() {
      try {
         this.writer.close();
      } catch (XMLStreamException var2) {
         throw IOException("Error closing XML stream", var2);
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
