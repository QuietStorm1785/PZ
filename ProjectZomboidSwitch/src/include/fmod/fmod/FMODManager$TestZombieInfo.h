#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"

namespace fmod {
namespace fmod {


class FMODManager {
public:
    float X;
    float Y;
    long event;
    long inst;

   public FMODManager$TestZombieInfo(long var1, float var3, float var4) {
      this.createZombieInstance(var1, var3, var4);
   }

    long createZombieInstance(long var1, float var3, float var4) {
    long var5 = javafmod.FMOD_Studio_System_CreateEventInstance(var1);
      javafmod.FMOD_Studio_EventInstance3D(var5, var3, var4, 0.0F);
      javafmod.FMOD_Studio_StartEvent(var5);
      this.X = var3;
      this.Y = var4;
      this.event = var1;
      this.inst = var5;
    return var5;
   }
}
} // namespace fmod
} // namespace fmod
