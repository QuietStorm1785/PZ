package zombie.core.raknet;

import gnu.trove.list.array.TShortArrayList;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import zombie.SystemDisabler;
import zombie.characters.IsoPlayer;
import zombie.commands.PlayerType;
import zombie.core.Core;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection.ChecksumState;
import zombie.core.raknet.UdpConnection.ConnectionType;
import zombie.core.raknet.UdpConnection.MPClientStatistic;
import zombie.core.utils.UpdateTimer;
import zombie.core.znet.ZNetStatistics;
import zombie.iso.IsoUtils;
import zombie.iso.Vector3;
import zombie.network.ClientServerMap;
import zombie.network.ConnectionManager;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.MPStatistic;
import zombie.network.PacketValidator;
import zombie.network.PlayerDownloadServer;

public class UdpConnection {
   Lock bufferLock = new ReentrantLock();
   private ByteBuffer bb = ByteBuffer.allocate(1000000);
   private ByteBufferWriter bbw = new ByteBufferWriter(this.bb);
   Lock bufferLockPing = new ReentrantLock();
   private ByteBuffer bbPing = ByteBuffer.allocate(50);
   private ByteBufferWriter bbwPing = new ByteBufferWriter(this.bbPing);
   long connectedGUID = 0L;
   UdpEngine engine;
   public int index;
   public boolean allChatMuted = false;
   public String username;
   public String[] usernames = new String[4];
   public byte ReleventRange;
   public byte accessLevel = 1;
   public long lastUnauthorizedPacket = 0L;
   public String ip;
   public boolean preferredInQueue;
   public boolean wasInLoadingQueue;
   public String password;
   public boolean ping = false;
   public Vector3[] ReleventPos = new Vector3[4];
   public short[] playerIDs = new short[4];
   public IsoPlayer[] players = new IsoPlayer[4];
   public Vector3[] connectArea = new Vector3[4];
   public int ChunkGridWidth;
   public ClientServerMap[] loadedCells = new ClientServerMap[4];
   public PlayerDownloadServer playerDownloadServer;
   public ChecksumState checksumState = ChecksumState.Init;
   public long checksumTime;
   public boolean awaitingCoopApprove = false;
   public long steamID;
   public long ownerID;
   public String idStr;
   public boolean isCoopHost;
   public int maxPlayers;
   public final TShortArrayList chunkObjectState = new TShortArrayList();
   public MPClientStatistic statistic = new MPClientStatistic(this);
   public ZNetStatistics netStatistics;
   public final Deque<Long> pingHistory = new ArrayDeque<>();
   public final PacketValidator validator = new PacketValidator(this);
   private static final long CONNECTION_ATTEMPT_TIMEOUT = 5000L;
   public static final long CONNECTION_GRACE_INTERVAL = 60000L;
   public long connectionTimestamp;
   public UpdateTimer timerSendZombie = new UpdateTimer();
   private boolean bFullyConnected = false;
   public boolean isNeighborPlayer = false;

   public UdpConnection(UdpEngine var1, long var2, int var4) {
      this.engine = var1;
      this.connectedGUID = var2;
      this.index = var4;
      this.ReleventPos[0] = new Vector3();

      for (int var5 = 0; var5 < 4; var5++) {
         this.playerIDs[var5] = -1;
      }

      this.connectionTimestamp = System.currentTimeMillis();
      this.wasInLoadingQueue = false;
   }

   public RakNetPeerInterface getPeer() {
      return this.engine.peer;
   }

   public long getConnectedGUID() {
      return this.connectedGUID;
   }

   public String getServerIP() {
      return this.engine.getServerIP();
   }

   public ByteBufferWriter startPacket() {
      this.bufferLock.lock();
      this.bb.clear();
      return this.bbw;
   }

   public ByteBufferWriter startPingPacket() {
      this.bufferLockPing.lock();
      this.bbPing.clear();
      return this.bbwPing;
   }

   public boolean RelevantTo(float var1, float var2) {
      for (int var3 = 0; var3 < 4; var3++) {
         if (this.connectArea[var3] != null) {
            int var4 = (int)this.connectArea[var3].z;
            int var5 = (int)(this.connectArea[var3].x - var4 / 2) * 10;
            int var6 = (int)(this.connectArea[var3].y - var4 / 2) * 10;
            int var7 = var5 + var4 * 10;
            int var8 = var6 + var4 * 10;
            if (var1 >= var5 && var1 < var7 && var2 >= var6 && var2 < var8) {
               return true;
            }
         }

         if (this.ReleventPos[var3] != null
            && Math.abs(this.ReleventPos[var3].x - var1) <= this.ReleventRange * 10
            && Math.abs(this.ReleventPos[var3].y - var2) <= this.ReleventRange * 10) {
            return true;
         }
      }

      return false;
   }

   public float getRelevantAndDistance(float var1, float var2, float var3) {
      for (int var4 = 0; var4 < 4; var4++) {
         if (this.ReleventPos[var4] != null
            && Math.abs(this.ReleventPos[var4].x - var1) <= this.ReleventRange * 10
            && Math.abs(this.ReleventPos[var4].y - var2) <= this.ReleventRange * 10) {
            return IsoUtils.DistanceTo(this.ReleventPos[var4].x, this.ReleventPos[var4].y, var1, var2);
         }
      }

      return Float.POSITIVE_INFINITY;
   }

   public boolean RelevantToPlayerIndex(int var1, float var2, float var3) {
      if (this.connectArea[var1] != null) {
         int var4 = (int)this.connectArea[var1].z;
         int var5 = (int)(this.connectArea[var1].x - var4 / 2) * 10;
         int var6 = (int)(this.connectArea[var1].y - var4 / 2) * 10;
         int var7 = var5 + var4 * 10;
         int var8 = var6 + var4 * 10;
         if (var2 >= var5 && var2 < var7 && var3 >= var6 && var3 < var8) {
            return true;
         }
      }

      return this.ReleventPos[var1] != null
         && Math.abs(this.ReleventPos[var1].x - var2) <= this.ReleventRange * 10
         && Math.abs(this.ReleventPos[var1].y - var3) <= this.ReleventRange * 10;
   }

   public boolean RelevantTo(float var1, float var2, float var3) {
      for (int var4 = 0; var4 < 4; var4++) {
         if (this.connectArea[var4] != null) {
            int var5 = (int)this.connectArea[var4].z;
            int var6 = (int)(this.connectArea[var4].x - var5 / 2) * 10;
            int var7 = (int)(this.connectArea[var4].y - var5 / 2) * 10;
            int var8 = var6 + var5 * 10;
            int var9 = var7 + var5 * 10;
            if (var1 >= var6 && var1 < var8 && var2 >= var7 && var2 < var9) {
               return true;
            }
         }

         if (this.ReleventPos[var4] != null && Math.abs(this.ReleventPos[var4].x - var1) <= var3 && Math.abs(this.ReleventPos[var4].y - var2) <= var3) {
            return true;
         }
      }

      return false;
   }

   public void cancelPacket() {
      this.bufferLock.unlock();
   }

   public int getBufferPosition() {
      return this.bb.position();
   }

   public void endPacket(int var1, int var2, byte var3) {
      if (GameServer.bServer) {
         int var4 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var4);
         this.bb.position(var4);
      }

      this.bb.flip();
      int var5 = this.engine.peer.Send(this.bb, var1, var2, var3, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

   public void endPacket() {
      if (GameServer.bServer) {
         int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
      int var2 = this.engine.peer.Send(this.bb, 1, 3, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

   public void endPacketImmediate() {
      if (GameServer.bServer) {
         int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
      int var2 = this.engine.peer.Send(this.bb, 0, 3, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

   public void endPacketUnordered() {
      if (GameServer.bServer) {
         int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
      int var2 = this.engine.peer.Send(this.bb, 2, 2, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

   public void endPacketUnreliable() {
      this.bb.flip();
      int var1 = this.engine.peer.Send(this.bb, 2, 1, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

   public void endPacketSuperHighUnreliable() {
      if (GameServer.bServer) {
         int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
      int var2 = this.engine.peer.Send(this.bb, 0, 1, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

   public void endPingPacket() {
      if (GameServer.bServer) {
         int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bbPing.flip();
      this.engine.peer.Send(this.bbPing, 0, 1, (byte)0, this.connectedGUID, false);
      this.bufferLockPing.unlock();
   }

   public InetSocketAddress getInetSocketAddress() {
      String var1 = this.engine.peer.getIPFromGUID(this.connectedGUID);
      if ("UNASSIGNED_SYSTEM_ADDRESS".equals(var1)) {
         return null;
      } else {
         var1 = var1.replace("|", "Â£");
         String[] var2 = var1.split("Â£");
         return new InetSocketAddress(var2[0], Integer.parseInt(var2[1]));
      }
   }

   public void forceDisconnect(String var1) {
      if (!GameServer.bServer) {
         GameClient.instance.disconnect();
      }

      this.engine.forceDisconnect(this.getConnectedGUID(), var1);
      ConnectionManager.log("force-disconnect", var1, this);
   }

   public void setFullyConnected() {
      this.validator.reset();
      this.bFullyConnected = true;
      this.setConnectionTimestamp();
      ConnectionManager.log("fully-connected", "", this);
   }

   public void setConnectionTimestamp() {
      this.connectionTimestamp = System.currentTimeMillis();
   }

   public boolean isConnectionAttemptTimeout() {
      return System.currentTimeMillis() > this.connectionTimestamp + 5000L;
   }

   public boolean isConnectionGraceIntervalTimeout() {
      return System.currentTimeMillis() > this.connectionTimestamp + 60000L || Core.bDebug && SystemDisabler.doKickInDebug;
   }

   public boolean isFullyConnected() {
      return this.bFullyConnected;
   }

   public void calcCountPlayersInRelevantPosition() {
      if (this.isFullyConnected()) {
         boolean var1 = false;

         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
            UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
            if (var3.isFullyConnected() && var3 != this) {
               for (int var4 = 0; var4 < var3.players.length; var4++) {
                  IsoPlayer var5 = var3.players[var4];
                  if (var5 != null && this.RelevantTo(var5.x, var5.y, 120.0F)) {
                     var1 = true;
                  }
               }

               if (var1) {
                  break;
               }
            }
         }

         this.isNeighborPlayer = var1;
      }
   }

   public ZNetStatistics getStatistics() {
      try {
         this.netStatistics = this.engine.peer.GetNetStatistics(this.connectedGUID);
      } catch (Exception var5) {
         this.netStatistics = null;
      } finally {
         return this.netStatistics;
      }
   }

   public int getAveragePing() {
      return this.engine.peer.GetAveragePing(this.connectedGUID);
   }

   public int getLastPing() {
      return this.engine.peer.GetLastPing(this.connectedGUID);
   }

   public int getLowestPing() {
      return this.engine.peer.GetLowestPing(this.connectedGUID);
   }

   public int getMTUSize() {
      return this.engine.peer.GetMTUSize(this.connectedGUID);
   }

   public ConnectionType getConnectionType() {
      return ConnectionType.values()[this.engine.peer.GetConnectionType(this.connectedGUID)];
   }

   @Override
   public String toString() {
      return GameClient.bClient
         ? String.format(
            "guid=%s ip=%s steam-id=%s access=\"%s\" username=\"%s\" connection-type=\"%s\"",
            this.connectedGUID,
            this.ip == null ? GameClient.ip : this.ip,
            this.steamID == 0L ? GameClient.steamID : this.steamID,
            PlayerType.toString(this.accessLevel),
            this.username == null ? GameClient.username : this.username,
            this.getConnectionType().name()
         )
         : String.format(
            "guid=%s ip=%s steam-id=%s access=%s username=\"%s\" connection-type=\"%s\"",
            this.connectedGUID,
            this.ip,
            this.steamID,
            PlayerType.toString(this.accessLevel),
            this.username,
            this.getConnectionType().name()
         );
   }

   public boolean havePlayer(IsoPlayer var1) {
      if (var1 == null) {
         return false;
      } else {
         for (int var2 = 0; var2 < this.players.length; var2++) {
            if (this.players[var2] == var1) {
               return true;
            }
         }

         return false;
      }
   }
}
