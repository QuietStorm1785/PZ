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


class Point2i : public Tuple2i {
public:
    static const long serialVersionUID = 9208072376494084954L;

    public Point2i(int var1, int var2) {
      super(var1, var2);
   }

    public Point2i(int[] var1) {
      super(var1);
   }

    public Point2i(Tuple2i var1) {
      super(var1);
   }

    public Point2i() {
   }
}
} // namespace vecmath
} // namespace javax
