#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/activation/DataHandler.h"
#include "javax/activation/DataSource.h"
#include "javax/activation/MimeType.h"
#include "javax/activation/MimeTypeParseException.h"
#include "javax/xml/transform/stream/StreamSource.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class DataSourceSource : public StreamSource {
public:
    const DataSource source;
    const std::string charset;
    Reader r;
    InputStream is;

    public DataSourceSource(DataHandler dh) {
      this(dh.getDataSource());
   }

    public DataSourceSource(DataSource source) {
      this.source = source;
    std::string ct = source.getContentType();
      if (ct == nullptr) {
         this.charset = nullptr;
      } else {
    MimeType mimeType = std::make_shared<MimeType>(ct);
         this.charset = mimeType.getParameter("charset");
      }
   }

    void setReader(Reader reader) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setInputStream(InputStream inputStream) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Reader getReader() {
      try {
         if (this.charset == nullptr) {
    return nullptr;
         } else {
            if (this.r == nullptr) {
               this.r = std::make_shared<InputStreamReader>(this.source.getInputStream(), this.charset);
            }

            return this.r;
         }
      } catch (IOException var2) {
         throw RuntimeException(var2);
      }
   }

    InputStream getInputStream() {
      try {
         if (this.charset != nullptr) {
    return nullptr;
         } else {
            if (this.is == nullptr) {
               this.is = this.source.getInputStream();
            }

            return this.is;
         }
      } catch (IOException var2) {
         throw RuntimeException(var2);
      }
   }

    DataSource getDataSource() {
      return this.source;
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
