#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "org/apache/http/client/methods/HttpEntityEnclosingRequestBase.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class HttpDeleteWithBody : public HttpEntityEnclosingRequestBase {
public:
    static const std::string METHOD_NAME = "DELETE";

    std::string getMethod() {
      return "DELETE";
   }

    public HttpDeleteWithBody(const std::string& uri) {
      this.setURI(URI.create(uri));
   }

    public HttpDeleteWithBody(URI uri) {
      this.setURI(uri);
   }

    public HttpDeleteWithBody() {
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
