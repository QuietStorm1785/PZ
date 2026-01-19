package zombie.network;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.GameTime;
import zombie.ZomboidFileSystem;
import zombie.characters.IsoPlayer;
import zombie.core.logger.ExceptionLogger;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugLog;
import zombie.network.PacketTypes.PacketType;
import zombie.network.ReplayManager.State;
import zombie.network.packets.PlayerPacket;

public class ReplayManager {
   private static final int ReplayManagerVersion = 1;
   private State state = State.Stop;
   private IsoPlayer player = null;
   private ByteBuffer bbpp = ByteBuffer.allocate(43);
   private FileOutputStream outStream = null;
   private DataOutputStream output = null;
   private FileInputStream inStream = null;
   private DataInputStream input = null;
   private int inputVersion = 0;
   private long inputTimeShift = 0L;
   private PlayerPacket nextpp = null;
   private long nextppTime = 0L;

   public ReplayManager(IsoPlayer var1) {
      this.player = var1;
   }

   public State getState() {
      return this.state;
   }

   public boolean isPlay() {
      return this.state == State.Playing;
   }

   public void recordPlayerPacket(PlayerPacket var1) {
      if (this.state == State.Recording && var1.id == this.player.OnlineID) {
         this.bbpp.position(0);
         ByteBufferWriter var2 = new ByteBufferWriter(this.bbpp);
         var1.write(var2);

         try {
            this.output.writeLong(GameTime.getServerTime());
            this.output.write(PacketType.PlayerUpdate.getId());
            this.output.write(var2.bb.array());
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }
   }

   public boolean startRecordReplay(IsoPlayer var1, String var2) {
      File var3 = ZomboidFileSystem.instance.getFileInCurrentSave(var2);
      if (this.player != null && this.state == State.Recording) {
         DebugLog.log("ReplayManager: record replay already active for " + this.player.getUsername() + " user");
         return false;
      } else if (var3.exists()) {
         DebugLog.log("ReplayManager: invalid filename \"" + var2 + "\"");
         return false;
      } else {
         try {
            this.outStream = new FileOutputStream(var3);
            this.output = new DataOutputStream(this.outStream);
            this.output.write(1);
            this.output.writeLong(GameTime.getServerTime());
            this.player = var1;
            this.state = State.Recording;
            return true;
         } catch (Exception var5) {
            ExceptionLogger.logException(var5);
            return false;
         }
      }
   }

   public boolean stopRecordReplay() {
      if (this.state != State.Recording) {
         DebugLog.log("ReplayManager: record inactive");
         return false;
      } else {
         try {
            this.state = State.Stop;
            this.player = null;
            this.output.flush();
            this.output.close();
            this.outStream.close();
            this.output = null;
            return true;
         } catch (IOException var2) {
            var2.printStackTrace();
            return false;
         }
      }
   }

   public boolean startPlayReplay(IsoPlayer var1, String var2, UdpConnection var3) {
      File var4 = ZomboidFileSystem.instance.getFileInCurrentSave(var2);
      if (this.state == State.Playing) {
         DebugLog.log("ReplayManager: play replay already active for " + this.player.getUsername() + " user");
         return false;
      } else if (!var4.exists()) {
         DebugLog.log("ReplayManager: invalid filename \"" + var2 + "\"");
         return false;
      } else {
         try {
            this.inStream = new FileInputStream(var4);
            this.input = new DataInputStream(this.inStream);
            this.inputVersion = this.input.read();
            this.inputTimeShift = GameTime.getServerTime() - this.input.readLong();
            this.nextppTime = this.input.readLong();
            int var5 = this.input.read();
            if (var5 == PacketType.PlayerUpdate.getId() || var5 == PacketType.PlayerUpdateReliable.getId()) {
               this.input.read(this.bbpp.array());
               this.bbpp.position(0);
               this.nextpp = new PlayerPacket();
               this.nextpp.parse(this.bbpp, var3);
            }

            this.player = var1;
            this.state = State.Playing;
            return true;
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
            return false;
         }
      }
   }

   public boolean stopPlayReplay() {
      if (this.state != State.Playing) {
         DebugLog.log("ReplayManager: play inactive");
         return false;
      } else {
         try {
            this.state = State.Stop;
            this.player = null;
            this.input.close();
            this.inStream.close();
            this.input = null;
            this.inputVersion = 0;
            this.inputTimeShift = 0L;
            this.nextpp = null;
            return true;
         } catch (IOException var2) {
            var2.printStackTrace();
            return false;
         }
      }
   }

   public void update() {
      if (this.state == State.Playing) {
         if (GameTime.getServerTime() >= this.nextppTime + this.inputTimeShift) {
            this.nextpp.id = this.player.OnlineID;
            this.nextpp.realt = (int)(this.nextpp.realt + this.inputTimeShift / 1000000L);
            IsoPlayer var1 = (IsoPlayer)GameServer.IDToPlayerMap.get(Integer.valueOf(this.nextpp.id));
            UdpConnection var2 = GameServer.getConnectionFromPlayer(var1);

            try {
               if (var1 == null) {
                  DebugLog.General
                     .error("receivePlayerUpdate: Server received position for unknown player (id:" + this.nextpp.id + "). Server will ignore this data.");
               } else {
                  var1.networkAI.parse(this.nextpp);
                  var2.ReleventPos[var1.PlayerIndex].x = this.nextpp.realx;
                  var2.ReleventPos[var1.PlayerIndex].y = this.nextpp.realy;
                  var2.ReleventPos[var1.PlayerIndex].z = this.nextpp.realz;
               }
            } catch (Exception var6) {
               var6.printStackTrace();
            }

            for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
               UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);
               if (var2.getConnectedGUID() != var4.getConnectedGUID()) {
                  ByteBufferWriter var5 = var4.startPacket();
                  PacketType.PlayerUpdate.doPacket(var5);
                  this.nextpp.write(var5);
                  PacketType.PlayerUpdate.send(var4);
               }
            }

            try {
               this.nextppTime = this.input.readLong();
               int var8 = this.input.read();
               if (var8 == PacketType.PlayerUpdate.getId() || var8 == PacketType.PlayerUpdateReliable.getId()) {
                  this.bbpp.position(0);
                  this.input.read(this.bbpp.array());
                  this.bbpp.position(0);
                  this.nextpp = new PlayerPacket();
                  this.nextpp.parse(this.bbpp, var2);
               }
            } catch (IOException var7) {
               DebugLog.log("ReplayManager: stop playing replay");
               this.stopPlayReplay();
            }
         }
      }
   }
}
