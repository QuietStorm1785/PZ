#include "zombie/network/ServerMap.h"

namespace zombie {
namespace network {

short ServerMap::getUniqueZombieId() {
 // TODO: Implement getUniqueZombieId
 return 0;
}

Vector3 ServerMap::getStartLocation(ServerWorldDatabase.LogonResult var1) {
 // TODO: Implement getStartLocation
 return nullptr;
}

void ServerMap::SaveAll() {
 // TODO: Implement SaveAll
}

void ServerMap::QueueSaveAll() {
 // TODO: Implement QueueSaveAll
}

void ServerMap::QueueQuit() {
 // TODO: Implement QueueQuit
}

int ServerMap::toServerCellX(int int0) {
 // TODO: Implement toServerCellX
 return 0;
}

int ServerMap::toServerCellY(int int0) {
 // TODO: Implement toServerCellY
 return 0;
}

int ServerMap::toWorldCellX(int int0) {
 // TODO: Implement toWorldCellX
 return 0;
}

int ServerMap::toWorldCellY(int int0) {
 // TODO: Implement toWorldCellY
 return 0;
}

int ServerMap::getMaxX() {
 // TODO: Implement getMaxX
 return 0;
}

int ServerMap::getMaxY() {
 // TODO: Implement getMaxY
 return 0;
}

int ServerMap::getMinX() {
 // TODO: Implement getMinX
 return 0;
}

int ServerMap::getMinY() {
 // TODO: Implement getMinY
 return 0;
}

void ServerMap::init(IsoMetaGrid metaGrid) {
 // TODO: Implement init
}

bool ServerMap::isValidCell(int int1, int int0) {
 // TODO: Implement isValidCell
 return false;
}

void ServerMap::loadOrKeepRelevent(int int0, int int1) {
 // TODO: Implement loadOrKeepRelevent
}

void ServerMap::characterIn(IsoPlayer player) {
 // TODO: Implement characterIn
}

void ServerMap::characterIn(int int1, int int3, int int7) {
 // TODO: Implement characterIn
}

void ServerMap::loadMapChunk(int int1, int int3) {
 // TODO: Implement loadMapChunk
}

void ServerMap::preupdate() {
 // TODO: Implement preupdate
}

IsoGridSquare ServerMap::getRandomSquareFromCell(int int0, int int1) {
 // TODO: Implement getRandomSquareFromCell
 return nullptr;
}

void ServerMap::postupdate() {
 // TODO: Implement postupdate
}

void ServerMap::physicsCheck(int int1, int int3) {
 // TODO: Implement physicsCheck
}

bool ServerMap::outsidePlayerInfluence(ServerMap.ServerCell serverCell) {
 // TODO: Implement outsidePlayerInfluence
 return false;
}

void ServerMap::saveZoneInsidePlayerInfluence(short short0) {
 // TODO: Implement saveZoneInsidePlayerInfluence
}

bool ServerMap::InsideThePlayerInfluence(ServerMap.ServerCell serverCell,
 short short0) {
 // TODO: Implement InsideThePlayerInfluence
 return false;
}

IsoGridSquare ServerMap::getGridSquare(int int0, int int1, int int2) {
 // TODO: Implement getGridSquare
 return nullptr;
}

void ServerMap::setGridSquare(int int1, int int3, int int10,
 IsoGridSquare square) {
 // TODO: Implement setGridSquare
}

bool ServerMap::isInLoaded(float float0, float float1) {
 // TODO: Implement isInLoaded
 return false;
}

IsoChunk ServerMap::getChunk(int int1, int int0) {
 // TODO: Implement getChunk
 return nullptr;
}

void ServerMap::setSoftResetChunk(IsoChunk chunk) {
 // TODO: Implement setSoftResetChunk
}

void ServerMap::clearSoftResetChunk(IsoChunk chunk) {
 // TODO: Implement clearSoftResetChunk
}

public
ServerMap::DistToCellComparator() {
 // TODO: Implement DistToCellComparator
 return nullptr;
}

void ServerMap::init() {
 // TODO: Implement init
}

int ServerMap::compare(ServerMap.ServerCell serverCell0,
 ServerMap.ServerCell serverCell1) {
 // TODO: Implement compare
 return 0;
}

float ServerMap::distToCell(float float1, float float3,
 ServerMap.ServerCell serverCell) {
 // TODO: Implement distToCell
 return 0;
}

bool ServerMap::Load2() {
 // TODO: Implement Load2
 return false;
}

void ServerMap::loadVehicles() {
 // TODO: Implement loadVehicles
}

void ServerMap::RecalcAll2() {
 // TODO: Implement RecalcAll2
}

void ServerMap::Unload() {
 // TODO: Implement Unload
}

void ServerMap::Save() {
 // TODO: Implement Save
}

void ServerMap::update() {
 // TODO: Implement update
}

IsoChunk ServerMap::getChunk(int int1, int int0) {
 // TODO: Implement getChunk
 return nullptr;
}

int ServerMap::getWX() {
 // TODO: Implement getWX
 return 0;
}

int ServerMap::getWY() {
 // TODO: Implement getWY
 return 0;
}

} // namespace network
} // namespace zombie
