#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace Styles {

class Style {
public:
    virtual ~Style() = default;
    void setupState();

    void resetState();

    int getStyleID();

    AlphaOp getAlphaOp();

    bool getRenderSprite();

    GeometryData build();

    void render(int var1, int var2);
}
} // namespace Styles
} // namespace core
} // namespace zombie
