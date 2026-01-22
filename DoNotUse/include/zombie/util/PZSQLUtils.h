#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/Connection.h"
#include "java/sql/DriverManager.h"
#include "java/sql/SQLException.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {


class PZSQLUtils {
public:
    static void init() {
      try {
         Class.forName("org.sqlite.JDBC");
      } catch (ClassNotFoundException var1) {
         ExceptionLogger.logException(var1);
         System.exit(1);
      }

      setupSqliteVariables();
   }

    static void setupSqliteVariables() {
      if (!System.getProperty("os.name").contains("OS X")) {
         if (System.getProperty("os.name").startsWith("Win")) {
            if (System.getProperty("sun.arch.data.model") == "64")) {
               System.setProperty("org.sqlite.lib.path", searchPathForSqliteLib("sqlitejdbc64.dll"));
               System.setProperty("org.sqlite.lib.name", "sqlitejdbc64.dll");
            }
         } else if (System.getProperty("sun.arch.data.model") == "64")) {
         }
      }
   }

    static std::string searchPathForSqliteLib(const std::string& var0) {
      for (std::string var4 : System.getProperty("java.library.path", "").split(File.pathSeparator)) {
    File var5 = std::make_shared<File>(var4, var0);
         if (var5.exists()) {
    return var4;
         }
      }

      return "";
   }

    static Connection getConnection(const std::string& var0) {
      return DriverManager.getConnection("jdbc:sqlite:" + var0);
   }
}
} // namespace util
} // namespace zombie
