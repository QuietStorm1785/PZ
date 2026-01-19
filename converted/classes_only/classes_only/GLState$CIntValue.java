package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;

public class GLState$CIntValue implements Value {
   int value;

   public GLState$CIntValue set(int var1) {
      this.value = var1;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      return var1 instanceof GLState$CIntValue && ((GLState$CIntValue)var1).value == this.value;
   }

   public Value set(Value var1) {
      this.value = ((GLState$CIntValue)var1).value;
      return this;
   }
}
