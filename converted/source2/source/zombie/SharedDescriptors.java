package zombie;

import zombie.SharedDescriptors.Descriptor;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoZombie;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.core.skinnedmodel.visual.ItemVisuals;
import zombie.debug.DebugLog;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.util.Type;

public final class SharedDescriptors {
   private static final int DESCRIPTOR_COUNT = 500;
   private static final int DESCRIPTOR_ID_START = 500;
   private static final byte[] DESCRIPTOR_MAGIC = new byte[]{68, 69, 83, 67};
   private static final int VERSION_1 = 1;
   private static final int VERSION_2 = 2;
   private static final int VERSION = 2;
   private static Descriptor[] PlayerZombieDescriptors = new Descriptor[10];
   private static final int FIRST_PLAYER_ZOMBIE_DESCRIPTOR_ID = 1000;

   public static void initSharedDescriptors() {
      if (GameServer.bServer) {
         ;
      }
   }

   private static void noise(String var0) {
      DebugLog.log("shared-descriptor: " + var0);
   }

   public static void createPlayerZombieDescriptor(IsoZombie var0) {
      if (GameServer.bServer) {
         if (var0.isReanimatedPlayer()) {
            if (var0.getDescriptor().getID() == 0) {
               int var1 = -1;

               for (int var2 = 0; var2 < PlayerZombieDescriptors.length; var2++) {
                  if (PlayerZombieDescriptors[var2] == null) {
                     var1 = var2;
                     break;
                  }
               }

               if (var1 == -1) {
                  Descriptor[] var10 = new Descriptor[PlayerZombieDescriptors.length + 10];
                  System.arraycopy(PlayerZombieDescriptors, 0, var10, 0, PlayerZombieDescriptors.length);
                  var1 = PlayerZombieDescriptors.length;
                  PlayerZombieDescriptors = var10;
                  noise("resized PlayerZombieDescriptors array size=" + PlayerZombieDescriptors.length);
               }

               var0.getDescriptor().setID(1000 + var1);
               int var11 = PersistentOutfits.instance.pickOutfit("ReanimatedPlayer", var0.isFemale());
               var11 = var11 & -65536 | var1 + 1;
               var0.setPersistentOutfitID(var11);
               Descriptor var3 = new Descriptor();
               var3.bFemale = var0.isFemale();
               var3.bZombie = false;
               var3.ID = 1000 + var1;
               var3.persistentOutfitID = var11;
               var3.getHumanVisual().copyFrom(var0.getHumanVisual());
               ItemVisuals var4 = new ItemVisuals();
               var0.getItemVisuals(var4);

               for (int var5 = 0; var5 < var4.size(); var5++) {
                  ItemVisual var6 = new ItemVisual((ItemVisual)var4.get(var5));
                  var3.itemVisuals.add(var6);
               }

               PlayerZombieDescriptors[var1] = var3;
               noise("added id=" + var3.getID());

               for (int var13 = 0; var13 < GameServer.udpEngine.connections.size(); var13++) {
                  UdpConnection var14 = (UdpConnection)GameServer.udpEngine.connections.get(var13);
                  ByteBufferWriter var7 = var14.startPacket();

                  try {
                     PacketType.ZombieDescriptors.doPacket(var7);
                     var3.save(var7.bb);
                     PacketType.ZombieDescriptors.send(var14);
                  } catch (Exception var9) {
                     var9.printStackTrace();
                     var14.cancelPacket();
                  }
               }
            }
         }
      }
   }

   public static void releasePlayerZombieDescriptor(IsoZombie var0) {
      if (GameServer.bServer) {
         if (var0.isReanimatedPlayer()) {
            int var1 = var0.getDescriptor().getID() - 1000;
            if (var1 >= 0 && var1 < PlayerZombieDescriptors.length) {
               noise("released id=" + var0.getDescriptor().getID());
               var0.getDescriptor().setID(0);
               PlayerZombieDescriptors[var1] = null;
            }
         }
      }
   }

   public static Descriptor[] getPlayerZombieDescriptors() {
      return PlayerZombieDescriptors;
   }

   public static void registerPlayerZombieDescriptor(Descriptor var0) {
      if (GameClient.bClient) {
         int var1 = var0.getID() - 1000;
         if (var1 >= 0 && var1 < 32767) {
            if (PlayerZombieDescriptors.length <= var1) {
               int var2 = (var1 + 10) / 10 * 10;
               Descriptor[] var3 = new Descriptor[var2];
               System.arraycopy(PlayerZombieDescriptors, 0, var3, 0, PlayerZombieDescriptors.length);
               PlayerZombieDescriptors = var3;
               noise("resized PlayerZombieDescriptors array size=" + PlayerZombieDescriptors.length);
            }

            PlayerZombieDescriptors[var1] = var0;
            noise("registered id=" + var0.getID());
         }
      }
   }

   public static void ApplyReanimatedPlayerOutfit(int var0, String var1, IsoGameCharacter var2) {
      IsoZombie var3 = (IsoZombie)Type.tryCastTo(var2, IsoZombie.class);
      if (var3 != null) {
         short var4 = (short)(var0 & 65535);
         if (var4 >= 1 && var4 <= PlayerZombieDescriptors.length) {
            Descriptor var5 = PlayerZombieDescriptors[var4 - 1];
            if (var5 != null) {
               var3.useDescriptor(var5);
            }
         }
      }
   }
}
