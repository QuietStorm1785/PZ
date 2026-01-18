#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IListBoxItem {
public:
 virtual ~IListBoxItem() = default;
 std::string getLabel();

 std::string getLeftLabel();

 std::string getRightLabel();
}
} // namespace interfaces
} // namespace zombie
