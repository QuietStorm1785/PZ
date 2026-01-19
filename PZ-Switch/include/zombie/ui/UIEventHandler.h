#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
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
 void DoubleClick(std::string_view name, int x, int y);

 void ModalClick(std::string_view name, std::string_view chosen);

 void Selected(std::string_view name, int Selected, int LastSelected);
}
} // namespace ui
} // namespace zombie
