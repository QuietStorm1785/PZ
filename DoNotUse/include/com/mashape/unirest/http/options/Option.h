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
namespace options {

enum class Option {
   HTTPCLIENT,
   ASYNCHTTPCLIENT,
   CONNECTION_TIMEOUT,
   SOCKET_TIMEOUT,
   DEFAULT_HEADERS,
   SYNC_MONITOR,
   ASYNC_MONITOR,
   MAX_TOTAL,
   MAX_PER_ROUTE,
   PROXY,
   OBJECT_MAPPER;
}
} // namespace options
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
