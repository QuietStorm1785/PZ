#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/runtime/output/Pcdata.h"
#include "com/sun/xml/bind/v2/runtime/output/UTF8XmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data/1.h"
#include "com/sun/xml/bind/v2/util/ByteArrayOutputStreamEx.h"
#include "javax/activation/DataHandler.h"
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
namespace unmarshaller {


class Base64Data : public Pcdata {
public:
    DataHandler dataHandler;
   private byte[] data;
    int dataLen;
    std::string mimeType;

    void set(byte[] data, int len, @Nullable std::string) {
      this.data = data;
      this.dataLen = len;
      this.dataHandler = nullptr;
      this.mimeType = mimeType;
   }

    void set(byte[] data, @Nullable std::string) {
      this.set(data, data.length, mimeType);
   }

    void set(DataHandler data) {
      assert data != nullptr;

      this.dataHandler = data;
      this.data = nullptr;
   }

    DataHandler getDataHandler() {
      if (this.dataHandler == nullptr) {
         this.dataHandler = std::make_shared<DataHandler>(std::make_shared<1>(this));
      }

      return this.dataHandler;
   }

   public byte[] getExact() {
      this.get();
      if (this.dataLen != this.data.length) {
         byte[] buf = new byte[this.dataLen];
         System.arraycopy(this.data, 0, buf, 0, this.dataLen);
         this.data = buf;
      }

      return this.data;
   }

    InputStream getInputStream() {
      return (InputStream)(this.dataHandler != nullptr ? this.dataHandler.getInputStream() : std::make_shared<ByteArrayInputStream>(this.data, 0, this.dataLen));
   }

    bool hasData() {
      return this.data != nullptr;
   }

   public byte[] get() {
      if (this.data == nullptr) {
         try {
    ByteArrayOutputStreamEx baos = std::make_shared<ByteArrayOutputStreamEx>(1024);
    InputStream is = this.dataHandler.getDataSource().getInputStream();
            baos.readFrom(is);
            is.close();
            this.data = baos.getBuffer();
            this.dataLen = baos.size();
         } catch (IOException var3) {
            this.dataLen = 0;
         }
      }

      return this.data;
   }

    int getDataLen() {
      return this.dataLen;
   }

    std::string getMimeType() {
      return this.mimeType == nullptr ? "application/octet-stream" : this.mimeType;
   }

    int length() {
      this.get();
      return (this.dataLen + 2) / 3 * 4;
   }

    char charAt(int index) {
    int offset = index % 4;
    int base = index / 4 * 3;
      switch (offset) {
         case 0:
            return DatatypeConverterImpl.encode(this.data[base] >> 2);
         case 1:
    uint8_t b1;
            if (base + 1 < this.dataLen) {
               b1 = this.data[base + 1];
            } else {
               b1 = 0;
            }

            return DatatypeConverterImpl.encode((this.data[base] & 3) << 4 | b1 >> 4 & 15);
         case 2:
            if (base + 1 < this.dataLen) {
    uint8_t b1 = this.data[base + 1];
    uint8_t b2;
               if (base + 2 < this.dataLen) {
                  b2 = this.data[base + 2];
               } else {
                  b2 = 0;
               }

               return DatatypeConverterImpl.encode((b1 & 15) << 2 | b2 >> 6 & 3);
            }

            return '=';
         case 3:
            if (base + 2 < this.dataLen) {
               return DatatypeConverterImpl.encode(this.data[base + 2] & '?');
            }

            return '=';
         default:
            throw std::make_unique<IllegalStateException>();
      }
   }

    CharSequence subSequence(int start, int end) {
    std::stringstream buf = new std::stringstream();
      this.get();

      for (int i = start; i < end; i++) {
         buf.append(this.charAt(i));
      }

    return buf;
   }

    std::string toString() {
      this.get();
      return DatatypeConverterImpl._printBase64Binary(this.data, 0, this.dataLen);
   }

    void writeTo(char[] buf, int start) {
      this.get();
      DatatypeConverterImpl._printBase64Binary(this.data, 0, this.dataLen, buf, start);
   }

    void writeTo(UTF8XmlOutput output) {
      this.get();
      output.text(this.data, this.dataLen);
   }

    void writeTo(XMLStreamWriter output) {
      this.get();
      DatatypeConverterImpl._printBase64Binary(this.data, 0, this.dataLen, output);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
