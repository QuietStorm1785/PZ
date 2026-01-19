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
:
    static const int INT_0 = new Integer(0);
    static const int INT_1 = new Integer(1);
    static const int INT_2 = new Integer(2);
    static const int INT_3 = new Integer(3);
    static const int INT_4 = new Integer(4);
    static const int INT_5 = new Integer(5);
    static const int INT_6 = new Integer(6);
    static const int INT_7 = new Integer(7);
    static const int INT_8 = new Integer(8);

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
