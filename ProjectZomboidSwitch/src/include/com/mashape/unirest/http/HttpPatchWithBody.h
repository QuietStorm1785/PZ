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


class HttpPatchWithBody : public HttpEntityEnclosingRequestBase {
public:
    static const std::string METHOD_NAME = "PATCH";

    std::string getMethod() {
      return "PATCH";
   }

    public HttpPatchWithBody(const std::string& uri) {
      this.setURI(URI.create(uri));
   }

    public HttpPatchWithBody(URI uri) {
      this.setURI(uri);
   }

    public HttpPatchWithBody() {
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
