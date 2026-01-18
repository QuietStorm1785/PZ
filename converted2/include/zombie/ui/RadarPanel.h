#pragma once
#include "zombie/IndieGL.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RadarPanel : public UIElement {
public:
  int playerIndex;
  float xPos;
  float yPos;
  float offx;
  float offy;
  float zoom;
  float draww;
  float drawh;
  Texture mask;
  Texture border;
private
  ArrayList<RadarPanel.ZombiePos> zombiePos = std::make_unique<ArrayList<>>();
private
  RadarPanel.ZombiePosPool zombiePosPool = new RadarPanel.ZombiePosPool();
  int zombiePosFrameCount;
private
  boolean[] zombiePosOccupied = new boolean[360];

public
  RadarPanel(int _playerIndex) {
    this.setX(IsoCamera.getScreenLeft(_playerIndex) + 20);
    this.setY(IsoCamera.getScreenTop(_playerIndex) +
              IsoCamera.getScreenHeight(_playerIndex) - 120 - 20);
    this.setWidth(120.0);
    this.setHeight(120.0);
    this.mask = Texture.getSharedTexture("media/ui/RadarMask.png");
    this.border = Texture.getSharedTexture("media/ui/RadarBorder.png");
    this.playerIndex = _playerIndex;
  }

  void update() {
    uint8_t byte0 = 0;
    if (IsoPlayer.players[this.playerIndex] != nullptr &&
        IsoPlayer.players[this.playerIndex].getJoypadBind() != -1) {
      byte0 = -72;
    }

    this.setX(IsoCamera.getScreenLeft(this.playerIndex) + 20);
    this.setY(IsoCamera.getScreenTop(this.playerIndex) +
              IsoCamera.getScreenHeight(this.playerIndex) - this.getHeight() -
              20.0 + byte0);
  }

  void render() {
    if (this.isVisible()) {
      if (IsoPlayer.players[this.playerIndex] != nullptr) {
        if (!GameClient.bClient) {
          this.draww = this.getWidth().intValue();
          this.drawh = this.getHeight().intValue();
          this.xPos = IsoPlayer.players[this.playerIndex].getX();
          this.yPos = IsoPlayer.players[this.playerIndex].getY();
          this.offx = this.getAbsoluteX().intValue();
          this.offy = this.getAbsoluteY().intValue();
          this.zoom = 3.0F;
          this.stencilOn();
          SpriteRenderer.instance.render(nullptr, this.offx, this.offy,
                                         this.getWidth().intValue(), this.drawh,
                                         0.0F, 0.2F, 0.0F, 0.66F, nullptr);
          this.renderBuildings();
          this.renderRect(this.xPos - 0.5F, this.yPos - 0.5F, 1.0F, 1.0F, 1.0F,
                          1.0F, 1.0F, 1.0F);
          this.stencilOff();
          this.renderZombies();
          SpriteRenderer.instance.render(this.border, this.offx - 4.0F,
                                         this.offy - 4.0F, this.draww + 8.0F,
                                         this.drawh + 8.0F, 1.0F, 1.0F, 1.0F,
                                         0.25F, nullptr);
        }
      }
    }
  }

  void stencilOn() {
    IndieGL.glStencilMask(255);
    IndieGL.glClear(1280);
    IndieGL.enableStencilTest();
    IndieGL.glStencilFunc(519, 128, 255);
    IndieGL.glStencilOp(7680, 7680, 7681);
    IndieGL.enableAlphaTest();
    IndieGL.glAlphaFunc(516, 0.1F);
    IndieGL.glColorMask(false, false, false, false);
    SpriteRenderer.instance.renderi(this.mask, (int)this.x, (int)this.y,
                                    (int)this.width, (int)this.height, 1.0F,
                                    1.0F, 1.0F, 1.0F, nullptr);
    IndieGL.glColorMask(true, true, true, true);
    IndieGL.glAlphaFunc(516, 0.0F);
    IndieGL.glStencilFunc(514, 128, 128);
    IndieGL.glStencilOp(7680, 7680, 7680);
  }

  void stencilOff() {
    IndieGL.glAlphaFunc(519, 0.0F);
    IndieGL.disableStencilTest();
    IndieGL.disableAlphaTest();
    IndieGL.glStencilFunc(519, 255, 255);
    IndieGL.glStencilOp(7680, 7680, 7680);
    IndieGL.glClear(1280);
  }

  void renderBuildings() {
    IsoMetaGrid metaGrid = IsoWorld.instance.MetaGrid;
    IsoMetaCell[][] metaCells = metaGrid.Grid;
    int int0 = (int)((this.xPos - 100.0F) / 300.0F) - metaGrid.minX;
    int int1 = (int)((this.yPos - 100.0F) / 300.0F) - metaGrid.minY;
    int int2 = (int)((this.xPos + 100.0F) / 300.0F) - metaGrid.minX;
    int int3 = (int)((this.yPos + 100.0F) / 300.0F) - metaGrid.minY;
    int0 = Math.max(int0, 0);
    int1 = Math.max(int1, 0);
    int2 = Math.min(int2, metaCells.length - 1);
    int3 = Math.min(int3, metaCells[0].length - 1);

    for (int int4 = int0; int4 <= int2; int4++) {
      for (int int5 = int1; int5 <= int3; int5++) {
        LotHeader lotHeader = metaCells[int4][int5].info;
        if (lotHeader != nullptr) {
          for (int int6 = 0; int6 < lotHeader.Buildings.size(); int6++) {
            BuildingDef buildingDef = lotHeader.Buildings.get(int6);

            for (int int7 = 0; int7 < buildingDef.rooms.size(); int7++) {
              if (buildingDef.rooms.get(int7).level <= 0) {
                std::vector arrayList = buildingDef.rooms.get(int7).getRects();

                for (int int8 = 0; int8 < arrayList.size(); int8++) {
                  RoomDef.RoomRect roomRect =
                      (RoomDef.RoomRect)arrayList.get(int8);
                  this.renderRect(roomRect.getX(), roomRect.getY(),
                                  roomRect.getW(), roomRect.getH(), 0.5F, 0.5F,
                                  0.8F, 0.3F);
                }
              }
            }
          }
        }
      }
    }
  }

  void renderZombies() {
    float float0 = this.offx + this.draww / 2.0F;
    float float1 = this.offy + this.drawh / 2.0F;
    float float2 = this.draww / 2.0F;
    float float3 = 0.5F * this.zoom;
    if (++this.zombiePosFrameCount >= PerformanceSettings.getLockFPS() / 5) {
      this.zombiePosFrameCount = 0;
      this.zombiePosPool.release(this.zombiePos);
      this.zombiePos.clear();
      Arrays.fill(this.zombiePosOccupied, false);
      std::vector arrayList = IsoWorld.instance.CurrentCell.getZombieList();

      for (int int0 = 0; int0 < arrayList.size(); int0++) {
        IsoZombie zombie0 = (IsoZombie)arrayList.get(int0);
        float float4 = this.worldToScreenX(zombie0.getX());
        float float5 = this.worldToScreenY(zombie0.getY());
        float float6 =
            IsoUtils.DistanceToSquared(float0, float1, float4, float5);
        if (float6 > float2 * float2) {
          double double0 =
              Math.atan2(float5 - float1, float4 - float0) + Math.PI;
          double double1 = (Math.toDegrees(double0) + 180.0) % 360.0;
          this.zombiePosOccupied[(int)double1] = true;
        } else {
          this.zombiePos.add(this.zombiePosPool.alloc(zombie0.x, zombie0.y));
        }
      }

      if (Core.bLastStand) {
        if (ZombiePopulationManager.instance.radarXY == nullptr) {
          ZombiePopulationManager.instance.radarXY = new float[2048];
        }

        float[] floats = ZombiePopulationManager.instance.radarXY;
        synchronized(floats) {
          for (int int1 = 0; int1 < ZombiePopulationManager.instance.radarCount;
               int1++) {
            float float7 = floats[int1 * 2 + 0];
            float float8 = floats[int1 * 2 + 1];
            float float9 = this.worldToScreenX(float7);
            float float10 = this.worldToScreenY(float8);
            float float11 =
                IsoUtils.DistanceToSquared(float0, float1, float9, float10);
            if (float11 > float2 * float2) {
              double double2 =
                  Math.atan2(float10 - float1, float9 - float0) + Math.PI;
              double double3 = (Math.toDegrees(double2) + 180.0) % 360.0;
              this.zombiePosOccupied[(int)double3] = true;
            } else {
              this.zombiePos.add(this.zombiePosPool.alloc(float7, float8));
            }
          }

          ZombiePopulationManager.instance.radarRenderFlag = true;
        }
      }
    }

    int int2 = this.zombiePos.size();

    for (int int3 = 0; int3 < int2; int3++) {
      RadarPanel.ZombiePos zombiePosx = this.zombiePos.get(int3);
      this.renderRect(zombiePosx.x - 0.5F, zombiePosx.y - 0.5F, 1.0F, 1.0F,
                      1.0F, 0.0F, 0.0F, 1.0F);
    }

    for (int int4 = 0; int4 < this.zombiePosOccupied.length; int4++) {
      if (this.zombiePosOccupied[int4]) {
        double double4 = Math.toRadians((float)int4 /
                                        this.zombiePosOccupied.length * 360.0F);
        SpriteRenderer.instance.render(
            nullptr,
            float0 + (float2 + 1.0F) * (float)Math.cos(double4) - float3,
            float1 + (float2 + 1.0F) * (float)Math.sin(double4) - float3,
            1.0F * this.zoom, 1.0F * this.zoom, 1.0F, 1.0F, 0.0F, 1.0F,
            nullptr);
      }
    }
  }

  float worldToScreenX(float float0) {
    float0 -= this.xPos;
    float0 *= this.zoom;
    float0 += this.offx;
    return float0 + this.draww / 2.0F;
  }

  float worldToScreenY(float float0) {
    float0 -= this.yPos;
    float0 *= this.zoom;
    float0 += this.offy;
    return float0 + this.drawh / 2.0F;
  }

  void renderRect(float float1, float float3, float float5, float float7,
                  float float8, float float9, float float10, float float11) {
    float float0 = this.worldToScreenX(float1);
    float float2 = this.worldToScreenY(float3);
    float float4 = this.worldToScreenX(float1 + float5);
    float float6 = this.worldToScreenY(float3 + float7);
    float5 = float4 - float0;
    float7 = float6 - float2;
    if (!(float0 >= this.offx + this.draww) && !(float4 < this.offx) &&
        !(float2 >= this.offy + this.drawh) && !(float6 < this.offy)) {
      SpriteRenderer.instance.render(nullptr, float0, float2, float5, float7,
                                     float8, float9, float10, float11, nullptr);
    }
  }

private
  static final class ZombiePos {
    float x;
    float y;

  public
    ZombiePos(float arg0, float arg1) {
      this.x = arg0;
      this.y = arg1;
    }

  public
    RadarPanel.ZombiePos set(float arg0, float arg1) {
      this.x = arg0;
      this.y = arg1;
      return this;
    }
  }

  private static class ZombiePosPool {
  private
    ArrayDeque<RadarPanel.ZombiePos> pool = std::make_unique<ArrayDeque<>>();

  public
    RadarPanel.ZombiePos alloc(float arg0, float arg1) {
      return this.pool.isEmpty() ? new RadarPanel.ZombiePos(arg0, arg1)
                                 : this.pool.pop().set(arg0, arg1);
    }

    void release(Collection<RadarPanel.ZombiePos> collection) {
      this.pool.addAll(collection);
    }
  }
}
} // namespace ui
} // namespace zombie
