#pragma once
#include "java/sql/Connection.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/PZSQLUtils.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleDBHelper {
public:
 static bool isPlayerAlive(const std::string &string0, int int0) {
 File file0 = new File(string0 + File.separator + "map_p.bin");
 if (file0.exists()) {
 return true;
 } else if (int0 == -1) {
 return false;
 } else {
 Connection connection = nullptr;
 File file1 = new File(string0 + File.separator + "vehicles.db");
 file1.setReadable(true, false);
 if (!file1.exists()) {
 return false;
 } else {
 try {
 connection = PZSQLUtils.getConnection(file1.getAbsolutePath());
 } catch (Exception exception) {
 DebugLog.log("failed to create vehicles database");
 ExceptionLogger.logException(exception);
 System.exit(1);
 }

 bool boolean0 = false;
 std::string string1 = "SELECT isDead FROM localPlayers WHERE id=?";
 PreparedStatement preparedStatement = nullptr;

 bool boolean1;
 try {
 preparedStatement = connection.prepareStatement(string1);
 preparedStatement.setInt(1, int0);
 ResultSet resultSet = preparedStatement.executeQuery();
 if (resultSet.next()) {
 boolean0 = !resultSet.getBoolean(1);
 }

 return boolean0;
 } catch (SQLException sQLException0) {
 boolean1 = false;
 } finally {
 try {
 if (preparedStatement != nullptr) {
 preparedStatement.close();
 }

 connection.close();
 } catch (SQLException sQLException1) {
 System.out.println(sQLException1.getMessage());
 }
 }

 return boolean1;
 }
 }
 }
}
} // namespace vehicles
} // namespace zombie
