#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistic.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace physics {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Bullet {
public:
  static ByteBuffer cmdBuf;
  static const uint8_t TO_ADD_VEHICLE = 4;
  static const uint8_t TO_SCROLL_CHUNKMAP = 5;
  static const uint8_t TO_ACTIVATE_CHUNKMAP = 6;
  static const uint8_t TO_INIT_WORLD = 7;
  static const uint8_t TO_UPDATE_CHUNK = 8;
  static const uint8_t TO_DEBUG_DRAW_WORLD = 9;
  static const uint8_t TO_STEP_SIMULATION = 10;
  static const uint8_t TO_UPDATE_PLAYER_LIST = 12;
  static const uint8_t TO_END = -1;

  static void init() {
    std::string string0 = "";
    if ("1" == System.getProperty("zomboid.debuglibs.bullet"))) {
        DebugLog.log("***** Loading debug version of PZBullet");
        string0 = "d";
      }

    std::string string1 = "";
    if (GameServer.bServer && GameWindow.OSValidator.isUnix()) {
      string1 = "NoOpenGL";
    }

    if (System.getProperty("os.name").contains("OS X")) {
      System.loadLibrary("PZBullet");
    } else if (System.getProperty("sun.arch.data.model") == "64")) {
            System.loadLibrary("PZBullet" + string1 + "64" + string0);
        }
    else {
      System.loadLibrary("PZBullet" + string1 + "32" + string0);
    }

    cmdBuf = ByteBuffer.allocateDirect(4096);
    cmdBuf.order(ByteOrder.LITTLE_ENDIAN);
  }

private
  static native void ToBullet(ByteBuffer var0);

  static void CatchToBullet(ByteBuffer byteBuffer) {
    try {
      MPStatistic.getInstance().Bullet.Start();
      ToBullet(byteBuffer);
      MPStatistic.getInstance().Bullet.End();
    } catch (RuntimeException runtimeException) {
      runtimeException.printStackTrace();
    }
  }

public
  static native void initWorld(int var0, int var1, boolean var2);

public
  static native void destroyWorld();

public
  static native void activateChunkMap(int var0, int var1, int var2, int var3);

public
  static native void deactivateChunkMap(int var0);

  static void initWorld(int int0, int int1, int int2, int int3, int int4) {
    MPStatistic.getInstance().Bullet.Start();
    initWorld(int0, int1, GameServer.bServer);
    activateChunkMap(0, int2, int3, int4);
    MPStatistic.getInstance().Bullet.End();
  }

  static void updatePlayerList(ArrayList<IsoPlayer> arrayList) {
    cmdBuf.clear();
    cmdBuf.put((byte)12);
    cmdBuf.putShort((short)arrayList.size());

    for (auto &player : arrayList)
      cmdBuf.putInt(player.OnlineID);
    cmdBuf.putInt((int)player.getX());
    cmdBuf.putInt((int)player.getY());
  }

  cmdBuf.put((byte)-1);
  cmdBuf.put((byte)-1);
  CatchToBullet(cmdBuf);
}

static void
beginUpdateChunk(IsoChunk chunk) {
  cmdBuf.clear();
  cmdBuf.put((byte)8);
  cmdBuf.putShort((short)chunk.wx);
  cmdBuf.putShort((short)chunk.wy);
}

static void updateChunk(int int0, int int1, int int2, int int3, byte[] bytes) {
  cmdBuf.put((byte)int0);
  cmdBuf.put((byte)int1);
  cmdBuf.put((byte)int2);
  cmdBuf.put((byte)int3);

  for (int int4 = 0; int4 < int3; int4++) {
    cmdBuf.put(bytes[int4]);
  }
}

static void endUpdateChunk() {
  if (cmdBuf.position() != 5) {
    cmdBuf.put((byte)-1);
    cmdBuf.put((byte)-1);
    CatchToBullet(cmdBuf);
  }
}

public
static native void scrollChunkMap(int var0, int var1);

static void scrollChunkMapLeft(int int0) {
  MPStatistic.getInstance().Bullet.Start();
  scrollChunkMap(int0, 0);
  MPStatistic.getInstance().Bullet.End();
}

static void scrollChunkMapRight(int int0) {
  MPStatistic.getInstance().Bullet.Start();
  scrollChunkMap(int0, 1);
  MPStatistic.getInstance().Bullet.End();
}

static void scrollChunkMapUp(int int0) {
  MPStatistic.getInstance().Bullet.Start();
  scrollChunkMap(int0, 2);
  MPStatistic.getInstance().Bullet.End();
}

static void scrollChunkMapDown(int int0) {
  MPStatistic.getInstance().Bullet.Start();
  scrollChunkMap(int0, 3);
  MPStatistic.getInstance().Bullet.End();
}

static void setVehicleActive(BaseVehicle vehicle, bool boolean0) {
  vehicle.isActive = boolean0;
  setVehicleActive(vehicle.getId(), boolean0);
}

static int setVehicleStatic(BaseVehicle vehicle, bool boolean0) {
  vehicle.isStatic = boolean0;
  return setVehicleStatic();
}

public
static native void addVehicle(int var0, float var1, float var2, float var3,
                              float var4, float var5, float var6, float var7,
                              String var8);

public
static native void removeVehicle(int var0);

public
static native void controlVehicle(int var0, float var1, float var2, float var3);

public
static native void setVehicleActive(int var0, boolean var1);

public
static native void applyCentralForceToVehicle(int var0, float var1, float var2,
                                              float var3);

public
static native void applyTorqueToVehicle(int var0, float var1, float var2,
                                        float var3);

public
static native void teleportVehicle(int var0, float var1, float var2, float var3,
                                   float var4, float var5, float var6,
                                   float var7);

public
static native void setTireInflation(int var0, int var1, float var2);

public
static native void setTireRemoved(int var0, int var1, boolean var2);

public
static native void stepSimulation(float var0, int var1, float var2);

public
static native int getVehicleCount();

public
static native int getVehiclePhysics(int var0, float[] var1);

public
static native int getOwnVehiclePhysics(int var0, float[] var1);

public
static native int setOwnVehiclePhysics(int var0, float[] var1);

public
static native int setVehicleParams(int var0, float[] var1);

public
static native int setVehicleMass(int var0, float var1);

public
static native int getObjectPhysics(float[] var0);

public
static native void createServerCell(int var0, int var1);

public
static native void removeServerCell(int var0, int var1);

public
static native int addPhysicsObject(float var0, float var1);

public
static native void defineVehicleScript(String var0, float[] var1);

public
static native void setVehicleVelocityMultiplier(int var0, float var1,
                                                float var2);

public
static native int setVehicleStatic(int var0, boolean var1);

public
static native int addHingeConstraint(int var0, int var1, float var2, float var3,
                                     float var4, float var5, float var6,
                                     float var7);

public
static native int addPointConstraint(int var0, int var1, float var2, float var3,
                                     float var4, float var5, float var6,
                                     float var7);

public
static native int addRopeConstraint(int var0, int var1, float var2, float var3,
                                    float var4, float var5, float var6,
                                    float var7, float var8);

public
static native void removeConstraint(int var0);
}
} // namespace physics
} // namespace core
} // namespace zombie
