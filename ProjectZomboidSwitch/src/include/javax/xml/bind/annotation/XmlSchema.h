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


public @interface XmlSchema {
    std::string NO_LOCATION = "##generate";

   XmlNs[] xmlns() default {};

    std::string namespace();

    XmlNsForm elementFormDefault();

    XmlNsForm attributeFormDefault();

    std::string location();
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
