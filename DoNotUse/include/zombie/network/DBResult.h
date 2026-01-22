#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {


class DBResult {
public:
   private std::unordered_map<std::string, std::string> values = std::make_unique<std::unordered_map<>>();
   private std::vector<std::string> columns = std::make_unique<std::vector<>>();
    std::string type;
    std::string tableName;

   public std::unordered_map<std::string, std::string> getValues() {
      return this.values;
   }

    std::string getType() {
      return this.type;
   }

    void setType(const std::string& var1) {
      this.type = var1;
   }

   public std::vector<std::string> getColumns() {
      return this.columns;
   }

    void setColumns(std::vector<std::string> var1) {
      this.columns = var1;
   }

    std::string getTableName() {
      return this.tableName;
   }

    void setTableName(const std::string& var1) {
      this.tableName = var1;
   }
}
} // namespace network
} // namespace zombie
