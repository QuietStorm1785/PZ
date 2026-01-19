package zombie.core.textures;

class Pcx$pcx_t {
   char bits_per_pixel;
   short bytes_per_line;
   char color_planes;
   byte[] data;
   char encoding;
   byte[] filler;
   short hres;
   short vres;
   char manufacturer;
   int[] palette;
   short palette_type;
   char reserved;
   char version;
   short xmin;
   short ymin;
   short xmax;
   short ymax;

   Pcx$pcx_t(Pcx var1, byte[] var2) {
      this.this$0 = var1;
      this.filler = new byte[58];
      this.palette = new int[48];
      this.manufacturer = (char)var2[0];
      this.version = (char)var2[1];
      this.encoding = (char)var2[2];
      this.bits_per_pixel = (char)var2[3];
      this.xmin = (short)(var2[4] + (var2[5] << 8) & 0xFF);
      this.ymin = (short)(var2[6] + (var2[7] << 8) & 0xFF);
      this.xmax = (short)(var2[8] + (var2[9] << 8) & 0xFF);
      this.ymax = (short)(var2[10] + (var2[11] << 8) & 0xFF);
      this.hres = (short)(var2[12] + (var2[13] << 8) & 0xFF);
      this.vres = (short)(var2[14] + (var2[15] << 8) & 0xFF);

      for (int var3 = 0; var3 < 48; var3++) {
         this.palette[var3] = var2[16 + var3] & 255;
      }

      this.reserved = (char)var2[64];
      this.color_planes = (char)var2[65];
      this.bytes_per_line = (short)(var2[66] + (var2[67] << 8) & 0xFF);
      this.palette_type = (short)(var2[68] + (var2[69] << 8) & 0xFF);

      for (int var4 = 0; var4 < 58; var4++) {
         this.filler[var4] = var2[70 + var4];
      }

      this.data = new byte[var2.length - 128];

      for (int var5 = 0; var5 < var2.length - 128; var5++) {
         this.data[var5] = var2[128 + var5];
      }
   }
}
