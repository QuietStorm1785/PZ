#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/NetworkCharacter/Operation.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace characters {


class NetworkCharacter {
public:
    auto position = std::make_shared<Vector2>();
    auto rotation = std::make_shared<Vector2>();
    Operation operation = Operation.NONE;
    bool moving = false;
    int time = 0;
}
} // namespace characters
} // namespace zombie
