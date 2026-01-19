#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/Shader.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"

namespace zombie {


class ShaderStackEntry :  PooledObject {
:
    Shader m_shader;
    int m_playerIndex;
   private static Pool<ShaderStackEntry> s_pool = new Pool(ShaderStackEntry::new);

    Shader getShader() const {
      return this.m_shader;
   }

    int getPlayerIndex() const {
      return this.m_playerIndex;
   }

    static ShaderStackEntry alloc(Shader var0, int var1) {
    ShaderStackEntry var2 = (ShaderStackEntry)s_pool.alloc();
      var2.m_shader = var0;
      var2.m_playerIndex = var1;
    return var2;
   }
}
} // namespace zombie
