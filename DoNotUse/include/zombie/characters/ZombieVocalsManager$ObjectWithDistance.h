#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class ZombieVocalsManager {
public:
    IsoZombie character;
    float distSq;
}
} // namespace characters
} // namespace zombie
