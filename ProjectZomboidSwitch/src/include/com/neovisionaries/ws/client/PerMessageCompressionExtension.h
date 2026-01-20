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

class PerMessageCompressionExtension : public WebSocketExtension {
public:
    public PerMessageCompressionExtension(const std::string& name) {
      super(name);
   }

    public PerMessageCompressionExtension(WebSocketExtension source) {
      super(source);
   }

   protected abstract byte[] decompress(byte[] var1) throws WebSocketException;

   protected abstract byte[] compress(byte[] var1) throws WebSocketException;
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
