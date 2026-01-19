#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoLuaMover : public IsoGameCharacter {
public:
 KahluaTable luaMoverTable;

public
 IsoLuaMover(KahluaTable table) {
 super(nullptr, 0.0F, 0.0F, 0.0F);
 this->sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->luaMoverTable = table;
 if (this->def.empty()) {
 this->def = IsoSpriteInstance.get(this->sprite);
 }
 }

 void playAnim(std::string_view name, float seconds, bool looped,
 bool playing) {
 this->sprite.PlayAnim(name);
 float float0 = this->sprite.CurrentAnim.Frames.size();
 float float1 = 1000.0F / float0;
 float float2 = float1 * seconds;
 this->def.AnimFrameIncrease =
 float2 * GameTime.getInstance().getMultiplier();
 this->def.Finished = !playing;
 this->def.Looped = looped;
 }

 std::string getObjectName() { return "IsoLuaMover"; }

 void update() {
 try {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(),
 this->luaMoverTable.rawget("update"),
 this->luaMoverTable);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 this->sprite.update(this->def);
 super.update();
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoAttached,
 bool bWallLightingPass, Shader shader) {
 float float0 = this->offsetY;
 float0 -= 100.0F;
 float float1 = this->offsetX;
 float1 -= 34.0F;
 this->sprite.render(this->def, this, this->x, this->y, this->z, this->dir, float1,
 float0, col, true);

 try {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(),
 this->luaMoverTable.rawget("postrender"),
 this->luaMoverTable, col, bDoAttached);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}
} // namespace iso
} // namespace zombie
