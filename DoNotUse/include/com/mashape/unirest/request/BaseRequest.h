#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpClientHelper.h"
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/async/Callback.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace request {


class BaseRequest {
public:
    static const std::string UTF_8 = "UTF-8";
    HttpRequest httpRequest;

    protected BaseRequest(HttpRequest httpRequest) {
      this.httpRequest = httpRequest;
   }

    HttpRequest getHttpRequest() {
      return this.httpRequest;
   }

    protected BaseRequest() {
   }

   public HttpResponse<std::string> asString() throws UnirestException {
      return HttpClientHelper.request(this.httpRequest, std::string.class);
   }

   public Future<HttpResponse<std::string>> asStringAsync() {
      return HttpClientHelper.requestAsync(this.httpRequest, std::string.class, nullptr);
   }

   public Future<HttpResponse<std::string>> asStringAsync(Callback<std::string> callback) {
      return HttpClientHelper.requestAsync(this.httpRequest, std::string.class, callback);
   }

   public HttpResponse<JsonNode> asJson() throws UnirestException {
      return HttpClientHelper.request(this.httpRequest, JsonNode.class);
   }

   public Future<HttpResponse<JsonNode>> asJsonAsync() {
      return HttpClientHelper.requestAsync(this.httpRequest, JsonNode.class, nullptr);
   }

   public Future<HttpResponse<JsonNode>> asJsonAsync(Callback<JsonNode> callback) {
      return HttpClientHelper.requestAsync(this.httpRequest, JsonNode.class, callback);
   }

   public <T> HttpResponse<T> asObject(Class<? : public T> responseClass) throws UnirestException {
      return HttpClientHelper.request(this.httpRequest, responseClass);
   }

   public <T> Future<HttpResponse<T>> asObjectAsync(Class<? : public T> responseClass) {
      return HttpClientHelper.requestAsync(this.httpRequest, responseClass, nullptr);
   }

   public <T> Future<HttpResponse<T>> asObjectAsync(Class<? : public T> responseClass, Callback<T> callback) {
      return HttpClientHelper.requestAsync(this.httpRequest, responseClass, callback);
   }

   public HttpResponse<InputStream> asBinary() throws UnirestException {
      return HttpClientHelper.request(this.httpRequest, InputStream.class);
   }

   public Future<HttpResponse<InputStream>> asBinaryAsync() {
      return HttpClientHelper.requestAsync(this.httpRequest, InputStream.class, nullptr);
   }

   public Future<HttpResponse<InputStream>> asBinaryAsync(Callback<InputStream> callback) {
      return HttpClientHelper.requestAsync(this.httpRequest, InputStream.class, callback);
   }
}
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
