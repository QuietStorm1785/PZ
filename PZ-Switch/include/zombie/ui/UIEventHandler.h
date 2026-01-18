#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UIEventHandler {
public:
 virtual ~UIEventHandler() = default;
 void DoubleClick(const std::string &name, int x, int y);

 void ModalClick(const std::string &name, const std::string &chosen);

 void Selected(const std::string &name, int Selected, int LastSelected);
}
} // namespace ui
} // namespace zombie
