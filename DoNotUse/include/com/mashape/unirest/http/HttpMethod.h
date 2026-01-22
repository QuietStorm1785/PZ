#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace mashape {
namespace unirest {
namespace http {

enum class HttpMethod {
   GET,
   POST,
   PUT,
   DELETE,
   PATCH,
   HEAD,
   OPTIONS;
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
