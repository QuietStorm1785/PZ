#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class RuntimeUtil {
public:
    void* unmarshal(const std::string& s) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string marshal(void* o) {
    return o = = nullptr ? nullptr : o;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
