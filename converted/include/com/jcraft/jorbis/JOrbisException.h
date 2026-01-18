#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class JOrbisException : public Exception {
public:
 static const long serialVersionUID = 1L;

 public JOrbisException() {
 }

 public JOrbisException(const std::string& string) {
 super("JOrbis: " + string);
 }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
