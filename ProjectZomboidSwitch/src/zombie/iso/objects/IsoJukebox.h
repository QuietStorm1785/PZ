#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoJukebox : public IsoObject {
public:
    Audio JukeboxTrack = nullptr;
    bool IsPlaying = false;
    float MusicRadius = 30.0F;
    bool Activated = false;
    int WorldSoundPulseRate = 150;
    int WorldSoundPulseDelay = 0;

    public IsoJukebox(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    std::string getObjectName() {
      return "Jukebox";
   }

    public IsoJukebox(IsoCell var1) {
      super(var1);
   }

    public IsoJukebox(IsoCell var1, IsoGridSquare var2, const std::string& var3) {
      super(var1, var2, var3);
      this.JukeboxTrack = nullptr;
      this.IsPlaying = false;
      this.Activated = false;
      this.WorldSoundPulseDelay = 0;
   }

    void addToWorld() {
      super.addToWorld();
      this.getCell().addToStaticUpdaterObjectList(this);
   }

    void SetPlaying(bool var1) {
      if (this.IsPlaying != var1) {
         this.IsPlaying = var1;
         if (this.IsPlaying && this.JukeboxTrack == nullptr) {
    std::string var2 = nullptr;
            switch (Rand.Next(4)) {
               case 0:
                  var2 = "paws1";
                  break;
               case 1:
                  var2 = "paws2";
                  break;
               case 2:
                  var2 = "paws3";
                  break;
               case 3:
                  var2 = "paws4";
            }

            this.JukeboxTrack = SoundManager.instance.PlaySound(var2, false, 0.0F);
         }
      }
   }

    bool onMouseLeftClick(int var1, int var2) {
    IsoPlayer var3 = IsoPlayer.getInstance();
      if (var3 == nullptr || var3.isDead()) {
    return false;
      } else if (IsoPlayer.getInstance().getCurrentSquare() == nullptr) {
    return false;
      } else {
    float var4 = 0.0F;
         int var5 = Math.abs(this.square.getX() - IsoPlayer.getInstance().getCurrentSquare().getX())
            + Math.abs(
               this.square.getY()
                  - IsoPlayer.getInstance().getCurrentSquare().getY()
                  + Math.abs(this.square.getZ() - IsoPlayer.getInstance().getCurrentSquare().getZ())
            );
         if (var5 < 4) {
            if (!this.Activated) {
               if (Core.NumJukeBoxesActive < Core.MaxJukeBoxesActive) {
                  this.WorldSoundPulseDelay = 0;
                  this.Activated = true;
                  this.SetPlaying(true);
                  Core.NumJukeBoxesActive++;
               }
            } else {
               this.WorldSoundPulseDelay = 0;
               this.SetPlaying(false);
               this.Activated = false;
               if (this.JukeboxTrack != nullptr) {
                  SoundManager.instance.StopSound(this.JukeboxTrack);
                  this.JukeboxTrack.stop();
                  this.JukeboxTrack = nullptr;
               }

               Core.NumJukeBoxesActive--;
            }
         }

    return true;
      }
   }

    void update() {
      if (IsoPlayer.getInstance() != nullptr) {
         if (IsoPlayer.getInstance().getCurrentSquare() != nullptr) {
            if (this.Activated) {
    float var1 = 0.0F;
               int var2 = Math.abs(this.square.getX() - IsoPlayer.getInstance().getCurrentSquare().getX())
                  + Math.abs(
                     this.square.getY()
                        - IsoPlayer.getInstance().getCurrentSquare().getY()
                        + Math.abs(this.square.getZ() - IsoPlayer.getInstance().getCurrentSquare().getZ())
                  );
               if (var2 < this.MusicRadius) {
                  this.SetPlaying(true);
                  var1 = (this.MusicRadius - var2) / this.MusicRadius;
               }

               if (this.JukeboxTrack != nullptr) {
    float var3 = var1 + 0.2F;
                  if (var3 > 1.0F) {
                     var3 = 1.0F;
                  }

                  SoundManager.instance.BlendVolume(this.JukeboxTrack, var1);
                  if (this.WorldSoundPulseDelay > 0) {
                     this.WorldSoundPulseDelay--;
                  }

                  if (this.WorldSoundPulseDelay == 0) {
                     WorldSoundManager.instance.addSound(IsoPlayer.getInstance(), this.square.getX(), this.square.getY(), this.square.getZ(), 70, 70, true);
                     this.WorldSoundPulseDelay = this.WorldSoundPulseRate;
                  }

                  if (!this.JukeboxTrack.isPlaying()) {
                     this.WorldSoundPulseDelay = 0;
                     this.SetPlaying(false);
                     this.Activated = false;
                     if (this.JukeboxTrack != nullptr) {
                        SoundManager.instance.StopSound(this.JukeboxTrack);
                        this.JukeboxTrack.stop();
                        this.JukeboxTrack = nullptr;
                     }

                     Core.NumJukeBoxesActive--;
                  }
               }
            }
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
