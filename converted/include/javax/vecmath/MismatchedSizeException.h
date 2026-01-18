#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class MismatchedSizeException : public RuntimeException {
public:
 public MismatchedSizeException() {
 }

 public MismatchedSizeException(const std::string& string) {
 super(string);
 }
}
} // namespace vecmath
} // namespace javax
