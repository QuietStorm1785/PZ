#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class StatusLine {
public:
    const std::string mHttpVersion;
    const int mStatusCode;
    const std::string mReasonPhrase;
    const std::string mString;

   StatusLine(std::string line) {
      std::string[] elements = line.split(" +", 3);
      if (elements.length < 2) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.mHttpVersion = elements[0];
         this.mStatusCode = int.parseInt(elements[1]);
         this.mReasonPhrase = elements.length == 3 ? elements[2] : nullptr;
         this.mString = line;
      }
   }

    std::string getHttpVersion() {
      return this.mHttpVersion;
   }

    int getStatusCode() {
      return this.mStatusCode;
   }

    std::string getReasonPhrase() {
      return this.mReasonPhrase;
   }

    std::string toString() {
      return this.mString;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
