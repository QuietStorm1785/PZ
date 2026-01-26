#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#extern "C" {
#include "lua-5.4.7/lua.h"
#include "lua-5.4.7/lauxlib.h"
#include "lua-5.4.7/lualib.h"
#}
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


// A wrapper for a Lua table reference
class LuaTable {
public:
   lua_State* L;
   int ref;
   LuaTable(lua_State* L_, int ref_) : L(L_), ref(ref_) {}
   ~LuaTable() {
      if (L && ref != LUA_NOREF) luaL_unref(L, LUA_REGISTRYINDEX, ref);
   }
   // Get a field from the table
   void getField(const char* key) const {
      lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
      lua_getfield(L, -1, key);
      lua_remove(L, -2);
   }
};

class IsoLuaMover : public IsoGameCharacter {
public:
   std::shared_ptr<LuaTable> luaMoverTable;
   IsoLuaMover(lua_State* L, int tableRef)
      : IsoGameCharacter(nullptr, 0.0f, 0.0f, 0.0f),
        luaMoverTable(std::make_shared<LuaTable>(L, tableRef)) {
      this->sprite = IsoSprite::CreateSprite(IsoSpriteManager::instance());
      if (!this->def) {
         this->def = IsoSpriteInstance::get(this->sprite);
      }
   }

   void playAnim(const std::string& anim, float speed, bool looped, bool finished) {
      this->sprite->PlayAnim(anim);
      float frames = static_cast<float>(this->sprite->CurrentAnim->Frames.size());
      float frameTime = 1000.0f / frames;
      float animInc = frameTime * speed;
      this->def->AnimFrameIncrease = animInc * GameTime::getInstance()->getMultiplier();
      this->def->Finished = !finished;
      this->def->Looped = looped;
   }

   std::string getObjectName() const override {
      return "IsoLuaMover";
   }

   void update() override {
      if (luaMoverTable && luaMoverTable->L) {
         luaMoverTable->getField("update");
         if (lua_isfunction(luaMoverTable->L, -1)) {
            lua_rawgeti(luaMoverTable->L, LUA_REGISTRYINDEX, luaMoverTable->ref);
            if (lua_pcall(luaMoverTable->L, 1, 0, 0) != LUA_OK) {
               // Handle error
               const char* err = lua_tostring(luaMoverTable->L, -1);
               // Log or print error
               lua_pop(luaMoverTable->L, 1);
            }
         } else {
            lua_pop(luaMoverTable->L, 1);
         }
      }
      this->sprite->update(this->def);
      IsoGameCharacter::update();
   }

   void render(float x, float y, float z, ColorInfo* color, bool b1, bool b2, Shader* shader) override {
      float offY = this->offsetY - 100.0f;
      float offX = this->offsetX - 34.0f;
      this->sprite->render(this->def, this, this->x, this->y, this->z, this->dir, offX, offY, color, true);
      if (luaMoverTable && luaMoverTable->L) {
         luaMoverTable->getField("postrender");
         if (lua_isfunction(luaMoverTable->L, -1)) {
            lua_rawgeti(luaMoverTable->L, LUA_REGISTRYINDEX, luaMoverTable->ref);
            // Push color as a Lua table {r,g,b,a}
            lua_newtable(luaMoverTable->L);
            if (color) {
               lua_pushstring(luaMoverTable->L, "r");
               lua_pushnumber(luaMoverTable->L, color->r);
               lua_settable(luaMoverTable->L, -3);
               lua_pushstring(luaMoverTable->L, "g");
               lua_pushnumber(luaMoverTable->L, color->g);
               lua_settable(luaMoverTable->L, -3);
               lua_pushstring(luaMoverTable->L, "b");
               lua_pushnumber(luaMoverTable->L, color->b);
               lua_settable(luaMoverTable->L, -3);
               lua_pushstring(luaMoverTable->L, "a");
               lua_pushnumber(luaMoverTable->L, color->a);
               lua_settable(luaMoverTable->L, -3);
            }
            // Push b1 as a boolean
            lua_pushboolean(luaMoverTable->L, b1);
            // Call: postrender(self, color, b1)
            if (lua_pcall(luaMoverTable->L, 3, 0, 0) != LUA_OK) {
               const char* err = lua_tostring(luaMoverTable->L, -1);
               // Log or print error
               lua_pop(luaMoverTable->L, 1);
            }
         } else {
            lua_pop(luaMoverTable->L, 1);
         }
      }
   }
};
} // namespace iso
} // namespace zombie
