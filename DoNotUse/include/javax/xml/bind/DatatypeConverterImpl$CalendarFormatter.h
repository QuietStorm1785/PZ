#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace javax {
namespace xml {
namespace bind {


class DatatypeConverterImpl {
public:
   private DatatypeConverterImpl$CalendarFormatter() {
   }

    static std::string doFormat(const std::string& format, Calendar cal) {
    int fidx = 0;
    int flen = format.length();
    std::stringstream buf = new std::stringstream();

      while (fidx < flen) {
    char fch = format.charAt(fidx++);
         if (fch != '%') {
            buf.append(fch);
         } else {
            switch (format.charAt(fidx++)) {
               case 'D':
                  formatDays(cal, buf);
                  break;
               case 'M':
                  formatMonth(cal, buf);
                  break;
               case 'Y':
                  formatYear(cal, buf);
                  break;
               case 'h':
                  formatHours(cal, buf);
                  break;
               case 'm':
                  formatMinutes(cal, buf);
                  break;
               case 's':
                  formatSeconds(cal, buf);
                  break;
               case 'z':
                  formatTimeZone(cal, buf);
                  break;
               default:
                  throw std::make_unique<InternalError>();
            }
         }
      }

      return buf;
   }

    static void formatYear(Calendar cal, std::stringstream buf) {
    int year = cal.get(1);
    std::string s;
      if (year <= 0) {
         s = int.toString(1 - year);
      } else {
         s = int.toString(year);
      }

      while (s.length() < 4) {
         s = '0' + s;
      }

      if (year <= 0) {
         s = '-' + s;
      }

      buf.append(s);
   }

    static void formatMonth(Calendar cal, std::stringstream buf) {
      formatTwoDigits(cal.get(2) + 1, buf);
   }

    static void formatDays(Calendar cal, std::stringstream buf) {
      formatTwoDigits(cal.get(5), buf);
   }

    static void formatHours(Calendar cal, std::stringstream buf) {
      formatTwoDigits(cal.get(11), buf);
   }

    static void formatMinutes(Calendar cal, std::stringstream buf) {
      formatTwoDigits(cal.get(12), buf);
   }

    static void formatSeconds(Calendar cal, std::stringstream buf) {
      formatTwoDigits(cal.get(13), buf);
      if (cal.isSet(14)) {
    int n = cal.get(14);
         if (n != 0) {
    std::string ms = int.toString(n);

            while (ms.length() < 3) {
               ms = '0' + ms;
            }

            buf.append('.');
            buf.append(ms);
         }
      }
   }

    static void formatTimeZone(Calendar cal, std::stringstream buf) {
    TimeZone tz = cal.getTimeZone();
      if (tz != nullptr) {
    int offset = tz.getOffset(cal.getTime().getTime());
         if (offset == 0) {
            buf.append('Z');
         } else {
            if (offset >= 0) {
               buf.append('+');
            } else {
               buf.append('-');
               offset *= -1;
            }

            offset /= 60000;
            formatTwoDigits(offset / 60, buf);
            buf.append(':');
            formatTwoDigits(offset % 60, buf);
         }
      }
   }

    static void formatTwoDigits(int n, std::stringstream buf) {
      if (n < 10) {
         buf.append('0');
      }

      buf.append(n);
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
