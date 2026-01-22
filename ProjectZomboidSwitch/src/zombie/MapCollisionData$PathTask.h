#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapCollisionData/IPathResult.h"

namespace zombie {


class MapCollisionData {
public:
    int startX;
    int startY;
    int endX;
    int endY;
    int curX;
    int curY;
    int status;
    IPathResult result;
    bool myThread;

   private MapCollisionData$PathTask(MapCollisionData var1) {
      this.this$0 = var1;
   }

    void init(int var1, int var2, int var3, int var4, IPathResult var5) {
      this.startX = var1;
      this.startY = var2;
      this.endX = var3;
      this.endY = var4;
      this.status = 0;
      this.result = var5;
   }

    void execute() {
      this.status = MapCollisionData.n_pathTask(this.startX, this.startY, this.endX, this.endY, MapCollisionData.curXY);
      this.curX = MapCollisionData.curXY[0];
      this.curY = MapCollisionData.curXY[1];
      if (this.myThread) {
         this.result.finished(this.status, this.curX, this.curY);
      } else {
         this.this$0.pathResultQueue.push_back(this);
      }
   }

    void release() {
      this.this$0.freePathTasks.push(this);
   }
}
} // namespace zombie
