#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/utils/MapUtil.h"
#include "com/mashape/unirest/request/BaseRequest.h"
#include "com/mashape/unirest/request/HttpRequest.h"
#include "org/apache/http/HttpEntity.h"
#include "org/apache/http/client/entity/UrlEncodedFormEntity.h"
#include "org/apache/http/entity/ContentType.h"
#include "org/apache/http/entity/mime/HttpMultipartMode.h"
#include "org/apache/http/entity/mime/MultipartEntityBuilder.h"
#include "org/apache/http/entity/mime/content/ByteArrayBody.h"
#include "org/apache/http/entity/mime/content/ContentBody.h"
#include "org/apache/http/entity/mime/content/FileBody.h"
#include "org/apache/http/entity/mime/content/InputStreamBody.h"
#include "org/apache/http/entity/mime/content/StringBody.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace request {
namespace body {


class MultipartBody : public BaseRequest {
public:
   private Map<std::string, List<Object>> parameters = std::make_unique<LinkedHashMap<>>();
   private Map<std::string, ContentType> contentTypes = std::make_unique<std::unordered_map<>>();
    bool hasFile;
    HttpRequest httpRequestObj;
    HttpMultipartMode mode;

    public MultipartBody(HttpRequest httpRequest) {
      super(httpRequest);
      this.httpRequestObj = httpRequest;
   }

    MultipartBody field(const std::string& name, const std::string& value) {
      return this.field(name, value, false, nullptr);
   }

    MultipartBody field(const std::string& name, const std::string& value, const std::string& contentType) {
      return this.field(name, value, false, contentType);
   }

    MultipartBody field(const std::string& name, Collection<?> collection) {
    for (auto& current : collection)    bool isFile = dynamic_cast<File*>(current) != nullptr;
         this.field(name, current, isFile, nullptr);
      }

    return this;
   }

    MultipartBody field(const std::string& name, void* value) {
      return this.field(name, value, false, nullptr);
   }

    MultipartBody field(const std::string& name, void* value, bool file) {
      return this.field(name, value, file, nullptr);
   }

    MultipartBody field(const std::string& name, void* value, bool file, const std::string& contentType) {
      List<Object> list = this.parameters.get(name);
      if (list == nullptr) {
         list = std::make_unique<std::list<>>();
      }

      list.push_back(value);
      this.parameters.put(name, list);
    ContentType type = nullptr;
      if (contentType != nullptr && contentType.length() > 0) {
         type = ContentType.parse(contentType);
      } else if (file) {
         type = ContentType.APPLICATION_OCTET_STREAM;
      } else {
         type = ContentType.APPLICATION_FORM_URLENCODED.withCharset("UTF-8");
      }

      this.contentTypes.put(name, type);
      if (!this.hasFile && file) {
         this.hasFile = true;
      }

    return this;
   }

    MultipartBody field(const std::string& name, File file) {
      return this.field(name, file, true, nullptr);
   }

    MultipartBody field(const std::string& name, File file, const std::string& contentType) {
      return this.field(name, file, true, contentType);
   }

    MultipartBody field(const std::string& name, InputStream stream, ContentType contentType, const std::string& fileName) {
      return this.field(name, std::make_shared<InputStreamBody>(stream, contentType, fileName), true, contentType.getMimeType());
   }

    MultipartBody field(const std::string& name, InputStream stream, const std::string& fileName) {
      return this.field(
         name, std::make_shared<InputStreamBody>(stream, ContentType.APPLICATION_OCTET_STREAM, fileName), true, ContentType.APPLICATION_OCTET_STREAM.getMimeType()
      );
   }

    MultipartBody field(const std::string& name, byte[] bytes, ContentType contentType, const std::string& fileName) {
      return this.field(name, std::make_shared<ByteArrayBody>(bytes, contentType, fileName), true, contentType.getMimeType());
   }

    MultipartBody field(const std::string& name, byte[] bytes, const std::string& fileName) {
      return this.field(
         name, std::make_shared<ByteArrayBody>(bytes, ContentType.APPLICATION_OCTET_STREAM, fileName), true, ContentType.APPLICATION_OCTET_STREAM.getMimeType()
      );
   }

    MultipartBody basicAuth(const std::string& username, const std::string& password) {
      this.httpRequestObj.basicAuth(username, password);
    return this;
   }

    MultipartBody mode(const std::string& mode) {
      this.mode = HttpMultipartMode.valueOf(mode);
    return this;
   }

    HttpEntity getEntity() {
      if (!this.hasFile) {
         try {
            return std::make_shared<UrlEncodedFormEntity>(MapUtil.getList(this.parameters), "UTF-8");
         } catch (UnsupportedEncodingException var9) {
            throw RuntimeException(var9);
         }
      } else {
    MultipartEntityBuilder builder = MultipartEntityBuilder.create();
         if (this.mode != nullptr) {
            builder.setMode(HttpMultipartMode.BROWSER_COMPATIBLE);
         }

         for (std::string key : this.parameters.keySet()) {
            List<Object> value = this.parameters.get(key);
    ContentType contentType = this.contentTypes.get(key);

    for (auto& cur : value)               if (dynamic_cast<File*>(cur) != nullptr) {
    File file = (File)cur;
                  builder.addPart(key, std::make_shared<FileBody>(file, contentType, file.getName()));
               } else if (dynamic_cast<InputStreamBody*>(cur) != nullptr) {
                  builder.addPart(key, (ContentBody)cur);
               } else if (dynamic_cast<ByteArrayBody*>(cur) != nullptr) {
                  builder.addPart(key, (ContentBody)cur);
               } else {
                  builder.addPart(key, std::make_shared<StringBody>(cur, contentType));
               }
            }
         }

         return builder.build();
      }
   }
}
} // namespace body
} // namespace request
} // namespace unirest
} // namespace mashape
} // namespace com
