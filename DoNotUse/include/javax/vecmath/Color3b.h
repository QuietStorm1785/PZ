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


class Color3b : public Tuple3b {
public:
    static const long serialVersionUID = 6632576088353444794L;

    public Color3b(uint8_t var1, uint8_t var2, uint8_t var3) {
      super(var1, var2, var3);
   }

    public Color3b(byte[] var1) {
      super(var1);
   }

    public Color3b(Color3b var1) {
      super(var1);
   }

    public Color3b(Tuple3b var1) {
      super(var1);
   }

    public Color3b(Color var1) {
      super((byte)var1.getRed(), (byte)var1.getGreen(), (byte)var1.getBlue());
   }

    public Color3b() {
   }

    void set(Color var1) {
      this.x = (byte)var1.getRed();
      this.y = (byte)var1.getGreen();
      this.z = (byte)var1.getBlue();
   }

    Color get() {
    int var1 = this.x & 255;
    int var2 = this.y & 255;
    int var3 = this.z & 255;
      return std::make_shared<Color>(var1, var2, var3);
   }
}
} // namespace vecmath
} // namespace javax
