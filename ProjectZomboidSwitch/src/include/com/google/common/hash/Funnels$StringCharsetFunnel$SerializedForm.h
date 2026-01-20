#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Funnels {
public:
    const std::string charsetCanonicalName;
    static const long serialVersionUID = 0L;

   Funnels$StringCharsetFunnel$SerializedForm(Charset charset) {
      this.charsetCanonicalName = charset.name();
   }

    void* readResolve() {
      return Funnels.stringFunnel(Charset.forName(this.charsetCanonicalName));
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
