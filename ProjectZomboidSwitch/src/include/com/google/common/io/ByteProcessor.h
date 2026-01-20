#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteProcessor {
public:
    virtual ~ByteProcessor() = default;
    bool processBytes(byte[] var1, int var2, int var3);

    T getResult();
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
