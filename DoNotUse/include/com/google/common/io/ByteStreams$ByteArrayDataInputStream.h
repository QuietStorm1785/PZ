#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteStreams {
public:
    const DataInput input;

   ByteStreams$ByteArrayDataInputStream(ByteArrayInputStream byteArrayInputStream) {
      this.input = std::make_shared<DataInputStream>(byteArrayInputStream);
   }

    void readFully(byte[] b) {
      try {
         this.input.readFully(b);
      } catch (IOException var3) {
         throw IllegalStateException(var3);
      }
   }

    void readFully(byte[] b, int off, int len) {
      try {
         this.input.readFully(b, off, len);
      } catch (IOException var5) {
         throw IllegalStateException(var5);
      }
   }

    int skipBytes(int n) {
      try {
         return this.input.skipBytes(n);
      } catch (IOException var3) {
         throw IllegalStateException(var3);
      }
   }

    bool readBoolean() {
      try {
         return this.input.readBoolean();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    uint8_t readByte() {
      try {
         return this.input.readByte();
      } catch (EOFException var2) {
         throw IllegalStateException(var2);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    int readUnsignedByte() {
      try {
         return this.input.readUnsignedByte();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    short readShort() {
      try {
         return this.input.readShort();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    int readUnsignedShort() {
      try {
         return this.input.readUnsignedShort();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    char readChar() {
      try {
         return this.input.readChar();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    int readInt() {
      try {
         return this.input.readInt();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    long readLong() {
      try {
         return this.input.readLong();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    float readFloat() {
      try {
         return this.input.readFloat();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    double readDouble() {
      try {
         return this.input.readDouble();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    std::string readLine() {
      try {
         return this.input.readLine();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }

    std::string readUTF() {
      try {
         return this.input.readUTF();
      } catch (IOException var2) {
         throw IllegalStateException(var2);
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
