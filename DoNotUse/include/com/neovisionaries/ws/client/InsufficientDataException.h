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

class InsufficientDataException : public WebSocketException {
public:
    static const long serialVersionUID = 1L;
    const int mRequestedByteCount;
    const int mReadByteCount;

    public InsufficientDataException(int requestedByteCount, int readByteCount) {
      super(WebSocketError.INSUFFICENT_DATA, "The end of the stream has been reached unexpectedly.");
      this.mRequestedByteCount = requestedByteCount;
      this.mReadByteCount = readByteCount;
   }

    int getRequestedByteCount() {
      return this.mRequestedByteCount;
   }

    int getReadByteCount() {
      return this.mReadByteCount;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
