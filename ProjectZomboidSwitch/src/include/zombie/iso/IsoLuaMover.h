#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace iso {


class IsoLuaMover : public IsoGameCharacter {
public:
    KahluaTable luaMoverTable;

    public IsoLuaMover(KahluaTable var1) {
      super(nullptr, 0.0F, 0.0F, 0.0F);
      this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      this.luaMoverTable = var1;
      if (this.def == nullptr) {
         this.def = IsoSpriteInstance.get(this.sprite);
      }
   }

    void playAnim(const std::string& var1, float var2, bool var3, bool var4) {
      this.sprite.PlayAnim(var1);
    float var5 = this.sprite.CurrentAnim.Frames.size();
    float var6 = 1000.0F / var5;
    float var7 = var6 * var2;
      this.def.AnimFrameIncrease = var7 * GameTime.getInstance().getMultiplier();
      this.def.Finished = !var4;
      this.def.Looped = var3;
   }

    std::string getObjectName() {
      return "IsoLuaMover";
   }

    void update() {
      try {
         LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this.luaMoverTable.rawget("update"), this.luaMoverTable);
      } catch (Exception var2) {
         var2.printStackTrace();
      }

      this.sprite.update(this.def);
      super.update();
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    float var8 = this.offsetY;
      var8 -= 100.0F;
    float var9 = this.offsetX;
      var9 -= 34.0F;
      this.sprite.render(this.def, this, this.x, this.y, this.z, this.dir, var9, var8, var4, true);

      try {
         LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this.luaMoverTable.rawget("postrender"), this.luaMoverTable, var4, var5);
      } catch (Exception var11) {
         var11.printStackTrace();
      }
   }
}
} // namespace iso
} // namespace zombie
