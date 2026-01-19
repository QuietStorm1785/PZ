package zombie.popman;

import com.google.common.collect.Sets;
import com.google.common.collect.UnmodifiableIterator;
import com.google.common.collect.Sets.SetView;
import java.nio.ByteBuffer;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import zombie.VirtualZombieManager;
import zombie.ai.states.ZombieHitReactionState;
import zombie.ai.states.ZombieOnGroundState;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.characters.NetworkZombieVariables;
import zombie.core.Core;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.core.utils.UpdateLimit;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.debug.DebugType;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.objects.IsoDeadBody;
import zombie.network.GameClient;
import zombie.network.PacketTypes.PacketType;
import zombie.network.packets.ZombiePacket;

public class NetworkZombieSimulator {
   public static final int MAX_ZOMBIES_PER_UPDATE = 300;
   private static final NetworkZombieSimulator instance = new NetworkZombieSimulator();
   private static final ZombiePacket zombiePacket = new ZombiePacket();
   private final ByteBuffer bb = ByteBuffer.allocate(1000000);
   private final ArrayList<Short> unknownZombies = new ArrayList<>();
   private final HashSet<Short> authoriseZombies = new HashSet<>();
   private final ArrayDeque<IsoZombie> SendQueue = new ArrayDeque<>();
   private final ArrayDeque<IsoZombie> ExtraSendQueue = new ArrayDeque<>();
   private HashSet<Short> authoriseZombiesCurrent = new HashSet<>();
   private HashSet<Short> authoriseZombiesLast = new HashSet<>();
   UpdateLimit ZombieSimulationReliableLimit = new UpdateLimit(1000L);

   public static NetworkZombieSimulator getInstance() {
      return instance;
   }

   public int getAuthorizedZombieCount() {
      return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(var0 -> var0.authOwner == GameClient.connection).count();
   }

   public int getUnauthorizedZombieCount() {
      return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(var0 -> var0.authOwner == null).count();
   }

   public void clear() {
      HashSet var1 = this.authoriseZombiesCurrent;
      this.authoriseZombiesCurrent = this.authoriseZombiesLast;
      this.authoriseZombiesLast = var1;
      this.authoriseZombiesLast.removeIf(var0 -> GameClient.getZombie(var0) == null);
      this.authoriseZombiesCurrent.clear();
   }

   public void addExtraUpdate(IsoZombie var1) {
      if (var1.authOwner == GameClient.connection && !this.ExtraSendQueue.contains(var1)) {
         this.ExtraSendQueue.add(var1);
      }
   }

   public void add(short var1) {
      this.authoriseZombiesCurrent.add(var1);
   }

   public void added() {
      SetView var1 = Sets.difference(this.authoriseZombiesCurrent, this.authoriseZombiesLast);
      UnmodifiableIterator var2 = var1.iterator();

      while (var2.hasNext()) {
         Short var3 = (Short)var2.next();
         IsoZombie var4 = GameClient.getZombie(var3);
         if (var4 != null && var4.OnlineID == var3) {
            this.becomeLocal(var4);
         } else if (!this.unknownZombies.contains(var3)) {
            this.unknownZombies.add(var3);
         }
      }

      SetView var8 = Sets.difference(this.authoriseZombiesLast, this.authoriseZombiesCurrent);
      UnmodifiableIterator var9 = var8.iterator();

      while (var9.hasNext()) {
         Short var11 = (Short)var9.next();
         IsoZombie var5 = GameClient.getZombie(var11);
         if (var5 != null) {
            this.becomeRemote(var5);
         }
      }

      synchronized (this.authoriseZombies) {
         this.authoriseZombies.clear();
         this.authoriseZombies.addAll(this.authoriseZombiesCurrent);
      }
   }

   public void becomeLocal(IsoZombie var1) {
      var1.lastRemoteUpdate = 0;
      var1.authOwner = GameClient.connection;
      var1.authOwnerPlayer = IsoPlayer.getInstance();
      var1.networkAI.setUpdateTimer(0.0F);
      var1.AllowRepathDelay = 0.0F;
      var1.networkAI.mindSync.restorePFBTarget();
   }

   public void becomeRemote(IsoZombie var1) {
      if (var1.isDead() && var1.authOwner == GameClient.connection) {
         var1.getNetworkCharacterAI().setLocal(true);
      }

      var1.lastRemoteUpdate = 0;
      var1.authOwner = null;
      var1.authOwnerPlayer = null;
      if (var1.group != null) {
         var1.group.remove(var1);
      }
   }

   public boolean isZombieSimulated(Short var1) {
      synchronized (this.authoriseZombies) {
         return this.authoriseZombies.contains(var1);
      }
   }

   public void receivePacket(ByteBuffer var1, UdpConnection var2) {
      if (DebugOptions.instance.Network.Client.UpdateZombiesFromPacket.getValue()) {
         short var3 = var1.getShort();

         for (short var4 = 0; var4 < var3; var4++) {
            this.parseZombie(var1, var2);
         }
      }
   }

   private void parseZombie(ByteBuffer var1, UdpConnection var2) {
      ZombiePacket var3 = zombiePacket;
      var3.parse(var1, var2);
      if (var3.id == -1) {
         DebugLog.General.error("NetworkZombieSimulator.parseZombie id=" + var3.id);
      } else {
         try {
            IsoZombie var4 = (IsoZombie)GameClient.IDToZombieMap.get(var3.id);
            if (var4 == null) {
               if (IsoDeadBody.isDead(var3.id)) {
                  DebugLog.Death.debugln("Skip dead zombie creation id=%d", var3.id);
                  return;
               }

               IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var3.realX, var3.realY, var3.realZ);
               if (var5 != null) {
                  VirtualZombieManager.instance.choices.clear();
                  VirtualZombieManager.instance.choices.add(var5);
                  var4 = VirtualZombieManager.instance.createRealZombieAlways(var3.descriptorID, IsoDirections.getRandom().index(), false);
                  DebugLog.log(DebugType.ActionSystem, "ParseZombie: CreateRealZombieAlways id=" + var3.id);
                  if (var4 != null) {
                     var4.setFakeDead(false);
                     var4.OnlineID = var3.id;
                     GameClient.IDToZombieMap.put(var3.id, var4);
                     var4.lx = var4.nx = var4.x = var3.realX;
                     var4.ly = var4.ny = var4.y = var3.realY;
                     var4.lz = var4.z = var3.realZ;
                     var4.setForwardDirection(var4.dir.ToVector());
                     var4.setCurrent(var5);
                     var4.networkAI.targetX = var3.x;
                     var4.networkAI.targetY = var3.y;
                     var4.networkAI.targetZ = var3.z;
                     var4.networkAI.predictionType = var3.moveType;
                     var4.networkAI.reanimatedBodyID = var3.reanimatedBodyID;
                     NetworkZombieVariables.setInt(var4, (short)0, var3.realHealth);
                     NetworkZombieVariables.setInt(var4, (short)2, var3.speedMod);
                     NetworkZombieVariables.setInt(var4, (short)1, var3.target);
                     NetworkZombieVariables.setInt(var4, (short)3, var3.timeSinceSeenFlesh);
                     NetworkZombieVariables.setInt(var4, (short)4, var3.smParamTargetAngle);
                     NetworkZombieVariables.setBooleanVariables(var4, var3.booleanVariables);
                     if (var4.isKnockedDown()) {
                        var4.setOnFloor(true);
                        var4.changeState(ZombieOnGroundState.instance());
                     }

                     var4.setWalkType(var3.walkType.toString());
                     var4.realState = var3.realState;
                     if (var4.isReanimatedPlayer()) {
                        IsoDeadBody var6 = IsoDeadBody.getDeadBody(var4.networkAI.reanimatedBodyID);
                        if (var6 != null) {
                           var4.setDir(var6.getDir());
                           var4.setForwardDirection(var6.getDir().ToVector());
                           var4.setFallOnFront(var6.isFallOnFront());
                        }

                        var4.getStateMachine().changeState(ZombieOnGroundState.instance(), null);
                        var4.bNeverDoneAlpha = false;
                     }

                     for (int var9 = 0; var9 < IsoPlayer.numPlayers; var9++) {
                        IsoPlayer var7 = IsoPlayer.players[var9];
                        if (var5.isCanSee(var9)) {
                           var4.setAlphaAndTarget(var9, 1.0F);
                        }

                        if (var7 != null && var7.ReanimatedCorpseID == var3.id && var3.id != -1) {
                           var7.ReanimatedCorpseID = -1;
                           var7.ReanimatedCorpse = var4;
                        }
                     }

                     var4.networkAI.mindSync.parse(var3);
                  } else {
                     DebugLog.log("Error: VirtualZombieManager can't create zombie");
                  }
               }

               if (var4 == null) {
                  return;
               }
            }

            if (getInstance().isZombieSimulated(var4.OnlineID)) {
               var4.authOwner = GameClient.connection;
               var4.authOwnerPlayer = IsoPlayer.getInstance();
               return;
            }

            var4.authOwner = null;
            var4.authOwnerPlayer = null;
            if (!var4.networkAI.isSetVehicleHit() || !var4.isCurrentState(ZombieHitReactionState.instance())) {
               var4.networkAI.parse(var3);
               var4.networkAI.mindSync.parse(var3);
            }

            var4.lastRemoteUpdate = 0;
            if (!IsoWorld.instance.CurrentCell.getZombieList().contains(var4)) {
               IsoWorld.instance.CurrentCell.getZombieList().add(var4);
            }

            if (!IsoWorld.instance.CurrentCell.getObjectList().contains(var4)) {
               IsoWorld.instance.CurrentCell.getObjectList().add(var4);
            }
         } catch (Exception var8) {
            var8.printStackTrace();
         }
      }
   }

   public boolean anyUnknownZombies() {
      return this.unknownZombies.size() > 0;
   }

   public void send() {
      if (this.authoriseZombies.size() != 0 || this.unknownZombies.size() != 0) {
         if (this.SendQueue.isEmpty()) {
            synchronized (this.authoriseZombies) {
               for (Short var3 : this.authoriseZombies) {
                  IsoZombie var4 = GameClient.getZombie(var3);
                  if (var4 != null && var4.OnlineID != -1) {
                     this.SendQueue.add(var4);
                  }
               }
            }
         }

         this.bb.clear();
         synchronized (ZombieCountOptimiser.zombiesForDelete) {
            int var11 = ZombieCountOptimiser.zombiesForDelete.size();
            this.bb.putShort((short)var11);

            for (int var15 = 0; var15 < var11; var15++) {
               this.bb.putShort(((IsoZombie)ZombieCountOptimiser.zombiesForDelete.get(var15)).OnlineID);
            }

            ZombieCountOptimiser.zombiesForDelete.clear();
         }

         int var10 = this.unknownZombies.size();
         this.bb.putShort((short)var10);

         for (int var12 = 0; var12 < var10; var12++) {
            this.bb.putShort(this.unknownZombies.get(var12));
         }

         this.unknownZombies.clear();
         int var13 = this.bb.position();
         this.bb.putShort((short)300);
         int var16 = 0;

         while (!this.SendQueue.isEmpty()) {
            IsoZombie var17 = this.SendQueue.poll();
            this.ExtraSendQueue.remove(var17);
            var17.zombiePacket.set(var17);
            if (var17.OnlineID != -1) {
               var17.zombiePacket.write(this.bb);
               var17.networkAI.targetX = var17.realx = var17.x;
               var17.networkAI.targetY = var17.realy = var17.y;
               var17.networkAI.targetZ = var17.realz = (byte)var17.z;
               var17.realdir = var17.getDir();
               if (++var16 >= 300) {
                  break;
               }
            }
         }

         if (var16 < 300) {
            int var18 = this.bb.position();
            this.bb.position(var13);
            this.bb.putShort((short)var16);
            this.bb.position(var18);
         }

         if (var16 > 0 || var10 > 0) {
            ByteBufferWriter var19 = GameClient.connection.startPacket();
            PacketType var5;
            if (var10 > 0 && this.ZombieSimulationReliableLimit.Check()) {
               var5 = PacketType.ZombieSimulationReliable;
            } else {
               var5 = PacketType.ZombieSimulation;
            }

            var5.doPacket(var19);
            var19.bb.put(this.bb.array(), 0, this.bb.position());
            var5.send(GameClient.connection);
         }

         if (!this.ExtraSendQueue.isEmpty()) {
            this.bb.clear();
            this.bb.putShort((short)0);
            this.bb.putShort((short)0);
            var13 = this.bb.position();
            this.bb.putShort((short)0);
            int var20 = 0;

            while (!this.ExtraSendQueue.isEmpty()) {
               IsoZombie var21 = this.ExtraSendQueue.poll();
               var21.zombiePacket.set(var21);
               if (var21.OnlineID != -1) {
                  var21.zombiePacket.write(this.bb);
                  var21.networkAI.targetX = var21.realx = var21.x;
                  var21.networkAI.targetY = var21.realy = var21.y;
                  var21.networkAI.targetZ = var21.realz = (byte)var21.z;
                  var21.realdir = var21.getDir();
                  var20++;
               }
            }

            int var22 = this.bb.position();
            this.bb.position(var13);
            this.bb.putShort((short)var20);
            this.bb.position(var22);
            if (var20 > 0) {
               ByteBufferWriter var6 = GameClient.connection.startPacket();
               PacketType.ZombieSimulation.doPacket(var6);
               var6.bb.put(this.bb.array(), 0, this.bb.position());
               PacketType.ZombieSimulation.send(GameClient.connection);
            }
         }
      }
   }

   public void remove(IsoZombie var1) {
      if (var1 != null && var1.OnlineID != -1) {
         GameClient.IDToZombieMap.remove(var1.OnlineID);
      }
   }

   public void clearTargetAuth(IsoPlayer var1) {
      if (Core.bDebug) {
         DebugLog.log(DebugType.Multiplayer, "Clear zombies target and auth for player id=" + var1.getOnlineID());
      }

      if (GameClient.bClient) {
         for (IsoZombie var3 : GameClient.IDToZombieMap.valueCollection()) {
            if (var3.target == var1) {
               var3.setTarget(null);
            }
         }
      }
   }
}
