package zombie;

import zombie.MapCollisionData.IPathResult;

final class MapCollisionData$PathTask {
   public int startX;
   public int startY;
   public int endX;
   public int endY;
   public int curX;
   public int curY;
   public int status;
   public IPathResult result;
   public boolean myThread;

   private MapCollisionData$PathTask(MapCollisionData var1) {
      this.this$0 = var1;
   }

   public void init(int var1, int var2, int var3, int var4, IPathResult var5) {
      this.startX = var1;
      this.startY = var2;
      this.endX = var3;
      this.endY = var4;
      this.status = 0;
      this.result = var5;
   }

   public void execute() {
      this.status = MapCollisionData.n_pathTask(this.startX, this.startY, this.endX, this.endY, MapCollisionData.curXY);
      this.curX = MapCollisionData.curXY[0];
      this.curY = MapCollisionData.curXY[1];
      if (this.myThread) {
         this.result.finished(this.status, this.curX, this.curY);
      } else {
         this.this$0.pathResultQueue.add(this);
      }
   }

   public void release() {
      this.this$0.freePathTasks.push(this);
   }
}
