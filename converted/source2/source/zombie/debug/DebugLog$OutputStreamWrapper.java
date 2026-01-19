package zombie.debug;

import java.io.FilterOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import zombie.core.Core;
import zombie.ui.UIDebugConsole;

final class DebugLog$OutputStreamWrapper extends FilterOutputStream {
   public DebugLog$OutputStreamWrapper(OutputStream var1) {
      super(var1);
   }

   @Override
   public void write(byte[] var1, int var2, int var3) throws IOException {
      this.out.write(var1, var2, var3);
      if (Core.bDebug && UIDebugConsole.instance != null && DebugOptions.instance.UIDebugConsoleDebugLog.getValue()) {
         UIDebugConsole.instance.addOutput(var1, var2, var3);
      }
   }

   public void setStream(OutputStream var1) {
      this.out = var1;
   }
}
