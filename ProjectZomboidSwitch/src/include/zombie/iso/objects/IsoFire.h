#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoHeatSource.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/ui/TutorialManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoFire : public IsoObject {
public:
    int Age = 0;
    int Energy = 0;
    int Life;
    int LifeStage;
    int LifeStageDuration;
    int LifeStageTimer;
    int MaxLife = 3000;
    int MinLife = 800;
    int SpreadDelay;
    int SpreadTimer;
    int numFlameParticles;
    bool perm = false;
    bool bSmoke = false;
    IsoLightSource LightSource = nullptr;
    int LightRadius = 1;
    float LightOscillator = 0.0F;
    IsoHeatSource heatSource;
    float accum = 0.0F;

    public IsoFire(IsoCell var1) {
      super(var1);
   }

    public IsoFire(IsoCell var1, IsoGridSquare var2) {
      super(var1);
      this.square = var2;
      this.perm = true;
   }

    std::string getObjectName() {
      return "Fire";
   }

    void save(ByteBuffer var1, bool var2) {
    std::vector var3 = this.AttachedAnimSprite;
      this.AttachedAnimSprite = nullptr;
      super.save(var1, var2);
      this.AttachedAnimSprite = var3;
      this.sprite = nullptr;
      var1.putInt(this.Life);
      var1.putInt(this.SpreadDelay);
      var1.putInt(this.LifeStage - 1);
      var1.putInt(this.LifeStageTimer);
      var1.putInt(this.LifeStageDuration);
      var1.putInt(this.Energy);
      var1.putInt(this.numFlameParticles);
      var1.putInt(this.SpreadTimer);
      var1.putInt(this.Age);
      var1.put((byte)(this.perm ? 1 : 0));
      var1.put((byte)this.LightRadius);
      var1.put((byte)(this.bSmoke ? 1 : 0));
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.sprite = nullptr;
      this.Life = var1.getInt();
      this.SpreadDelay = var1.getInt();
      this.LifeStage = var1.getInt();
      this.LifeStageTimer = var1.getInt();
      this.LifeStageDuration = var1.getInt();
      this.Energy = var1.getInt();
      this.numFlameParticles = var1.getInt();
      this.SpreadTimer = var1.getInt();
      this.Age = var1.getInt();
      this.perm = var1.get() == 1;
      this.LightRadius = var1.get() & 255;
      if (var2 >= 89) {
         this.bSmoke = var1.get() == 1;
      }

      if (this.perm) {
         this.AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16, -78, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
      } else {
         if (this.numFlameParticles == 0) {
            this.numFlameParticles = 1;
         }

         switch (this.LifeStage) {
            case -1:
               this.LifeStage = 0;

               for (int var4 = 0; var4 < this.numFlameParticles; var4++) {
                  this.AttachAnim(
                     "Fire",
                     "01",
                     4,
                     IsoFireManager.FireAnimDelay,
                     -16 + -16 + Rand.Next(32),
                     -85 + -16 + Rand.Next(32),
                     true,
                     0,
                     false,
                     0.7F,
                     IsoFireManager.FireTintMod
                  );
               }
               break;
            case 0:
               this.LifeStage = 1;
               this.LifeStageTimer = this.LifeStageDuration;
               this.AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -72, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 1:
               this.LifeStage = 2;
               this.LifeStageTimer = this.LifeStageDuration;
               this.AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
               this.AttachAnim("Fire", "03", 4, IsoFireManager.FireAnimDelay, -9, -52, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 2:
               this.LifeStage = 3;
               this.LifeStageTimer = this.LifeStageDuration / 3;
               this.RemoveAttachedAnims();
               this.AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
               this.AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -72, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 3:
               this.LifeStage = 4;
               this.LifeStageTimer = this.LifeStageDuration / 3;
               this.RemoveAttachedAnims();
               if (this.bSmoke) {
                  this.AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
               } else {
                  this.AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
                  this.AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16, -85, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               }
               break;
            case 4:
               this.LifeStage = 5;
               this.LifeStageTimer = this.LifeStageDuration / 3;
               this.RemoveAttachedAnims();
               this.AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
         }

         if (this.square != nullptr) {
            if (this.LifeStage < 4) {
               this.square.getProperties().Set(IsoFlagType.burning);
            } else {
               this.square.getProperties().Set(IsoFlagType.smoke);
            }
         }
      }
   }

    public IsoFire(IsoCell var1, IsoGridSquare var2, bool var3, int var4, int var5, bool var6) {
      this.square = var2;
      this.DirtySlice();
      this.square.getProperties().Set(IsoFlagType.smoke);
      this.AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
      this.Life = this.MinLife + Rand.Next(this.MaxLife - this.MinLife);
      if (var5 > 0) {
         this.Life = var5;
      }

      this.LifeStage = 4;
      this.LifeStageTimer = this.LifeStageDuration = this.Life / 4;
      this.Energy = var4;
      this.bSmoke = var6;
   }

    public IsoFire(IsoCell var1, IsoGridSquare var2, bool var3, int var4, int var5) {
      this.square = var2;
      this.DirtySlice();
      this.numFlameParticles = 2 + Rand.Next(2);

      for (int var6 = 0; var6 < this.numFlameParticles; var6++) {
         this.AttachAnim(
            "Fire",
            "01",
            4,
            IsoFireManager.FireAnimDelay,
            -16 + -16 + Rand.Next(32),
            -85 + -16 + Rand.Next(32),
            true,
            0,
            false,
            0.7F,
            IsoFireManager.FireTintMod
         );
      }

      this.Life = this.MinLife + Rand.Next(this.MaxLife - this.MinLife);
      if (var5 > 0) {
         this.Life = var5;
      }

      if (this.square.getProperties() != nullptr && !this.square.getProperties().Is(IsoFlagType.vegitation) && this.square.getFloor() != nullptr) {
         this.Life = this.Life - this.square.getFloor().getSprite().firerequirement * 100;
         if (this.Life < 600) {
            this.Life = Rand.Next(300, 600);
         }
      }

      this.SpreadDelay = this.SpreadTimer = Rand.Next(this.Life - this.Life / 2);
      this.LifeStage = 0;
      this.LifeStageTimer = this.LifeStageDuration = this.Life / 4;
      if (TutorialManager.instance.Active) {
         this.LifeStageDuration *= 2;
         this.Life *= 2;
      }

      if (TutorialManager.instance.Active) {
         this.SpreadDelay = this.SpreadTimer /= 4;
      }

      var2.getProperties().Set(IsoFlagType.burning);
      this.Energy = var4;
      if (this.square.getProperties().Is(IsoFlagType.vegitation)) {
         this.Energy += 50;
      }

      LuaEventManager.triggerEvent("OnNewFire", this);
   }

    public IsoFire(IsoCell var1, IsoGridSquare var2, bool var3, int var4) {
      this(var1, var2, var3, var4, 0);
   }

    static bool CanAddSmoke(IsoGridSquare var0, bool var1) {
    return CanAddFire();
   }

    static bool CanAddFire(IsoGridSquare var0, bool var1) {
    return CanAddFire();
   }

    static bool CanAddFire(IsoGridSquare var0, bool var1, bool var2) {
      if (!var2 && (GameServer.bServer || GameClient.bClient) && ServerOptions.instance.NoFire.getValue()) {
    return false;
      } else if (var0 == nullptr || var0.getObjects().empty()) {
    return false;
      } else if (var0.Is(IsoFlagType.water)) {
    return false;
      } else if (!var1 && var0.getProperties().Is(IsoFlagType.burntOut)) {
    return false;
      } else if (var0.getProperties().Is(IsoFlagType.burning) || var0.getProperties().Is(IsoFlagType.smoke)) {
    return false;
      } else {
         return !var1 && !Fire_IsSquareFlamable(var0)
            ? false
            : var2
               || !GameServer.bServer && !GameClient.bClient
               || SafeHouse.getSafeHouse(var0) == nullptr
               || ServerOptions.instance.SafehouseAllowFire.getValue();
      }
   }

    static bool Fire_IsSquareFlamable(IsoGridSquare var0) {
      return !var0.getProperties().Is(IsoFlagType.unflamable);
   }

    bool HasTooltip() {
    return false;
   }

    void Spread() {
      if (!GameClient.bClient) {
         if (SandboxOptions.instance.FireSpread.getValue()) {
            if (this.getCell() != nullptr) {
               if (this.square != nullptr) {
                  if (this.LifeStage < 4) {
    IsoGridSquare var1 = nullptr;
    int var2 = Rand.Next(3) + 1;
                     if (Rand.Next(50) == 0) {
                        var2 += 15;
                     }

                     if (TutorialManager.instance.Active) {
                        var2 += 15;
                     }

                     for (int var3 = 0; var3 < var2; var3++) {
    int var4 = Rand.Next(13);
                        switch (var4) {
                           case 0:
                              var1 = this.getCell().getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ());
                              break;
                           case 1:
                              var1 = this.getCell().getGridSquare(this.square.getX() + 1, this.square.getY() - 1, this.square.getZ());
                              break;
                           case 2:
                              var1 = this.getCell().getGridSquare(this.square.getX() + 1, this.square.getY(), this.square.getZ());
                              break;
                           case 3:
                              var1 = this.getCell().getGridSquare(this.square.getX() + 1, this.square.getY() + 1, this.square.getZ());
                              break;
                           case 4:
                              var1 = this.getCell().getGridSquare(this.square.getX(), this.square.getY() + 1, this.square.getZ());
                              break;
                           case 5:
                              var1 = this.getCell().getGridSquare(this.square.getX() - 1, this.square.getY() + 1, this.square.getZ());
                              break;
                           case 6:
                              var1 = this.getCell().getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ());
                              break;
                           case 7:
                              var1 = this.getCell().getGridSquare(this.square.getX() - 1, this.square.getY() - 1, this.square.getZ());
                              break;
                           case 8:
                              var1 = this.getCell().getGridSquare(this.square.getX() - 1, this.square.getY() - 1, this.square.getZ() - 1);
                              break;
                           case 9:
                              var1 = this.getCell().getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ() - 1);
                              break;
                           case 10:
                              var1 = this.getCell().getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ() - 1);
                              break;
                           case 11:
                              var1 = this.getCell().getGridSquare(this.square.getX(), this.square.getY(), this.square.getZ() - 1);
                              break;
                           case 12:
                              var1 = this.getCell().getGridSquare(this.square.getX(), this.square.getY(), this.square.getZ() + 1);
                        }

                        if (CanAddFire(var1, false)) {
    int var5 = this.getSquaresEnergyRequirement(var1);
                           if (this.Energy >= var5) {
                              this.Energy -= var5;
                              if (GameServer.bServer) {
                                 this.sendObjectChange("Energy");
                              }

                              if (RainManager.isRaining()) {
                                 return;
                              }

    int var6 = var1.getProperties().Is(IsoFlagType.exterior) ? this.Energy : var5 * 2;
                              IsoFireManager.StartFire(this.getCell(), var1, false, var6);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2) {
      return this.square == var2;
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      return VisionResult.NoEffect;
   }

    void update() {
      if (this.getObjectIndex() != -1) {
         if (!GameServer.bServer) {
            IsoFireManager.updateSound(this);
         }

         if (this.LifeStage < 4) {
            this.square.getProperties().Set(IsoFlagType.burning);
         } else {
            this.square.getProperties().Set(IsoFlagType.smoke);
         }

         if (!this.bSmoke && this.LifeStage < 5) {
            this.square.BurnTick();
         }

    int var1 = this.AttachedAnimSprite.size();

         for (int var2 = 0; var2 < var1; var2++) {
    IsoSpriteInstance var3 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var2);
    IsoSprite var4 = var3.parentSprite;
            var3.update();
    float var5 = GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F;
            var3.Frame = var3.Frame + var3.AnimFrameIncrease * var5;
            if ((int)var3.Frame >= var4.CurrentAnim.Frames.size() && var4.Loop && var3.Looped) {
               var3.Frame = 0.0F;
            }
         }

         if (!this.bSmoke && !GameServer.bServer && this.LightSource == nullptr) {
            this.LightSource = std::make_shared<IsoLightSource>(
               this.square.getX(), this.square.getY(), this.square.getZ(), 0.61F, 0.165F, 0.0F, this.perm ? this.LightRadius : 5
            );
            IsoWorld.instance.CurrentCell.addLamppost(this.LightSource);
         }

         if (this.perm) {
            if (this.heatSource == nullptr) {
               this.heatSource = std::make_shared<IsoHeatSource>(this.square.x, this.square.y, this.square.z, this.LightRadius, 35);
               IsoWorld.instance.CurrentCell.addHeatSource(this.heatSource);
            } else {
               this.heatSource.setRadius(this.LightRadius);
            }
         } else {
            this.accum = this.accum + GameTime.getInstance().getMultiplier() / 1.6F;

            while (this.accum > 1.0F) {
               this.accum--;
               this.Age++;
               if (this.LifeStageTimer > 0) {
                  this.LifeStageTimer--;
                  if (this.LifeStageTimer <= 0) {
                     switch (this.LifeStage) {
                        case 0:
                           this.LifeStage = 1;
                           this.LifeStageTimer = this.LifeStageDuration;
                           this.AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16, -72, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
                           this.square.Burn();
                           if (this.LightSource != nullptr) {
                              this.setLightRadius(5);
                           }
                           break;
                        case 1:
                           this.LifeStage = 2;
                           this.LifeStageTimer = this.LifeStageDuration;
                           this.RemoveAttachedAnims();
                           this.AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, -9, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
                           this.AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -9, -52, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
                           this.square.Burn();
                           if (this.LightSource != nullptr) {
                              this.setLightRadius(8);
                           }
                           break;
                        case 2:
                           this.LifeStage = 3;
                           this.LifeStageTimer = this.LifeStageDuration / 3;
                           this.RemoveAttachedAnims();
                           this.AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
                           this.AttachAnim("Fire", "03", 4, IsoFireManager.FireAnimDelay, -16, -72, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
                           if (this.LightSource != nullptr) {
                              this.setLightRadius(12);
                           }
                           break;
                        case 3:
                           this.LifeStage = 4;
                           this.LifeStageTimer = this.LifeStageDuration / 3;
                           this.RemoveAttachedAnims();
                           this.AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
                           this.AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -85, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
                           if (this.LightSource != nullptr) {
                              this.setLightRadius(8);
                           }
                           break;
                        case 4:
                           this.LifeStage = 5;
                           this.LifeStageTimer = this.LifeStageDuration / 3;
                           this.RemoveAttachedAnims();
                           this.AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
                           if (this.LightSource != nullptr) {
                              this.setLightRadius(1);
                           }
                     }
                  }
               }

               if (this.Life > 0) {
                  this.Life--;
                  if (this.LifeStage > 0 && this.SpreadTimer > 0) {
                     this.SpreadTimer--;
                     if (this.SpreadTimer <= 0) {
                        if (this.LifeStage != 5) {
                           this.Spread();
                        }

                        this.SpreadTimer = this.SpreadDelay;
                     }
                  }

                  if (this.Energy > 0) {
                     continue;
                  }

                  this.extinctFire();
                  break;
               }

               this.extinctFire();
               break;
            }
         }
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      var1 += 0.5F;
      var2 += 0.5F;
      this.sx = 0.0F;
      this.offsetX = 0.0F;
      this.offsetY = 0.0F;
    float var8 = Core.TileScale;

      for (int var9 = 0; var9 < this.AttachedAnimSprite.size(); var9++) {
    IsoSprite var10 = ((IsoSpriteInstance)this.AttachedAnimSprite.get(var9)).parentSprite;
         if (var10 != nullptr && var10.CurrentAnim != nullptr && var10.def != nullptr) {
    Texture var11 = ((IsoDirectionFrame)var10.CurrentAnim.Frames.get((int)var10.def.Frame)).directions[this.dir.index()];
            if (var11 != nullptr) {
               var10.soffX = (short)(-(var11.getWidthOrig() / 2 * var8));
               var10.soffY = (short)(-(var11.getHeightOrig() * var8));
               ((IsoSpriteInstance)this.AttachedAnimSprite.get(var9)).setScale(var8, var8);
            }
         }
      }

      super.render(var1, var2, var3, var4, var5, var6, var7);
      if (Core.bDebug) {
      }
   }

    void extinctFire() {
      this.square.getProperties().UnSet(IsoFlagType.burning);
      this.square.getProperties().UnSet(IsoFlagType.smoke);
      this.RemoveAttachedAnims();
      this.square.getObjects().remove(this);
      this.square.RemoveTileObject(this);
      this.setLife(0);
      this.removeFromWorld();
   }

    int getSquaresEnergyRequirement(IsoGridSquare var1) {
    int var2 = 30;
      if (var1.getProperties().Is(IsoFlagType.vegitation)) {
         var2 = -15;
      }

      if (!var1.getProperties().Is(IsoFlagType.exterior)) {
         var2 = 40;
      }

      if (var1.getFloor() != nullptr && var1.getFloor().getSprite() != nullptr) {
         var2 = var1.getFloor().getSprite().firerequirement;
      }

      return TutorialManager.instance.Active ? var2 / 4 : var2;
   }

    void setSpreadDelay(int var1) {
      this.SpreadDelay = var1;
   }

    int getSpreadDelay() {
      return this.SpreadDelay;
   }

    void setLife(int var1) {
      this.Life = var1;
   }

    int getLife() {
      return this.Life;
   }

    int getEnergy() {
      return this.Energy;
   }

    bool isPermanent() {
      return this.perm;
   }

    void setLifeStage(int var1) {
      if (this.perm) {
         this.RemoveAttachedAnims();
         switch (var1) {
            case 0:
               this.AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16, -72, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 1:
               this.AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, -9, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
               this.AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -9, -52, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 2:
               this.AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
               this.AttachAnim("Fire", "03", 4, IsoFireManager.FireAnimDelay, -16, -72, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 3:
               this.AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, 0, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
               this.AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -85, true, 0, false, 0.7F, IsoFireManager.FireTintMod);
               break;
            case 4:
               this.AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12, true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
         }
      }
   }

    void setLightRadius(int var1) {
      this.LightRadius = var1;
      if (this.LightSource != nullptr && var1 != this.LightSource.getRadius()) {
         this.getCell().removeLamppost(this.LightSource);
         this.LightSource = std::make_shared<IsoLightSource>(this.square.getX(), this.square.getY(), this.square.getZ(), 0.61F, 0.165F, 0.0F, this.LightRadius);
         this.getCell().getLamppostPositions().push_back(this.LightSource);
         IsoGridSquare.RecalcLightTime = -1;
         GameTime.instance.lightSourceUpdate = 100.0F;
      }
   }

    int getLightRadius() {
      return this.LightRadius;
   }

    void addToWorld() {
      if (this.perm) {
         this.getCell().addToStaticUpdaterObjectList(this);
      } else {
         IsoFireManager.Add(this);
      }
   }

    void removeFromWorld() {
      if (!this.perm) {
         IsoFireManager.Remove(this);
      }

      IsoFireManager.stopSound(this);
      if (this.LightSource != nullptr) {
         this.getCell().removeLamppost(this.LightSource);
         this.LightSource = nullptr;
      }

      if (this.heatSource != nullptr) {
         this.getCell().removeHeatSource(this.heatSource);
         this.heatSource = nullptr;
      }

      super.removeFromWorld();
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      super.saveChange(var1, var2, var3);
      if ("Energy" == var1)) {
         var3.putInt(this.Energy);
      } else if ("lightRadius" == var1)) {
         var3.putInt(this.getLightRadius());
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      super.loadChange(var1, var2);
      if ("Energy" == var1)) {
         this.Energy = var2.getInt();
      }

      if ("lightRadius" == var1)) {
    int var3 = var2.getInt();
         this.setLightRadius(var3);
      }
   }

    bool isCampfire() {
      if (this.getSquare() == nullptr) {
    return false;
      } else {
         IsoObject[] var1 = (IsoObject[])this.getSquare().getObjects().getElements();
    int var2 = 1;

         for (int var3 = this.getSquare().getObjects().size(); var2 < var3; var2++) {
    IsoObject var4 = var1[var2];
            if (!(dynamic_cast<IsoWorldInventoryObject*>(var4) != nullptr) && "Campfire".equalsIgnoreCase(var4.getName())) {
    return true;
            }
         }

    return false;
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
