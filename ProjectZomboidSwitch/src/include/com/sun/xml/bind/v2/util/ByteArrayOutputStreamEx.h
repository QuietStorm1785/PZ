#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class ByteArrayOutputStreamEx : public ByteArrayOutputStream {
public:
    public ByteArrayOutputStreamEx() {
   }

    public ByteArrayOutputStreamEx(int size) {
      super(size);
   }

    void set(Base64Data dt, const std::string& mimeType) {
      dt.set(this.buf, this.count, mimeType);
   }

   public byte[] getBuffer() {
      return this.buf;
   }

    void readFrom(InputStream is) {
      while (true) {
         if (this.count == this.buf.length) {
            byte[] data = new byte[this.buf.length * 2];
            System.arraycopy(this.buf, 0, data, 0, this.buf.length);
            this.buf = data;
         }

    int sz = is.read(this.buf, this.count, this.buf.length - this.count);
         if (sz < 0) {
            return;
         }

         this.count += sz;
      }
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
