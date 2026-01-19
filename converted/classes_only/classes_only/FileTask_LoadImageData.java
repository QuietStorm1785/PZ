package zombie.asset;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import zombie.core.textures.ImageData;
import zombie.core.textures.TextureIDAssetManager;
import zombie.debug.DebugOptions;
import zombie.fileSystem.FileSystem;
import zombie.fileSystem.FileTask;
import zombie.fileSystem.IFileTaskCallback;

public final class FileTask_LoadImageData extends FileTask {
   String m_image_name;
   boolean bMask = false;

   public FileTask_LoadImageData(String var1, FileSystem var2, IFileTaskCallback var3) {
      super(var2, var3);
      this.m_image_name = var1;
   }

   public String getErrorMessage() {
      return this.m_image_name;
   }

   public void done() {
   }

   public Object call() throws Exception {
      TextureIDAssetManager.instance.waitFileTask();
      if (DebugOptions.instance.AssetSlowLoad.getValue()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var9) {
         }
      }

      ImageData var3;
      try (
         FileInputStream var1 = new FileInputStream(this.m_image_name);
         BufferedInputStream var2 = new BufferedInputStream(var1);
      ) {
         var3 = new ImageData(var2, this.bMask);
      }

      return var3;
   }
}
