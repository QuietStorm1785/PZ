#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {


class Util {
public:
    private Util() {
   }

    static Logger getClassLogger() {
      try {
         StackTraceElement[] trace = std::make_unique<Exception>().getStackTrace();
         return Logger.getLogger(trace[1].getClassName());
      } catch (SecurityException var1) {
         return Logger.getLogger("com.sun.xml.bind");
      }
   }

    static std::string getSystemProperty(const std::string& name) {
      try {
         return System.getProperty(name);
      } catch (SecurityException var2) {
    return nullptr;
      }
   }
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
