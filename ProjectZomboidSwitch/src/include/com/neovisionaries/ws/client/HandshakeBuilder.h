#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URI.h"
#include <algorithm>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class HandshakeBuilder {
public:
   private static const std::string[] CONNECTION_HEADER = new std::string[]{"Connection", "Upgrade"};
   private static const std::string[] UPGRADE_HEADER = new std::string[]{"Upgrade", "websocket"};
   private static const std::string[] VERSION_HEADER = new std::string[]{"Sec-WebSocket-Version", "13"};
    static const std::string RN = "\r\n";
    bool mSecure;
    std::string mUserInfo;
    const std::string mHost;
    const std::string mPath;
    const URI mUri;
    std::string mKey;
   private Set<std::string> mProtocols;
   private List<WebSocketExtension> mExtensions;
   private List<std::string[]> mHeaders;

    public HandshakeBuilder(bool secure, const std::string& userInfo, const std::string& host, const std::string& path) {
      this.mSecure = secure;
      this.mUserInfo = userInfo;
      this.mHost = host;
      this.mPath = path;
      this.mUri = URI.create(std::string.format("%s://%s%s", secure ? "wss" : "ws", host, path));
   }

    public HandshakeBuilder(HandshakeBuilder source) {
      this.mSecure = source.mSecure;
      this.mUserInfo = source.mUserInfo;
      this.mHost = source.mHost;
      this.mPath = source.mPath;
      this.mUri = source.mUri;
      this.mKey = source.mKey;
      this.mProtocols = copyProtocols(source.mProtocols);
      this.mExtensions = copyExtensions(source.mExtensions);
      this.mHeaders = copyHeaders(source.mHeaders);
   }

    void addProtocol(const std::string& protocol) {
      if (!isValidProtocol(protocol)) {
         throw IllegalArgumentException(
            "'protocol' must be a non-empty string with characters in the range U+0021 to U+007E not including separator characters."
         );
      } else {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mProtocols == nullptr) {
               this.mProtocols = std::make_unique<LinkedHashSet<>>();
            }

            this.mProtocols.push_back(protocol);
         }
      }
   }

    void removeProtocol(const std::string& protocol) {
      if (protocol != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mProtocols != nullptr) {
               this.mProtocols.remove(protocol);
               if (this.mProtocols.size() == 0) {
                  this.mProtocols = nullptr;
               }
            }
         }
      }
   }

    void clearProtocols() {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mProtocols = nullptr;
      }
   }

    static bool isValidProtocol(const std::string& protocol) {
      if (protocol != nullptr && protocol.length() != 0) {
    int len = protocol.length();

         for (int i = 0; i < len; i++) {
    char ch = protocol.charAt(i);
            if (ch < '!' || '~' < ch || Token.isSeparator(ch)) {
    return false;
            }
         }

    return true;
      } else {
    return false;
      }
   }

    bool containsProtocol(const std::string& protocol) {
      /* synchronized - TODO: add std::mutex */ (this) {
         return this.mProtocols == nullptr ? false : this.mProtocols.contains(protocol);
      }
   }

    void addExtension(WebSocketExtension extension) {
      if (extension != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mExtensions == nullptr) {
               this.mExtensions = std::make_unique<std::vector<>>();
            }

            this.mExtensions.push_back(extension);
         }
      }
   }

    void addExtension(const std::string& extension) {
      this.addExtension(WebSocketExtension.parse(extension));
   }

    void removeExtension(WebSocketExtension extension) {
      if (extension != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mExtensions != nullptr) {
               this.mExtensions.remove(extension);
               if (this.mExtensions.size() == 0) {
                  this.mExtensions = nullptr;
               }
            }
         }
      }
   }

    void removeExtensions(const std::string& name) {
      if (name != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mExtensions != nullptr) {
               List<WebSocketExtension> extensionsToRemove = std::make_unique<std::vector<>>();

               for (WebSocketExtension extension : this.mExtensions) {
                  if (extension.getName() == name)) {
                     extensionsToRemove.push_back(extension);
                  }
               }

    for (auto& extensionx : extensionsToRemove)                  this.mExtensions.remove(extensionx);
               }

               if (this.mExtensions.size() == 0) {
                  this.mExtensions = nullptr;
               }
            }
         }
      }
   }

    void clearExtensions() {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mExtensions = nullptr;
      }
   }

    bool containsExtension(WebSocketExtension extension) {
      if (extension == nullptr) {
    return false;
      } else {
         /* synchronized - TODO: add std::mutex */ (this) {
            return this.mExtensions == nullptr ? false : this.mExtensions.contains(extension);
         }
      }
   }

    bool containsExtension(const std::string& name) {
      if (name == nullptr) {
    return false;
      } else {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mExtensions == nullptr) {
    return false;
            } else {
               for (WebSocketExtension extension : this.mExtensions) {
                  if (extension.getName() == name)) {
    return true;
                  }
               }

    return false;
            }
         }
      }
   }

    void addHeader(const std::string& name, const std::string& value) {
      if (name != nullptr && name.length() != 0) {
         if (value == nullptr) {
            value = "";
         }

         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mHeaders == nullptr) {
               this.mHeaders = std::make_unique<std::vector<>>();
            }

            this.mHeaders.push_back(new std::string[]{name, value});
         }
      }
   }

    void removeHeaders(const std::string& name) {
      if (name != nullptr && name.length() != 0) {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.mHeaders != nullptr) {
               List<std::string[]> headersToRemove = std::make_unique<std::vector<>>();

               for (std::string[] header : this.mHeaders) {
                  if (header[0] == name)) {
                     headersToRemove.push_back(header);
                  }
               }

               for (std::string[] headerx : headersToRemove) {
                  this.mHeaders.remove(headerx);
               }

               if (this.mHeaders.size() == 0) {
                  this.mHeaders = nullptr;
               }
            }
         }
      }
   }

    void clearHeaders() {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mHeaders = nullptr;
      }
   }

    void setUserInfo(const std::string& userInfo) {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mUserInfo = userInfo;
      }
   }

    void setUserInfo(const std::string& id, const std::string& password) {
      if (id == nullptr) {
         id = "";
      }

      if (password == nullptr) {
         password = "";
      }

    std::string userInfo = std::string.format("%s:%s", id, password);
      this.setUserInfo(userInfo);
   }

    void clearUserInfo() {
      /* synchronized - TODO: add std::mutex */ (this) {
         this.mUserInfo = nullptr;
      }
   }

    URI getURI() {
      return this.mUri;
   }

    void setKey(const std::string& key) {
      this.mKey = key;
   }

    std::string buildRequestLine() {
      return std::string.format("GET %s HTTP/1.1", this.mPath);
   }

   public List<std::string[]> buildHeaders() {
      List<std::string[]> headers = std::make_unique<std::vector<>>();
      headers.push_back(new std::string[]{"Host", this.mHost});
      headers.push_back(CONNECTION_HEADER);
      headers.push_back(UPGRADE_HEADER);
      headers.push_back(VERSION_HEADER);
      headers.push_back(new std::string[]{"Sec-WebSocket-Key", this.mKey});
      if (this.mProtocols != nullptr && this.mProtocols.size() != 0) {
         headers.push_back(new std::string[]{"Sec-WebSocket-Protocol", Misc.join(this.mProtocols, ", ")});
      }

      if (this.mExtensions != nullptr && this.mExtensions.size() != 0) {
         headers.push_back(new std::string[]{"Sec-WebSocket-Extensions", Misc.join(this.mExtensions, ", ")});
      }

      if (this.mUserInfo != nullptr && this.mUserInfo.length() != 0) {
         headers.push_back(new std::string[]{"Authorization", "Basic " + Base64.encode(this.mUserInfo)});
      }

      if (this.mHeaders != nullptr && this.mHeaders.size() != 0) {
         headers.addAll(this.mHeaders);
      }

    return headers;
   }

    static std::string build(const std::string& requestLine, List<std::string[]> headers) {
    std::stringstream builder = new std::stringstream();
      builder.append(requestLine).append("\r\n");

      for (std::string[] header : headers) {
         builder.append(header[0]).append(": ").append(header[1]).append("\r\n");
      }

      builder.append("\r\n");
      return builder;
   }

   private static Set<std::string> copyProtocols(Set<std::string> protocols) {
      if (protocols == nullptr) {
    return nullptr;
      } else {
         Set<std::string> newProtocols = new LinkedHashSet<>(protocols.size());
         newProtocols.addAll(protocols);
    return newProtocols;
      }
   }

   private static List<WebSocketExtension> copyExtensions(List<WebSocketExtension> extensions) {
      if (extensions == nullptr) {
    return nullptr;
      } else {
         List<WebSocketExtension> newExtensions = new std::vector<>(extensions.size());

    for (auto& extension : extensions)            newExtensions.push_back(std::make_shared<WebSocketExtension>(extension));
         }

    return newExtensions;
      }
   }

   private static List<std::string[]> copyHeaders(List<std::string[]> headers) {
      if (headers == nullptr) {
    return nullptr;
      } else {
         List<std::string[]> newHeaders = new std::vector<>(headers.size());

         for (std::string[] header : headers) {
            newHeaders.push_back(copyHeader(header));
         }

    return newHeaders;
      }
   }

   private static std::string[] copyHeader(std::string[] header) {
      return new std::string[]{header[0], header[1]};
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
