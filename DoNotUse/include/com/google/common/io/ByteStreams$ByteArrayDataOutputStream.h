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
    const DataOutput output;
    const ByteArrayOutputStream byteArrayOutputSteam;

   ByteStreams$ByteArrayDataOutputStream(ByteArrayOutputStream byteArrayOutputSteam) {
      this.byteArrayOutputSteam = byteArrayOutputSteam;
      this.output = std::make_shared<DataOutputStream>(byteArrayOutputSteam);
   }

    void write(int b) {
      try {
         this.output.write(b);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void write(byte[] b) {
      try {
         this.output.write(b);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void write(byte[] b, int off, int len) {
      try {
         this.output.write(b, off, len);
      } catch (IOException var5) {
         throw AssertionError(var5);
      }
   }

    void writeBoolean(bool v) {
      try {
         this.output.writeBoolean(v);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeByte(int v) {
      try {
         this.output.writeByte(v);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeBytes(const std::string& s) {
      try {
         this.output.writeBytes(s);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeChar(int v) {
      try {
         this.output.writeChar(v);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeChars(const std::string& s) {
      try {
         this.output.writeChars(s);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeDouble(double v) {
      try {
         this.output.writeDouble(v);
      } catch (IOException var4) {
         throw AssertionError(var4);
      }
   }

    void writeFloat(float v) {
      try {
         this.output.writeFloat(v);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeInt(int v) {
      try {
         this.output.writeInt(v);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeLong(long v) {
      try {
         this.output.writeLong(v);
      } catch (IOException var4) {
         throw AssertionError(var4);
      }
   }

    void writeShort(int v) {
      try {
         this.output.writeShort(v);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

    void writeUTF(const std::string& s) {
      try {
         this.output.writeUTF(s);
      } catch (IOException var3) {
         throw AssertionError(var3);
      }
   }

   public byte[] toByteArray() {
      return this.byteArrayOutputSteam.toByteArray();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
