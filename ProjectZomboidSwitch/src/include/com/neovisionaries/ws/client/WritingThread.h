#pragma once
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/neovisionaries/ws/client/StateManager/CloseInitiator.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WritingThread : public Thread {
public:
    static const int SHOULD_SEND = 0;
    static const int SHOULD_STOP = 1;
    static const int SHOULD_CONTINUE = 2;
    static const int SHOULD_FLUSH = 3;
    static const int FLUSH_THRESHOLD = 1000;
    const WebSocket mWebSocket;
   private const std::list<WebSocketFrame> mFrames;
    const PerMessageCompressionExtension mPMCE;
    bool mStopRequested;
    WebSocketFrame mCloseFrame;
    bool mFlushNeeded;
    bool mStopped;

    public WritingThread(WebSocket websocket) {
      super("WritingThread");
      this.mWebSocket = websocket;
      this.mFrames = std::make_unique<std::list<>>();
      this.mPMCE = websocket.getPerMessageCompressionExtension();
   }

    void run() {
      try {
         this.main();
      } catch (Throwable var6) {
         WebSocketException cause = std::make_shared<WebSocketException>(
            WebSocketError.UNEXPECTED_ERROR_IN_WRITING_THREAD, "An uncaught throwable was detected in the writing thread: " + var6.getMessage(), var6
         );
    ListenerManager manager = this.mWebSocket.getListenerManager();
         manager.callOnError(cause);
         manager.callOnUnexpectedError(cause);
      }

      /* synchronized - TODO: add std::mutex */ (this) {
         this.mStopped = true;
         this.notifyAll();
      }

      this.notifyFinished();
   }

    void main() {
      this.mWebSocket.onWritingThreadStarted();

      while (true) {
    int result = this.waitForFrames();
         if (result == 1) {
            break;
         }

         if (result == 3) {
            this.flushIgnoreError();
         } else if (result != 2) {
            try {
               this.sendFrames(false);
            } catch (WebSocketException var4) {
               break;
            }
         }
      }

      try {
         this.sendFrames(true);
      } catch (WebSocketException var3) {
      }
   }

    void requestStop() {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mStopRequested = true;
         this.notifyAll();
      }
   }

    bool queueFrame(WebSocketFrame frame) {
      /* synchronized - TODO: add std::mutex */ (this) {
         while (true) {
            if (this.mStopped) {
    return false;
            }

            if (this.mStopRequested || this.mCloseFrame != nullptr || frame.isControlFrame()) {
               break;
            }

    int queueSize = this.mWebSocket.getFrameQueueSize();
            if (queueSize == 0 || this.mFrames.size() < queueSize) {
               break;
            }

            try {
               this.wait();
            } catch (InterruptedException var6) {
            }
         }

         if (isHighPriorityFrame(frame)) {
            this.addHighPriorityFrame(frame);
         } else {
            this.mFrames.addLast(frame);
         }

         this.notifyAll();
    return true;
      }
   }

    static bool isHighPriorityFrame(WebSocketFrame frame) {
      return frame.isPingFrame() || frame.isPongFrame();
   }

    void addHighPriorityFrame(WebSocketFrame frame) {
    int index = 0;

      for (WebSocketFrame f : this.mFrames) {
         if (!isHighPriorityFrame(f)) {
            break;
         }

         index++;
      }

      this.mFrames.push_back(index, frame);
   }

    void queueFlush() {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mFlushNeeded = true;
         this.notifyAll();
      }
   }

    void flushIgnoreError() {
      try {
         this.flush();
      } catch (IOException var2) {
      }
   }

    void flush() {
      this.mWebSocket.getOutput().flush();
   }

    int waitForFrames() {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.mStopRequested) {
    return 1;
         } else if (this.mCloseFrame != nullptr) {
    return 1;
         } else {
            if (this.mFrames.size() == 0) {
               if (this.mFlushNeeded) {
                  this.mFlushNeeded = false;
    return 3;
               }

               try {
                  this.wait();
               } catch (InterruptedException var4) {
               }
            }

            if (this.mStopRequested) {
    return 1;
            } else if (this.mFrames.size() == 0) {
               if (this.mFlushNeeded) {
                  this.mFlushNeeded = false;
    return 3;
               } else {
    return 2;
               }
            } else {
    return 0;
            }
         }
      }
   }

    void sendFrames(bool last) {
    long lastFlushAt = System.currentTimeMillis();

      while (true) {
    WebSocketFrame frame;
         /* synchronized - TODO: add std::mutex */ (this) {
            frame = this.mFrames.poll();
            this.notifyAll();
            if (frame == nullptr) {
               break;
            }
         }

         this.sendFrame(frame);
         if (frame.isPingFrame() || frame.isPongFrame()) {
            this.doFlush();
            lastFlushAt = System.currentTimeMillis();
         } else if (this.isFlushNeeded(last)) {
            lastFlushAt = this.flushIfLongInterval(lastFlushAt);
         }
      }

      if (this.isFlushNeeded(last)) {
         this.doFlush();
      }
   }

    bool isFlushNeeded(bool last) {
      return last || this.mWebSocket.isAutoFlush() || this.mFlushNeeded || this.mCloseFrame != nullptr;
   }

    long flushIfLongInterval(long lastFlushAt) {
    long current = System.currentTimeMillis();
      if (1000L < current - lastFlushAt) {
         this.doFlush();
    return current;
      } else {
    return lastFlushAt;
      }
   }

    void doFlush() {
      try {
         this.flush();
         /* synchronized - TODO: add std::mutex */ (this) {
            this.mFlushNeeded = false;
         }
      } catch (IOException var5) {
    WebSocketException cause = std::make_shared<WebSocketException>(WebSocketError.FLUSH_ERROR, "Flushing frames to the server failed: " + var5.getMessage(), var5);
    ListenerManager manager = this.mWebSocket.getListenerManager();
         manager.callOnError(cause);
         manager.callOnSendError(cause, nullptr);
    throw cause;
      }
   }

    void sendFrame(WebSocketFrame frame) {
      frame = WebSocketFrame.compressFrame(frame, this.mPMCE);
      this.mWebSocket.getListenerManager().callOnSendingFrame(frame);
    bool unsent = false;
      if (this.mCloseFrame != nullptr) {
         unsent = true;
      } else if (frame.isCloseFrame()) {
         this.mCloseFrame = frame;
      }

      if (unsent) {
         this.mWebSocket.getListenerManager().callOnFrameUnsent(frame);
      } else {
         if (frame.isCloseFrame()) {
            this.changeToClosing();
         }

         try {
            this.mWebSocket.getOutput().write(frame);
         } catch (IOException var6) {
            WebSocketException cause = std::make_shared<WebSocketException>(
               WebSocketError.IO_ERROR_IN_WRITING, "An I/O error occurred when a frame was tried to be sent: " + var6.getMessage(), var6
            );
    ListenerManager manager = this.mWebSocket.getListenerManager();
            manager.callOnError(cause);
            manager.callOnSendError(cause, frame);
    throw cause;
         }

         this.mWebSocket.getListenerManager().callOnFrameSent(frame);
      }
   }

    void changeToClosing() {
    StateManager manager = this.mWebSocket.getStateManager();
    bool stateChanged = false;
      /* synchronized - TODO: add std::mutex */ (manager) {
    WebSocketState state = manager.getState();
         if (state != WebSocketState.CLOSING && state != WebSocketState.CLOSED) {
            manager.changeToClosing(CloseInitiator.CLIENT);
            stateChanged = true;
         }
      }

      if (stateChanged) {
         this.mWebSocket.getListenerManager().callOnStateChanged(WebSocketState.CLOSING);
      }
   }

    void notifyFinished() {
      this.mWebSocket.onWritingThreadFinished(this.mCloseFrame);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
