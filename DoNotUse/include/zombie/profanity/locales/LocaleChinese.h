#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace profanity {
namespace locales {

class LocaleChinese : public Locale {
public:
    public LocaleChinese(const std::string& var1) {
      super(var1);
   }

    void Init() {
   }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
