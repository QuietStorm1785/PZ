package zombie.worldMap;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import zombie.ZomboidFileSystem;
import zombie.core.math.PZMath;

public final class WorldMapImages {
   private static final HashMap<String, WorldMapImages> s_filenameToImages = new HashMap<>();
   private String m_directory;
   private ImagePyramid m_pyramid;

   public static WorldMapImages getOrCreate(String var0) {
      String var1 = ZomboidFileSystem.instance.getString(var0 + "/pyramid.zip");
      if (!Files.exists(Paths.get(var1))) {
         return null;
      } else {
         WorldMapImages var2 = s_filenameToImages.get(var1);
         if (var2 == null) {
            var2 = new WorldMapImages();
            var2.m_directory = var0;
            var2.m_pyramid = new ImagePyramid();
            var2.m_pyramid.setZipFile(var1);
            s_filenameToImages.put(var1, var2);
         }

         return var2;
      }
   }

   public ImagePyramid getPyramid() {
      return this.m_pyramid;
   }

   public int getMinX() {
      return this.m_pyramid.m_minX;
   }

   public int getMinY() {
      return this.m_pyramid.m_minY;
   }

   public int getMaxX() {
      return this.m_pyramid.m_maxX;
   }

   public int getMaxY() {
      return this.m_pyramid.m_maxY;
   }

   public int getZoom(float var1) {
      byte var2 = 4;
      if (var1 >= 16.0) {
         var2 = 0;
      } else if (var1 >= 15.0F) {
         var2 = 1;
      } else if (var1 >= 14.0F) {
         var2 = 2;
      } else if (var1 >= 13.0F) {
         var2 = 3;
      }

      return PZMath.clamp(var2, this.m_pyramid.m_minZ, this.m_pyramid.m_maxZ);
   }

   public float getResolution() {
      return this.m_pyramid.m_resolution;
   }

   private void destroy() {
      this.m_pyramid.destroy();
   }

   public static void Reset() {
      for (WorldMapImages var1 : s_filenameToImages.values()) {
         var1.destroy();
      }

      s_filenameToImages.clear();
   }
}
