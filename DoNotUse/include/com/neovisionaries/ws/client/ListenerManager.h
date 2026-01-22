#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class ListenerManager {
public:
    const WebSocket mWebSocket;
   private const List<WebSocketListener> mListeners = std::make_unique<std::vector<>>();
    bool mSyncNeeded = true;
   private List<WebSocketListener> mCopiedListeners;

    public ListenerManager(WebSocket websocket) {
      this.mWebSocket = websocket;
   }

   public List<WebSocketListener> getListeners() {
      return this.mListeners;
   }

    void addListener(WebSocketListener listener) {
      if (listener != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this.mListeners) {
            this.mListeners.push_back(listener);
            this.mSyncNeeded = true;
         }
      }
   }

    void addListeners(List<WebSocketListener> listeners) {
      if (listeners != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this.mListeners) {
    for (auto& listener : listeners)               if (listener != nullptr) {
                  this.mListeners.push_back(listener);
                  this.mSyncNeeded = true;
               }
            }
         }
      }
   }

    void removeListener(WebSocketListener listener) {
      if (listener != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this.mListeners) {
            if (this.mListeners.remove(listener)) {
               this.mSyncNeeded = true;
            }
         }
      }
   }

    void removeListeners(List<WebSocketListener> listeners) {
      if (listeners != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this.mListeners) {
    for (auto& listener : listeners)               if (listener != nullptr && this.mListeners.remove(listener)) {
                  this.mSyncNeeded = true;
               }
            }
         }
      }
   }

    void clearListeners() {
      /* synchronized - TODO: add std::mutex */ (this.mListeners) {
         if (this.mListeners.size() != 0) {
            this.mListeners.clear();
            this.mSyncNeeded = true;
         }
      }
   }

   private List<WebSocketListener> getSynchronizedListeners() {
      /* synchronized - TODO: add std::mutex */ (this.mListeners) {
         if (!this.mSyncNeeded) {
            return this.mCopiedListeners;
         } else {
            List<WebSocketListener> copiedListeners = new std::vector<>(this.mListeners.size());

            for (WebSocketListener listener : this.mListeners) {
               copiedListeners.push_back(listener);
            }

            this.mCopiedListeners = copiedListeners;
            this.mSyncNeeded = false;
    return copiedListeners;
         }
      }
   }

    void callOnStateChanged(WebSocketState newState) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onStateChanged(this.mWebSocket, newState);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnConnected(List<std::string>> headers) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onConnected(this.mWebSocket, headers);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnConnectError(WebSocketException cause) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onConnectError(this.mWebSocket, cause);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnDisconnected(WebSocketFrame serverCloseFrame, WebSocketFrame clientCloseFrame, bool closedByServer) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onDisconnected(this.mWebSocket, serverCloseFrame, clientCloseFrame, closedByServer);
         } catch (Throwable var7) {
            this.callHandleCallbackError(listener, var7);
         }
      }
   }

    void callOnFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnContinuationFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onContinuationFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnTextFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onTextFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnBinaryFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onBinaryFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnCloseFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onCloseFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnPingFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onPingFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnPongFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onPongFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnTextMessage(const std::string& message) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onTextMessage(this.mWebSocket, message);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnBinaryMessage(byte[] message) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onBinaryMessage(this.mWebSocket, message);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnSendingFrame(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onSendingFrame(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnFrameSent(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onFrameSent(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnFrameUnsent(WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onFrameUnsent(this.mWebSocket, frame);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnError(WebSocketException cause) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onError(this.mWebSocket, cause);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callOnFrameError(WebSocketException cause, WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onFrameError(this.mWebSocket, cause, frame);
         } catch (Throwable var6) {
            this.callHandleCallbackError(listener, var6);
         }
      }
   }

    void callOnMessageError(WebSocketException cause, List<WebSocketFrame> frames) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onMessageError(this.mWebSocket, cause, frames);
         } catch (Throwable var6) {
            this.callHandleCallbackError(listener, var6);
         }
      }
   }

    void callOnMessageDecompressionError(WebSocketException cause, byte[] compressed) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onMessageDecompressionError(this.mWebSocket, cause, compressed);
         } catch (Throwable var6) {
            this.callHandleCallbackError(listener, var6);
         }
      }
   }

    void callOnTextMessageError(WebSocketException cause, byte[] data) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onTextMessageError(this.mWebSocket, cause, data);
         } catch (Throwable var6) {
            this.callHandleCallbackError(listener, var6);
         }
      }
   }

    void callOnSendError(WebSocketException cause, WebSocketFrame frame) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onSendError(this.mWebSocket, cause, frame);
         } catch (Throwable var6) {
            this.callHandleCallbackError(listener, var6);
         }
      }
   }

    void callOnUnexpectedError(WebSocketException cause) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onUnexpectedError(this.mWebSocket, cause);
         } catch (Throwable var5) {
            this.callHandleCallbackError(listener, var5);
         }
      }
   }

    void callHandleCallbackError(WebSocketListener listener, std::exception cause) {
      try {
         listener.handleCallbackError(this.mWebSocket, cause);
      } catch (Throwable var4) {
      }
   }

    void callOnSendingHandshake(const std::string& requestLine, List<std::string[]> headers) {
      for (WebSocketListener listener : this.getSynchronizedListeners()) {
         try {
            listener.onSendingHandshake(this.mWebSocket, requestLine, headers);
         } catch (Throwable var6) {
            this.callHandleCallbackError(listener, var6);
         }
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
