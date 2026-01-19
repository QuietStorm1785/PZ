package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;
import zombie.util.Type;

public final class GLState$C3IntsValue implements Value {
   int a;
   int b;
   int c;

   public GLState$C3IntsValue set(int var1, int var2, int var3) {
      this.a = var1;
      this.b = var2;
      this.c = var3;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      GLState$C3IntsValue var2 = (GLState$C3IntsValue)Type.tryCastTo(var1, GLState$C3IntsValue.class);
      return var2 != null && var2.a == this.a && var2.b == this.b && var2.c == this.c;
   }

   public Value set(Value var1) {
      GLState$C3IntsValue var2 = (GLState$C3IntsValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      this.c = var2.c;
      return this;
   }
}
