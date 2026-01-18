#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoRegionException : public Exception {
public:
public
 IsoRegionException(const std::string &string) { super(string); }

public
 IsoRegionException(const std::string &string, std::exception throwable) {
 super(string, throwable);
 }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
