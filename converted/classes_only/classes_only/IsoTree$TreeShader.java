package zombie.iso.objects;

import org.lwjgl.opengl.ARBShaderObjects;
import zombie.IndieGL;
import zombie.core.SpriteRenderer;
import zombie.core.opengl.RenderThread;
import zombie.core.opengl.ShaderProgram;

public class IsoTree$TreeShader {
   public static final IsoTree$TreeShader instance = new IsoTree$TreeShader();
   private ShaderProgram shaderProgram;
   private int stepSize;
   private int outlineColor;

   public void initShader() {
      this.shaderProgram = ShaderProgram.createShaderProgram("tree", false, true);
      if (this.shaderProgram.isCompiled()) {
         this.stepSize = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "stepSize");
         this.outlineColor = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "outlineColor");
         ARBShaderObjects.glUseProgramObjectARB(this.shaderProgram.getShaderID());
         ARBShaderObjects.glUniform2fARB(this.stepSize, 0.001F, 0.001F);
         ARBShaderObjects.glUseProgramObjectARB(0);
      }
   }

   public void setOutlineColor(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.outlineColor, var1, var2, var3, var4);
   }

   public void setStepSize(float var1, int var2, int var3) {
      SpriteRenderer.instance.ShaderUpdate2f(this.shaderProgram.getShaderID(), this.stepSize, var1 / var2, var1 / var3);
   }

   public boolean StartShader() {
      if (this.shaderProgram == null) {
         RenderThread.invokeOnRenderContext(this::initShader);
      }

      if (this.shaderProgram.isCompiled()) {
         IndieGL.StartShader(this.shaderProgram.getShaderID(), 0);
         return true;
      } else {
         return false;
      }
   }
}
