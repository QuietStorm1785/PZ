#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteArrayDataOutput {
public:
    virtual ~ByteArrayDataOutput() = default;
    void write(int var1);

    void write(byte[] var1);

    void write(byte[] var1, int var2, int var3);

    void writeBoolean(bool var1);

    void writeByte(int var1);

    void writeShort(int var1);

    void writeChar(int var1);

    void writeInt(int var1);

    void writeLong(long var1);

    void writeFloat(float var1);

    void writeDouble(double var1);

    void writeChars(const std::string& var1);

    void writeUTF(const std::string& var1);

    void writeBytes(const std::string& var1);

   byte[] toByteArray();
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
