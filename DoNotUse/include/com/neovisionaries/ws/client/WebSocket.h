#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/neovisionaries/ws/client/StateManager/CloseInitiator.h"
#include "com/neovisionaries/ws/client/WebSocket/1.h"
#include "com/neovisionaries/ws/client/WebSocket/2.h"
#include "java/net/Socket.h"
#include "java/net/URI.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WebSocket {
public:
    static const long DEFAULT_CLOSE_DELAY = 10000L;
    const WebSocketFactory mWebSocketFactory;
    const SocketConnector mSocketConnector;
    const StateManager mStateManager;
    HandshakeBuilder mHandshakeBuilder;
    const ListenerManager mListenerManager;
    const PingSender mPingSender;
    const PongSender mPongSender;
    const void* mThreadsLock = std::make_shared<Object>();
    WebSocketInputStream mInput;
    WebSocketOutputStream mOutput;
    ReadingThread mReadingThread;
    WritingThread mWritingThread;
   private Map<std::string, List<std::string>> mServerHeaders;
   private List<WebSocketExtension> mAgreedExtensions;
    std::string mAgreedProtocol;
    bool mExtended;
    bool mAutoFlush = true;
    bool mMissingCloseFrameAllowed = true;
    int mFrameQueueSize;
    int mMaxPayloadSize;
    bool mOnConnectedCalled;
    void* mOnConnectedCalledLock = std::make_shared<Object>();
    bool mReadingThreadStarted;
    bool mWritingThreadStarted;
    bool mReadingThreadFinished;
    bool mWritingThreadFinished;
    WebSocketFrame mServerCloseFrame;
    WebSocketFrame mClientCloseFrame;
    PerMessageCompressionExtension mPerMessageCompressionExtension;

   WebSocket(WebSocketFactory factory, boolean secure, std::string userInfo, std::string host, std::string path, SocketConnector connector) {
      this.mWebSocketFactory = factory;
      this.mSocketConnector = connector;
      this.mStateManager = std::make_unique<StateManager>();
      this.mHandshakeBuilder = std::make_shared<HandshakeBuilder>(secure, userInfo, host, path);
      this.mListenerManager = std::make_shared<ListenerManager>(this);
      this.mPingSender = std::make_shared<PingSender>(this, std::make_unique<CounterPayloadGenerator>());
      this.mPongSender = std::make_shared<PongSender>(this, std::make_unique<CounterPayloadGenerator>());
   }

    WebSocket recreate() {
      return this.recreate(this.mSocketConnector.getConnectionTimeout());
   }

    WebSocket recreate(int timeout) {
      if (timeout < 0) {
         throw IllegalArgumentException("The given timeout value is negative.");
      } else {
    WebSocket instance = this.mWebSocketFactory.createSocket(this.getURI(), timeout);
         instance.mHandshakeBuilder = std::make_shared<HandshakeBuilder>(this.mHandshakeBuilder);
         instance.setPingInterval(this.getPingInterval());
         instance.setPongInterval(this.getPongInterval());
         instance.setPingPayloadGenerator(this.getPingPayloadGenerator());
         instance.setPongPayloadGenerator(this.getPongPayloadGenerator());
         instance.mExtended = this.mExtended;
         instance.mAutoFlush = this.mAutoFlush;
         instance.mMissingCloseFrameAllowed = this.mMissingCloseFrameAllowed;
         instance.mFrameQueueSize = this.mFrameQueueSize;
         List<WebSocketListener> listeners = this.mListenerManager.getListeners();
         /* synchronized - TODO: add std::mutex */ (listeners) {
            instance.addListeners(listeners);
    return instance;
         }
      }
   }

    void finalize() {
      if (this.isInState(WebSocketState.CREATED)) {
         this.finish();
      }

      super.finalize();
   }

    WebSocketState getState() {
      /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
         return this.mStateManager.getState();
      }
   }

    bool isOpen() {
      return this.isInState(WebSocketState.OPEN);
   }

    bool isInState(WebSocketState state) {
      /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
         return this.mStateManager.getState() == state;
      }
   }

    WebSocket addProtocol(const std::string& protocol) {
      this.mHandshakeBuilder.addProtocol(protocol);
    return this;
   }

    WebSocket removeProtocol(const std::string& protocol) {
      this.mHandshakeBuilder.removeProtocol(protocol);
    return this;
   }

    WebSocket clearProtocols() {
      this.mHandshakeBuilder.clearProtocols();
    return this;
   }

    WebSocket addExtension(WebSocketExtension extension) {
      this.mHandshakeBuilder.addExtension(extension);
    return this;
   }

    WebSocket addExtension(const std::string& extension) {
      this.mHandshakeBuilder.addExtension(extension);
    return this;
   }

    WebSocket removeExtension(WebSocketExtension extension) {
      this.mHandshakeBuilder.removeExtension(extension);
    return this;
   }

    WebSocket removeExtensions(const std::string& name) {
      this.mHandshakeBuilder.removeExtensions(name);
    return this;
   }

    WebSocket clearExtensions() {
      this.mHandshakeBuilder.clearExtensions();
    return this;
   }

    WebSocket addHeader(const std::string& name, const std::string& value) {
      this.mHandshakeBuilder.addHeader(name, value);
    return this;
   }

    WebSocket removeHeaders(const std::string& name) {
      this.mHandshakeBuilder.removeHeaders(name);
    return this;
   }

    WebSocket clearHeaders() {
      this.mHandshakeBuilder.clearHeaders();
    return this;
   }

    WebSocket setUserInfo(const std::string& userInfo) {
      this.mHandshakeBuilder.setUserInfo(userInfo);
    return this;
   }

    WebSocket setUserInfo(const std::string& id, const std::string& password) {
      this.mHandshakeBuilder.setUserInfo(id, password);
    return this;
   }

    WebSocket clearUserInfo() {
      this.mHandshakeBuilder.clearUserInfo();
    return this;
   }

    bool isExtended() {
      return this.mExtended;
   }

    WebSocket setExtended(bool extended) {
      this.mExtended = extended;
    return this;
   }

    bool isAutoFlush() {
      return this.mAutoFlush;
   }

    WebSocket setAutoFlush(bool auto) {
      this.mAutoFlush = auto;
    return this;
   }

    bool isMissingCloseFrameAllowed() {
      return this.mMissingCloseFrameAllowed;
   }

    WebSocket setMissingCloseFrameAllowed(bool allowed) {
      this.mMissingCloseFrameAllowed = allowed;
    return this;
   }

    WebSocket flush() {
      /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
    WebSocketState state = this.mStateManager.getState();
         if (state != WebSocketState.OPEN && state != WebSocketState.CLOSING) {
    return this;
         }
      }

    WritingThread wt = this.mWritingThread;
      if (wt != nullptr) {
         wt.queueFlush();
      }

    return this;
   }

    int getFrameQueueSize() {
      return this.mFrameQueueSize;
   }

    WebSocket setFrameQueueSize(int size) {
      if (size < 0) {
         throw IllegalArgumentException("size must not be negative.");
      } else {
         this.mFrameQueueSize = size;
    return this;
      }
   }

    int getMaxPayloadSize() {
      return this.mMaxPayloadSize;
   }

    WebSocket setMaxPayloadSize(int size) {
      if (size < 0) {
         throw IllegalArgumentException("size must not be negative.");
      } else {
         this.mMaxPayloadSize = size;
    return this;
      }
   }

    long getPingInterval() {
      return this.mPingSender.getInterval();
   }

    WebSocket setPingInterval(long interval) {
      this.mPingSender.setInterval(interval);
    return this;
   }

    long getPongInterval() {
      return this.mPongSender.getInterval();
   }

    WebSocket setPongInterval(long interval) {
      this.mPongSender.setInterval(interval);
    return this;
   }

    PayloadGenerator getPingPayloadGenerator() {
      return this.mPingSender.getPayloadGenerator();
   }

    WebSocket setPingPayloadGenerator(PayloadGenerator generator) {
      this.mPingSender.setPayloadGenerator(generator);
    return this;
   }

    PayloadGenerator getPongPayloadGenerator() {
      return this.mPongSender.getPayloadGenerator();
   }

    WebSocket setPongPayloadGenerator(PayloadGenerator generator) {
      this.mPongSender.setPayloadGenerator(generator);
    return this;
   }

    WebSocket addListener(WebSocketListener listener) {
      this.mListenerManager.addListener(listener);
    return this;
   }

    WebSocket addListeners(List<WebSocketListener> listeners) {
      this.mListenerManager.addListeners(listeners);
    return this;
   }

    WebSocket removeListener(WebSocketListener listener) {
      this.mListenerManager.removeListener(listener);
    return this;
   }

    WebSocket removeListeners(List<WebSocketListener> listeners) {
      this.mListenerManager.removeListeners(listeners);
    return this;
   }

    WebSocket clearListeners() {
      this.mListenerManager.clearListeners();
    return this;
   }

    Socket getSocket() {
      return this.mSocketConnector.getSocket();
   }

    URI getURI() {
      return this.mHandshakeBuilder.getURI();
   }

    WebSocket connect() {
      this.changeStateOnConnect();

      Map<std::string, List<std::string>> headers;
      try {
         this.mSocketConnector.connect();
         headers = this.shakeHands();
      } catch (WebSocketException var3) {
         this.mSocketConnector.closeSilently();
         this.mStateManager.setState(WebSocketState.CLOSED);
         this.mListenerManager.callOnStateChanged(WebSocketState.CLOSED);
    throw var3;
      }

      this.mServerHeaders = headers;
      this.mPerMessageCompressionExtension = this.findAgreedPerMessageCompressionExtension();
      this.mStateManager.setState(WebSocketState.OPEN);
      this.mListenerManager.callOnStateChanged(WebSocketState.OPEN);
      this.startThreads();
    return this;
   }

   public Future<WebSocket> connect(ExecutorService executorService) {
      return executorService.submit(this.connectable());
   }

   public Callable<WebSocket> connectable() {
      return std::make_shared<Connectable>(this);
   }

    WebSocket connectAsynchronously() {
    std::make_shared<ConnectThread>();
    return this;
   }

    WebSocket disconnect() {
      return this.disconnect(1000, nullptr);
   }

    WebSocket disconnect(int closeCode) {
      return this.disconnect(closeCode, nullptr);
   }

    WebSocket disconnect(const std::string& reason) {
      return this.disconnect(1000, reason);
   }

    WebSocket disconnect(int closeCode, const std::string& reason) {
      return this.disconnect(closeCode, reason, 10000L);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    WebSocket disconnect(int closeCode, const std::string& reason, long closeDelay) {
      /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
         switch (2.$SwitchMap$com$neovisionaries$ws$client$WebSocketState[this.mStateManager.getState().ordinal()]) {
            case 1:
               this.finishAsynchronously();
    return this;
            case 2:
               this.mStateManager.changeToClosing(CloseInitiator.CLIENT);
    WebSocketFrame frame = WebSocketFrame.createCloseFrame(closeCode, reason);
               this.sendFrame(frame);
               break;
            default:
    return this;
         }
      }

      this.mListenerManager.callOnStateChanged(WebSocketState.CLOSING);
      if (closeDelay < 0L) {
         closeDelay = 10000L;
      }

      this.stopThreads(closeDelay);
    return this;
   }

   public List<WebSocketExtension> getAgreedExtensions() {
      return this.mAgreedExtensions;
   }

    std::string getAgreedProtocol() {
      return this.mAgreedProtocol;
   }

    WebSocket sendFrame(WebSocketFrame frame) {
      if (frame == nullptr) {
    return this;
      } else {
         /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
    WebSocketState state = this.mStateManager.getState();
            if (state != WebSocketState.OPEN && state != WebSocketState.CLOSING) {
    return this;
            }
         }

    WritingThread wt = this.mWritingThread;
         if (wt == nullptr) {
    return this;
         } else {
            List<WebSocketFrame> frames = this.splitIfNecessary(frame);
            if (frames == nullptr) {
               wt.queueFrame(frame);
            } else {
    for (auto& f : frames)                  wt.queueFrame(f);
               }
            }

    return this;
         }
      }
   }

   private List<WebSocketFrame> splitIfNecessary(WebSocketFrame frame) {
      return WebSocketFrame.splitIfNecessary(frame, this.mMaxPayloadSize, this.mPerMessageCompressionExtension);
   }

    WebSocket sendContinuation() {
      return this.sendFrame(WebSocketFrame.createContinuationFrame());
   }

    WebSocket sendContinuation(bool fin) {
      return this.sendFrame(WebSocketFrame.createContinuationFrame().setFin(fin));
   }

    WebSocket sendContinuation(const std::string& payload) {
      return this.sendFrame(WebSocketFrame.createContinuationFrame(payload));
   }

    WebSocket sendContinuation(const std::string& payload, bool fin) {
      return this.sendFrame(WebSocketFrame.createContinuationFrame(payload).setFin(fin));
   }

    WebSocket sendContinuation(byte[] payload) {
      return this.sendFrame(WebSocketFrame.createContinuationFrame(payload));
   }

    WebSocket sendContinuation(byte[] payload, bool fin) {
      return this.sendFrame(WebSocketFrame.createContinuationFrame(payload).setFin(fin));
   }

    WebSocket sendText(const std::string& message) {
      return this.sendFrame(WebSocketFrame.createTextFrame(message));
   }

    WebSocket sendText(const std::string& payload, bool fin) {
      return this.sendFrame(WebSocketFrame.createTextFrame(payload).setFin(fin));
   }

    WebSocket sendBinary(byte[] message) {
      return this.sendFrame(WebSocketFrame.createBinaryFrame(message));
   }

    WebSocket sendBinary(byte[] payload, bool fin) {
      return this.sendFrame(WebSocketFrame.createBinaryFrame(payload).setFin(fin));
   }

    WebSocket sendClose() {
      return this.sendFrame(WebSocketFrame.createCloseFrame());
   }

    WebSocket sendClose(int closeCode) {
      return this.sendFrame(WebSocketFrame.createCloseFrame(closeCode));
   }

    WebSocket sendClose(int closeCode, const std::string& reason) {
      return this.sendFrame(WebSocketFrame.createCloseFrame(closeCode, reason));
   }

    WebSocket sendPing() {
      return this.sendFrame(WebSocketFrame.createPingFrame());
   }

    WebSocket sendPing(byte[] payload) {
      return this.sendFrame(WebSocketFrame.createPingFrame(payload));
   }

    WebSocket sendPing(const std::string& payload) {
      return this.sendFrame(WebSocketFrame.createPingFrame(payload));
   }

    WebSocket sendPong() {
      return this.sendFrame(WebSocketFrame.createPongFrame());
   }

    WebSocket sendPong(byte[] payload) {
      return this.sendFrame(WebSocketFrame.createPongFrame(payload));
   }

    WebSocket sendPong(const std::string& payload) {
      return this.sendFrame(WebSocketFrame.createPongFrame(payload));
   }

    void changeStateOnConnect() {
      /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
         if (this.mStateManager.getState() != WebSocketState.CREATED) {
            throw WebSocketException(WebSocketError.NOT_IN_CREATED_STATE, "The current state of the WebSocket is not CREATED.");
         }

         this.mStateManager.setState(WebSocketState.CONNECTING);
      }

      this.mListenerManager.callOnStateChanged(WebSocketState.CONNECTING);
   }

   private Map<std::string, List<std::string>> shakeHands() throws WebSocketException {
    Socket socket = this.mSocketConnector.getSocket();
    WebSocketInputStream input = this.openInputStream(socket);
    WebSocketOutputStream output = this.openOutputStream(socket);
    std::string key = generateWebSocketKey();
      this.writeHandshake(output, key);
      Map<std::string, List<std::string>> headers = this.readHandshake(input, key);
      this.mInput = input;
      this.mOutput = output;
    return headers;
   }

    WebSocketInputStream openInputStream(Socket socket) {
      try {
         return std::make_shared<WebSocketInputStream>(std::make_shared<BufferedInputStream>(socket.getInputStream()));
      } catch (IOException var3) {
         throw WebSocketException(
            WebSocketError.SOCKET_INPUT_STREAM_FAILURE, "Failed to get the input stream of the raw socket: " + var3.getMessage(), var3
         );
      }
   }

    WebSocketOutputStream openOutputStream(Socket socket) {
      try {
         return std::make_shared<WebSocketOutputStream>(std::make_shared<BufferedOutputStream>(socket.getOutputStream()));
      } catch (IOException var3) {
         throw WebSocketException(
            WebSocketError.SOCKET_OUTPUT_STREAM_FAILURE, "Failed to get the output stream from the raw socket: " + var3.getMessage(), var3
         );
      }
   }

    static std::string generateWebSocketKey() {
      byte[] data = new byte[16];
      Misc.nextBytes(data);
      return Base64.encode(data);
   }

    void writeHandshake(WebSocketOutputStream output, const std::string& key) {
      this.mHandshakeBuilder.setKey(key);
    std::string requestLine = this.mHandshakeBuilder.buildRequestLine();
      List<std::string[]> headers = this.mHandshakeBuilder.buildHeaders();
    std::string handshake = HandshakeBuilder.build(requestLine, headers);
      this.mListenerManager.callOnSendingHandshake(requestLine, headers);

      try {
         output.write(handshake);
         output.flush();
      } catch (IOException var7) {
         throw WebSocketException(
            WebSocketError.OPENING_HAHDSHAKE_REQUEST_FAILURE, "Failed to send an opening handshake request to the server: " + var7.getMessage(), var7
         );
      }
   }

   private Map<std::string, List<std::string>> readHandshake(WebSocketInputStream input, std::string key) throws WebSocketException {
      return std::make_shared<HandshakeReader>(this).readHandshake(input, key);
   }

    void startThreads() {
    ReadingThread readingThread = std::make_shared<ReadingThread>(this);
    WritingThread writingThread = std::make_shared<WritingThread>(this);
      /* synchronized - TODO: add std::mutex */ (this.mThreadsLock) {
         this.mReadingThread = readingThread;
         this.mWritingThread = writingThread;
      }

      readingThread.start();
      writingThread.start();
   }

    void stopThreads(long closeDelay) {
    ReadingThread readingThread;
    WritingThread writingThread;
      /* synchronized - TODO: add std::mutex */ (this.mThreadsLock) {
         readingThread = this.mReadingThread;
         writingThread = this.mWritingThread;
         this.mReadingThread = nullptr;
         this.mWritingThread = nullptr;
      }

      if (readingThread != nullptr) {
         readingThread.requestStop(closeDelay);
      }

      if (writingThread != nullptr) {
         writingThread.requestStop();
      }
   }

    WebSocketInputStream getInput() {
      return this.mInput;
   }

    WebSocketOutputStream getOutput() {
      return this.mOutput;
   }

    StateManager getStateManager() {
      return this.mStateManager;
   }

    ListenerManager getListenerManager() {
      return this.mListenerManager;
   }

    HandshakeBuilder getHandshakeBuilder() {
      return this.mHandshakeBuilder;
   }

    void setAgreedExtensions(List<WebSocketExtension> extensions) {
      this.mAgreedExtensions = extensions;
   }

    void setAgreedProtocol(const std::string& protocol) {
      this.mAgreedProtocol = protocol;
   }

    void onReadingThreadStarted() {
    bool bothStarted = false;
      /* synchronized - TODO: add std::mutex */ (this.mThreadsLock) {
         this.mReadingThreadStarted = true;
         if (this.mWritingThreadStarted) {
            bothStarted = true;
         }
      }

      this.callOnConnectedIfNotYet();
      if (bothStarted) {
         this.onThreadsStarted();
      }
   }

    void onWritingThreadStarted() {
    bool bothStarted = false;
      /* synchronized - TODO: add std::mutex */ (this.mThreadsLock) {
         this.mWritingThreadStarted = true;
         if (this.mReadingThreadStarted) {
            bothStarted = true;
         }
      }

      this.callOnConnectedIfNotYet();
      if (bothStarted) {
         this.onThreadsStarted();
      }
   }

    void callOnConnectedIfNotYet() {
      /* synchronized - TODO: add std::mutex */ (this.mOnConnectedCalledLock) {
         if (this.mOnConnectedCalled) {
            return;
         }

         this.mOnConnectedCalled = true;
      }

      this.mListenerManager.callOnConnected(this.mServerHeaders);
   }

    void onThreadsStarted() {
      this.mPingSender.start();
      this.mPongSender.start();
   }

    void onReadingThreadFinished(WebSocketFrame closeFrame) {
      /* synchronized - TODO: add std::mutex */ (this.mThreadsLock) {
         this.mReadingThreadFinished = true;
         this.mServerCloseFrame = closeFrame;
         if (!this.mWritingThreadFinished) {
            return;
         }
      }

      this.onThreadsFinished();
   }

    void onWritingThreadFinished(WebSocketFrame closeFrame) {
      /* synchronized - TODO: add std::mutex */ (this.mThreadsLock) {
         this.mWritingThreadFinished = true;
         this.mClientCloseFrame = closeFrame;
         if (!this.mReadingThreadFinished) {
            return;
         }
      }

      this.onThreadsFinished();
   }

    void onThreadsFinished() {
      this.finish();
   }

    void finish() {
      this.mPingSender.stop();
      this.mPongSender.stop();

      try {
         this.mSocketConnector.getSocket().close();
      } catch (Throwable var4) {
      }

      /* synchronized - TODO: add std::mutex */ (this.mStateManager) {
         this.mStateManager.setState(WebSocketState.CLOSED);
      }

      this.mListenerManager.callOnStateChanged(WebSocketState.CLOSED);
      this.mListenerManager.callOnDisconnected(this.mServerCloseFrame, this.mClientCloseFrame, this.mStateManager.getClosedByServer());
   }

    void finishAsynchronously() {
    std::make_shared<1>();
   }

    PerMessageCompressionExtension findAgreedPerMessageCompressionExtension() {
      if (this.mAgreedExtensions == nullptr) {
    return nullptr;
      } else {
         for (WebSocketExtension extension : this.mAgreedExtensions) {
            if (dynamic_cast<PerMessageCompressionExtension*>(extension) != nullptr) {
               return (PerMessageCompressionExtension)extension;
            }
         }

    return nullptr;
      }
   }

    PerMessageCompressionExtension getPerMessageCompressionExtension() {
      return this.mPerMessageCompressionExtension;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
