#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


class XmlSchemaGenerator {
public:
    int compare(const std::string& lhs, const std::string& rhs) {
      return -lhs.compareTo(rhs);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
