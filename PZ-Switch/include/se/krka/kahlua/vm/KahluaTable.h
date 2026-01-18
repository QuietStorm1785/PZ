#pragma once
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KahluaTable {
public:
 virtual ~KahluaTable() = default;
 void setMetatable(KahluaTable var1);

 KahluaTable getMetatable();

 void rawset(void *var1, void *var2);

 void *rawget(void *var1);

 void rawset(int var1, void *var2);

 void *rawget(int var1);

 int len();

 KahluaTableIterator iterator();

 bool isEmpty();

 void wipe();

 int size();

 void save(ByteBuffer var1);

 void load(ByteBuffer var1, int var2);

 void save(DataOutputStream var1);

 void load(DataInputStream var1, int var2);

 std::string getString(const std::string &var1);
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
