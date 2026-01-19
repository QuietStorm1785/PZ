package zombie.network;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import zombie.characters.IsoPlayer;
import zombie.characters.BodyDamage.BodyDamage;
import zombie.characters.BodyDamage.BodyPart;
import zombie.core.Core;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugLog;
import zombie.network.BodyDamageSync.Updater;
import zombie.network.PacketTypes.PacketType;

public class BodyDamageSync {
   public static final byte BD_Health = 1;
   public static final byte BD_bandaged = 2;
   public static final byte BD_bitten = 3;
   public static final byte BD_bleeding = 4;
   public static final byte BD_IsBleedingStemmed = 5;
   public static final byte BD_IsCortorised = 6;
   public static final byte BD_scratched = 7;
   public static final byte BD_stitched = 8;
   public static final byte BD_deepWounded = 9;
   public static final byte BD_IsInfected = 10;
   public static final byte BD_IsFakeInfected = 11;
   public static final byte BD_bandageLife = 12;
   public static final byte BD_scratchTime = 13;
   public static final byte BD_biteTime = 14;
   public static final byte BD_alcoholicBandage = 15;
   public static final byte BD_woundInfectionLevel = 16;
   public static final byte BD_infectedWound = 17;
   public static final byte BD_bleedingTime = 18;
   public static final byte BD_deepWoundTime = 19;
   public static final byte BD_haveGlass = 20;
   public static final byte BD_stitchTime = 21;
   public static final byte BD_alcoholLevel = 22;
   public static final byte BD_additionalPain = 23;
   public static final byte BD_bandageType = 24;
   public static final byte BD_getBandageXp = 25;
   public static final byte BD_getStitchXp = 26;
   public static final byte BD_getSplintXp = 27;
   public static final byte BD_fractureTime = 28;
   public static final byte BD_splint = 29;
   public static final byte BD_splintFactor = 30;
   public static final byte BD_haveBullet = 31;
   public static final byte BD_burnTime = 32;
   public static final byte BD_needBurnWash = 33;
   public static final byte BD_lastTimeBurnWash = 34;
   public static final byte BD_splintItem = 35;
   public static final byte BD_plantainFactor = 36;
   public static final byte BD_comfreyFactor = 37;
   public static final byte BD_garlicFactor = 38;
   public static final byte BD_cut = 39;
   public static final byte BD_cutTime = 40;
   public static final byte BD_stiffness = 41;
   public static final byte BD_BodyDamage = 50;
   private static final byte BD_START = 64;
   private static final byte BD_END = 65;
   private static final byte PKT_START_UPDATING = 1;
   private static final byte PKT_STOP_UPDATING = 2;
   private static final byte PKT_UPDATE = 3;
   public static BodyDamageSync instance = new BodyDamageSync();
   private ArrayList<Updater> updaters = new ArrayList<>();

   private static void noise(String var0) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
         DebugLog.log("BodyDamage: " + var0);
      }
   }

   public void startSendingUpdates(short var1, short var2) {
      if (GameClient.bClient) {
         noise("start sending updates to " + var2);

         for (int var3 = 0; var3 < this.updaters.size(); var3++) {
            Updater var4 = this.updaters.get(var3);
            if (var4.localIndex == var1 && var4.remoteID == var2) {
               return;
            }
         }

         IsoPlayer var5 = IsoPlayer.players[var1];
         Updater var6 = new Updater();
         var6.localIndex = var1;
         var6.remoteID = var2;
         var6.bdLocal = var5.getBodyDamage();
         var6.bdSent = new BodyDamage(null);
         this.updaters.add(var6);
      }
   }

   public void stopSendingUpdates(short var1, short var2) {
      if (GameClient.bClient) {
         noise("stop sending updates to " + var2);

         for (int var3 = 0; var3 < this.updaters.size(); var3++) {
            Updater var4 = this.updaters.get(var3);
            if (var4.localIndex == var1 && var4.remoteID == var2) {
               this.updaters.remove(var3);
               return;
            }
         }
      }
   }

   public void startReceivingUpdates(short var1) {
      if (GameClient.bClient) {
         noise("start receiving updates from " + var1 + " to " + IsoPlayer.players[0].getOnlineID());
         ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.BodyDamageUpdate.doPacket(var2);
         var2.putByte((byte)1);
         var2.putShort(IsoPlayer.players[0].getOnlineID());
         var2.putShort(var1);
         PacketType.BodyDamageUpdate.send(GameClient.connection);
      }
   }

   public void stopReceivingUpdates(short var1) {
      if (GameClient.bClient) {
         noise("stop receiving updates from " + var1 + " to " + IsoPlayer.players[0].getOnlineID());
         ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.BodyDamageUpdate.doPacket(var2);
         var2.putByte((byte)2);
         var2.putShort(IsoPlayer.players[0].getOnlineID());
         var2.putShort(var1);
         PacketType.BodyDamageUpdate.send(GameClient.connection);
      }
   }

   public void update() {
      if (GameClient.bClient) {
         for (int var1 = 0; var1 < this.updaters.size(); var1++) {
            Updater var2 = this.updaters.get(var1);
            var2.update();
         }
      }
   }

   public void serverPacket(ByteBuffer var1) {
      byte var2 = var1.get();
      if (var2 == 1) {
         short var9 = var1.getShort();
         short var11 = var1.getShort();
         Long var13 = (Long)GameServer.IDToAddressMap.get(var11);
         if (var13 != null) {
            UdpConnection var15 = GameServer.udpEngine.getActiveConnection(var13);
            if (var15 != null) {
               ByteBufferWriter var17 = var15.startPacket();
               PacketType.BodyDamageUpdate.doPacket(var17);
               var17.putByte((byte)1);
               var17.putShort(var9);
               var17.putShort(var11);
               PacketType.BodyDamageUpdate.send(var15);
            }
         }
      } else if (var2 == 2) {
         short var8 = var1.getShort();
         short var10 = var1.getShort();
         Long var12 = (Long)GameServer.IDToAddressMap.get(var10);
         if (var12 != null) {
            UdpConnection var14 = GameServer.udpEngine.getActiveConnection(var12);
            if (var14 != null) {
               ByteBufferWriter var16 = var14.startPacket();
               PacketType.BodyDamageUpdate.doPacket(var16);
               var16.putByte((byte)2);
               var16.putShort(var8);
               var16.putShort(var10);
               PacketType.BodyDamageUpdate.send(var14);
            }
         }
      } else if (var2 == 3) {
         short var3 = var1.getShort();
         short var4 = var1.getShort();
         Long var5 = (Long)GameServer.IDToAddressMap.get(var4);
         if (var5 != null) {
            UdpConnection var6 = GameServer.udpEngine.getActiveConnection(var5);
            if (var6 != null) {
               ByteBufferWriter var7 = var6.startPacket();
               PacketType.BodyDamageUpdate.doPacket(var7);
               var7.putByte((byte)3);
               var7.putShort(var3);
               var7.putShort(var4);
               var7.bb.put(var1);
               PacketType.BodyDamageUpdate.send(var6);
            }
         }
      }
   }

   public void clientPacket(ByteBuffer var1) {
      byte var2 = var1.get();
      if (var2 == 1) {
         short var12 = var1.getShort();
         short var14 = var1.getShort();

         for (short var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
            IsoPlayer var18 = IsoPlayer.players[var16];
            noise("looking for " + var14 + " testing player ID=" + var18.getOnlineID());
            if (var18 != null && var18.isAlive() && var18.getOnlineID() == var14) {
               this.startSendingUpdates(var16, var12);
               break;
            }
         }
      } else if (var2 == 2) {
         short var11 = var1.getShort();
         short var13 = var1.getShort();

         for (short var15 = 0; var15 < IsoPlayer.numPlayers; var15++) {
            IsoPlayer var17 = IsoPlayer.players[var15];
            if (var17 != null && var17.getOnlineID() == var13) {
               this.stopSendingUpdates(var15, var11);
               break;
            }
         }
      } else if (var2 == 3) {
         short var3 = var1.getShort();
         short var4 = var1.getShort();
         IsoPlayer var5 = (IsoPlayer)GameClient.IDToPlayerMap.get(var3);
         if (var5 != null) {
            BodyDamage var6 = var5.getBodyDamageRemote();
            byte var7 = var1.get();
            if (var7 == 50) {
               var6.setOverallBodyHealth(var1.getFloat());
               var6.setRemotePainLevel(var1.get());
               var6.IsFakeInfected = var1.get() == 1;
               var6.InfectionLevel = var1.getFloat();
               var7 = var1.get();
            }

            while (var7 == 64) {
               byte var8 = var1.get();
               BodyPart var9 = (BodyPart)var6.BodyParts.get(var8);

               for (byte var10 = var1.get(); var10 != 65; var10 = var1.get()) {
                  var9.sync(var1, var10);
               }

               var7 = var1.get();
            }
         }
      }
   }
}
