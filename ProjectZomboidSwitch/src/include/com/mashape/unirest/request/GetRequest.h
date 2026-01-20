#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpMethod.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {


class GetRequest : public HttpRequest {
public:
    public GetRequest(HttpMethod method, const std::string& url) {
      super(method, url);
   }

    GetRequest routeParam(const std::string& name, const std::string& value) {
      super.routeParam(name, value);
    return this;
   }

    GetRequest header(const std::string& name, const std::string& value) {
      return (GetRequest)super.header(name, value);
   }

    GetRequest headers(std::string> headers) {
      return (GetRequest)super.headers(headers);
   }

    GetRequest basicAuth(const std::string& username, const std::string& password) {
      super.basicAuth(username, password);
    return this;
   }
}
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
