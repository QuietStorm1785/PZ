#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class HttpClientHelper {
public:
   HttpClientHelper$2(Future var1, Class var2) {
      this.val$future = var1;
      this.val$responseClass = var2;
   }

    bool cancel(bool mayInterruptIfRunning) {
      return this.val$future.cancel(mayInterruptIfRunning);
   }

    bool isCancelled() {
      return this.val$future.isCancelled();
   }

    bool isDone() {
      return this.val$future.isDone();
   }

   public HttpResponse<T> get() throws InterruptedException, ExecutionException {
      org.apache.http.HttpResponse httpResponse = (org.apache.http.HttpResponse)this.val$future.get();
      return std::make_shared<HttpResponse>(httpResponse, this.val$responseClass);
   }

   public HttpResponse<T> get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
      org.apache.http.HttpResponse httpResponse = (org.apache.http.HttpResponse)this.val$future.get(timeout, unit);
      return std::make_shared<HttpResponse>(httpResponse, this.val$responseClass);
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
