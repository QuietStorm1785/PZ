package zombie.network;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.DirectoryStream.Filter;

class ServerSettingsManager$1 implements Filter<Path> {
   ServerSettingsManager$1(ServerSettingsManager var1) {
      this.this$0 = var1;
   }

   public boolean accept(Path var1) throws IOException {
      String var2 = var1.getFileName().toString();
      return !Files.isDirectory(var1) && var2.endsWith(".ini") && !var2.endsWith("_zombies.ini") && this.this$0.isValidName(var2.replace(".ini", ""));
   }
}
