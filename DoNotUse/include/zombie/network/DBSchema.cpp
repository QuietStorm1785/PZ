#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/Connection.h"
#include "java/sql/DatabaseMetaData.h"
#include "java/sql/ResultSet.h"
#include "se/krka/kahlua/vm/KahluaTable.h"

namespace zombie {
namespace network {


class DBSchema {
public:
   private std::unordered_map<std::string, std::unordered_map<std::string, std::string>> schema = std::make_unique<std::unordered_map<>>();
    KahluaTable fullTable;

    public DBSchema(Connection var1) {
      try {
    DatabaseMetaData var2 = var1.getMetaData();
         std::string[] var3 = new std::string[]{"TABLE"};
    ResultSet var4 = var2.getTables(nullptr, nullptr, nullptr, var3);

         while (var4.next()) {
    std::string var5 = var4.getString(3);
            if (!var5.startsWith("SQLITE_")) {
    ResultSet var6 = var2.getColumns(nullptr, nullptr, var5, nullptr);
    std::unordered_map var7 = new std::unordered_map();

               while (var6.next()) {
    std::string var8 = var6.getString(4);
                  if (!var8 == "world")
                     && !var8 == "moderator")
                     && !var8 == "admin")
                     && !var8 == "password")
                     && !var8 == "encryptedPwd")
                     && !var8 == "pwdEncryptType")
                     && !var8 == "transactionID")) {
                     var7.put(var8, var6.getString(6));
                  }
               }

               this.schema.put(var5, var7);
            }
         }
      } catch (Exception var9) {
         var9.printStackTrace();
      }
   }

    KahluaTable getFullTable() {
      return this.fullTable;
   }

    void setFullTable(KahluaTable var1) {
      this.fullTable = var1;
   }

   public std::unordered_map<std::string, std::unordered_map<std::string, std::string>> getSchema() {
      return this.schema;
   }
}
} // namespace network
} // namespace zombie
