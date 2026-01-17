#include "zombie/iso/areas/isoregion/data/DataChunk.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {

protected
DataChunk::DataChunk(int int1, int int2, DataCell dataCell, int int0) {
  // TODO: Implement DataChunk
  return nullptr;
}

int DataChunk::getHashId() {
  // TODO: Implement getHashId
  return 0;
}

int DataChunk::getChunkX() {
  // TODO: Implement getChunkX
  return 0;
}

int DataChunk::getChunkY() {
  // TODO: Implement getChunkY
  return 0;
}

long DataChunk::getLastUpdateStamp() {
  // TODO: Implement getLastUpdateStamp
  return 0;
}

void DataChunk::setLastUpdateStamp(long _lastUpdateStamp) {
  // TODO: Implement setLastUpdateStamp
}

bool DataChunk::isDirty(int int0) {
  // TODO: Implement isDirty
  return false;
}

void DataChunk::setDirty(int int0) {
  // TODO: Implement setDirty
}

void DataChunk::setDirtyAllActive() {
  // TODO: Implement setDirtyAllActive
}

void DataChunk::unsetDirtyAll() {
  // TODO: Implement unsetDirtyAll
}

bool DataChunk::validCoords(int int2, int int1, int int0) {
  // TODO: Implement validCoords
  return false;
}

int DataChunk::getCoord1D(int int0, int int1, int int2) {
  // TODO: Implement getCoord1D
  return 0;
}

uint8_t DataChunk::getSquare(int x, int y, int z) {
  // TODO: Implement getSquare
  return 0;
}

uint8_t DataChunk::getSquare(int x, int y, int z, bool ignoreCoordCheck) {
  // TODO: Implement getSquare
  return 0;
}

uint8_t DataChunk::setOrAddSquare(int int0, int int1, int int2, uint8_t byte0) {
  // TODO: Implement setOrAddSquare
  return 0;
}

uint8_t DataChunk::setOrAddSquare(int int0, int int1, int int2, uint8_t byte0,
                                  bool boolean0) {
  // TODO: Implement setOrAddSquare
  return 0;
}

void DataChunk::ensureSquares(int int0) {
  // TODO: Implement ensureSquares
}

void DataChunk::ensureSquareArray(int int1) {
  // TODO: Implement ensureSquareArray
}

void DataChunk::save(ByteBuffer bb) {
  // TODO: Implement save
}

void DataChunk::load(ByteBuffer bb, int worldVersion, bool readLength) {
  // TODO: Implement load
}

void DataChunk::setSelectedFlags(int x, int y, int z) {
  // TODO: Implement setSelectedFlags
}

bool DataChunk::selectedHasFlags(uint8_t flags) {
  // TODO: Implement selectedHasFlags
  return false;
}

bool DataChunk::squareHasFlags(int int0, int int1, int int2, uint8_t byte0) {
  // TODO: Implement squareHasFlags
  return false;
}

bool DataChunk::squareHasFlags(int int0, uint8_t byte1) {
  // TODO: Implement squareHasFlags
  return false;
}

uint8_t DataChunk::squareGetFlags(int x, int y, int z) {
  // TODO: Implement squareGetFlags
  return 0;
}

uint8_t DataChunk::squareGetFlags(int int0) {
  // TODO: Implement squareGetFlags
  return 0;
}

void DataChunk::squareAddFlags(int int0, int int1, int int2, uint8_t byte0) {
  // TODO: Implement squareAddFlags
}

void DataChunk::squareAddFlags(int int0, uint8_t byte0) {
  // TODO: Implement squareAddFlags
}

void DataChunk::squareRemoveFlags(int int0, int int1, int int2, uint8_t byte0) {
  // TODO: Implement squareRemoveFlags
}

void DataChunk::squareRemoveFlags(int int0, uint8_t byte0) {
  // TODO: Implement squareRemoveFlags
}

bool DataChunk::squareCanConnect(int int1, int int2, int int0, uint8_t byte0) {
  // TODO: Implement squareCanConnect
  return false;
}

bool DataChunk::squareCanConnect(int int1, int int0, uint8_t byte0) {
  // TODO: Implement squareCanConnect
  return false;
}

IsoChunkRegion DataChunk::getIsoChunkRegion(int x, int y, int z) {
  // TODO: Implement getIsoChunkRegion
  return nullptr;
}

IsoChunkRegion DataChunk::getIsoChunkRegion(int int1, int int0) {
  // TODO: Implement getIsoChunkRegion
  return nullptr;
}

void DataChunk::setRegion(int x, int y, int z, uint8_t regionIndex) {
  // TODO: Implement setRegion
}

void DataChunk::recalculate() {
  // TODO: Implement recalculate
}

void DataChunk::recalculate(int int0) {
  // TODO: Implement recalculate
}

IsoChunkRegion DataChunk::floodFill(int int1, int int2, int int0) {
  // TODO: Implement floodFill
  return nullptr;
}

bool DataChunk::isExploredPosition(int int1, int int2) {
  // TODO: Implement isExploredPosition
  return false;
}

void DataChunk::setExploredPosition(int int1, int int2) {
  // TODO: Implement setExploredPosition
}

void DataChunk::clearExploredPositions() {
  // TODO: Implement clearExploredPositions
}

DataSquarePos DataChunk::getNeighbor(DataSquarePos dataSquarePos,
                                     uint8_t byte0) {
  // TODO: Implement getNeighbor
  return nullptr;
}

void DataChunk::link(DataChunk dataChunk1, DataChunk dataChunk2,
                     DataChunk dataChunk3, DataChunk dataChunk4) {
  // TODO: Implement link
}

void DataChunk::linkRegionsOnSide(int int4, DataChunk dataChunk0,
                                  uint8_t byte0) {
  // TODO: Implement linkRegionsOnSide
}

void DataChunk::resetEnclosedSide(int int0, uint8_t byte0) {
  // TODO: Implement resetEnclosedSide
}

void DataChunk::interConnect() {
  // TODO: Implement interConnect
}

void DataChunk::floodFillExpandWorldRegion(IsoChunkRegion chunkRegion0,
                                           IsoWorldRegion worldRegion) {
  // TODO: Implement floodFillExpandWorldRegion
}

void DataChunk::recalcRoofs() {
  // TODO: Implement recalcRoofs
}

} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
