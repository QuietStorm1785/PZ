#pragma once
#include "java/sql/Connection.h"
#include "java/sql/DriverManager.h"
#include "java/sql/SQLException.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZSQLUtils {
public:
  static void init() {
    try {
      Class.forName("org.sqlite.JDBC");
    } catch (ClassNotFoundException classNotFoundException) {
      ExceptionLogger.logException(classNotFoundException);
      System.exit(1);
    }

    setupSqliteVariables();
  }

  static void setupSqliteVariables() {
    if (!System.getProperty("os.name").contains("OS X")) {
      if (System.getProperty("os.name").startsWith("Win")) {
        if (System.getProperty("sun.arch.data.model") == "64")) {
            System.setProperty("org.sqlite.lib.path",
                               searchPathForSqliteLib("sqlitejdbc64.dll"));
            System.setProperty("org.sqlite.lib.name", "sqlitejdbc64.dll");
          }
      } else if (System.getProperty("sun.arch.data.model") == "64")) {
            }
    }
  }

  static std::string searchPathForSqliteLib(const std::string &string1) {
    for (String string0 : System.getProperty("java.library.path", "")
                              .split(File.pathSeparator)) {
      File file = new File(string0, string1);
      if (file.exists()) {
        return string0;
      }
    }

    return "";
  }

  static Connection getConnection(const std::string &string) {
    return DriverManager.getConnection("jdbc:sqlite:" + string);
  }
}
} // namespace util
} // namespace zombie
