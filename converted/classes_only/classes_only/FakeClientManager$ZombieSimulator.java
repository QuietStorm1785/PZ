package zombie.network;

import com.google.common.collect.Sets;
import com.google.common.collect.UnmodifiableIterator;
import com.google.common.collect.Sets.SetView;
import java.nio.ByteBuffer;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import zombie.core.Rand;
import zombie.core.math.PZMath;
import zombie.core.utils.UpdateLimit;
import zombie.iso.IsoDirections;
import zombie.iso.IsoUtils;
import zombie.iso.Vector2;
import zombie.network.FakeClientManager.Player;
import zombie.network.FakeClientManager.Zombie;
import zombie.network.FakeClientManager.PlayerManager.RemotePlayer;
import zombie.network.FakeClientManager.ZombieSimulator.Behaviour;
import zombie.network.NetworkVariables.PredictionTypes;
import zombie.network.NetworkVariables.WalkType;
import zombie.network.NetworkVariables.ZombieState;
import zombie.network.PacketTypes.PacketType;
import zombie.network.packets.ZombiePacket;

class FakeClientManager$ZombieSimulator {
   public static Behaviour behaviour = Behaviour.Stay;
   public static int deleteZombieDistanceSquared = 10000;
   public static int forgotZombieDistanceSquared = 225;
   public static int canSeeZombieDistanceSquared = 100;
   public static int seeZombieDistanceSquared = 25;
   private static boolean canChangeTarget = true;
   private static int updatePeriod = 100;
   private static int attackPeriod = 1000;
   public static int maxZombiesPerUpdate = 300;
   private final ByteBuffer bb = ByteBuffer.allocate(1000000);
   private UpdateLimit updateLimiter = new UpdateLimit(updatePeriod);
   private UpdateLimit attackLimiter = new UpdateLimit(attackPeriod);
   private Player player = null;
   private final ZombiePacket zombiePacket = new ZombiePacket();
   private HashSet<Short> authoriseZombiesCurrent = new HashSet<>();
   private HashSet<Short> authoriseZombiesLast = new HashSet<>();
   private final ArrayList<Short> unknownZombies = new ArrayList<>();
   private final HashMap<Integer, Zombie> zombies = new HashMap<>();
   private final ArrayDeque<Zombie> zombies4Add = new ArrayDeque<>();
   private final ArrayDeque<Zombie> zombies4Delete = new ArrayDeque<>();
   private final HashSet<Short> authoriseZombies = new HashSet<>();
   private final ArrayDeque<Zombie> SendQueue = new ArrayDeque<>();
   private static Vector2 tmpDir = new Vector2();

   public FakeClientManager$ZombieSimulator(Player var1) {
      this.player = var1;
   }

   public void becomeLocal(Zombie var1) {
      var1.localOwnership = true;
   }

   public void becomeRemote(Zombie var1) {
      var1.localOwnership = false;
   }

   public void clear() {
      HashSet var1 = this.authoriseZombiesCurrent;
      this.authoriseZombiesCurrent = this.authoriseZombiesLast;
      this.authoriseZombiesLast = var1;
      this.authoriseZombiesLast.removeIf(var1x -> this.zombies.get(Integer.valueOf(var1x)) == null);
      this.authoriseZombiesCurrent.clear();
   }

   public void add(short var1) {
      this.authoriseZombiesCurrent.add(var1);
   }

   public void receivePacket(ByteBuffer var1) {
      short var2 = var1.getShort();

      for (short var3 = 0; var3 < var2; var3++) {
         this.parseZombie(var1);
      }
   }

   private void parseZombie(ByteBuffer var1) {
      ZombiePacket var2 = this.zombiePacket;
      var2.parse(var1, null);
      Zombie var3 = this.zombies.get(Integer.valueOf(var2.id));
      if (!this.authoriseZombies.contains(var2.id) || var3 == null) {
         if (var3 == null) {
            var3 = new Zombie(var2.id);
            this.zombies4Add.add(var3);
            FakeClientManager.trace(this.player.movement.id, String.format("New zombie %s", var3.OnlineID));
         }

         var3.lastUpdate = System.currentTimeMillis();
         var3.zombiePacket.copy(var2);
         var3.x = var2.realX;
         var3.y = var2.realY;
         var3.z = var2.realZ;
      }
   }

   public void process() {
      SetView var1 = Sets.difference(this.authoriseZombiesCurrent, this.authoriseZombiesLast);
      UnmodifiableIterator var2 = var1.iterator();

      while (var2.hasNext()) {
         Short var3 = (Short)var2.next();
         Zombie var4 = this.zombies.get(Integer.valueOf(var3));
         if (var4 != null) {
            this.becomeLocal(var4);
         } else if (!this.unknownZombies.contains(var3)) {
            this.unknownZombies.add(var3);
         }
      }

      SetView var8 = Sets.difference(this.authoriseZombiesLast, this.authoriseZombiesCurrent);
      UnmodifiableIterator var9 = var8.iterator();

      while (var9.hasNext()) {
         Short var11 = (Short)var9.next();
         Zombie var5 = this.zombies.get(Integer.valueOf(var11));
         if (var5 != null) {
            this.becomeRemote(var5);
         }
      }

      synchronized (this.authoriseZombies) {
         this.authoriseZombies.clear();
         this.authoriseZombies.addAll(this.authoriseZombiesCurrent);
      }
   }

   public void send() {
      if (this.authoriseZombies.size() != 0 || this.unknownZombies.size() != 0) {
         if (this.SendQueue.isEmpty()) {
            synchronized (this.authoriseZombies) {
               for (Short var3 : this.authoriseZombies) {
                  Zombie var4 = this.zombies.get(Integer.valueOf(var3));
                  if (var4 != null && var4.OnlineID != -1) {
                     this.SendQueue.add(var4);
                  }
               }
            }
         }

         this.bb.clear();
         this.bb.putShort((short)0);
         int var7 = this.unknownZombies.size();
         this.bb.putShort((short)var7);

         for (int var8 = 0; var8 < this.unknownZombies.size(); var8++) {
            if (this.unknownZombies.get(var8) == null) {
               return;
            }

            this.bb.putShort(this.unknownZombies.get(var8));
         }

         this.unknownZombies.clear();
         int var9 = this.bb.position();
         this.bb.putShort((short)maxZombiesPerUpdate);
         int var10 = 0;

         while (!this.SendQueue.isEmpty()) {
            Zombie var11 = this.SendQueue.poll();
            if (var11.OnlineID != -1) {
               var11.zombiePacket.write(this.bb);
               if (++var10 >= maxZombiesPerUpdate) {
                  break;
               }
            }
         }

         if (var10 < maxZombiesPerUpdate) {
            int var12 = this.bb.position();
            this.bb.position(var9);
            this.bb.putShort((short)var10);
            this.bb.position(var12);
         }

         if (var10 > 0 || var7 > 0) {
            ByteBuffer var13 = this.player.client.network.startPacket();
            this.player.client.doPacket(PacketType.ZombieSimulation.getId(), var13);
            var13.put(this.bb.array(), 0, this.bb.position());
            this.player.client.network.endPacketSuperHighUnreliable(this.player.client.connectionGUID);
         }
      }
   }

   private void simulate(Integer var1, Zombie var2) {
      float var3 = IsoUtils.DistanceToSquared(this.player.x, this.player.y, var2.x, var2.y);
      if (!(var3 > deleteZombieDistanceSquared) && (var2.localOwnership || var2.lastUpdate + 5000L >= System.currentTimeMillis())) {
         tmpDir.set(-var2.x + this.player.x, -var2.y + this.player.y);
         if (var2.isMoving) {
            float var4 = 0.2F;
            var2.x = PZMath.lerp(var2.x, var2.zombiePacket.x, var4);
            var2.y = PZMath.lerp(var2.y, var2.zombiePacket.y, var4);
            var2.z = 0.0F;
            var2.dir = IsoDirections.fromAngle(tmpDir);
         }

         if (canChangeTarget) {
            synchronized (this.player.playerManager.players) {
               for (RemotePlayer var6 : this.player.playerManager.players.values()) {
                  float var7 = IsoUtils.DistanceToSquared(var6.x, var6.y, var2.x, var2.y);
                  if (var7 < seeZombieDistanceSquared) {
                     var2.zombiePacket.target = var6.OnlineID;
                     break;
                  }
               }
            }
         } else {
            var2.zombiePacket.target = this.player.OnlineID;
         }

         if (behaviour == Behaviour.Stay) {
            var2.isMoving = false;
         } else if (behaviour == Behaviour.Normal) {
            if (var3 > forgotZombieDistanceSquared) {
               var2.isMoving = false;
            }

            if (var3 < canSeeZombieDistanceSquared && (Rand.Next(100) < 1 || var2.dir == IsoDirections.fromAngle(tmpDir))) {
               var2.isMoving = true;
            }

            if (var3 < seeZombieDistanceSquared) {
               var2.isMoving = true;
            }
         } else {
            var2.isMoving = true;
         }

         float var11 = 0.0F;
         if (var2.isMoving) {
            Vector2 var13 = var2.dir.ToVector();
            var11 = 3.0F;
            if (var3 < 100.0F) {
               var11 = 6.0F;
            }

            long var14 = System.currentTimeMillis() - var2.lastUpdate;
            var2.zombiePacket.x = var2.x + var13.x * (float)var14 * 0.001F * var11;
            var2.zombiePacket.y = var2.y + var13.y * (float)var14 * 0.001F * var11;
            var2.zombiePacket.z = (byte)var2.z;
            var2.zombiePacket.moveType = PredictionTypes.Moving;
         } else {
            var2.zombiePacket.x = var2.x;
            var2.zombiePacket.y = var2.y;
            var2.zombiePacket.z = (byte)var2.z;
            var2.zombiePacket.moveType = PredictionTypes.Static;
         }

         var2.zombiePacket.booleanVariables = 0;
         if (var3 < 100.0F) {
            var2.zombiePacket.booleanVariables = (short)(var2.zombiePacket.booleanVariables | 2);
         }

         var2.zombiePacket.timeSinceSeenFlesh = var2.isMoving ? 0 : 100000;
         var2.zombiePacket.smParamTargetAngle = 0;
         var2.zombiePacket.speedMod = 1000;
         var2.zombiePacket.walkType = WalkType.values()[var2.walkType];
         var2.zombiePacket.realX = var2.x;
         var2.zombiePacket.realY = var2.y;
         var2.zombiePacket.realZ = (byte)var2.z;
         var2.zombiePacket.realHealth = (short)(var2.health * 1000.0F);
         var2.zombiePacket.realState = ZombieState.fromString("fakezombie-" + behaviour.toString().toLowerCase());
         if (var2.isMoving) {
            var2.zombiePacket.pfbType = 1;
            var2.zombiePacket.pfbTarget = this.player.OnlineID;
         } else {
            var2.zombiePacket.pfbType = 0;
         }

         if (var3 < 2.0F && this.attackLimiter.Check()) {
            var2.health = var2.health - Player.damage;
            this.sendHitCharacter(var2, Player.damage);
            if (var2.health <= 0.0F) {
               this.player.client.sendChatMessage("DIE!!");
               this.zombies4Delete.add(var2);
            }
         }

         var2.lastUpdate = System.currentTimeMillis();
      } else {
         this.zombies4Delete.add(var2);
      }
   }

   private void writeHitInfoToZombie(ByteBuffer var1, short var2, float var3, float var4, float var5) {
      var1.put((byte)2);
      var1.putShort(var2);
      var1.put((byte)0);
      var1.putFloat(var3);
      var1.putFloat(var4);
      var1.putFloat(0.0F);
      var1.putFloat(var5);
      var1.putFloat(1.0F);
      var1.putInt(100);
   }

   private void sendHitCharacter(Zombie var1, float var2) {
      boolean var3 = false;
      ByteBuffer var4 = this.player.client.network.startPacket();
      this.player.client.doPacket(PacketType.HitCharacter.getId(), var4);
      var4.put((byte)3);
      var4.putShort(this.player.OnlineID);
      var4.putShort((short)0);
      var4.putFloat(this.player.x);
      var4.putFloat(this.player.y);
      var4.putFloat(this.player.z);
      var4.putFloat(this.player.direction.x);
      var4.putFloat(this.player.direction.y);
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      var4.putShort((short)((this.player.weapon_isBareHeads ? 2 : 0) + (var3 ? 8 : 0)));
      var4.putFloat(1.0F);
      var4.putFloat(1.0F);
      var4.putFloat(1.0F);
      FakeClientManager.WriteStringUTF(var4, "default");
      byte var5 = 0;
      var5 = (byte)(var5 | (byte)(this.player.weapon_isBareHeads ? 9 : 0));
      var4.put(var5);
      var4.put((byte)0);
      var4.putShort((short)0);
      var4.putFloat(1.0F);
      var4.putInt(0);
      byte var6 = 1;
      var4.put(var6);

      for (int var7 = 0; var7 < var6; var7++) {
         this.writeHitInfoToZombie(var4, var1.OnlineID, var1.x, var1.y, var2);
      }

      var6 = 0;
      var4.put(var6);
      var6 = 1;
      var4.put(var6);

      for (int var11 = 0; var11 < var6; var11++) {
         this.writeHitInfoToZombie(var4, var1.OnlineID, var1.x, var1.y, var2);
      }

      if (!this.player.weapon_isBareHeads) {
         var4.put((byte)0);
      } else {
         var4.put((byte)1);
         var4.putShort(this.player.registry_id);
         var4.put((byte)1);
         var4.putInt(this.player.weapon_id);
         var4.put((byte)0);
         var4.putInt(0);
         var4.putInt(0);
      }

      var4.putShort(var1.OnlineID);
      var4.putShort((short)(var2 >= var1.health ? 3 : 0));
      var4.putFloat(var1.x);
      var4.putFloat(var1.y);
      var4.putFloat(var1.z);
      var4.putFloat(var1.dir.ToVector().x);
      var4.putFloat(var1.dir.ToVector().y);
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      var4.putShort((short)0);
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "FRONT");
      var4.put((byte)0);
      var4.putFloat(var2);
      var4.putFloat(1.0F);
      var4.putFloat(this.player.direction.x);
      var4.putFloat(this.player.direction.y);
      var4.putFloat(1.0F);
      var4.put((byte)0);
      if (tmpDir.getLength() > 0.0F) {
         var1.dropPositionX = var1.x + tmpDir.x / tmpDir.getLength();
         var1.dropPositionY = var1.y + tmpDir.y / tmpDir.getLength();
      } else {
         var1.dropPositionX = var1.x;
         var1.dropPositionY = var1.y;
      }

      var4.putFloat(var1.dropPositionX);
      var4.putFloat(var1.dropPositionY);
      var4.put((byte)var1.z);
      var4.putFloat(var1.dir.toAngle());
      this.player.client.network.endPacketImmediate(this.player.client.connectionGUID);
   }

   private void sendSendDeadZombie(Zombie var1) {
      ByteBuffer var2 = this.player.client.network.startPacket();
      this.player.client.doPacket(PacketType.ZombieDeath.getId(), var2);
      var2.putShort(var1.OnlineID);
      var2.putFloat(var1.x);
      var2.putFloat(var1.y);
      var2.putFloat(var1.z);
      var2.putFloat(var1.dir.toAngle());
      var2.put((byte)var1.dir.index());
      var2.put((byte)0);
      var2.put((byte)0);
      var2.put((byte)0);
      this.player.client.network.endPacketImmediate(this.player.client.connectionGUID);
   }

   public void simulateAll() {
      while (!this.zombies4Add.isEmpty()) {
         Zombie var1 = this.zombies4Add.poll();
         this.zombies.put(Integer.valueOf(var1.OnlineID), var1);
      }

      this.zombies.forEach(this::simulate);

      while (!this.zombies4Delete.isEmpty()) {
         Zombie var2 = this.zombies4Delete.poll();
         this.zombies.remove(Integer.valueOf(var2.OnlineID));
      }
   }

   public void update() {
      if (this.updateLimiter.Check()) {
         this.simulateAll();
         this.send();
      }
   }
}
