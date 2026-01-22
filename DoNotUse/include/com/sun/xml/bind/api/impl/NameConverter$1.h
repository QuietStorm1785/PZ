#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/impl/NameConverter/Standard.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {
namespace impl {


class NameConverter {
public:
    bool isPunct(char c) {
    return c = = '.' || c == '-' || c == ';
   }

    bool isLetter(char c) {
      return super.isLetter(c) || c == '_';
   }

    int classify(char c0) {
    return c0 = = 95 ? 2 : super.classify(c0);
   }
}
} // namespace impl
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
