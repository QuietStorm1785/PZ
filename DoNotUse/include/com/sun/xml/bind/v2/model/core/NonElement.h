#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class NonElement {
public:
    virtual ~NonElement() = default;
    QName ANYTYPE_NAME = std::make_shared<QName>("http://www.w3.org/2001/XMLSchema", "anyType");

    QName getTypeName();

    bool isSimpleType();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
