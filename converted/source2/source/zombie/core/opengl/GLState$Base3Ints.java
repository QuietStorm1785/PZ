package zombie.core.opengl;

import zombie.core.opengl.GLState.C3IntsValue;

public abstract class GLState$Base3Ints extends IOpenGLState<C3IntsValue> {
   C3IntsValue defaultValue() {
      return new C3IntsValue();
   }
}
