#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoFireManager/FireSounds.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace objects {


class IsoFireManager {
public:
    static double Red_Oscilator = 0.0;
    static double Green_Oscilator = 0.0;
    static double Blue_Oscilator = 0.0;
    static double Red_Oscilator_Rate = 0.1F;
    static double Green_Oscilator_Rate = 0.13F;
    static double Blue_Oscilator_Rate = 0.0876F;
    static double Red_Oscilator_Val = 0.0;
    static double Green_Oscilator_Val = 0.0;
    static double Blue_Oscilator_Val = 0.0;
    static double OscilatorSpeedScalar = 15.6F;
    static double OscilatorEffectScalar = 0.0039F;
    static int MaxFireObjects = 75;
    static int FireRecalcDelay = 25;
    static int FireRecalc = FireRecalcDelay;
    static bool LightCalcFromBurningCharacters = false;
    static float FireAlpha = 1.0F;
    static float SmokeAlpha = 0.3F;
    static float FireAnimDelay = 0.2F;
    static float SmokeAnimDelay = 0.2F;
    static ColorInfo FireTintMod = std::make_shared<ColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
    static ColorInfo SmokeTintMod = std::make_shared<ColorInfo>(0.5F, 0.5F, 0.5F, 1.0F);
   public static const std::vector<IsoFire> FireStack = std::make_unique<std::vector<>>();
   public static const std::vector<IsoGameCharacter> CharactersOnFire_Stack = std::make_unique<std::vector<>>();
    static const FireSounds fireSounds = std::make_shared<FireSounds>(20);
   private static std::stack<IsoFire> updateStack = std::make_unique<std::stack<>>();
   private static const std::unordered_set<IsoGameCharacter> charactersOnFire = std::make_unique<std::unordered_set<>>();

    static void Add(IsoFire var0) {
      if (FireStack.contains(var0)) {
         System.out.println("IsoFireManager.Add already added fire, ignoring");
      } else {
         if (FireStack.size() < MaxFireObjects) {
            FireStack.push_back(var0);
         } else {
    IsoFire var1 = nullptr;
    int var2 = 0;

            for (int var3 = 0; var3 < FireStack.size(); var3++) {
               if (FireStack.get(var3).Age > var2) {
                  var2 = FireStack.get(var3).Age;
                  var1 = FireStack.get(var3);
               }
            }

            if (var1 != nullptr && var1.square != nullptr) {
               var1.square.getProperties().UnSet(IsoFlagType.burning);
               var1.square.getProperties().UnSet(IsoFlagType.smoke);
               var1.RemoveAttachedAnims();
               var1.removeFromWorld();
               var1.removeFromSquare();
            }

            FireStack.push_back(var0);
         }
      }
   }

    static void AddBurningCharacter(IsoGameCharacter var0) {
      for (int var1 = 0; var1 < CharactersOnFire_Stack.size(); var1++) {
         if (CharactersOnFire_Stack.get(var1) == var0) {
            return;
         }
      }

      CharactersOnFire_Stack.push_back(var0);
   }

    static void Fire_LightCalc(IsoGridSquare var0, IsoGridSquare var1, int var2) {
      if (var1 != nullptr && var0 != nullptr) {
    int var3 = 0;
    uint8_t var4 = 8;
         var3 += Math.abs(var1.getX() - var0.getX());
         var3 += Math.abs(var1.getY() - var0.getY());
         var3 += Math.abs(var1.getZ() - var0.getZ());
         if (var3 <= var4) {
    float var5 = 0.199F / var4 * (var4 - var3);
    float var7 = var5 * 0.6F;
    float var8 = var5 * 0.4F;
            if (var1.getLightInfluenceR() == nullptr) {
               var1.setLightInfluenceR(std::make_unique<std::vector>());
            }

            var1.getLightInfluenceR().push_back(var5);
            if (var1.getLightInfluenceG() == nullptr) {
               var1.setLightInfluenceG(std::make_unique<std::vector>());
            }

            var1.getLightInfluenceG().push_back(var7);
            if (var1.getLightInfluenceB() == nullptr) {
               var1.setLightInfluenceB(std::make_unique<std::vector>());
            }

            var1.getLightInfluenceB().push_back(var8);
    ColorInfo var9 = var1.lighting[var2].lightInfo();
            var9.r += var5;
            var9.g += var7;
            var9.b += var8;
            if (var9.r > 1.0F) {
               var9.r = 1.0F;
            }

            if (var9.g > 1.0F) {
               var9.g = 1.0F;
            }

            if (var9.b > 1.0F) {
               var9.b = 1.0F;
            }
         }
      }
   }

    static void LightTileWithFire(IsoGridSquare var0) {
   }

    static void explode(IsoCell var0, IsoGridSquare var1, int var2) {
      if (var1 != nullptr) {
    IsoGridSquare var3 = nullptr;
    void* var4 = nullptr;
         FireRecalc = 1;

         for (int var5 = -2; var5 <= 2; var5++) {
            for (int var6 = -2; var6 <= 2; var6++) {
               for (int var7 = 0; var7 <= 1; var7++) {
                  var3 = var0.getGridSquare(var1.getX() + var5, var1.getY() + var6, var1.getZ() + var7);
                  if (var3 != nullptr && Rand.Next(100) < var2 && IsoFire.CanAddFire(var3, true)) {
                     StartFire(var0, var3, true, Rand.Next(100, 250 + var2));
                     var3.BurnWalls(true);
                  }
               }
            }
         }
      }
   }

    static void MolotovSmash(IsoCell var0, IsoGridSquare var1) {
   }

    static void Remove(IsoFire var0) {
      if (!FireStack.contains(var0)) {
         System.out.println("IsoFireManager.Remove unknown fire, ignoring");
      } else {
         FireStack.remove(var0);
      }
   }

    static void RemoveBurningCharacter(IsoGameCharacter var0) {
      CharactersOnFire_Stack.remove(var0);
   }

    static void StartFire(IsoCell var0, IsoGridSquare var1, bool var2, int var3, int var4) {
      if (var1.getFloor() != nullptr && var1.getFloor().getSprite() != nullptr) {
         var3 -= var1.getFloor().getSprite().firerequirement;
      }

      if (var3 < 5) {
         var3 = 5;
      }

      if (IsoFire.CanAddFire(var1, var2)) {
         if (GameClient.bClient) {
            DebugLog.General.warn("The StartFire function was called on Client");
         } else if (GameServer.bServer) {
            GameServer.startFireOnClient(var1, var3, var2, var4, false);
         } else {
    IsoFire var5 = std::make_shared<IsoFire>(var0, var1, var2, var3, var4);
            Add(var5);
            var1.getObjects().push_back(var5);
            if (Rand.Next(5) == 0) {
               WorldSoundManager.instance.addSound(var5, var1.getX(), var1.getY(), var1.getZ(), 20, 20);
            }
         }
      }
   }

    static void StartSmoke(IsoCell var0, IsoGridSquare var1, bool var2, int var3, int var4) {
      if (IsoFire.CanAddSmoke(var1, var2)) {
         if (GameClient.bClient) {
    ByteBufferWriter var6 = GameClient.connection.startPacket();
            PacketType.StartFire.doPacket(var6);
            var6.putInt(var1.getX());
            var6.putInt(var1.getY());
            var6.putInt(var1.getZ());
            var6.putInt(var3);
            var6.putBoolean(var2);
            var6.putInt(var4);
            var6.putBoolean(true);
            PacketType.StartFire.send(GameClient.connection);
         } else if (GameServer.bServer) {
            GameServer.startFireOnClient(var1, var3, var2, var4, true);
         } else {
    IsoFire var5 = std::make_shared<IsoFire>(var0, var1, var2, var3, var4, true);
            Add(var5);
            var1.getObjects().push_back(var5);
         }
      }
   }

    static void StartFire(IsoCell var0, IsoGridSquare var1, bool var2, int var3) {
      StartFire(var0, var1, var2, var3, 0);
   }

    static void addCharacterOnFire(IsoGameCharacter var0) {
      /* synchronized - TODO: add std::mutex */ (charactersOnFire) {
         charactersOnFire.push_back(var0);
      }
   }

    static void deleteCharacterOnFire(IsoGameCharacter var0) {
      /* synchronized - TODO: add std::mutex */ (charactersOnFire) {
         charactersOnFire.remove(var0);
      }
   }

    static void Update() {
      /* synchronized - TODO: add std::mutex */ (charactersOnFire) {
         charactersOnFire.forEach(IsoGameCharacter::SpreadFireMP);
      }

      Red_Oscilator_Val = Math.sin(Red_Oscilator = Red_Oscilator + Blue_Oscilator_Rate * OscilatorSpeedScalar);
      Green_Oscilator_Val = Math.sin(Green_Oscilator = Green_Oscilator + Blue_Oscilator_Rate * OscilatorSpeedScalar);
      Blue_Oscilator_Val = Math.sin(Blue_Oscilator = Blue_Oscilator + Blue_Oscilator_Rate * OscilatorSpeedScalar);
      Red_Oscilator_Val = (Red_Oscilator_Val + 1.0) / 2.0;
      Green_Oscilator_Val = (Green_Oscilator_Val + 1.0) / 2.0;
      Blue_Oscilator_Val = (Blue_Oscilator_Val + 1.0) / 2.0;
      Red_Oscilator_Val = Red_Oscilator_Val * OscilatorEffectScalar;
      Green_Oscilator_Val = Green_Oscilator_Val * OscilatorEffectScalar;
      Blue_Oscilator_Val = Blue_Oscilator_Val * OscilatorEffectScalar;
      updateStack.clear();
      updateStack.addAll(FireStack);

      for (int var3 = 0; var3 < updateStack.size(); var3++) {
    IsoFire var1 = updateStack.get(var3);
         if (var1.getObjectIndex() != -1 && FireStack.contains(var1)) {
            var1.update();
         }
      }

      FireRecalc--;
      if (FireRecalc < 0) {
         FireRecalc = FireRecalcDelay;
      }

      fireSounds.update();
   }

    static void updateSound(IsoFire var0) {
      fireSounds.addFire(var0);
   }

    static void stopSound(IsoFire var0) {
      fireSounds.removeFire(var0);
   }

    static void RemoveAllOn(IsoGridSquare var0) {
      for (int var1 = FireStack.size() - 1; var1 >= 0; var1--) {
    IsoFire var2 = FireStack.get(var1);
         if (var2.square == var0) {
            var2.extinctFire();
         }
      }
   }

    static void Reset() {
      FireStack.clear();
      CharactersOnFire_Stack.clear();
      fireSounds.Reset();
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
