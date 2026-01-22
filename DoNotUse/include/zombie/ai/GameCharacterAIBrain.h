#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/states/ThumpState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Stance.h"
#include "zombie/characters/Stats.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/SurvivorGroup.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include <algorithm>

namespace zombie {
namespace ai {


class GameCharacterAIBrain {
public:
    const IsoGameCharacter character;
   public const std::vector<IsoGameCharacter> spottedCharacters = std::make_unique<std::vector<>>();
    bool StepBehaviors;
    Stance stance;
    bool controlledByAdvancedPathfinder;
    bool isInMeta;
   public const std::unordered_map<Vector3, std::vector<Vector3>> BlockedMemories = std::make_unique<std::unordered_map<>>();
    const Vector2 AIFocusPoint = std::make_shared<Vector2>();
    const Vector3 nextPathTarget = std::make_shared<Vector3>();
    IsoMovingObject aiTarget;
    bool NextPathNodeInvalidated;
    const AIBrainPlayerControlVars HumanControlVars = std::make_shared<AIBrainPlayerControlVars>();
    std::string order;
   public std::vector<IsoZombie> teammateChasingZombies = std::make_unique<std::vector<>>();
   public std::vector<IsoZombie> chasingZombies = std::make_unique<std::vector<>>();
    bool allowLongTermTick = true;
    bool isAI = false;
   static std::vector<IsoZombie> tempZombies = std::make_unique<std::vector<>>();
    static IsoGameCharacter compare;
   private static const std::stack<Vector3> Vectors = std::make_unique<std::stack<>>();

    IsoGameCharacter getCharacter() {
      return this.character;
   }

    public GameCharacterAIBrain(IsoGameCharacter var1) {
      this.character = var1;
   }

    void update() {
   }

    void postUpdateHuman(IsoPlayer var1) {
   }

    std::string getOrder() {
      return this.order;
   }

    void setOrder(const std::string& var1) {
      this.order = var1;
   }

    SurvivorGroup getGroup() {
      return this.character.getDescriptor().getGroup();
   }

    int getCloseZombieCount() {
      this.character.getStats();
      return Stats.NumCloseZombies;
   }

    IsoZombie getClosestChasingZombie(bool var1) {
    IsoZombie var2 = nullptr;
    float var3 = 1.0E7F;

      for (int var4 = 0; var4 < this.chasingZombies.size(); var4++) {
    IsoZombie var5 = this.chasingZombies.get(var4);
    float var6 = var5.DistTo(this.character);
         if (var5.isOnFloor()) {
            var6 += 2.0F;
         }

         if (!LosUtil.lineClearCollide((int)var5.x, (int)var5.y, (int)var5.z, (int)this.character.x, (int)this.character.y, (int)this.character.z, false)
            && var5.getStateMachine().getCurrent() != ThumpState.instance()
            && var6 < var3
            && var5.target == this.character) {
            var3 = var6;
            var2 = this.chasingZombies.get(var4);
         }
      }

      if (var2 == nullptr && var1) {
         for (int var8 = 0; var8 < this.getGroup().Members.size(); var8++) {
    IsoGameCharacter var10 = ((SurvivorDesc)this.getGroup().Members.get(var8)).getInstance();
    IsoZombie var12 = var10.getGameCharacterAIBrain().getClosestChasingZombie(false);
            if (var12 != nullptr) {
    float var7 = var12.DistTo(this.character);
               if (var7 < var3) {
                  var3 = var7;
                  var2 = var12;
               }
            }
         }
      }

      if (var2 == nullptr && var1) {
         for (int var9 = 0; var9 < this.spottedCharacters.size(); var9++) {
    IsoGameCharacter var11 = this.spottedCharacters.get(var9);
    IsoZombie var13 = var11.getGameCharacterAIBrain().getClosestChasingZombie(false);
            if (var13 != nullptr) {
    float var14 = var13.DistTo(this.character);
               if (var14 < var3) {
                  var3 = var14;
                  var2 = var13;
               }
            }
         }
      }

      return var2 != nullptr && var2.DistTo(this.character) > 30.0F ? nullptr : var2;
   }

    IsoZombie getClosestChasingZombie() {
      return this.getClosestChasingZombie(true);
   }

   public std::vector<IsoZombie> getClosestChasingZombies(int var1) {
      tempZombies.clear();
    void* var2 = nullptr;
    float var3 = 1.0E7F;

      for (int var4 = 0; var4 < this.chasingZombies.size(); var4++) {
    IsoZombie var5 = this.chasingZombies.get(var4);
    float var6 = var5.DistTo(this.character);
         if (!LosUtil.lineClearCollide((int)var5.x, (int)var5.y, (int)var5.z, (int)this.character.x, (int)this.character.y, (int)this.character.z, false)) {
            tempZombies.push_back(var5);
         }
      }

      compare = this.character;
      tempZombies.sort((var0, var1x) -> {
    float var2x = compare.DistTo(var0);
    float var3x = compare.DistTo(var1x);
         if (var2x > var3x) {
    return 1;
         } else {
            return var2x < var3x ? -1 : 0;
         }
      });
    int var7 = var1 - tempZombies.size();
      if (var7 > tempZombies.size() - 2) {
         var7 = tempZombies.size() - 2;
      }

      for (int var8 = 0; var8 < var7; var8++) {
         tempZombies.remove(tempZombies.size() - 1);
      }

    return tempZombies;
   }

    void AddBlockedMemory(int var1, int var2, int var3) {
      /* synchronized - TODO: add std::mutex */ (this.BlockedMemories) {
    Vector3 var5 = std::make_shared<Vector3>((int)this.character.x, (int)this.character.y, (int)this.character.z);
         if (!this.BlockedMemories.containsKey(var5)) {
            this.BlockedMemories.put(var5, std::make_unique<std::vector<>>());
         }

    std::vector var6 = this.BlockedMemories.get(var5);
    Vector3 var7 = std::make_shared<Vector3>(var1, var2, var3);
         if (!var6.contains(var7)) {
            var6.push_back(var7);
         }
      }
   }

    bool HasBlockedMemory(int var1, int var2, int var3, int var4, int var5, int var6) {
      /* synchronized - TODO: add std::mutex */ (this.BlockedMemories) {
         /* synchronized - TODO: add std::mutex */ (Vectors) {
    Vector3 var7;
            if (Vectors.empty()) {
               var7 = std::make_unique<Vector3>();
            } else {
               var7 = Vectors.pop();
            }

    Vector3 var8;
            if (Vectors.empty()) {
               var8 = std::make_unique<Vector3>();
            } else {
               var8 = Vectors.pop();
            }

            var7.x = var1;
            var7.y = var2;
            var7.z = var3;
            var8.x = var4;
            var8.y = var5;
            var8.z = var6;
            if (!this.BlockedMemories.containsKey(var7)) {
               Vectors.push(var7);
               Vectors.push(var8);
    return false;
            }

            if (this.BlockedMemories.get(var7).contains(var8)) {
               Vectors.push(var7);
               Vectors.push(var8);
    return true;
            }

            Vectors.push(var7);
            Vectors.push(var8);
         }

    return false;
      }
   }

    void renderlast() {
   }
}
} // namespace ai
} // namespace zombie
