#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Color.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {


class Color3f : public Tuple3f {
public:
    static const long serialVersionUID = -1861792981817493659L;

    public Color3f(float var1, float var2, float var3) {
      super(var1, var2, var3);
   }

    public Color3f(float[] var1) {
      super(var1);
   }

    public Color3f(Color3f var1) {
      super(var1);
   }

    public Color3f(Tuple3f var1) {
      super(var1);
   }

    public Color3f(Tuple3d var1) {
      super(var1);
   }

    public Color3f(Color var1) {
      super(var1.getRed() / 255.0F, var1.getGreen() / 255.0F, var1.getBlue() / 255.0F);
   }

    public Color3f() {
   }

    void set(Color var1) {
      this.x = var1.getRed() / 255.0F;
      this.y = var1.getGreen() / 255.0F;
      this.z = var1.getBlue() / 255.0F;
   }

    Color get() {
    int var1 = Math.round(this.x * 255.0F);
    int var2 = Math.round(this.y * 255.0F);
    int var3 = Math.round(this.z * 255.0F);
      return std::make_shared<Color>(var1, var2, var3);
   }
}
} // namespace vecmath
} // namespace javax
