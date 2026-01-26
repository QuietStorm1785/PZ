#pragma once
#include <memory>
#include "zombie/iso/IsoGridStack.h"

namespace zombie {
namespace iso {

class PerPlayerRender {
public:
    std::shared_ptr<IsoGridStack> GridStacks;
    // 3D boolean array: VisiOccludedFlags[x][y][2]
    std::vector<std::vector<std::vector<bool>>> VisiOccludedFlags;
    // 2D boolean array: VisiCulledFlags[x][y]
    std::vector<std::vector<bool>> VisiCulledFlags;
    // 3D short array: StencilValues[x][y][2]
    std::vector<std::vector<std::vector<short>>> StencilValues;
    // 2D boolean array: FlattenGrassEtc[x][y]
    std::vector<std::vector<bool>> FlattenGrassEtc;
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    PerPlayerRender() : GridStacks(std::make_shared<IsoGridStack>(9)) {}
    void setSize(int w, int h) {
        if (VisiOccludedFlags.size() < w || (VisiOccludedFlags.size() > 0 && VisiOccludedFlags[0].size() < h)) {
            VisiOccludedFlags.resize(w, std::vector<std::vector<bool>>(h, std::vector<bool>(2)));
            VisiCulledFlags.resize(w, std::vector<bool>(h));
            StencilValues.resize(w, std::vector<std::vector<short>>(h, std::vector<short>(2)));
            FlattenGrassEtc.resize(w, std::vector<bool>(h));
        }
    }
};

} // namespace iso
} // namespace zombie
