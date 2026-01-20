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

class ObjectMapper {
public:
    virtual ~ObjectMapper() = default;
   <T> T readValue(std::string var1, Class<T> var2);

    std::string writeValue(void* var1);
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
