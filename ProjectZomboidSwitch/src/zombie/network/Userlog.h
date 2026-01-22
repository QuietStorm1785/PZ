#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class Userlog {
public:
    const std::string username;
    const std::string type;
    const std::string text;
    const std::string issuedBy;
    const std::string lastUpdate;
    int amount;

    public Userlog(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, int var5, const std::string& var6) {
      this.username = var1;
      this.type = var2;
      this.text = var3;
      this.issuedBy = var4;
      this.amount = var5;
      this.lastUpdate = var6;
   }

    std::string getUsername() {
      return this.username;
   }

    std::string getType() {
      return this.type;
   }

    std::string getText() {
      return this.text;
   }

    std::string getIssuedBy() {
      return this.issuedBy;
   }

    int getAmount() {
      return this.amount;
   }

    void setAmount(int var1) {
      this.amount = var1;
   }

    std::string getLastUpdate() {
      return this.lastUpdate;
   }
}
} // namespace network
} // namespace zombie
