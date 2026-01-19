#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/PersistentOutfits/IOutfitter.h"

namespace zombie {


class PersistentOutfits {
public:
    int m_index;
    std::string m_outfitName;
    bool m_useSeed = true;
    IOutfitter m_outfitter;

   private PersistentOutfits$Data() {
   }
}
} // namespace zombie
