package zombie.network;

import zombie.iso.IsoDirections;
import zombie.iso.Vector2;
import zombie.network.FakeClientManager.HordeCreator;
import zombie.network.FakeClientManager.SoundMaker;
import zombie.network.FakeClientManager.Movement.Motion;
import zombie.network.FakeClientManager.Movement.Type;

class FakeClientManager$Movement {
   static String version;
   static int defaultRadius = 150;
   static int aimSpeed = 4;
   static int sneakSpeed = 6;
   static int walkSpeed = 7;
   static int sneakRunSpeed = 10;
   static int runSpeed = 13;
   static int sprintSpeed = 19;
   static int pedestrianSpeedMin = 5;
   static int pedestrianSpeedMax = 20;
   static int vehicleSpeedMin = 40;
   static int vehicleSpeedMax = 80;
   static final float zombieLungeDistanceSquared = 100.0F;
   static final float zombieWalkSpeed = 3.0F;
   static final float zombieLungeSpeed = 6.0F;
   final int id;
   final String description;
   final Vector2 spawn;
   Motion motion;
   float speed;
   final Type type;
   final int radius;
   final IsoDirections direction;
   final Vector2 destination;
   final boolean ghost;
   final long connectDelay;
   final long disconnectDelay;
   final long reconnectDelay;
   final long teleportDelay;
   final HordeCreator hordeCreator;
   SoundMaker soundMaker;
   long timestamp;

   public FakeClientManager$Movement(
      int var1,
      String var2,
      int var3,
      int var4,
      Motion var5,
      int var6,
      Type var7,
      int var8,
      int var9,
      int var10,
      IsoDirections var11,
      boolean var12,
      long var13,
      long var15,
      long var17,
      long var19,
      HordeCreator var21,
      SoundMaker var22
   ) {
      this.id = var1;
      this.description = var2;
      this.spawn = new Vector2(var3, var4);
      this.motion = var5;
      this.speed = var6;
      this.type = var7;
      this.radius = var8;
      this.direction = var11;
      this.destination = new Vector2(var9, var10);
      this.ghost = var12;
      this.connectDelay = var13;
      this.disconnectDelay = var15;
      this.reconnectDelay = var17;
      this.teleportDelay = var19;
      this.hordeCreator = var21;
      this.soundMaker = var22;
   }

   public void connect(int var1) {
      long var2 = System.currentTimeMillis();
      if (this.disconnectDelay != 0L) {
         FakeClientManager.info(
            this.id,
            String.format(
               "Player %3d connect in %.3fs, disconnect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F, (float)this.disconnectDelay / 1000.0F
            )
         );
      } else {
         FakeClientManager.info(this.id, String.format("Player %3d connect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F));
      }

      this.timestamp = var2;
   }

   public void disconnect(int var1) {
      long var2 = System.currentTimeMillis();
      if (this.reconnectDelay != 0L) {
         FakeClientManager.info(
            this.id,
            String.format(
               "Player %3d disconnect in %.3fs, reconnect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F, (float)this.reconnectDelay / 1000.0F
            )
         );
      } else {
         FakeClientManager.info(this.id, String.format("Player %3d disconnect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F));
      }

      this.timestamp = var2;
   }

   public boolean doTeleport() {
      return this.teleportDelay != 0L;
   }

   public boolean doDisconnect() {
      return this.disconnectDelay != 0L;
   }

   public boolean checkDisconnect() {
      return System.currentTimeMillis() - this.timestamp > this.disconnectDelay;
   }

   public boolean doReconnect() {
      return this.reconnectDelay != 0L;
   }

   public boolean checkReconnect() {
      return System.currentTimeMillis() - this.timestamp > this.reconnectDelay;
   }
}
