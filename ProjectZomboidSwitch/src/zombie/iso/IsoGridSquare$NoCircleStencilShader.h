#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL20.h"
#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace iso {


class IsoGridSquare {
public:
   public static const IsoGridSquare$NoCircleStencilShader instance = new IsoGridSquare$NoCircleStencilShader();
    ShaderProgram shaderProgram;
    int ShaderID = -1;
    int a_wallShadeColor = -1;

    void initShader() {
      this.shaderProgram = ShaderProgram.createShaderProgram("NoCircleStencil", false, true);
      if (this.shaderProgram.isCompiled()) {
         this.ShaderID = this.shaderProgram.getShaderID();
         this.a_wallShadeColor = GL20.glGetAttribLocation(this.ShaderID, "a_wallShadeColor");
      }
   }
}
} // namespace iso
} // namespace zombie
