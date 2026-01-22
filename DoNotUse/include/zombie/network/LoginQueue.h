#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/LoadingQueueState.h"
#include "zombie/network/LoginQueue/LoginQueueMessageType.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>

namespace zombie {
namespace network {


class LoginQueue {
public:
   private static std::vector<UdpConnection> LoginQueue = std::make_unique<std::vector<>>();
   private static std::vector<UdpConnection> PreferredLoginQueue = std::make_unique<std::vector<>>();
    static UdpConnection currentLoginQueue;
    static UpdateLimit UpdateLimit = std::make_shared<UpdateLimit>(3050L);
    static UpdateLimit LoginQueueTimeout = std::make_shared<UpdateLimit>(15000L);

    static void receiveClientLoginQueueRequest(ByteBuffer var0, short var1) {
    uint8_t var2 = var0.get();
      if (var2 == LoginQueueMessageType.ConnectionImmediate.ordinal()) {
         LoadingQueueState.onConnectionImmediate();
      } else if (var2 == LoginQueueMessageType.PlaceInQueue.ordinal()) {
    int var3 = var0.getInt();
         LoadingQueueState.onPlaceInQueue(var3);
         LuaEventManager.triggerEvent("OnConnectionStateChanged", "FormatMessage", "PlaceInQueue", var3);
      }

      ConnectionManager.log("receive-packet", "login-queue-request", nullptr);
   }

    static void receiveLoginQueueDone(ByteBuffer var0, UdpConnection var1, short var2) {
    long var3 = var0.getLong();
      LoggerManager.getLogger("user").write("player " + var1.username + " loading time was: " + var3 + " ms");
      /* synchronized - TODO: add std::mutex */ (LoginQueue) {
         if (currentLoginQueue == var1) {
            currentLoginQueue = nullptr;
         }

         loadNextPlayer();
      }

      ConnectionManager.log("receive-packet", "login-queue-done", var1);
      var1.validator.sendChecksum(true, false, false);
   }

    static void receiveServerLoginQueueRequest(ByteBuffer var0, UdpConnection var1, short var2) {
      LoggerManager.getLogger("user")
         .write(var1.idStr + " \"" + var1.username + "\" attempting to join used " + (var1.preferredInQueue ? "preferred " : "") + "queue");
      /* synchronized - TODO: add std::mutex */ (LoginQueue) {
         if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()
            || !var1.preferredInQueue && currentLoginQueue == nullptr && PreferredLoginQueue.empty() && LoginQueue.empty()
            || var1.preferredInQueue && currentLoginQueue == nullptr && PreferredLoginQueue.empty()) {
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
                  PreferredLoginQueue.push_back(var1);
               }
            } else if (!LoginQueue.contains(var1)) {
               LoginQueue.push_back(var1);
            }

            sendPlaceInTheQueue();
         }
      }

      ConnectionManager.log("receive-packet", "login-queue-request", var1);
   }

    static void sendAccessDenied(UdpConnection var0, const std::string& var1) {
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

    static void sendPlaceInTheQueue() {
    for (auto& var1 : PreferredLoginQueue)    ByteBufferWriter var2 = var1.startPacket();
         PacketType.LoginQueueRequest2.doPacket(var2);
         var2.putByte((byte)LoginQueueMessageType.PlaceInQueue.ordinal());
         var2.putInt(PreferredLoginQueue.indexOf(var1) + 1);
         PacketType.LoginQueueRequest2.send(var1);
      }

    for (auto& var4 : LoginQueue)    ByteBufferWriter var5 = var4.startPacket();
         PacketType.LoginQueueRequest2.doPacket(var5);
         var5.putByte((byte)LoginQueueMessageType.PlaceInQueue.ordinal());
         var5.putInt(PreferredLoginQueue.size() + LoginQueue.indexOf(var4) + 1);
         PacketType.LoginQueueRequest2.send(var4);
      }
   }

    static void sendConnectRequest(UdpConnection var0) {
      if (Core.bDebug) {
         DebugLog.log("sendApplyRequest: (ip:" + var0.ip + ")");
      }

    ByteBufferWriter var1 = var0.startPacket();
      PacketType.LoginQueueRequest2.doPacket(var1);
      var1.putByte((byte)LoginQueueMessageType.ConnectionImmediate.ordinal());
      PacketType.LoginQueueRequest2.send(var0);
      ConnectionManager.log("send-packet", "login-queue-request", var0);
   }

    static bool receiveLogin(UdpConnection var0) {
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

    static void disconnect(UdpConnection var0) {
      if (Core.bDebug) {
         DebugLog.log("disconnect: (ip:" + var0.ip + ")");
      }

      /* synchronized - TODO: add std::mutex */ (LoginQueue) {
         if (var0 == currentLoginQueue) {
            currentLoginQueue = nullptr;
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

    static bool isInTheQueue(UdpConnection var0) {
      if (!ServerOptions.getInstance().LoginQueueEnabled.getValue()) {
    return false;
      } else {
         /* synchronized - TODO: add std::mutex */ (LoginQueue) {
    return var0 = = currentLoginQueue || LoginQueue.contains(var0) || PreferredLoginQueue.contains(var0);
         }
      }
   }

    static void update() {
      if (ServerOptions.getInstance().LoginQueueEnabled.getValue() && UpdateLimit.Check()) {
         /* synchronized - TODO: add std::mutex */ (LoginQueue) {
            if (currentLoginQueue != nullptr) {
               if (currentLoginQueue.isFullyConnected()) {
                  if (Core.bDebug) {
                     DebugLog.log("update: isFullyConnected (ip:" + currentLoginQueue.ip + ")");
                  }

                  currentLoginQueue = nullptr;
               } else if (LoginQueueTimeout.Check()) {
                  if (Core.bDebug) {
                     DebugLog.log("update: timeout (ip:" + currentLoginQueue.ip + ")");
                  }

                  currentLoginQueue = nullptr;
               }
            }

            loadNextPlayer();
         }
      }
   }

    static void loadNextPlayer() {
      if (!PreferredLoginQueue.empty() && currentLoginQueue == nullptr) {
         currentLoginQueue = PreferredLoginQueue.remove(0);
         currentLoginQueue.wasInLoadingQueue = true;
         if (Core.bDebug) {
            DebugLog.log("update: Next player from the preferred queue to connect (ip:" + currentLoginQueue.ip + ")");
         }

         LoginQueueTimeout.Reset(ServerOptions.getInstance().LoginQueueConnectTimeout.getValue() * 1000);
         sendConnectRequest(currentLoginQueue);
         sendPlaceInTheQueue();
      }

      if (!LoginQueue.empty() && currentLoginQueue == nullptr) {
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

    static std::string getDescription() {
      return "queue=["
         + LoginQueue.size()
         + "/"
         + PreferredLoginQueue.size()
         + "/\""
         + (currentLoginQueue == nullptr ? "" : currentLoginQueue.getConnectedGUID())
         + "\"]";
   }
}
} // namespace network
} // namespace zombie
