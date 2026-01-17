#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IDebugOption {
public:
  virtual ~IDebugOption() = default;
  std::string getName();

  IDebugOptionGroup getParent();

  void setParent(IDebugOptionGroup parent);
}
} // namespace options
} // namespace debug
} // namespace zombie
