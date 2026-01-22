#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL20.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace iso {


class IsoGridSquare {
public:
   public static const IsoGridSquare$CircleStencilShader instance = new IsoGridSquare$CircleStencilShader();
    int a_wallShadeColor = -1;

   public IsoGridSquare$CircleStencilShader() {
      super("CircleStencil");
   }

    void onCompileSuccess(ShaderProgram var1) {
      this.Start();
      this.a_wallShadeColor = GL20.glGetAttribLocation(this.getID(), "a_wallShadeColor");
      var1.setSamplerUnit("texture", 0);
      var1.setSamplerUnit("CutawayStencil", 1);
      this.End();
   }
}
} // namespace iso
} // namespace zombie
