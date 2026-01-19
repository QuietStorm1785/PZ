#pragma once
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
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/ui/TutorialManager.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

public
 IsoFire(IsoCell cell) { super(cell); }

public
 IsoFire(IsoCell cell, IsoGridSquare gridSquare) {
 super(cell);
 this->square = gridSquare;
 this->perm = true;
 }

 std::string getObjectName() { return "Fire"; }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 std::vector arrayList = this->AttachedAnimSprite;
 this->AttachedAnimSprite = nullptr;
 super.save(output, IS_DEBUG_SAVE);
 this->AttachedAnimSprite = arrayList;
 this->sprite = nullptr;
 output.putInt(this->Life);
 output.putInt(this->SpreadDelay);
 output.putInt(this->LifeStage - 1);
 output.putInt(this->LifeStageTimer);
 output.putInt(this->LifeStageDuration);
 output.putInt(this->Energy);
 output.putInt(this->numFlameParticles);
 output.putInt(this->SpreadTimer);
 output.putInt(this->Age);
 output.put((byte)(this->perm ? 1 : 0);
 output.put((byte)this->LightRadius);
 output.put((byte)(this->bSmoke ? 1 : 0);
 }

 void load(ByteBuffer b, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(b, WorldVersion, IS_DEBUG_SAVE);
 this->sprite = nullptr;
 this->Life = b.getInt();
 this->SpreadDelay = b.getInt();
 this->LifeStage = b.getInt();
 this->LifeStageTimer = b.getInt();
 this->LifeStageDuration = b.getInt();
 this->Energy = b.getInt();
 this->numFlameParticles = b.getInt();
 this->SpreadTimer = b.getInt();
 this->Age = b.getInt();
 this->perm = b.get() == 1;
 this->LightRadius = b.get() & 255;
 if (WorldVersion >= 89) {
 this->bSmoke = b.get() == 1;
 }

 if (this->perm) {
 this->AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16, -78,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 } else {
 if (this->numFlameParticles == 0) {
 this->numFlameParticles = 1;
 }

 switch (this->LifeStage) {
 case -1:
 this->LifeStage = 0;

 for (int int0 = 0; int0 < this->numFlameParticles; int0++) {
 this->AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay,
 -16 + -16 + Rand.Next(32), -85 + -16 + Rand.Next(32),
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 }
 break;
 case 0:
 this->LifeStage = 1;
 this->LifeStageTimer = this->LifeStageDuration;
 this->AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -72,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 1:
 this->LifeStage = 2;
 this->LifeStageTimer = this->LifeStageDuration;
 this->AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "03", 4, IsoFireManager.FireAnimDelay, -9, -52,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 2:
 this->LifeStage = 3;
 this->LifeStageTimer = this->LifeStageDuration / 3;
 this->RemoveAttachedAnims();
 this->AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, 0, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -72,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 3:
 this->LifeStage = 4;
 this->LifeStageTimer = this->LifeStageDuration / 3;
 this->RemoveAttachedAnims();
 if (this->bSmoke) {
 this->AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0,
 12, true, 0, false, 0.7F,
 IsoFireManager.SmokeTintMod);
 } else {
 this->AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0,
 12, true, 0, false, 0.7F,
 IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16,
 -85, true, 0, false, 0.7F,
 IsoFireManager.FireTintMod);
 }
 break;
 case 4:
 this->LifeStage = 5;
 this->LifeStageTimer = this->LifeStageDuration / 3;
 this->RemoveAttachedAnims();
 this->AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 }

 if (this->square != nullptr) {
 if (this->LifeStage < 4) {
 this->square.getProperties().Set(IsoFlagType.burning);
 } else {
 this->square.getProperties().Set(IsoFlagType.smoke);
 }
 }
 }
 }

public
 IsoFire(IsoCell cell, IsoGridSquare gridSquare, bool CanBurnAnywhere,
 int StartingEnergy, int SetLife, bool isSmoke) {
 this->square = gridSquare;
 this->DirtySlice();
 this->square.getProperties().Set(IsoFlagType.smoke);
 this->AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 this->Life = this->MinLife + Rand.Next(this->MaxLife - this->MinLife);
 if (SetLife > 0) {
 this->Life = SetLife;
 }

 this->LifeStage = 4;
 this->LifeStageTimer = this->LifeStageDuration = this->Life / 4;
 this->Energy = StartingEnergy;
 this->bSmoke = isSmoke;
 }

public
 IsoFire(IsoCell cell, IsoGridSquare gridSquare, bool CanBurnAnywhere,
 int StartingEnergy, int SetLife) {
 this->square = gridSquare;
 this->DirtySlice();
 this->numFlameParticles = 2 + Rand.Next(2);

 for (int int0 = 0; int0 < this->numFlameParticles; int0++) {
 this->AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay,
 -16 + -16 + Rand.Next(32), -85 + -16 + Rand.Next(32),
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 }

 this->Life = this->MinLife + Rand.Next(this->MaxLife - this->MinLife);
 if (SetLife > 0) {
 this->Life = SetLife;
 }

 if (this->square.getProperties() != nullptr &&
 !this->square.getProperties().Is(IsoFlagType.vegitation) &&
 this->square.getFloor() != nullptr) {
 this->Life =
 this->Life - this->square.getFloor().getSprite().firerequirement * 100;
 if (this->Life < 600) {
 this->Life = Rand.Next(300, 600);
 }
 }

 this->SpreadDelay = this->SpreadTimer = Rand.Next(this->Life - this->Life / 2);
 this->LifeStage = 0;
 this->LifeStageTimer = this->LifeStageDuration = this->Life / 4;
 if (TutorialManager.instance.Active) {
 this->LifeStageDuration *= 2;
 this->Life *= 2;
 }

 if (TutorialManager.instance.Active) {
 this->SpreadDelay = this->SpreadTimer /= 4;
 }

 gridSquare.getProperties().Set(IsoFlagType.burning);
 this->Energy = StartingEnergy;
 if (this->square.getProperties().Is(IsoFlagType.vegitation) {
 this->Energy += 50;
 }

 LuaEventManager.triggerEvent("OnNewFire", this);
 }

public
 IsoFire(IsoCell cell, IsoGridSquare gridSquare, bool CanBurnAnywhere,
 int StartingEnergy) {
 this(cell, gridSquare, CanBurnAnywhere, StartingEnergy, 0);
 }

 static bool CanAddSmoke(IsoGridSquare gridSquare, bool CanBurnAnywhere) {
 return CanAddFire();
 }

 static bool CanAddFire(IsoGridSquare gridSquare, bool CanBurnAnywhere) {
 return CanAddFire();
 }

 static bool CanAddFire(IsoGridSquare gridSquare, bool CanBurnAnywhere,
 bool smoke) {
 if (!smoke && (GameServer.bServer || GameClient.bClient) &&
 ServerOptions.instance.NoFire.getValue()) {
 return false;
 } else if (gridSquare.empty() || gridSquare.getObjects().empty()) {
 return false;
 } else if (gridSquare.Is(IsoFlagType.water) {
 return false;
 } else if (!CanBurnAnywhere &&
 gridSquare.getProperties().Is(IsoFlagType.burntOut) {
 return false;
 } else if (gridSquare.getProperties().Is(IsoFlagType.burning) ||
 gridSquare.getProperties().Is(IsoFlagType.smoke) {
 return false;
 } else {
 return !CanBurnAnywhere && !Fire_IsSquareFlamable(gridSquare)
 ? false
 : smoke || !GameServer.bServer && !GameClient.bClient ||
 SafeHouse.getSafeHouse(gridSquare) == nullptr ||
 ServerOptions.instance.SafehouseAllowFire.getValue();
 }
 }

 static bool Fire_IsSquareFlamable(IsoGridSquare gridSquare) {
 return !gridSquare.getProperties().Is(IsoFlagType.unflamable);
 }

 bool HasTooltip() { return false; }

 void Spread() {
 if (!GameClient.bClient) {
 if (SandboxOptions.instance.FireSpread.getValue()) {
 if (this->getCell() != nullptr) {
 if (this->square != nullptr) {
 if (this->LifeStage < 4) {
 IsoGridSquare square = nullptr;
 int int0 = Rand.Next(3) + 1;
 if (Rand.Next(50) == 0) {
 int0 += 15;
 }

 if (TutorialManager.instance.Active) {
 int0 += 15;
 }

 for (int int1 = 0; int1 < int0; int1++) {
 int int2 = Rand.Next(13);
 switch (int2) {
 case 0:
 square = this->getCell().getGridSquare(this->square.getX(),
 this->square.getY() - 1,
 this->square.getZ());
 break;
 case 1:
 square = this->getCell().getGridSquare(this->square.getX() + 1,
 this->square.getY() - 1,
 this->square.getZ());
 break;
 case 2:
 square = this->getCell().getGridSquare(this->square.getX() + 1,
 this->square.getY(),
 this->square.getZ());
 break;
 case 3:
 square = this->getCell().getGridSquare(this->square.getX() + 1,
 this->square.getY() + 1,
 this->square.getZ());
 break;
 case 4:
 square = this->getCell().getGridSquare(this->square.getX(),
 this->square.getY() + 1,
 this->square.getZ());
 break;
 case 5:
 square = this->getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY() + 1,
 this->square.getZ());
 break;
 case 6:
 square = this->getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY(),
 this->square.getZ());
 break;
 case 7:
 square = this->getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY() - 1,
 this->square.getZ());
 break;
 case 8:
 square = this->getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY() - 1,
 this->square.getZ() - 1);
 break;
 case 9:
 square = this->getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY(),
 this->square.getZ() - 1);
 break;
 case 10:
 square = this->getCell().getGridSquare(this->square.getX(),
 this->square.getY() - 1,
 this->square.getZ() - 1);
 break;
 case 11:
 square = this->getCell().getGridSquare(this->square.getX(),
 this->square.getY(),
 this->square.getZ() - 1);
 break;
 case 12:
 square = this->getCell().getGridSquare(this->square.getX(),
 this->square.getY(),
 this->square.getZ() + 1);
 }

 if (CanAddFire(square, false) {
 int int3 = this->getSquaresEnergyRequirement(square);
 if (this->Energy >= int3) {
 this->Energy -= int3;
 if (GameServer.bServer) {
 this->sendObjectChange("Energy");
 }

 if (RainManager.isRaining()) {
 return;
 }

 int int4 = square.getProperties().Is(IsoFlagType.exterior)
 ? this->Energy
 : int3 * 2;
 IsoFireManager.StartFire(this->getCell(), square, false,
 int4);
 }
 }
 }
 }
 }
 }
 }
 }
 }

 bool TestCollide(IsoMovingObject obj, IsoGridSquare PassedObjectSquare) {
 return this->square == PassedObjectSquare;
 }

public
 IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 return IsoObject.VisionResult.NoEffect;
 }

 void update() {
 if (this->getObjectIndex() != -1) {
 if (!GameServer.bServer) {
 IsoFireManager.updateSound(this);
 }

 if (this->LifeStage < 4) {
 this->square.getProperties().Set(IsoFlagType.burning);
 } else {
 this->square.getProperties().Set(IsoFlagType.smoke);
 }

 if (!this->bSmoke && this->LifeStage < 5) {
 this->square.BurnTick();
 }

 int int0 = this->AttachedAnimSprite.size();

 for (int int1 = 0; int1 < int0; int1++) {
 IsoSpriteInstance spriteInstance = this->AttachedAnimSprite.get(int1);
 IsoSprite sprite = spriteInstance.parentSprite;
 spriteInstance.update();
 float float0 =
 GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F;
 spriteInstance.Frame =
 spriteInstance.Frame + spriteInstance.AnimFrameIncrease * float0;
 if ((int)spriteInstance.Frame >= sprite.CurrentAnim.Frames.size() &&
 sprite.Loop && spriteInstance.Looped) {
 spriteInstance.Frame = 0.0F;
 }
 }

 if (!this->bSmoke && !GameServer.bServer && this->LightSource.empty()) {
 this->LightSource = new IsoLightSource(
 this->square.getX(), this->square.getY(), this->square.getZ(), 0.61F,
 0.165F, 0.0F, this->perm ? this->LightRadius : 5);
 IsoWorld.instance.CurrentCell.addLamppost(this->LightSource);
 }

 if (this->perm) {
 if (this->heatSource.empty()) {
 this->heatSource =
 new IsoHeatSource(this->square.x, this->square.y, this->square.z,
 this->LightRadius, 35);
 IsoWorld.instance.CurrentCell.addHeatSource(this->heatSource);
 } else {
 this->heatSource.setRadius(this->LightRadius);
 }
 } else {
 this->accum = this->accum + GameTime.getInstance().getMultiplier() / 1.6F;

 while (this->accum > 1.0F) {
 this->accum--;
 this->Age++;
 if (this->LifeStageTimer > 0) {
 this->LifeStageTimer--;
 if (this->LifeStageTimer <= 0) {
 switch (this->LifeStage) {
 case 0:
 this->LifeStage = 1;
 this->LifeStageTimer = this->LifeStageDuration;
 this->AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay,
 -16, -72, true, 0, false, 0.7F,
 IsoFireManager.FireTintMod);
 this->square.Burn();
 if (this->LightSource != nullptr) {
 this->setLightRadius(5);
 }
 break;
 case 1:
 this->LifeStage = 2;
 this->LifeStageTimer = this->LifeStageDuration;
 this->RemoveAttachedAnims();
 this->AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay,
 -9, 12, true, 0, false, 0.7F,
 IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay,
 -9, -52, true, 0, false, 0.7F,
 IsoFireManager.FireTintMod);
 this->square.Burn();
 if (this->LightSource != nullptr) {
 this->setLightRadius(8);
 }
 break;
 case 2:
 this->LifeStage = 3;
 this->LifeStageTimer = this->LifeStageDuration / 3;
 this->RemoveAttachedAnims();
 this->AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay,
 0, 12, true, 0, false, 0.7F,
 IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "03", 4, IsoFireManager.FireAnimDelay,
 -16, -72, true, 0, false, 0.7F,
 IsoFireManager.FireTintMod);
 if (this->LightSource != nullptr) {
 this->setLightRadius(12);
 }
 break;
 case 3:
 this->LifeStage = 4;
 this->LifeStageTimer = this->LifeStageDuration / 3;
 this->RemoveAttachedAnims();
 this->AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay,
 0, 12, true, 0, false, 0.7F,
 IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay,
 -16, -85, true, 0, false, 0.7F,
 IsoFireManager.FireTintMod);
 if (this->LightSource != nullptr) {
 this->setLightRadius(8);
 }
 break;
 case 4:
 this->LifeStage = 5;
 this->LifeStageTimer = this->LifeStageDuration / 3;
 this->RemoveAttachedAnims();
 this->AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay,
 -9, 12, true, 0, false, 0.7F,
 IsoFireManager.SmokeTintMod);
 if (this->LightSource != nullptr) {
 this->setLightRadius(1);
 }
 }
 }
 }

 if (this->Life > 0) {
 this->Life--;
 if (this->LifeStage > 0 && this->SpreadTimer > 0) {
 this->SpreadTimer--;
 if (this->SpreadTimer <= 0) {
 if (this->LifeStage != 5) {
 this->Spread();
 }

 this->SpreadTimer = this->SpreadDelay;
 }
 }

 if (this->Energy > 0) {
 continue;
 }

 this->extinctFire();
 break;
 }

 this->extinctFire();
 break;
 }
 }
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild,
 bool bWallLightingPass, Shader shader) {
 x += 0.5F;
 y += 0.5F;
 this->sx = 0.0F;
 this->offsetX = 0.0F;
 this->offsetY = 0.0F;
 float float0 = Core.TileScale;

 for (int int0 = 0; int0 < this->AttachedAnimSprite.size(); int0++) {
 IsoSprite sprite = this->AttachedAnimSprite.get(int0).parentSprite;
 if (sprite != nullptr && sprite.CurrentAnim != nullptr &&
 sprite.def != nullptr) {
 Texture texture = sprite.CurrentAnim.Frames.get((int)sprite.def.Frame)
 .directions[this->dir.index()];
 if (texture != nullptr) {
 sprite.soffX = (short)(-(texture.getWidthOrig() / 2 * float0);
 sprite.soffY = (short)(-(texture.getHeightOrig() * float0);
 this->AttachedAnimSprite.get(int0).setScale(float0, float0);
 }
 }
 }

 super.render(x, y, z, col, bDoChild, bWallLightingPass, shader);
 if (Core.bDebug) {
 }
 }

 void extinctFire() {
 this->square.getProperties().UnSet(IsoFlagType.burning);
 this->square.getProperties().UnSet(IsoFlagType.smoke);
 this->RemoveAttachedAnims();
 this->square.getObjects().remove(this);
 this->square.RemoveTileObject(this);
 this->setLife(0);
 this->removeFromWorld();
 }

 int getSquaresEnergyRequirement(IsoGridSquare square) {
 int int0 = 30;
 if (square.getProperties().Is(IsoFlagType.vegitation) {
 int0 = -15;
 }

 if (!square.getProperties().Is(IsoFlagType.exterior) {
 int0 = 40;
 }

 if (square.getFloor() != nullptr &&
 square.getFloor().getSprite() != nullptr) {
 int0 = square.getFloor().getSprite().firerequirement;
 }

 return TutorialManager.instance.Active ? int0 / 4 : int0;
 }

 /**
 * The more this number is low, the faster it's gonna spread
 */
 void setSpreadDelay(int _SpreadDelay) { this->SpreadDelay = _SpreadDelay; }

 /**
 * The more this number is low, the faster it's gonna spread
 */
 int getSpreadDelay() { return this->SpreadDelay; }

 /**
 * Up this number to make the fire life longer
 */
 void setLife(int _Life) { this->Life = _Life; }

 int getLife() { return this->Life; }

 int getEnergy() { return this->Energy; }

 bool isPermanent() { return this->perm; }

 void setLifeStage(int lifeStage) {
 if (this->perm) {
 this->RemoveAttachedAnims();
 switch (lifeStage) {
 case 0:
 this->AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay, -16, -72,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 1:
 this->AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, -9, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -9, -52,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 2:
 this->AttachAnim("Smoke", "03", 4, IsoFireManager.SmokeAnimDelay, 0, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "03", 4, IsoFireManager.FireAnimDelay, -16, -72,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 3:
 this->AttachAnim("Smoke", "02", 4, IsoFireManager.SmokeAnimDelay, 0, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 this->AttachAnim("Fire", "02", 4, IsoFireManager.FireAnimDelay, -16, -85,
 true, 0, false, 0.7F, IsoFireManager.FireTintMod);
 break;
 case 4:
 this->AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -9, 12,
 true, 0, false, 0.7F, IsoFireManager.SmokeTintMod);
 }
 }
 }

 void setLightRadius(int radius) {
 this->LightRadius = radius;
 if (this->LightSource != nullptr && radius != this->LightSource.getRadius()) {
 this->getCell().removeLamppost(this->LightSource);
 this->LightSource = new IsoLightSource(
 this->square.getX(), this->square.getY(), this->square.getZ(), 0.61F,
 0.165F, 0.0F, this->LightRadius);
 this->getCell().getLamppostPositions().add(this->LightSource);
 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 }
 }

 int getLightRadius() { return this->LightRadius; }

 void addToWorld() {
 if (this->perm) {
 this->getCell().addToStaticUpdaterObjectList(this);
 } else {
 IsoFireManager.Add(this);
 }
 }

 void removeFromWorld() {
 if (!this->perm) {
 IsoFireManager.Remove(this);
 }

 IsoFireManager.stopSound(this);
 if (this->LightSource != nullptr) {
 this->getCell().removeLamppost(this->LightSource);
 this->LightSource = nullptr;
 }

 if (this->heatSource != nullptr) {
 this->getCell().removeHeatSource(this->heatSource);
 this->heatSource = nullptr;
 }

 super.removeFromWorld();
 }

 void saveChange(std::string_view change, KahluaTable tbl, ByteBuffer bb) {
 super.saveChange(change, tbl, bb);
 if ("Energy" == change) {
 bb.putInt(this->Energy);
 }
 else if ("lightRadius" == change) {
 bb.putInt(this->getLightRadius());
 }
 }

 void loadChange(std::string_view change, ByteBuffer bb) {
 super.loadChange(change, bb);
 if ("Energy" == change) {
 this->Energy = bb.getInt();
 }

 if ("lightRadius" == change) {
 int int0 = bb.getInt();
 this->setLightRadius(int0);
 }
 }

 bool isCampfire() {
 if (this->getSquare() == nullptr) {
 return false;
 } else {
 IsoObject[] objects = this->getSquare().getObjects().getElements();
 int int0 = 1;

 for (int int1 = this->getSquare().getObjects().size(); int0 < int1;
 int0++) {
 IsoObject object = objects[int0];
 if (!(object instanceof IsoWorldInventoryObject) &&
 "Campfire".equalsIgnoreCase(object.getName())) {
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
