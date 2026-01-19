package zombie.core;

import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;

class WinReqistry$StreamReader extends Thread {
   private InputStream is;
   private StringWriter sw = new StringWriter();

   public WinReqistry$StreamReader(InputStream var1) {
      this.is = var1;
   }

   @Override
   public void run() {
      int var1;
      try {
         while ((var1 = this.is.read()) != -1) {
            this.sw.write(var1);
         }
      } catch (IOException var2) {
      }
   }

   public String getResult() {
      return this.sw.toString();
   }
}
