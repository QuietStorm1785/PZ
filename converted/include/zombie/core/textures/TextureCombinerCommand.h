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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 public ArrayList<TextureCombinerShaderParam> shaderParams = nullptr;
 public static ObjectPool<TextureCombinerCommand> pool = new ObjectPool<>(TextureCombinerCommand::new);

 std::string toString() {
 std::string string = System.lineSeparator();
 return "{"
 + string
 + "\tpos: "
 + this->x
 + ","
 + this->y
 + string
 + "\tsize: "
 + this->w
 + ","
 + this->h
 + string
 + "\tmask:"
 + this->mask
 + string
 + "\ttex:"
 + this->tex
 + string
 + "\tblendSrc:"
 + this->blendSrc
 + string
 + "\tblendDest:"
 + this->blendDest
 + string
 + "\tblendSrcA:"
 + this->blendSrcA
 + string
 + "\tblendDestA:"
 + this->blendDestA
 + string
 + "\tshader:"
 + this->shader
 + string
 + "\tshaderParams:"
 + PZArrayUtil.arrayToString(this->shaderParams)
 + string
 + "}";
 }

 TextureCombinerCommand init(Texture texture) {
 this->tex = this->requireNonNull(texture);
 this->blendSrc = 770;
 this->blendDest = 771;
 this->blendSrcA = 1;
 this->blendDestA = 771;
 return this;
 }

 TextureCombinerCommand initSeparate(Texture texture, int int0, int int1, int int2, int int3) {
 this->tex = this->requireNonNull(texture);
 this->blendSrc = int0;
 this->blendDest = int1;
 this->blendSrcA = int2;
 this->blendDestA = int3;
 return this;
 }

 TextureCombinerCommand init(Texture texture, int int0, int int1) {
 return this->initSeparate(texture, int0, int1, 1, 771);
 }

 TextureCombinerCommand init(Texture texture, SmartShader smartShader) {
 this->tex = this->requireNonNull(texture);
 this->shader = smartShader;
 this->blendSrc = 770;
 this->blendDest = 771;
 this->blendSrcA = 1;
 this->blendDestA = 771;
 return this;
 }

 TextureCombinerCommand init(Texture texture0, SmartShader smartShader, Texture texture1, int int0, int int1) {
 this->tex = this->requireNonNull(texture0);
 this->shader = smartShader;
 this->blendSrc = int0;
 this->blendDest = int1;
 this->blendSrcA = 1;
 this->blendDestA = 771;
 this->mask = this->requireNonNull(texture1);
 return this;
 }

 TextureCombinerCommand init(Texture texture, int int0, int int1, int int2, int int3) {
 this->tex = this->requireNonNull(texture);
 this->x = int0;
 this->y = int1;
 this->w = int2;
 this->h = int3;
 this->blendSrc = 770;
 this->blendDest = 771;
 this->blendSrcA = 1;
 this->blendDestA = 771;
 return this;
 }

 public TextureCombinerCommand initSeparate(
 Texture texture0, SmartShader smartShader, ArrayList<TextureCombinerShaderParam> arrayList, Texture texture1, int int0, int int1, int int2, int int3
 ) {
 this->tex = this->requireNonNull(texture0);
 this->shader = smartShader;
 this->blendSrc = int0;
 this->blendDest = int1;
 this->blendSrcA = int2;
 this->blendDestA = int3;
 this->mask = this->requireNonNull(texture1);
 if (this->shaderParams.empty()) {
 this->shaderParams = std::make_unique<ArrayList<>>();
 }

 this->shaderParams.clear();
 this->shaderParams.addAll(arrayList);
 return this;
 }

 public TextureCombinerCommand init(
 Texture texture0, SmartShader smartShader, ArrayList<TextureCombinerShaderParam> arrayList, Texture texture1, int int0, int int1
 ) {
 return this->initSeparate(texture0, smartShader, arrayList, texture1, int0, int1, 1, 771);
 }

 TextureCombinerCommand init(Texture texture, SmartShader smartShader, ArrayList<TextureCombinerShaderParam> arrayList) {
 this->tex = this->requireNonNull(texture);
 this->blendSrc = 770;
 this->blendDest = 771;
 this->blendSrcA = 1;
 this->blendDestA = 771;
 this->shader = smartShader;
 if (this->shaderParams.empty()) {
 this->shaderParams = std::make_unique<ArrayList<>>();
 }

 this->shaderParams.clear();
 this->shaderParams.addAll(arrayList);
 return this;
 }

 Texture requireNonNull(Texture texture) {
 return texture = = nullptr ? Texture.getErrorTexture() : texture;
 }

 static TextureCombinerCommand get() {
 TextureCombinerCommand textureCombinerCommand = pool.alloc();
 textureCombinerCommand.x = -1;
 textureCombinerCommand.tex = nullptr;
 textureCombinerCommand.mask = nullptr;
 textureCombinerCommand.shader = nullptr;
 if (textureCombinerCommand.shaderParams != nullptr) {
 textureCombinerCommand.shaderParams.clear();
 }

 return textureCombinerCommand;
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
