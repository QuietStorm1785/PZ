#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class DataCell {
public:
 const DataRoot dataRoot;
protected
 Map<Integer, DataChunk> dataChunks = std::make_unique<HashMap<>>();

protected
 DataCell(DataRoot dataRootx, int var2, int var3, int var4) {
 this->dataRoot = dataRootx;
 }

 DataRoot getDataRoot() { return this->dataRoot; }

 DataChunk getChunk(int int0) { return this->dataChunks.get(int0); }

 DataChunk addChunk(int int0, int int1, int int2) {
 DataChunk dataChunk = new DataChunk(int0, int1, this, int2);
 this->dataChunks.put(int2, dataChunk);
 return dataChunk;
 }

 void setChunk(DataChunk dataChunk) {
 this->dataChunks.put(dataChunk.getHashId(), dataChunk);
 }

 void getAllChunks(List<DataChunk> list) {
 for (Entry entry : this->dataChunks.entrySet()) {
 list.add((DataChunk)entry.getValue());
 }
 }
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
