#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

enum class TextureDraw {
   glDraw,
   glBuffer,
   glStencilFunc,
   glAlphaFunc,
   glStencilOp,
   glEnable,
   glDisable,
   glColorMask,
   glStencilMask,
   glClear,
   glBlendFunc,
   glDoStartFrame,
   glDoStartFrameText,
   glDoEndFrame,
   glTexParameteri,
   StartShader,
   glLoadIdentity,
   glGenerateMipMaps,
   glBind,
   glViewport,
   DrawModel,
   DrawSkyBox,
   DrawWater,
   DrawPuddles,
   DrawParticles,
   ShaderUpdate,
   BindActiveTexture,
   glBlendEquation,
   glDoStartFrameFx,
   glDoEndFrameFx,
   glIgnoreStyles,
   glClearColor,
   glBlendFuncSeparate,
   glDepthMask,
   doCoreIntParam,
   drawTerrain;
}
} // namespace textures
} // namespace core
} // namespace zombie
