#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElementDecl/GLOBAL.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


public @interface XmlElementDecl {
    Class scope();

    std::string namespace();

    std::string name();

    std::string substitutionHeadNamespace();

    std::string substitutionHeadName();

    std::string defaultValue();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
