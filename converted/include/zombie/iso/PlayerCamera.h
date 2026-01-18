#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerCamera {
public:
 const int playerIndex;
 float OffX;
 float OffY;
 float TOffX;
 float TOffY;
 float lastOffX;
 float lastOffY;
 float RightClickTargetX;
 float RightClickTargetY;
 float RightClickX;
 float RightClickY;
 float RightClickX_f;
 float RightClickY_f;
 float DeferedX;
 float DeferedY;
 float zoom;
 int OffscreenWidth;
 int OffscreenHeight;
 static const Vector2 offVec = new Vector2();
 static float PAN_SPEED = 1.0F;
 long panTime = -1L;
 const Vector3f m_lastVehicleForwardDirection = new Vector3f();

 public PlayerCamera(int _playerIndex) {
 this->playerIndex = _playerIndex;
 }

 void center() {
 float float0 = this->OffX;
 float float1 = this->OffY;
 if (IsoCamera.CamCharacter != nullptr) {
 IsoGameCharacter character = IsoCamera.CamCharacter;
 float0 = IsoUtils.XToScreen(character.x + this->DeferedX, character.y + this->DeferedY, character.z, 0);
 float1 = IsoUtils.YToScreen(character.x + this->DeferedX, character.y + this->DeferedY, character.z, 0);
 float0 -= IsoCamera.getOffscreenWidth(this->playerIndex) / 2;
 float1 -= IsoCamera.getOffscreenHeight(this->playerIndex) / 2;
 float1 -= character.getOffsetY() * 1.5F;
 float0 += IsoCamera.PLAYER_OFFSET_X;
 float1 += IsoCamera.PLAYER_OFFSET_Y;
 }

 this->OffX = this->TOffX = float0;
 this->OffY = this->TOffY = float1;
 }

 void update() {
 this->center();
 float float0 = (this->TOffX - this->OffX) / 15.0F;
 float float1 = (this->TOffY - this->OffY) / 15.0F;
 this->OffX += float0;
 this->OffY += float1;
 if (this->lastOffX == 0.0F && this->lastOffY == 0.0F) {
 this->lastOffX = this->OffX;
 this->lastOffY = this->OffY;
 }

 long long0 = System.currentTimeMillis();
 PAN_SPEED = 110.0F;
 float float2 = this->panTime < 0L ? 1.0F : (float)(long0 - this->panTime) / 1000.0F * PAN_SPEED;
 float2 = 1.0F / float2;
 this->panTime = long0;
 IsoPlayer player = IsoPlayer.players[this->playerIndex];
 bool boolean0 = GameWindow.ActivatedJoyPad != nullptr && player != nullptr && player.JoypadBind != -1;
 BaseVehicle vehicle = player.empty() ? nullptr : player.getVehicle();
 if (vehicle != nullptr && vehicle.getCurrentSpeedKmHour() <= 1.0F) {
 vehicle.getForwardVector(this->m_lastVehicleForwardDirection);
 }

 if (Core.getInstance().getOptionPanCameraWhileDriving() && vehicle != nullptr && vehicle.getCurrentSpeedKmHour() > 1.0F) {
 float float3 = Core.getInstance().getZoom(this->playerIndex);
 float float4 = vehicle.getCurrentSpeedKmHour() * BaseVehicle.getFakeSpeedModifier() / 10.0F;
 float4 *= float3;
 Vector3f vector3f = vehicle.getForwardVector(BaseVehicle.TL_vector3f_pool.get().alloc());
 float float5 = this->m_lastVehicleForwardDirection.angle(vector3f) * (180.0F / (float)Math.PI);
 if (float5 > 1.0F) {
 float float6 = float5 / 180.0F / PerformanceSettings.getLockFPS();
 float6 = PZMath.max(float6, 0.1F);
 this->m_lastVehicleForwardDirection.lerp(vector3f, float6, vector3f);
 this->m_lastVehicleForwardDirection.set(vector3f);
 }

 this->RightClickTargetX = (int)IsoUtils.XToScreen(vector3f.x * float4, vector3f.z * float4, player.z, 0);
 this->RightClickTargetY = (int)IsoUtils.YToScreen(vector3f.x * float4, vector3f.z * float4, player.z, 0);
 BaseVehicle.TL_vector3f_pool.get().release(vector3f);
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 int int0 = IsoCamera.getOffscreenWidth(this->playerIndex);
 int int1 = IsoCamera.getOffscreenHeight(this->playerIndex);
 float float7 = byte0 + int0 / 2.0F;
 float float8 = byte1 + int1 / 2.0F;
 float float9 = 150.0F * float3;
 this->RightClickTargetX = (int)PZMath.clamp(float7 + this->RightClickTargetX, float9, int0 - float9) - float7;
 this->RightClickTargetY = (int)PZMath.clamp(float8 + this->RightClickTargetY, float9, int1 - float9) - float8;
 if (Math.abs(float4) < 5.0F) {
 float float10 = 1.0F - Math.abs(float4) / 5.0F;
 this->returnToCenter(1.0F / (16.0F * float2 / float10);
 } else {
 float2 /= 0.5F * float3;
 float float11 = IsoUtils.XToScreenExact(player.x, player.y, player.z, 0);
 float float12 = IsoUtils.YToScreenExact(player.x, player.y, player.z, 0);
 if (float11 < float9 / 2.0F || float11 > int0 - float9 / 2.0F || float12 < float9 / 2.0F || float12 > int1 - float9 / 2.0F) {
 float2 /= 4.0F;
 }

 this->RightClickX_f = PZMath.step(
 this->RightClickX_f, this->RightClickTargetX, 1.875F * PZMath.sign(this->RightClickTargetX - this->RightClickX_f) / float2
 );
 this->RightClickY_f = PZMath.step(
 this->RightClickY_f, this->RightClickTargetY, 1.875F * PZMath.sign(this->RightClickTargetY - this->RightClickY_f) / float2
 );
 this->RightClickX = (int)this->RightClickX_f;
 this->RightClickY = (int)this->RightClickY_f;
 }
 } else if (boolean0 && player != nullptr) {
 if ((player.IsAiming() || player.isLookingWhileInVehicle())
 && JoypadManager.instance.isRBPressed(player.JoypadBind)
 && !player.bJoypadIgnoreAimUntilCentered) {
 this->RightClickTargetX = JoypadManager.instance.getAimingAxisX(player.JoypadBind) * 1500.0F;
 this->RightClickTargetY = JoypadManager.instance.getAimingAxisY(player.JoypadBind) * 1500.0F;
 float2 /= 0.5F * Core.getInstance().getZoom(this->playerIndex);
 this->RightClickX_f = PZMath.step(this->RightClickX_f, this->RightClickTargetX, (this->RightClickTargetX - this->RightClickX_f) / (80.0F * float2);
 this->RightClickY_f = PZMath.step(this->RightClickY_f, this->RightClickTargetY, (this->RightClickTargetY - this->RightClickY_f) / (80.0F * float2);
 this->RightClickX = (int)this->RightClickX_f;
 this->RightClickY = (int)this->RightClickY_f;
 player.dirtyRecalcGridStackTime = 2.0F;
 } else {
 this->returnToCenter(1.0F / (16.0F * float2);
 }
 } else if (this->playerIndex == 0 && player != nullptr && !player.isBlockMovement() && GameKeyboard.isKeyDown(Core.getInstance().getKey("PanCamera"))) {
 int int2 = IsoCamera.getScreenWidth(this->playerIndex);
 int int3 = IsoCamera.getScreenHeight(this->playerIndex);
 int int4 = IsoCamera.getScreenLeft(this->playerIndex);
 int int5 = IsoCamera.getScreenTop(this->playerIndex);
 float float13 = Mouse.getXA() - (int4 + int2 / 2.0F);
 float float14 = Mouse.getYA() - (int5 + int3 / 2.0F);
 float float15;
 if (int2 > int3) {
 float15 = (float)int3 / int2;
 float13 *= float15;
 } else {
 float15 = (float)int2 / int3;
 float14 *= float15;
 }

 float15 *= int2 / 1366.0F;
 offVec.set(float13, float14);
 offVec.setLength(Math.min(offVec.getLength(), Math.min(int2, int3) / 2.0F);
 float13 = offVec.x / float15;
 float14 = offVec.y / float15;
 this->RightClickTargetX = float13 * 2.0F;
 this->RightClickTargetY = float14 * 2.0F;
 float2 /= 0.5F * Core.getInstance().getZoom(this->playerIndex);
 this->RightClickX_f = PZMath.step(this->RightClickX_f, this->RightClickTargetX, (this->RightClickTargetX - this->RightClickX_f) / (80.0F * float2);
 this->RightClickY_f = PZMath.step(this->RightClickY_f, this->RightClickTargetY, (this->RightClickTargetY - this->RightClickY_f) / (80.0F * float2);
 this->RightClickX = (int)this->RightClickX_f;
 this->RightClickY = (int)this->RightClickY_f;
 player.dirtyRecalcGridStackTime = 2.0F;
 IsoSprite.globalOffsetX = -1.0F;
 } else if (this->playerIndex == 0 && Core.getInstance().getOptionPanCameraWhileAiming()) {
 bool boolean1 = !GameServer.bServer;
 bool boolean2 = !UIManager.isMouseOverInventory() && player != nullptr && player.isAiming();
 bool boolean3 = !boolean0 && player != nullptr && !player.isDead();
 if (boolean1 && boolean2 && boolean3) {
 int int6 = IsoCamera.getScreenWidth(this->playerIndex);
 int int7 = IsoCamera.getScreenHeight(this->playerIndex);
 int int8 = IsoCamera.getScreenLeft(this->playerIndex);
 int int9 = IsoCamera.getScreenTop(this->playerIndex);
 float float16 = Mouse.getXA() - (int8 + int6 / 2.0F);
 float float17 = Mouse.getYA() - (int9 + int7 / 2.0F);
 float float18;
 if (int6 > int7) {
 float18 = (float)int7 / int6;
 float16 *= float18;
 } else {
 float18 = (float)int6 / int7;
 float17 *= float18;
 }

 float18 *= int6 / 1366.0F;
 float float19 = Math.min(int6, int7) / 6.0F;
 float float20 = Math.min(int6, int7) / 2.0F - float19;
 offVec.set(float16, float17);
 if (offVec.getLength() < float20) {
 float17 = 0.0F;
 float16 = 0.0F;
 } else {
 offVec.setLength(Math.min(offVec.getLength(), Math.min(int6, int7) / 2.0F) - float20);
 float16 = offVec.x / float18;
 float17 = offVec.y / float18;
 }

 this->RightClickTargetX = float16 * 7.0F;
 this->RightClickTargetY = float17 * 7.0F;
 float2 /= 0.5F * Core.getInstance().getZoom(this->playerIndex);
 this->RightClickX_f = PZMath.step(this->RightClickX_f, this->RightClickTargetX, (this->RightClickTargetX - this->RightClickX_f) / (80.0F * float2);
 this->RightClickY_f = PZMath.step(this->RightClickY_f, this->RightClickTargetY, (this->RightClickTargetY - this->RightClickY_f) / (80.0F * float2);
 this->RightClickX = (int)this->RightClickX_f;
 this->RightClickY = (int)this->RightClickY_f;
 player.dirtyRecalcGridStackTime = 2.0F;
 } else {
 this->returnToCenter(1.0F / (16.0F * float2);
 }

 IsoSprite.globalOffsetX = -1.0F;
 } else {
 this->returnToCenter(1.0F / (16.0F * float2);
 }

 this->zoom = Core.getInstance().getZoom(this->playerIndex);
 }

 void returnToCenter(float float0) {
 this->RightClickTargetX = 0.0F;
 this->RightClickTargetY = 0.0F;
 if (this->RightClickTargetX != this->RightClickX || this->RightClickTargetY != this->RightClickY) {
 this->RightClickX_f = PZMath.step(this->RightClickX_f, this->RightClickTargetX, (this->RightClickTargetX - this->RightClickX_f) * float0);
 this->RightClickY_f = PZMath.step(this->RightClickY_f, this->RightClickTargetY, (this->RightClickTargetY - this->RightClickY_f) * float0);
 this->RightClickX = (int)this->RightClickX_f;
 this->RightClickY = (int)this->RightClickY_f;
 if (Math.abs(this->RightClickTargetX - this->RightClickX_f) < 0.001F) {
 this->RightClickX = (int)this->RightClickTargetX;
 this->RightClickX_f = this->RightClickX;
 }

 if (Math.abs(this->RightClickTargetY - this->RightClickY_f) < 0.001F) {
 this->RightClickY = (int)this->RightClickTargetY;
 this->RightClickY_f = this->RightClickY;
 }

 IsoPlayer player = IsoPlayer.players[this->playerIndex];
 player.dirtyRecalcGridStackTime = 2.0F;
 }
 }

 float getOffX() {
 return (int)(this->OffX + this->RightClickX);
 }

 float getOffY() {
 return (int)(this->OffY + this->RightClickY);
 }

 float getTOffX() {
 float float0 = this->TOffX - this->OffX;
 return (int)(this->OffX + this->RightClickX - float0);
 }

 float getTOffY() {
 float float0 = this->TOffY - this->OffY;
 return (int)(this->OffY + this->RightClickY - float0);
 }

 float getLastOffX() {
 return (int)(this->lastOffX + this->RightClickX);
 }

 float getLastOffY() {
 return (int)(this->lastOffY + this->RightClickY);
 }

 float XToIso(float screenX, float screenY, float floor) {
 screenX = (int)screenX;
 screenY = (int)screenY;
 float float0 = screenX + this->getOffX();
 float float1 = screenY + this->getOffY();
 float float2 = (float0 + 2.0F * float1) / (64.0F * Core.TileScale);
 return float2 + 3.0F * floor;
 }

 float YToIso(float screenX, float screenY, float floor) {
 screenX = (int)screenX;
 screenY = (int)screenY;
 float float0 = screenX + this->getOffX();
 float float1 = screenY + this->getOffY();
 float float2 = (float0 - 2.0F * float1) / (-64.0F * Core.TileScale);
 return float2 + 3.0F * floor;
 }

 float YToScreenExact(float objectX, float objectY, float objectZ, int screenZ) {
 float float0 = IsoUtils.YToScreen(objectX, objectY, objectZ, screenZ);
 return float0 - this->getOffY();
 }

 float XToScreenExact(float objectX, float objectY, float objectZ, int screenZ) {
 float float0 = IsoUtils.XToScreen(objectX, objectY, objectZ, screenZ);
 return float0 - this->getOffX();
 }

 void copyFrom(PlayerCamera other) {
 this->OffX = other.OffX;
 this->OffY = other.OffY;
 this->TOffX = other.TOffX;
 this->TOffY = other.TOffY;
 this->lastOffX = other.lastOffX;
 this->lastOffY = other.lastOffY;
 this->RightClickTargetX = other.RightClickTargetX;
 this->RightClickTargetY = other.RightClickTargetY;
 this->RightClickX = other.RightClickX;
 this->RightClickY = other.RightClickY;
 this->DeferedX = other.DeferedX;
 this->DeferedY = other.DeferedY;
 this->zoom = other.zoom;
 this->OffscreenWidth = other.OffscreenWidth;
 this->OffscreenHeight = other.OffscreenHeight;
 }

 void initFromIsoCamera(int _playerIndex) {
 this->copyFrom(IsoCamera.cameras[_playerIndex]);
 this->zoom = Core.getInstance().getZoom(_playerIndex);
 this->OffscreenWidth = IsoCamera.getOffscreenWidth(_playerIndex);
 this->OffscreenHeight = IsoCamera.getOffscreenHeight(_playerIndex);
 }
}
} // namespace iso
} // namespace zombie
