#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/neovisionaries/ws/client/ReadingThread/1.h"
#include "com/neovisionaries/ws/client/ReadingThread/CloseTask.h"
#include "com/neovisionaries/ws/client/StateManager/CloseInitiator.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class ReadingThread : public Thread {
public:
    const WebSocket mWebSocket;
    bool mStopRequested;
    WebSocketFrame mCloseFrame;
   private List<WebSocketFrame> mContinuation = std::make_unique<std::vector<>>();
    const PerMessageCompressionExtension mPMCE;
    void* mCloseLock = std::make_shared<Object>();
    Timer mCloseTimer;
    CloseTask mCloseTask;
    long mCloseDelay;
    bool mNotWaitForCloseFrame;

    public ReadingThread(WebSocket websocket) {
      super("ReadingThread");
      this.mWebSocket = websocket;
      this.mPMCE = websocket.getPerMessageCompressionExtension();
   }

    void run() {
      try {
         this.main();
      } catch (Throwable var4) {
         WebSocketException cause = std::make_shared<WebSocketException>(
            WebSocketError.UNEXPECTED_ERROR_IN_READING_THREAD, "An uncaught throwable was detected in the reading thread: " + var4.getMessage(), var4
         );
    ListenerManager manager = this.mWebSocket.getListenerManager();
         manager.callOnError(cause);
         manager.callOnUnexpectedError(cause);
      }

      this.notifyFinished();
   }

    void main() {
      this.mWebSocket.onReadingThreadStarted();

    bool keepReading;
      do {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mStopRequested) {
               break;
            }
         }

    WebSocketFrame frame = this.readFrame();
         if (frame == nullptr) {
            break;
         }

         keepReading = this.handleFrame(frame);
      } while (keepReading);

      this.waitForCloseFrame();
      this.cancelClose();
   }

    void requestStop(long closeDelay) {
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.mStopRequested) {
            return;
         }

         this.mStopRequested = true;
      }

      this.interrupt();
      this.mCloseDelay = closeDelay;
      this.scheduleClose();
   }

    void callOnFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnFrame(frame);
   }

    void callOnContinuationFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnContinuationFrame(frame);
   }

    void callOnTextFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnTextFrame(frame);
   }

    void callOnBinaryFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnBinaryFrame(frame);
   }

    void callOnCloseFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnCloseFrame(frame);
   }

    void callOnPingFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnPingFrame(frame);
   }

    void callOnPongFrame(WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnPongFrame(frame);
   }

    void callOnTextMessage(byte[] data) {
      try {
    std::string message = Misc.toStringUTF8(data);
         this.callOnTextMessage(message);
      } catch (Throwable var4) {
         WebSocketException wse = std::make_shared<WebSocketException>(
            WebSocketError.TEXT_MESSAGE_CONSTRUCTION_ERROR, "Failed to convert payload data into a string: " + var4.getMessage(), var4
         );
         this.callOnError(wse);
         this.callOnTextMessageError(wse, data);
      }
   }

    void callOnTextMessage(const std::string& message) {
      this.mWebSocket.getListenerManager().callOnTextMessage(message);
   }

    void callOnBinaryMessage(byte[] message) {
      this.mWebSocket.getListenerManager().callOnBinaryMessage(message);
   }

    void callOnError(WebSocketException cause) {
      this.mWebSocket.getListenerManager().callOnError(cause);
   }

    void callOnFrameError(WebSocketException cause, WebSocketFrame frame) {
      this.mWebSocket.getListenerManager().callOnFrameError(cause, frame);
   }

    void callOnMessageError(WebSocketException cause, List<WebSocketFrame> frames) {
      this.mWebSocket.getListenerManager().callOnMessageError(cause, frames);
   }

    void callOnMessageDecompressionError(WebSocketException cause, byte[] compressed) {
      this.mWebSocket.getListenerManager().callOnMessageDecompressionError(cause, compressed);
   }

    void callOnTextMessageError(WebSocketException cause, byte[] data) {
      this.mWebSocket.getListenerManager().callOnTextMessageError(cause, data);
   }

    WebSocketFrame readFrame() {
    WebSocketFrame frame = nullptr;
    WebSocketException wse = nullptr;

      try {
         frame = this.mWebSocket.getInput().readFrame();
         this.verifyFrame(frame);
    return frame;
      } catch (InterruptedIOException var5) {
         if (this.mStopRequested) {
    return nullptr;
         }

         wse = std::make_shared<WebSocketException>(
            WebSocketError.INTERRUPTED_IN_READING, "Interruption occurred while a frame was being read from the web socket: " + var5.getMessage(), var5
         );
      } catch (IOException var6) {
         if (this.mStopRequested && this.isInterrupted()) {
    return nullptr;
         }

         wse = std::make_shared<WebSocketException>(
            WebSocketError.IO_ERROR_IN_READING, "An I/O error occurred while a frame was being read from the web socket: " + var6.getMessage(), var6
         );
      } catch (WebSocketException var7) {
         wse = var7;
      }

    bool error = true;
      if (dynamic_cast<NoMoreFrameException*>(wse) != nullptr) {
         this.mNotWaitForCloseFrame = true;
         if (this.mWebSocket.isMissingCloseFrameAllowed()) {
            error = false;
         }
      }

      if (error) {
         this.callOnError(wse);
         this.callOnFrameError(wse, frame);
      }

    WebSocketFrame closeFrame = this.createCloseFrame(wse);
      this.mWebSocket.sendFrame(closeFrame);
    return nullptr;
   }

    void verifyFrame(WebSocketFrame frame) {
      this.verifyReservedBits(frame);
      this.verifyFrameOpcode(frame);
      this.verifyFrameMask(frame);
      this.verifyFrameFragmentation(frame);
      this.verifyFrameSize(frame);
   }

    void verifyReservedBits(WebSocketFrame frame) {
      if (!this.mWebSocket.isExtended()) {
         this.verifyReservedBit1(frame);
         this.verifyReservedBit2(frame);
         this.verifyReservedBit3(frame);
      }
   }

    void verifyReservedBit1(WebSocketFrame frame) {
      if (this.mPMCE != nullptr) {
    bool verified = this.verifyReservedBit1ForPMCE(frame);
         if (verified) {
            return;
         }
      }

      if (frame.getRsv1()) {
         throw WebSocketException(WebSocketError.UNEXPECTED_RESERVED_BIT, "The RSV1 bit of a frame is set unexpectedly.");
      }
   }

    bool verifyReservedBit1ForPMCE(WebSocketFrame frame) {
      return frame.isTextFrame() || frame.isBinaryFrame();
   }

    void verifyReservedBit2(WebSocketFrame frame) {
      if (frame.getRsv2()) {
         throw WebSocketException(WebSocketError.UNEXPECTED_RESERVED_BIT, "The RSV2 bit of a frame is set unexpectedly.");
      }
   }

    void verifyReservedBit3(WebSocketFrame frame) {
      if (frame.getRsv3()) {
         throw WebSocketException(WebSocketError.UNEXPECTED_RESERVED_BIT, "The RSV3 bit of a frame is set unexpectedly.");
      }
   }

    void verifyFrameOpcode(WebSocketFrame frame) {
      switch (frame.getOpcode()) {
         case 0:
         case 1:
         case 2:
         case 8:
         case 9:
         case 10:
            return;
         case 3:
         case 4:
         case 5:
         case 6:
         case 7:
         default:
            if (!this.mWebSocket.isExtended()) {
               throw WebSocketException(WebSocketError.UNKNOWN_OPCODE, "A frame has an unknown opcode: 0x" + int.toHexString(frame.getOpcode()));
            }
      }
   }

    void verifyFrameMask(WebSocketFrame frame) {
      if (frame.getMask()) {
         throw WebSocketException(WebSocketError.FRAME_MASKED, "A frame from the server is masked.");
      }
   }

    void verifyFrameFragmentation(WebSocketFrame frame) {
      if (frame.isControlFrame()) {
         if (!frame.getFin()) {
            throw WebSocketException(WebSocketError.FRAGMENTED_CONTROL_FRAME, "A control frame is fragmented.");
         }
      } else {
    bool continuationExists = this.mContinuation.size() != 0;
         if (frame.isContinuationFrame()) {
            if (!continuationExists) {
               throw WebSocketException(
                  WebSocketError.UNEXPECTED_CONTINUATION_FRAME, "A continuation frame was detected although a continuation had not started."
               );
            }
         } else if (continuationExists) {
            throw WebSocketException(
               WebSocketError.CONTINUATION_NOT_CLOSED, "A non-control frame was detected although the existing continuation had not been closed."
            );
         }
      }
   }

    void verifyFrameSize(WebSocketFrame frame) {
      if (frame.isControlFrame()) {
         byte[] payload = frame.getPayload();
         if (payload != nullptr) {
            if (125 < payload.length) {
               throw WebSocketException(
                  WebSocketError.TOO_LONG_CONTROL_FRAME_PAYLOAD, "The payload size of a control frame exceeds the maximum size (125 bytes): " + payload.length
               );
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    WebSocketFrame createCloseFrame(WebSocketException wse) {
    int closeCode;
      switch (1.$SwitchMap$com$neovisionaries$ws$client$WebSocketError[wse.getError().ordinal()]) {
         case 1:
         case 2:
         case 3:
            closeCode = 1002;
            break;
         case 4:
         case 5:
            closeCode = 1009;
            break;
         case 6:
         case 7:
         case 8:
         case 9:
         case 10:
         case 11:
         case 12:
         case 13:
            closeCode = 1002;
            break;
         case 14:
         case 15:
            closeCode = 1008;
            break;
         default:
            closeCode = 1008;
      }

      return WebSocketFrame.createCloseFrame(closeCode, wse.getMessage());
   }

    bool handleFrame(WebSocketFrame frame) {
      this.callOnFrame(frame);
      switch (frame.getOpcode()) {
         case 0:
            return this.handleContinuationFrame(frame);
         case 1:
            return this.handleTextFrame(frame);
         case 2:
            return this.handleBinaryFrame(frame);
         case 3:
         case 4:
         case 5:
         case 6:
         case 7:
         default:
    return true;
         case 8:
            return this.handleCloseFrame(frame);
         case 9:
            return this.handlePingFrame(frame);
         case 10:
            return this.handlePongFrame(frame);
      }
   }

    bool handleContinuationFrame(WebSocketFrame frame) {
      this.callOnContinuationFrame(frame);
      this.mContinuation.push_back(frame);
      if (!frame.getFin()) {
    return true;
      } else {
         byte[] data = this.getMessage(this.mContinuation);
         if (data == nullptr) {
    return false;
         } else {
            if (this.mContinuation.get(0).isTextFrame()) {
               this.callOnTextMessage(data);
            } else {
               this.callOnBinaryMessage(data);
            }

            this.mContinuation.clear();
    return true;
         }
      }
   }

   private byte[] getMessage(List<WebSocketFrame> frames) {
      byte[] data = this.concatenatePayloads(this.mContinuation);
      if (data == nullptr) {
    return nullptr;
      } else {
         if (this.mPMCE != nullptr && frames.get(0).getRsv1()) {
            data = this.decompress(data);
         }

    return data;
      }
   }

   private byte[] concatenatePayloads(List<WebSocketFrame> frames) {
    std::exception cause;
      try {
    ByteArrayOutputStream baos = std::make_shared<ByteArrayOutputStream>();

    for (auto& frame : frames)            byte[] payload = frame.getPayload();
            if (payload != nullptr && payload.length != 0) {
               baos.write(payload);
            }
         }

         return baos.toByteArray();
      } catch (IOException var7) {
         cause = var7;
      } catch (OutOfMemoryError var8) {
         cause = var8;
      }

      WebSocketException wse = std::make_shared<WebSocketException>(
         WebSocketError.MESSAGE_CONSTRUCTION_ERROR, "Failed to concatenate payloads of multiple frames to construct a message: " + cause.getMessage(), cause
      );
      this.callOnError(wse);
      this.callOnMessageError(wse, frames);
    WebSocketFrame framex = WebSocketFrame.createCloseFrame(1009, wse.getMessage());
      this.mWebSocket.sendFrame(framex);
    return nullptr;
   }

   private byte[] getMessage(WebSocketFrame frame) {
      byte[] payload = frame.getPayload();
      if (this.mPMCE != nullptr && frame.getRsv1()) {
         payload = this.decompress(payload);
      }

    return payload;
   }

   private byte[] decompress(byte[] input) {
      try {
         return this.mPMCE.decompress(input);
      } catch (WebSocketException var4) {
         this.callOnError(var4);
         this.callOnMessageDecompressionError(var4, input);
    WebSocketFrame frame = WebSocketFrame.createCloseFrame(1003, var4.getMessage());
         this.mWebSocket.sendFrame(frame);
    return nullptr;
      }
   }

    bool handleTextFrame(WebSocketFrame frame) {
      this.callOnTextFrame(frame);
      if (!frame.getFin()) {
         this.mContinuation.push_back(frame);
    return true;
      } else {
         byte[] payload = this.getMessage(frame);
         this.callOnTextMessage(payload);
    return true;
      }
   }

    bool handleBinaryFrame(WebSocketFrame frame) {
      this.callOnBinaryFrame(frame);
      if (!frame.getFin()) {
         this.mContinuation.push_back(frame);
    return true;
      } else {
         byte[] payload = this.getMessage(frame);
         this.callOnBinaryMessage(payload);
    return true;
      }
   }

    bool handleCloseFrame(WebSocketFrame frame) {
    StateManager manager = this.mWebSocket.getStateManager();
      this.mCloseFrame = frame;
    bool stateChanged = false;
      /* synchronized - TODO: add std::mutex */ (manager) {
    WebSocketState state = manager.getState();
         if (state != WebSocketState.CLOSING && state != WebSocketState.CLOSED) {
            manager.changeToClosing(CloseInitiator.SERVER);
            this.mWebSocket.sendFrame(frame);
            stateChanged = true;
         }
      }

      if (stateChanged) {
         this.mWebSocket.getListenerManager().callOnStateChanged(WebSocketState.CLOSING);
      }

      this.callOnCloseFrame(frame);
    return false;
   }

    bool handlePingFrame(WebSocketFrame frame) {
      this.callOnPingFrame(frame);
    WebSocketFrame pong = WebSocketFrame.createPongFrame(frame.getPayload());
      this.mWebSocket.sendFrame(pong);
    return true;
   }

    bool handlePongFrame(WebSocketFrame frame) {
      this.callOnPongFrame(frame);
    return true;
   }

    void waitForCloseFrame() {
      if (!this.mNotWaitForCloseFrame) {
         if (this.mCloseFrame == nullptr) {
    WebSocketFrame frame = nullptr;
            this.scheduleClose();

            do {
               try {
                  frame = this.mWebSocket.getInput().readFrame();
               } catch (Throwable var3) {
                  break;
               }

               if (frame.isCloseFrame()) {
                  this.mCloseFrame = frame;
                  break;
               }
            } while (!this.isInterrupted());
         }
      }
   }

    void notifyFinished() {
      this.mWebSocket.onReadingThreadFinished(this.mCloseFrame);
   }

    void scheduleClose() {
      /* synchronized - TODO: add std::mutex */ (this.mCloseLock) {
         this.cancelCloseTask();
         this.scheduleCloseTask();
      }
   }

    void scheduleCloseTask() {
      this.mCloseTask = std::make_shared<CloseTask>(this, nullptr);
      this.mCloseTimer = std::make_shared<Timer>("ReadingThreadCloseTimer");
      this.mCloseTimer.schedule(this.mCloseTask, this.mCloseDelay);
   }

    void cancelClose() {
      /* synchronized - TODO: add std::mutex */ (this.mCloseLock) {
         this.cancelCloseTask();
      }
   }

    void cancelCloseTask() {
      if (this.mCloseTimer != nullptr) {
         this.mCloseTimer.cancel();
         this.mCloseTimer = nullptr;
      }

      if (this.mCloseTask != nullptr) {
         this.mCloseTask.cancel();
         this.mCloseTask = nullptr;
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
