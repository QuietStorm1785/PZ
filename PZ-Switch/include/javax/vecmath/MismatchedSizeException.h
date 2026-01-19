#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
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
 MismatchedSizeException() noexcept{}

public
 MismatchedSizeException(std::string_view string) { super(string); }
}
} // namespace vecmath
} // namespace javax
