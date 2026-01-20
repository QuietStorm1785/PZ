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


class TexCoord3f : public Tuple3f {
public:
    static const long serialVersionUID = -3517736544731446513L;

    public TexCoord3f(float var1, float var2, float var3) {
      super(var1, var2, var3);
   }

    public TexCoord3f(float[] var1) {
      super(var1);
   }

    public TexCoord3f(TexCoord3f var1) {
      super(var1);
   }

    public TexCoord3f(Tuple3f var1) {
      super(var1);
   }

    public TexCoord3f(Tuple3d var1) {
      super(var1);
   }

    public TexCoord3f() {
   }
}
} // namespace vecmath
} // namespace javax
