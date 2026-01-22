#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoZombieHead/1.h"
#include "zombie/iso/objects/IsoZombieHead/GibletType.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoZombieHead : public IsoMovingObject {
public:
    float tintb = 1.0F;
    float tintg = 1.0F;
    float tintr = 1.0F;
    float time = 0.0F;

    public IsoZombieHead(IsoCell var1) {
      super(var1);
   }

    bool Serialize() {
    return false;
   }

    std::string getObjectName() {
      return "ZombieHead";
   }

    void update() {
      super.update();
      this.time = this.time + GameTime.instance.getMultipliedSecondsSinceLastUpdate();
      this.sx = this.sy = 0.0F;
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      this.setTargetAlpha(1.0F);
      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    public IsoZombieHead(GibletType var1, IsoCell var2, float var3, float var4, float var5) {
      super(var2);
      this.solid = false;
      this.shootable = false;
      this.x = var3;
      this.y = var4;
      this.z = var5;
      this.nx = var3;
      this.ny = var4;
      this.setAlpha(0.5F);
      this.def = IsoSpriteInstance.get(this.sprite);
      this.def.alpha = 1.0F;
      this.sprite.def.alpha = 1.0F;
      this.offsetX = -26.0F;
      this.offsetY = -242.0F;
      switch (1.$SwitchMap$zombie$iso$objects$IsoZombieHead$GibletType[var1.ordinal()]) {
         case 1:
            this.sprite.LoadFramesNoDirPageDirect("media/gibs/Giblet", "00", 3);
            break;
         case 2:
            this.sprite.LoadFramesNoDirPageDirect("media/gibs/Giblet", "01", 3);
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
