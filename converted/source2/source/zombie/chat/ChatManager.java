package zombie.chat;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import zombie.GameWindow;
import zombie.Lua.LuaEventManager;
import zombie.characters.Faction;
import zombie.characters.IsoPlayer;
import zombie.chat.ChatManager.1;
import zombie.chat.ChatManager.Stage;
import zombie.chat.defaultChats.AdminChat;
import zombie.chat.defaultChats.FactionChat;
import zombie.chat.defaultChats.GeneralChat;
import zombie.chat.defaultChats.RadioChat;
import zombie.chat.defaultChats.SafehouseChat;
import zombie.chat.defaultChats.SayChat;
import zombie.chat.defaultChats.ServerChat;
import zombie.chat.defaultChats.ShoutChat;
import zombie.chat.defaultChats.WhisperChat;
import zombie.chat.defaultChats.WhisperChat.ChatStatus;
import zombie.core.Core;
import zombie.core.Translator;
import zombie.core.logger.ExceptionLogger;
import zombie.core.logger.LoggerManager;
import zombie.core.logger.ZLogger;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.core.raknet.VoiceManagerData;
import zombie.core.raknet.VoiceManagerData.RadioData;
import zombie.debug.DebugLog;
import zombie.inventory.types.Radio;
import zombie.iso.areas.SafeHouse;
import zombie.network.GameClient;
import zombie.network.PacketTypes.PacketType;
import zombie.network.chat.ChatType;
import zombie.radio.devices.DeviceData;

public class ChatManager {
   private static ChatManager instance = null;
   private UdpConnection serverConnection = null;
   private final HashMap<Integer, ChatBase> mpChats;
   private final HashMap<String, WhisperChat> whisperChats;
   private final HashMap<String, WhisperChatCreation> whisperChatCreation = new HashMap<>();
   private final HashMap<Short, ChatTab> tabs;
   private ChatTab focusTab;
   private IsoPlayer player;
   private String myNickname;
   private boolean singlePlayerMode = false;
   private GeneralChat generalChat = null;
   private SayChat sayChat = null;
   private ShoutChat shoutChat = null;
   private FactionChat factionChat = null;
   private SafehouseChat safehouseChat = null;
   private RadioChat radioChat = null;
   private AdminChat adminChat = null;
   private ServerChat serverChat = null;
   private Stage chatManagerStage = Stage.notStarted;
   private static volatile ZLogger logger;
   private static final String logNamePrefix = "client chat";

   private ChatManager() {
      this.mpChats = new HashMap<>();
      this.tabs = new HashMap<>();
      this.whisperChats = new HashMap<>();
   }

   public static ChatManager getInstance() {
      if (instance == null) {
         instance = new ChatManager();
      }

      return instance;
   }

   public boolean isSinglePlayerMode() {
      return this.singlePlayerMode;
   }

   public boolean isWorking() {
      return this.chatManagerStage == Stage.working;
   }

   public void init(boolean var1, IsoPlayer var2) {
      LoggerManager.init();
      LoggerManager.createLogger("client chat " + var2.getDisplayName(), Core.bDebug);
      logger = LoggerManager.getLogger("client chat " + var2.getDisplayName());
      logger.write("Init chat system...", "info");
      logger.write("Mode: " + (var1 ? "single player" : "multiplayer"), "info");
      logger.write("Chat owner: " + var2.getDisplayName(), "info");
      this.chatManagerStage = Stage.starting;
      this.singlePlayerMode = var1;
      this.generalChat = null;
      this.sayChat = null;
      this.shoutChat = null;
      this.factionChat = null;
      this.safehouseChat = null;
      this.radioChat = null;
      this.adminChat = null;
      this.serverChat = null;
      this.mpChats.clear();
      this.tabs.clear();
      this.focusTab = null;
      this.whisperChats.clear();
      this.player = var2;
      this.myNickname = this.player.username;
      if (var1) {
         this.serverConnection = null;
         this.sayChat = new SayChat();
         this.sayChat.Init();
         this.generalChat = new GeneralChat();
         this.shoutChat = new ShoutChat();
         this.shoutChat.Init();
         this.radioChat = new RadioChat();
         this.radioChat.Init();
         this.adminChat = new AdminChat();
      } else {
         this.serverConnection = GameClient.connection;
         LuaEventManager.triggerEvent("OnChatWindowInit");
      }
   }

   public void processInitPlayerChatPacket(ByteBuffer var1) {
      this.init(false, IsoPlayer.getInstance());
      short var2 = var1.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
         ChatTab var4 = new ChatTab(var1.getShort(), GameWindow.ReadString(var1));
         this.tabs.put(var4.getID(), var4);
      }

      this.addTab((short)0);
      this.focusOnTab(this.tabs.get((short)0).getID());
      LuaEventManager.triggerEvent("OnSetDefaultTab", this.tabs.get((short)0).getTitle());
   }

   public void setFullyConnected() {
      this.chatManagerStage = Stage.working;
   }

   public void processAddTabPacket(ByteBuffer var1) {
      this.addTab(var1.getShort());
   }

   public void processRemoveTabPacket(ByteBuffer var1) {
      this.removeTab(var1.getShort());
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public void processJoinChatPacket(ByteBuffer var1) {
      ChatType var2 = ChatType.valueOf(var1.getInt());
      ChatTab var3 = this.tabs.get(var1.getShort());
      Object var4 = null;
      switch (1.$SwitchMap$zombie$network$chat$ChatType[var2.ordinal()]) {
         case 1:
            this.generalChat = new GeneralChat(var1, var3, this.player);
            var4 = this.generalChat;
            break;
         case 2:
            this.sayChat = new SayChat(var1, var3, this.player);
            this.sayChat.Init();
            var4 = this.sayChat;
            break;
         case 3:
            this.shoutChat = new ShoutChat(var1, var3, this.player);
            this.shoutChat.Init();
            var4 = this.shoutChat;
            break;
         case 4:
            WhisperChat var5 = new WhisperChat(var1, var3, this.player);
            var5.init();
            this.whisperChats.put(var5.getCompanionName(), var5);
            var4 = var5;
            break;
         case 5:
            this.factionChat = new FactionChat(var1, var3, this.player);
            var4 = this.factionChat;
            break;
         case 6:
            this.safehouseChat = new SafehouseChat(var1, var3, this.player);
            var4 = this.safehouseChat;
            break;
         case 7:
            this.radioChat = new RadioChat(var1, var3, this.player);
            this.radioChat.Init();
            var4 = this.radioChat;
            break;
         case 8:
            this.adminChat = new AdminChat(var1, var3, this.player);
            var4 = this.adminChat;
            break;
         case 9:
            this.serverChat = new ServerChat(var1, var3, this.player);
            var4 = this.serverChat;
            break;
         default:
            DebugLog.log("Chat of type '" + var2.toString() + "' is not supported to join to");
            return;
      }

      this.mpChats.put(var4.getID(), (ChatBase)var4);
      var4.setFontSize(Core.getInstance().getOptionChatFontSize());
      var4.setShowTimestamp(Core.getInstance().isOptionShowChatTimestamp());
      var4.setShowTitle(Core.getInstance().isOptionShowChatTitle());
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public void processLeaveChatPacket(ByteBuffer var1) {
      Integer var2 = var1.getInt();
      ChatType var3 = ChatType.valueOf(var1.getInt());
      switch (1.$SwitchMap$zombie$network$chat$ChatType[var3.ordinal()]) {
         case 1:
         case 2:
         case 3:
         case 7:
         case 9:
            DebugLog.log("Chat type is '" + var3.toString() + "'. Can't leave it. Ignored.");
            break;
         case 4:
            this.whisperChats.remove(((WhisperChat)this.mpChats.get(var2)).getCompanionName());
            this.mpChats.remove(var2);
            break;
         case 5:
            this.mpChats.remove(var2);
            this.factionChat = null;
            DebugLog.log("You leaved faction chat");
            break;
         case 6:
            this.mpChats.remove(var2);
            this.safehouseChat = null;
            DebugLog.log("You leaved safehouse chat");
            break;
         case 8:
            this.mpChats.remove(var2);
            this.removeTab(this.adminChat.getTabID());
            this.adminChat = null;
            DebugLog.log("You leaved admin chat");
            break;
         default:
            DebugLog.log("Chat of type '" + var3.toString() + "' is not supported to leave to");
      }
   }

   public void processPlayerNotFound(String var1) {
      logger.write("Got player not found packet", "info");
      WhisperChatCreation var2 = this.whisperChatCreation.get(var1);
      if (var2 != null) {
         var2.status = ChatStatus.PlayerNotFound;
      }
   }

   public ChatMessage unpackMessage(ByteBuffer var1) {
      int var2 = var1.getInt();
      ChatBase var3 = this.mpChats.get(var2);
      return var3.unpackMessage(var1);
   }

   public void processChatMessagePacket(ByteBuffer var1) {
      ChatMessage var2 = this.unpackMessage(var1);
      ChatBase var3 = var2.getChat();
      if (ChatUtility.chatStreamEnabled(var3.getType())) {
         var3.showMessage(var2);
         logger.write("Got message from server: " + var2, "info");
      } else {
         DebugLog.log("Can't process message '" + var2.getText() + "' because '" + var3.getType() + "' chat is disabled");
         logger.write("Can't process message '" + var2.getText() + "' because '" + var3.getType() + "' chat is disabled", "warning");
      }
   }

   public void updateChatSettings(String var1, boolean var2, boolean var3) {
      Core.getInstance().setOptionChatFontSize(var1);
      Core.getInstance().setOptionShowChatTimestamp(var2);
      Core.getInstance().setOptionShowChatTitle(var3);

      for (ChatBase var5 : this.mpChats.values()) {
         var5.setFontSize(var1);
         var5.setShowTimestamp(var2);
         var5.setShowTitle(var3);
      }
   }

   public void showInfoMessage(String var1) {
      ChatMessage var2 = this.sayChat.createInfoMessage(var1);
      this.sayChat.showMessage(var2);
   }

   public void showInfoMessage(String var1, String var2) {
      if (this.sayChat != null) {
         ChatMessage var3 = this.sayChat.createInfoMessage(var2);
         var3.setAuthor(var1);
         this.sayChat.showMessage(var3);
      }
   }

   public void sendMessageToChat(String var1, ChatType var2, String var3) {
      var3 = var3.trim();
      if (!var3.isEmpty()) {
         ChatBase var4 = this.getChat(var2);
         if (var4 == null) {
            if (Core.bDebug) {
               throw new IllegalArgumentException("Chat '" + var2 + "' is null. Chat should be init before use!");
            } else {
               this.showChatDisabledMessage(var2);
            }
         } else {
            ChatMessage var5 = var4.createMessage(var3);
            var5.setAuthor(var1);
            this.sendMessageToChat(var4, var5);
         }
      }
   }

   public void sendMessageToChat(ChatType var1, String var2) {
      this.sendMessageToChat(this.player.getUsername(), var1, var2);
   }

   public synchronized void sendWhisperMessage(String var1, String var2) {
      logger.write("Send message '" + var2 + "' for player '" + var1 + "' in whisper chat", "info");
      if (ChatUtility.chatStreamEnabled(ChatType.whisper)) {
         if (var1 == null || var1.equalsIgnoreCase(this.myNickname)) {
            logger.write("Message can't be send to yourself");
            this.showServerChatMessage(Translator.getText("UI_chat_whisper_message_to_yourself_error"));
            return;
         }

         if (this.whisperChats.containsKey(var1)) {
            WhisperChat var5 = this.whisperChats.get(var1);
            this.sendMessageToChat(var5, var5.createMessage(var2));
            return;
         }

         if (this.whisperChatCreation.containsKey(var1)) {
            WhisperChatCreation var4 = this.whisperChatCreation.get(var1);
            var4.messages.add(var2);
            return;
         }

         WhisperChatCreation var3 = this.createWhisperChat(var1);
         var3.messages.add(var2);
      } else {
         logger.write("Whisper chat is disabled", "info");
         this.showChatDisabledMessage(ChatType.whisper);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public Boolean isPlayerCanUseChat(ChatType var1) {
      if (!ChatUtility.chatStreamEnabled(var1)) {
         return false;
      } else {
         switch (1.$SwitchMap$zombie$network$chat$ChatType[var1.ordinal()]) {
            case 5:
               return Faction.isAlreadyInFaction(this.player);
            case 6:
               return SafeHouse.hasSafehouse(this.player) != null;
            case 7:
               return this.isPlayerCanUseRadioChat();
            case 8:
               return this.player.isAccessLevel("admin");
            default:
               return true;
         }
      }
   }

   public void focusOnTab(Short var1) {
      for (ChatTab var3 : this.tabs.values()) {
         if (var3.getID() == var1) {
            this.focusTab = var3;
            return;
         }
      }

      throw new RuntimeException("Tab with id = '" + var1 + "' not found");
   }

   public String getTabName(short var1) {
      return this.tabs.containsKey(var1) ? this.tabs.get(var1).getTitle() : Short.toString(var1);
   }

   public ChatTab getFocusTab() {
      return this.focusTab;
   }

   public void showRadioMessage(ChatMessage var1) {
      this.radioChat.showMessage(var1);
   }

   public void showRadioMessage(String var1, int var2) {
      ChatMessage var3 = this.radioChat.createMessage(var1);
      if (var2 != 0) {
         var3.setRadioChannel(var2);
      }

      this.radioChat.showMessage(var3);
   }

   public void showStaticRadioSound(String var1) {
      this.radioChat.showMessage(this.radioChat.createStaticSoundMessage(var1));
   }

   public ChatMessage createRadiostationMessage(String var1, int var2) {
      return this.radioChat.createBroadcastingMessage(var1, var2);
   }

   public void showServerChatMessage(String var1) {
      ServerChatMessage var2 = this.serverChat.createServerMessage(var1);
      this.serverChat.showMessage(var2);
   }

   private void addMessage(int var1, String var2, String var3) {
      ChatBase var4 = this.mpChats.get(var1);
      var4.showMessage(var3, var2);
   }

   public void addMessage(String var1, String var2) throws RuntimeException {
      if (this.generalChat == null) {
         throw new RuntimeException();
      } else {
         this.addMessage(this.generalChat.getID(), var1, var2);
      }
   }

   private void sendMessageToChat(ChatBase var1, ChatMessage var2) {
      if (var1.getType() == ChatType.radio) {
         if (Core.bDebug) {
            throw new IllegalArgumentException("You can't send message to radio directly. Use radio and send say message");
         } else {
            DebugLog.log("You try to use radio chat directly. It's restricted. Try to use say chat");
         }
      } else {
         var1.showMessage(var2);
         if (var1.isEnabled()) {
            if (!this.isSinglePlayerMode() && !var2.isLocal()) {
               DeviceData var3 = this.getTransmittingRadio();
               var1.sendToServer(var2, var3);
               if (var3 != null && var1.isSendingToRadio()) {
                  ChatMessage var4 = this.radioChat.createMessage(var2.getText());
                  var4.setRadioChannel(var3.getChannel());
                  this.radioChat.sendToServer(var4, var3);
               }
            }
         } else {
            this.showChatDisabledMessage(var1.getType());
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private ChatBase getChat(ChatType var1) {
      if (var1 == ChatType.whisper) {
         throw new IllegalArgumentException("Whisper not unique chat");
      } else {
         switch (1.$SwitchMap$zombie$network$chat$ChatType[var1.ordinal()]) {
            case 1:
               return this.generalChat;
            case 2:
               return this.sayChat;
            case 3:
               return this.shoutChat;
            case 4:
            default:
               throw new IllegalArgumentException("Chat type is undefined");
            case 5:
               return this.factionChat;
            case 6:
               return this.safehouseChat;
            case 7:
               return this.radioChat;
            case 8:
               return this.adminChat;
            case 9:
               return this.serverChat;
         }
      }
   }

   private void addTab(short var1) {
      ChatTab var2 = this.tabs.get(var1);
      if (!var2.isEnabled()) {
         var2.setEnabled(true);
         LuaEventManager.triggerEvent("OnTabAdded", var2.getTitle(), var2.getID());
      }
   }

   private void removeTab(Short var1) {
      ChatTab var2 = this.tabs.get(var1);
      if (var2.isEnabled()) {
         LuaEventManager.triggerEvent("OnTabRemoved", var2.getTitle(), var2.getID());
         var2.setEnabled(false);
      }
   }

   private WhisperChatCreation createWhisperChat(String var1) {
      logger.write("Whisper chat is not created for '" + var1 + "'", "info");
      WhisperChatCreation var2 = new WhisperChatCreation();
      var2.destPlayerName = var1;
      var2.status = ChatStatus.Creating;
      var2.createTime = System.currentTimeMillis();
      this.whisperChatCreation.put(var1, var2);
      ByteBufferWriter var3 = this.serverConnection.startPacket();
      PacketType.PlayerStartPMChat.doPacket(var3);
      var3.putUTF(this.myNickname);
      var3.putUTF(var1);
      PacketType.PlayerStartPMChat.send(this.serverConnection);
      logger.write("'Start PM chat' package sent. Waiting for a creating whisper chat by server...", "info");
      return var2;
   }

   public static void UpdateClient() {
      if (instance != null) {
         try {
            instance.updateClient();
         } catch (Throwable var1) {
            ExceptionLogger.logException(var1);
         }
      }
   }

   private void updateClient() {
      if (this.isWorking()) {
         this.updateWhisperChat();
      }
   }

   private void updateWhisperChat() {
      if (!this.whisperChatCreation.isEmpty()) {
         long var1 = System.currentTimeMillis();

         for (WhisperChatCreation var5 : new ArrayList<>(this.whisperChatCreation.values())) {
            if (this.whisperChats.containsKey(var5.destPlayerName)) {
               WhisperChat var6 = this.whisperChats.get(var5.destPlayerName);
               logger.write("Whisper chat created between '" + this.myNickname + "' and '" + var5.destPlayerName + "' and has id = " + var6.getID(), "info");
               this.whisperChatCreation.remove(var5.destPlayerName);

               for (String var8 : var5.messages) {
                  this.sendMessageToChat(var6, var6.createMessage(var8));
               }
            } else if (var5.status == ChatStatus.PlayerNotFound) {
               logger.write("Player '" + var5.destPlayerName + "' is not found. Chat is not created", "info");
               this.whisperChatCreation.remove(var5.destPlayerName);
               this.showServerChatMessage(Translator.getText("UI_chat_whisper_player_not_found_error", var5.destPlayerName));
            } else if (var5.status == ChatStatus.Creating && var1 - var5.createTime >= 10000L) {
               logger.write("Whisper chat is not created by timeout. See server chat logs", "error");
               this.whisperChatCreation.remove(var5.destPlayerName);
            }
         }
      }
   }

   private void showChatDisabledMessage(ChatType var1) {
      StringBuilder var2 = new StringBuilder();
      var2.append(Translator.getText("UI_chat_chat_disabled_msg", Translator.getText(var1.getTitleID())));

      for (ChatType var5 : ChatUtility.getAllowedChatStreams()) {
         if (this.isPlayerCanUseChat(var5)) {
            var2.append("    * ").append(Translator.getText(var5.getTitleID())).append(" <LINE> ");
         }
      }

      this.showServerChatMessage(var2.toString());
   }

   private boolean isPlayerCanUseRadioChat() {
      Radio var1 = this.player.getEquipedRadio();
      if (var1 != null && var1.getDeviceData() != null) {
         boolean var2 = var1.getDeviceData().getIsTurnedOn();
         var2 &= var1.getDeviceData().getIsTwoWay();
         var2 &= var1.getDeviceData().getIsPortable();
         return var2 & !var1.getDeviceData().getMicIsMuted();
      } else {
         return false;
      }
   }

   private DeviceData getTransmittingRadio() {
      if (this.player.getOnlineID() == -1) {
         return null;
      } else {
         VoiceManagerData var1 = VoiceManagerData.get(this.player.getOnlineID());
         synchronized (var1.radioData) {
            return var1.radioData.stream().filter(RadioData::isTransmissionAvailable).findFirst().<DeviceData>map(RadioData::getDeviceData).orElse(null);
         }
      }
   }
}
