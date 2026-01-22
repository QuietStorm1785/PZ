#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/options/Option.h"
#include "com/mashape/unirest/http/options/Options.h"
#include "org/apache/http/client/HttpClient.h"
#include "org/apache/http/impl/nio/client/CloseableHttpAsyncClient.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {


class ClientFactory {
public:
    static HttpClient getHttpClient() {
      return (HttpClient)Options.getOption(Option.HTTPCLIENT);
   }

    static CloseableHttpAsyncClient getAsyncHttpClient() {
      return (CloseableHttpAsyncClient)Options.getOption(Option.ASYNCHTTPCLIENT);
   }
}
} // namespace utils
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
