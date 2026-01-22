#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/Socket.h"
#include "javax/net/ssl/SSLSocket.h"
#include "javax/net/ssl/SSLSocketFactory.h"
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class SocketConnector {
public:
    Socket mSocket;
    const Address mAddress;
    const int mConnectionTimeout;
    const ProxyHandshaker mProxyHandshaker;
    const SSLSocketFactory mSSLSocketFactory;
    const std::string mHost;
    const int mPort;

   SocketConnector(Socket socket, Address address, int timeout) {
      this(socket, address, timeout, nullptr, nullptr, nullptr, 0);
   }

   SocketConnector(Socket socket, Address address, int timeout, ProxyHandshaker handshaker, SSLSocketFactory sslSocketFactory, std::string host, int port) {
      this.mSocket = socket;
      this.mAddress = address;
      this.mConnectionTimeout = timeout;
      this.mProxyHandshaker = handshaker;
      this.mSSLSocketFactory = sslSocketFactory;
      this.mHost = host;
      this.mPort = port;
   }

    Socket getSocket() {
      return this.mSocket;
   }

    int getConnectionTimeout() {
      return this.mConnectionTimeout;
   }

    void connect() {
      try {
         this.doConnect();
      } catch (WebSocketException var4) {
         try {
            this.mSocket.close();
         } catch (IOException var3) {
         }

    throw var4;
      }
   }

    void doConnect() {
    bool proxied = this.mProxyHandshaker != nullptr;

      try {
         this.mSocket.connect(this.mAddress.toInetSocketAddress(), this.mConnectionTimeout);
      } catch (IOException var4) {
    std::string message = std::string.format("Failed to connect to %s'%s': %s", proxied ? "the proxy " : "", this.mAddress, var4.getMessage());
         throw WebSocketException(WebSocketError.SOCKET_CONNECT_ERROR, message, var4);
      }

      if (proxied) {
         this.handshake();
      }
   }

    void handshake() {
      try {
         this.mProxyHandshaker.perform();
      } catch (IOException var5) {
    std::string message = std::string.format("Handshake with the proxy server (%s) failed: %s", this.mAddress, var5.getMessage());
         throw WebSocketException(WebSocketError.PROXY_HANDSHAKE_ERROR, message, var5);
      }

      if (this.mSSLSocketFactory != nullptr) {
         try {
            this.mSocket = this.mSSLSocketFactory.createSocket(this.mSocket, this.mHost, this.mPort, true);
         } catch (IOException var4) {
    std::string message = "Failed to overlay an existing socket: " + var4.getMessage();
            throw WebSocketException(WebSocketError.SOCKET_OVERLAY_ERROR, message, var4);
         }

         try {
            ((SSLSocket)this.mSocket).startHandshake();
         } catch (IOException var3) {
    std::string message = std::string.format("SSL handshake with the WebSocket endpoint (%s) failed: %s", this.mAddress, var3.getMessage());
            throw WebSocketException(WebSocketError.SSL_HANDSHAKE_ERROR, message, var3);
         }
      }
   }

    void closeSilently() {
      try {
         this.mSocket.close();
      } catch (Throwable var2) {
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
