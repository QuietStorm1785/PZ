package zombie.network;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.util.HashMap;
import zombie.characters.NetworkCharacter.Transform;
import zombie.core.ThreadGroups;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.RakVoice;
import zombie.core.utils.UpdateLimit;
import zombie.iso.IsoDirections;
import zombie.iso.Vector2;
import zombie.network.FakeClientManager.1;
import zombie.network.FakeClientManager.Network;
import zombie.network.FakeClientManager.Player;
import zombie.network.FakeClientManager.Zombie;
import zombie.network.FakeClientManager.Client.Request;
import zombie.network.FakeClientManager.Client.State;
import zombie.network.FakeClientManager.Player.Clothes;
import zombie.network.NetworkVariables.PredictionTypes;
import zombie.network.PacketTypes.PacketType;
import zombie.network.packets.PlayerPacket;
import zombie.network.packets.SyncInjuriesPacket;

class FakeClientManager$Client {
   private static String connectionServerHost = "127.0.0.1";
   private static long connectionInterval = 1500L;
   private static long connectionTimeout = 10000L;
   private static long connectionDelay = 15000L;
   private static int statisticsClientID = -1;
   private static int statisticsPeriod = 1;
   private static long serverTimeShift = 0L;
   private static boolean serverTimeShiftIsSet = false;
   private final HashMap<Integer, Request> requests = new HashMap<>();
   private final Player player;
   private final Network network;
   private final int connectionIndex;
   private final int port;
   private long connectionGUID = -1L;
   private int requestId = 0;
   private long stateTime;
   private State state;
   private String host;
   public static String luaChecksum = "";
   public static String scriptChecksum = "";

   private FakeClientManager$Client(Player var1, Network var2, int var3, int var4) {
      this.connectionIndex = var3;
      this.network = var2;
      this.player = var1;
      this.port = var4;

      try {
         this.host = InetAddress.getByName(connectionServerHost).getHostAddress();
         this.state = State.CONNECT;
         Thread var5 = new Thread(ThreadGroups.Workers, this::updateThread, this.player.username);
         var5.setDaemon(true);
         var5.start();
      } catch (UnknownHostException var6) {
         this.state = State.QUIT;
         var6.printStackTrace();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private void updateThread() {
      FakeClientManager.info(
         this.player.movement.id,
         String.format(
            "Start client (%d) %s:%d => %s:%d / \"%s\"", this.connectionIndex, "0.0.0.0", this.port, this.host, 16261, this.player.movement.description
         )
      );
      FakeClientManager.sleep(this.player.movement.connectDelay);
      switch (1.$SwitchMap$zombie$network$FakeClientManager$Movement$Type[this.player.movement.type.ordinal()]) {
         case 1:
            this.player.circleMovement();
            break;
         case 2:
            this.player.lineMovement();
            break;
         case 3:
            this.player.aiAttackZombiesMovement();
            break;
         case 4:
            this.player.aiRunAwayFromZombiesMovement();
            break;
         case 5:
            this.player.aiRunToAnotherPlayersMovement();
            break;
         case 6:
            this.player.aiNormalMovement();
      }

      while (this.state != State.QUIT) {
         this.update();
         FakeClientManager.sleep(1L);
      }

      FakeClientManager.info(
         this.player.movement.id,
         String.format(
            "Stop client (%d) %s:%d => %s:%d / \"%s\"", this.connectionIndex, "0.0.0.0", this.port, this.host, 16261, this.player.movement.description
         )
      );
   }

   private void updateTime() {
      this.stateTime = System.currentTimeMillis();
   }

   private long getServerTime() {
      return serverTimeShiftIsSet ? System.nanoTime() + serverTimeShift : 0L;
   }

   private boolean checkConnectionTimeout() {
      return System.currentTimeMillis() - this.stateTime > connectionTimeout;
   }

   private boolean checkConnectionDelay() {
      return System.currentTimeMillis() - this.stateTime > connectionDelay;
   }

   private void changeState(State var1) {
      this.updateTime();
      FakeClientManager.log(this.player.movement.id, String.format("%s >> %s", this.state, var1));
      if (State.RUN.equals(var1)) {
         this.player.movement.connect(this.player.OnlineID);
         if (this.player.teleportLimiter == null) {
            this.player.teleportLimiter = new UpdateLimit(this.player.movement.teleportDelay);
         }

         if (this.player.movement.id == statisticsClientID) {
            this.sendTimeSync();
            this.sendInjuries();
            this.sendStatisticsEnable(statisticsPeriod);
         }
      } else if (State.DISCONNECT.equals(var1) && !State.DISCONNECT.equals(this.state)) {
         this.player.movement.disconnect(this.player.OnlineID);
      }

      this.state = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private void update() {
      switch (1.$SwitchMap$zombie$network$FakeClientManager$Client$State[this.state.ordinal()]) {
         case 1:
            this.player.movement.timestamp = System.currentTimeMillis();
            this.network.connect(this.player.movement.id, this.host);
            this.changeState(State.WAIT);
            break;
         case 2:
            this.sendPlayerLogin();
            this.changeState(State.WAIT);
            break;
         case 3:
            this.sendPlayerConnect();
            this.changeState(State.WAIT);
            break;
         case 4:
            this.sendChecksum();
            this.changeState(State.WAIT);
            break;
         case 5:
            this.sendPlayerExtraInfo(this.player.movement.ghost, this.player.movement.hordeCreator != null || Player.isVOIPEnabled);
            this.sendEquip();
            this.changeState(State.WAIT);
            break;
         case 6:
            this.requestId = 0;
            this.requests.clear();
            this.requestFullUpdate();
            this.requestLargeAreaZip();
            this.changeState(State.WAIT);
            break;
         case 7:
            if (this.player.movement.doDisconnect() && this.player.movement.checkDisconnect()) {
               this.changeState(State.DISCONNECT);
            } else {
               this.player.run();
            }
            break;
         case 8:
            if (this.checkConnectionTimeout()) {
               this.changeState(State.DISCONNECT);
            }
            break;
         case 9:
            if (this.network.isConnected()) {
               this.player.movement.timestamp = System.currentTimeMillis();
               this.network.disconnect(this.connectionGUID, this.player.movement.id, this.host);
            }

            if (this.player.movement.doReconnect() && this.player.movement.checkReconnect()
               || !this.player.movement.doReconnect() && this.checkConnectionDelay()) {
               this.changeState(State.CONNECT);
            }
         case 10:
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private void receive(short var1, ByteBuffer var2) {
      PacketType var3 = (PacketType)PacketTypes.packetTypes.get(var1);
      Network.logUserPacket(this.player.movement.id, var1);
      switch (1.$SwitchMap$zombie$network$PacketTypes$PacketType[var3.ordinal()]) {
         case 1:
            if (this.receivePlayerConnect(var2)) {
               if (luaChecksum.isEmpty()) {
                  this.changeState(State.PLAYER_EXTRA_INFO);
               } else {
                  this.changeState(State.CHECKSUM);
               }
            }
            break;
         case 2:
            if (this.receivePlayerExtraInfo(var2)) {
               this.changeState(State.RUN);
            }
            break;
         case 3:
            if (this.state == State.WAIT && this.receiveChunkPart(var2)) {
               this.updateTime();
               if (this.allChunkPartsReceived()) {
                  this.changeState(State.PLAYER_CONNECT);
               }
            }
            break;
         case 4:
            if (this.state == State.WAIT && this.receiveNotRequired(var2)) {
               this.updateTime();
               if (this.allChunkPartsReceived()) {
                  this.changeState(State.PLAYER_CONNECT);
               }
            }
         case 5:
         default:
            break;
         case 6:
            this.receiveStatistics(var2);
            break;
         case 7:
            this.receiveTimeSync(var2);
            break;
         case 8:
            this.receiveSyncClock(var2);
            break;
         case 9:
         case 10:
            this.receiveZombieSimulation(var2);
            break;
         case 11:
         case 12:
            this.player.playerManager.parsePlayer(var2);
            break;
         case 13:
            this.player.playerManager.parsePlayerTimeout(var2);
            break;
         case 14:
            this.receiveKicked(var2);
            break;
         case 15:
            this.receiveChecksum(var2);
            break;
         case 16:
            this.receiveKillZombie(var2);
            break;
         case 17:
            this.receiveTeleport(var2);
      }

      var2.clear();
   }

   private void doPacket(short var1, ByteBuffer var2) {
      var2.put((byte)-122);
      var2.putShort(var1);
   }

   private void putUTF(ByteBuffer var1, String var2) {
      if (var2 == null) {
         var1.putShort((short)0);
      } else {
         byte[] var3 = var2.getBytes();
         var1.putShort((short)var3.length);
         var1.put(var3);
      }
   }

   private void putBoolean(ByteBuffer var1, boolean var2) {
      var1.put((byte)(var2 ? 1 : 0));
   }

   private void sendPlayerLogin() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.Login.getId(), var1);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, FakeClientManager.versionNumber);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendPlayerConnect() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.PlayerConnect.getId(), var1);
      this.writePlayerConnectData(var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void writePlayerConnectData(ByteBuffer var1) {
      var1.put((byte)0);
      var1.put((byte)13);
      var1.putFloat(this.player.x);
      var1.putFloat(this.player.y);
      var1.putFloat(this.player.z);
      var1.putInt(0);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, this.player.isFemale == 0 ? "Kate" : "Male");
      var1.putInt(this.player.isFemale);
      this.putUTF(var1, "fireofficer");
      var1.putInt(0);
      var1.putInt(4);
      this.putUTF(var1, "Sprinting");
      var1.putInt(1);
      this.putUTF(var1, "Fitness");
      var1.putInt(6);
      this.putUTF(var1, "Strength");
      var1.putInt(6);
      this.putUTF(var1, "Axe");
      var1.putInt(1);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)Math.round(Math.random() * 5.0));
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)0);
      int var2 = this.player.clothes.size();
      var1.put((byte)var2);

      for (Clothes var4 : this.player.clothes) {
         var1.put(var4.flags);
         this.putUTF(var1, "Base." + var4.name);
         this.putUTF(var1, null);
         this.putUTF(var1, var4.name);
         var1.put((byte)-1);
         var1.put((byte)-1);
         var1.put((byte)-1);
         var1.put(var4.text);
         var1.putFloat(0.0F);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
      }

      this.putUTF(var1, "fake_str");
      var1.putShort((short)0);
      var1.putInt(2);
      this.putUTF(var1, "Fit");
      this.putUTF(var1, "Stout");
      var1.putFloat(0.0F);
      var1.putInt(0);
      var1.putInt(0);
      var1.putInt(4);
      this.putUTF(var1, "Sprinting");
      var1.putFloat(75.0F);
      this.putUTF(var1, "Fitness");
      var1.putFloat(67500.0F);
      this.putUTF(var1, "Strength");
      var1.putFloat(67500.0F);
      this.putUTF(var1, "Axe");
      var1.putFloat(75.0F);
      var1.putInt(4);
      this.putUTF(var1, "Sprinting");
      var1.putInt(1);
      this.putUTF(var1, "Fitness");
      var1.putInt(6);
      this.putUTF(var1, "Strength");
      var1.putInt(6);
      this.putUTF(var1, "Axe");
      var1.putInt(1);
      var1.putInt(0);
      this.putBoolean(var1, true);
      this.putUTF(var1, "fake");
      var1.putFloat(this.player.tagColor.r);
      var1.putFloat(this.player.tagColor.g);
      var1.putFloat(this.player.tagColor.b);
      var1.putInt(0);
      var1.putDouble(0.0);
      var1.putInt(0);
      this.putUTF(var1, this.player.username);
      var1.putFloat(this.player.speakColor.r);
      var1.putFloat(this.player.speakColor.g);
      var1.putFloat(this.player.speakColor.b);
      this.putBoolean(var1, true);
      this.putBoolean(var1, false);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.putInt(0);
      var1.putInt(0);
   }

   private void sendPlayerExtraInfo(boolean var1, boolean var2) {
      ByteBuffer var3 = this.network.startPacket();
      this.doPacket(PacketType.ExtraInfo.getId(), var3);
      var3.putShort(this.player.OnlineID);
      var3.put((byte)0);
      var3.put((byte)(var1 ? 1 : 0));
      var3.put((byte)0);
      var3.put((byte)0);
      var3.put((byte)0);
      var3.put((byte)(Player.isVOIPEnabled ? 1 : 0));
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendSyncRadioData() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.SyncRadioData.getId(), var1);
      var1.put((byte)(Player.isVOIPEnabled ? 1 : 0));
      var1.putInt(4);
      var1.putInt(0);
      var1.putInt((int)RakVoice.GetMaxDistance());
      var1.putInt((int)this.player.x);
      var1.putInt((int)this.player.y);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendEquip() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.Equip.getId(), var1);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)1);
      var1.putInt(16);
      var1.putShort(this.player.registry_id);
      var1.put((byte)1);
      var1.putInt(this.player.weapon_id);
      var1.put((byte)0);
      var1.putInt(0);
      var1.putInt(0);
      var1.put((byte)0);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendChatMessage(String var1) {
      ByteBuffer var2 = this.network.startPacket();
      var2.putShort(this.player.OnlineID);
      var2.putInt(2);
      this.putUTF(var2, this.player.username);
      this.putUTF(var2, var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private int getBooleanVariables() {
      short var1 = 0;
      if (this.player.movement.speed > 0.0F) {
         switch (1.$SwitchMap$zombie$network$FakeClientManager$Movement$Motion[this.player.movement.motion.ordinal()]) {
            case 1:
               var1 |= 64;
               break;
            case 2:
               var1 |= 1;
               break;
            case 3:
               var1 |= 17;
               break;
            case 4:
               var1 |= 16;
               break;
            case 5:
               var1 |= 32;
         }

         var1 |= 17408;
      }

      return var1;
   }

   private void sendPlayer(Transform var1, int var2, Vector2 var3) {
      PlayerPacket var4 = new PlayerPacket();
      var4.id = this.player.OnlineID;
      var4.x = var1.position.x;
      var4.y = var1.position.y;
      var4.z = (byte)this.player.z;
      var4.direction = var3.getDirection();
      var4.usePathFinder = false;
      var4.moveType = PredictionTypes.None;
      var4.VehicleID = -1;
      var4.VehicleSeat = -1;
      var4.booleanVariables = this.getBooleanVariables();
      var4.footstepSoundRadius = 0;
      var4.bleedingLevel = 0;
      var4.realx = this.player.x;
      var4.realy = this.player.y;
      var4.realz = (byte)this.player.z;
      var4.realdir = (byte)IsoDirections.fromAngleActual(this.player.direction).index();
      var4.realt = var2;
      var4.collidePointX = -1.0F;
      var4.collidePointY = -1.0F;
      ByteBuffer var5 = this.network.startPacket();
      this.doPacket(PacketType.PlayerUpdateReliable.getId(), var5);
      ByteBufferWriter var6 = new ByteBufferWriter(var5);
      var4.write(var6);
      this.network.endPacket(this.connectionGUID);
   }

   private boolean receivePlayerConnect(ByteBuffer var1) {
      short var2 = var1.getShort();
      if (var2 == -1) {
         byte var3 = var1.get();
         var2 = var1.getShort();
         this.player.OnlineID = var2;
         return true;
      } else {
         return false;
      }
   }

   private boolean receivePlayerExtraInfo(ByteBuffer var1) {
      short var2 = var1.getShort();
      return var2 == this.player.OnlineID;
   }

   private boolean receiveChunkPart(ByteBuffer var1) {
      boolean var2 = false;
      int var3 = var1.getInt();
      int var4 = var1.getInt();
      int var5 = var1.getInt();
      int var6 = var1.getInt();
      int var7 = var1.getInt();
      int var8 = var1.getInt();
      if (this.requests.remove(var3) != null) {
         var2 = true;
      }

      return var2;
   }

   private boolean receiveNotRequired(ByteBuffer var1) {
      boolean var2 = false;
      int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
         int var5 = var1.getInt();
         boolean var6 = var1.get() == 1;
         if (this.requests.remove(var5) != null) {
            var2 = true;
         }
      }

      return var2;
   }

   private boolean allChunkPartsReceived() {
      return this.requests.size() == 0;
   }

   private void addChunkRequest(int var1, int var2, int var3, int var4) {
      Request var5 = new Request(var1, var2, this.requestId);
      this.requestId++;
      this.requests.put(var5.id, var5);
   }

   private void requestZipList() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.RequestZipList.getId(), var1);
      var1.putInt(this.requests.size());

      for (Request var3 : this.requests.values()) {
         var1.putInt(var3.id);
         var1.putInt(var3.wx);
         var1.putInt(var3.wy);
         var1.putLong(var3.crc);
      }

      this.network.endPacket(this.connectionGUID);
   }

   private void requestLargeAreaZip() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.RequestLargeAreaZip.getId(), var1);
      var1.putInt(this.player.WorldX);
      var1.putInt(this.player.WorldY);
      var1.putInt(13);
      this.network.endPacketImmediate(this.connectionGUID);
      int var2 = this.player.WorldX - 6 + 2;
      int var3 = this.player.WorldY - 6 + 2;
      int var4 = this.player.WorldX + 6 + 2;
      int var5 = this.player.WorldY + 6 + 2;

      for (int var6 = var3; var6 <= var5; var6++) {
         for (int var7 = var2; var7 <= var4; var7++) {
            Request var8 = new Request(var7, var6, this.requestId);
            this.requestId++;
            this.requests.put(var8.id, var8);
         }
      }

      this.requestZipList();
   }

   private void requestFullUpdate() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.IsoRegionClientRequestFullUpdate.getId(), var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void requestChunkObjectState() {
      for (Request var2 : this.requests.values()) {
         ByteBuffer var3 = this.network.startPacket();
         this.doPacket(PacketType.ChunkObjectState.getId(), var3);
         var3.putShort((short)var2.wx);
         var3.putShort((short)var2.wy);
         this.network.endPacket(this.connectionGUID);
      }
   }

   private void requestChunks() {
      if (!this.requests.isEmpty()) {
         this.requestZipList();
         this.requestChunkObjectState();
         this.requests.clear();
      }
   }

   private void sendStatisticsEnable(int var1) {
      ByteBuffer var2 = this.network.startPacket();
      this.doPacket(PacketType.StatisticRequest.getId(), var2);
      var2.put((byte)3);
      var2.putInt(var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void receiveStatistics(ByteBuffer var1) {
      long var2 = var1.getLong();
      long var4 = var1.getLong();
      long var6 = var1.getLong();
      long var8 = var1.getLong();
      long var10 = var1.getLong();
      long var12 = var1.getLong();
      long var14 = var1.getLong();
      long var16 = var1.getLong();
      long var18 = var1.getLong();
      FakeClientManager.info(
         this.player.movement.id,
         String.format(
            "ServerStats: con=[%2d] fps=[%2d] tps=[%2d] upt=[%4d-%4d/%4d], c1=[%d] c2=[%d] c3=[%d]", var12, var8, var10, var2, var4, var6, var14, var16, var18
         )
      );
   }

   private void sendTimeSync() {
      ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.TimeSync.getId(), var1);
      long var2 = System.nanoTime();
      var1.putLong(var2);
      var1.putLong(0L);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void receiveTimeSync(ByteBuffer var1) {
      long var2 = var1.getLong();
      long var4 = var1.getLong();
      long var6 = System.nanoTime();
      long var8 = var6 - var2;
      long var10 = var4 - var6 + var8 / 2L;
      long var12 = serverTimeShift;
      if (!serverTimeShiftIsSet) {
         serverTimeShift = var10;
      } else {
         serverTimeShift = (long)((float)serverTimeShift + (float)(var10 - serverTimeShift) * 0.05F);
      }

      long var14 = 10000000L;
      if (Math.abs(serverTimeShift - var12) > var14) {
         this.sendTimeSync();
      } else {
         serverTimeShiftIsSet = true;
      }
   }

   private void receiveSyncClock(ByteBuffer var1) {
      FakeClientManager.trace(this.player.movement.id, String.format("Player %3d sync clock", this.player.OnlineID));
   }

   private void receiveKicked(ByteBuffer var1) {
      String var2 = FakeClientManager.ReadStringUTF(var1);
      FakeClientManager.info(this.player.movement.id, String.format("Client kicked. Reason: %s", var2));
   }

   private void receiveChecksum(ByteBuffer var1) {
      FakeClientManager.trace(this.player.movement.id, String.format("Player %3d receive Checksum", this.player.OnlineID));
      short var2 = var1.getShort();
      boolean var3 = var1.get() == 1;
      boolean var4 = var1.get() == 1;
      if (var2 != 1 || !var3 || !var4) {
         FakeClientManager.info(this.player.movement.id, String.format("checksum lua: %b, script: %b", var3, var4));
      }

      this.changeState(State.PLAYER_EXTRA_INFO);
   }

   private void receiveKillZombie(ByteBuffer var1) {
      FakeClientManager.trace(this.player.movement.id, String.format("Player %3d receive KillZombie", this.player.OnlineID));
      short var2 = var1.getShort();
      Zombie var3 = (Zombie)this.player.simulator.zombies.get(Integer.valueOf(var2));
      if (var3 != null) {
         this.player.simulator.zombies4Delete.add(var3);
      }
   }

   private void receiveTeleport(ByteBuffer var1) {
      byte var2 = var1.get();
      float var3 = var1.getFloat();
      float var4 = var1.getFloat();
      float var5 = var1.getFloat();
      FakeClientManager.info(this.player.movement.id, String.format("Player %3d teleport to (%d, %d)", this.player.OnlineID, (int)var3, (int)var4));
      this.player.x = var3;
      this.player.y = var4;
   }

   private void receiveZombieSimulation(ByteBuffer var1) {
      this.player.simulator.clear();
      boolean var2 = var1.get() == 1;
      short var3 = var1.getShort();

      for (short var4 = 0; var4 < var3; var4++) {
         short var5 = var1.getShort();
         Zombie var6 = (Zombie)this.player.simulator.zombies.get(Integer.valueOf(var5));
         this.player.simulator.zombies4Delete.add(var6);
      }

      short var7 = var1.getShort();

      for (short var8 = 0; var8 < var7; var8++) {
         short var9 = var1.getShort();
         this.player.simulator.add(var9);
      }

      this.player.simulator.receivePacket(var1);
      this.player.simulator.process();
   }

   private void sendInjuries() {
      SyncInjuriesPacket var1 = new SyncInjuriesPacket();
      var1.id = this.player.OnlineID;
      var1.strafeSpeed = 1.0F;
      var1.walkSpeed = 1.0F;
      var1.walkInjury = 0.0F;
      ByteBuffer var2 = this.network.startPacket();
      this.doPacket(PacketType.SyncInjuries.getId(), var2);
      ByteBufferWriter var3 = new ByteBufferWriter(var2);
      var1.write(var3);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendChecksum() {
      if (!luaChecksum.isEmpty()) {
         FakeClientManager.trace(this.player.movement.id, String.format("Player %3d sendChecksum", this.player.OnlineID));
         ByteBuffer var1 = this.network.startPacket();
         this.doPacket(PacketType.Checksum.getId(), var1);
         var1.putShort((short)1);
         this.putUTF(var1, luaChecksum);
         this.putUTF(var1, scriptChecksum);
         this.network.endPacketImmediate(this.connectionGUID);
      }
   }

   public void sendCommand(String var1) {
      ByteBuffer var2 = this.network.startPacket();
      this.doPacket(PacketType.ReceiveCommand.getId(), var2);
      FakeClientManager.WriteStringUTF(var2, var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendEventPacket(short var1, int var2, int var3, int var4, byte var5, String var6) {
      ByteBuffer var7 = this.network.startPacket();
      this.doPacket(PacketType.EventPacket.getId(), var7);
      var7.putShort(var1);
      var7.putFloat(var2);
      var7.putFloat(var3);
      var7.putFloat(var4);
      var7.put(var5);
      FakeClientManager.WriteStringUTF(var7, var6);
      FakeClientManager.WriteStringUTF(var7, "");
      FakeClientManager.WriteStringUTF(var7, "");
      FakeClientManager.WriteStringUTF(var7, "");
      var7.putFloat(1.0F);
      var7.putFloat(1.0F);
      var7.putFloat(0.0F);
      var7.putInt(0);
      var7.putShort((short)0);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   private void sendWorldSound4Player(int var1, int var2, int var3, int var4, int var5) {
      ByteBuffer var6 = this.network.startPacket();
      this.doPacket(PacketType.WorldSound.getId(), var6);
      var6.putInt(var1);
      var6.putInt(var2);
      var6.putInt(var3);
      var6.putInt(var4);
      var6.putInt(var5);
      var6.put((byte)0);
      var6.putFloat(0.0F);
      var6.putFloat(1.0F);
      var6.put((byte)0);
      this.network.endPacketImmediate(this.connectionGUID);
   }
}
