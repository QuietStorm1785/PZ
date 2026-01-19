package zombie.network.packets;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.PersistentOutfits;
import zombie.SharedDescriptors;
import zombie.ZomboidFileSystem;
import zombie.SharedDescriptors.Descriptor;
import zombie.core.logger.ExceptionLogger;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugLog;
import zombie.debug.LogSeverity;
import zombie.iso.IsoWorld;
import zombie.network.ConnectionDetails;
import zombie.network.ConnectionManager;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.RequestDataManager;
import zombie.network.GameClient.RequestState;
import zombie.network.PacketTypes.PacketType;
import zombie.network.ServerWorldDatabase.LogonResult;
import zombie.network.packets.RequestDataPacket.1;
import zombie.network.packets.RequestDataPacket.RequestID;
import zombie.network.packets.RequestDataPacket.RequestType;
import zombie.radio.ZomboidRadio;
import zombie.radio.media.RecordedMedia;

public class RequestDataPacket implements INetworkPacket {
   RequestType type;
   RequestID id;
   ByteBuffer buffer = null;
   int dataSize;
   int dataSent;
   int partSize;
   public static ByteBuffer large_file_bb = ByteBuffer.allocate(52428800);

   public void setRequest() {
      this.type = RequestType.Request;
      this.id = RequestID.Descriptors;
   }

   public void setRequest(RequestID var1) {
      this.type = RequestType.Request;
      this.id = var1;
   }

   public void setPartData(RequestID var1, ByteBuffer var2) {
      this.type = RequestType.PartData;
      this.buffer = var2;
      this.id = var1;
      this.dataSize = var2.limit();
   }

   public void setPartDataParameters(int var1, int var2) {
      this.dataSent = var1;
      this.partSize = var2;
   }

   public void setACK(RequestID var1) {
      this.type = RequestType.PartDataACK;
      this.id = var1;
   }

   public void sendConnectingDetails(UdpConnection var1, LogonResult var2) {
      if (GameServer.bServer) {
         this.id = RequestID.ConnectionDetails;
         large_file_bb.clear();
         ConnectionDetails.write(var1, var2, large_file_bb);
         this.doSendRequest(var1);
         DebugLog.Multiplayer.debugln("%s %db", this.id.name(), large_file_bb.position());
         ConnectionManager.log("send-packet", "connection-details", var1);
      }
   }

   public void parse(ByteBuffer var1, UdpConnection var2) {
      try {
         this.type = RequestType.values()[var1.get()];
      } catch (Exception var4) {
         DebugLog.Multiplayer.printException(var4, "RequestData packet parse failed", LogSeverity.Error);
         this.type = RequestType.None;
      }

      this.id = RequestID.values()[var1.get()];
      if (GameClient.bClient) {
         if (this.type == RequestType.FullData) {
            int var3 = var1.limit() - var1.position();
            large_file_bb.clear();
            large_file_bb.limit(var3);
            large_file_bb.put(var1.array(), var1.position(), var3);
            this.buffer = large_file_bb;
         } else if (this.type == RequestType.PartData) {
            this.dataSize = var1.getInt();
            this.dataSent = var1.getInt();
            this.partSize = var1.getInt();
            large_file_bb.clear();
            large_file_bb.limit(this.partSize);
            large_file_bb.put(var1.array(), var1.position(), this.partSize);
            this.buffer = large_file_bb;
         }
      }
   }

   public void write(ByteBufferWriter var1) {
      var1.putByte((byte)this.type.ordinal());
      var1.putByte((byte)this.id.ordinal());
      if (GameServer.bServer) {
         if (this.type == RequestType.FullData) {
            var1.bb.put(this.buffer.array(), 0, this.buffer.position());
         } else if (this.type == RequestType.PartData) {
            var1.putInt(this.dataSize);
            var1.putInt(this.dataSent);
            var1.putInt(this.partSize);
            var1.bb.put(this.buffer.array(), this.dataSent, this.partSize);
         }
      }
   }

   public void processServer(PacketType var1, UdpConnection var2) {
      if (!var2.wasInLoadingQueue && this.id != RequestID.ConnectionDetails) {
         GameServer.kick(var2, "UI_Policy_Kick", "The server received an invalid request");
      }

      if (this.type == RequestType.Request) {
         this.doProcessRequest(var2);
      } else if (this.type == RequestType.PartDataACK) {
         RequestDataManager.getInstance().ACKWasReceived(this.id, var2, this.dataSent);
      }
   }

   private void doSendRequest(UdpConnection var1) {
      if (large_file_bb.position() < 1024) {
         this.type = RequestType.FullData;
         this.buffer = large_file_bb;
         ByteBufferWriter var2 = var1.startPacket();
         PacketType.RequestData.doPacket(var2);
         this.write(var2);
         PacketType.RequestData.send(var1);
      } else {
         RequestDataManager.getInstance().putDataForTransmit(this.id, var1, large_file_bb);
      }
   }

   private void doProcessRequest(UdpConnection var1) {
      if (this.id == RequestID.Descriptors) {
         try {
            large_file_bb.clear();
            PersistentOutfits.instance.save(large_file_bb);
         } catch (Exception var10) {
            var10.printStackTrace();
         }

         this.doSendRequest(var1);
      }

      if (this.id == RequestID.PlayerZombieDescriptors) {
         Descriptor[] var2 = SharedDescriptors.getPlayerZombieDescriptors();
         int var3 = 0;

         for (int var4 = 0; var4 < var2.length; var4++) {
            if (var2[var4] != null) {
               var3++;
            }
         }

         if (var3 * 2 * 1024 > large_file_bb.capacity()) {
            large_file_bb = ByteBuffer.allocate(var3 * 2 * 1024);
         }

         try {
            large_file_bb.clear();
            large_file_bb.putShort((short)var3);

            for (Descriptor var7 : var2) {
               if (var7 != null) {
                  var7.save(large_file_bb);
               }
            }

            this.doSendRequest(var1);
         } catch (Exception var11) {
            var11.printStackTrace();
         }
      }

      if (this.id == RequestID.MetaGrid) {
         try {
            large_file_bb.clear();
            IsoWorld.instance.MetaGrid.savePart(large_file_bb, 0, true);
            IsoWorld.instance.MetaGrid.savePart(large_file_bb, 1, true);
            this.doSendRequest(var1);
         } catch (Exception var9) {
            DebugLog.Multiplayer.printException(var9, "map_meta.bin could not be saved", LogSeverity.Error);
            GameServer.kick(var1, "You have been kicked from this server because map_meta.bin could not be saved.", null);
            var1.forceDisconnect("save-map-meta-bin");
            GameServer.addDisconnect(var1);
         }
      }

      if (this.id == RequestID.MapZone) {
         try {
            large_file_bb.clear();
            IsoWorld.instance.MetaGrid.saveZone(large_file_bb);
            this.doSendRequest(var1);
         } catch (Exception var8) {
            DebugLog.Multiplayer.printException(var8, "map_zone.bin could not be saved", LogSeverity.Error);
            GameServer.kick(var1, "You have been kicked from this server because map_zone.bin could not be saved.", null);
            var1.forceDisconnect("save-map-zone-bin");
            GameServer.addDisconnect(var1);
         }
      }

      if (this.id == RequestID.RadioData) {
         large_file_bb.clear();
         ZomboidRadio.getInstance().getRecordedMedia().sendRequestData(large_file_bb);
         this.doSendRequest(var1);
      }

      DebugLog.Multiplayer.debugln("%s %db", this.id.name(), large_file_bb.position());
   }

   public void process(UdpConnection var1) {
      if (this.type == RequestType.FullData) {
         large_file_bb.position(0);
         this.doProcessData(large_file_bb);
      } else if (this.type == RequestType.PartData) {
         large_file_bb.position(0);
         this.doProcessPart(large_file_bb);
      }
   }

   private void doProcessPart(ByteBuffer var1) {
      ByteBuffer var2 = RequestDataManager.getInstance().receiveClientData(this.id, var1, this.dataSize, this.dataSent);
      if (var2 != null) {
         this.doProcessData(var2);
      }
   }

   private void doProcessData(ByteBuffer var1) {
      if (this.id == RequestID.ConnectionDetails) {
         ConnectionDetails.parse(var1);
      }

      if (this.id == RequestID.Descriptors) {
         try {
            DebugLog.Multiplayer.debugln("received zombie descriptors");
            PersistentOutfits.instance.load(var1);
         } catch (IOException var5) {
            DebugLog.Multiplayer.printException(var5, "PersistentOutfits loading IO error", LogSeverity.Error);
            ExceptionLogger.logException(var5);
         } catch (Exception var6) {
            DebugLog.Multiplayer.printException(var6, "PersistentOutfits loading error", LogSeverity.Error);
         }
      }

      if (this.id == RequestID.PlayerZombieDescriptors) {
         try {
            this.receivePlayerZombieDescriptors(var1);
         } catch (Exception var4) {
            DebugLog.Multiplayer.printException(var4, "Player zombie descriptors loading error", LogSeverity.Error);
            ExceptionLogger.logException(var4);
         }
      }

      if (this.id == RequestID.MetaGrid) {
         this.saveToFile(var1, "map_meta.bin");
      }

      if (this.id == RequestID.MapZone) {
         this.saveToFile(var1, "map_zone.bin");
      }

      if (this.id == RequestID.RadioData) {
         try {
            RecordedMedia.receiveRequestData(var1);
         } catch (Exception var3) {
            DebugLog.Multiplayer.printException(var3, "Radio data loading error", LogSeverity.Error);
            ExceptionLogger.logException(var3);
         }
      }

      this.sendNextRequest(this.id);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private void sendNextRequest(RequestID var1) {
      switch (1.$SwitchMap$zombie$network$packets$RequestDataPacket$RequestID[var1.ordinal()]) {
         case 1:
            this.setRequest(RequestID.MetaGrid);
            break;
         case 2:
            this.setRequest(RequestID.MapZone);
            break;
         case 3:
            this.setRequest(RequestID.PlayerZombieDescriptors);
            break;
         case 4:
            this.setRequest(RequestID.RadioData);
            break;
         case 5:
            GameClient.instance.setRequest(RequestState.Complete);
      }

      if (var1 != RequestID.RadioData) {
         ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.RequestData.doPacket(var2);
         this.write(var2);
         PacketType.RequestData.send(GameClient.connection);
      }
   }

   private void saveToFile(ByteBuffer var1, String var2) {
      File var3 = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(var2));

      try (
         FileOutputStream var4 = new FileOutputStream(var3, false);
         BufferedOutputStream var5 = new BufferedOutputStream(var4);
      ) {
         var5.write(var1.array(), 0, var1.limit());
         var5.flush();
      } catch (IOException var12) {
         DebugLog.Multiplayer.printException(var12, "Save to the " + var2 + " file error", LogSeverity.Error);
      }
   }

   private void receivePlayerZombieDescriptors(ByteBuffer var1) throws IOException {
      short var2 = var1.getShort();
      DebugLog.Multiplayer.debugln("received " + var2 + " player-zombie descriptors");

      for (short var3 = 0; var3 < var2; var3++) {
         Descriptor var4 = new Descriptor();
         var4.load(var1, 195);
         SharedDescriptors.registerPlayerZombieDescriptor(var4);
      }
   }

   public boolean isConsistent() {
      return this.type != RequestType.None;
   }

   public String getDescription() {
      String var1 = "\n\tRequestDataPacket [";
      var1 = var1 + "type=" + this.type.name() + " | ";
      if (this.type == RequestType.Request || this.type == RequestType.PartDataACK) {
         var1 = var1 + "id=" + this.id.name() + "] ";
      }

      if (this.type == RequestType.FullData) {
         var1 = var1 + "id=" + this.id.name() + " | ";
         var1 = var1 + "data=(size:" + this.buffer.limit() + ", data=";
         this.buffer.position(0);

         for (int var2 = 0; var2 < Math.min(15, this.buffer.limit()); var2++) {
            var1 = var1 + " 0x" + Integer.toHexString(this.buffer.get() & 255);
         }

         var1 = var1 + ".. ] ";
      }

      if (this.type == RequestType.PartData) {
         var1 = var1 + "id=" + this.id.name() + " | ";
         var1 = var1 + "dataSize=" + this.dataSize + " | ";
         var1 = var1 + "dataSent=" + this.dataSent + " | ";
         var1 = var1 + "partSize=" + this.partSize + " | ";
         var1 = var1 + "data=(size:" + this.buffer.limit() + ", data=";
         if (this.buffer.limit() >= this.dataSize) {
            this.buffer.position(this.dataSent);
         } else {
            this.buffer.position(0);
         }

         for (int var11 = 0; var11 < Math.min(15, this.buffer.limit() - this.buffer.position()); var11++) {
            var1 = var1 + " " + Integer.toHexString(this.buffer.get() & 255);
         }

         var1 = var1 + ".. ] ";
      }

      return var1;
   }
}
