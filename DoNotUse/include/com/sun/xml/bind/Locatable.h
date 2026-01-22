#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Locator.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class Locatable {
public:
    virtual ~Locatable() = default;
    Locator sourceLocation();
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
