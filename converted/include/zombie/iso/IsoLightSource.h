#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoLightSwitch.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoLightSource {
public:
 static int NextID = 1;
 int ID;
 int x;
 int y;
 int z;
 float r;
 float g;
 float b;
 float rJNI;
 float gJNI;
 float bJNI;
 int radius;
 bool bActive;
 bool bWasActive;
 bool bActiveJNI;
 int life = -1;
 int startlife = -1;
 IsoBuilding localToBuilding;
 bool bHydroPowered = false;
 public ArrayList<IsoLightSwitch> switches = new ArrayList<>(0);
 IsoChunk chunk;
 void* lightMap;

 public IsoLightSource(int _x, int _y, int _z, float _r, float _g, float _b, int _radius) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 this->r = _r;
 this->g = _g;
 this->b = _b;
 this->radius = _radius;
 this->bActive = true;
 }

 public IsoLightSource(int _x, int _y, int _z, float _r, float _g, float _b, int _radius, IsoBuilding building) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 this->r = _r;
 this->g = _g;
 this->b = _b;
 this->radius = _radius;
 this->bActive = true;
 this->localToBuilding = building;
 }

 public IsoLightSource(int _x, int _y, int _z, float _r, float _g, float _b, int _radius, int _life) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 this->r = _r;
 this->g = _g;
 this->b = _b;
 this->radius = _radius;
 this->bActive = true;
 this->startlife = this->life = _life;
 }

 void update() {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(this->x, this->y, this->z);
 if (!this->bHydroPowered || IsoWorld.instance.isHydroPowerOn() || square != nullptr && square.haveElectricity()) {
 if (this->bActive) {
 if (this->localToBuilding != nullptr) {
 this->r = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 this->g = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 this->b = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.7F;
 }

 if (this->life > 0) {
 this->life--;
 }

 if (this->localToBuilding != nullptr && square != nullptr) {
 this->r = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.rmod * 0.7F;
 this->g = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.gmod * 0.7F;
 this->b = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex()) * 0.8F * IsoGridSquare.bmod * 0.7F;
 }

 for (int int0 = this->x - this->radius; int0 < this->x + this->radius; int0++) {
 for (int int1 = this->y - this->radius; int1 < this->y + this->radius; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr && (this->localToBuilding.empty() || this->localToBuilding == square.getBuilding())) {
 LosUtil.TestResults testResults = LosUtil.lineClear(
 square.getCell(), this->x, this->y, this->z, square.getX(), square.getY(), square.getZ(), false
 );
 if (square.getX() == this->x && square.getY() == this->y && square.getZ() == this->z || testResults != LosUtil.TestResults.Blocked
 )
 {
 float float0 = 0.0F;
 float float1;
 if (Math.abs(square.getZ() - this->z) <= 1) {
 float1 = IsoUtils.DistanceTo(this->x, this->y, 0.0F, square.getX(), square.getY(), 0.0F);
 } else {
 float1 = IsoUtils.DistanceTo(this->x, this->y, this->z, square.getX(), square.getY(), square.getZ());
 }

 if (!(float1 > this->radius) {
 float0 = float1 / this->radius;
 float0 = 1.0F - float0;
 float0 *= float0;
 if (this->life > -1) {
 float0 *= (float)this->life / this->startlife;
 }

 float float2 = float0 * this->r * 2.0F;
 float float3 = float0 * this->g * 2.0F;
 float float4 = float0 * this->b * 2.0F;
 square.setLampostTotalR(square.getLampostTotalR() + float2);
 square.setLampostTotalG(square.getLampostTotalG() + float3);
 square.setLampostTotalB(square.getLampostTotalB() + float4);
 }
 }
 }
 }
 }
 }
 }
 } else {
 this->bActive = false;
 }
 }

 /**
 * @return the x
 */
 int getX() {
 return this->x;
 }

 /**
 * 
 * @param _x the x to set
 */
 void setX(int _x) {
 this->x = _x;
 }

 /**
 * @return the y
 */
 int getY() {
 return this->y;
 }

 /**
 * 
 * @param _y the y to set
 */
 void setY(int _y) {
 this->y = _y;
 }

 /**
 * @return the z
 */
 int getZ() {
 return this->z;
 }

 /**
 * 
 * @param _z the z to set
 */
 void setZ(int _z) {
 this->z = _z;
 }

 /**
 * @return the r
 */
 float getR() {
 return this->r;
 }

 /**
 * 
 * @param _r the r to set
 */
 void setR(float _r) {
 this->r = _r;
 }

 /**
 * @return the g
 */
 float getG() {
 return this->g;
 }

 /**
 * 
 * @param _g the g to set
 */
 void setG(float _g) {
 this->g = _g;
 }

 /**
 * @return the b
 */
 float getB() {
 return this->b;
 }

 /**
 * 
 * @param _b the b to set
 */
 void setB(float _b) {
 this->b = _b;
 }

 /**
 * @return the radius
 */
 int getRadius() {
 return this->radius;
 }

 /**
 * 
 * @param _radius the radius to set
 */
 void setRadius(int _radius) {
 this->radius = _radius;
 }

 /**
 * @return the bActive
 */
 bool isActive() {
 return this->bActive;
 }

 /**
 * 
 * @param _bActive the bActive to set
 */
 void setActive(bool _bActive) {
 this->bActive = _bActive;
 }

 /**
 * @return the bWasActive
 */
 bool wasActive() {
 return this->bWasActive;
 }

 /**
 * 
 * @param _bWasActive the bWasActive to set
 */
 void setWasActive(bool _bWasActive) {
 this->bWasActive = _bWasActive;
 }

 /**
 * @return the switches
 */
 public ArrayList<IsoLightSwitch> getSwitches() {
 return this->switches;
 }

 /**
 * 
 * @param _switches the switches to set
 */
 void setSwitches(ArrayList<IsoLightSwitch> _switches) {
 this->switches = _switches;
 }

 void clearInfluence() {
 for (int int0 = this->x - this->radius; int0 < this->x + this->radius; int0++) {
 for (int int1 = this->y - this->radius; int1 < this->y + this->radius; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 square.setLampostTotalR(0.0F);
 square.setLampostTotalG(0.0F);
 square.setLampostTotalB(0.0F);
 }
 }
 }
 }
 }

 bool isInBounds(int minX, int minY, int maxX, int maxY) {
 return this->x >= minX && this->x < maxX && this->y >= minY && this->y < maxY;
 }

 bool isInBounds() {
 IsoChunkMap[] chunkMaps = IsoWorld.instance.CurrentCell.ChunkMap;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (!chunkMaps[int0].ignore) {
 int int1 = chunkMaps[int0].getWorldXMinTiles();
 int int2 = chunkMaps[int0].getWorldXMaxTiles();
 int int3 = chunkMaps[int0].getWorldYMinTiles();
 int int4 = chunkMaps[int0].getWorldYMaxTiles();
 if (this->isInBounds(int1, int3, int2, int4) {
 return true;
 }
 }
 }

 return false;
 }

 bool isHydroPowered() {
 return this->bHydroPowered;
 }

 IsoBuilding getLocalToBuilding() {
 return this->localToBuilding;
 }
}
} // namespace iso
} // namespace zombie
