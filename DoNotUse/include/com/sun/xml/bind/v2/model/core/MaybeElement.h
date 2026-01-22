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


class MaybeElement {
public:
    virtual ~MaybeElement() = default;
    bool isElement();

    QName getElementName();

   Element<T, C> asElement();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
