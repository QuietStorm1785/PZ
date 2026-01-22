#pragma once
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpMethod.h"
#include "com/mashape/unirest/http/utils/Base64Coder.h"
#include "com/mashape/unirest/http/utils/URLParamEncoder.h"
#include "com/mashape/unirest/request/body/Body.h"
#include "java/net/URLEncoder.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace request {


class HttpRequest : public BaseRequest {
public:
    HttpMethod httpMethod;
    std::string url;
   Map<std::string, List<std::string>> headers = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
    Body body;

    public HttpRequest(HttpMethod method, const std::string& url) {
      this.httpMethod = method;
      this.url = url;
      super.httpRequest = this;
   }

    HttpRequest routeParam(const std::string& name, const std::string& value) {
    Matcher matcher = Pattern.compile("\\{" + name + "\\}").matcher(this.url);
    int count = 0;

      while (matcher.find()) {
         count++;
      }

      if (count == 0) {
         throw RuntimeException("Can't find route parameter name \"" + name + "\"");
      } else {
         this.url = this.url.replaceAll("\\{" + name + "\\}", URLParamEncoder.encode(value));
    return this;
      }
   }

    HttpRequest basicAuth(const std::string& username, const std::string& password) {
      this.header("Authorization", "Basic " + Base64Coder.encodeString(username + ":" + password));
    return this;
   }

    HttpRequest header(const std::string& name, const std::string& value) {
      List<std::string> list = this.headers.get(name.trim());
      if (list == nullptr) {
         list = std::make_unique<std::vector<>>();
      }

      list.push_back(value);
      this.headers.put(name.trim(), list);
    return this;
   }

    HttpRequest headers(std::string> headers) {
      if (headers != nullptr) {
         for (Entry<std::string, std::string> entry : headers.entrySet()) {
            this.header(entry.getKey(), entry.getValue());
         }
      }

    return this;
   }

    HttpRequest queryString(const std::string& name, Collection<?> value) {
    for (auto& cur : value)         this.queryString(name, cur);
      }

    return this;
   }

    HttpRequest queryString(const std::string& name, void* value) {
    std::stringstream queryString = new std::stringstream();
      if (this.url.contains("?")) {
         queryString.append("&");
      } else {
         queryString.append("?");
      }

      try {
         queryString.append(URLEncoder.encode(name)).append("=").append(URLEncoder.encode(value == nullptr ? "" : value, "UTF-8"));
      } catch (UnsupportedEncodingException var5) {
         throw RuntimeException(var5);
      }

      this.url = this.url + queryString;
    return this;
   }

    HttpRequest queryString(Object> parameters) {
      if (parameters != nullptr) {
         for (Entry<std::string, Object> param : parameters.entrySet()) {
            if (!(param.getValue() instanceof std::string) && !(param.getValue() instanceof Number) && !(param.getValue() instanceof bool)) {
               throw RuntimeException(
                  "Parameter \"" + param.getKey() + "\" can't be sent with a GET request because of type: " + param.getValue().getClass().getName()
               );
            }

            this.queryString(param.getKey(), param.getValue());
         }
      }

    return this;
   }

    HttpMethod getHttpMethod() {
      return this.httpMethod;
   }

    std::string getUrl() {
      return this.url;
   }

   public Map<std::string, List<std::string>> getHeaders() {
      return (Map<std::string, List<std::string>>)(this.headers == nullptr ? std::make_unique<std::unordered_map<>>() : this.headers);
   }

    Body getBody() {
      return this.body;
   }
}
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
