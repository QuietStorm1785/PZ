#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/request/BaseRequest.h"
#include "com/mashape/unirest/request/HttpRequest.h"
#include "org/apache/http/HttpEntity.h"
#include "org/apache/http/entity/StringEntity.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {
namespace body {


class RequestBodyEntity : public BaseRequest {
public:
    void* body;

    public RequestBodyEntity(HttpRequest httpRequest) {
      super(httpRequest);
   }

    RequestBodyEntity body(const std::string& body) {
      this.body = body;
    return this;
   }

    RequestBodyEntity body(JsonNode body) {
      this.body = body;
    return this;
   }

    void* getBody() {
      return this.body;
   }

    HttpEntity getEntity() {
      return std::make_shared<StringEntity>(this.body, "UTF-8");
   }
}
} // namespace body
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
