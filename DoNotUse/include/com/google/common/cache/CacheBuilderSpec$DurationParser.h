#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/ValueParser.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
   protected abstract void parseDuration(CacheBuilderSpec var1, long var2, TimeUnit var4);

    void parse(CacheBuilderSpec spec, const std::string& key, const std::string& value) {
      Preconditions.checkArgument(value != nullptr && !value.empty(), "value of key %s omitted", key);

      try {
    char lastChar = value.charAt(value.length() - 1);
    TimeUnit timeUnit;
         switch (lastChar) {
            case 'd':
               timeUnit = TimeUnit.DAYS;
               break;
            case 'h':
               timeUnit = TimeUnit.HOURS;
               break;
            case 'm':
               timeUnit = TimeUnit.MINUTES;
               break;
            case 's':
               timeUnit = TimeUnit.SECONDS;
               break;
            default:
               throw IllegalArgumentException(
                  CacheBuilderSpec.access$000("key %s invalid format.  was %s, must end with one of [dDhHmMsS]", new Object[]{key, value})
               );
         }

    long duration = int64_t.parseLong(value.substr(0, value.length() - 1));
         this.parseDuration(spec, duration, timeUnit);
      } catch (NumberFormatException var8) {
         throw IllegalArgumentException(CacheBuilderSpec.access$000("key %s value set to %s, must be integer", new Object[]{key, value}));
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
