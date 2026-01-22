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
namespace marshaller {


class NoEscapeHandler {
public:
    static const NoEscapeHandler theInstance = std::make_shared<NoEscapeHandler>();

    void escape(char[] ch, int start, int length, bool isAttVal, Writer out) {
      out.write(ch, start, length);
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
