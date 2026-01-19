package zombie.network;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import zombie.Lua.LuaEventManager;
import zombie.core.Core;
import zombie.core.logger.LoggerManager;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.core.utils.UpdateLimit;
import zombie.debug.DebugLog;
import zombie.gameStates.LoadingQueueState;
import zombie.network.LoginQueue.LoginQueueMessageType;
import zombie.network.PacketTypes.PacketType;

public class LoginQueue {
   private static ArrayList<UdpConnection> LoginQueue = new ArrayList<>();
   private static ArrayList<UdpConnection> PreferredLoginQueue = new ArrayList<>();
   private static UdpConnection currentLoginQueue;
   private static UpdateLimit UpdateLimit = new UpdateLimit(3050L);
   private static UpdateLimit LoginQueueTimeout = new UpdateLimit(15000L);

   public static void receiveClientLoginQueueRequest(ByteBuffer var0, short var1) {
      byte var2 = var0.get();
      if (var2 == LoginQueueMessageType.ConnectionImmediate.ordinal()) {
         LoadingQueueState.onConnectionImmediate();
      } else if (var2 == LoginQueueMessageType.PlaceInQueue.ordinal()) {
         int var3 = var0.getInt();
         LoadingQueueState.onPlaceInQueue(var3);
         LuaEventManager.triggerEvent("OnConnectionStateChanged", "FormatMessage", "PlaceInQueue", var3);
      }

      ConnectionManager.log("receive-packet", "login-queue-request", null);
   }

   public static void receiveLoginQueueDone(ByteBuffer var0, UdpConnection var1, short var2) {
      long var3 = var0.getLong();
      LoggerManager.getLogger("user").write("player " + var1.username + " loading time was: " + var3 + " ms");
      synchronized (LoginQueue) {
         if (currentLoginQueue == var1) {
            currentLoginQueue = null;
         }

         loadNextPlayer();
      }

      ConnectionManager.log("receive-packet", "login-queue-done", var1);
      var1.validator.sendChecksum(true, false, false);
   }

   public static void receiveServerLoginQueueRequest(ByteBuffer var0, UdpConnection var1, short var2) {
      LoggerManager.getLogger("user")
         .write(var1.idStr + " \"" + var1.username + "\" attempting to join used " + (var1.preferredInQueue ? "preferred " : "") + "queue");
      synchronized (LoginQueue) {
         if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()
            || !var1.preferredInQueue && currentLoginQueue == null && PreferredLoginQueue.isEmpty() && LoginQueue.isEmpty()
            || var1.preferredInQueue && currentLoginQueue == null && PreferredLoginQueue.isEmpty()) {
            if (Core.bDebug) {
               DebugLog.log("receiveServerLoginQueueRequest: ConnectionImmediate (ip:" + var1.ip + ")");
            }

            currentLoginQueue = var1;
            currentLoginQueue.wasInLoadingQueue = true;
            LoginQueueTimeout.Reset(ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() * 1000);
            ByteBufferWriter var4 = var1.startPacket();
            PacketType.LoginQueueRequest2.doPacket(var4);
            var4.putByte((byte)LoginQueueMessageType.ConnectionImmediate.ordinal());
            PacketType.LoginQueueRequest2.send(var1);
         } else {
            if (Core.bDebug) {
               DebugLog.log("receiveServerLoginQueueRequest: PlaceInQueue (ip:" + var1.ip + " preferredInQueue:" + var1.preferredInQueue + ")");
            }

            if (var1.preferredInQueue) {
               if (!PreferredLoginQueue.contains(var1)) {
                  PreferredLoginQueue.add(var1);
               }
            } else if (!LoginQueue.contains(var1)) {
               LoginQueue.add(var1);
            }

            sendPlaceInTheQueue();
         }
      }

      ConnectionManager.log("receive-packet", "login-queue-request", var1);
   }

   private static void sendAccessDenied(UdpConnection var0, String var1) {
      if (Core.bDebug) {
         DebugLog.log("sendAccessDenied: (ip:" + var0.ip + " message:" + var1 + ")");
      }

      ByteBufferWriter var2 = var0.startPacket();
      PacketType.AccessDenied.doPacket(var2);
      var2.putUTF(var1);
      PacketType.AccessDenied.send(var0);
      ConnectionManager.log("access-denied", "invalid-queue", var0);
      var0.forceDisconnect("queue-" + var1);
   }

   private static void sendPlaceInTheQueue() {
      for (UdpConnection var1 : PreferredLoginQueue) {
         ByteBufferWriter var2 = var1.startPacket();
         PacketType.LoginQueueRequest2.doPacket(var2);
         var2.putByte((byte)LoginQueueMessageType.PlaceInQueue.ordinal());
         var2.putInt(PreferredLoginQueue.indexOf(var1) + 1);
         PacketType.LoginQueueRequest2.send(var1);
      }

      for (UdpConnection var4 : LoginQueue) {
         ByteBufferWriter var5 = var4.startPacket();
         PacketType.LoginQueueRequest2.doPacket(var5);
         var5.putByte((byte)LoginQueueMessageType.PlaceInQueue.ordinal());
         var5.putInt(PreferredLoginQueue.size() + LoginQueue.indexOf(var4) + 1);
         PacketType.LoginQueueRequest2.send(var4);
      }
   }

   private static void sendConnectRequest(UdpConnection var0) {
      if (Core.bDebug) {
         DebugLog.log("sendApplyRequest: (ip:" + var0.ip + ")");
      }

      ByteBufferWriter var1 = var0.startPacket();
      PacketType.LoginQueueRequest2.doPacket(var1);
      var1.putByte((byte)LoginQueueMessageType.ConnectionImmediate.ordinal());
      PacketType.LoginQueueRequest2.send(var0);
      ConnectionManager.log("send-packet", "login-queue-request", var0);
   }

   public static boolean receiveLogin(UdpConnection var0) {
      if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()) {
         return true;
      } else {
         if (Core.bDebug) {
            DebugLog.log("receiveLogin: (ip:" + var0.ip + ")");
         }

         if (var0 != currentLoginQueue) {
            sendAccessDenied(currentLoginQueue, "QueueNotFound");
            if (Core.bDebug) {
               DebugLog.log("receiveLogin: error");
            }

            return false;
         } else {
            if (Core.bDebug) {
               DebugLog.log("receiveLogin: ok");
            }

            return true;
         }
      }
   }

   public static void disconnect(UdpConnection var0) {
      if (Core.bDebug) {
         DebugLog.log("disconnect: (ip:" + var0.ip + ")");
      }

      synchronized (LoginQueue) {
         if (var0 == currentLoginQueue) {
            currentLoginQueue = null;
         } else {
            if (LoginQueue.contains(var0)) {
               LoginQueue.remove(var0);
            }

            if (PreferredLoginQueue.contains(var0)) {
               PreferredLoginQueue.remove(var0);
            }
         }

         sendPlaceInTheQueue();
      }
   }

   public static boolean isInTheQueue(UdpConnection var0) {
      if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()) {
         return false;
      } else {
         synchronized (LoginQueue) {
            return var0 == currentLoginQueue || LoginQueue.contains(var0) || PreferredLoginQueue.contains(var0);
         }
      }
   }

   public static void update() {
      if (ServerOptions.getInstance().LoginQueueEnabled.getValue() && UpdateLimit.Check()) {
         synchronized (LoginQueue) {
            if (currentLoginQueue != null) {
               if (currentLoginQueue.isFullyConnected()) {
                  if (Core.bDebug) {
                     DebugLog.log("update: isFullyConnected (ip:" + currentLoginQueue.ip + ")");
                  }

                  currentLoginQueue = null;
               } else if (LoginQueueTimeout.Check()) {
                  if (Core.bDebug) {
                     DebugLog.log("update: timeout (ip:" + currentLoginQueue.ip + ")");
                  }

                  currentLoginQueue = null;
               }
            }

            loadNextPlayer();
         }
      }
   }

   private static void loadNextPlayer() {
      if (!PreferredLoginQueue.isEmpty() && currentLoginQueue == null) {
         currentLoginQueue = PreferredLoginQueue.remove(0);
         currentLoginQueue.wasInLoadingQueue = true;
         if (Core.bDebug) {
            DebugLog.log("update: Next player from the preferred queue to connect (ip:" + currentLoginQueue.ip + ")");
         }

         LoginQueueTimeout.Reset(ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() * 1000);
         sendConnectRequest(currentLoginQueue);
         sendPlaceInTheQueue();
      }

      if (!LoginQueue.isEmpty() && currentLoginQueue == null) {
         currentLoginQueue = LoginQueue.remove(0);
         currentLoginQueue.wasInLoadingQueue = true;
         if (Core.bDebug) {
            DebugLog.log("update: Next player to connect (ip:" + currentLoginQueue.ip + ")");
         }

         LoginQueueTimeout.Reset(ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() * 1000);
         sendConnectRequest(currentLoginQueue);
         sendPlaceInTheQueue();
      }
   }

   public static String getDescription() {
      return "queue=["
         + LoginQueue.size()
         + "/"
         + PreferredLoginQueue.size()
         + "/\""
         + (currentLoginQueue == null ? "" : currentLoginQueue.getConnectedGUID())
         + "\"]";
   }
}
