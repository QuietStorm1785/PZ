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


class TexCoord4f : public Tuple4f {
public:
    static const long serialVersionUID = -3517736544731446513L;

    public TexCoord4f(float var1, float var2, float var3, float var4) {
      super(var1, var2, var3, var4);
   }

    public TexCoord4f(float[] var1) {
      super(var1);
   }

    public TexCoord4f(TexCoord4f var1) {
      super(var1);
   }

    public TexCoord4f(Tuple4f var1) {
      super(var1);
   }

    public TexCoord4f(Tuple4d var1) {
      super(var1);
   }

    public TexCoord4f() {
   }
}
} // namespace vecmath
} // namespace javax
