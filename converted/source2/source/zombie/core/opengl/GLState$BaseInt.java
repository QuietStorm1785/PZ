package zombie.core.opengl;

import zombie.core.opengl.GLState.CIntValue;

public abstract class GLState$BaseInt extends IOpenGLState<CIntValue> {
   CIntValue defaultValue() {
      return new CIntValue();
   }
}
