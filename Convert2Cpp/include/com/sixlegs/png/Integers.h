#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class Integers {
public:
    static auto INT_0 = std::make_shared<Integer>(0);
    static auto INT_1 = std::make_shared<Integer>(1);
    static auto INT_2 = std::make_shared<Integer>(2);
    static auto INT_3 = std::make_shared<Integer>(3);
    static auto INT_4 = std::make_shared<Integer>(4);
    static auto INT_5 = std::make_shared<Integer>(5);
    static auto INT_6 = std::make_shared<Integer>(6);
    static auto INT_7 = std::make_shared<Integer>(7);
    static auto INT_8 = std::make_shared<Integer>(8);

    static int valueOf(int var0) {
      switch (var0) {
         case 0:
    return INT_0;
         case 1:
    return INT_1;
         case 2:
    return INT_2;
         case 3:
    return INT_3;
         case 4:
    return INT_4;
         case 5:
    return INT_5;
         case 6:
    return INT_6;
         case 7:
    return INT_7;
         case 8:
    return INT_8;
         default:
            return new Integer(var0);
      }
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
