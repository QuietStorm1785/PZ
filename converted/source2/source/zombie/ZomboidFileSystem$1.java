package zombie;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.DirectoryStream.Filter;

class ZomboidFileSystem$1 implements Filter<Path> {
   ZomboidFileSystem$1(ZomboidFileSystem var1) {
      this.this$0 = var1;
   }

   public boolean accept(Path var1) throws IOException {
      return Files.isDirectory(var1) && Files.exists(var1.resolve("mod.info"));
   }
}
