#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/impl/NameConverter/Standard.h"
#include "javax/lang/model/SourceVersion.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {
namespace impl {


class NameConverter {
public:
    std::string toConstantName(const std::string& token) {
    std::string name = super.toConstantName(token);
      return !SourceVersion.isKeyword(name) ? name : '_' + name;
   }
}
} // namespace impl
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
