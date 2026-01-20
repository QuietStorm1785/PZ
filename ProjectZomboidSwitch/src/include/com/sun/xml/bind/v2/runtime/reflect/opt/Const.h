#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {
namespace opt {

class Const {
public:
    static const uint8_t default_value_byte = 0;
    static const bool default_value_boolean = false;
    static const char default_value_char = '\u0000';
    static const float default_value_float = 0.0F;
    static const double default_value_double = 0.0;
    static const int default_value_int = 0;
    static const long default_value_long = 0L;
    static const short default_value_short = 0;
}
} // namespace opt
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
