#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/Socket.h"
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "java/net/URL.h"
#include "javax/net/SocketFactory.h"
#include "javax/net/ssl/SSLContext.h"
#include "javax/net/ssl/SSLSocketFactory.h"
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class WebSocketFactory {
public:
    const SocketFactorySettings mSocketFactorySettings = std::make_shared<SocketFactorySettings>();
    const ProxySettings mProxySettings = std::make_shared<ProxySettings>(this);
    int mConnectionTimeout;

    SocketFactory getSocketFactory() {
      return this.mSocketFactorySettings.getSocketFactory();
   }

    WebSocketFactory setSocketFactory(SocketFactory factory) {
      this.mSocketFactorySettings.setSocketFactory(factory);
    return this;
   }

    SSLSocketFactory getSSLSocketFactory() {
      return this.mSocketFactorySettings.getSSLSocketFactory();
   }

    WebSocketFactory setSSLSocketFactory(SSLSocketFactory factory) {
      this.mSocketFactorySettings.setSSLSocketFactory(factory);
    return this;
   }

    SSLContext getSSLContext() {
      return this.mSocketFactorySettings.getSSLContext();
   }

    WebSocketFactory setSSLContext(SSLContext context) {
      this.mSocketFactorySettings.setSSLContext(context);
    return this;
   }

    ProxySettings getProxySettings() {
      return this.mProxySettings;
   }

    int getConnectionTimeout() {
      return this.mConnectionTimeout;
   }

    WebSocketFactory setConnectionTimeout(int timeout) {
      if (timeout < 0) {
         throw IllegalArgumentException("timeout value cannot be negative.");
      } else {
         this.mConnectionTimeout = timeout;
    return this;
      }
   }

    WebSocket createSocket(const std::string& uri) {
      return this.createSocket(uri, this.getConnectionTimeout());
   }

    WebSocket createSocket(const std::string& uri, int timeout) {
      if (uri == nullptr) {
         throw IllegalArgumentException("The given URI is nullptr.");
      } else if (timeout < 0) {
         throw IllegalArgumentException("The given timeout value is negative.");
      } else {
         return this.createSocket(URI.create(uri), timeout);
      }
   }

    WebSocket createSocket(URL url) {
      return this.createSocket(url, this.getConnectionTimeout());
   }

    WebSocket createSocket(URL url, int timeout) {
      if (url == nullptr) {
         throw IllegalArgumentException("The given URL is nullptr.");
      } else if (timeout < 0) {
         throw IllegalArgumentException("The given timeout value is negative.");
      } else {
         try {
            return this.createSocket(url.toURI(), timeout);
         } catch (URISyntaxException var4) {
            throw IllegalArgumentException("Failed to convert the given URL into a URI.");
         }
      }
   }

    WebSocket createSocket(URI uri) {
      return this.createSocket(uri, this.getConnectionTimeout());
   }

    WebSocket createSocket(URI uri, int timeout) {
      if (uri == nullptr) {
         throw IllegalArgumentException("The given URI is nullptr.");
      } else if (timeout < 0) {
         throw IllegalArgumentException("The given timeout value is negative.");
      } else {
    std::string scheme = uri.getScheme();
    std::string userInfo = uri.getUserInfo();
    std::string host = Misc.extractHost(uri);
    int port = uri.getPort();
    std::string path = uri.getRawPath();
    std::string query = uri.getRawQuery();
         return this.createSocket(scheme, userInfo, host, port, path, query, timeout);
      }
   }

    WebSocket createSocket(const std::string& scheme, const std::string& userInfo, const std::string& host, int port, const std::string& path, const std::string& query, int timeout) {
    bool secure = isSecureConnectionRequired(scheme);
      if (host != nullptr && host.length() != 0) {
         path = determinePath(path);
    SocketConnector connector = this.createRawSocket(host, port, secure, timeout);
         return this.createWebSocket(secure, userInfo, host, port, path, query, connector);
      } else {
         throw IllegalArgumentException("The host part is empty.");
      }
   }

    static bool isSecureConnectionRequired(const std::string& scheme) {
      if (scheme == nullptr || scheme.length() == 0) {
         throw IllegalArgumentException("The scheme part is empty.");
      } else if ("wss".equalsIgnoreCase(scheme) || "https".equalsIgnoreCase(scheme)) {
    return true;
      } else if (!"ws".equalsIgnoreCase(scheme) && !"http".equalsIgnoreCase(scheme)) {
         throw IllegalArgumentException("Bad scheme: " + scheme);
      } else {
    return false;
      }
   }

    static std::string determinePath(const std::string& path) {
      if (path == nullptr || path.length() == 0) {
         return "/";
      } else {
         return path.startsWith("/") ? path : "/" + path;
      }
   }

    SocketConnector createRawSocket(const std::string& host, int port, bool secure, int timeout) {
      port = determinePort(port, secure);
    bool proxied = this.mProxySettings.getHost() != nullptr;
      return proxied ? this.createProxiedRawSocket(host, port, secure, timeout) : this.createDirectRawSocket(host, port, secure, timeout);
   }

    SocketConnector createProxiedRawSocket(const std::string& host, int port, bool secure, int timeout) {
    int proxyPort = determinePort(this.mProxySettings.getPort(), this.mProxySettings.isSecure());
    SocketFactory socketFactory = this.mProxySettings.selectSocketFactory();
    Socket socket = socketFactory.createSocket();
    Address address = std::make_shared<Address>(this.mProxySettings.getHost(), proxyPort);
    ProxyHandshaker handshaker = std::make_shared<ProxyHandshaker>(socket, host, port, this.mProxySettings);
    SSLSocketFactory sslSocketFactory = secure ? (SSLSocketFactory)this.mSocketFactorySettings.selectSocketFactory(secure) : nullptr;
      return std::make_shared<SocketConnector>(socket, address, timeout, handshaker, sslSocketFactory, host, port);
   }

    SocketConnector createDirectRawSocket(const std::string& host, int port, bool secure, int timeout) {
    SocketFactory factory = this.mSocketFactorySettings.selectSocketFactory(secure);
    Socket socket = factory.createSocket();
    Address address = std::make_shared<Address>(host, port);
      return std::make_shared<SocketConnector>(socket, address, timeout);
   }

    static int determinePort(int port, bool secure) {
      if (0 <= port) {
    return port;
      } else {
         return secure ? 443 : 80;
      }
   }

    WebSocket createWebSocket(bool secure, const std::string& userInfo, const std::string& host, int port, const std::string& path, const std::string& query, SocketConnector connector) {
      if (0 <= port) {
         host = host + ":" + port;
      }

      if (query != nullptr) {
         path = path + "?" + query;
      }

      return std::make_shared<WebSocket>(this, secure, userInfo, host, path, connector);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
