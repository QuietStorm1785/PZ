#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpMethod.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/ObjectMapper.h"
#include "com/mashape/unirest/http/options/Option.h"
#include "com/mashape/unirest/http/options/Options.h"
#include "com/mashape/unirest/request/body/MultipartBody.h"
#include "com/mashape/unirest/request/body/RawBody.h"
#include "com/mashape/unirest/request/body/RequestBodyEntity.h"
#include "org/apache/http/entity/ContentType.h"
#include "org/apache/http/entity/mime/content/InputStreamBody.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace request {


class HttpRequestWithBody : public HttpRequest {
public:
    public HttpRequestWithBody(HttpMethod method, const std::string& url) {
      super(method, url);
   }

    HttpRequestWithBody routeParam(const std::string& name, const std::string& value) {
      super.routeParam(name, value);
    return this;
   }

    HttpRequestWithBody header(const std::string& name, const std::string& value) {
      return (HttpRequestWithBody)super.header(name, value);
   }

    HttpRequestWithBody headers(std::string> headers) {
      return (HttpRequestWithBody)super.headers(headers);
   }

    HttpRequestWithBody basicAuth(const std::string& username, const std::string& password) {
      super.basicAuth(username, password);
    return this;
   }

    HttpRequestWithBody queryString(Object> parameters) {
      return (HttpRequestWithBody)super.queryString(parameters);
   }

    HttpRequestWithBody queryString(const std::string& name, void* value) {
      return (HttpRequestWithBody)super.queryString(name, value);
   }

    MultipartBody field(const std::string& name, Collection<?> value) {
    MultipartBody body = std::make_shared<MultipartBody>(this).field(name, value);
      this.body = body;
    return body;
   }

    MultipartBody field(const std::string& name, void* value) {
      return this.field(name, value, nullptr);
   }

    MultipartBody field(const std::string& name, File file) {
      return this.field(name, file, nullptr);
   }

    MultipartBody field(const std::string& name, void* value, const std::string& contentType) {
    MultipartBody body = std::make_shared<MultipartBody>(this).field(name, value == nullptr ? "" : value, contentType);
      this.body = body;
    return body;
   }

    MultipartBody field(const std::string& name, File file, const std::string& contentType) {
    MultipartBody body = std::make_shared<MultipartBody>(this).field(name, file, contentType);
      this.body = body;
    return body;
   }

    MultipartBody fields(Object> parameters) {
    MultipartBody body = std::make_shared<MultipartBody>(this);
      if (parameters != nullptr) {
         for (Entry<std::string, Object> param : parameters.entrySet()) {
            if (param.getValue() instanceof File) {
               body.field(param.getKey(), (File)param.getValue());
            } else {
               body.field(param.getKey(), param.getValue() == nullptr ? "" : param.getValue());
            }
         }
      }

      this.body = body;
    return body;
   }

    MultipartBody field(const std::string& name, InputStream stream, ContentType contentType, const std::string& fileName) {
    InputStreamBody inputStreamBody = std::make_shared<InputStreamBody>(stream, contentType, fileName);
    MultipartBody body = std::make_shared<MultipartBody>(this).field(name, inputStreamBody, true, contentType);
      this.body = body;
    return body;
   }

    MultipartBody field(const std::string& name, InputStream stream, const std::string& fileName) {
    MultipartBody body = this.field(name, stream, ContentType.APPLICATION_OCTET_STREAM, fileName);
      this.body = body;
    return body;
   }

    RequestBodyEntity body(JsonNode body) {
      return this.body(body);
   }

    RequestBodyEntity body(const std::string& body) {
    RequestBodyEntity b = std::make_shared<RequestBodyEntity>(this).body(body);
      this.body = b;
    return b;
   }

    RequestBodyEntity body(void* body) {
    ObjectMapper objectMapper = (ObjectMapper)Options.getOption(Option.OBJECT_MAPPER);
      if (objectMapper == nullptr) {
         throw RuntimeException("Serialization Impossible. Can't find an ObjectMapper implementation.");
      } else {
         return this.body(objectMapper.writeValue(body));
      }
   }

    RawBody body(byte[] body) {
    RawBody b = std::make_shared<RawBody>(this).body(body);
      this.body = b;
    return b;
   }

    RequestBodyEntity body(JSONObject body) {
      return this.body(body);
   }

    RequestBodyEntity body(JSONArray body) {
      return this.body(body);
   }
}
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
