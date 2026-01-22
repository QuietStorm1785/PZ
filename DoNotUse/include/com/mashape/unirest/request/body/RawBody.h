#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/request/BaseRequest.h"
#include "com/mashape/unirest/request/HttpRequest.h"
#include "org/apache/http/HttpEntity.h"
#include "org/apache/http/entity/ByteArrayEntity.h"

namespace com {
namespace mashape {
namespace unirest {
namespace request {
namespace body {


class RawBody : public BaseRequest {
public:
   private byte[] body;

    public RawBody(HttpRequest httpRequest) {
      super(httpRequest);
   }

    RawBody body(byte[] body) {
      this.body = body;
    return this;
   }

    void* getBody() {
      return this.body;
   }

    HttpEntity getEntity() {
      return std::make_shared<ByteArrayEntity>(this.body);
   }
}
} // namespace body
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
