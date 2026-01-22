#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/InetSocketAddress.h"

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class Address {
public:
    const std::string mHost;
    const int mPort;
   private transient std::string mString;

   Address(std::string host, int port) {
      this.mHost = host;
      this.mPort = port;
   }

    InetSocketAddress toInetSocketAddress() {
      return std::make_shared<InetSocketAddress>(this.mHost, this.mPort);
   }

    std::string toString() {
      if (this.mString == nullptr) {
         this.mString = std::string.format("%s:%d", this.mHost, this.mPort);
      }

      return this.mString;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
