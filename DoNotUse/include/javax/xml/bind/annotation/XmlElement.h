#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElement/DEFAULT.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


public @interface XmlElement {
    std::string name();

    bool nillable();

    bool required();

    std::string namespace();

    std::string defaultValue();

    Class type();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
