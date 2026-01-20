#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/options/Option.h"
#include "com/mashape/unirest/http/options/Options.h"
#include "com/mashape/unirest/http/utils/ResponseUtils.h"
#include "org/apache/http/Header.h"
#include "org/apache/http/HttpEntity.h"
#include "org/apache/http/StatusLine.h"
#include "org/apache/http/util/EntityUtils.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class HttpResponse {
public:
    int statusCode;
    std::string statusText;
    Headers headers = std::make_shared<Headers>();
    InputStream rawBody;
    T body;

    public HttpResponse(org.apache.http.HttpResponse response, Class<T> responseClass) {
    HttpEntity responseEntity = response.getEntity();
    ObjectMapper objectMapper = (ObjectMapper)Options.getOption(Option.OBJECT_MAPPER);
      Header[] allHeaders = response.getAllHeaders();

    for (auto& header : allHeaders)    std::string headerName = header.getName();
         List<std::string> list = (List<std::string>)this.headers.get(headerName);
         if (list == nullptr) {
            list = std::make_unique<std::vector<>>();
         }

         list.push_back(header.getValue());
         this.headers.put(headerName, list);
      }

    StatusLine statusLine = response.getStatusLine();
      this.statusCode = statusLine.getStatusCode();
      this.statusText = statusLine.getReasonPhrase();
      if (responseEntity != nullptr) {
    std::string charset = "UTF-8";
    Header contentType = responseEntity.getContentType();
         if (contentType != nullptr) {
    std::string responseCharset = ResponseUtils.getCharsetFromContentType(contentType.getValue());
            if (responseCharset != nullptr && !responseCharset.trim() == "")) {
               charset = responseCharset;
            }
         }

         try {
            byte[] rawBody;
            try {
    InputStream responseInputStream = responseEntity.getContent();
               if (ResponseUtils.isGzipped(responseEntity.getContentEncoding())) {
                  responseInputStream = std::make_shared<GZIPInputStream>(responseEntity.getContent());
               }

               rawBody = ResponseUtils.getBytes(responseInputStream);
            } catch (IOException var12) {
               throw RuntimeException(var12);
            }

            this.rawBody = std::make_shared<ByteArrayInputStream>(rawBody);
            if (JsonNode.class == responseClass)) {
    std::string jsonString = new std::string(rawBody, charset).trim();
               this.body = (T)(std::make_shared<JsonNode>(jsonString));
            } else if (std::string.class == responseClass)) {
               this.body = (T)(new std::string(rawBody, charset));
            } else if (InputStream.class == responseClass)) {
               this.body = (T)this.rawBody;
            } else {
               if (objectMapper == nullptr) {
                  throw Exception("Only std::string, JsonNode and InputStream are supported, or an ObjectMapper implementation is required.");
               }

               this.body = (T)objectMapper.readValue(new std::string(rawBody, charset), responseClass);
            }
         } catch (Exception var13) {
            throw RuntimeException(var13);
         }
      }

      EntityUtils.consumeQuietly(responseEntity);
   }

    int getStatus() {
      return this.statusCode;
   }

    std::string getStatusText() {
      return this.statusText;
   }

    Headers getHeaders() {
      return this.headers;
   }

    InputStream getRawBody() {
      return this.rawBody;
   }

    T getBody() {
      return this.body;
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
