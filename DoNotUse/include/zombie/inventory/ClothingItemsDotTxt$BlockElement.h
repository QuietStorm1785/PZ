#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ClothingItemsDotTxt/Block.h"
#include "zombie/inventory/ClothingItemsDotTxt/Value.h"

namespace zombie {
namespace inventory {


class ClothingItemsDotTxt {
public:
    virtual ~ClothingItemsDotTxt() = default;
    Block asBlock();

    Value asValue();

    std::string toXML();
}
} // namespace inventory
} // namespace zombie
