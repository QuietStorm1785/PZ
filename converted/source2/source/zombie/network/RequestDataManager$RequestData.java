package zombie.network;

import java.nio.ByteBuffer;
import zombie.network.packets.RequestDataPacket.RequestID;

class RequestDataManager$RequestData {
   private final RequestID id;
   private final ByteBuffer bb;
   private final long connectionGUID;
   private long creationTime = System.currentTimeMillis();
   private int realTransmitted;
   private int realTransmittedFromLastACK;

   public RequestDataManager$RequestData(RequestID var1, ByteBuffer var2, long var3) {
      this.id = var1;
      this.bb = ByteBuffer.allocate(var2.position());
      this.bb.put(var2.array(), 0, this.bb.limit());
      this.connectionGUID = var3;
      this.realTransmitted = 0;
      this.realTransmittedFromLastACK = 0;
   }

   public RequestDataManager$RequestData(RequestID var1, int var2, long var3) {
      this.id = var1;
      this.bb = ByteBuffer.allocate(var2);
      this.bb.clear();
      this.connectionGUID = var3;
      this.realTransmitted = 0;
      this.realTransmittedFromLastACK = 0;
   }
}
