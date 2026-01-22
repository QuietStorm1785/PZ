#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class ServerWorldDatabase {
public:
    bool bAuthorized;
    int x;
    int y;
    int z;
    bool newUser;
    bool admin;
    bool banned;
    bool priority;
    std::string bannedReason;
    std::string dcReason;
    std::string accessLevel;
    int transactionID;

   public ServerWorldDatabase$LogonResult(ServerWorldDatabase var1) {
      this.this$0 = var1;
      this.bAuthorized = false;
      this.newUser = false;
      this.admin = false;
      this.banned = false;
      this.priority = false;
      this.bannedReason = nullptr;
      this.dcReason = nullptr;
      this.accessLevel = "";
      this.transactionID = 0;
   }
}
} // namespace network
} // namespace zombie
