package zombie.Lua;

import java.io.IOException;
import java.nio.file.FileVisitResult;
import java.nio.file.FileVisitor;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.BasicFileAttributes;

class LuaManager$GlobalObject$3 implements FileVisitor<Path> {
   public FileVisitResult preVisitDirectory(Path var1, BasicFileAttributes var2) throws IOException {
      return FileVisitResult.CONTINUE;
   }

   public FileVisitResult visitFile(Path var1, BasicFileAttributes var2) throws IOException {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }

   public FileVisitResult visitFileFailed(Path var1, IOException var2) throws IOException {
      var2.printStackTrace();
      return FileVisitResult.CONTINUE;
   }

   public FileVisitResult postVisitDirectory(Path var1, IOException var2) throws IOException {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }
}
