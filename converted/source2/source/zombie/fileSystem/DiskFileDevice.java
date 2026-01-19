package zombie.fileSystem;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import zombie.fileSystem.DiskFileDevice.DiskFile;

public final class DiskFileDevice implements IFileDevice {
   private final String m_name;

   public DiskFileDevice(String var1) {
      this.m_name = var1;
   }

   public IFile createFile(IFile var1) {
      return new DiskFile(var1, this);
   }

   public void destroyFile(IFile var1) {
   }

   public InputStream createStream(String var1, InputStream var2) throws IOException {
      return new FileInputStream(var1);
   }

   public void destroyStream(InputStream var1) {
   }

   public String name() {
      return this.m_name;
   }
}
