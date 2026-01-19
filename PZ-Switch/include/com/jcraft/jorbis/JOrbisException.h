#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class JOrbisException : public Exception {
public:
 static const long serialVersionUID = 1L;

public
 JOrbisException() {}

public
 JOrbisException(std::string_view string) { super("JOrbis: " + string); }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
