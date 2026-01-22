#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoGridSquare {
public:
    static uint8_t PUDDLES_DIR_NONE = 1;
    static uint8_t PUDDLES_DIR_NE = 2;
    static uint8_t PUDDLES_DIR_NW = 4;
    static uint8_t PUDDLES_DIR_ALL = 8;
}
} // namespace iso
} // namespace zombie
