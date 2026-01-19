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
:
    Vector2 position = new Vector2();
    Vector2 rotation = new Vector2();
    Operation operation = Operation.NONE;
    bool moving = false;
    int time = 0;
}
} // namespace characters
} // namespace zombie
