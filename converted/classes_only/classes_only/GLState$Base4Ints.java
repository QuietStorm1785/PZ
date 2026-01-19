package zombie.core.opengl;

import zombie.core.opengl.GLState.C4IntsValue;

public abstract class GLState$Base4Ints extends IOpenGLState<C4IntsValue> {
   C4IntsValue defaultValue() {
      return new C4IntsValue();
   }
}
