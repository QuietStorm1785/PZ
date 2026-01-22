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

class Bean {
public:
    bool f_boolean;
    char f_char;
    uint8_t f_byte;
    short f_short;
    int f_int;
    long f_long;
    float f_float;
    double f_double;
    Ref f_ref;

    bool get_boolean() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_boolean(bool b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char get_char() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_char(char b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t get_byte() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_byte(uint8_t b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short get_short() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_short(short b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int get_int() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_int(int b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long get_long() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_long(long b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float get_float() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_float(float b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double get_double() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_double(double b) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Ref get_ref() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void set_ref(Ref r) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace opt
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
