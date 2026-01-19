package zombie.iso;

import org.lwjgl.opengl.GL20;
import zombie.core.opengl.ShaderProgram;

public final class IsoGridSquare$NoCircleStencilShader {
   public static final IsoGridSquare$NoCircleStencilShader instance = new IsoGridSquare$NoCircleStencilShader();
   private ShaderProgram shaderProgram;
   public int ShaderID = -1;
   public int a_wallShadeColor = -1;

   private void initShader() {
      this.shaderProgram = ShaderProgram.createShaderProgram("NoCircleStencil", false, true);
      if (this.shaderProgram.isCompiled()) {
         this.ShaderID = this.shaderProgram.getShaderID();
         this.a_wallShadeColor = GL20.glGetAttribLocation(this.ShaderID, "a_wallShadeColor");
      }
   }
}
