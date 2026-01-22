#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/SpawnRegions/Profession.h"

namespace zombie {
namespace network {


class SpawnRegions {
public:
    std::string name;
    std::string file;
    std::string serverfile;
   public std::vector<Profession> professions;
}
} // namespace network
} // namespace zombie
