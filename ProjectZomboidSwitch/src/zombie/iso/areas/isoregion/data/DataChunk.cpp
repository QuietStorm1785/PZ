#include <cstdint>
#include "zombie\iso\areas\isoregion\data/DataChunk.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {

protected DataChunk::DataChunk(int var1, int var2, DataCell var3, int var4) {
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

void DataChunk::setLastUpdateStamp(long var1) {
    // TODO: Implement setLastUpdateStamp
}

bool DataChunk::isDirty(int var1) {
    // TODO: Implement isDirty
    return false;
}

void DataChunk::setDirty(int var1) {
    // TODO: Implement setDirty
}

void DataChunk::setDirtyAllActive() {
    // TODO: Implement setDirtyAllActive
}

void DataChunk::unsetDirtyAll() {
    // TODO: Implement unsetDirtyAll
}

bool DataChunk::validCoords(int var1, int var2, int var3) {
    // TODO: Implement validCoords
    return false;
}

int DataChunk::getCoord1D(int var1, int var2, int var3) {
    // TODO: Implement getCoord1D
    return 0;
}

uint8_t DataChunk::getSquare(int var1, int var2, int var3) {
    // TODO: Implement getSquare
    return 0;
}

uint8_t DataChunk::getSquare(int var1, int var2, int var3, bool var4) {
    // TODO: Implement getSquare
    return 0;
}

uint8_t DataChunk::setOrAddSquare(int var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement setOrAddSquare
    return 0;
}

uint8_t DataChunk::setOrAddSquare(int var1, int var2, int var3, uint8_t var4, bool var5) {
    // TODO: Implement setOrAddSquare
    return 0;
}

void DataChunk::ensureSquares(int var1) {
    // TODO: Implement ensureSquares
}

void DataChunk::ensureSquareArray(int var1) {
    // TODO: Implement ensureSquareArray
}

void DataChunk::save(ByteBuffer var1) {
    // TODO: Implement save
}

void DataChunk::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void DataChunk::setSelectedFlags(int var1, int var2, int var3) {
    // TODO: Implement setSelectedFlags
}

bool DataChunk::selectedHasFlags(uint8_t var1) {
    // TODO: Implement selectedHasFlags
    return false;
}

bool DataChunk::squareHasFlags(int var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement squareHasFlags
    return false;
}

bool DataChunk::squareHasFlags(int var1, uint8_t var2) {
    // TODO: Implement squareHasFlags
    return false;
}

uint8_t DataChunk::squareGetFlags(int var1, int var2, int var3) {
    // TODO: Implement squareGetFlags
    return 0;
}

uint8_t DataChunk::squareGetFlags(int var1) {
    // TODO: Implement squareGetFlags
    return 0;
}

void DataChunk::squareAddFlags(int var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement squareAddFlags
}

void DataChunk::squareAddFlags(int var1, uint8_t var2) {
    // TODO: Implement squareAddFlags
}

void DataChunk::squareRemoveFlags(int var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement squareRemoveFlags
}

void DataChunk::squareRemoveFlags(int var1, uint8_t var2) {
    // TODO: Implement squareRemoveFlags
}

bool DataChunk::squareCanConnect(int var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement squareCanConnect
    return false;
}

bool DataChunk::squareCanConnect(int var1, int var2, uint8_t var3) {
    // TODO: Implement squareCanConnect
    return false;
}

IsoChunkRegion DataChunk::getIsoChunkRegion(int var1, int var2, int var3) {
    // TODO: Implement getIsoChunkRegion
    return nullptr;
}

IsoChunkRegion DataChunk::getIsoChunkRegion(int var1, int var2) {
    // TODO: Implement getIsoChunkRegion
    return nullptr;
}

void DataChunk::setRegion(int var1, int var2, int var3, uint8_t var4) {
    // TODO: Implement setRegion
}

void DataChunk::recalculate() {
    // TODO: Implement recalculate
}

void DataChunk::recalculate(int var1) {
    // TODO: Implement recalculate
}

IsoChunkRegion DataChunk::floodFill(int var1, int var2, int var3) {
    // TODO: Implement floodFill
    return nullptr;
}

bool DataChunk::isExploredPosition(int var1, int var2) {
    // TODO: Implement isExploredPosition
    return false;
}

void DataChunk::setExploredPosition(int var1, int var2) {
    // TODO: Implement setExploredPosition
}

void DataChunk::clearExploredPositions() {
    // TODO: Implement clearExploredPositions
}

DataSquarePos DataChunk::getNeighbor(DataSquarePos var1, uint8_t var2) {
    // TODO: Implement getNeighbor
    return nullptr;
}

void DataChunk::link(DataChunk var1, DataChunk var2, DataChunk var3, DataChunk var4) {
    // TODO: Implement link
}

void DataChunk::linkRegionsOnSide(int var1, DataChunk var2, uint8_t var3) {
    // TODO: Implement linkRegionsOnSide
}

void DataChunk::resetEnclosedSide(int var1, uint8_t var2) {
    // TODO: Implement resetEnclosedSide
}

void DataChunk::interConnect() {
    // TODO: Implement interConnect
}

void DataChunk::floodFillExpandWorldRegion(IsoChunkRegion var1, IsoWorldRegion var2) {
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
