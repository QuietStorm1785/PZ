package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;

public class GLState$CBooleanValue implements Value {
   public static final GLState$CBooleanValue TRUE = new GLState$CBooleanValue(true);
   public static final GLState$CBooleanValue FALSE = new GLState$CBooleanValue(false);
   boolean value;

   GLState$CBooleanValue(boolean var1) {
      this.value = var1;
   }

   @Override
   public boolean equals(Object var1) {
      return var1 instanceof GLState$CBooleanValue && ((GLState$CBooleanValue)var1).value == this.value;
   }

   public Value set(Value var1) {
      this.value = ((GLState$CBooleanValue)var1).value;
      return this;
   }
}
