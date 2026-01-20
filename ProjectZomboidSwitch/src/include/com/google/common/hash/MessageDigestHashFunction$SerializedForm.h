#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class MessageDigestHashFunction {
public:
    const std::string algorithmName;
    const int bytes;
    const std::string toString;
    static const long serialVersionUID = 0L;

   private MessageDigestHashFunction$SerializedForm(std::string algorithmName, int bytes, std::string toString) {
      this.algorithmName = algorithmName;
      this.bytes = bytes;
      this.toString = toString;
   }

    void* readResolve() {
      return std::make_shared<MessageDigestHashFunction>(this.algorithmName, this.bytes, this.toString);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
