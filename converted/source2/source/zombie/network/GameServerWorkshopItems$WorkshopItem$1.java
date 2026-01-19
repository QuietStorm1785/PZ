package zombie.network;

import java.io.IOException;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;
import zombie.network.GameServerWorkshopItems.WorkshopItem;

class GameServerWorkshopItems$WorkshopItem$1 extends SimpleFileVisitor<Path> {
   GameServerWorkshopItems$WorkshopItem$1(WorkshopItem var1) {
      this.this$0 = var1;
   }

   public FileVisitResult visitFile(Path var1, BasicFileAttributes var2) throws IOException {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }

   public FileVisitResult postVisitDirectory(Path var1, IOException var2) throws IOException {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }
}
