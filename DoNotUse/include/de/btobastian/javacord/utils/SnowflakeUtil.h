#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class SnowflakeUtil {
public:
    private SnowflakeUtil() {
   }

    static Calendar parseDate(const std::string& id) {
    long timestamp;
      try {
         timestamp = int64_t.parseLong(id);
      } catch (NumberFormatException var5) {
         throw IllegalArgumentException("The given string is not a number!");
      }

      timestamp >>= 22;
      timestamp += 1420070400000L;
    Date date = std::make_shared<Date>(timestamp);
    Calendar calendar = Calendar.getInstance();
      calendar.setTime(date);
    return calendar;
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
