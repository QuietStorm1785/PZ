package zombie.network;

import java.util.zip.CRC32;

final class FakeClientManager$Client$Request {
   private final int id;
   private final int wx;
   private final int wy;
   private final long crc;

   private FakeClientManager$Client$Request(int var1, int var2, int var3) {
      this.id = var3;
      this.wx = var1;
      this.wy = var2;
      CRC32 var4 = new CRC32();
      var4.reset();
      var4.update(String.format("map_%d_%d.bin", var1, var2).getBytes());
      this.crc = var4.getValue();
   }
}
