#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


public @interface XmlAttribute {
    std::string name();

    bool required();

    std::string namespace();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
