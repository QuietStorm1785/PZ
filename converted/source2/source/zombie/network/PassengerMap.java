package zombie.network;

import java.nio.ByteBuffer;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.network.PacketTypes.PacketType;
import zombie.network.PassengerMap.DriverLocal;
import zombie.network.PassengerMap.PassengerLocal;
import zombie.network.PassengerMap.PassengerRemote;
import zombie.vehicles.BaseVehicle;

public final class PassengerMap {
   private static final int CHUNKS = 7;
   private static final int MAX_PASSENGERS = 16;
   private static final PassengerLocal[] perPlayerPngr = new PassengerLocal[4];
   private static final DriverLocal[] perPlayerDriver = new DriverLocal[4];

   public static void updatePassenger(IsoPlayer var0) {
      if (var0 != null && var0.getVehicle() != null && !var0.getVehicle().isDriver(var0)) {
         IsoGameCharacter var1 = var0.getVehicle().getDriver();
         if (var1 instanceof IsoPlayer && !((IsoPlayer)var1).isLocalPlayer()) {
            PassengerLocal var2 = perPlayerPngr[var0.PlayerIndex];
            var2.chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[var0.PlayerIndex];
            var2.updateLoaded();
         }
      }
   }

   public static void serverReceivePacket(ByteBuffer var0, UdpConnection var1) {
      byte var2 = var0.get();
      int var3 = var0.getInt();
      int var4 = var0.getInt();
      long var5 = var0.getLong();
      IsoPlayer var7 = var1.players[var2];
      if (var7 != null && var7.getVehicle() != null) {
         IsoGameCharacter var8 = var7.getVehicle().getDriver();
         if (var8 instanceof IsoPlayer && var8 != var7) {
            UdpConnection var9 = GameServer.getConnectionFromPlayer((IsoPlayer)var8);
            if (var9 != null) {
               ByteBufferWriter var10 = var9.startPacket();
               PacketType.PassengerMap.doPacket(var10);
               var10.putShort(var7.getVehicle().VehicleID);
               var10.putByte((byte)var7.getVehicle().getSeat(var7));
               var10.putInt(var3);
               var10.putInt(var4);
               var10.putLong(var5);
               PacketType.PassengerMap.send(var9);
            }
         }
      }
   }

   public static void clientReceivePacket(ByteBuffer var0) {
      short var1 = var0.getShort();
      byte var2 = var0.get();
      int var3 = var0.getInt();
      int var4 = var0.getInt();
      long var5 = var0.getLong();

      for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
         IsoPlayer var8 = IsoPlayer.players[var7];
         if (var8 != null && var8.getVehicle() != null) {
            BaseVehicle var9 = var8.getVehicle();
            if (var9.VehicleID == var1 && var9.isDriver(var8)) {
               DriverLocal var10 = perPlayerDriver[var7];
               PassengerRemote var11 = var10.passengers[var2];
               if (var11 == null) {
                  var11 = var10.passengers[var2] = new PassengerRemote();
               }

               var11.setLoaded(var3, var4, var5);
            }
         }
      }
   }

   public static boolean isChunkLoaded(BaseVehicle var0, int var1, int var2) {
      if (!GameClient.bClient) {
         return false;
      } else if (var0 != null && var1 >= 0 && var2 >= 0) {
         IsoGameCharacter var3 = var0.getDriver();
         if (var3 instanceof IsoPlayer && ((IsoPlayer)var3).isLocalPlayer()) {
            int var4 = ((IsoPlayer)var3).PlayerIndex;
            DriverLocal var5 = perPlayerDriver[var4];

            for (int var6 = 1; var6 < var0.getMaxPassengers(); var6++) {
               PassengerRemote var7 = var5.passengers[var6];
               if (var7 != null && var7.wx != -1) {
                  IsoGameCharacter var8 = var0.getCharacter(var6);
                  if (var8 instanceof IsoPlayer && !((IsoPlayer)var8).isLocalPlayer()) {
                     int var9 = var7.wx - 3;
                     int var10 = var7.wy - 3;
                     if (var1 >= var9 && var2 >= var10 && var1 < var9 + 7 && var2 < var10 + 7 && (var7.loaded & 1L << var1 - var9 + (var2 - var10) * 7) == 0L) {
                        return false;
                     }
                  } else {
                     var7.wx = -1;
                  }
               }
            }

            return true;
         } else {
            return false;
         }
      } else {
         return false;
      }
   }

   public static void render(int var0) {
      if (GameClient.bClient) {
         IsoPlayer var1 = IsoPlayer.players[var0];
         if (var1 != null && var1.getVehicle() != null) {
            BaseVehicle var2 = var1.getVehicle();
            int var3 = Core.TileScale;
            byte var4 = 10;
            float var5 = 0.1F;
            float var6 = 0.1F;
            float var7 = 0.1F;
            float var8 = 0.75F;
            float var9 = 0.0F;
            DriverLocal var10 = perPlayerDriver[var0];

            for (int var11 = 1; var11 < var2.getMaxPassengers(); var11++) {
               PassengerRemote var12 = var10.passengers[var11];
               if (var12 != null && var12.wx != -1) {
                  IsoGameCharacter var13 = var2.getCharacter(var11);
                  if (var13 instanceof IsoPlayer && !((IsoPlayer)var13).isLocalPlayer()) {
                     for (int var14 = 0; var14 < 7; var14++) {
                        for (int var15 = 0; var15 < 7; var15++) {
                           boolean var16 = (var12.loaded & 1L << var15 + var14 * 7) != 0L;
                           if (!var16) {
                              float var17 = (var12.wx - 3 + var15) * var4;
                              float var18 = (var12.wy - 3 + var14) * var4;
                              float var19 = IsoUtils.XToScreenExact(var17, var18 + var4, var9, 0);
                              float var20 = IsoUtils.YToScreenExact(var17, var18 + var4, var9, 0);
                              SpriteRenderer.instance
                                 .renderPoly(
                                    (int)var19,
                                    (int)var20,
                                    (int)(var19 + var4 * 64 / 2 * var3),
                                    (int)(var20 - var4 * 32 / 2 * var3),
                                    (int)(var19 + var4 * 64 * var3),
                                    (int)var20,
                                    (int)(var19 + var4 * 64 / 2 * var3),
                                    (int)(var20 + var4 * 32 / 2 * var3),
                                    var5,
                                    var6,
                                    var7,
                                    var8
                                 );
                           }
                        }
                     }
                  } else {
                     var12.wx = -1;
                  }
               }
            }
         }
      }
   }

   public static void Reset() {
      for (int var0 = 0; var0 < 4; var0++) {
         PassengerLocal var1 = perPlayerPngr[var0];
         var1.wx = -1;
         DriverLocal var2 = perPlayerDriver[var0];

         for (int var3 = 0; var3 < 16; var3++) {
            PassengerRemote var4 = var2.passengers[var3];
            if (var4 != null) {
               var4.wx = -1;
            }
         }
      }
   }

   static {
      for (int var0 = 0; var0 < 4; var0++) {
         perPlayerPngr[var0] = new PassengerLocal(var0);
         perPlayerDriver[var0] = new DriverLocal();
      }
   }
}
