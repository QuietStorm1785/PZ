#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DBResult {
public:
private
 HashMap<String, String> values = std::make_unique<HashMap<>>();
private
 ArrayList<String> columns = std::make_unique<ArrayList<>>();
 std::string type;
 std::string tableName;

public
 HashMap<String, String> getValues() { return this->values; }

 std::string getType() { return this->type; }

 void setType(std::string_view _type) { this->type = _type; }

public
 ArrayList<String> getColumns() { return this->columns; }

 void setColumns(ArrayList<String> _columns) { this->columns = _columns; }

 std::string getTableName() { return this->tableName; }

 void setTableName(std::string_view _tableName) {
 this->tableName = _tableName;
 }
}
} // namespace network
} // namespace zombie
