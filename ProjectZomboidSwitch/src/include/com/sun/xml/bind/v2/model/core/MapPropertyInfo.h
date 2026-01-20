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


class MapPropertyInfo {
public:
    virtual ~MapPropertyInfo() = default;
    QName getXmlName();

    bool isCollectionNillable();

   NonElement<T, C> getKeyType();

   NonElement<T, C> getValueType();
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
