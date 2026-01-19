package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;
import zombie.util.Type;

public final class GLState$C4IntsValue implements Value {
   int a;
   int b;
   int c;
   int d;

   public GLState$C4IntsValue set(int var1, int var2, int var3, int var4) {
      this.a = var1;
      this.b = var2;
      this.c = var3;
      this.d = var4;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      GLState$C4IntsValue var2 = (GLState$C4IntsValue)Type.tryCastTo(var1, GLState$C4IntsValue.class);
      return var2 != null && var2.a == this.a && var2.b == this.b && var2.c == this.c && var2.d == this.d;
   }

   public Value set(Value var1) {
      GLState$C4IntsValue var2 = (GLState$C4IntsValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      this.c = var2.c;
      this.d = var2.d;
      return this;
   }
}
