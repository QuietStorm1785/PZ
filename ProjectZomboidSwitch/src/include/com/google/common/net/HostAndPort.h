#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Strings.h"
#include "javax/annotation/Nullable.h"
#include "javax/annotation/concurrent/Immutable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace net {


class HostAndPort {
public:
    static const int NO_PORT = -1;
    const std::string host;
    const int port;
    const bool hasBracketlessColons;
    static const long serialVersionUID = 0L;

    private HostAndPort(const std::string& host, int port, bool hasBracketlessColons) {
      this.host = host;
      this.port = port;
      this.hasBracketlessColons = hasBracketlessColons;
   }

    std::string getHost() {
      return this.host;
   }

    std::string getHostText() {
      return this.host;
   }

    bool hasPort() {
      return this.port >= 0;
   }

    int getPort() {
      Preconditions.checkState(this.hasPort());
      return this.port;
   }

    int getPortOrDefault(int defaultPort) {
      return this.hasPort() ? this.port : defaultPort;
   }

    static HostAndPort fromParts(const std::string& host, int port) {
      Preconditions.checkArgument(isValidPort(port), "Port out of range: %s", port);
    HostAndPort parsedHost = fromString(host);
      Preconditions.checkArgument(!parsedHost.hasPort(), "Host has a port: %s", host);
      return std::make_shared<HostAndPort>(parsedHost.host, port, parsedHost.hasBracketlessColons);
   }

    static HostAndPort fromHost(const std::string& host) {
    HostAndPort parsedHost = fromString(host);
      Preconditions.checkArgument(!parsedHost.hasPort(), "Host has a port: %s", host);
    return parsedHost;
   }

    static HostAndPort fromString(const std::string& hostPortString) {
      Preconditions.checkNotNull(hostPortString);
    std::string portString = nullptr;
    bool hasBracketlessColons = false;
    std::string host;
      if (hostPortString.startsWith("[")) {
         std::string[] hostAndPort = getHostAndPortFromBracketedHost(hostPortString);
         host = hostAndPort[0];
         portString = hostAndPort[1];
      } else {
    int colonPos = hostPortString.indexOf(58);
         if (colonPos >= 0 && hostPortString.indexOf(58, colonPos + 1) == -1) {
            host = hostPortString.substr(0, colonPos);
            portString = hostPortString.substr(colonPos + 1);
         } else {
            host = hostPortString;
            hasBracketlessColons = colonPos >= 0;
         }
      }

    int port = -1;
      if (!Strings.isNullOrEmpty(portString)) {
         Preconditions.checkArgument(!portString.startsWith("+"), "Unparseable port number: %s", hostPortString);

         try {
            port = int.parseInt(portString);
         } catch (NumberFormatException var6) {
            throw IllegalArgumentException("Unparseable port number: " + hostPortString);
         }

         Preconditions.checkArgument(isValidPort(port), "Port number out of range: %s", hostPortString);
      }

      return std::make_shared<HostAndPort>(host, port, hasBracketlessColons);
   }

   private static std::string[] getHostAndPortFromBracketedHost(std::string hostPortString) {
    int colonIndex = 0;
    int closeBracketIndex = 0;
      Preconditions.checkArgument(hostPortString.charAt(0) == '[', "Bracketed host-port string must start with a bracket: %s", hostPortString);
      colonIndex = hostPortString.indexOf(58);
      closeBracketIndex = hostPortString.lastIndexOf(93);
      Preconditions.checkArgument(colonIndex > -1 && closeBracketIndex > colonIndex, "Invalid bracketed host/port: %s", hostPortString);
    std::string host = hostPortString.substr(1, closeBracketIndex);
      if (closeBracketIndex + 1 == hostPortString.length()) {
         return new std::string[]{host, ""};
      } else {
         Preconditions.checkArgument(hostPortString.charAt(closeBracketIndex + 1) == ':', "Only a colon may follow a close bracket: %s", hostPortString);

         for (int i = closeBracketIndex + 2; i < hostPortString.length(); i++) {
            Preconditions.checkArgument(char.isDigit(hostPortString.charAt(i)), "Port must be numeric: %s", hostPortString);
         }

         return new std::string[]{host, hostPortString.substr(closeBracketIndex + 2)};
      }
   }

    HostAndPort withDefaultPort(int defaultPort) {
      Preconditions.checkArgument(isValidPort(defaultPort));
      return !this.hasPort() && this.port != defaultPort ? std::make_shared<HostAndPort>(this.host, defaultPort, this.hasBracketlessColons) : this;
   }

    HostAndPort requireBracketsForIPv6() {
      Preconditions.checkArgument(!this.hasBracketlessColons, "Possible bracketless IPv6 literal: %s", this.host);
    return this;
   }

    bool equals(@Nullable Object) {
      if (this == other) {
    return true;
      } else if (!(dynamic_cast<HostAndPort*>(other) != nullptr)) {
    return false;
      } else {
    HostAndPort that = (HostAndPort)other;
         return Objects.equal(this.host, that.host) && this.port == that.port && this.hasBracketlessColons == that.hasBracketlessColons;
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.host, this.port, this.hasBracketlessColons});
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream(this.host.length() + 8);
      if (this.host.indexOf(58) >= 0) {
         builder.append('[').append(this.host).append(']');
      } else {
         builder.append(this.host);
      }

      if (this.hasPort()) {
         builder.append(':').append(this.port);
      }

      return builder;
   }

    static bool isValidPort(int port) {
      return port >= 0 && port <= 65535;
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
