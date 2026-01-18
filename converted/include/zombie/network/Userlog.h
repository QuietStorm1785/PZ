#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Userlog {
public:
 const std::string username;
 const std::string type;
 const std::string text;
 const std::string issuedBy;
 const std::string lastUpdate;
 int amount;

 public Userlog(const std::string& string0, const std::string& string1, const std::string& string2, const std::string& string3, int int0, const std::string& string4) {
 this->username = string0;
 this->type = string1;
 this->text = string2;
 this->issuedBy = string3;
 this->amount = int0;
 this->lastUpdate = string4;
 }

 std::string getUsername() {
 return this->username;
 }

 std::string getType() {
 return this->type;
 }

 std::string getText() {
 return this->text;
 }

 std::string getIssuedBy() {
 return this->issuedBy;
 }

 int getAmount() {
 return this->amount;
 }

 void setAmount(int _amount) {
 this->amount = _amount;
 }

 std::string getLastUpdate() {
 return this->lastUpdate;
 }

 public static enum UserlogType {
 AdminLog(0),
 Kicked(1),
 Banned(2),
 DupeItem(3),
 LuaChecksum(4),
 WarningPoint(5),
 UnauthorizedPacket(6),
 SuspiciousActivity(7);

 const int index;

 private UserlogType(int int1) {
 this->index = int1;
 }

 int index() {
 return this->index;
 }

 public static Userlog.UserlogType fromIndex(int value) {
 return Userlog.UserlogType.class.getEnumConstants()[value];
 }

 public static Userlog.UserlogType FromString(String str) {
 return valueOf();
 }
 }
}
} // namespace network
} // namespace zombie
