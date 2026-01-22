#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/activation/DataSource.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace istack {


class ByteArrayDataSource {
public:
    const std::string contentType;
   private const byte[] buf;
    const int len;

    public ByteArrayDataSource(byte[] buf, const std::string& contentType) {
      this(buf, buf.length, contentType);
   }

    public ByteArrayDataSource(byte[] buf, int length, const std::string& contentType) {
      this.buf = buf;
      this.len = length;
      this.contentType = contentType;
   }

    std::string getContentType() {
      return this.contentType == nullptr ? "application/octet-stream" : this.contentType;
   }

    InputStream getInputStream() {
      return std::make_shared<ByteArrayInputStream>(this.buf, 0, this.len);
   }

    std::string getName() {
    return nullptr;
   }

    OutputStream getOutputStream() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace istack
} // namespace sun
} // namespace com
