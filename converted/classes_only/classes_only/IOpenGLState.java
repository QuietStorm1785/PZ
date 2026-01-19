package zombie.core.opengl;

import zombie.core.opengl.IOpenGLState.Value;

public abstract class IOpenGLState<T extends Value> {
   protected T currentValue = this.defaultValue();
   private boolean dirty = true;

   public void set(T var1) {
      if (this.dirty || !var1.equals(this.currentValue)) {
         this.setCurrentValue((T)var1);
         this.Set((T)var1);
      }
   }

   void setCurrentValue(T var1) {
      this.dirty = false;
      this.currentValue.set(var1);
   }

   public void setDirty() {
      this.dirty = true;
   }

   T getCurrentValue() {
      return this.currentValue;
   }

   abstract T defaultValue();

   abstract void Set(T var1);
}
