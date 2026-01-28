#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
// #include "OpenAL/OpenALManager.h" // Use OpenAL equivalents if needed
#include "zombie/GameSounds.h"
#include "zombie/SoundManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/radio/StorySounds/StoryEmitter/Sound.h"
#include <algorithm>

namespace zombie {
namespace radio {
namespace StorySounds {


class StoryEmitter {
public:
    int max = -1;
    float volumeMod = 1.0F;
    bool coordinate3D = true;
   public std::stack<Sound> SoundStack = std::make_unique<std::stack<>>();
   public std::vector<Sound> Instances = std::make_unique<std::vector<>>();
   public std::vector<Sound> ToStart = std::make_unique<std::vector<>>();
    Vector2 soundVect = std::make_shared<Vector2>();
    Vector2 playerVect = std::make_shared<Vector2>();

    int stopSound(long var1) {
      return OpenALSystem::Channel_Stop(var1);
   }

    long playSound(const std::string& var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      if (this.max != -1 && this.max <= this.Instances.size() + this.ToStart.size()) {
    return 0L;
      } else {
    GameSound var8 = GameSounds.getSound(var1);
         if (var8 == nullptr) {
    return 0L;
         } else {
    GameSoundClip var9 = var8.getRandomClip();
   long var10 = OpenALManager::instance.loadSound(var1);
            if (var10 == 0L) {
    return 0L;
            } else {
    Sound var12;
               if (this.SoundStack.empty()) {
                  var12 = std::make_unique<Sound>();
               } else {
                  var12 = this.SoundStack.pop();
               }

               var12.minRange = var6;
               var12.maxRange = var7;
               var12.x = var3;
               var12.y = var4;
               var12.z = var5;
               var12.volume = SoundManager.instance.getSoundVolume() * var2 * this.volumeMod;
               var12.sound = var10;
               var12.channel = OpenALSystem::PlaySound(var10, true);
               this.ToStart.push_back(var12);
               OpenALSystem::Channel_Set3DAttributes(
                  var12.channel,
                  var12.x - IsoPlayer.getInstance().x,
                  var12.y - IsoPlayer.getInstance().y,
                  var12.z - IsoPlayer.getInstance().z,
                  0.0F,
                  0.0F,
                  0.0F
               );
               OpenALSystem::Channel_Set3DOcclusion(var12.channel, 1.0F, 1.0F);
               if (IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().Traits.Deaf.isSet()) {
                  OpenALSystem::Channel_SetVolume(var12.channel, 0.0F);
               } else {
                  OpenALSystem::Channel_SetVolume(var12.channel, var12.volume);
               }

               return var12.channel;
            }
         }
      }
   }

    void tick() {
      for (int var1 = 0; var1 < this.ToStart.size(); var1++) {
    Sound var2 = this.ToStart.get(var1);
         OpenALSystem::Channel_SetPaused(var2.channel, false);
         this.Instances.push_back(var2);
      }

      this.ToStart.clear();

      for (int var12 = 0; var12 < this.Instances.size(); var12++) {
    Sound var13 = this.Instances.get(var12);
         if (!OpenALSystem::Channel_IsPlaying(var13.channel)) {
            this.SoundStack.push(var13);
            this.Instances.remove(var13);
            var12--;
         } else {
            float var3 = IsoUtils.DistanceManhatten(var13.x, var13.y, IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, var13.z, IsoPlayer.getInstance().z)
               / var13.maxRange;
            if (var3 > 1.0F) {
               var3 = 1.0F;
            }

            if (!this.coordinate3D) {
               OpenALSystem::Channel_Set3DAttributes(
                  var13.channel,
                  Math.abs(var13.x - IsoPlayer.getInstance().x),
                  Math.abs(var13.y - IsoPlayer.getInstance().y),
                  Math.abs(var13.z - IsoPlayer.getInstance().z),
                  0.0F,
                  0.0F,
                  0.0F
               );
            } else {
               OpenALSystem::Channel_Set3DAttributes(
                  var13.channel,
                  Math.abs(var13.x - IsoPlayer.getInstance().x),
                  Math.abs(var13.z - IsoPlayer.getInstance().z),
                  Math.abs(var13.y - IsoPlayer.getInstance().y),
                  0.0F,
                  0.0F,
                  0.0F
               );
            }

            OpenALSystem::SetReverbDefault(0, OpenALManager::PRESET_MOUNTAINS);
            OpenALSystem::Channel_SetReverbProperties(var13.channel, 0, 1.0F);
            OpenALSystem::Channel_Set3DMinMaxDistance(var13.channel, var13.minRange, var13.maxRange);
    float var4 = 0.0F;
    float var5 = 0.0F;
    IsoGridSquare var6 = IsoPlayer.getInstance().getCurrentSquare();
            this.soundVect.set(var13.x, var13.y);
            this.playerVect.set(IsoPlayer.getInstance().x, IsoPlayer.getInstance().y);
    float var7 = (float)Math.toDegrees(this.playerVect.angleTo(this.soundVect));
    float var8 = (float)Math.toDegrees(IsoPlayer.getInstance().getForwardDirection().getDirectionNeg());
            if (var8 >= 0.0F && var8 <= 90.0F) {
               var8 = -90.0F - var8;
            } else if (var8 > 90.0F && var8 <= 180.0F) {
               var8 = 90.0F + (180.0F - var8);
            } else if (var8 < 0.0F && var8 >= -90.0F) {
               var8 = 0.0F - (90.0F + var8);
            } else if (var8 < 0.0F && var8 >= -180.0F) {
               var8 = 90.0F - (180.0F + var8);
            }

    float var9 = Math.abs(var7 - var8) % 360.0F;
    float var10 = var9 > 180.0F ? 360.0F - var9 : var9;
    float var11 = (180.0F - var10) / 180.0F;
            var3 /= 0.4F;
            if (var3 > 1.0F) {
               var3 = 1.0F;
            }

            var4 = 0.85F * var3 * var11;
            var5 = 0.85F * var3 * var11;
            if (var6.getRoom() != nullptr) {
               var4 = 0.75F + 0.1F * var3 + 0.1F * var11;
               var5 = 0.75F + 0.1F * var3 + 0.1F * var11;
            }

            OpenALSystem::Channel_Set3DOcclusion(var13.channel, var4, var5);
         }
      }
   }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
