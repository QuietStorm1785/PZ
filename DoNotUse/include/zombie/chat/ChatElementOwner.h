#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"

namespace zombie {
namespace chat {


class ChatElementOwner {
public:
    virtual ~ChatElementOwner() = default;
    float getX();

    float getY();

    float getZ();

    IsoGridSquare getSquare();
}
} // namespace chat
} // namespace zombie
