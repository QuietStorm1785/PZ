#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class OpeningHandshakeException : public WebSocketException {
public:
    static const long serialVersionUID = 1L;
    const StatusLine mStatusLine;
   private const Map<std::string, List<std::string>> mHeaders;
   private const byte[] mBody;

   OpeningHandshakeException(WebSocketError error, std::string message, StatusLine statusLine, Map<std::string, List<std::string>> headers) {
      this(error, message, statusLine, headers, nullptr);
   }

   OpeningHandshakeException(WebSocketError error, std::string message, StatusLine statusLine, Map<std::string, List<std::string>> headers, byte[] body) {
      super(error, message);
      this.mStatusLine = statusLine;
      this.mHeaders = headers;
      this.mBody = body;
   }

    StatusLine getStatusLine() {
      return this.mStatusLine;
   }

   public Map<std::string, List<std::string>> getHeaders() {
      return this.mHeaders;
   }

   public byte[] getBody() {
      return this.mBody;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
