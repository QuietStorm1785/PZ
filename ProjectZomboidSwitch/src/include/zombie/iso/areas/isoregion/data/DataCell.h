#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {


class DataCell {
public:
    const DataRoot dataRoot;
   protected const Map<int, DataChunk> dataChunks = std::make_unique<std::unordered_map<>>();

    protected DataCell(DataRoot var1, int var2, int var3, int var4) {
      this.dataRoot = var1;
   }

    DataRoot getDataRoot() {
      return this.dataRoot;
   }

    DataChunk getChunk(int var1) {
      return this.dataChunks.get(var1);
   }

    DataChunk addChunk(int var1, int var2, int var3) {
    DataChunk var4 = std::make_shared<DataChunk>(var1, var2, this, var3);
      this.dataChunks.put(var3, var4);
    return var4;
   }

    void setChunk(DataChunk var1) {
      this.dataChunks.put(var1.getHashId(), var1);
   }

    void getAllChunks(List<DataChunk> var1) {
      for (Entry var3 : this.dataChunks.entrySet()) {
         var1.push_back((DataChunk)var3.getValue());
      }
   }
}
} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
