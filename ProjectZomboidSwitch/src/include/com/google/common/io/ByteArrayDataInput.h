#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteArrayDataInput {
public:
    virtual ~ByteArrayDataInput() = default;
    void readFully(byte[] var1);

    void readFully(byte[] var1, int var2, int var3);

    int skipBytes(int var1);

    bool readBoolean();

    uint8_t readByte();

    int readUnsignedByte();

    short readShort();

    int readUnsignedShort();

    char readChar();

    int readInt();

    long readLong();

    float readFloat();

    double readDouble();

    std::string readLine();

    std::string readUTF();
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
