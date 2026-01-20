#pragma once
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/MessageDigest.h"
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class HandshakeReader {
public:
    static const std::string ACCEPT_MAGIC = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    const WebSocket mWebSocket;

    public HandshakeReader(WebSocket websocket) {
      this.mWebSocket = websocket;
   }

   public Map<std::string, List<std::string>> readHandshake(WebSocketInputStream input, std::string key) throws WebSocketException {
    StatusLine statusLine = this.readStatusLine(input);
      Map<std::string, List<std::string>> headers = this.readHttpHeaders(input);
      this.validateStatusLine(statusLine, headers, input);
      this.validateUpgrade(statusLine, headers);
      this.validateConnection(statusLine, headers);
      this.validateAccept(statusLine, headers, key);
      this.validateExtensions(statusLine, headers);
      this.validateProtocol(statusLine, headers);
    return headers;
   }

    StatusLine readStatusLine(WebSocketInputStream input) {
    std::string line;
      try {
         line = input.readLine();
      } catch (IOException var5) {
         throw WebSocketException(
            WebSocketError.OPENING_HANDSHAKE_RESPONSE_FAILURE, "Failed to read an opening handshake response from the server: " + var5.getMessage(), var5
         );
      }

      if (line != nullptr && line.length() != 0) {
         try {
            return std::make_shared<StatusLine>(line);
         } catch (Exception var4) {
            throw WebSocketException(
               WebSocketError.STATUS_LINE_BAD_FORMAT, "The status line of the opening handshake response is badly formatted. The status line is: " + line
            );
         }
      } else {
         throw WebSocketException(WebSocketError.STATUS_LINE_EMPTY, "The status line of the opening handshake response is empty.");
      }
   }

   private Map<std::string, List<std::string>> readHttpHeaders(WebSocketInputStream input) throws WebSocketException {
      Map<std::string, List<std::string>> headers = new std::map<>(std::string.CASE_INSENSITIVE_ORDER);
    std::stringstream builder = nullptr;

      while (true) {
    std::string line;
         try {
            line = input.readLine();
         } catch (IOException var6) {
            throw WebSocketException(
               WebSocketError.HTTP_HEADER_FAILURE, "An error occurred while HTTP header section was being read: " + var6.getMessage(), var6
            );
         }

         if (line == nullptr || line.length() == 0) {
            if (builder != nullptr) {
               this.parseHttpHeader(headers, builder);
            }

    return headers;
         }

    char ch = line.charAt(0);
         if (ch != ' ' && ch != '\t') {
            if (builder != nullptr) {
               this.parseHttpHeader(headers, builder);
            }

            builder = new std::stringstream(line);
         } else if (builder != nullptr) {
            line = line.replaceAll("^[ \t]+", " ");
            builder.append(line);
         }
      }
   }

    void parseHttpHeader(List<std::string>> headers, const std::string& header) {
      std::string[] pair = header.split(":", 2);
      if (pair.length >= 2) {
    std::string name = pair[0].trim();
    std::string value = pair[1].trim();
         List<std::string> list = headers.get(name);
         if (list == nullptr) {
            list = std::make_unique<std::vector<>>();
            headers.put(name, list);
         }

         list.push_back(value);
      }
   }

    void validateStatusLine(StatusLine statusLine, List<std::string>> headers, WebSocketInputStream input) {
      if (statusLine.getStatusCode() != 101) {
         byte[] body = this.readBody(headers, input);
         throw OpeningHandshakeException(
            WebSocketError.NOT_SWITCHING_PROTOCOLS,
            "The status code of the opening handshake response is not '101 Switching Protocols'. The status line is: " + statusLine,
            statusLine,
            headers,
            body
         );
      }
   }

   private byte[] readBody(Map<std::string, List<std::string>> headers, WebSocketInputStream input) {
    int length = this.getContentLength(headers);
      if (length <= 0) {
    return nullptr;
      } else {
         try {
            byte[] body = new byte[length];
            input.readBytes(body, length);
    return body;
         } catch (Throwable var5) {
    return nullptr;
         }
      }
   }

    int getContentLength(List<std::string>> headers) {
      try {
         return int.parseInt(headers.get("Content-Length").get(0));
      } catch (Exception var3) {
         return -1;
      }
   }

    void validateUpgrade(StatusLine statusLine, List<std::string>> headers) {
      List<std::string> values = headers.get("Upgrade");
      if (values != nullptr && values.size() != 0) {
    for (auto& value : values)            std::string[] elements = value.split("\\s*,\\s*");

    for (auto& element : elements)               if ("websocket".equalsIgnoreCase(element)) {
                  return;
               }
            }
         }

         throw OpeningHandshakeException(
            WebSocketError.NO_WEBSOCKET_IN_UPGRADE_HEADER, "'websocket' was not found in 'Upgrade' header.", statusLine, headers
         );
      } else {
         throw OpeningHandshakeException(
            WebSocketError.NO_UPGRADE_HEADER, "The opening handshake response does not contain 'Upgrade' header.", statusLine, headers
         );
      }
   }

    void validateConnection(StatusLine statusLine, List<std::string>> headers) {
      List<std::string> values = headers.get("Connection");
      if (values != nullptr && values.size() != 0) {
    for (auto& value : values)            std::string[] elements = value.split("\\s*,\\s*");

    for (auto& element : elements)               if ("Upgrade".equalsIgnoreCase(element)) {
                  return;
               }
            }
         }

         throw OpeningHandshakeException(
            WebSocketError.NO_UPGRADE_IN_CONNECTION_HEADER, "'Upgrade' was not found in 'Connection' header.", statusLine, headers
         );
      } else {
         throw OpeningHandshakeException(
            WebSocketError.NO_CONNECTION_HEADER, "The opening handshake response does not contain 'Connection' header.", statusLine, headers
         );
      }
   }

    void validateAccept(StatusLine statusLine, List<std::string>> headers, const std::string& key) {
      List<std::string> values = headers.get("Sec-WebSocket-Accept");
      if (values == nullptr) {
         throw OpeningHandshakeException(
            WebSocketError.NO_SEC_WEBSOCKET_ACCEPT_HEADER,
            "The opening handshake response does not contain 'Sec-WebSocket-Accept' header.",
            statusLine,
            headers
         );
      } else {
    std::string actual = values.get(0);
    std::string input = key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

    std::string expected;
         try {
    MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] digest = md.digest(Misc.getBytesUTF8(input));
            expected = Base64.encode(digest);
         } catch (Exception var10) {
            return;
         }

         if (!expected == actual)) {
            throw OpeningHandshakeException(
               WebSocketError.UNEXPECTED_SEC_WEBSOCKET_ACCEPT_HEADER,
               "The value of 'Sec-WebSocket-Accept' header is different from the expected one.",
               statusLine,
               headers
            );
         }
      }
   }

    void validateExtensions(StatusLine statusLine, List<std::string>> headers) {
      List<std::string> values = headers.get("Sec-WebSocket-Extensions");
      if (values != nullptr && values.size() != 0) {
         List<WebSocketExtension> extensions = std::make_unique<std::vector<>>();

    for (auto& value : values)            std::string[] elements = value.split("\\s*,\\s*");

    for (auto& element : elements)    WebSocketExtension extension = WebSocketExtension.parse(element);
               if (extension == nullptr) {
                  throw OpeningHandshakeException(
                     WebSocketError.EXTENSION_PARSE_ERROR, "The value in 'Sec-WebSocket-Extensions' failed to be parsed: " + element, statusLine, headers
                  );
               }

    std::string name = extension.getName();
               if (!this.mWebSocket.getHandshakeBuilder().containsExtension(name)) {
                  throw OpeningHandshakeException(
                     WebSocketError.UNSUPPORTED_EXTENSION,
                     "The extension contained in the Sec-WebSocket-Extensions header is not supported: " + name,
                     statusLine,
                     headers
                  );
               }

               extension.validate();
               extensions.push_back(extension);
            }
         }

         this.validateExtensionCombination(statusLine, headers, extensions);
         this.mWebSocket.setAgreedExtensions(extensions);
      }
   }

    void validateExtensionCombination(StatusLine statusLine, List<std::string>> headers, List<WebSocketExtension> extensions) {
    WebSocketExtension pmce = nullptr;

    for (auto& extension : extensions)         if (dynamic_cast<PerMessageCompressionExtension*>(extension) != nullptr) {
            if (pmce != nullptr) {
    std::string message = std::string.format("'%s' extension and '%s' extension conflict with each other.", pmce.getName(), extension.getName());
               throw OpeningHandshakeException(WebSocketError.EXTENSIONS_CONFLICT, message, statusLine, headers);
            }

            pmce = extension;
         }
      }
   }

    void validateProtocol(StatusLine statusLine, List<std::string>> headers) {
      List<std::string> values = headers.get("Sec-WebSocket-Protocol");
      if (values != nullptr) {
    std::string protocol = values.get(0);
         if (protocol != nullptr && protocol.length() != 0) {
            if (!this.mWebSocket.getHandshakeBuilder().containsProtocol(protocol)) {
               throw OpeningHandshakeException(
                  WebSocketError.UNSUPPORTED_PROTOCOL,
                  "The protocol contained in the Sec-WebSocket-Protocol header is not supported: " + protocol,
                  statusLine,
                  headers
               );
            } else {
               this.mWebSocket.setAgreedProtocol(protocol);
            }
         }
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
