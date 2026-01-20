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

enum class WildcardMode {
   STRICT(false, true),
   SKIP(true, false),
   LAX(true, true);

    const bool allowDom;
    const bool allowTypedObject;

    private WildcardMode(bool allowDom, bool allowTypedObject) {
      this.allowDom = allowDom;
      this.allowTypedObject = allowTypedObject;
   }
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
