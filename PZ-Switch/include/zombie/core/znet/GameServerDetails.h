#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GameServerDetails {
public:
 std::string address;
 int port;
 long steamId;
 std::string name;
 std::string gamedir;
 std::string map;
 std::string gameDescription;
 std::string tags;
 int ping;
 int numPlayers;
 int maxPlayers;
 bool passwordProtected;
 int version;

public
 GameServerDetails() {}

public
 GameServerDetails(String string0, int int0, long long0, String string1,
 String string2, String string3, String string4,
 String string5, int int1, int int2, int int3,
 boolean boolean0, int int4) {
 this->address = string0;
 this->port = int0;
 this->steamId = long0;
 this->name = string1;
 this->gamedir = string2;
 this->map = string3;
 this->gameDescription = string4;
 this->tags = string5;
 this->ping = int1;
 this->numPlayers = int2;
 this->maxPlayers = int3;
 this->passwordProtected = boolean0;
 this->version = int4;
 }
}
} // namespace znet
} // namespace core
} // namespace zombie
