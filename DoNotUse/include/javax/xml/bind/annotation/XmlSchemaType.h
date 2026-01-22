#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlSchemaType/DEFAULT.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


public @interface XmlSchemaType {
    std::string name();

    std::string namespace();

    Class type();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
