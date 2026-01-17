#pragma once
#include "java/security/MessageDigest.h"
#include "java/security/NoSuchAlgorithmException.h"
#include "java/sql/Connection.h"
#include "java/sql/DatabaseMetaData.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "java/sql/Statement.h"
#include "java/text/DateFormat.h"
#include "java/text/SimpleDateFormat.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/secure/PZcrypt.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/util/PZSQLUtils.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ServerWorldDatabase {
public:
  static const DateFormat dateFormat =
      new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
  static ServerWorldDatabase instance = new ServerWorldDatabase();
  std::string CommandLineAdminUsername = "admin";
  std::string CommandLineAdminPassword;
  bool doAdmin = true;
  DBSchema dbSchema = null;
  static CharsetEncoder asciiEncoder = Charset.forName("US-ASCII").newEncoder();
  Connection conn;
  static const std::string nullChar = String.valueOf('\u0000');

  DBSchema getDBSchema() {
    if (this.dbSchema == nullptr) {
      this.dbSchema = new DBSchema(this.conn);
    }

    return this.dbSchema;
  }

  void executeQuery(const std::string &string, KahluaTable table) {
    PreparedStatement preparedStatement = this.conn.prepareStatement(string);
    KahluaTableIterator kahluaTableIterator = table.iterator();
    int int0 = 1;

    while (kahluaTableIterator.advance()) {
      preparedStatement.setString(int0++,
                                  (String)kahluaTableIterator.getValue());
    }

    preparedStatement.executeUpdate();
  }

public
  ArrayList<DBResult> getTableResult(String string1) throws SQLException {
    std::vector arrayList0 = new ArrayList();
    std::string string0 = "SELECT * FROM " + string1;
    if ("userlog" == string1)) {
            string0 = string0 + " ORDER BY lastUpdate DESC";
        }

    PreparedStatement preparedStatement = this.conn.prepareStatement(string0);
    ResultSet resultSet0 = preparedStatement.executeQuery();
    DatabaseMetaData databaseMetaData = this.conn.getMetaData();
    ResultSet resultSet1 =
        databaseMetaData.getColumns(null, null, string1, null);
    std::vector arrayList1 = new ArrayList();
    DBResult dBResult = new DBResult();

    while (resultSet1.next()) {
      std::string string2 = resultSet1.getString(4);
      if (!string2 == "world")
                && !string2 == "moderator")
                && !string2 == "admin")
                && !string2 == "password")
                && !string2 == "encryptedPwd")
                && !string2 == "pwdEncryptType")
                && !string2 == "transactionID")) {
                  arrayList1.add(string2);
                }
    }

    dBResult.setColumns(arrayList1);
    dBResult.setTableName(string1);

    while (resultSet0.next()) {
      for (int int0 = 0; int0 < arrayList1.size(); int0++) {
        std::string string3 = (String)arrayList1.get(int0);
        std::string string4 = resultSet0.getString(string3);
        if ("'false'" == string4)) {
                    string4 = "false";
                }

        if ("'true'" == string4)) {
                    string4 = "true";
                }

        if (string4 == nullptr) {
          string4 = "";
        }

        dBResult.getValues().put(string3, string4);
      }

      arrayList0.add(dBResult);
      dBResult = std::make_unique<DBResult>();
      dBResult.setColumns(arrayList1);
      dBResult.setTableName(string1);
    }

    preparedStatement.close();
    return arrayList0;
  }

  void saveAllTransactionsID(Integer > hashMap) {
    try {
      Iterator iterator = hashMap.keySet().iterator();
      PreparedStatement preparedStatement = null;

      while (iterator.hasNext()) {
        std::string string = (String)iterator.next();
        int integer = (Integer)hashMap.get(string);
        preparedStatement = this.conn.prepareStatement(
            "UPDATE whitelist SET transactionID = ? WHERE username = ?");
        preparedStatement.setString(1, integer.toString());
        preparedStatement.setString(2, string);
        preparedStatement.executeUpdate();
        preparedStatement.close();
      }
    } catch (Exception exception) {
      exception.printStackTrace();
    }
  }

  void saveTransactionID(const std::string &string, int integer) {
    try {
      if (!this.containsUser(string)) {
        this.addUser(string, "");
      }

      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET transactionID = ? WHERE username = ?");
      preparedStatement.setString(1, integer.toString());
      preparedStatement.setString(2, string);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (Exception exception) {
      exception.printStackTrace();
    }
  }

  bool containsUser(const std::string &string) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM whitelist WHERE username = ? AND world = ?");
      preparedStatement.setString(1, string);
      preparedStatement.setString(2, Core.GameSaveWorld);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (resultSet.next()) {
        preparedStatement.close();
        return true;
      }

      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }

    return false;
  }

  bool containsCaseinsensitiveUser(const std::string &string) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM whitelist WHERE LOWER(username) = LOWER(?) AND world "
          "= ?");
      preparedStatement.setString(1, string);
      preparedStatement.setString(2, Core.GameSaveWorld);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (resultSet.next()) {
        preparedStatement.close();
        return true;
      }

      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }

    return false;
  }

  std::string changeUsername(const std::string &string0,
                             const std::string &string2) {
    PreparedStatement preparedStatement = this.conn.prepareStatement(
        "SELECT * FROM whitelist WHERE username = ? AND world = ?");
    preparedStatement.setString(1, string0);
    preparedStatement.setString(2, Core.GameSaveWorld);
    ResultSet resultSet = preparedStatement.executeQuery();
    if (resultSet.next()) {
      std::string string1 = resultSet.getString("id");
      preparedStatement.close();
      preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET username = ? WHERE id = ?");
      preparedStatement.setString(1, string2);
      preparedStatement.setString(2, string1);
      preparedStatement.executeUpdate();
      preparedStatement.close();
      return "Changed " + string0 + " user's name into " + string2;
    } else {
      return !ServerOptions.instance.getBoolean("Open")
                 ? "User \"" + string0 +
                       "\" is not in the whitelist, use /adduser first"
                 : "Changed's name " + string0 + " into " + string2;
    }
  }

  std::string addUser(const std::string &string0, const std::string &string1) {
    if (this.containsCaseinsensitiveUser(string0)) {
      return "A user with this name already exists";
    } else {
      try {
        PreparedStatement preparedStatement = this.conn.prepareStatement(
            "SELECT * FROM whitelist WHERE username = ? AND world = ?");
        preparedStatement.setString(1, string0);
        preparedStatement.setString(2, Core.GameSaveWorld);
        ResultSet resultSet = preparedStatement.executeQuery();
        if (resultSet.next()) {
          preparedStatement.close();
          return "User " + string0 + " already exist.";
        }

        preparedStatement.close();
        preparedStatement = this.conn.prepareStatement(
            "INSERT INTO whitelist (world, username, password, encryptedPwd, "
            "pwdEncryptType) VALUES (?, ?, ?, 'true', '2')");
        preparedStatement.setString(1, Core.GameSaveWorld);
        preparedStatement.setString(2, string0);
        preparedStatement.setString(3, string1);
        preparedStatement.executeUpdate();
        preparedStatement.close();
      } catch (SQLException sQLException) {
        sQLException.printStackTrace();
      }

      return "User " + string0 + " created with the password " + string1;
    }
  }

  void updateDisplayName(const std::string &string0,
                         const std::string &string1) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM whitelist WHERE username = ? AND world = ?");
      preparedStatement.setString(1, string0);
      preparedStatement.setString(2, Core.GameSaveWorld);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (resultSet.next()) {
        preparedStatement.close();
        preparedStatement = this.conn.prepareStatement(
            "UPDATE whitelist SET displayName = ? WHERE username = ?");
        preparedStatement.setString(1, string1);
        preparedStatement.setString(2, string0);
        preparedStatement.executeUpdate();
        preparedStatement.close();
      }

      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }
  }

  std::string getDisplayName(const std::string &string0) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM whitelist WHERE username = ? AND world = ?");
      preparedStatement.setString(1, string0);
      preparedStatement.setString(2, Core.GameSaveWorld);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (resultSet.next()) {
        std::string string1 = resultSet.getString("displayName");
        preparedStatement.close();
        return string1;
      }

      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }

    return null;
  }

  std::string removeUser(const std::string &string) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "DELETE FROM whitelist WHERE world = ? and username = ?");
      preparedStatement.setString(1, Core.GameSaveWorld);
      preparedStatement.setString(2, string);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }

    return "User " + string + " removed from white list";
  }

  void removeUserLog(const std::string &string0, const std::string &string1,
                     const std::string &string2) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "DELETE FROM userlog WHERE username = ? AND type = ? AND text = ?");
      preparedStatement.setString(1, string0);
      preparedStatement.setString(2, string1);
      preparedStatement.setString(3, string2);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }
  }

  void create() {
    File file0 = new File(ZomboidFileSystem.instance.getCacheDir() +
                          File.separator + "db");
    if (!file0.exists()) {
      file0.mkdirs();
    }

    File file1 =
        new File(ZomboidFileSystem.instance.getCacheDir() + File.separator +
                 "db" + File.separator + GameServer.ServerName + ".db");
    file1.setReadable(true, false);
    file1.setExecutable(true, false);
    file1.setWritable(true, false);
    DebugLog.log("user database \"" + file1.getPath() + "\"");
    if (!file1.exists()) {
      try {
        file1.createNewFile();
        this.conn = PZSQLUtils.getConnection(file1.getAbsolutePath());
        Statement statement0 = this.conn.createStatement();
        statement0.executeUpdate(
            "CREATE TABLE [whitelist] ([id] INTEGER  PRIMARY KEY AUTOINCREMENT "
            "NOT NULL,[world] TEXT DEFAULT '" +
            GameServer.ServerName +
            "' NULL,[username] TEXT  NULL,[password] TEXT  NULL, [admin] "
            "BOOLEAN DEFAULT false NULL, [moderator] BOOLEAN DEFAULT false "
            "NULL, [banned] BOOLEAN DEFAULT false NULL, [priority] BOOLEAN "
            "DEFAULT false NULL,  [lastConnection] TEXT NULL)");
        statement0.executeUpdate(
            "CREATE UNIQUE INDEX [id] ON [whitelist]([id]  ASC)");
        statement0.executeUpdate(
            "CREATE UNIQUE INDEX [username] ON [whitelist]([username]  ASC)");
        statement0.executeUpdate(
            "CREATE TABLE [bannedip] ([ip] TEXT NOT NULL,[username] TEXT NULL, "
            "[reason] TEXT NULL)");
        statement0.close();
      } catch (Exception exception0) {
        exception0.printStackTrace();
        DebugLog.log("failed to create user database, server shut down");
        System.exit(1);
      }
    }

    if (this.conn == nullptr) {
      try {
        this.conn = PZSQLUtils.getConnection(file1.getAbsolutePath());
      } catch (Exception exception1) {
        exception1.printStackTrace();
        DebugLog.log("failed to open user database, server shut down");
        System.exit(1);
      }
    }

    DatabaseMetaData databaseMetaData = this.conn.getMetaData();
    ResultSet resultSet0 =
        databaseMetaData.getColumns(null, null, "whitelist", "admin");
    Statement statement1 = this.conn.createStatement();
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'admin' BOOLEAN NULL DEFAULT false");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "moderator");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'moderator' BOOLEAN NULL DEFAULT false");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "banned");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'banned' BOOLEAN NULL DEFAULT false");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "priority");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'priority' BOOLEAN NULL DEFAULT false");
    }

    resultSet0.close();
    resultSet0 = databaseMetaData.getColumns(nullptr, nullptr, "whitelist",
                                             "lastConnection");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'lastConnection' TEXT NULL");
    }

    resultSet0.close();
    resultSet0 = databaseMetaData.getColumns(nullptr, nullptr, "whitelist",
                                             "encryptedPwd");
    if (!resultSet0.next()) {
      statement1.executeUpdate("ALTER TABLE 'whitelist' ADD 'encryptedPwd' "
                               "BOOLEAN NULL DEFAULT false");
    }

    resultSet0.close();
    resultSet0 = databaseMetaData.getColumns(nullptr, nullptr, "whitelist",
                                             "pwdEncryptType");
    if (!resultSet0.next()) {
      statement1.executeUpdate("ALTER TABLE 'whitelist' ADD 'pwdEncryptType' "
                               "INTEGER NULL DEFAULT 1");
    }

    resultSet0.close();
    if (SteamUtils.isSteamModeEnabled()) {
      resultSet0 =
          databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "steamid");
      if (!resultSet0.next()) {
        statement1.executeUpdate(
            "ALTER TABLE 'whitelist' ADD 'steamid' TEXT NULL");
      }

      resultSet0.close();
      resultSet0 =
          databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "ownerid");
      if (!resultSet0.next()) {
        statement1.executeUpdate(
            "ALTER TABLE 'whitelist' ADD 'ownerid' TEXT NULL");
      }

      resultSet0.close();
    }

    resultSet0 = databaseMetaData.getColumns(nullptr, nullptr, "whitelist",
                                             "accesslevel");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'accesslevel' TEXT NULL");
    }

    resultSet0.close();
    resultSet0 = databaseMetaData.getColumns(nullptr, nullptr, "whitelist",
                                             "transactionID");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'transactionID' INTEGER NULL");
    }

    resultSet0.close();
    resultSet0 = databaseMetaData.getColumns(nullptr, nullptr, "whitelist",
                                             "displayName");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'whitelist' ADD 'displayName' TEXT NULL");
    }

    resultSet0.close();
    resultSet0 = statement1.executeQuery(
        "SELECT * FROM sqlite_master WHERE type = 'index' AND sql LIKE "
        "'%UNIQUE%' and name = 'username'");
    if (!resultSet0.next()) {
      try {
        statement1.executeUpdate(
            "CREATE UNIQUE INDEX [username] ON [whitelist]([username]  ASC)");
      } catch (Exception exception2) {
        System.out.println(
            "Can't create the username index because some of the username in "
            "the database are in double, will drop the double username.");
        statement1.executeUpdate(
            "DELETE FROM whitelist WHERE whitelist.rowid > (SELECT rowid FROM "
            "whitelist dbl WHERE whitelist.rowid <> dbl.rowid AND  "
            "whitelist.username = dbl.username);");
        statement1.executeUpdate(
            "CREATE UNIQUE INDEX [username] ON [whitelist]([username]  ASC)");
      }
    }

    resultSet0 =
        databaseMetaData.getTables(nullptr, nullptr, "bannedip", nullptr);
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "CREATE TABLE [bannedip] ([ip] TEXT NOT NULL,[username] TEXT NULL, "
          "[reason] TEXT NULL)");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getTables(nullptr, nullptr, "bannedid", nullptr);
    if (!resultSet0.next()) {
      statement1.executeUpdate("CREATE TABLE [bannedid] ([steamid] TEXT NOT "
                               "NULL, [reason] TEXT NULL)");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getTables(nullptr, nullptr, "userlog", nullptr);
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "CREATE TABLE [userlog] ([id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT "
          "NULL,[username] TEXT  NULL,[type] TEXT  NULL, [text] TEXT  NULL, "
          "[issuedBy] TEXT  NULL, [amount] INTEGER NULL, [lastUpdate] TEXT "
          "NULL)");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getColumns(nullptr, nullptr, "userlog", "lastUpdate");
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "ALTER TABLE 'userlog' ADD 'lastUpdate' TEXT NULL");
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "moderator");
    if (resultSet0.next()) {
    }

    resultSet0.close();
    resultSet0 =
        databaseMetaData.getColumns(nullptr, nullptr, "whitelist", "admin");
    if (resultSet0.next()) {
      resultSet0.close();
      PreparedStatement preparedStatement0 = this.conn.prepareStatement(
          "SELECT * FROM whitelist where admin = 'true'");
      ResultSet resultSet1 = preparedStatement0.executeQuery();

      while (resultSet1.next()) {
        PreparedStatement preparedStatement1 = this.conn.prepareStatement(
            "UPDATE whitelist set accesslevel = 'admin' where id = ?");
        preparedStatement1.setString(1, resultSet1.getString("id"));
        System.out.println(resultSet1.getString("username"));
        preparedStatement1.executeUpdate();
      }
    }

    resultSet0 =
        databaseMetaData.getTables(nullptr, nullptr, "tickets", nullptr);
    if (!resultSet0.next()) {
      statement1.executeUpdate(
          "CREATE TABLE [tickets] ([id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT "
          "NULL, [message] TEXT NOT NULL, [author] TEXT NOT NULL,[answeredID] "
          "INTEGER,[viewed] BOOLEAN NULL DEFAULT false)");
    }

    resultSet0.close();
    PreparedStatement preparedStatement2 = this.conn.prepareStatement(
        "SELECT * FROM whitelist WHERE username = ?");
    preparedStatement2.setString(1, this.CommandLineAdminUsername);
    resultSet0 = preparedStatement2.executeQuery();
    if (!resultSet0.next()) {
      preparedStatement2.close();
      std::string string0 = this.CommandLineAdminPassword;
      if (string0 == nullptr || string0.isEmpty()) {
        Scanner scanner = new Scanner(new InputStreamReader(System.in));
        System.out.println("User 'admin' not found, creating it ");
        System.out.println("Command line admin password: " +
                           this.CommandLineAdminPassword);
        System.out.println("Enter new administrator password: ");

        for (string0 = scanner.nextLine(); string0 == nullptr || "" == string0)
          ; string0 = scanner.nextLine()) {
          System.out.println("Enter new administrator password: ");
        }

        System.out.println("Confirm the password: ");

        for (String string1 = scanner.nextLine();
             string1 == nullptr || "" == string1) || !string0 == string1); string1 = scanner.nextLine()) {
          System.out.println("Wrong password, confirm the password: ");
        }
      }

      if (this.doAdmin) {
        preparedStatement2 = this.conn.prepareStatement(
            "INSERT INTO whitelist (username, password, accesslevel, "
            "encryptedPwd, pwdEncryptType) VALUES (?, ?, 'admin', 'true', "
            "'2')");
      } else {
        preparedStatement2 = this.conn.prepareStatement(
            "INSERT INTO whitelist (username, password, encryptedPwd, "
            "pwdEncryptType) VALUES (?, ?, 'true', '2')");
      }

      preparedStatement2.setString(1, this.CommandLineAdminUsername);
      preparedStatement2.setString(2, PZcrypt.hash(encrypt(string0)));
      preparedStatement2.executeUpdate();
      preparedStatement2.close();
      System.out.println("Administrator account '" +
                         this.CommandLineAdminUsername + "' created.");
    } else {
      preparedStatement2.close();
    }

    statement1.close();
    if (this.CommandLineAdminPassword != nullptr &&
        !this.CommandLineAdminPassword.isEmpty()) {
      std::string string2 =
          PZcrypt.hash(encrypt(this.CommandLineAdminPassword));
      PreparedStatement preparedStatement3 = this.conn.prepareStatement(
          "SELECT * FROM whitelist WHERE username = ?");
      preparedStatement3.setString(1, this.CommandLineAdminUsername);
      resultSet0 = preparedStatement3.executeQuery();
      if (resultSet0.next()) {
        preparedStatement3.close();
        preparedStatement3 = this.conn.prepareStatement(
            "UPDATE whitelist SET password = ? WHERE username = ?");
        preparedStatement3.setString(1, string2);
        preparedStatement3.setString(2, this.CommandLineAdminUsername);
        preparedStatement3.executeUpdate();
        System.out.println("admin password changed via -adminpassword option");
      } else {
        System.out.println("ERROR: -adminpassword ignored, no '" +
                           this.CommandLineAdminUsername + "' account in db");
      }

      preparedStatement3.close();
    }
  }

  void close() {
    try {
      if (this.conn != nullptr) {
        this.conn.close();
      }
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }
  }

  static bool isValidUserName(const std::string &string) {
    if (string == nullptr || string.trim().isEmpty() || string.contains(";") ||
        string.contains("@") || string.contains("$") || string.contains(",") ||
        string.contains("/") || string.contains(".") || string.contains("'") ||
        string.contains("?") || string.contains("\"") ||
        string.trim().length() < 3 || string.length() > 20) {
      return false;
    } else if (string.contains(nullChar)) {
      return false;
    } else {
            return string.trim() == "admin") ? true : !string.trim().toLowerCase().startsWith("admin");
    }
  }

public
  ServerWorldDatabase.LogonResult authClient(String string0, String string2,
                                             String string1, long long0) {
    System.out.println("User " + string0 + " is trying to connect.");
    ServerWorldDatabase.LogonResult logonResult =
        new ServerWorldDatabase.LogonResult();
    if (!ServerOptions.instance.AllowNonAsciiUsername.getValue() &&
        !asciiEncoder.canEncode(string0)) {
      logonResult.bAuthorized = false;
      logonResult.dcReason = "NonAsciiCharacters";
      return logonResult;
    } else if (!isValidUserName(string0)) {
      logonResult.bAuthorized = false;
      logonResult.dcReason = "InvalidUsername";
      return logonResult;
    } else {
      try {
        if (!SteamUtils.isSteamModeEnabled() && !string1 == "127.0.0.1")) {
            PreparedStatement preparedStatement0 = this.conn.prepareStatement(
                "SELECT * FROM bannedip WHERE ip = ?");
            preparedStatement0.setString(1, string1);
            ResultSet resultSet0 = preparedStatement0.executeQuery();
            if (resultSet0.next()) {
              logonResult.bAuthorized = false;
              logonResult.bannedReason = resultSet0.getString("reason");
              logonResult.banned = true;
              preparedStatement0.close();
              return logonResult;
            }

            preparedStatement0.close();
          }

        if (isNullOrEmpty(string2) && ServerOptions.instance.Open.getValue() &&
            ServerOptions.instance.AutoCreateUserInWhiteList.getValue()) {
          logonResult.dcReason = "UserPasswordRequired";
          logonResult.bAuthorized = false;
          return logonResult;
        }

        PreparedStatement preparedStatement1 = this.conn.prepareStatement(
            "SELECT * FROM whitelist WHERE LOWER(username) = LOWER(?) AND "
            "world = ?");
        preparedStatement1.setString(1, string0);
        preparedStatement1.setString(2, Core.GameSaveWorld);
        ResultSet resultSet1 = preparedStatement1.executeQuery();
        if (resultSet1.next()) {
          if (!isNullOrEmpty(resultSet1.getString("password")) &&
                  (resultSet1.getString("encryptedPwd") == "false") ||
              resultSet1.getString("encryptedPwd") == "N"))) {
              std::string string3 = resultSet1.getString("password");
              std::string string4 = encrypt(string3);
              PreparedStatement preparedStatement2 = this.conn.prepareStatement(
                  "UPDATE whitelist SET encryptedPwd = 'true' WHERE username = "
                  "? and password = ?");
              preparedStatement2.setString(1, string0);
              preparedStatement2.setString(2, string3);
              preparedStatement2.executeUpdate();
              preparedStatement2.close();
              preparedStatement2 = this.conn.prepareStatement(
                  "UPDATE whitelist SET password = ? WHERE username = ? AND "
                  "password = ?");
              preparedStatement2.setString(1, string4);
              preparedStatement2.setString(2, string0);
              preparedStatement2.setString(3, string3);
              preparedStatement2.executeUpdate();
              preparedStatement2.close();
              resultSet1 = preparedStatement1.executeQuery();
            }

          if (!isNullOrEmpty(resultSet1.getString("password")) &&
              resultSet1.getInt("pwdEncryptType") == 1) {
            std::string string5 = resultSet1.getString("password");
            std::string string6 = PZcrypt.hash(string5);
            PreparedStatement preparedStatement3 = this.conn.prepareStatement(
                "UPDATE whitelist SET pwdEncryptType = '2', password = ? WHERE "
                "username = ? AND password = ?");
            preparedStatement3.setString(1, string6);
            preparedStatement3.setString(2, string0);
            preparedStatement3.setString(3, string5);
            preparedStatement3.executeUpdate();
            preparedStatement3.close();
            resultSet1 = preparedStatement1.executeQuery();
          }

          if (!isNullOrEmpty(resultSet1.getString("password")) &&
              !resultSet1.getString("password") == string2)) {
              logonResult.bAuthorized = false;
              preparedStatement1.close();
              if (isNullOrEmpty(string2)) {
                logonResult.dcReason = "DuplicateAccount";
              } else {
                logonResult.dcReason = "InvalidUsernamePassword";
              }

              return logonResult;
            }

          logonResult.bAuthorized = true;
                    logonResult.admin = "true" == resultSet1.getString("admin")) || "Y" == resultSet1.getString("admin"));
                    logonResult.accessLevel =
                        resultSet1.getString("accesslevel");
                    if (logonResult.accessLevel == nullptr) {
                      logonResult.accessLevel = "";
                      if (logonResult.admin) {
                        logonResult.accessLevel = "admin";
                      }

                      this.setAccessLevel(string0, logonResult.accessLevel);
                    }

                    logonResult.banned = "true" == resultSet1.getString("banned")) || "Y" == resultSet1.getString("banned"));
                    if (logonResult.banned) {
                      logonResult.bAuthorized = false;
                    }

                    if (resultSet1.getString("transactionID") == nullptr) {
                      logonResult.transactionID = 0;
                    } else {
                      logonResult.transactionID = Integer.parseInt(
                          resultSet1.getString("transactionID"));
                    }

                    logonResult.priority = resultSet1.getString("priority") == "true");
                    preparedStatement1.close();
                    return logonResult;
        }

        if (ServerOptions.instance.Open.getValue()) {
          if (!this.isNewAccountAllowed(string1, long0)) {
            preparedStatement1.close();
            logonResult.bAuthorized = false;
            logonResult.dcReason = "MaxAccountsReached";
            return logonResult;
          }

          logonResult.bAuthorized = true;
          logonResult.newUser = true;
          preparedStatement1.close();
          return logonResult;
        }

        logonResult.bAuthorized = false;
        logonResult.dcReason = "UnknownUsername";
        preparedStatement1.close();
      } catch (Exception exception) {
        exception.printStackTrace();
      }

      return logonResult;
    }
  }

public
  ServerWorldDatabase.LogonResult authClient(long long0) {
    std::string string = SteamUtils.convertSteamIDToString(long0);
    System.out.println("Steam client " + string +
                       " is initiating a connection.");
    ServerWorldDatabase.LogonResult logonResult =
        new ServerWorldDatabase.LogonResult();

    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM bannedid WHERE steamid = ?");
      preparedStatement.setString(1, string);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (resultSet.next()) {
        logonResult.bAuthorized = false;
        logonResult.bannedReason = resultSet.getString("reason");
        logonResult.banned = true;
        preparedStatement.close();
        return logonResult;
      }

      preparedStatement.close();
      logonResult.bAuthorized = true;
    } catch (Exception exception) {
      exception.printStackTrace();
    }

    return logonResult;
  }

public
  ServerWorldDatabase.LogonResult authOwner(long long0, long long1) {
    std::string string0 = SteamUtils.convertSteamIDToString(long0);
    std::string string1 = SteamUtils.convertSteamIDToString(long1);
    System.out.println("Steam client " + string0 + " borrowed the game from " +
                       string1);
    ServerWorldDatabase.LogonResult logonResult =
        new ServerWorldDatabase.LogonResult();

    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM bannedid WHERE steamid = ?");
      preparedStatement.setString(1, string1);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (resultSet.next()) {
        logonResult.bAuthorized = false;
        logonResult.bannedReason = resultSet.getString("reason");
        logonResult.banned = true;
        preparedStatement.close();
        return logonResult;
      }

      preparedStatement.close();
      logonResult.bAuthorized = true;
      preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET ownerid = ? where steamid = ?");
      preparedStatement.setString(1, string1);
      preparedStatement.setString(2, string0);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (Exception exception) {
      exception.printStackTrace();
    }

    return logonResult;
  }

  bool isNewAccountAllowed(const std::string &var1, long long0) {
    int int0 = ServerOptions.instance.MaxAccountsPerUser.getValue();
    if (int0 <= 0) {
      return true;
    } else if (!SteamUtils.isSteamModeEnabled()) {
      return true;
    } else {
      std::string string = SteamUtils.convertSteamIDToString(long0);
      int int1 = 0;

      try(PreparedStatement preparedStatement = this.conn.prepareStatement(
              "SELECT * FROM whitelist WHERE steamid = ? AND ((accessLevel = "
              "?) OR (accessLevel is NULL))")) {
        preparedStatement.setString(1, string);
        preparedStatement.setString(2, "");
        ResultSet resultSet = preparedStatement.executeQuery();

        while (resultSet.next()) {
          int1++;
        }
      }
      catch (Exception exception) {
        DebugLog.Multiplayer.printException(exception, "Query execution failed",
                                            LogSeverity.Error);
        return true;
      }

      DebugLog.Multiplayer.debugln(
          "IsNewAccountAllowed: steam-id=%d count=%d/%d", long0, int1, int0);
      return int1 < int0;
    }
  }

  static std::string encrypt(const std::string &string0) {
    if (isNullOrEmpty(string0)) {
      return "";
    } else {
      byte[] bytes = nullptr;

      try {
        bytes = MessageDigest.getInstance("MD5").digest(string0.getBytes());
      } catch (NoSuchAlgorithmException noSuchAlgorithmException) {
        System.out.println("Can't encrypt password");
        noSuchAlgorithmException.printStackTrace();
      }

      StringBuilder stringBuilder = new StringBuilder();

      for (int int0 = 0; int0 < bytes.length; int0++) {
        std::string string1 = Integer.toHexString(bytes[int0]);
        if (string1.length() == 1) {
          stringBuilder.append('0');
          stringBuilder.append(string1.charAt(string1.length() - 1));
        } else {
          stringBuilder.append(string1.substring(string1.length() - 2));
        }
      }

      return stringBuilder.toString();
    }
  }

  std::string changePwd(const std::string &string0, const std::string &string1,
                        const std::string &string2) {
    PreparedStatement preparedStatement =
        this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? "
                                   "AND password = ? AND world = ?");
    preparedStatement.setString(1, string0);
    preparedStatement.setString(2, string1);
    preparedStatement.setString(3, Core.GameSaveWorld);
    ResultSet resultSet = preparedStatement.executeQuery();
    if (resultSet.next()) {
      preparedStatement.close();
      preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET pwdEncryptType = '2', password = ? WHERE "
          "username = ? and password = ?");
      preparedStatement.setString(1, string2);
      preparedStatement.setString(2, string0);
      preparedStatement.setString(3, string1);
      preparedStatement.executeUpdate();
      preparedStatement.close();
      return "Your new password is " + string2;
    } else {
      preparedStatement.close();
      return "Wrong password for user " + string0;
    }
  }

  std::string grantAdmin(const std::string &string, bool boolean0) {
    PreparedStatement preparedStatement = this.conn.prepareStatement(
        "SELECT * FROM whitelist WHERE username = ? AND world = ?");
    preparedStatement.setString(1, string);
    preparedStatement.setString(2, Core.GameSaveWorld);
    ResultSet resultSet = preparedStatement.executeQuery();
    if (resultSet.next()) {
      preparedStatement.close();
      preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET admin = ? WHERE username = ?");
      preparedStatement.setString(1, boolean0 ? "true" : "false");
      preparedStatement.setString(2, string);
      preparedStatement.executeUpdate();
      preparedStatement.close();
      return boolean0 ? "User " + string + " is now admin"
                      : "User " + string + " is no longer admin";
    } else {
      preparedStatement.close();
      return "User \"" + string +
             "\" is not in the whitelist, use /adduser first";
    }
  }

  std::string setAccessLevel(const std::string &string1,
                             const std::string &string0) {
    string0 = string0.trim();
    if (!this.containsUser(string1)) {
      this.addUser(string1, "");
    }

    PreparedStatement preparedStatement = this.conn.prepareStatement(
        "SELECT * FROM whitelist WHERE username = ? AND world = ?");
    preparedStatement.setString(1, string1);
    preparedStatement.setString(2, Core.GameSaveWorld);
    ResultSet resultSet = preparedStatement.executeQuery();
    if (resultSet.next()) {
      preparedStatement.close();
      preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET accesslevel = ? WHERE username = ?");
      preparedStatement.setString(1, string0);
      preparedStatement.setString(2, string1);
      preparedStatement.executeUpdate();
      preparedStatement.close();
            return string0 == "") ? "User " + string1 + " no longer has access level" : "User " + string1 + " is now " + string0;
    } else {
      preparedStatement.close();
      return "User \"" + string1 +
             "\" is not in the whitelist, use /adduser first";
    }
  }

public
  ArrayList<Userlog> getUserlog(String string) {
    std::vector arrayList = new ArrayList();

    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM userlog WHERE username = ?");
      preparedStatement.setString(1, string);
      ResultSet resultSet = preparedStatement.executeQuery();

      while (resultSet.next()) {
        arrayList.add(new Userlog(
            string, resultSet.getString("type"), resultSet.getString("text"),
            resultSet.getString("issuedBy"), resultSet.getInt("amount"),
            resultSet.getString("lastUpdate")));
      }

      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }

    return arrayList;
  }

  void addUserlog(const std::string &string1, Userlog.UserlogType userlogType,
                  const std::string &string2, const std::string &string3,
                  int int0) {
    try {
      bool boolean0 = true;
      std::string string0 = dateFormat.format(Calendar.getInstance().getTime());
      if (userlogType != Userlog.UserlogType.LuaChecksum &&
          userlogType != Userlog.UserlogType.DupeItem) {
        if (userlogType == Userlog.UserlogType.Kicked ||
            userlogType == Userlog.UserlogType.Banned ||
            userlogType == Userlog.UserlogType.SuspiciousActivity ||
            userlogType == Userlog.UserlogType.UnauthorizedPacket) {
          PreparedStatement preparedStatement0 = this.conn.prepareStatement(
              "SELECT * FROM userlog WHERE username = ? AND type = ? AND text "
              "= ? AND issuedBy = ?");
          preparedStatement0.setString(1, string1);
          preparedStatement0.setString(2, userlogType.toString());
          preparedStatement0.setString(3, string2);
          preparedStatement0.setString(4, string3);
          ResultSet resultSet0 = preparedStatement0.executeQuery();
          if (resultSet0.next()) {
            boolean0 = false;
            int0 = Integer.parseInt(resultSet0.getString("amount")) + 1;
            preparedStatement0.close();
            PreparedStatement preparedStatement1 = this.conn.prepareStatement(
                "UPDATE userlog set amount = ?, lastUpdate = ? WHERE username "
                "= ? AND type = ? AND text = ? AND issuedBy = ?");
            preparedStatement1.setString(1, String.valueOf(int0));
            preparedStatement1.setString(2, string0);
            preparedStatement1.setString(3, string1);
            preparedStatement1.setString(4, userlogType.toString());
            preparedStatement1.setString(5, string2);
            preparedStatement1.setString(6, string3);
            preparedStatement1.executeUpdate();
            preparedStatement1.close();
          }
        }
      } else {
        PreparedStatement preparedStatement2 = this.conn.prepareStatement(
            "SELECT * FROM userlog WHERE username = ? AND type = ?");
        preparedStatement2.setString(1, string1);
        preparedStatement2.setString(2, userlogType.toString());
        ResultSet resultSet1 = preparedStatement2.executeQuery();
        if (resultSet1.next()) {
          boolean0 = false;
          int0 = Integer.parseInt(resultSet1.getString("amount")) + 1;
          preparedStatement2.close();
          PreparedStatement preparedStatement3 = this.conn.prepareStatement(
              "UPDATE userlog set amount = ?, lastUpdate = ?, text = ? WHERE "
              "username = ? AND type = ?");
          preparedStatement3.setString(1, String.valueOf(int0));
          preparedStatement3.setString(2, string0);
          preparedStatement3.setString(3, string2);
          preparedStatement3.setString(4, string1);
          preparedStatement3.setString(5, userlogType.toString());
          preparedStatement3.executeUpdate();
          preparedStatement3.close();
        }
      }

      if (boolean0) {
        PreparedStatement preparedStatement4 = this.conn.prepareStatement(
            "INSERT INTO userlog (username, type, text, issuedBy, amount, "
            "lastUpdate) VALUES (?, ?, ?, ?, ?, ?)");
        preparedStatement4.setString(1, string1);
        preparedStatement4.setString(2, userlogType.toString());
        preparedStatement4.setString(3, string2);
        preparedStatement4.setString(4, string3);
        preparedStatement4.setString(5, String.valueOf(int0));
        preparedStatement4.setString(6, string0);
        preparedStatement4.executeUpdate();
        preparedStatement4.close();
      }
    } catch (Exception exception) {
      exception.printStackTrace();
    }
  }

  std::string banUser(const std::string &string0, bool boolean1) {
    PreparedStatement preparedStatement0 = this.conn.prepareStatement(
        "SELECT * FROM whitelist WHERE username = ? AND world = ?");
    preparedStatement0.setString(1, string0);
    preparedStatement0.setString(2, Core.GameSaveWorld);
    ResultSet resultSet = preparedStatement0.executeQuery();
    bool boolean0 = resultSet.next();
    if (boolean1 && !boolean0) {
      PreparedStatement preparedStatement1 = this.conn.prepareStatement(
          "INSERT INTO whitelist (world, username, password, encryptedPwd) "
          "VALUES (?, ?, 'bogus', 'false')");
      preparedStatement1.setString(1, Core.GameSaveWorld);
      preparedStatement1.setString(2, string0);
      preparedStatement1.executeUpdate();
      preparedStatement1.close();
      resultSet = preparedStatement0.executeQuery();
      boolean0 = true;
    }

    if (boolean0) {
      std::string string1 = "true";
      if (!boolean1) {
        string1 = "false";
      }

      preparedStatement0.close();
      preparedStatement0 = this.conn.prepareStatement(
          "UPDATE whitelist SET banned = ? WHERE username = ?");
      preparedStatement0.setString(1, string1);
      preparedStatement0.setString(2, string0);
      preparedStatement0.executeUpdate();
      preparedStatement0.close();
      if (SteamUtils.isSteamModeEnabled()) {
        preparedStatement0 = this.conn.prepareStatement(
            "SELECT steamid FROM whitelist WHERE username = ? AND world = ?");
        preparedStatement0.setString(1, string0);
        preparedStatement0.setString(2, Core.GameSaveWorld);
        resultSet = preparedStatement0.executeQuery();
        if (resultSet.next()) {
          std::string string2 = resultSet.getString("steamid");
          preparedStatement0.close();
          if (string2 != nullptr && !string2.isEmpty()) {
            this.banSteamID(string2, "", boolean1);
          }
        } else {
          preparedStatement0.close();
        }
      }

      return boolean1 ? "User " + string0 + " is now banned"
                      : "User " + string0 + " is now un-banned";
    } else {
      preparedStatement0.close();
      return "User \"" + string0 +
             "\" is not in the whitelist, use /adduser first";
    }
  }

  std::string banIp(const std::string &string0, const std::string &string1,
                    const std::string &string2, bool boolean0) {
    if (boolean0) {
      PreparedStatement preparedStatement0 = this.conn.prepareStatement(
          "INSERT INTO bannedip (ip, username, reason) VALUES (?, ?, ?)");
      preparedStatement0.setString(1, string0);
      preparedStatement0.setString(2, string1);
      preparedStatement0.setString(3, string2);
      preparedStatement0.executeUpdate();
      preparedStatement0.close();
    } else {
      if (string0 != nullptr) {
        PreparedStatement preparedStatement1 =
            this.conn.prepareStatement("DELETE FROM bannedip WHERE ip = ?");
        preparedStatement1.setString(1, string0);
        preparedStatement1.executeUpdate();
        preparedStatement1.close();
      }

      PreparedStatement preparedStatement2 =
          this.conn.prepareStatement("DELETE FROM bannedip WHERE username = ?");
      preparedStatement2.setString(1, string1);
      preparedStatement2.executeUpdate();
      preparedStatement2.close();
    }

    return "";
  }

  std::string banSteamID(const std::string &string0, const std::string &string1,
                         bool boolean0) {
    if (boolean0) {
      PreparedStatement preparedStatement0 = this.conn.prepareStatement(
          "INSERT INTO bannedid (steamid, reason) VALUES (?, ?)");
      preparedStatement0.setString(1, string0);
      preparedStatement0.setString(2, string1);
      preparedStatement0.executeUpdate();
      preparedStatement0.close();
    } else {
      PreparedStatement preparedStatement1 =
          this.conn.prepareStatement("DELETE FROM bannedid WHERE steamid = ?");
      preparedStatement1.setString(1, string0);
      preparedStatement1.executeUpdate();
      preparedStatement1.close();
    }

    return "";
  }

  std::string setUserSteamID(const std::string &string0,
                             const std::string &string1) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM whitelist WHERE username = ?");
      preparedStatement.setString(1, string0);
      ResultSet resultSet = preparedStatement.executeQuery();
      if (!resultSet.next()) {
        preparedStatement.close();
        return "User " + string0 + " not found";
      }

      preparedStatement.close();
      preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET steamid = ? WHERE username = ?");
      preparedStatement.setString(1, string1);
      preparedStatement.setString(2, string0);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }

    return "User " + string0 + " SteamID set to " + string1;
  }

  void setPassword(const std::string &string1, const std::string &string0) {
    try {
      PreparedStatement preparedStatement = this.conn.prepareStatement(
          "UPDATE whitelist SET pwdEncryptType = '2', password = ? WHERE "
          "username = ? and world = ?");
      preparedStatement.setString(1, string0);
      preparedStatement.setString(2, string1);
      preparedStatement.setString(3, Core.GameSaveWorld);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }
  }

  void updateLastConnectionDate(const std::string &string0,
                                const std::string &string1) {
    try {
      PreparedStatement preparedStatement =
          this.conn.prepareStatement("UPDATE whitelist SET lastConnection = ? "
                                     "WHERE username = ? AND password = ?");
      preparedStatement.setString(
          1, dateFormat.format(Calendar.getInstance().getTime()));
      preparedStatement.setString(2, string0);
      preparedStatement.setString(3, string1);
      preparedStatement.executeUpdate();
      preparedStatement.close();
    } catch (SQLException sQLException) {
      sQLException.printStackTrace();
    }
  }

  static bool isNullOrEmpty(const std::string &string) {
    return string = = null || string.isEmpty();
  }

  std::string addWarningPoint(const std::string &string0,
                              const std::string &string1, int int0,
                              const std::string &string2) {
    PreparedStatement preparedStatement = this.conn.prepareStatement(
        "SELECT * FROM whitelist WHERE username = ? AND world = ?");
    preparedStatement.setString(1, string0);
    preparedStatement.setString(2, Core.GameSaveWorld);
    ResultSet resultSet = preparedStatement.executeQuery();
    if (resultSet.next()) {
      this.addUserlog(string0, Userlog.UserlogType.WarningPoint, string1,
                      string2, int0);
      return "Added a warning point on " + string0 + " reason: " + string1;
    } else {
      return "User " + string0 + " doesn't exist.";
    }
  }

  void addTicket(const std::string &string0, const std::string &string1,
                 int int0) {
    if (int0 > -1) {
      PreparedStatement preparedStatement0 = this.conn.prepareStatement(
          "INSERT INTO tickets (author, message, answeredID) VALUES (?, ?, ?)");
      preparedStatement0.setString(1, string0);
      preparedStatement0.setString(2, string1);
      preparedStatement0.setInt(3, int0);
      preparedStatement0.executeUpdate();
      preparedStatement0.close();
    } else {
      PreparedStatement preparedStatement1 = this.conn.prepareStatement(
          "INSERT INTO tickets (author, message) VALUES (?, ?)");
      preparedStatement1.setString(1, string0);
      preparedStatement1.setString(2, string1);
      preparedStatement1.executeUpdate();
      preparedStatement1.close();
    }
  }

public
  ArrayList<DBTicket> getTickets(String string) throws SQLException {
    std::vector arrayList = new ArrayList();
    PreparedStatement preparedStatement = null;
    if (string != nullptr) {
      preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM tickets WHERE author = ? and answeredID is nullptr");
      preparedStatement.setString(1, string);
    } else {
      preparedStatement = this.conn.prepareStatement(
          "SELECT * FROM tickets where answeredID is nullptr");
    }

    ResultSet resultSet = preparedStatement.executeQuery();

    while (resultSet.next()) {
      DBTicket dBTicket0 =
          new DBTicket(resultSet.getString("author"),
                       resultSet.getString("message"), resultSet.getInt("id"));
      arrayList.add(dBTicket0);
      DBTicket dBTicket1 = this.getAnswer(dBTicket0.getTicketID());
      if (dBTicket1 != nullptr) {
        dBTicket0.setAnswer(dBTicket1);
      }
    }

    return arrayList;
  }

  DBTicket getAnswer(int int0) {
    PreparedStatement preparedStatement = null;
    preparedStatement = this.conn.prepareStatement(
        "SELECT * FROM tickets WHERE answeredID = ?");
    preparedStatement.setInt(1, int0);
    ResultSet resultSet = preparedStatement.executeQuery();
    return resultSet.next() ? new DBTicket(resultSet.getString("author"),
                                           resultSet.getString("message"),
                                           resultSet.getInt("id"))
                            : nullptr;
  }

  void removeTicket(int int0) {
    DBTicket dBTicket = this.getAnswer(int0);
    if (dBTicket != nullptr) {
      PreparedStatement preparedStatement0 =
          this.conn.prepareStatement("DELETE FROM tickets WHERE id = ?");
      preparedStatement0.setInt(1, dBTicket.getTicketID());
      preparedStatement0.executeUpdate();
      preparedStatement0.close();
    }

    PreparedStatement preparedStatement1 =
        this.conn.prepareStatement("DELETE FROM tickets WHERE id = ?");
    preparedStatement1.setInt(1, int0);
    preparedStatement1.executeUpdate();
    preparedStatement1.close();
  }

public
  class LogonResult {
    bool bAuthorized = false;
    int x;
    int y;
    int z;
    bool newUser = false;
    bool admin = false;
    bool banned = false;
    bool priority = false;
    std::string bannedReason = null;
    std::string dcReason = null;
    std::string accessLevel = "";
    int transactionID = 0;
  }
}
} // namespace network
} // namespace zombie
