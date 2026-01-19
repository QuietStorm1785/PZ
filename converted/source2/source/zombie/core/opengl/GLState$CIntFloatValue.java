package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;
import zombie.util.Type;

public final class GLState$CIntFloatValue implements Value {
   int a;
   float b;

   public GLState$CIntFloatValue set(int var1, float var2) {
      this.a = var1;
      this.b = var2;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      GLState$CIntFloatValue var2 = (GLState$CIntFloatValue)Type.tryCastTo(var1, GLState$CIntFloatValue.class);
      return var2 != null && var2.a == this.a && var2.b == this.b;
   }

   public Value set(Value var1) {
      GLState$CIntFloatValue var2 = (GLState$CIntFloatValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      return this;
   }
}
