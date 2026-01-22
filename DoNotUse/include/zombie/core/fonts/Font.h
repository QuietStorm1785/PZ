#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"

namespace zombie {
namespace core {
namespace fonts {


class Font {
public:
    virtual ~Font() = default;
    void drawString(float var1, float var2, const std::string& var3);

    void drawString(float var1, float var2, const std::string& var3, Color var4);

    void drawString(float var1, float var2, const std::string& var3, Color var4, int var5, int var6);

    int getHeight(const std::string& var1);

    int getWidth(const std::string& var1);

    int getWidth(const std::string& var1, bool var2);

    int getWidth(const std::string& var1, int var2, int var3);

    int getWidth(const std::string& var1, int var2, int var3, bool var4);

    int getLineHeight();
}
} // namespace fonts
} // namespace core
} // namespace zombie
