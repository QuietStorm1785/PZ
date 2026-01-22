#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "java/net/URL.h"
#include "javax/net/SocketFactory.h"
#include "javax/net/ssl/SSLContext.h"
#include "javax/net/ssl/SSLSocketFactory.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class ProxySettings {
public:
    const WebSocketFactory mWebSocketFactory;
   private const Map<std::string, List<std::string>> mHeaders;
    const SocketFactorySettings mSocketFactorySettings;
    bool mSecure;
    std::string mHost;
    int mPort;
    std::string mId;
    std::string mPassword;

   ProxySettings(WebSocketFactory factory) {
      this.mWebSocketFactory = factory;
      this.mHeaders = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
      this.mSocketFactorySettings = std::make_unique<SocketFactorySettings>();
      this.reset();
   }

    WebSocketFactory getWebSocketFactory() {
      return this.mWebSocketFactory;
   }

    ProxySettings reset() {
      this.mSecure = false;
      this.mHost = nullptr;
      this.mPort = -1;
      this.mId = nullptr;
      this.mPassword = nullptr;
      this.mHeaders.clear();
    return this;
   }

    bool isSecure() {
      return this.mSecure;
   }

    ProxySettings setSecure(bool secure) {
      this.mSecure = secure;
    return this;
   }

    std::string getHost() {
      return this.mHost;
   }

    ProxySettings setHost(const std::string& host) {
      this.mHost = host;
    return this;
   }

    int getPort() {
      return this.mPort;
   }

    ProxySettings setPort(int port) {
      this.mPort = port;
    return this;
   }

    std::string getId() {
      return this.mId;
   }

    ProxySettings setId(const std::string& id) {
      this.mId = id;
    return this;
   }

    std::string getPassword() {
      return this.mPassword;
   }

    ProxySettings setPassword(const std::string& password) {
      this.mPassword = password;
    return this;
   }

    ProxySettings setCredentials(const std::string& id, const std::string& password) {
      return this.setId(id).setPassword(password);
   }

    ProxySettings setServer(const std::string& uri) {
    return uri = = nullptr ? this : this.setServer(URI.create(uri));
   }

    ProxySettings setServer(URL url) {
      if (url == nullptr) {
    return this;
      } else {
         try {
            return this.setServer(url.toURI());
         } catch (URISyntaxException var3) {
            throw IllegalArgumentException(var3);
         }
      }
   }

    ProxySettings setServer(URI uri) {
      if (uri == nullptr) {
    return this;
      } else {
    std::string scheme = uri.getScheme();
    std::string userInfo = uri.getUserInfo();
    std::string host = uri.getHost();
    int port = uri.getPort();
         return this.setServer(scheme, userInfo, host, port);
      }
   }

    ProxySettings setServer(const std::string& scheme, const std::string& userInfo, const std::string& host, int port) {
      this.setByScheme(scheme);
      this.setByUserInfo(userInfo);
      this.mHost = host;
      this.mPort = port;
    return this;
   }

    void setByScheme(const std::string& scheme) {
      if ("http".equalsIgnoreCase(scheme)) {
         this.mSecure = false;
      } else if ("https".equalsIgnoreCase(scheme)) {
         this.mSecure = true;
      }
   }

    void setByUserInfo(const std::string& userInfo) {
      if (userInfo != nullptr) {
         std::string[] pair = userInfo.split(":", 2);
    std::string id;
    std::string pw;
         switch (pair.length) {
            case 1:
               id = pair[0];
               pw = nullptr;
               break;
            case 2:
               id = pair[0];
               pw = pair[1];
               break;
            default:
               return;
         }

         if (id.length() != 0) {
            this.mId = id;
            this.mPassword = pw;
         }
      }
   }

   public Map<std::string, List<std::string>> getHeaders() {
      return this.mHeaders;
   }

    ProxySettings addHeader(const std::string& name, const std::string& value) {
      if (name != nullptr && name.length() != 0) {
         List<std::string> list = this.mHeaders.get(name);
         if (list == nullptr) {
            list = std::make_unique<std::vector<>>();
            this.mHeaders.put(name, list);
         }

         list.push_back(value);
    return this;
      } else {
    return this;
      }
   }

    SocketFactory getSocketFactory() {
      return this.mSocketFactorySettings.getSocketFactory();
   }

    ProxySettings setSocketFactory(SocketFactory factory) {
      this.mSocketFactorySettings.setSocketFactory(factory);
    return this;
   }

    SSLSocketFactory getSSLSocketFactory() {
      return this.mSocketFactorySettings.getSSLSocketFactory();
   }

    ProxySettings setSSLSocketFactory(SSLSocketFactory factory) {
      this.mSocketFactorySettings.setSSLSocketFactory(factory);
    return this;
   }

    SSLContext getSSLContext() {
      return this.mSocketFactorySettings.getSSLContext();
   }

    ProxySettings setSSLContext(SSLContext context) {
      this.mSocketFactorySettings.setSSLContext(context);
    return this;
   }

    SocketFactory selectSocketFactory() {
      return this.mSocketFactorySettings.selectSocketFactory(this.mSecure);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
