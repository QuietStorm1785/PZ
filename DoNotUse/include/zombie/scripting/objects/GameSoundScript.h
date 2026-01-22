#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSound/MasterVolume.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace scripting {
namespace objects {


class GameSoundScript : public BaseScriptObject {
public:
    const GameSound gameSound = std::make_shared<GameSound>();

    void Load(const std::string& var1, const std::string& var2) {
      this.gameSound.name = var1;
    Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
         std::string[] var6 = var5.string.split("=");
    std::string var7 = var6[0].trim();
    std::string var8 = var6[1].trim();
         if ("category" == var7)) {
            this.gameSound.category = var8;
         } else if ("is3D" == var7)) {
            this.gameSound.is3D = bool.parseBoolean(var8);
         } else if ("loop" == var7)) {
            this.gameSound.loop = bool.parseBoolean(var8);
         } else if ("master" == var7)) {
            this.gameSound.master = MasterVolume.valueOf(var8);
         } else if ("maxInstancesPerEmitter" == var7)) {
            this.gameSound.maxInstancesPerEmitter = PZMath.tryParseInt(var8, -1);
         }
      }

      for (Block var11 : var3.children) {
         if ("clip" == var11.type)) {
    GameSoundClip var12 = this.LoadClip(var11);
            this.gameSound.clips.push_back(var12);
         }
      }
   }

    GameSoundClip LoadClip(Block var1) {
    GameSoundClip var2 = std::make_shared<GameSoundClip>(this.gameSound);

      for (Value var4 : var1.values) {
         std::string[] var5 = var4.string.split("=");
    std::string var6 = var5[0].trim();
    std::string var7 = var5[1].trim();
         if ("distanceMax" == var6)) {
            var2.distanceMax = int.parseInt(var7);
            var2.initFlags = (short)(var2.initFlags | GameSoundClip.INIT_FLAG_DISTANCE_MAX);
         } else if ("distanceMin" == var6)) {
            var2.distanceMin = int.parseInt(var7);
            var2.initFlags = (short)(var2.initFlags | GameSoundClip.INIT_FLAG_DISTANCE_MIN);
         } else if ("event" == var6)) {
            var2.event = var7;
         } else if ("file" == var6)) {
            var2.file = var7;
         } else if ("pitch" == var6)) {
            var2.pitch = float.parseFloat(var7);
         } else if ("volume" == var6)) {
            var2.volume = float.parseFloat(var7);
         } else if ("reverbFactor" == var6)) {
            var2.reverbFactor = float.parseFloat(var7);
         } else if ("reverbMaxRange" == var6)) {
            var2.reverbMaxRange = float.parseFloat(var7);
         }
      }

    return var2;
   }

    void reset() {
      this.gameSound.reset();
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
