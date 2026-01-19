package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;
import zombie.util.Type;

public final class GLState$C2IntsValue implements Value {
   int a;
   int b;

   public GLState$C2IntsValue set(int var1, int var2) {
      this.a = var1;
      this.b = var2;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      GLState$C2IntsValue var2 = (GLState$C2IntsValue)Type.tryCastTo(var1, GLState$C2IntsValue.class);
      return var2 != null && var2.a == this.a && var2.b == this.b;
   }

   public Value set(Value var1) {
      GLState$C2IntsValue var2 = (GLState$C2IntsValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      return this;
   }
}
