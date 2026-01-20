#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoBrokenGlass : public IsoObject {
public:
    public IsoBrokenGlass(IsoCell var1) {
      super(var1);
    int var2 = Rand.Next(4);
      this.sprite = IsoSpriteManager.instance.getSprite("brokenglass_1_" + var2);
   }

    std::string getObjectName() {
      return "IsoBrokenGlass";
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
   }

    void addToWorld() {
      super.addToWorld();
   }

    void removeFromWorld() {
      super.removeFromWorld();
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

    void renderObjectPicker(float var1, float var2, float var3, ColorInfo var4) {
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
