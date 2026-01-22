#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Longs.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class LittleEndianDataOutputStream : public FilterOutputStream {
public:
    public LittleEndianDataOutputStream(OutputStream out) {
      super(std::make_shared<DataOutputStream>((OutputStream)Preconditions.checkNotNull(out)));
   }

    void write(byte[] b, int off, int len) {
      this.out.write(b, off, len);
   }

    void writeBoolean(bool v) {
      ((DataOutputStream)this.out).writeBoolean(v);
   }

    void writeByte(int v) {
      ((DataOutputStream)this.out).writeByte(v);
   }

    void writeBytes(const std::string& s) {
      ((DataOutputStream)this.out).writeBytes(s);
   }

    void writeChar(int v) {
      this.writeShort(v);
   }

    void writeChars(const std::string& s) {
      for (int i = 0; i < s.length(); i++) {
         this.writeChar(s.charAt(i));
      }
   }

    void writeDouble(double v) {
      this.writeLong(double.doubleToLongBits(v));
   }

    void writeFloat(float v) {
      this.writeInt(float.floatToIntBits(v));
   }

    void writeInt(int v) {
      this.out.write(0xFF & v);
      this.out.write(0xFF & v >> 8);
      this.out.write(0xFF & v >> 16);
      this.out.write(0xFF & v >> 24);
   }

    void writeLong(long v) {
      byte[] bytes = Longs.toByteArray(int64_t.reverseBytes(v));
      this.write(bytes, 0, bytes.length);
   }

    void writeShort(int v) {
      this.out.write(0xFF & v);
      this.out.write(0xFF & v >> 8);
   }

    void writeUTF(const std::string& str) {
      ((DataOutputStream)this.out).writeUTF(str);
   }

    void close() {
      this.out.close();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
