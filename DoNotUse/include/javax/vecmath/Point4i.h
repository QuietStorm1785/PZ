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


class Point4i : public Tuple4i {
public:
    static const long serialVersionUID = 620124780244617983L;

    public Point4i(int var1, int var2, int var3, int var4) {
      super(var1, var2, var3, var4);
   }

    public Point4i(int[] var1) {
      super(var1);
   }

    public Point4i(Tuple4i var1) {
      super(var1);
   }

    public Point4i() {
   }
}
} // namespace vecmath
} // namespace javax
