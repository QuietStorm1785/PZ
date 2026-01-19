package zombie.fileSystem;

import java.io.IOException;
import java.io.InputStream;
import zombie.fileSystem.MemoryFileDevice.MemoryFile;

public final class MemoryFileDevice implements IFileDevice {
   public IFile createFile(IFile var1) {
      return new MemoryFile(var1, this);
   }

   public void destroyFile(IFile var1) {
   }

   public InputStream createStream(String var1, InputStream var2) throws IOException {
      return null;
   }

   public void destroyStream(InputStream var1) {
   }

   public String name() {
      return "memory";
   }
}
