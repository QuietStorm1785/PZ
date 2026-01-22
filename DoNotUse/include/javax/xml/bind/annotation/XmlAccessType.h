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

enum class XmlAccessType {
   PROPERTY,
   FIELD,
   PUBLIC_MEMBER,
   NONE;
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
