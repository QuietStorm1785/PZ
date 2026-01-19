package zombie.network;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Arrays;
import org.apache.commons.codec.binary.Hex;

public final class NetChecksum$GroupOfFiles {
   static final int MAX_FILES = 20;
   static MessageDigest mdTotal;
   static MessageDigest mdCurrentFile;
   static final ArrayList<NetChecksum$GroupOfFiles> groups = new ArrayList<>();
   static NetChecksum$GroupOfFiles currentGroup;
   byte[] totalChecksum;
   short fileCount;
   final String[] relPaths = new String[20];
   final String[] absPaths = new String[20];
   final byte[][] checksums = new byte[20][];

   private NetChecksum$GroupOfFiles() throws NoSuchAlgorithmException {
      if (mdTotal == null) {
         mdTotal = MessageDigest.getInstance("MD5");
         mdCurrentFile = MessageDigest.getInstance("MD5");
      }

      mdTotal.reset();
      groups.add(this);
   }

   @Override
   public String toString() {
      StringBuilder var1 = new StringBuilder()
         .append(this.fileCount)
         .append(" files, ")
         .append(this.absPaths.length)
         .append("/")
         .append(this.relPaths.length)
         .append("/")
         .append(this.checksums.length)
         .append(" \"")
         .append(Hex.encodeHexString(this.totalChecksum))
         .append("\"");

      for (int var2 = 0; var2 < 20; var2++) {
         var1.append("\n");
         if (var2 < this.relPaths.length) {
            var1.append(" \"").append(this.relPaths[var2]).append("\"");
         }

         if (var2 < this.checksums.length) {
            if (this.checksums[var2] == null) {
               var1.append(" \"\"");
            } else {
               var1.append(" \"").append(Hex.encodeHexString(this.checksums[var2])).append("\"");
            }
         }

         if (var2 < this.absPaths.length) {
            var1.append(" \"").append(this.absPaths[var2]).append("\"");
         }
      }

      return var1.toString();
   }

   private void gc_() {
      Arrays.fill(this.relPaths, null);
      Arrays.fill(this.absPaths, null);
      Arrays.fill(this.checksums, null);
   }

   public static void initChecksum() {
      groups.clear();
      currentGroup = null;
   }

   public static void finishChecksum() {
      if (currentGroup != null) {
         currentGroup.totalChecksum = mdTotal.digest();
         currentGroup = null;
      }
   }

   private static void addFile(String var0, String var1) throws NoSuchAlgorithmException {
      if (currentGroup == null) {
         currentGroup = new NetChecksum$GroupOfFiles();
      }

      currentGroup.relPaths[currentGroup.fileCount] = var0;
      currentGroup.absPaths[currentGroup.fileCount] = var1;
      mdCurrentFile.reset();
   }

   private static void updateFile(byte[] var0, int var1) {
      mdCurrentFile.update(var0, 0, var1);
      mdTotal.update(var0, 0, var1);
   }

   private static void endFile() {
      currentGroup.checksums[currentGroup.fileCount] = mdCurrentFile.digest();
      currentGroup.fileCount++;
      if (currentGroup.fileCount >= 20) {
         currentGroup.totalChecksum = mdTotal.digest();
         currentGroup = null;
      }
   }

   public static void gc() {
      for (NetChecksum$GroupOfFiles var1 : groups) {
         var1.gc_();
      }

      groups.clear();
   }
}
