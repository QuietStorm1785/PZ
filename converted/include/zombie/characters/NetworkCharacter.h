#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NetworkCharacter {
public:
 float minMovement;
 float maxMovement;
 long deltaTime;
 public NetworkCharacter.Transform transform = new NetworkCharacter.Transform();
 const Vector2 movement = new Vector2();
 NetworkCharacter.Point d1 = new NetworkCharacter.Point();
 NetworkCharacter.Point d2 = new NetworkCharacter.Point();

 public NetworkCharacter() {
 this->minMovement = 0.075F;
 this->maxMovement = 0.5F;
 this->deltaTime = 10L;
 }

 NetworkCharacter(float float0, float float1, long long0) {
 this->minMovement = float0;
 this->maxMovement = float1;
 this->deltaTime = long0;
 }

 void updateTransform(float px, float py, float rx, float ry) {
 this->transform.position.x = px;
 this->transform.position.y = py;
 this->transform.rotation.x = rx;
 this->transform.rotation.y = ry;
 }

 void updateInterpolationPoint(int t, float px, float py, float rx, float ry) {
 if (this->d2.t == 0) {
 this->updateTransform(px, py, rx, ry);
 }

 this->d2.t = t;
 this->d2.px = px;
 this->d2.py = py;
 this->d2.rx = rx;
 this->d2.ry = ry;
 }

 void updatePointInternal(float px, float py, float rx, float ry) {
 this->d1.px = px;
 this->d1.py = py;
 this->d1.rx = rx;
 this->d1.ry = ry;
 }

 void updateExtrapolationPoint(int t, float px, float py, float rx, float ry) {
 if (t > this->d1.t) {
 this->d2.t = this->d1.t;
 this->d2.px = this->d1.px;
 this->d2.py = this->d1.py;
 this->d2.rx = this->d1.rx;
 this->d2.ry = this->d1.ry;
 this->d1.t = t;
 this->d1.px = px;
 this->d1.py = py;
 this->d1.rx = rx;
 this->d1.ry = ry;
 }
 }

 void extrapolate(int int0) {
 float float0 = (float)(int0 - this->d1.t) / (this->d1.t - this->d2.t);
 float float1 = this->d1.px - this->d2.px;
 float float2 = this->d1.py - this->d2.py;
 this->movement.x = float1 * float0;
 this->movement.y = float2 * float0;
 if (float1 > this->minMovement || float2 > this->minMovement || -float1 > this->minMovement || -float2 > this->minMovement) {
 this->transform.moving = true;
 this->transform.rotation.x = this->movement.x;
 this->transform.rotation.y = this->movement.y;
 this->transform.rotation.normalize();
 }

 this->transform.position.x = this->d1.px + this->movement.x;
 this->transform.position.y = this->d1.py + this->movement.y;
 this->transform.operation = NetworkCharacter.Operation.EXTRAPOLATION;
 }

 void extrapolateInternal(int int0, float float2, float float4) {
 float float0 = (float)(int0 - this->d1.t) / (int0 - this->d1.t);
 float float1 = float2 - this->d1.px;
 float float3 = float4 - this->d1.py;
 this->movement.x = float1 * float0;
 this->movement.y = float3 * float0;
 if (this->movement.getLength() > this->maxMovement) {
 this->movement.setLength(this->maxMovement);
 }

 if (float1 > this->minMovement || float3 > this->minMovement || -float1 > this->minMovement || -float3 > this->minMovement) {
 this->transform.moving = true;
 this->transform.rotation.x = this->movement.x;
 this->transform.rotation.y = this->movement.y;
 this->transform.rotation.normalize();
 }

 this->transform.position.x = float2 + this->movement.x;
 this->transform.position.y = float4 + this->movement.y;
 this->transform.operation = NetworkCharacter.Operation.EXTRAPOLATION;
 }

 void interpolate(int int0) {
 float float0 = (float)(int0 - this->d1.t) / (this->d2.t - this->d1.t);
 float float1 = this->d2.px - this->d1.px;
 float float2 = this->d2.py - this->d1.py;
 this->movement.x = float1 * float0;
 this->movement.y = float2 * float0;
 if (this->movement.getLength() > this->maxMovement) {
 this->movement.setLength(this->maxMovement);
 }

 if (float1 > this->minMovement || float2 > this->minMovement || -float1 > this->minMovement || -float2 > this->minMovement) {
 this->transform.moving = true;
 this->transform.rotation.x = this->movement.x;
 this->transform.rotation.y = this->movement.y;
 this->transform.rotation.normalize();
 }

 this->transform.position.x = this->d1.px + this->movement.x;
 this->transform.position.y = this->d1.py + this->movement.y;
 this->transform.operation = NetworkCharacter.Operation.INTERPOLATION;
 }

 public NetworkCharacter.Transform predict(int dt, int t, float px, float py, float rx, float ry) {
 this->transform.moving = false;
 this->transform.operation = NetworkCharacter.Operation.NONE;
 this->transform.time = t + dt;
 this->updateExtrapolationPoint(t, px, py, rx, ry);
 if (this->d1.t != 0 && this->d2.t != 0) {
 this->extrapolate(dt + t);
 } else {
 this->updateTransform(px, py, rx, ry);
 }

 return this->transform;
 }

 public NetworkCharacter.Transform reconstruct(int t, float px, float py, float rx, float ry) {
 this->transform.moving = false;
 this->transform.operation = NetworkCharacter.Operation.NONE;
 if (this->d2.t != 0) {
 if (t + this->deltaTime <= this->d2.t) {
 this->updatePointInternal(px, py, rx, ry);
 if (this->d1.t != 0 && this->d1.t != t) {
 this->interpolate(t);
 }

 this->d1.t = t;
 } else if (t > this->d2.t && t < this->d2.t + 2000) {
 this->extrapolateInternal(t, px, py);
 this->updatePointInternal(px, py, rx, ry);
 this->d1.t = t;
 }
 }

 return this->transform;
 }

 void checkReset(int t) {
 if (t > 2000 + this->d2.t) {
 this->reset();
 }
 }

 void checkResetPlayer(int t) {
 if (t > 2000 + this->d1.t) {
 this->reset();
 }
 }

 void reset() {
 this->d1.t = 0;
 this->d1.px = 0.0F;
 this->d1.py = 0.0F;
 this->d1.rx = 0.0F;
 this->d1.ry = 0.0F;
 this->d2.t = 0;
 this->d2.px = 0.0F;
 this->d2.py = 0.0F;
 this->d2.rx = 0.0F;
 this->d2.ry = 0.0F;
 }

 public static enum Operation {
 INTERPOLATION,
 EXTRAPOLATION,
 NONE;
 }

 static class Point {
 float px = 0.0F;
 float py = 0.0F;
 float rx = 0.0F;
 float ry = 0.0F;
 int t = 0;
 }

 public static class Transform {
 Vector2 position = new Vector2();
 Vector2 rotation = new Vector2();
 public NetworkCharacter.Operation operation = NetworkCharacter.Operation.NONE;
 bool moving = false;
 int time = 0;
 }
}
} // namespace characters
} // namespace zombie
