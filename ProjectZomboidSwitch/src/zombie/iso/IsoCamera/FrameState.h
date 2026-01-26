#pragma once
#include <memory>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace iso {

class FrameState {
public:
    int frameCount = 0;
    bool Paused = false;
    int playerIndex = 0;
    float CamCharacterX = 0.0f;
    float CamCharacterY = 0.0f;
    float CamCharacterZ = 0.0f;
    std::shared_ptr<IsoGameCharacter> CamCharacter;
    std::shared_ptr<IsoGridSquare> CamCharacterSquare;
    std::shared_ptr<IsoRoom> CamCharacterRoom;
    float OffX = 0.0f;
    float OffY = 0.0f;
    int OffscreenWidth = 0;
    int OffscreenHeight = 0;

    void set(int idx);
};

} // namespace iso
} // namespace zombie
