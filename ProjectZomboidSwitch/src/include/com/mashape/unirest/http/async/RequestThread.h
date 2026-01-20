#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpClientHelper.h"
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"
#include "com/mashape/unirest/request/HttpRequest.h"

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace async {


class RequestThread {
public:
    HttpRequest httpRequest;
   private Class<T> responseClass;
   private Callback<T> callback;

    public RequestThread(HttpRequest httpRequest, Class<T> responseClass, Callback<T> callback) {
      this.httpRequest = httpRequest;
      this.responseClass = responseClass;
      this.callback = callback;
   }

    void run() {
      try {
         HttpResponse<T> response = HttpClientHelper.request(this.httpRequest, this.responseClass);
         if (this.callback != nullptr) {
            this.callback.completed(response);
         }
      } catch (UnirestException var3) {
         this.callback.failed(var3);
      }
   }
}
} // namespace async
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
