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


class Color4b : public Tuple4b {
public:
    static const long serialVersionUID = -105080578052502155L;

    public Color4b(uint8_t var1, uint8_t var2, uint8_t var3, uint8_t var4) {
      super(var1, var2, var3, var4);
   }

    public Color4b(byte[] var1) {
      super(var1);
   }

    public Color4b(Color4b var1) {
      super(var1);
   }

    public Color4b(Tuple4b var1) {
      super(var1);
   }

    public Color4b(Color var1) {
      super((byte)var1.getRed(), (byte)var1.getGreen(), (byte)var1.getBlue(), (byte)var1.getAlpha());
   }

    public Color4b() {
   }

    void set(Color var1) {
      this.x = (byte)var1.getRed();
      this.y = (byte)var1.getGreen();
      this.z = (byte)var1.getBlue();
      this.w = (byte)var1.getAlpha();
   }

    Color get() {
    int var1 = this.x & 255;
    int var2 = this.y & 255;
    int var3 = this.z & 255;
    int var4 = this.w & 255;
      return std::make_shared<Color>(var1, var2, var3, var4);
   }
}
} // namespace vecmath
} // namespace javax
