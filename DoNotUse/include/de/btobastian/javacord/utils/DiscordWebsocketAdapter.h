#pragma once
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/SettableFuture.h"
#include "com/neovisionaries/ws/client/WebSocket.h"
#include "com/neovisionaries/ws/client/WebSocketAdapter.h"
#include "com/neovisionaries/ws/client/WebSocketException.h"
#include "com/neovisionaries/ws/client/WebSocketFactory.h"
#include "com/neovisionaries/ws/client/WebSocketFrame.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/utils/DiscordWebsocketAdapter/1.h"
#include "de/btobastian/javacord/utils/DiscordWebsocketAdapter/2.h"
#include "de/btobastian/javacord/utils/handler/ReadyHandler.h"
#include "de/btobastian/javacord/utils/handler/ResumedHandler.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelCreateHandler.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelDeleteHandler.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageAckHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageBulkDeleteHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageCreateHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageDeleteHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageReactionAddHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageReactionRemoveHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/message/TypingStartHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildBanAddHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildBanRemoveHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildCreateHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildDeleteHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMemberAddHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMemberRemoveHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMemberUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMembersChunkHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleCreateHandler.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleDeleteHandler.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/user/PresenceUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/user/UserGuildSettingsUpdateHandler.h"
#include "de/btobastian/javacord/utils/handler/voice/VoiceStateUpdateHandler.h"
#include "java/security/NoSuchAlgorithmException.h"
#include "javax/net/ssl/SSLContext.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class DiscordWebsocketAdapter : public WebSocketAdapter {
public:
    static const Logger logger = LoggerUtil.getLogger(DiscordWebsocketAdapter.class);
    const ImplDiscordAPI api;
   private const std::unordered_map<std::string, PacketHandler> handlers = std::make_unique<std::unordered_map<>>();
   private const SettableFuture<bool> ready = SettableFuture.create();
    const std::string gateway;
    WebSocket websocket = nullptr;
    Timer heartbeatTimer = nullptr;
    int heartbeatInterval = -1;
    int lastSeq = -1;
    std::string sessionId = nullptr;
    bool heartbeatAckReceived = false;
    bool reconnect = true;
    long lastGuildMembersChunkReceived = System.currentTimeMillis();
   private std::queue<int64_t> ratelimitQueue = std::make_unique<std::list<>>();
    int reconnectAttempts = 5;
    int ratelimitResetIntervalInSeconds = 300;

    public DiscordWebsocketAdapter(ImplDiscordAPI api, const std::string& gateway) {
      this.api = api;
      this.gateway = gateway;
      this.registerHandlers();
      this.connect();
   }

    void disconnect() {
      this.reconnect = false;
      this.websocket.sendClose(1000);
   }

    void connect() {
    WebSocketFactory factory = std::make_shared<WebSocketFactory>();

      try {
         factory.setSSLContext(SSLContext.getDefault());
      } catch (NoSuchAlgorithmException var4) {
         logger.warn("An error occurred while setting ssl context", var4);
      }

      try {
         this.websocket = factory.createSocket(this.gateway + "?encoding=json&v=6");
         this.websocket.addHeader("Accept-Encoding", "gzip");
         this.websocket.addListener(this);
         this.websocket.connect();
      } catch (WebSocketException | IOException var3) {
         logger.warn("An error occurred while connecting to websocket", var3);
      }
   }

    void onConnected(WebSocket websocket, List<std::string>> headers) {
      if (this.sessionId == nullptr) {
         this.sendIdentify(websocket);
      } else {
         this.sendResume(websocket);
      }
   }

    void onDisconnected(WebSocket websocket, WebSocketFrame serverCloseFrame, WebSocketFrame clientCloseFrame, bool closedByServer) {
      if (closedByServer) {
         logger.info(
            "Websocket closed with reason {} and code {} by server!",
            serverCloseFrame != nullptr ? serverCloseFrame.getCloseReason() : "unknown",
            serverCloseFrame != nullptr ? serverCloseFrame.getCloseCode() : "unknown"
         );
      } else {
         switch (clientCloseFrame == nullptr ? -1 : clientCloseFrame.getCloseCode()) {
            case 1002:
            case 1008:
               logger.debug("Websocket closed! Trying to resume connection.");
               break;
            default:
               logger.info(
                  "Websocket closed with reason {} and code {} by client!",
                  clientCloseFrame != nullptr ? clientCloseFrame.getCloseReason() : "unknown",
                  clientCloseFrame != nullptr ? clientCloseFrame.getCloseCode() : "unknown"
               );
         }
      }

      if (!this.ready.isDone()) {
         this.ready.set(false);
      } else {
         if (this.heartbeatTimer != nullptr) {
            this.heartbeatTimer.cancel();
            this.heartbeatTimer = nullptr;
         }

         if (this.reconnect) {
            this.ratelimitQueue.offer(System.currentTimeMillis());
            if (this.ratelimitQueue.size() > this.reconnectAttempts) {
    long timestamp = this.ratelimitQueue.poll();
               if (System.currentTimeMillis() - 1000 * this.ratelimitResetIntervalInSeconds < timestamp) {
                  logger.error(
                     "Websocket connection failed more than {} times in the last {} seconds! Stopping reconnecting.",
                     this.reconnectAttempts,
                     this.ratelimitResetIntervalInSeconds
                  );
                  return;
               }
            }

            this.connect();
         }
      }
   }

    void onTextMessage(WebSocket websocket, const std::string& text) {
    JSONObject packet = std::make_shared<JSONObject>(text);
    int op = packet.getInt("op");
      switch (op) {
         case 0:
            this.lastSeq = packet.getInt("s");
    std::string type = packet.getString("t");
    PacketHandler handler = this.handlers.get(type);
            if (handler != nullptr) {
               handler.handlePacket(packet.getJSONObject("d"));
            } else {
               logger.debug("Received unknown packet of type {} (packet: {})", type, packet);
            }

            if (type == "GUILD_MEMBERS_CHUNK")) {
               this.lastGuildMembersChunkReceived = System.currentTimeMillis();
            }

            if (type == "RESUMED")) {
               this.heartbeatAckReceived = true;
               this.heartbeatTimer = this.startHeartbeat(websocket, this.heartbeatInterval);
               logger.debug("Received RESUMED packet");
            }

            if (type == "READY") && this.sessionId == nullptr) {
               this.heartbeatAckReceived = true;
               this.heartbeatTimer = this.startHeartbeat(websocket, this.heartbeatInterval);
               this.sessionId = packet.getJSONObject("d").getString("session_id");
               if (this.api.isWaitingForServersOnStartup()) {
                  this.api.getThreadPool().getSingleThreadExecutorService("startupWait").submit(std::make_shared<1>(this));
               } else {
                  this.ready.set(true);
               }

               logger.debug("Received READY packet");
            } else if (type == "READY")) {
               this.heartbeatAckReceived = true;
               this.heartbeatTimer = this.startHeartbeat(websocket, this.heartbeatInterval);
            }
            break;
         case 1:
            this.sendHeartbeat(websocket);
            break;
         case 2:
         case 3:
         case 4:
         case 5:
         case 6:
         case 8:
         default:
            logger.debug("Received unknown packet (op: {}, content: {})", op, packet);
            break;
         case 7:
            logger.debug("Received op 7 packet. Reconnecting...");
            websocket.sendClose(1000);
            this.connect();
            break;
         case 9:
            logger.info("Could not resume session. Reconnecting now...");
            this.sendIdentify(websocket);
            break;
         case 10:
    JSONObject data = packet.getJSONObject("d");
            this.heartbeatInterval = data.getInt("heartbeat_interval");
            logger.debug("Received HELLO packet");
            break;
         case 11:
            this.heartbeatAckReceived = true;
      }
   }

    void onBinaryMessage(WebSocket websocket, byte[] binary) {
    Inflater decompressor = std::make_shared<Inflater>();
      decompressor.setInput(binary);
    ByteArrayOutputStream bos = std::make_shared<ByteArrayOutputStream>(binary.length);
      byte[] buf = new byte[1024];

      while (!decompressor.finished()) {
    int count;
         try {
            count = decompressor.inflate(buf);
         } catch (DataFormatException var10) {
            logger.warn("An error occurred while decompressing data", var10);
            return;
         }

         bos.write(buf, 0, count);
      }

      try {
         bos.close();
      } catch (IOException var9) {
      }

      byte[] decompressedData = bos.toByteArray();

      try {
         this.onTextMessage(websocket, new std::string(decompressedData, "UTF-8"));
      } catch (UnsupportedEncodingException var8) {
         logger.warn("An error occurred while decompressing data", var8);
      }
   }

    Timer startHeartbeat(WebSocket websocket, int heartbeatInterval) {
    Timer timer = std::make_shared<Timer>(true);
      timer.scheduleAtFixedRate(std::make_shared<2>(this, websocket, heartbeatInterval), 0L, heartbeatInterval);
    return timer;
   }

    void sendHeartbeat(WebSocket websocket) {
    JSONObject heartbeatPacket = std::make_shared<JSONObject>();
      heartbeatPacket.put("op", 1);
      heartbeatPacket.put("d", this.lastSeq);
      websocket.sendText(heartbeatPacket);
   }

    void sendResume(WebSocket websocket) {
      JSONObject resumePacket = std::make_unique<JSONObject>()
         .put("op", 6)
         .put("d", std::make_unique<JSONObject>().put("token", this.api.getToken()).put("session_id", this.sessionId).put("seq", this.lastSeq));
      logger.debug("Sending resume packet");
      websocket.sendText(resumePacket);
   }

    void sendIdentify(WebSocket websocket) {
      JSONObject identifyPacket = std::make_unique<JSONObject>()
         .put("op", 2)
         .put(
            "d",
    std::make_shared<JSONObject>();
               .put("token", this.api.getToken())
               .put(
                  "properties",
    std::make_shared<JSONObject>();
                     .put("$os", System.getProperty("os.name"))
                     .put("$browser", "Javacord")
                     .put("$device", "Javacord")
                     .put("$referrer", "")
                     .put("$referring_domain", "")
               )
               .put("compress", true)
               .put("large_threshold", 250)
         );
      logger.debug("Sending identify packet");
      websocket.sendText(identifyPacket);
   }

    void registerHandlers() {
      this.addHandler(std::make_shared<ReadyHandler>(this.api));
      this.addHandler(std::make_shared<ResumedHandler>(this.api));
      this.addHandler(std::make_shared<ChannelCreateHandler>(this.api));
      this.addHandler(std::make_shared<ChannelDeleteHandler>(this.api));
      this.addHandler(std::make_shared<ChannelUpdateHandler>(this.api));
      this.addHandler(std::make_shared<MessageAckHandler>(this.api));
      this.addHandler(std::make_shared<MessageBulkDeleteHandler>(this.api));
      this.addHandler(std::make_shared<MessageCreateHandler>(this.api));
      this.addHandler(std::make_shared<MessageDeleteHandler>(this.api));
      this.addHandler(std::make_shared<MessageReactionAddHandler>(this.api));
      this.addHandler(std::make_shared<MessageReactionRemoveHandler>(this.api));
      this.addHandler(std::make_shared<MessageUpdateHandler>(this.api));
      this.addHandler(std::make_shared<TypingStartHandler>(this.api));
      this.addHandler(std::make_shared<GuildBanAddHandler>(this.api));
      this.addHandler(std::make_shared<GuildBanRemoveHandler>(this.api));
      this.addHandler(std::make_shared<GuildCreateHandler>(this.api));
      this.addHandler(std::make_shared<GuildDeleteHandler>(this.api));
      this.addHandler(std::make_shared<GuildMemberAddHandler>(this.api));
      this.addHandler(std::make_shared<GuildMemberRemoveHandler>(this.api));
      this.addHandler(std::make_shared<GuildMembersChunkHandler>(this.api));
      this.addHandler(std::make_shared<GuildMemberUpdateHandler>(this.api));
      this.addHandler(std::make_shared<GuildUpdateHandler>(this.api));
      this.addHandler(std::make_shared<GuildRoleCreateHandler>(this.api));
      this.addHandler(std::make_shared<GuildRoleDeleteHandler>(this.api));
      this.addHandler(std::make_shared<GuildRoleUpdateHandler>(this.api));
      this.addHandler(std::make_shared<PresenceUpdateHandler>(this.api));
      this.addHandler(std::make_shared<UserGuildSettingsUpdateHandler>(this.api));
      this.addHandler(std::make_shared<VoiceStateUpdateHandler>(this.api));
   }

    void addHandler(PacketHandler handler) {
      this.handlers.put(handler.getType(), handler);
   }

    WebSocket getWebSocket() {
      return this.websocket;
   }

   public Future<bool> isReady() {
      return this.ready;
   }

    void updateStatus() {
      logger.debug("Updating status (game: {}, idle: {})", this.api.getGame() == nullptr ? "none" : this.api.getGame(), this.api.isIdle());
    JSONObject game = std::make_shared<JSONObject>();
      game.put("name", this.api.getGame() == nullptr ? JSONObject.NULL : this.api.getGame());
      game.put("type", this.api.getStreamingUrl() == nullptr ? 0 : 1);
      if (this.api.getStreamingUrl() != nullptr) {
         game.put("url", this.api.getStreamingUrl());
      }

      JSONObject updateStatus = std::make_unique<JSONObject>()
         .put("op", 3)
         .put("d", std::make_unique<JSONObject>().put("status", "online").put("afk", false).put("game", game).put("since", this.api.isIdle() ? 1 : JSONObject.NULL));
      logger.debug(updateStatus.toString(2));
      this.websocket.sendText(updateStatus);
   }

    void setRatelimitResetIntervalInSeconds(int ratelimitResetIntervalInSeconds) {
      this.ratelimitResetIntervalInSeconds = ratelimitResetIntervalInSeconds;
   }

    void setReconnectAttempts(int reconnectAttempts) {
      this.reconnectAttempts = reconnectAttempts;
   }

    void onError(WebSocket websocket, WebSocketException cause) {
    std::string var3 = cause.getMessage();
      switch (var3) {
         default:
            logger.warn("Websocket error!", cause);
         case "Flushing frames to the server failed: Connection closed by remote host":
         case "Flushing frames to the server failed: Socket is closed":
         case "Flushing frames to the server failed: Connection has been shutdown: javax.net.ssl.SSLException: java.net.SocketException: Connection reset":
         case "An I/O error occurred while a frame was being read from the web socket: Connection reset":
      }
   }

    void onUnexpectedError(WebSocket websocket, WebSocketException cause) {
      logger.warn("Websocket onUnexpected error!", cause);
   }

    void onConnectError(WebSocket websocket, WebSocketException exception) {
      logger.warn("Websocket onConnect error!", exception);
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
