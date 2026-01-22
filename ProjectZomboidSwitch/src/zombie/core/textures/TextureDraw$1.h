#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer/WallShaderTexRender.h"
#include "zombie/core/textures/TextureDraw/Type.h"

namespace zombie {
namespace core {
namespace textures {


// $VF: synthetic class
class TextureDraw {
public:
   static {
      try {
         $SwitchMap$zombie$core$SpriteRenderer$WallShaderTexRender[WallShaderTexRender.LeftOnly.ordinal()] = 1;
      } catch (NoSuchFieldError var38) {
      }

      try {
         $SwitchMap$zombie$core$SpriteRenderer$WallShaderTexRender[WallShaderTexRender.RightOnly.ordinal()] = 2;
      } catch (NoSuchFieldError var37) {
      }

      try {
         $SwitchMap$zombie$core$SpriteRenderer$WallShaderTexRender[WallShaderTexRender.All.ordinal()] = 3;
      } catch (NoSuchFieldError var36) {
      }

      $SwitchMap$zombie$core$textures$TextureDraw$Type = new int[Type.values().length];

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.StartShader.ordinal()] = 1;
      } catch (NoSuchFieldError var35) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.ShaderUpdate.ordinal()] = 2;
      } catch (NoSuchFieldError var34) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.BindActiveTexture.ordinal()] = 3;
      } catch (NoSuchFieldError var33) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.DrawModel.ordinal()] = 4;
      } catch (NoSuchFieldError var32) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.DrawSkyBox.ordinal()] = 5;
      } catch (NoSuchFieldError var31) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.DrawWater.ordinal()] = 6;
      } catch (NoSuchFieldError var30) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.DrawPuddles.ordinal()] = 7;
      } catch (NoSuchFieldError var29) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.DrawParticles.ordinal()] = 8;
      } catch (NoSuchFieldError var28) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glClear.ordinal()] = 9;
      } catch (NoSuchFieldError var27) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glClearColor.ordinal()] = 10;
      } catch (NoSuchFieldError var26) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glBlendFunc.ordinal()] = 11;
      } catch (NoSuchFieldError var25) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glBlendFuncSeparate.ordinal()] = 12;
      } catch (NoSuchFieldError var24) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glColorMask.ordinal()] = 13;
      } catch (NoSuchFieldError var23) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glTexParameteri.ordinal()] = 14;
      } catch (NoSuchFieldError var22) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glStencilMask.ordinal()] = 15;
      } catch (NoSuchFieldError var21) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDoEndFrame.ordinal()] = 16;
      } catch (NoSuchFieldError var20) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDoEndFrameFx.ordinal()] = 17;
      } catch (NoSuchFieldError var19) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDoStartFrame.ordinal()] = 18;
      } catch (NoSuchFieldError var18) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDoStartFrameText.ordinal()] = 19;
      } catch (NoSuchFieldError var17) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDoStartFrameFx.ordinal()] = 20;
      } catch (NoSuchFieldError var16) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glStencilFunc.ordinal()] = 21;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glBuffer.ordinal()] = 22;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glStencilOp.ordinal()] = 23;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glLoadIdentity.ordinal()] = 24;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glBind.ordinal()] = 25;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glViewport.ordinal()] = 26;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.drawTerrain.ordinal()] = 27;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.doCoreIntParam.ordinal()] = 28;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDepthMask.ordinal()] = 29;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glGenerateMipMaps.ordinal()] = 30;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glAlphaFunc.ordinal()] = 31;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glEnable.ordinal()] = 32;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glDisable.ordinal()] = 33;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glBlendEquation.ordinal()] = 34;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$textures$TextureDraw$Type[Type.glIgnoreStyles.ordinal()] = 35;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
