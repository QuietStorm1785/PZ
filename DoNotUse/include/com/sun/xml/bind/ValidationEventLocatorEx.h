#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventLocator.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class ValidationEventLocatorEx {
public:
    virtual ~ValidationEventLocatorEx() = default;
    std::string getFieldName();
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
