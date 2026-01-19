package zombie;

import java.nio.file.FileVisitResult;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;

class DebugFileWatcher$1 extends SimpleFileVisitor<Path> {
   DebugFileWatcher$1(DebugFileWatcher var1) {
      this.this$0 = var1;
   }

   public FileVisitResult preVisitDirectory(Path var1, BasicFileAttributes var2) {
      this.this$0.registerDir(var1);
      return FileVisitResult.CONTINUE;
   }
}
