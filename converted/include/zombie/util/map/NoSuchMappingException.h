#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace map {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class NoSuchMappingException : public RuntimeException {
public:
 static const long serialVersionUID = 1L;

 public NoSuchMappingException(const std::string& string) {
 super(string);
 }
}
} // namespace map
} // namespace util
} // namespace zombie
