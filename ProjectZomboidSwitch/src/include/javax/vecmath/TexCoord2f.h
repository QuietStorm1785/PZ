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


class TexCoord2f : public Tuple2f {
public:
    static const long serialVersionUID = 7998248474800032487L;

    public TexCoord2f(float var1, float var2) {
      super(var1, var2);
   }

    public TexCoord2f(float[] var1) {
      super(var1);
   }

    public TexCoord2f(TexCoord2f var1) {
      super(var1);
   }

    public TexCoord2f(Tuple2f var1) {
      super(var1);
   }

    public TexCoord2f() {
   }
}
} // namespace vecmath
} // namespace javax
