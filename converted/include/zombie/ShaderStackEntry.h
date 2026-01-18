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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ShaderStackEntry : public PooledObject {
public:
 Shader m_shader;
 int m_playerIndex;
 private static Pool<ShaderStackEntry> s_pool = new Pool<>(ShaderStackEntry::new);

 Shader getShader() {
 return this->m_shader;
 }

 int getPlayerIndex() {
 return this->m_playerIndex;
 }

 static ShaderStackEntry alloc(Shader shader, int int0) {
 ShaderStackEntry shaderStackEntry = s_pool.alloc();
 shaderStackEntry.m_shader = shader;
 shaderStackEntry.m_playerIndex = int0;
 return shaderStackEntry;
 }
}
} // namespace zombie
