package zombie.core.skinnedmodel;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import zombie.core.ImmutableColor;
import zombie.iso.IsoGridSquare.ResultLight;

final class DeadBodyAtlas$Checksummer {
   private MessageDigest md;
   private final StringBuilder sb = new StringBuilder();

   private DeadBodyAtlas$Checksummer() {
   }

   public void reset() throws NoSuchAlgorithmException {
      if (this.md == null) {
         this.md = MessageDigest.getInstance("MD5");
      }

      this.md.reset();
   }

   public void update(byte var1) {
      this.md.update(var1);
   }

   public void update(boolean var1) {
      this.md.update((byte)(var1 ? 1 : 0));
   }

   public void update(int var1) {
      this.md.update((byte)(var1 & 0xFF));
      this.md.update((byte)(var1 >> 8 & 0xFF));
      this.md.update((byte)(var1 >> 16 & 0xFF));
      this.md.update((byte)(var1 >> 24 & 0xFF));
   }

   public void update(String var1) {
      if (var1 != null && !var1.isEmpty()) {
         this.md.update(var1.getBytes());
      }
   }

   public void update(ImmutableColor var1) {
      this.update((byte)(var1.r * 255.0F));
      this.update((byte)(var1.g * 255.0F));
      this.update((byte)(var1.b * 255.0F));
   }

   public void update(ResultLight var1, float var2, float var3, float var4) {
      if (var1 != null && var1.radius > 0) {
         this.update((int)(var1.x - var2));
         this.update((int)(var1.y - var3));
         this.update((int)(var1.z - var4));
         this.update((byte)(var1.r * 255.0F));
         this.update((byte)(var1.g * 255.0F));
         this.update((byte)(var1.b * 255.0F));
         this.update((byte)var1.radius);
      }
   }

   public String checksumToString() {
      byte[] var1 = this.md.digest();
      this.sb.setLength(0);

      for (int var2 = 0; var2 < var1.length; var2++) {
         this.sb.append(var1[var2] & 255);
      }

      return this.sb.toString();
   }
}
