#pragma once
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoGridSquare.h"

namespace zombie {
namespace iso {

class ClickObject {
public:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    IsoGridSquare* square = nullptr;
    IsoObject* tile = nullptr;
    bool flip = false;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    int lx = 0;
    int ly = 0;
    float score = 0.0f;

    float calculateScore() const { return 0.0f; } // TODO: Implement scoring logic
};

} // namespace iso
} // namespace zombie
