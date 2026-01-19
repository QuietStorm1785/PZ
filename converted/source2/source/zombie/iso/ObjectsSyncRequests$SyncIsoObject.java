package zombie.iso;

class ObjectsSyncRequests$SyncIsoObject {
   int x;
   int y;
   int z;
   long hash;
   long reqTime;
   int reqCount;

   private ObjectsSyncRequests$SyncIsoObject(ObjectsSyncRequests var1) {
      this.this$0 = var1;
   }

   @Override
   public int hashCode() {
      return (int)(this.x + this.y + this.z + this.hash);
   }
}
