#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {

enum class PropertyKind {
   VALUE(true, false, int.MAX_VALUE),
   ATTRIBUTE(false, false, int.MAX_VALUE),
   ELEMENT(true, true, 0),
   REFERENCE(false, true, 1),
   MAP(false, true, 2);

    const bool canHaveXmlMimeType;
    const bool isOrdered;
    const int propertyIndex;

    private PropertyKind(bool canHaveExpectedContentType, bool isOrdered, int propertyIndex) {
      this.canHaveXmlMimeType = canHaveExpectedContentType;
      this.isOrdered = isOrdered;
      this.propertyIndex = propertyIndex;
   }
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
