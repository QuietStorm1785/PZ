package zombie.network;

import java.io.FileInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import zombie.core.logger.ExceptionLogger;
import zombie.network.NetChecksum.GroupOfFiles;

public final class NetChecksum$Checksummer {
   private MessageDigest md;
   private final byte[] fileBytes = new byte[1024];
   private final byte[] convertBytes = new byte[1024];
   private boolean convertLineEndings;

   public void reset(boolean var1) throws NoSuchAlgorithmException {
      if (this.md == null) {
         this.md = MessageDigest.getInstance("MD5");
      }

      this.convertLineEndings = var1;
      this.md.reset();
   }

   public void addFile(String var1, String var2) throws NoSuchAlgorithmException {
      if (this.md == null) {
         this.md = MessageDigest.getInstance("MD5");
      }

      try (FileInputStream var3 = new FileInputStream(var2)) {
         GroupOfFiles.addFile(var1, var2);

         int var4;
         while ((var4 = var3.read(this.fileBytes)) != -1) {
            if (this.convertLineEndings) {
               boolean var5 = false;
               int var6 = 0;

               for (int var7 = 0; var7 < var4 - 1; var7++) {
                  if (this.fileBytes[var7] == 13 && this.fileBytes[var7 + 1] == 10) {
                     this.convertBytes[var6++] = 10;
                     var5 = true;
                  } else {
                     var5 = false;
                     this.convertBytes[var6++] = this.fileBytes[var7];
                  }
               }

               if (!var5) {
                  this.convertBytes[var6++] = this.fileBytes[var4 - 1];
               }

               this.md.update(this.convertBytes, 0, var6);
               GroupOfFiles.updateFile(this.convertBytes, var6);
            } else {
               this.md.update(this.fileBytes, 0, var4);
               GroupOfFiles.updateFile(this.fileBytes, var4);
            }
         }

         GroupOfFiles.endFile();
      } catch (Exception var10) {
         ExceptionLogger.logException(var10);
      }
   }

   public String checksumToString() {
      byte[] var1 = this.md.digest();
      StringBuilder var2 = new StringBuilder();

      for (int var3 = 0; var3 < var1.length; var3++) {
         var2.append(Integer.toString((var1[var3] & 255) + 256, 16).substring(1));
      }

      return var2.toString();
   }

   @Override
   public String toString() {
      StringBuilder var1 = new StringBuilder();

      for (GroupOfFiles var3 : GroupOfFiles.groups) {
         String var4 = var3.toString();
         var1.append("\n").append(var4);
         if (GameClient.bClient) {
            NetChecksum.comparer.sendError(GameClient.connection, var4);
         }
      }

      return var1.toString();
   }
}
