#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/net/SocketFactory.h"
#include "javax/net/ssl/SSLContext.h"
#include "javax/net/ssl/SSLSocketFactory.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class SocketFactorySettings {
public:
    SocketFactory mSocketFactory;
    SSLSocketFactory mSSLSocketFactory;
    SSLContext mSSLContext;

    SocketFactory getSocketFactory() {
      return this.mSocketFactory;
   }

    void setSocketFactory(SocketFactory factory) {
      this.mSocketFactory = factory;
   }

    SSLSocketFactory getSSLSocketFactory() {
      return this.mSSLSocketFactory;
   }

    void setSSLSocketFactory(SSLSocketFactory factory) {
      this.mSSLSocketFactory = factory;
   }

    SSLContext getSSLContext() {
      return this.mSSLContext;
   }

    void setSSLContext(SSLContext context) {
      this.mSSLContext = context;
   }

    SocketFactory selectSocketFactory(bool secure) {
      if (secure) {
         if (this.mSSLContext != nullptr) {
            return this.mSSLContext.getSocketFactory();
         } else {
            return (SocketFactory)(this.mSSLSocketFactory != nullptr ? this.mSSLSocketFactory : SSLSocketFactory.getDefault());
         }
      } else {
         return this.mSocketFactory != nullptr ? this.mSocketFactory : SocketFactory.getDefault();
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
