package zombie.core.logger;

import java.io.PrintStream;

class ZLogger$OutputStreams {
   public PrintStream file;
   public PrintStream console;

   private ZLogger$OutputStreams() {
   }

   public void println(String var1) {
      if (this.file != null) {
         this.file.println(var1);
         this.file.flush();
      }

      if (this.console != null) {
         this.console.println(var1);
      }
   }
}
