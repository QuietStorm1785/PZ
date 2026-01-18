#include "zombie/erosion/ErosionMain.h"

namespace zombie {
namespace erosion {

ErosionMain ErosionMain::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

public
ErosionMain::ErosionMain(IsoSpriteManager _sprMngr, bool _debug) {
 // TODO: Implement ErosionMain
 return nullptr;
}

ErosionConfig ErosionMain::getConfig() {
 // TODO: Implement getConfig
 return nullptr;
}

ErosionSeason ErosionMain::getSeasons() {
 // TODO: Implement getSeasons
 return nullptr;
}

int ErosionMain::getEtick() {
 // TODO: Implement getEtick
 return 0;
}

IsoSpriteManager ErosionMain::getSpriteManager() {
 // TODO: Implement getSpriteManager
 return nullptr;
}

void ErosionMain::mainTimer() {
 // TODO: Implement mainTimer
}

void ErosionMain::snowCheck() {
 // TODO: Implement snowCheck
}

int ErosionMain::getSnowFraction() {
 // TODO: Implement getSnowFraction
 return 0;
}

int ErosionMain::getSnowFractionYesterday() {
 // TODO: Implement getSnowFractionYesterday
 return 0;
}

bool ErosionMain::isSnow() {
 // TODO: Implement isSnow
 return false;
}

void ErosionMain::sendState(ByteBuffer bb) {
 // TODO: Implement sendState
}

void ErosionMain::receiveState(ByteBuffer bb) {
 // TODO: Implement receiveState
}

void ErosionMain::loadGridsquare(IsoGridSquare square0) {
 // TODO: Implement loadGridsquare
}

void ErosionMain::initGridSquare(IsoGridSquare square0,
 ErosionData.Square square1) {
 // TODO: Implement initGridSquare
}

void ErosionMain::getChunk(IsoGridSquare square) {
 // TODO: Implement getChunk
}

void ErosionMain::initChunk(IsoChunk chunk1, ErosionData.Chunk chunk0) {
 // TODO: Implement initChunk
}

bool ErosionMain::initConfig() {
 // TODO: Implement initConfig
 return false;
}

void ErosionMain::start() {
 // TODO: Implement start
}

void ErosionMain::loadChunk(IsoChunk chunk1) {
 // TODO: Implement loadChunk
}

void ErosionMain::DebugUpdateMapNow() {
 // TODO: Implement DebugUpdateMapNow
}

void ErosionMain::updateMapNow() {
 // TODO: Implement updateMapNow
}

void ErosionMain::LoadGridsquare(IsoGridSquare _sq) {
 // TODO: Implement LoadGridsquare
}

void ErosionMain::ChunkLoaded(IsoChunk _chunk) {
 // TODO: Implement ChunkLoaded
}

void ErosionMain::EveryTenMinutes() {
 // TODO: Implement EveryTenMinutes
}

void ErosionMain::Reset() {
 // TODO: Implement Reset
}

} // namespace erosion
} // namespace zombie
