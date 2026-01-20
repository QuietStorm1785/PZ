#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElementRef/DEFAULT.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


public @interface XmlElementRef {
    Class type();

    std::string namespace();

    std::string name();

    bool required();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
