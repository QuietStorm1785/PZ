#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class UIEventHandler {
public:
    virtual ~UIEventHandler() = default;
    void DoubleClick(const std::string& var1, int var2, int var3);

    void ModalClick(const std::string& var1, const std::string& var2);

    void Selected(const std::string& var1, int var2, int var3);
}
} // namespace ui
} // namespace zombie
