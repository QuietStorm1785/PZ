package zombie.core.opengl;

import zombie.core.opengl.GLState.CBooleanValue;

public abstract class GLState$BaseBoolean extends IOpenGLState<CBooleanValue> {
   CBooleanValue defaultValue() {
      return new CBooleanValue(true);
   }
}
