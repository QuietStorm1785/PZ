#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {


class Point3i : public Tuple3i {
public:
    static const long serialVersionUID = 6149289077348153921L;

    public Point3i(int var1, int var2, int var3) {
      super(var1, var2, var3);
   }

    public Point3i(int[] var1) {
      super(var1);
   }

    public Point3i(Tuple3i var1) {
      super(var1);
   }

    public Point3i() {
   }
}
} // namespace vecmath
} // namespace javax
