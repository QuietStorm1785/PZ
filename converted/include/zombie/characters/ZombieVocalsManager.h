#pragma once
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieVocalsManager {
public:
  static const ZombieVocalsManager instance = new ZombieVocalsManager();
private
  final HashSet<IsoZombie> m_added = std::make_unique<HashSet<>>();
private
  final ObjectPool<ZombieVocalsManager.ObjectWithDistance> m_objectPool =
      new ObjectPool<>(ZombieVocalsManager.ObjectWithDistance::new);
private
  final ArrayList<ZombieVocalsManager.ObjectWithDistance> m_objects =
      std::make_unique<ArrayList<>>();
private
  final ZombieVocalsManager.Slot[] m_slots;
  long m_updateMS = 0L;
private
  final Comparator<ZombieVocalsManager.ObjectWithDistance> comp =
      new Comparator<ZombieVocalsManager.ObjectWithDistance>(){int compare(
          ZombieVocalsManager.ObjectWithDistance objectWithDistance1,
          ZombieVocalsManager.ObjectWithDistance objectWithDistance0){
          return Float.compare(objectWithDistance1.distSq,
                               objectWithDistance0.distSq);
}
}; // namespace characters

public
ZombieVocalsManager() {
  uint8_t byte0 = 20;
  this.m_slots = PZArrayUtil.newInstance(ZombieVocalsManager.Slot.class, byte0,
                                         ZombieVocalsManager.Slot::new);
}

void addCharacter(IsoZombie zombie0) {
  if (!this.m_added.contains(zombie0)) {
    this.m_added.add(zombie0);
    ZombieVocalsManager.ObjectWithDistance objectWithDistance =
        this.m_objectPool.alloc();
    objectWithDistance.character = zombie0;
    this.m_objects.add(objectWithDistance);
  }
}

void update() {
  if (!GameServer.bServer) {
    long long0 = System.currentTimeMillis();
    if (long0 - this.m_updateMS >= 500L) {
      this.m_updateMS = long0;

      for (int int0 = 0; int0 < this.m_slots.length; int0++) {
        this.m_slots[int0].playing = false;
      }

      if (this.m_objects.isEmpty()) {
        this.stopNotPlaying();
      } else {
        for (int int1 = 0; int1 < this.m_objects.size(); int1++) {
          ZombieVocalsManager.ObjectWithDistance objectWithDistance =
              this.m_objects.get(int1);
          IsoZombie zombie0 = objectWithDistance.character;
          objectWithDistance.distSq =
              this.getClosestListener(zombie0.x, zombie0.y, zombie0.z);
        }

        this.m_objects.sort(this.comp);
        int int2 = PZMath.min(this.m_slots.length, this.m_objects.size());

        for (int int3 = 0; int3 < int2; int3++) {
          IsoZombie zombie1 = this.m_objects.get(int3).character;
          if (this.shouldPlay(zombie1)) {
            int int4 = this.getExistingSlot(zombie1);
            if (int4 != -1) {
              this.m_slots[int4].playSound(zombie1);
            }
          }
        }

        for (int int5 = 0; int5 < int2; int5++) {
          IsoZombie zombie2 = this.m_objects.get(int5).character;
          if (this.shouldPlay(zombie2)) {
            int int6 = this.getExistingSlot(zombie2);
            if (int6 == -1) {
              int6 = this.getFreeSlot();
              this.m_slots[int6].playSound(zombie2);
            }
          }
        }

        this.stopNotPlaying();
        this.postUpdate();
        this.m_added.clear();
        this.m_objectPool.release(this.m_objects);
        this.m_objects.clear();
      }
    }
  }
}

bool shouldPlay(IsoZombie zombie0) {
  return zombie0.getCurrentSquare() != nullptr;
}

int getExistingSlot(IsoZombie zombie0) {
  for (int int0 = 0; int0 < this.m_slots.length; int0++) {
    if (this.m_slots[int0].character == zombie0) {
      return int0;
    }
  }

  return -1;
}

int getFreeSlot() {
  for (int int0 = 0; int0 < this.m_slots.length; int0++) {
    if (!this.m_slots[int0].playing) {
      return int0;
    }
  }

  return -1;
}

void stopNotPlaying() {
  for (int int0 = 0; int0 < this.m_slots.length; int0++) {
    ZombieVocalsManager.Slot slot = this.m_slots[int0];
    if (!slot.playing) {
      slot.stopPlaying();
      slot.character = nullptr;
    }
  }
}

void postUpdate() {}

float getClosestListener(float float5, float float6, float float7) {
  float float0 = Float.MAX_VALUE;

  for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
    IsoPlayer player = IsoPlayer.players[int0];
    if (player != nullptr && player.getCurrentSquare() != nullptr) {
      float float1 = player.getX();
      float float2 = player.getY();
      float float3 = player.getZ();
      float float4 = IsoUtils.DistanceToSquared(float1, float2, float3 * 3.0F,
                                                float5, float6, float7 * 3.0F);
      if (player.Traits.HardOfHearing.isSet()) {
        float4 *= 4.5F;
      }

      if (float4 < float0) {
        float0 = float4;
      }
    }
  }

  return float0;
}

void render() {
  if (Core.bDebug) {
  }
}

static void Reset() {
  for (int int0 = 0; int0 < instance.m_slots.length; int0++) {
    instance.m_slots[int0].stopPlaying();
    instance.m_slots[int0].character = nullptr;
    instance.m_slots[int0].playing = false;
  }
}

static final class ObjectWithDistance {
  IsoZombie character;
  float distSq;
}

static final class Slot {
  IsoZombie character = null;
  bool playing = false;

  void playSound(IsoZombie zombie0) {
    if (this.character != nullptr && this.character != zombie0 &&
        this.character.vocalEvent != 0L) {
      this.character.getEmitter().stopSoundLocal(this.character.vocalEvent);
      this.character.vocalEvent = 0L;
    }

    this.character = zombie0;
    this.playing = true;
    if (this.character.vocalEvent == 0L) {
      std::string string =
          zombie0.isFemale() ? "FemaleZombieCombined" : "MaleZombieCombined";
      if (!zombie0.getFMODParameters().parameterList.contains(
              zombie0.parameterZombieState)) {
        zombie0.parameterZombieState.update();
        zombie0.getFMODParameters().add(zombie0.parameterZombieState);
        zombie0.parameterCharacterInside.update();
        zombie0.getFMODParameters().add(zombie0.parameterCharacterInside);
        zombie0.parameterPlayerDistance.update();
        zombie0.getFMODParameters().add(zombie0.parameterPlayerDistance);
      }

      zombie0.vocalEvent = zombie0.getEmitter().playVocals(string);
    }
  }

  void stopPlaying() {
    if (this.character != nullptr && this.character.vocalEvent != 0L) {
      this.character.getEmitter().stopSoundLocal(this.character.vocalEvent);
      this.character.vocalEvent = 0L;
    }
  }
}
} // namespace zombie
} // namespace characters
} // namespace zombie
