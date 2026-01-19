package zombie.core.znet;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.DirectoryStream.Filter;

class SteamWorkshop$1 implements Filter<Path> {
   SteamWorkshop$1(SteamWorkshop var1) {
      this.this$0 = var1;
   }

   public boolean accept(Path var1) throws IOException {
      return Files.isDirectory(var1);
   }
}
