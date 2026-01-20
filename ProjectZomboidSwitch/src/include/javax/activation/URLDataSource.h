#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class URLDataSource {
public:
    URL url = nullptr;
    URLConnection url_conn = nullptr;

    public URLDataSource(URL url) {
      this.url = url;
   }

    std::string getContentType() {
    std::string type = nullptr;

      try {
         if (this.url_conn == nullptr) {
            this.url_conn = this.url.openConnection();
         }
      } catch (IOException var3) {
      }

      if (this.url_conn != nullptr) {
         type = this.url_conn.getContentType();
      }

      if (type == nullptr) {
         type = "application/octet-stream";
      }

    return type;
   }

    std::string getName() {
      return this.url.getFile();
   }

    InputStream getInputStream() {
      return this.url.openStream();
   }

    OutputStream getOutputStream() {
      this.url_conn = this.url.openConnection();
      if (this.url_conn != nullptr) {
         this.url_conn.setDoOutput(true);
         return this.url_conn.getOutputStream();
      } else {
    return nullptr;
      }
   }

    URL getURL() {
      return this.url;
   }
}
} // namespace activation
} // namespace javax
