#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class TextManager {
public:
    virtual ~TextManager() = default;
    void draw(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13);
}
} // namespace ui
} // namespace zombie
