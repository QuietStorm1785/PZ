#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlAttribute.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class HairStyle {
public:
    std::string category;
    std::string style;
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
