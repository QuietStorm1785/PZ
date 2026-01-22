#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/areas/IsoRoom.h"

namespace zombie {
namespace iso {


class IsoCamera {
public:
    int frameCount;
    bool Paused;
    int playerIndex;
    float CamCharacterX;
    float CamCharacterY;
    float CamCharacterZ;
    IsoGameCharacter CamCharacter;
    IsoGridSquare CamCharacterSquare;
    IsoRoom CamCharacterRoom;
    float OffX;
    float OffY;
    int OffscreenWidth;
    int OffscreenHeight;

    void set(int var1) {
      this.Paused = GameTime.isGamePaused();
      this.playerIndex = var1;
      this.CamCharacter = IsoPlayer.players[var1];
      this.CamCharacterX = this.CamCharacter.getX();
      this.CamCharacterY = this.CamCharacter.getY();
      this.CamCharacterZ = this.CamCharacter.getZ();
      this.CamCharacterSquare = this.CamCharacter.getCurrentSquare();
      this.CamCharacterRoom = this.CamCharacterSquare == nullptr ? nullptr : this.CamCharacterSquare.getRoom();
      this.OffX = IsoCamera.getOffX();
      this.OffY = IsoCamera.getOffY();
      this.OffscreenWidth = IsoCamera.getOffscreenWidth(var1);
      this.OffscreenHeight = IsoCamera.getOffscreenHeight(var1);
   }
}
} // namespace iso
} // namespace zombie
