package zombie.network;

import zombie.GameTime;

class ItemTransactionManager$ItemRequest {
   private static final byte StateUnknown = 0;
   private static final byte StateRejected = 1;
   private static final byte StateAccepted = 2;
   private final int itemID;
   private final int srcID;
   private final int dstID;
   private final long timestamp;
   private byte state;

   private ItemTransactionManager$ItemRequest(int var1, int var2, int var3) {
      this.itemID = var1;
      this.srcID = var2;
      this.dstID = var3;
      this.timestamp = GameTime.getServerTimeMills() + 5000L;
      this.state = (byte)(GameServer.bServer ? 1 : 0);
   }

   private void setState(byte var1) {
      this.state = var1;
   }

   private boolean isTimeout() {
      return GameTime.getServerTimeMills() > this.timestamp;
   }
}
