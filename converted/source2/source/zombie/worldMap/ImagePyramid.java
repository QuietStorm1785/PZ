package zombie.worldMap;

import java.awt.image.BufferedImage;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.IntBuffer;
import java.nio.file.DirectoryStream;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;
import javax.imageio.ImageIO;
import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.core.opengl.RenderThread;
import zombie.core.textures.ImageData;
import zombie.core.textures.MipMapLevel;
import zombie.core.textures.Texture;
import zombie.core.textures.TextureID;
import zombie.worldMap.ImagePyramid.PyramidTexture;

public final class ImagePyramid {
   String m_directory;
   String m_zipFile;
   FileSystem m_zipFS;
   final HashMap<String, PyramidTexture> m_textures = new HashMap<>();
   final HashSet<String> m_missing = new HashSet<>();
   int m_requestNumber = 0;
   int m_minX;
   int m_minY;
   int m_maxX;
   int m_maxY;
   float m_resolution = 1.0F;
   int m_minZ;
   int m_maxZ;
   int MAX_TEXTURES = 100;
   int MAX_REQUEST_NUMBER = Core.bDebug ? 10000 : Integer.MAX_VALUE;

   public void setDirectory(String var1) {
      if (this.m_zipFile != null) {
         this.m_zipFile = null;
         if (this.m_zipFS != null) {
            try {
               this.m_zipFS.close();
            } catch (IOException var3) {
            }

            this.m_zipFS = null;
         }
      }

      this.m_directory = var1;
   }

   public void setZipFile(String var1) {
      this.m_directory = null;
      this.m_zipFile = var1;
      this.m_zipFS = this.openZipFile();
      this.readInfoFile();
      this.m_minZ = Integer.MAX_VALUE;
      this.m_maxZ = Integer.MIN_VALUE;
      if (this.m_zipFS != null) {
         try (DirectoryStream var2 = Files.newDirectoryStream(this.m_zipFS.getPath("/"))) {
            for (Path var4 : var2) {
               if (Files.isDirectory(var4)) {
                  int var5 = PZMath.tryParseInt(var4.getFileName().toString(), -1);
                  this.m_minZ = PZMath.min(this.m_minZ, var5);
                  this.m_maxZ = PZMath.max(this.m_maxZ, var5);
               }
            }
         } catch (IOException var8) {
            ExceptionLogger.logException(var8);
         }
      }
   }

   public Texture getImage(int var1, int var2, int var3) {
      String var4 = String.format("%dx%dx%d", var1, var2, var3);
      if (this.m_missing.contains(var4)) {
         return null;
      } else {
         File var5 = new File(this.m_directory, String.format("%s%d%stile%dx%d.png", File.separator, var3, File.separator, var1, var2));
         if (!var5.exists()) {
            this.m_missing.add(var4);
            return null;
         } else {
            return Texture.getSharedTexture(var5.getAbsolutePath());
         }
      }
   }

   public TextureID getTexture(int var1, int var2, int var3) {
      String var4 = String.format("%dx%dx%d", var1, var2, var3);
      if (this.m_textures.containsKey(var4)) {
         PyramidTexture var15 = this.m_textures.get(var4);
         var15.m_requestNumber = this.m_requestNumber++;
         if (this.m_requestNumber >= this.MAX_REQUEST_NUMBER) {
            this.resetRequestNumbers();
         }

         return var15.m_textureID;
      } else if (this.m_missing.contains(var4)) {
         return null;
      } else if (this.m_zipFile == null) {
         File var14 = new File(this.m_directory, String.format("%s%d%stile%dx%d.png", File.separator, var3, File.separator, var1, var2));
         if (!var14.exists()) {
            this.m_missing.add(var4);
            return null;
         } else {
            Texture var16 = Texture.getSharedTexture(var14.getAbsolutePath());
            return var16 == null ? null : var16.getTextureId();
         }
      } else if (this.m_zipFS != null && this.m_zipFS.isOpen()) {
         try {
            Path var5 = this.m_zipFS.getPath(String.valueOf(var3), String.format("tile%dx%d.png", var1, var2));

            try {
               TextureID var17;
               try (InputStream var6 = Files.newInputStream(var5)) {
                  ImageData var7 = new ImageData(var6, false);
                  PyramidTexture var8 = this.checkTextureCache(var4);
                  if (var8.m_textureID == null) {
                     var17 = new TextureID(var7);
                     var8.m_textureID = var17;
                  } else {
                     this.replaceTextureData(var8, var7);
                  }

                  var17 = var8.m_textureID;
               }

               return var17;
            } catch (NoSuchFileException var12) {
               this.m_missing.add(var4);
            }
         } catch (Exception var13) {
            this.m_missing.add(var4);
            var13.printStackTrace();
         }

         return null;
      } else {
         return null;
      }
   }

   private void replaceTextureData(PyramidTexture var1, ImageData var2) {
      char var3;
      if (GL.getCapabilities().GL_ARB_texture_compression) {
         var3 = '蓮';
      } else {
         var3 = 6408;
      }

      GL11.glBindTexture(3553, Texture.lastTextureID = var1.m_textureID.getID());
      SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      GL11.glTexImage2D(3553, 0, var3, var2.getWidthHW(), var2.getHeightHW(), 0, 6408, 5121, var2.getData().getBuffer());
      var2.dispose();
   }

   public void generateFiles(String var1, String var2) throws Exception {
      ImageData var3 = new ImageData(var1);
      if (var3 != null) {
         short var4 = 256;
         byte var5 = 5;

         for (int var6 = 0; var6 < var5; var6++) {
            MipMapLevel var7 = var3.getMipMapData(var6);
            float var8 = (float)var3.getWidth() / (1 << var6);
            float var9 = (float)var3.getHeight() / (1 << var6);
            int var10 = (int)Math.ceil(var8 / var4);
            int var11 = (int)Math.ceil(var9 / var4);

            for (int var12 = 0; var12 < var11; var12++) {
               for (int var13 = 0; var13 < var10; var13++) {
                  BufferedImage var14 = this.getBufferedImage(var7, var13, var12, var4);
                  this.writeImageToFile(var14, var2, var13, var12, var6);
               }
            }
         }
      }
   }

   public FileSystem openZipFile() {
      try {
         return FileSystems.newFileSystem(Paths.get(this.m_zipFile));
      } catch (IOException var2) {
         var2.printStackTrace();
         return null;
      }
   }

   public void generateZip(String var1, String var2) throws Exception {
      ImageData var3 = new ImageData(var1);
      if (var3 != null) {
         short var4 = 256;

         try (
            FileOutputStream var5 = new FileOutputStream(var2);
            BufferedOutputStream var6 = new BufferedOutputStream(var5);
            ZipOutputStream var7 = new ZipOutputStream(var6);
         ) {
            byte var8 = 5;

            for (int var9 = 0; var9 < var8; var9++) {
               MipMapLevel var10 = var3.getMipMapData(var9);
               float var11 = (float)var3.getWidth() / (1 << var9);
               float var12 = (float)var3.getHeight() / (1 << var9);
               int var13 = (int)Math.ceil(var11 / var4);
               int var14 = (int)Math.ceil(var12 / var4);

               for (int var15 = 0; var15 < var14; var15++) {
                  for (int var16 = 0; var16 < var13; var16++) {
                     BufferedImage var17 = this.getBufferedImage(var10, var16, var15, var4);
                     this.writeImageToZip(var17, var7, var16, var15, var9);
                  }
               }

               if (var11 <= var4 && var12 <= var4) {
                  break;
               }
            }
         }
      }
   }

   BufferedImage getBufferedImage(MipMapLevel var1, int var2, int var3, int var4) {
      BufferedImage var5 = new BufferedImage(var4, var4, 2);
      int[] var6 = new int[var4];
      IntBuffer var7 = var1.getBuffer().asIntBuffer();

      for (int var8 = 0; var8 < var4; var8++) {
         var7.get(var2 * var4 + (var3 * var4 + var8) * var1.width, var6);

         for (int var9 = 0; var9 < var4; var9++) {
            int var10 = var6[var9];
            int var11 = var10 & 0xFF;
            int var12 = var10 >> 8 & 0xFF;
            int var13 = var10 >> 16 & 0xFF;
            int var14 = var10 >> 24 & 0xFF;
            var6[var9] = var14 << 24 | var11 << 16 | var12 << 8 | var13;
         }

         var5.setRGB(0, var8, var4, 1, var6, 0, var4);
      }

      return var5;
   }

   void writeImageToFile(BufferedImage var1, String var2, int var3, int var4, int var5) throws Exception {
      File var6 = new File(var2 + File.separator + var5);
      if (var6.exists() || var6.mkdirs()) {
         var6 = new File(var6, String.format("tile%dx%d.png", var3, var4));
         ImageIO.write(var1, "png", var6);
      }
   }

   void writeImageToZip(BufferedImage var1, ZipOutputStream var2, int var3, int var4, int var5) throws Exception {
      var2.putNextEntry(new ZipEntry(String.format("%d/tile%dx%d.png", var5, var3, var4)));
      ImageIO.write(var1, "PNG", var2);
      var2.closeEntry();
   }

   PyramidTexture checkTextureCache(String var1) {
      if (this.m_textures.size() < this.MAX_TEXTURES) {
         PyramidTexture var5 = new PyramidTexture();
         var5.m_key = var1;
         var5.m_requestNumber = this.m_requestNumber++;
         this.m_textures.put(var1, var5);
         if (this.m_requestNumber >= this.MAX_REQUEST_NUMBER) {
            this.resetRequestNumbers();
         }

         return var5;
      } else {
         PyramidTexture var2 = null;

         for (PyramidTexture var4 : this.m_textures.values()) {
            if (var2 == null || var2.m_requestNumber > var4.m_requestNumber) {
               var2 = var4;
            }
         }

         this.m_textures.remove(var2.m_key);
         var2.m_key = var1;
         var2.m_requestNumber = this.m_requestNumber++;
         this.m_textures.put(var2.m_key, var2);
         if (this.m_requestNumber >= this.MAX_REQUEST_NUMBER) {
            this.resetRequestNumbers();
         }

         return var2;
      }
   }

   void resetRequestNumbers() {
      ArrayList var1 = new ArrayList<>(this.m_textures.values());
      var1.sort(Comparator.comparingInt(var0 -> var0.m_requestNumber));
      this.m_requestNumber = 1;

      for (PyramidTexture var3 : var1) {
         var3.m_requestNumber = this.m_requestNumber++;
      }

      var1.clear();
   }

   private void readInfoFile() {
      if (this.m_zipFS != null && this.m_zipFS.isOpen()) {
         Path var1 = this.m_zipFS.getPath("pyramid.txt");

         String var5;
         try (
            InputStream var2 = Files.newInputStream(var1);
            InputStreamReader var3 = new InputStreamReader(var2);
            BufferedReader var4 = new BufferedReader(var3);
         ) {
            while ((var5 = var4.readLine()) != null) {
               if (var5.startsWith("VERSION=")) {
                  var5 = var5.substring("VERSION=".length());
               } else if (var5.startsWith("bounds=")) {
                  var5 = var5.substring("bounds=".length());
                  String[] var6 = var5.split(" ");
                  if (var6.length == 4) {
                     this.m_minX = PZMath.tryParseInt(var6[0], -1);
                     this.m_minY = PZMath.tryParseInt(var6[1], -1);
                     this.m_maxX = PZMath.tryParseInt(var6[2], -1);
                     this.m_maxY = PZMath.tryParseInt(var6[3], -1);
                  }
               } else if (var5.startsWith("resolution=")) {
                  var5 = var5.substring("resolution=".length());
                  this.m_resolution = PZMath.tryParseFloat(var5, 1.0F);
               }
            }
         } catch (Exception var13) {
            var13.printStackTrace();
         }
      }
   }

   public void destroy() {
      if (this.m_zipFS != null) {
         try {
            this.m_zipFS.close();
         } catch (IOException var2) {
         }

         this.m_zipFS = null;
      }

      RenderThread.invokeOnRenderContext(() -> {
         for (PyramidTexture var2x : this.m_textures.values()) {
            var2x.m_textureID.destroy();
         }
      });
      this.m_missing.clear();
      this.m_textures.clear();
   }
}
