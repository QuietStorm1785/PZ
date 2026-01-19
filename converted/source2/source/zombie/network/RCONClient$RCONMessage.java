package zombie.network;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class RCONClient$RCONMessage {
   private static final byte[] input = new byte[4096];
   private static final ByteBuffer bbr = ByteBuffer.wrap(input);
   private static final byte[] output = new byte[4096];
   private static final ByteBuffer bbw = ByteBuffer.wrap(output);
   static final int baseSize = 10;
   int size;
   int id;
   int type;
   byte[] body;

   RCONClient$RCONMessage() {
   }

   RCONClient$RCONMessage(int var1, int var2, String var3) throws UnsupportedEncodingException {
      this.id = var1;
      this.type = var2;
      this.body = var3.getBytes();
      this.size = 10 + var3.length();
   }

   private void writeObject(OutputStream var1) throws IOException {
      bbw.putInt(this.size);
      bbw.putInt(this.id);
      bbw.putInt(this.type);
      bbw.put(this.body);
      bbw.put((byte)0);
      bbw.put((byte)0);
      var1.write(output, 0, this.size + 4);
      bbw.clear();
   }

   private void readObject(InputStream var1, int var2) throws IOException {
      if (var2 == 0) {
         var1.read(input);
      } else {
         var1.read(input, 0, var2);
      }

      this.size = bbr.getInt();
      this.id = bbr.getInt();
      this.type = bbr.getInt();
      if (this.size > 10) {
         this.body = new byte[this.size - 10];
         bbr.get(this.body, 0, this.size - 10);
      }

      bbr.get();
      bbr.get();
      bbr.clear();
   }

   static {
      bbr.order(ByteOrder.LITTLE_ENDIAN);
      bbw.order(ByteOrder.LITTLE_ENDIAN);
   }
}
