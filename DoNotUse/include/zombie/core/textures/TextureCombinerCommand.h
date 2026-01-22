#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/opengl/SmartShader.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace textures {


class TextureCombinerCommand {
public:
    static const int DEFAULT_SRC_A = 1;
    static const int DEFAULT_DST_A = 771;
    int x = -1;
    int y = -1;
    int w = -1;
    int h = -1;
    Texture mask;
    Texture tex;
    int blendSrc;
    int blendDest;
    int blendSrcA;
    int blendDestA;
    SmartShader shader;
   public std::vector<TextureCombinerShaderParam> shaderParams = nullptr;
   public static const ObjectPool<TextureCombinerCommand> pool = std::make_shared<ObjectPool>(TextureCombinerCommand::new);

    std::string toString() {
    std::string var1 = System.lineSeparator();
      return "{"
         + var1
         + "\tpos: "
         + this.x
         + ","
         + this.y
         + var1
         + "\tsize: "
         + this.w
         + ","
         + this.h
         + var1
         + "\tmask:"
         + this.mask
         + var1
         + "\ttex:"
         + this.tex
         + var1
         + "\tblendSrc:"
         + this.blendSrc
         + var1
         + "\tblendDest:"
         + this.blendDest
         + var1
         + "\tblendSrcA:"
         + this.blendSrcA
         + var1
         + "\tblendDestA:"
         + this.blendDestA
         + var1
         + "\tshader:"
         + this.shader
         + var1
         + "\tshaderParams:"
         + PZArrayUtil.arrayToString(this.shaderParams)
         + var1
         + "}";
   }

    TextureCombinerCommand init(Texture var1) {
      this.tex = this.requireNonNull(var1);
      this.blendSrc = 770;
      this.blendDest = 771;
      this.blendSrcA = 1;
      this.blendDestA = 771;
    return this;
   }

    TextureCombinerCommand initSeparate(Texture var1, int var2, int var3, int var4, int var5) {
      this.tex = this.requireNonNull(var1);
      this.blendSrc = var2;
      this.blendDest = var3;
      this.blendSrcA = var4;
      this.blendDestA = var5;
    return this;
   }

    TextureCombinerCommand init(Texture var1, int var2, int var3) {
      return this.initSeparate(var1, var2, var3, 1, 771);
   }

    TextureCombinerCommand init(Texture var1, SmartShader var2) {
      this.tex = this.requireNonNull(var1);
      this.shader = var2;
      this.blendSrc = 770;
      this.blendDest = 771;
      this.blendSrcA = 1;
      this.blendDestA = 771;
    return this;
   }

    TextureCombinerCommand init(Texture var1, SmartShader var2, Texture var3, int var4, int var5) {
      this.tex = this.requireNonNull(var1);
      this.shader = var2;
      this.blendSrc = var4;
      this.blendDest = var5;
      this.blendSrcA = 1;
      this.blendDestA = 771;
      this.mask = this.requireNonNull(var3);
    return this;
   }

    TextureCombinerCommand init(Texture var1, int var2, int var3, int var4, int var5) {
      this.tex = this.requireNonNull(var1);
      this.x = var2;
      this.y = var3;
      this.w = var4;
      this.h = var5;
      this.blendSrc = 770;
      this.blendDest = 771;
      this.blendSrcA = 1;
      this.blendDestA = 771;
    return this;
   }

   public TextureCombinerCommand initSeparate(
      Texture var1, SmartShader var2, std::vector<TextureCombinerShaderParam> var3, Texture var4, int var5, int var6, int var7, int var8
   ) {
      this.tex = this.requireNonNull(var1);
      this.shader = var2;
      this.blendSrc = var5;
      this.blendDest = var6;
      this.blendSrcA = var7;
      this.blendDestA = var8;
      this.mask = this.requireNonNull(var4);
      if (this.shaderParams == nullptr) {
         this.shaderParams = std::make_unique<std::vector<>>();
      }

      this.shaderParams.clear();
      this.shaderParams.addAll(var3);
    return this;
   }

    TextureCombinerCommand init(Texture var1, SmartShader var2, std::vector<TextureCombinerShaderParam> var3, Texture var4, int var5, int var6) {
      return this.initSeparate(var1, var2, var3, var4, var5, var6, 1, 771);
   }

    TextureCombinerCommand init(Texture var1, SmartShader var2, std::vector<TextureCombinerShaderParam> var3) {
      this.tex = this.requireNonNull(var1);
      this.blendSrc = 770;
      this.blendDest = 771;
      this.blendSrcA = 1;
      this.blendDestA = 771;
      this.shader = var2;
      if (this.shaderParams == nullptr) {
         this.shaderParams = std::make_unique<std::vector<>>();
      }

      this.shaderParams.clear();
      this.shaderParams.addAll(var3);
    return this;
   }

    Texture requireNonNull(Texture var1) {
    return var1 = = nullptr ? Texture.getErrorTexture() : var1;
   }

    static TextureCombinerCommand get() {
    TextureCombinerCommand var0 = (TextureCombinerCommand)pool.alloc();
      var0.x = -1;
      var0.tex = nullptr;
      var0.mask = nullptr;
      var0.shader = nullptr;
      if (var0.shaderParams != nullptr) {
         var0.shaderParams.clear();
      }

    return var0;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
