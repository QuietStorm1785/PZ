#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "java/net/URL.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Resources {
public:
    const URL url;

   private Resources$UrlByteSource(URL url) {
      this.url = (URL)Preconditions.checkNotNull(url);
   }

    InputStream openStream() {
      return this.url.openStream();
   }

    std::string toString() {
      return "Resources.asByteSource(" + this.url + ")";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
