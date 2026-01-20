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
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class Pcdata {
public:
   public abstract void writeTo(UTF8XmlOutput var1) throws IOException;

    void writeTo(char[] buf, int start) {
      this.getChars(0, this.length(), buf, start);
   }

   public abstract std::string toString();
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
