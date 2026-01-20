#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/async/Callback.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"
#include "org/apache/http/HttpResponse.h"
#include "org/apache/http/concurrent/FutureCallback.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class HttpClientHelper {
public:
   HttpClientHelper$1(Callback var1, Class var2) {
      this.val$callback = var1;
      this.val$responseClass = var2;
   }

    void cancelled() {
      this.val$callback.cancelled();
   }

    void completed(HttpResponse arg0) {
      this.val$callback.completed(new com.mashape.unirest.http.HttpResponse(arg0, this.val$responseClass));
   }

    void failed(std::exception arg0) {
      this.val$callback.failed(std::make_shared<UnirestException>(arg0));
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
