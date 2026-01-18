#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MismatchedSizeException : public RuntimeException {
public:
public
  MismatchedSizeException() {}

public
  MismatchedSizeException(const std::string &string) { super(string); }
}
} // namespace vecmath
} // namespace javax
