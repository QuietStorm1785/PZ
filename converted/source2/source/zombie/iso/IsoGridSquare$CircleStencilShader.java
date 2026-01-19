package zombie.iso;

import org.lwjgl.opengl.GL20;
import zombie.core.opengl.Shader;
import zombie.core.opengl.ShaderProgram;

public final class IsoGridSquare$CircleStencilShader extends Shader {
   public static final IsoGridSquare$CircleStencilShader instance = new IsoGridSquare$CircleStencilShader();
   public int a_wallShadeColor = -1;

   public IsoGridSquare$CircleStencilShader() {
      super("CircleStencil");
   }

   protected void onCompileSuccess(ShaderProgram var1) {
      this.Start();
      this.a_wallShadeColor = GL20.glGetAttribLocation(this.getID(), "a_wallShadeColor");
      var1.setSamplerUnit("texture", 0);
      var1.setSamplerUnit("CutawayStencil", 1);
      this.End();
   }
}
