#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/Vector4.h"
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/GLState/C2IntsValue.h"
#include "zombie/core/opengl/GLState/C3IntsValue.h"
#include "zombie/core/opengl/GLState/C4BooleansValue.h"
#include "zombie/core/opengl/GLState/C4IntsValue.h"
#include "zombie/core/opengl/GLState/CBooleanValue.h"
#include "zombie/core/opengl/GLState/CIntFloatValue.h"
#include "zombie/core/opengl/GLState/CIntValue.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/opengl/ShaderProgram/Uniform.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/lambda/Invokers/Params1/ICallback.h"
#include <algorithm>

namespace zombie {


class IndieGL {
:
    static int nCount = 0;
    static const CIntValue tempInt = new CIntValue();
    static const C2IntsValue temp2Ints = new C2IntsValue();
    static const C3IntsValue temp3Ints = new C3IntsValue();
    static const C4IntsValue temp4Ints = new C4IntsValue();
    static const C4BooleansValue temp4Booleans = new C4BooleansValue();
    static const CIntFloatValue tempIntFloat = new CIntFloatValue();
   private static Stack<ShaderStackEntry> m_shaderStack = std::make_unique<Stack<>>();

    static void glBlendFunc(int var0, int var1) {
      if (SpriteRenderer.instance != nullptr && SpriteRenderer.GL_BLENDFUNC_ENABLED) {
         GLState.BlendFuncSeparate.set(temp4Ints.set(var0, var1, var0, var1));
      }
   }

    static void glBlendFuncSeparate(int var0, int var1, int var2, int var3) {
      if (SpriteRenderer.instance != nullptr && SpriteRenderer.GL_BLENDFUNC_ENABLED) {
         GLState.BlendFuncSeparate.set(temp4Ints.set(var0, var1, var2, var3));
      }
   }

    static void StartShader(Shader var0) {
    int var1 = IsoCamera.frameState.playerIndex;
      StartShader(var0, var1);
   }

    static void StartShader(Shader var0, int var1) {
      if (var0 != nullptr) {
         StartShader(var0.getID(), var1);
      } else {
         EndShader();
      }
   }

    static void StartShader(int var0) {
    int var1 = IsoCamera.frameState.playerIndex;
      StartShader(var0, var1);
   }

    static void StartShader(int var0, int var1) {
      SpriteRenderer.instance.StartShader(var0, var1);
   }

    static void EndShader() {
      SpriteRenderer.instance.EndShader();
   }

    static void pushShader(Shader var0) {
    int var1 = IsoCamera.frameState.playerIndex;
      m_shaderStack.push(ShaderStackEntry.alloc(var0, var1));
      StartShader(var0, var1);
   }

    static void popShader(Shader var0) {
      if (m_shaderStack.isEmpty()) {
         throw RuntimeException("Push/PopShader mismatch. Cannot pop. Stack is empty.");
      } else if (m_shaderStack.peek().getShader() != var0) {
         throw RuntimeException("Push/PopShader mismatch. The popped shader != the pushed shader.");
      } else {
    ShaderStackEntry var1 = m_shaderStack.pop();
         var1.release();
         if (m_shaderStack.isEmpty()) {
            EndShader();
         } else {
    ShaderStackEntry var2 = m_shaderStack.peek();
            StartShader(var2.getShader(), var2.getPlayerIndex());
         }
      }
   }

    static void bindShader(Shader var0, Runnable var1) {
      pushShader(var0);

      try {
         var1.run();
      } finally {
         popShader(var0);
      }
   }

    static <T1> void bindShader(Shader var0, T1 var1, ICallback<T1> var2) {
      Lambda.capture(var0, var1, var2, (var0x, var1x, var2x, var3) -> bindShader(var1x, var0x.invoker(var2x, var3)));
   }

    static <T1, T2> void bindShader(Shader var0, T1 var1, T2 var2, zombie.util.lambda.Invokers.Params2.ICallback<T1, T2> var3) {
      Lambda.capture(var0, var1, var2, var3, (var0x, var1x, var2x, var3x, var4) -> bindShader(var1x, var0x.invoker(var2x, var3x, var4)));
   }

    static <T1, T2, T3> void bindShader(Shader var0, T1 var1, T2 var2, T3 var3, zombie.util.lambda.Invokers.Params3.ICallback<T1, T2, T3> var4) {
      Lambda.capture(var0, var1, var2, var3, var4, (var0x, var1x, var2x, var3x, var4x, var5) -> bindShader(var1x, var0x.invoker(var2x, var3x, var4x, var5)));
   }

    static <T1, T2, T3, T4> void bindShader(
      Shader var0, T1 var1, T2 var2, T3 var3, T4 var4, zombie.util.lambda.Invokers.Params4.ICallback<T1, T2, T3, T4> var5
   ) {
      Lambda.capture(
         var0,
         var1,
         var2,
         var3,
         var4,
         var5,
         (var0x, var1x, var2x, var3x, var4x, var5x, var6) -> bindShader(var1x, var0x.invoker(var2x, var3x, var4x, var5x, var6))
      );
   }

    static Uniform getShaderUniform(Shader var0, const std::string& var1, int var2) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    ShaderProgram var3 = var0.getProgram();
    return var3 = = nullptr ? nullptr : var3.getUniform(var1, var2, false);
      }
   }

    static void shaderSetSamplerUnit(Shader var0, const std::string& var1, int var2) {
    Uniform var3 = getShaderUniform(var0, var1, 35678);
      if (var3 != nullptr) {
         var3.sampler = var2;
         ShaderUpdate1i(var0.getID(), var3.loc, var2);
      }
   }

    static void shaderSetValue(Shader var0, const std::string& var1, float var2) {
    Uniform var3 = getShaderUniform(var0, var1, 5126);
      if (var3 != nullptr) {
         ShaderUpdate1f(var0.getID(), var3.loc, var2);
      }
   }

    static void shaderSetValue(Shader var0, const std::string& var1, int var2) {
    Uniform var3 = getShaderUniform(var0, var1, 5124);
      if (var3 != nullptr) {
         ShaderUpdate1i(var0.getID(), var3.loc, var2);
      }
   }

    static void shaderSetValue(Shader var0, const std::string& var1, Vector2 var2) {
      shaderSetVector2(var0, var1, var2.x, var2.y);
   }

    static void shaderSetValue(Shader var0, const std::string& var1, Vector3 var2) {
      shaderSetVector3(var0, var1, var2.x, var2.y, var2.z);
   }

    static void shaderSetValue(Shader var0, const std::string& var1, Vector4 var2) {
      shaderSetVector4(var0, var1, var2.x, var2.y, var2.z, var2.w);
   }

    static void shaderSetVector2(Shader var0, const std::string& var1, float var2, float var3) {
    Uniform var4 = getShaderUniform(var0, var1, 35664);
      if (var4 != nullptr) {
         ShaderUpdate2f(var0.getID(), var4.loc, var2, var3);
      }
   }

    static void shaderSetVector3(Shader var0, const std::string& var1, float var2, float var3, float var4) {
    Uniform var5 = getShaderUniform(var0, var1, 35665);
      if (var5 != nullptr) {
         ShaderUpdate3f(var0.getID(), var5.loc, var2, var3, var4);
      }
   }

    static void shaderSetVector4(Shader var0, const std::string& var1, float var2, float var3, float var4, float var5) {
    Uniform var6 = getShaderUniform(var0, var1, 35666);
      if (var6 != nullptr) {
         ShaderUpdate4f(var0.getID(), var6.loc, var2, var3, var4, var5);
      }
   }

    static void ShaderUpdate1i(int var0, int var1, int var2) {
      SpriteRenderer.instance.ShaderUpdate1i(var0, var1, var2);
   }

    static void ShaderUpdate1f(int var0, int var1, float var2) {
      SpriteRenderer.instance.ShaderUpdate1f(var0, var1, var2);
   }

    static void ShaderUpdate2f(int var0, int var1, float var2, float var3) {
      SpriteRenderer.instance.ShaderUpdate2f(var0, var1, var2, var3);
   }

    static void ShaderUpdate3f(int var0, int var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate3f(var0, var1, var2, var3, var4);
   }

    static void ShaderUpdate4f(int var0, int var1, float var2, float var3, float var4, float var5) {
      SpriteRenderer.instance.ShaderUpdate4f(var0, var1, var2, var3, var4, var5);
   }

    static void glBlendFuncA(int var0, int var1) {
      GL11.glBlendFunc(var0, var1);
   }

    static void glEnable(int var0) {
      SpriteRenderer.instance.glEnable(var0);
   }

    static void glDoStartFrame(int var0, int var1, float var2, int var3) {
      glDoStartFrame(var0, var1, var2, var3, false);
   }

    static void glDoStartFrame(int var0, int var1, float var2, int var3, bool var4) {
      SpriteRenderer.instance.glDoStartFrame(var0, var1, var2, var3, var4);
   }

    static void glDoEndFrame() {
      SpriteRenderer.instance.glDoEndFrame();
   }

    static void glColorMask(bool var0, bool var1, bool var2, bool var3) {
      GLState.ColorMask.set(temp4Booleans.set(var0, var1, var2, var3));
   }

    static void glColorMaskA(bool var0, bool var1, bool var2, bool var3) {
      GL11.glColorMask(var0, var0, var3, var3);
   }

    static void glEnableA(int var0) {
      GL11.glEnable(var0);
   }

    static void glAlphaFunc(int var0, float var1) {
      GLState.AlphaFunc.set(tempIntFloat.set(var0, var1));
   }

    static void glAlphaFuncA(int var0, float var1) {
      GL11.glAlphaFunc(var0, var1);
   }

    static void glStencilFunc(int var0, int var1, int var2) {
      GLState.StencilFunc.set(temp3Ints.set(var0, var1, var2));
   }

    static void glStencilFuncA(int var0, int var1, int var2) {
      GL11.glStencilFunc(var0, var1, var2);
   }

    static void glStencilOp(int var0, int var1, int var2) {
      GLState.StencilOp.set(temp3Ints.set(var0, var1, var2));
   }

    static void glStencilOpA(int var0, int var1, int var2) {
      GL11.glStencilOp(var0, var1, var2);
   }

    static void glTexParameteri(int var0, int var1, int var2) {
      SpriteRenderer.instance.glTexParameteri(var0, var1, var2);
   }

    static void glTexParameteriActual(int var0, int var1, int var2) {
      GL11.glTexParameteri(var0, var1, var2);
   }

    static void glStencilMask(int var0) {
      GLState.StencilMask.set(tempInt.set(var0));
   }

    static void glStencilMaskA(int var0) {
      GL11.glStencilMask(var0);
   }

    static void glDisable(int var0) {
      SpriteRenderer.instance.glDisable(var0);
   }

    static void glClear(int var0) {
      SpriteRenderer.instance.glClear(var0);
   }

    static void glClearA(int var0) {
      GL11.glClear(var0);
   }

    static void glDisableA(int var0) {
      GL11.glDisable(var0);
   }

    static void glLoadIdentity() {
      SpriteRenderer.instance.glLoadIdentity();
   }

    static void glBind(Texture var0) {
      SpriteRenderer.instance.glBind(var0.getID());
   }

    static void enableAlphaTest() {
      GLState.AlphaTest.set(CBooleanValue.TRUE);
   }

    static void disableAlphaTest() {
      GLState.AlphaTest.set(CBooleanValue.FALSE);
   }

    static void enableStencilTest() {
      GLState.StencilTest.set(CBooleanValue.TRUE);
   }

    static void disableStencilTest() {
      GLState.StencilTest.set(CBooleanValue.FALSE);
   }

    static bool isMaxZoomLevel() {
      return SpriteRenderer.instance.isMaxZoomLevel();
   }

    static bool isMinZoomLevel() {
      return SpriteRenderer.instance.isMinZoomLevel();
   }
}
} // namespace zombie
