package zombie.core.opengl;

import zombie.core.opengl.GLState.CIntFloatValue;

public abstract class GLState$BaseIntFloat extends IOpenGLState<CIntFloatValue> {
   CIntFloatValue defaultValue() {
      return new CIntFloatValue();
   }
}
