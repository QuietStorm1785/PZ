#pragma once
#include "java/sql/Connection.h"
#include "java/sql/DatabaseMetaData.h"
#include "java/sql/ResultSet.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DBSchema {
public:
private
  HashMap<String, HashMap<String, String>> schema =
      std::make_unique<HashMap<>>();
  KahluaTable fullTable;

public
  DBSchema(Connection connection) {
    try {
      DatabaseMetaData databaseMetaData = connection.getMetaData();
      String[] strings = new String[]{"TABLE"};
      ResultSet resultSet0 =
          databaseMetaData.getTables(null, null, null, strings);

      while (resultSet0.next()) {
        std::string string0 = resultSet0.getString(3);
        if (!string0.startsWith("SQLITE_")) {
          ResultSet resultSet1 =
              databaseMetaData.getColumns(null, null, string0, null);
          std::unordered_map hashMap = new HashMap();

          while (resultSet1.next()) {
            std::string string1 = resultSet1.getString(4);
            if (!string1 == "world")
                            && !string1 == "moderator")
                            && !string1 == "admin")
                            && !string1 == "password")
                            && !string1 == "encryptedPwd")
                            && !string1 == "pwdEncryptType")
                            && !string1 == "transactionID")) {
                              hashMap.put(string1, resultSet1.getString(6));
                            }
          }

          this.schema.put(string0, hashMap);
        }
      }
    } catch (Exception exception) {
      exception.printStackTrace();
    }
  }

  KahluaTable getFullTable() { return this.fullTable; }

  void setFullTable(KahluaTable table) { this.fullTable = table; }

public
  HashMap<String, HashMap<String, String>> getSchema() { return this.schema; }
}
} // namespace network
} // namespace zombie
