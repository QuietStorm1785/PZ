#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace chat {

class ServerChatMessage : public ChatMessage {
public:
    public ServerChatMessage(ChatBase var1, const std::string& var2) {
      super(var1, var2);
      super.setAuthor("Server");
      this.setServerAuthor(true);
   }

    std::string getAuthor() {
      return super.getAuthor();
   }

    void setAuthor(const std::string& var1) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace chat
} // namespace zombie
