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
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class Base64Data {
public:
   Base64Data$1(Base64Data this$0) {
      this.this$0 = this$0;
   }

    std::string getContentType() {
      return this.this$0.getMimeType();
   }

    InputStream getInputStream() {
      return std::make_shared<ByteArrayInputStream>(Base64Data.access$000(this.this$0), 0, Base64Data.access$100(this.this$0));
   }

    std::string getName() {
    return nullptr;
   }

    OutputStream getOutputStream() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
