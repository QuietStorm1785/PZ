package zombie.iso;

class ObjectsSyncRequests$SyncIsoGridSquare {
   int x;
   int y;
   int z;
   long reqTime;
   int reqCount;

   private ObjectsSyncRequests$SyncIsoGridSquare(ObjectsSyncRequests var1) {
      this.this$0 = var1;
   }

   @Override
   public int hashCode() {
      return this.x + this.y + this.z;
   }
}
