package zombie.core.opengl;

import zombie.core.opengl.GLState.CAlphaFunc;
import zombie.core.opengl.GLState.CAlphaTest;
import zombie.core.opengl.GLState.CBlendFunc;
import zombie.core.opengl.GLState.CBlendFuncSeparate;
import zombie.core.opengl.GLState.CColorMask;
import zombie.core.opengl.GLState.CStencilFunc;
import zombie.core.opengl.GLState.CStencilMask;
import zombie.core.opengl.GLState.CStencilOp;
import zombie.core.opengl.GLState.CStencilTest;

public final class GLState {
   public static final CAlphaFunc AlphaFunc = new CAlphaFunc();
   public static final CAlphaTest AlphaTest = new CAlphaTest();
   public static final CBlendFunc BlendFunc = new CBlendFunc();
   public static final CBlendFuncSeparate BlendFuncSeparate = new CBlendFuncSeparate();
   public static final CColorMask ColorMask = new CColorMask();
   public static final CStencilFunc StencilFunc = new CStencilFunc();
   public static final CStencilMask StencilMask = new CStencilMask();
   public static final CStencilOp StencilOp = new CStencilOp();
   public static final CStencilTest StencilTest = new CStencilTest();

   public static void startFrame() {
      AlphaFunc.setDirty();
      AlphaTest.setDirty();
      BlendFunc.setDirty();
      BlendFuncSeparate.setDirty();
      ColorMask.setDirty();
      StencilFunc.setDirty();
      StencilMask.setDirty();
      StencilOp.setDirty();
      StencilTest.setDirty();
   }
}
