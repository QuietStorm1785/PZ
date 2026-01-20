#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace impl {

class Constants {
public:
    static const bool VERBOSE = System.getProperty("gnu.trove.verbose", nullptr) != nullptr;
    static const int DEFAULT_CAPACITY = 10;
    static const float DEFAULT_LOAD_FACTOR = 0.5F;
    static const uint8_t DEFAULT_BYTE_NO_ENTRY_VALUE;
    static const short DEFAULT_SHORT_NO_ENTRY_VALUE;
    static const char DEFAULT_CHAR_NO_ENTRY_VALUE;
    static const int DEFAULT_INT_NO_ENTRY_VALUE;
    static const long DEFAULT_LONG_NO_ENTRY_VALUE;
    static const float DEFAULT_FLOAT_NO_ENTRY_VALUE;
    static const double DEFAULT_DOUBLE_NO_ENTRY_VALUE;

   static {
    std::string property = System.getProperty("gnu.trove.no_entry.byte", "0");
    uint8_t value;
      if ("MAX_VALUE".equalsIgnoreCase(property)) {
         value = (byte)127;
      } else if ("MIN_VALUE".equalsIgnoreCase(property)) {
         value = (byte)-128;
      } else {
         value = uint8_t.valueOf(property);
      }

      if (value > 127) {
         value = (byte)127;
      } else if (value < -128) {
         value = (byte)-128;
      }

      DEFAULT_BYTE_NO_ENTRY_VALUE = value;
      if (VERBOSE) {
         System.out.println("DEFAULT_BYTE_NO_ENTRY_VALUE: " + DEFAULT_BYTE_NO_ENTRY_VALUE);
      }

      property = System.getProperty("gnu.trove.no_entry.short", "0");
      if ("MAX_VALUE".equalsIgnoreCase(property)) {
         value = (byte)32767;
      } else if ("MIN_VALUE".equalsIgnoreCase(property)) {
         value = (byte)-32768;
      } else {
         value = (byte)int16_t.valueOf(property);
      }

      if (value > 32767) {
         value = (byte)32767;
      } else if (value < -32768) {
         value = (byte)-32768;
      }

      DEFAULT_SHORT_NO_ENTRY_VALUE = value;
      if (VERBOSE) {
         System.out.println("DEFAULT_SHORT_NO_ENTRY_VALUE: " + DEFAULT_SHORT_NO_ENTRY_VALUE);
      }

      property = System.getProperty("gnu.trove.no_entry.char", "\u0000");
    char valuex;
      if ("MAX_VALUE".equalsIgnoreCase(property)) {
         valuex = '\uffff';
      } else if ("MIN_VALUE".equalsIgnoreCase(property)) {
         valuex = 0;
      } else {
         valuex = property.toCharArray()[0];
      }

      if (valuex > '\uffff') {
         valuex = '\uffff';
      } else if (valuex < 0) {
         valuex = 0;
      }

      DEFAULT_CHAR_NO_ENTRY_VALUE = valuex;
      if (VERBOSE) {
         System.out.println("DEFAULT_CHAR_NO_ENTRY_VALUE: " + int.valueOf(valuex));
      }

      property = System.getProperty("gnu.trove.no_entry.int", "0");
      if ("MAX_VALUE".equalsIgnoreCase(property)) {
         value = (byte)int.MAX_VALUE;
      } else if ("MIN_VALUE".equalsIgnoreCase(property)) {
         value = (byte)int.MIN_VALUE;
      } else {
         value = (byte)int.valueOf(property);
      }

      DEFAULT_INT_NO_ENTRY_VALUE = value;
      if (VERBOSE) {
         System.out.println("DEFAULT_INT_NO_ENTRY_VALUE: " + DEFAULT_INT_NO_ENTRY_VALUE);
      }

    std::string propertyx = System.getProperty("gnu.trove.no_entry.long", "0");
    long valuexx;
      if ("MAX_VALUE".equalsIgnoreCase(propertyx)) {
         valuexx = int64_t.MAX_VALUE;
      } else if ("MIN_VALUE".equalsIgnoreCase(propertyx)) {
         valuexx = int64_t.MIN_VALUE;
      } else {
         valuexx = int64_t.valueOf(propertyx);
      }

      DEFAULT_LONG_NO_ENTRY_VALUE = valuexx;
      if (VERBOSE) {
         System.out.println("DEFAULT_LONG_NO_ENTRY_VALUE: " + DEFAULT_LONG_NO_ENTRY_VALUE);
      }

      property = System.getProperty("gnu.trove.no_entry.float", "0");
    float valuexxx;
      if ("MAX_VALUE".equalsIgnoreCase(property)) {
         valuexxx = float.MAX_VALUE;
      } else if ("MIN_VALUE".equalsIgnoreCase(property)) {
         valuexxx = float.MIN_VALUE;
      } else if ("MIN_NORMAL".equalsIgnoreCase(property)) {
         valuexxx = float.MIN_NORMAL;
      } else if ("NEGATIVE_INFINITY".equalsIgnoreCase(property)) {
         valuexxx = float.NEGATIVE_INFINITY;
      } else if ("POSITIVE_INFINITY".equalsIgnoreCase(property)) {
         valuexxx = float.POSITIVE_INFINITY;
      } else {
         valuexxx = float.valueOf(property);
      }

      DEFAULT_FLOAT_NO_ENTRY_VALUE = valuexxx;
      if (VERBOSE) {
         System.out.println("DEFAULT_FLOAT_NO_ENTRY_VALUE: " + DEFAULT_FLOAT_NO_ENTRY_VALUE);
      }

      propertyx = System.getProperty("gnu.trove.no_entry.double", "0");
    double valuexxxx;
      if ("MAX_VALUE".equalsIgnoreCase(propertyx)) {
         valuexxxx = double.MAX_VALUE;
      } else if ("MIN_VALUE".equalsIgnoreCase(propertyx)) {
         valuexxxx = double.MIN_VALUE;
      } else if ("MIN_NORMAL".equalsIgnoreCase(propertyx)) {
         valuexxxx = double.MIN_NORMAL;
      } else if ("NEGATIVE_INFINITY".equalsIgnoreCase(propertyx)) {
         valuexxxx = double.NEGATIVE_INFINITY;
      } else if ("POSITIVE_INFINITY".equalsIgnoreCase(propertyx)) {
         valuexxxx = double.POSITIVE_INFINITY;
      } else {
         valuexxxx = double.valueOf(propertyx);
      }

      DEFAULT_DOUBLE_NO_ENTRY_VALUE = valuexxxx;
      if (VERBOSE) {
         System.out.println("DEFAULT_DOUBLE_NO_ENTRY_VALUE: " + DEFAULT_DOUBLE_NO_ENTRY_VALUE);
      }
   }
}
} // namespace impl
} // namespace trove
} // namespace gnu
