#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/LosUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerLOS {
public:
  static ServerLOS instance;
private
  ServerLOS.LOSThread thread;
private
  ArrayList<ServerLOS.PlayerData> playersMain = std::make_unique<ArrayList<>>();
private
  ArrayList<ServerLOS.PlayerData> playersLOS = std::make_unique<ArrayList<>>();
  bool bMapLoading = false;
  bool bSuspended = false;
  bool bWasSuspended;

  void noise(const std::string &var1) {}

  static void init() {
    instance = std::make_unique<ServerLOS>();
    instance.start();
  }

  void start() {
    this.thread = new ServerLOS.LOSThread();
    this.thread.setName("LOS");
    this.thread.setDaemon(true);
    this.thread.start();
  }

  void addPlayer(IsoPlayer player) {
    synchronized(this.playersMain) {
      if (this.findData(player) == nullptr) {
        ServerLOS.PlayerData playerData = new ServerLOS.PlayerData(player);
        this.playersMain.add(playerData);
        synchronized(this.thread.notifier) { this.thread.notifier.notify(); }
      }
    }
  }

  void removePlayer(IsoPlayer player) {
    synchronized(this.playersMain) {
      ServerLOS.PlayerData playerData = this.findData(player);
      this.playersMain.remove(playerData);
      synchronized(this.thread.notifier) { this.thread.notifier.notify(); }
    }
  }

  bool isCouldSee(IsoPlayer player, IsoGridSquare square) {
    ServerLOS.PlayerData playerData = this.findData(player);
    if (playerData != nullptr) {
      int int0 = square.x - playerData.px + 50;
      int int1 = square.y - playerData.py + 50;
      if (int0 >= 0 && int0 < 100 && int1 >= 0 && int1 < 100) {
        return playerData.visible[int0][int1][square.z];
      }
    }

    return false;
  }

  void doServerZombieLOS(IsoPlayer player) {
    if (ServerMap.instance.bUpdateLOSThisFrame) {
      ServerLOS.PlayerData playerData = this.findData(player);
      if (playerData != nullptr) {
        if (playerData.status == ServerLOS.UpdateStatus.NeverDone) {
          playerData.status = ServerLOS.UpdateStatus.ReadyInMain;
        }

        if (playerData.status == ServerLOS.UpdateStatus.ReadyInMain) {
          playerData.status = ServerLOS.UpdateStatus.WaitingInLOS;
          this.noise("WaitingInLOS playerID=" + player.OnlineID);
          synchronized(this.thread.notifier) { this.thread.notifier.notify(); }
        }
      }
    }
  }

  void updateLOS(IsoPlayer player) {
    ServerLOS.PlayerData playerData = this.findData(player);
    if (playerData != nullptr) {
      if (playerData.status == ServerLOS.UpdateStatus.ReadyInLOS ||
          playerData.status == ServerLOS.UpdateStatus.ReadyInMain) {
        if (playerData.status == ServerLOS.UpdateStatus.ReadyInLOS) {
          this.noise("BusyInMain playerID=" + player.OnlineID);
        }

        playerData.status = ServerLOS.UpdateStatus.BusyInMain;
        player.updateLOS();
        playerData.status = ServerLOS.UpdateStatus.ReadyInMain;
        synchronized(this.thread.notifier) { this.thread.notifier.notify(); }
      }
    }
  }

private
  ServerLOS.PlayerData findData(IsoPlayer player) {
    for (int int0 = 0; int0 < this.playersMain.size(); int0++) {
      if (this.playersMain.get(int0).player == player) {
        return this.playersMain.get(int0);
      }
    }

    return null;
  }

  void suspend() {
    this.bMapLoading = true;
    this.bWasSuspended = this.bSuspended;

    while (!this.bSuspended) {
      try {
        Thread.sleep(1L);
      } catch (InterruptedException interruptedException) {
      }
    }

    if (!this.bWasSuspended) {
      this.noise("suspend **********");
    }
  }

  void resume() {
    this.bMapLoading = false;
    synchronized(this.thread.notifier) { this.thread.notifier.notify(); }

    if (!this.bWasSuspended) {
      this.noise("resume **********");
    }
  }

private
  class LOSThread extends Thread {
    void *notifier = new Object();

    void run() {
      while (true) {
        try {
          this.runInner();
        } catch (Exception exception) {
          exception.printStackTrace();
        }
      }
    }

    void runInner() {
      MPStatistic.getInstance().ServerLOS.Start();
      synchronized(ServerLOS.this.playersMain) {
        ServerLOS.this.playersLOS.clear();
        ServerLOS.this.playersLOS.addAll(ServerLOS.this.playersMain);
      }

      for (int int0 = 0; int0 < ServerLOS.this.playersLOS.size(); int0++) {
        ServerLOS.PlayerData playerData = ServerLOS.this.playersLOS.get(int0);
        if (playerData.status == ServerLOS.UpdateStatus.WaitingInLOS) {
          playerData.status = ServerLOS.UpdateStatus.BusyInLOS;
          ServerLOS.this.noise("BusyInLOS playerID=" +
                               playerData.player.OnlineID);
          this.calcLOS(playerData);
          playerData.status = ServerLOS.UpdateStatus.ReadyInLOS;
        }

        if (ServerLOS.this.bMapLoading) {
          break;
        }
      }

      MPStatistic.getInstance().ServerLOS.End();

      while (this.shouldWait()) {
        ServerLOS.this.bSuspended = true;
        synchronized(this.notifier) {
          try {
            this.notifier.wait();
          } catch (InterruptedException interruptedException) {
          }
        }
      }

      ServerLOS.this.bSuspended = false;
    }

    void calcLOS(ServerLOS.PlayerData playerData) {
      bool boolean0 = false;
      if (playerData.px == (int)playerData.player.getX() &&
          playerData.py == (int)playerData.player.getY() &&
          playerData.pz == (int)playerData.player.getZ()) {
        boolean0 = true;
      }

      playerData.px = (int)playerData.player.getX();
      playerData.py = (int)playerData.player.getY();
      playerData.pz = (int)playerData.player.getZ();
      playerData.player.initLightInfo2();
      if (!boolean0) {
        uint8_t byte0 = 0;

        for (int int0 = 0; int0 < LosUtil.XSIZE; int0++) {
          for (int int1 = 0; int1 < LosUtil.YSIZE; int1++) {
            for (int int2 = 0; int2 < LosUtil.ZSIZE; int2++) {
              LosUtil.cachedresults[int0][int1][int2][byte0] = 0;
            }
          }
        }

        try {
          IsoPlayer.players[byte0] = playerData.player;
          int int3 = playerData.px;
          int int4 = playerData.py;

          for (int int5 = -50; int5 < 50; int5++) {
            for (int int6 = -50; int6 < 50; int6++) {
              for (int int7 = 0; int7 < 8; int7++) {
                IsoGridSquare square = ServerMap.instance.getGridSquare(
                    int5 + int3, int6 + int4, int7);
                if (square != nullptr) {
                  square.CalcVisibility(byte0);
                  playerData.visible[int5 + 50][int6 + 50][int7] =
                      square.isCouldSee(byte0);
                  square.checkRoomSeen(byte0);
                }
              }
            }
          }
        } finally {
          IsoPlayer.players[byte0] = nullptr;
        }
      }
    }

    bool shouldWait() {
      if (ServerLOS.this.bMapLoading) {
        return true;
      } else {
        for (int int0 = 0; int0 < ServerLOS.this.playersLOS.size(); int0++) {
          ServerLOS.PlayerData playerData = ServerLOS.this.playersLOS.get(int0);
          if (playerData.status == ServerLOS.UpdateStatus.WaitingInLOS) {
            return false;
          }
        }

        synchronized(ServerLOS.this.playersMain) {
          return ServerLOS.this.playersLOS.size() ==
                 ServerLOS.this.playersMain.size();
        }
      }
    }
  }

  private class PlayerData {
    IsoPlayer player;
  public
    ServerLOS.UpdateStatus status = ServerLOS.UpdateStatus.NeverDone;
    int px;
    int py;
    int pz;
  public
    boolean[][][] visible = new boolean[100][100][8];

  public
    PlayerData(IsoPlayer playerx) { this.player = playerx; }
  }

  public static final class ServerLighting implements IsoGridSquare.ILighting {
    static const uint8_t LOS_SEEN = 1;
    static const uint8_t LOS_COULD_SEE = 2;
    static const uint8_t LOS_CAN_SEE = 4;
    static ColorInfo lightInfo = new ColorInfo();
    uint8_t los;

    int lightverts(int var1) { return 0; }

    float lampostTotalR() { return 0.0F; }

    float lampostTotalG() { return 0.0F; }

    float lampostTotalB() { return 0.0F; }

    bool bSeen() { return (this.los & 1) != 0; }

    bool bCanSee() { return (this.los & 4) != 0; }

    bool bCouldSee() { return (this.los & 2) != 0; }

    float darkMulti() { return 0.0F; }

    float targetDarkMulti() { return 0.0F; }

    ColorInfo lightInfo() {
      lightInfo.r = 1.0F;
      lightInfo.g = 1.0F;
      lightInfo.b = 1.0F;
      return lightInfo;
    }

    void lightverts(int var1, int var2) {}

    void lampostTotalR(float var1) {}

    void lampostTotalG(float var1) {}

    void lampostTotalB(float var1) {}

    void bSeen(bool boolean0) {
      if (boolean0) {
        this.los = (byte)(this.los | 1);
      } else {
        this.los &= -2;
      }
    }

    void bCanSee(bool boolean0) {
      if (boolean0) {
        this.los = (byte)(this.los | 4);
      } else {
        this.los &= -5;
      }
    }

    void bCouldSee(bool boolean0) {
      if (boolean0) {
        this.los = (byte)(this.los | 2);
      } else {
        this.los &= -3;
      }
    }

    void darkMulti(float var1) {}

    void targetDarkMulti(float var1) {}

    int resultLightCount() { return 0; }

  public
    IsoGridSquare.ResultLight getResultLight(int var1) { return null; }

    void reset() { this.los = 0; }
  }

  static enum UpdateStatus {
    NeverDone, WaitingInLOS, BusyInLOS, ReadyInLOS, BusyInMain, ReadyInMain;
  }
}
} // namespace network
} // namespace zombie
