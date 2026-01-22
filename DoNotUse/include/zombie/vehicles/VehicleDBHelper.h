#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/Connection.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/PZSQLUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehicleDBHelper {
public:
    static bool isPlayerAlive(const std::string& var0, int var1) {
    File var2 = std::make_shared<File>(var0 + File.separator + "map_p.bin");
      if (var2.exists()) {
    return true;
      } else if (var1 == -1) {
    return false;
      } else {
    Connection var3 = nullptr;
    File var4 = std::make_shared<File>(var0 + File.separator + "vehicles.db");
         var4.setReadable(true, false);
         if (!var4.exists()) {
    return false;
         } else {
            try {
               var3 = PZSQLUtils.getConnection(var4.getAbsolutePath());
            } catch (Exception var20) {
               DebugLog.log("failed to create vehicles database");
               ExceptionLogger.logException(var20);
               System.exit(1);
            }

    bool var5 = false;
    std::string var6 = "SELECT isDead FROM localPlayers WHERE id=?";
    PreparedStatement var7 = nullptr;

    bool var9;
            try {
               var7 = var3.prepareStatement(var6);
               var7.setInt(1, var1);
    ResultSet var8 = var7.executeQuery();
               if (var8.next()) {
                  var5 = !var8.getBoolean(1);
               }

    return var5;
            } catch (SQLException var21) {
               var9 = false;
            } finally {
               try {
                  if (var7 != nullptr) {
                     var7.close();
                  }

                  var3.close();
               } catch (SQLException var19) {
                  System.out.println(var19.getMessage());
               }
            }

    return var9;
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
