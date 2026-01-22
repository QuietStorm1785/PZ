#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/PredicatedFileWatcher.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class OutfitManager {
public:
    ClothingItem m_item;
    std::string m_guid;
    std::string m_filePath;
    PredicatedFileWatcher m_fileWatcher;

   private OutfitManager$ClothingItemEntry() {
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
