package zombie.Lua;

import java.io.IOException;
import java.io.PrintWriter;

public final class LuaManager$GlobalObject$LuaFileWriter {
   private final PrintWriter writer;

   public LuaManager$GlobalObject$LuaFileWriter(PrintWriter var1) {
      this.writer = var1;
   }

   public void write(String var1) throws IOException {
      this.writer.write(var1);
   }

   public void writeln(String var1) throws IOException {
      this.writer.write(var1);
      this.writer.write(System.lineSeparator());
   }

   public void close() throws IOException {
      this.writer.close();
   }
}
