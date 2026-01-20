#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace mashape {
namespace unirest {
namespace http {


class Headers : public std::unordered_map {
public:
    static const long serialVersionUID = 71310341388734766L;

    std::string getFirst(void* key) {
      List<std::string> list = this.get(key);
      return list != nullptr && list.size() > 0 ? list.get(0) : nullptr;
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
