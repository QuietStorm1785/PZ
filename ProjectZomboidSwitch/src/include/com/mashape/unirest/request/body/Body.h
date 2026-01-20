#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/apache/http/HttpEntity.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {
namespace body {


class Body {
public:
    virtual ~Body() = default;
    HttpEntity getEntity();
}
} // namespace body
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
