package zombie.network;

import java.util.ArrayList;
import zombie.characters.IsoPlayer;
import zombie.iso.IsoGridSquare;
import zombie.network.ServerLOS.LOSThread;
import zombie.network.ServerLOS.PlayerData;
import zombie.network.ServerLOS.UpdateStatus;

public class ServerLOS {
   public static ServerLOS instance;
   private LOSThread thread;
   private ArrayList<PlayerData> playersMain = new ArrayList<>();
   private ArrayList<PlayerData> playersLOS = new ArrayList<>();
   private boolean bMapLoading = false;
   private boolean bSuspended = false;
   boolean bWasSuspended;

   private void noise(String var1) {
   }

   public static void init() {
      instance = new ServerLOS();
      instance.start();
   }

   public void start() {
      this.thread = new LOSThread(this);
      this.thread.setName("LOS");
      this.thread.setDaemon(true);
      this.thread.start();
   }

   public void addPlayer(IsoPlayer var1) {
      synchronized (this.playersMain) {
         if (this.findData(var1) == null) {
            PlayerData var3 = new PlayerData(this, var1);
            this.playersMain.add(var3);
            synchronized (this.thread.notifier) {
               this.thread.notifier.notify();
            }
         }
      }
   }

   public void removePlayer(IsoPlayer var1) {
      synchronized (this.playersMain) {
         PlayerData var3 = this.findData(var1);
         this.playersMain.remove(var3);
         synchronized (this.thread.notifier) {
            this.thread.notifier.notify();
         }
      }
   }

   public boolean isCouldSee(IsoPlayer var1, IsoGridSquare var2) {
      PlayerData var3 = this.findData(var1);
      if (var3 != null) {
         int var4 = var2.x - var3.px + 50;
         int var5 = var2.y - var3.py + 50;
         if (var4 >= 0 && var4 < 100 && var5 >= 0 && var5 < 100) {
            return var3.visible[var4][var5][var2.z];
         }
      }

      return false;
   }

   public void doServerZombieLOS(IsoPlayer var1) {
      if (ServerMap.instance.bUpdateLOSThisFrame) {
         PlayerData var2 = this.findData(var1);
         if (var2 != null) {
            if (var2.status == UpdateStatus.NeverDone) {
               var2.status = UpdateStatus.ReadyInMain;
            }

            if (var2.status == UpdateStatus.ReadyInMain) {
               var2.status = UpdateStatus.WaitingInLOS;
               this.noise("WaitingInLOS playerID=" + var1.OnlineID);
               synchronized (this.thread.notifier) {
                  this.thread.notifier.notify();
               }
            }
         }
      }
   }

   public void updateLOS(IsoPlayer var1) {
      PlayerData var2 = this.findData(var1);
      if (var2 != null) {
         if (var2.status == UpdateStatus.ReadyInLOS || var2.status == UpdateStatus.ReadyInMain) {
            if (var2.status == UpdateStatus.ReadyInLOS) {
               this.noise("BusyInMain playerID=" + var1.OnlineID);
            }

            var2.status = UpdateStatus.BusyInMain;
            var1.updateLOS();
            var2.status = UpdateStatus.ReadyInMain;
            synchronized (this.thread.notifier) {
               this.thread.notifier.notify();
            }
         }
      }
   }

   private PlayerData findData(IsoPlayer var1) {
      for (int var2 = 0; var2 < this.playersMain.size(); var2++) {
         if (this.playersMain.get(var2).player == var1) {
            return this.playersMain.get(var2);
         }
      }

      return null;
   }

   public void suspend() {
      this.bMapLoading = true;
      this.bWasSuspended = this.bSuspended;

      while (!this.bSuspended) {
         try {
            Thread.sleep(1L);
         } catch (InterruptedException var2) {
         }
      }

      if (!this.bWasSuspended) {
         this.noise("suspend **********");
      }
   }

   public void resume() {
      this.bMapLoading = false;
      synchronized (this.thread.notifier) {
         this.thread.notifier.notify();
      }

      if (!this.bWasSuspended) {
         this.noise("resume **********");
      }
   }
}
