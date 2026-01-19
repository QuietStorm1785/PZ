package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;
import zombie.util.Type;

public final class GLState$C4BooleansValue implements Value {
   boolean a;
   boolean b;
   boolean c;
   boolean d;

   public GLState$C4BooleansValue set(boolean var1, boolean var2, boolean var3, boolean var4) {
      this.a = var1;
      this.b = var2;
      this.c = var3;
      this.d = var4;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      GLState$C4BooleansValue var2 = (GLState$C4BooleansValue)Type.tryCastTo(var1, GLState$C4BooleansValue.class);
      return var2 != null && var2.a == this.a && var2.b == this.b && var2.c == this.c;
   }

   public Value set(Value var1) {
      GLState$C4BooleansValue var2 = (GLState$C4BooleansValue)var1;
      this.a = var2.a;
      this.b = var2.b;
      this.c = var2.c;
      this.d = var2.d;
      return this;
   }
}
