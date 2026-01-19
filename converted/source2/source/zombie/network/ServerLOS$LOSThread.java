package zombie.network;

import zombie.characters.IsoPlayer;
import zombie.iso.IsoGridSquare;
import zombie.iso.LosUtil;
import zombie.network.ServerLOS.PlayerData;
import zombie.network.ServerLOS.UpdateStatus;

class ServerLOS$LOSThread extends Thread {
   public Object notifier;

   private ServerLOS$LOSThread(ServerLOS var1) {
      this.this$0 = var1;
      this.notifier = new Object();
   }

   @Override
   public void run() {
      while (true) {
         try {
            this.runInner();
         } catch (Exception var2) {
            var2.printStackTrace();
         }
      }
   }

   private void runInner() {
      MPStatistic.getInstance().ServerLOS.Start();
      synchronized (this.this$0.playersMain) {
         this.this$0.playersLOS.clear();
         this.this$0.playersLOS.addAll(this.this$0.playersMain);
      }

      for (int var7 = 0; var7 < this.this$0.playersLOS.size(); var7++) {
         PlayerData var2 = (PlayerData)this.this$0.playersLOS.get(var7);
         if (var2.status == UpdateStatus.WaitingInLOS) {
            var2.status = UpdateStatus.BusyInLOS;
            this.this$0.noise("BusyInLOS playerID=" + var2.player.OnlineID);
            this.calcLOS(var2);
            var2.status = UpdateStatus.ReadyInLOS;
         }

         if (this.this$0.bMapLoading) {
            break;
         }
      }

      MPStatistic.getInstance().ServerLOS.End();

      while (this.shouldWait()) {
         this.this$0.bSuspended = true;
         synchronized (this.notifier) {
            try {
               this.notifier.wait();
            } catch (InterruptedException var4) {
            }
         }
      }

      this.this$0.bSuspended = false;
   }

   private void calcLOS(PlayerData var1) {
      boolean var2 = false;
      if (var1.px == (int)var1.player.getX() && var1.py == (int)var1.player.getY() && var1.pz == (int)var1.player.getZ()) {
         var2 = true;
      }

      var1.px = (int)var1.player.getX();
      var1.py = (int)var1.player.getY();
      var1.pz = (int)var1.player.getZ();
      var1.player.initLightInfo2();
      if (!var2) {
         byte var3 = 0;

         for (int var4 = 0; var4 < LosUtil.XSIZE; var4++) {
            for (int var5 = 0; var5 < LosUtil.YSIZE; var5++) {
               for (int var6 = 0; var6 < LosUtil.ZSIZE; var6++) {
                  LosUtil.cachedresults[var4][var5][var6][var3] = 0;
               }
            }
         }

         try {
            IsoPlayer.players[var3] = var1.player;
            int var13 = var1.px;
            int var14 = var1.py;

            for (int var15 = -50; var15 < 50; var15++) {
               for (int var7 = -50; var7 < 50; var7++) {
                  for (int var8 = 0; var8 < 8; var8++) {
                     IsoGridSquare var9 = ServerMap.instance.getGridSquare(var15 + var13, var7 + var14, var8);
                     if (var9 != null) {
                        var9.CalcVisibility(var3);
                        var1.visible[var15 + 50][var7 + 50][var8] = var9.isCouldSee(var3);
                        var9.checkRoomSeen(var3);
                     }
                  }
               }
            }
         } finally {
            IsoPlayer.players[var3] = null;
         }
      }
   }

   private boolean shouldWait() {
      if (this.this$0.bMapLoading) {
         return true;
      } else {
         for (int var1 = 0; var1 < this.this$0.playersLOS.size(); var1++) {
            PlayerData var2 = (PlayerData)this.this$0.playersLOS.get(var1);
            if (var2.status == UpdateStatus.WaitingInLOS) {
               return false;
            }
         }

         synchronized (this.this$0.playersMain) {
            return this.this$0.playersLOS.size() == this.this$0.playersMain.size();
         }
      }
   }
}
