#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/apache/http/Header.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {


class ResponseUtils {
public:
    static const Pattern charsetPattern = Pattern.compile("(?i)\\bcharset=\\s*\"?([^\\s;

    static std::string getCharsetFromContentType(const std::string& contentType) {
      if (contentType == nullptr) {
    return nullptr;
      } else {
    Matcher m = charsetPattern.matcher(contentType);
         return m.find() ? m.group(1).trim().toUpperCase() : nullptr;
      }
   }

   public static byte[] getBytes(InputStream is) throws IOException {
    int size = 1024;
      byte[] buf;
      if (dynamic_cast<ByteArrayInputStream*>(is) != nullptr) {
         size = is.available();
         buf = new byte[size];
    int len = is.read(buf, 0, size);
      } else {
    ByteArrayOutputStream bos = std::make_shared<ByteArrayOutputStream>();
         buf = new byte[size];

    int len;
         while ((len = is.read(buf, 0, size)) != -1) {
            bos.write(buf, 0, len);
         }

         buf = bos.toByteArray();
      }

    return buf;
   }

    static bool isGzipped(Header contentEncoding) {
      if (contentEncoding != nullptr) {
    std::string value = contentEncoding.getValue();
         if (value != nullptr && "gzip" == value.toLowerCase().trim())) {
    return true;
         }
      }

    return false;
   }
}
} // namespace utils
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
