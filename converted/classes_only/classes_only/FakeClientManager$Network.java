package zombie.network;

import java.nio.ByteBuffer;
import java.util.HashMap;
import zombie.core.ThreadGroups;
import zombie.core.raknet.RakNetPeerInterface;
import zombie.core.raknet.VoiceManager;
import zombie.core.secure.PZcrypt;
import zombie.network.FakeClientManager.Client;
import zombie.network.FakeClientManager.Client.State;
import zombie.network.PacketTypes.PacketType;

class FakeClientManager$Network {
   private final HashMap<Integer, Client> createdClients = new HashMap<>();
   private final HashMap<Long, Client> connectedClients = new HashMap<>();
   private final ByteBuffer rb = ByteBuffer.allocate(1000000);
   private final ByteBuffer wb = ByteBuffer.allocate(1000000);
   private final RakNetPeerInterface peer;
   private final int started;
   private int connected = -1;
   private static final HashMap<Integer, String> systemPacketTypeNames = new HashMap<>();

   boolean isConnected() {
      return this.connected == 0;
   }

   boolean isStarted() {
      return this.started == 0;
   }

   private FakeClientManager$Network(int var1, int var2) {
      this.peer = new RakNetPeerInterface();
      this.peer.Init(false);
      this.peer.SetMaximumIncomingConnections(0);
      this.peer.SetClientPort(var2);
      this.peer.SetOccasionalPing(true);
      this.started = this.peer.Startup(var1);
      if (this.started == 0) {
         Thread var3 = new Thread(ThreadGroups.Network, this::receiveThread, "PeerInterfaceReceive");
         var3.setDaemon(true);
         var3.start();
         FakeClientManager.log(-1, "Network start ok");
      } else {
         FakeClientManager.error(-1, String.format("Network start failed: %d", this.started));
      }
   }

   private void connect(int var1, String var2) {
      this.connected = this.peer.Connect(var2, 16261, PZcrypt.hash("", true), false);
      if (this.connected == 0) {
         FakeClientManager.log(var1, String.format("Client connected to %s:%d", var2, 16261));
      } else {
         FakeClientManager.error(var1, String.format("Client connection to %s:%d failed: %d", var2, 16261, this.connected));
      }
   }

   private void disconnect(long var1, int var3, String var4) {
      if (var1 != 0L) {
         this.peer.disconnect(var1, "");
         this.connected = -1;
      }

      if (this.connected == -1) {
         FakeClientManager.log(var3, String.format("Client disconnected from %s:%d", var4, 16261));
      } else {
         FakeClientManager.log(var3, String.format("Client disconnection from %s:%d failed: %d", var4, 16261, var1));
      }
   }

   private ByteBuffer startPacket() {
      this.wb.clear();
      return this.wb;
   }

   private void cancelPacket() {
      this.wb.clear();
   }

   private void endPacket(long var1) {
      this.wb.flip();
      this.peer.Send(this.wb, 1, 3, (byte)0, var1, false);
   }

   private void endPacketImmediate(long var1) {
      this.wb.flip();
      this.peer.Send(this.wb, 0, 3, (byte)0, var1, false);
   }

   private void endPacketSuperHighUnreliable(long var1) {
      this.wb.flip();
      this.peer.Send(this.wb, 0, 1, (byte)0, var1, false);
   }

   private void receiveThread() {
      while (true) {
         if (this.peer.Receive(this.rb)) {
            this.decode(this.rb);
         } else {
            FakeClientManager.sleep(1L);
         }
      }
   }

   private static void logUserPacket(int var0, short var1) {
      PacketType var2 = (PacketType)PacketTypes.packetTypes.get(var1);
      String var3 = var2 == null ? "unknown user packet" : var2.name();
      FakeClientManager.trace(var0, String.format("## %s (%d)", var3, var1));
   }

   private static void logSystemPacket(int var0, int var1) {
      String var2 = systemPacketTypeNames.getOrDefault(var1, "unknown system packet");
      FakeClientManager.trace(var0, String.format("## %s (%d)", var2, var1));
   }

   private void decode(ByteBuffer var1) {
      int var2 = var1.get() & 255;
      int var3 = -1;
      long var4 = -1L;
      logSystemPacket(var3, var2);
      switch (var2) {
         case 0:
         case 1:
         case 20:
         case 25:
         case 31:
         case 33:
         default:
            break;
         case 16:
            var3 = var1.get() & 255;
            var4 = this.peer.getGuidOfPacket();
            Client var19 = this.createdClients.get(var3);
            if (var19 != null) {
               var19.connectionGUID = var4;
               this.connectedClients.put(var4, var19);
               VoiceManager.instance.VoiceConnectReq(var4);
               var19.changeState(State.LOGIN);
            }

            FakeClientManager.log(-1, String.format("Connected clients: %d (connection index %d)", this.connectedClients.size(), var3));
            break;
         case 17:
         case 18:
         case 23:
         case 24:
         case 32:
            FakeClientManager.error(-1, "Connection failed: " + var2);
            break;
         case 19:
            var3 = var1.get() & 255;
         case 44:
         case 45:
            var4 = this.peer.getGuidOfPacket();
            break;
         case 21:
            var3 = var1.get() & 255;
            var4 = this.peer.getGuidOfPacket();
            Client var18 = this.connectedClients.get(var4);
            if (var18 != null) {
               this.connectedClients.remove(var4);
               var18.changeState(State.DISCONNECT);
            }

            FakeClientManager.log(-1, String.format("Connected clients: %d (connection index %d)", this.connectedClients.size(), var3));
            break;
         case 22:
            var3 = var1.get() & 255;
            Client var17 = this.createdClients.get(var3);
            if (var17 != null) {
               var17.changeState(State.DISCONNECT);
            }
            break;
         case 134:
            short var7 = var1.getShort();
            var4 = this.peer.getGuidOfPacket();
            Client var6 = this.connectedClients.get(var4);
            if (var6 != null) {
               var6.receive((short)var7, var1);
               var3 = var6.connectionIndex;
            }
      }
   }

   static {
      systemPacketTypeNames.put(22, "connection lost");
      systemPacketTypeNames.put(21, "disconnected");
      systemPacketTypeNames.put(23, "connection banned");
      systemPacketTypeNames.put(17, "connection failed");
      systemPacketTypeNames.put(20, "no free connections");
      systemPacketTypeNames.put(16, "connection accepted");
      systemPacketTypeNames.put(18, "already connected");
      systemPacketTypeNames.put(44, "voice request");
      systemPacketTypeNames.put(45, "voice reply");
      systemPacketTypeNames.put(25, "wrong protocol version");
      systemPacketTypeNames.put(0, "connected ping");
      systemPacketTypeNames.put(1, "unconnected ping");
      systemPacketTypeNames.put(33, "new remote connection");
      systemPacketTypeNames.put(31, "remote disconnection");
      systemPacketTypeNames.put(32, "remote connection lost");
      systemPacketTypeNames.put(24, "invalid password");
      systemPacketTypeNames.put(19, "new connection");
      systemPacketTypeNames.put(134, "user packet");
   }
}
