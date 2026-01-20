#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/network/ServerWorldDatabase/LogonResult.h"
#include "zombie/network/Userlog/UserlogType.h"
#include "zombie/util/PZSQLUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace network {


class ServerWorldDatabase {
public:
    static const DateFormat dateFormat = std::make_shared<SimpleDateFormat>("yyyy-MM-dd HH:mm:ss");
    static ServerWorldDatabase instance = std::make_shared<ServerWorldDatabase>();
    std::string CommandLineAdminUsername = "admin";
    std::string CommandLineAdminPassword;
    bool doAdmin = true;
    DBSchema dbSchema = nullptr;
    static CharsetEncoder asciiEncoder = Charset.forName("US-ASCII").newEncoder();
    Connection conn;
    static const std::string nullChar = std::string.valueOf('\u0000');

    DBSchema getDBSchema() {
      if (this.dbSchema == nullptr) {
         this.dbSchema = std::make_shared<DBSchema>(this.conn);
      }

      return this.dbSchema;
   }

    void executeQuery(const std::string& var1, KahluaTable var2) {
    PreparedStatement var3 = this.conn.prepareStatement(var1);
    KahluaTableIterator var4 = var2.iterator();
    int var5 = 1;

      while (var4.advance()) {
         var3.setString(var5++, (std::string)var4.getValue());
      }

      var3.executeUpdate();
   }

   public std::vector<DBResult> getTableResult(std::string var1) throws SQLException {
    std::vector var2 = new std::vector();
    std::string var3 = "SELECT * FROM " + var1;
      if ("userlog" == var1)) {
         var3 = var3 + " ORDER BY lastUpdate DESC";
      }

    PreparedStatement var4 = this.conn.prepareStatement(var3);
    ResultSet var5 = var4.executeQuery();
    DatabaseMetaData var6 = this.conn.getMetaData();
    ResultSet var7 = var6.getColumns(nullptr, nullptr, var1, nullptr);
    std::vector var8 = new std::vector();
    DBResult var9 = std::make_shared<DBResult>();

      while (var7.next()) {
    std::string var10 = var7.getString(4);
         if (!var10 == "world")
            && !var10 == "moderator")
            && !var10 == "admin")
            && !var10 == "password")
            && !var10 == "encryptedPwd")
            && !var10 == "pwdEncryptType")
            && !var10 == "transactionID")) {
            var8.push_back(var10);
         }
      }

      var9.setColumns(var8);
      var9.setTableName(var1);

      while (var5.next()) {
         for (int var13 = 0; var13 < var8.size(); var13++) {
    std::string var11 = (std::string)var8.get(var13);
    std::string var12 = var5.getString(var11);
            if ("'false'" == var12)) {
               var12 = "false";
            }

            if ("'true'" == var12)) {
               var12 = "true";
            }

            if (var12 == nullptr) {
               var12 = "";
            }

            var9.getValues().put(var11, var12);
         }

         var2.push_back(var9);
         var9 = std::make_unique<DBResult>();
         var9.setColumns(var8);
         var9.setTableName(var1);
      }

      var4.close();
    return var2;
   }

    void saveAllTransactionsID(int> var1) {
      try {
    Iterator var2 = var1.keySet().iterator();
    PreparedStatement var3 = nullptr;

         while (var2.hasNext()) {
    std::string var4 = (std::string)var2.next();
    int var5 = (int)var1.get(var4);
            var3 = this.conn.prepareStatement("UPDATE whitelist SET transactionID = ? WHERE username = ?");
            var3.setString(1, var5);
            var3.setString(2, var4);
            var3.executeUpdate();
            var3.close();
         }
      } catch (Exception var6) {
         var6.printStackTrace();
      }
   }

    void saveTransactionID(const std::string& var1, int var2) {
      try {
         if (!this.containsUser(var1)) {
            this.addUser(var1, "");
         }

    PreparedStatement var3 = this.conn.prepareStatement("UPDATE whitelist SET transactionID = ? WHERE username = ?");
         var3.setString(1, var2);
         var3.setString(2, var1);
         var3.executeUpdate();
         var3.close();
      } catch (Exception var4) {
         var4.printStackTrace();
      }
   }

    bool containsUser(const std::string& var1) {
      try {
    PreparedStatement var2 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
         var2.setString(1, var1);
         var2.setString(2, Core.GameSaveWorld);
    ResultSet var3 = var2.executeQuery();
         if (var3.next()) {
            var2.close();
    return true;
         }

         var2.close();
      } catch (SQLException var4) {
         var4.printStackTrace();
      }

    return false;
   }

    bool containsCaseinsensitiveUser(const std::string& var1) {
      try {
    PreparedStatement var2 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE LOWER(username) = LOWER(?) AND world = ?");
         var2.setString(1, var1);
         var2.setString(2, Core.GameSaveWorld);
    ResultSet var3 = var2.executeQuery();
         if (var3.next()) {
            var2.close();
    return true;
         }

         var2.close();
      } catch (SQLException var4) {
         var4.printStackTrace();
      }

    return false;
   }

    std::string changeUsername(const std::string& var1, const std::string& var2) {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
      var3.setString(1, var1);
      var3.setString(2, Core.GameSaveWorld);
    ResultSet var4 = var3.executeQuery();
      if (var4.next()) {
    std::string var5 = var4.getString("id");
         var3.close();
         var3 = this.conn.prepareStatement("UPDATE whitelist SET username = ? WHERE id = ?");
         var3.setString(1, var2);
         var3.setString(2, var5);
         var3.executeUpdate();
         var3.close();
         return "Changed " + var1 + " user's name into " + var2;
      } else {
         return !ServerOptions.instance.getBoolean("Open")
            ? "User \"" + var1 + "\" is not in the whitelist, use /adduser first"
            : "Changed's name " + var1 + " into " + var2;
      }
   }

    std::string addUser(const std::string& var1, const std::string& var2) {
      if (this.containsCaseinsensitiveUser(var1)) {
         return "A user with this name already exists";
      } else {
         try {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
            var3.setString(1, var1);
            var3.setString(2, Core.GameSaveWorld);
    ResultSet var4 = var3.executeQuery();
            if (var4.next()) {
               var3.close();
               return "User " + var1 + " already exist.";
            }

            var3.close();
            var3 = this.conn.prepareStatement("INSERT INTO whitelist (world, username, password, encryptedPwd, pwdEncryptType) VALUES (?, ?, ?, 'true', '2')");
            var3.setString(1, Core.GameSaveWorld);
            var3.setString(2, var1);
            var3.setString(3, var2);
            var3.executeUpdate();
            var3.close();
         } catch (SQLException var5) {
            var5.printStackTrace();
         }

         return "User " + var1 + " created with the password " + var2;
      }
   }

    void updateDisplayName(const std::string& var1, const std::string& var2) {
      try {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
         var3.setString(1, var1);
         var3.setString(2, Core.GameSaveWorld);
    ResultSet var4 = var3.executeQuery();
         if (var4.next()) {
            var3.close();
            var3 = this.conn.prepareStatement("UPDATE whitelist SET displayName = ? WHERE username = ?");
            var3.setString(1, var2);
            var3.setString(2, var1);
            var3.executeUpdate();
            var3.close();
         }

         var3.close();
      } catch (SQLException var5) {
         var5.printStackTrace();
      }
   }

    std::string getDisplayName(const std::string& var1) {
      try {
    PreparedStatement var2 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
         var2.setString(1, var1);
         var2.setString(2, Core.GameSaveWorld);
    ResultSet var3 = var2.executeQuery();
         if (var3.next()) {
    std::string var4 = var3.getString("displayName");
            var2.close();
    return var4;
         }

         var2.close();
      } catch (SQLException var5) {
         var5.printStackTrace();
      }

    return nullptr;
   }

    std::string removeUser(const std::string& var1) {
      try {
    PreparedStatement var2 = this.conn.prepareStatement("DELETE FROM whitelist WHERE world = ? and username = ?");
         var2.setString(1, Core.GameSaveWorld);
         var2.setString(2, var1);
         var2.executeUpdate();
         var2.close();
      } catch (SQLException var3) {
         var3.printStackTrace();
      }

      return "User " + var1 + " removed from white list";
   }

    void removeUserLog(const std::string& var1, const std::string& var2, const std::string& var3) {
      try {
    PreparedStatement var4 = this.conn.prepareStatement("DELETE FROM userlog WHERE username = ? AND type = ? AND text = ?");
         var4.setString(1, var1);
         var4.setString(2, var2);
         var4.setString(3, var3);
         var4.executeUpdate();
         var4.close();
      } catch (SQLException var5) {
         var5.printStackTrace();
      }
   }

    void create() {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "db");
      if (!var1.exists()) {
         var1.mkdirs();
      }

    File var2 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "db" + File.separator + GameServer.ServerName + ".db");
      var2.setReadable(true, false);
      var2.setExecutable(true, false);
      var2.setWritable(true, false);
      DebugLog.log("user database \"" + var2.getPath() + "\"");
      if (!var2.exists()) {
         try {
            var2.createNewFile();
            this.conn = PZSQLUtils.getConnection(var2.getAbsolutePath());
    Statement var3 = this.conn.createStatement();
            var3.executeUpdate(
               "CREATE TABLE [whitelist] ([id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,[world] TEXT DEFAULT '"
                  + GameServer.ServerName
                  + "' NULL,[username] TEXT  NULL,[password] TEXT  NULL, [admin] BOOLEAN DEFAULT false NULL, [moderator] BOOLEAN DEFAULT false NULL, [banned] BOOLEAN DEFAULT false NULL, [priority] BOOLEAN DEFAULT false NULL,  [lastConnection] TEXT NULL)"
            );
            var3.executeUpdate("CREATE UNIQUE INDEX [id] ON [whitelist]([id]  ASC)");
            var3.executeUpdate("CREATE UNIQUE INDEX [username] ON [whitelist]([username]  ASC)");
            var3.executeUpdate("CREATE TABLE [bannedip] ([ip] TEXT NOT NULL,[username] TEXT NULL, [reason] TEXT NULL)");
            var3.close();
         } catch (Exception var12) {
            var12.printStackTrace();
            DebugLog.log("failed to create user database, server shut down");
            System.exit(1);
         }
      }

      if (this.conn == nullptr) {
         try {
            this.conn = PZSQLUtils.getConnection(var2.getAbsolutePath());
         } catch (Exception var11) {
            var11.printStackTrace();
            DebugLog.log("failed to open user database, server shut down");
            System.exit(1);
         }
      }

    DatabaseMetaData var13 = this.conn.getMetaData();
    ResultSet var4 = var13.getColumns(nullptr, nullptr, "whitelist", "admin");
    Statement var5 = this.conn.createStatement();
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'admin' BOOLEAN NULL DEFAULT false");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "moderator");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'moderator' BOOLEAN NULL DEFAULT false");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "banned");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'banned' BOOLEAN NULL DEFAULT false");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "priority");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'priority' BOOLEAN NULL DEFAULT false");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "lastConnection");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'lastConnection' TEXT NULL");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "encryptedPwd");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'encryptedPwd' BOOLEAN NULL DEFAULT false");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "pwdEncryptType");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'pwdEncryptType' INTEGER NULL DEFAULT 1");
      }

      var4.close();
      if (SteamUtils.isSteamModeEnabled()) {
         var4 = var13.getColumns(nullptr, nullptr, "whitelist", "steamid");
         if (!var4.next()) {
            var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'steamid' TEXT NULL");
         }

         var4.close();
         var4 = var13.getColumns(nullptr, nullptr, "whitelist", "ownerid");
         if (!var4.next()) {
            var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'ownerid' TEXT NULL");
         }

         var4.close();
      }

      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "accesslevel");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'accesslevel' TEXT NULL");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "transactionID");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'transactionID' INTEGER NULL");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "displayName");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'whitelist' ADD 'displayName' TEXT NULL");
      }

      var4.close();
      var4 = var5.executeQuery("SELECT * FROM sqlite_master WHERE type = 'index' AND sql LIKE '%UNIQUE%' and name = 'username'");
      if (!var4.next()) {
         try {
            var5.executeUpdate("CREATE UNIQUE INDEX [username] ON [whitelist]([username]  ASC)");
         } catch (Exception var10) {
            System.out.println("Can't create the username index because some of the username in the database are in double, will drop the double username.");
            var5.executeUpdate(
               "DELETE FROM whitelist WHERE whitelist.rowid > (SELECT rowid FROM whitelist dbl WHERE whitelist.rowid <> dbl.rowid AND  whitelist.username = dbl.username);"
            );
            var5.executeUpdate("CREATE UNIQUE INDEX [username] ON [whitelist]([username]  ASC)");
         }
      }

      var4 = var13.getTables(nullptr, nullptr, "bannedip", nullptr);
      if (!var4.next()) {
         var5.executeUpdate("CREATE TABLE [bannedip] ([ip] TEXT NOT NULL,[username] TEXT NULL, [reason] TEXT NULL)");
      }

      var4.close();
      var4 = var13.getTables(nullptr, nullptr, "bannedid", nullptr);
      if (!var4.next()) {
         var5.executeUpdate("CREATE TABLE [bannedid] ([steamid] TEXT NOT NULL, [reason] TEXT NULL)");
      }

      var4.close();
      var4 = var13.getTables(nullptr, nullptr, "userlog", nullptr);
      if (!var4.next()) {
         var5.executeUpdate(
            "CREATE TABLE [userlog] ([id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,[username] TEXT  NULL,[type] TEXT  NULL, [text] TEXT  NULL, [issuedBy] TEXT  NULL, [amount] INTEGER NULL, [lastUpdate] TEXT NULL)"
         );
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "userlog", "lastUpdate");
      if (!var4.next()) {
         var5.executeUpdate("ALTER TABLE 'userlog' ADD 'lastUpdate' TEXT NULL");
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "moderator");
      if (var4.next()) {
      }

      var4.close();
      var4 = var13.getColumns(nullptr, nullptr, "whitelist", "admin");
      if (var4.next()) {
         var4.close();
    PreparedStatement var6 = this.conn.prepareStatement("SELECT * FROM whitelist where admin = 'true'");
    ResultSet var7 = var6.executeQuery();

         while (var7.next()) {
    PreparedStatement var8 = this.conn.prepareStatement("UPDATE whitelist set accesslevel = 'admin' where id = ?");
            var8.setString(1, var7.getString("id"));
            System.out.println(var7.getString("username"));
            var8.executeUpdate();
         }
      }

      var4 = var13.getTables(nullptr, nullptr, "tickets", nullptr);
      if (!var4.next()) {
         var5.executeUpdate(
            "CREATE TABLE [tickets] ([id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL, [message] TEXT NOT NULL, [author] TEXT NOT NULL,[answeredID] INTEGER,[viewed] BOOLEAN NULL DEFAULT false)"
         );
      }

      var4.close();
    PreparedStatement var35 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ?");
      var35.setString(1, this.CommandLineAdminUsername);
      var4 = var35.executeQuery();
      if (!var4.next()) {
         var35.close();
    std::string var37 = this.CommandLineAdminPassword;
         if (var37 == nullptr || var37.empty()) {
    Scanner var39 = std::make_shared<Scanner>(std::make_shared<InputStreamReader>(System.in));
            System.out.println("User 'admin' not found, creating it ");
            System.out.println("Command line admin password: " + this.CommandLineAdminPassword);
            System.out.println("Enter new administrator password: ");

            for (var37 = var39.nextLine(); var37 == nullptr || "" == var37); var37 = var39.nextLine()) {
               System.out.println("Enter new administrator password: ");
            }

            System.out.println("Confirm the password: ");

            for (std::string var9 = var39.nextLine(); var9 == nullptr || "" == var9) || !var37 == var9); var9 = var39.nextLine()) {
               System.out.println("Wrong password, confirm the password: ");
            }
         }

         if (this.doAdmin) {
            var35 = this.conn
               .prepareStatement("INSERT INTO whitelist (username, password, accesslevel, encryptedPwd, pwdEncryptType) VALUES (?, ?, 'admin', 'true', '2')");
         } else {
            var35 = this.conn.prepareStatement("INSERT INTO whitelist (username, password, encryptedPwd, pwdEncryptType) VALUES (?, ?, 'true', '2')");
         }

         var35.setString(1, this.CommandLineAdminUsername);
         var35.setString(2, PZcrypt.hash(encrypt(var37)));
         var35.executeUpdate();
         var35.close();
         System.out.println("Administrator account '" + this.CommandLineAdminUsername + "' created.");
      } else {
         var35.close();
      }

      var5.close();
      if (this.CommandLineAdminPassword != nullptr && !this.CommandLineAdminPassword.empty()) {
    std::string var38 = PZcrypt.hash(encrypt(this.CommandLineAdminPassword));
    PreparedStatement var40 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ?");
         var40.setString(1, this.CommandLineAdminUsername);
         var4 = var40.executeQuery();
         if (var4.next()) {
            var40.close();
            var40 = this.conn.prepareStatement("UPDATE whitelist SET password = ? WHERE username = ?");
            var40.setString(1, var38);
            var40.setString(2, this.CommandLineAdminUsername);
            var40.executeUpdate();
            System.out.println("admin password changed via -adminpassword option");
         } else {
            System.out.println("ERROR: -adminpassword ignored, no '" + this.CommandLineAdminUsername + "' account in db");
         }

         var40.close();
      }
   }

    void close() {
      try {
         if (this.conn != nullptr) {
            this.conn.close();
         }
      } catch (SQLException var2) {
         var2.printStackTrace();
      }
   }

    static bool isValidUserName(const std::string& var0) {
      if (var0 == nullptr
         || var0.trim().empty()
         || var0.contains(";")
         || var0.contains("@")
         || var0.contains("$")
         || var0.contains(",")
         || var0.contains("/")
         || var0.contains(".")
         || var0.contains("'")
         || var0.contains("?")
         || var0.contains("\"")
         || var0.trim().length() < 3
         || var0.length() > 20) {
    return false;
      } else if (var0.contains(nullChar)) {
    return false;
      } else {
         return var0.trim() == "admin") ? true : !var0.trim().toLowerCase().startsWith("admin");
      }
   }

    LogonResult authClient(const std::string& var1, const std::string& var2, const std::string& var3, long var4) {
      System.out.println("User " + var1 + " is trying to connect.");
    LogonResult var6 = std::make_shared<LogonResult>(this);
      if (!ServerOptions.instance.AllowNonAsciiUsername.getValue() && !asciiEncoder.canEncode(var1)) {
         var6.bAuthorized = false;
         var6.dcReason = "NonAsciiCharacters";
    return var6;
      } else if (!isValidUserName(var1)) {
         var6.bAuthorized = false;
         var6.dcReason = "InvalidUsername";
    return var6;
      } else {
         try {
            if (!SteamUtils.isSteamModeEnabled() && !var3 == "127.0.0.1")) {
    PreparedStatement var7 = this.conn.prepareStatement("SELECT * FROM bannedip WHERE ip = ?");
               var7.setString(1, var3);
    ResultSet var8 = var7.executeQuery();
               if (var8.next()) {
                  var6.bAuthorized = false;
                  var6.bannedReason = var8.getString("reason");
                  var6.banned = true;
                  var7.close();
    return var6;
               }

               var7.close();
            }

            if (isNullOrEmpty(var2) && ServerOptions.instance.Open.getValue() && ServerOptions.instance.AutoCreateUserInWhiteList.getValue()) {
               var6.dcReason = "UserPasswordRequired";
               var6.bAuthorized = false;
    return var6;
            }

    PreparedStatement var13 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE LOWER(username) = LOWER(?) AND world = ?");
            var13.setString(1, var1);
            var13.setString(2, Core.GameSaveWorld);
    ResultSet var14 = var13.executeQuery();
            if (var14.next()) {
               if (!isNullOrEmpty(var14.getString("password"))
                  && (var14.getString("encryptedPwd") == "false") || var14.getString("encryptedPwd") == "N"))) {
    std::string var9 = var14.getString("password");
    std::string var10 = encrypt(var9);
    PreparedStatement var11 = this.conn.prepareStatement("UPDATE whitelist SET encryptedPwd = 'true' WHERE username = ? and password = ?");
                  var11.setString(1, var1);
                  var11.setString(2, var9);
                  var11.executeUpdate();
                  var11.close();
                  var11 = this.conn.prepareStatement("UPDATE whitelist SET password = ? WHERE username = ? AND password = ?");
                  var11.setString(1, var10);
                  var11.setString(2, var1);
                  var11.setString(3, var9);
                  var11.executeUpdate();
                  var11.close();
                  var14 = var13.executeQuery();
               }

               if (!isNullOrEmpty(var14.getString("password")) && var14.getInt("pwdEncryptType") == 1) {
    std::string var15 = var14.getString("password");
    std::string var16 = PZcrypt.hash(var15);
                  PreparedStatement var18 = this.conn
                     .prepareStatement("UPDATE whitelist SET pwdEncryptType = '2', password = ? WHERE username = ? AND password = ?");
                  var18.setString(1, var16);
                  var18.setString(2, var1);
                  var18.setString(3, var15);
                  var18.executeUpdate();
                  var18.close();
                  var14 = var13.executeQuery();
               }

               if (!isNullOrEmpty(var14.getString("password")) && !var14.getString("password") == var2)) {
                  var6.bAuthorized = false;
                  var13.close();
                  if (isNullOrEmpty(var2)) {
                     var6.dcReason = "DuplicateAccount";
                  } else {
                     var6.dcReason = "InvalidUsernamePassword";
                  }

    return var6;
               }

               var6.bAuthorized = true;
               var6.admin = "true" == var14.getString("admin")) || "Y" == var14.getString("admin"));
               var6.accessLevel = var14.getString("accesslevel");
               if (var6.accessLevel == nullptr) {
                  var6.accessLevel = "";
                  if (var6.admin) {
                     var6.accessLevel = "admin";
                  }

                  this.setAccessLevel(var1, var6.accessLevel);
               }

               var6.banned = "true" == var14.getString("banned")) || "Y" == var14.getString("banned"));
               if (var6.banned) {
                  var6.bAuthorized = false;
               }

               if (var14.getString("transactionID") == nullptr) {
                  var6.transactionID = 0;
               } else {
                  var6.transactionID = int.parseInt(var14.getString("transactionID"));
               }

               var6.priority = var14.getString("priority") == "true");
               var13.close();
    return var6;
            }

            if (ServerOptions.instance.Open.getValue()) {
               if (!this.isNewAccountAllowed(var3, var4)) {
                  var13.close();
                  var6.bAuthorized = false;
                  var6.dcReason = "MaxAccountsReached";
    return var6;
               }

               var6.bAuthorized = true;
               var6.newUser = true;
               var13.close();
    return var6;
            }

            var6.bAuthorized = false;
            var6.dcReason = "UnknownUsername";
            var13.close();
         } catch (Exception var12) {
            var12.printStackTrace();
         }

    return var6;
      }
   }

    LogonResult authClient(long var1) {
    std::string var3 = SteamUtils.convertSteamIDToString(var1);
      System.out.println("Steam client " + var3 + " is initiating a connection.");
    LogonResult var4 = std::make_shared<LogonResult>(this);

      try {
    PreparedStatement var5 = this.conn.prepareStatement("SELECT * FROM bannedid WHERE steamid = ?");
         var5.setString(1, var3);
    ResultSet var6 = var5.executeQuery();
         if (var6.next()) {
            var4.bAuthorized = false;
            var4.bannedReason = var6.getString("reason");
            var4.banned = true;
            var5.close();
    return var4;
         }

         var5.close();
         var4.bAuthorized = true;
      } catch (Exception var7) {
         var7.printStackTrace();
      }

    return var4;
   }

    LogonResult authOwner(long var1, long var3) {
    std::string var5 = SteamUtils.convertSteamIDToString(var1);
    std::string var6 = SteamUtils.convertSteamIDToString(var3);
      System.out.println("Steam client " + var5 + " borrowed the game from " + var6);
    LogonResult var7 = std::make_shared<LogonResult>(this);

      try {
    PreparedStatement var8 = this.conn.prepareStatement("SELECT * FROM bannedid WHERE steamid = ?");
         var8.setString(1, var6);
    ResultSet var9 = var8.executeQuery();
         if (var9.next()) {
            var7.bAuthorized = false;
            var7.bannedReason = var9.getString("reason");
            var7.banned = true;
            var8.close();
    return var7;
         }

         var8.close();
         var7.bAuthorized = true;
         var8 = this.conn.prepareStatement("UPDATE whitelist SET ownerid = ? where steamid = ?");
         var8.setString(1, var6);
         var8.setString(2, var5);
         var8.executeUpdate();
         var8.close();
      } catch (Exception var10) {
         var10.printStackTrace();
      }

    return var7;
   }

    bool isNewAccountAllowed(const std::string& var1, long var2) {
    int var4 = ServerOptions.instance.MaxAccountsPerUser.getValue();
      if (var4 <= 0) {
    return true;
      } else if (!SteamUtils.isSteamModeEnabled()) {
    return true;
      } else {
    std::string var5 = SteamUtils.convertSteamIDToString(var2);
    int var6 = 0;

         try (PreparedStatement var7 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE steamid = ? AND ((accessLevel = ?) OR (accessLevel is NULL))")) {
            var7.setString(1, var5);
            var7.setString(2, "");
    ResultSet var8 = var7.executeQuery();

            while (var8.next()) {
               var6++;
            }
         } catch (Exception var12) {
            DebugLog.Multiplayer.printException(var12, "Query execution failed", LogSeverity.Error);
    return true;
         }

         DebugLog.Multiplayer.debugln("IsNewAccountAllowed: steam-id=%d count=%d/%d", var2, var6, var4);
         return var6 < var4;
      }
   }

    static std::string encrypt(const std::string& var0) {
      if (isNullOrEmpty(var0)) {
         return "";
      } else {
         byte[] var1 = nullptr;

         try {
            var1 = MessageDigest.getInstance("MD5").digest(var0.getBytes());
         } catch (NoSuchAlgorithmException var5) {
            System.out.println("Can't encrypt password");
            var5.printStackTrace();
         }

    std::stringstream var2 = new std::stringstream();

         for (int var3 = 0; var3 < var1.length; var3++) {
    std::string var4 = int.toHexString(var1[var3]);
            if (var4.length() == 1) {
               var2.append('0');
               var2.append(var4.charAt(var4.length() - 1));
            } else {
               var2.append(var4.substr(var4.length() - 2));
            }
         }

         return var2;
      }
   }

    std::string changePwd(const std::string& var1, const std::string& var2, const std::string& var3) {
    PreparedStatement var5 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND password = ? AND world = ?");
      var5.setString(1, var1);
      var5.setString(2, var2);
      var5.setString(3, Core.GameSaveWorld);
    ResultSet var6 = var5.executeQuery();
      if (var6.next()) {
         var5.close();
         var5 = this.conn.prepareStatement("UPDATE whitelist SET pwdEncryptType = '2', password = ? WHERE username = ? and password = ?");
         var5.setString(1, var3);
         var5.setString(2, var1);
         var5.setString(3, var2);
         var5.executeUpdate();
         var5.close();
         return "Your new password is " + var3;
      } else {
         var5.close();
         return "Wrong password for user " + var1;
      }
   }

    std::string grantAdmin(const std::string& var1, bool var2) {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
      var3.setString(1, var1);
      var3.setString(2, Core.GameSaveWorld);
    ResultSet var4 = var3.executeQuery();
      if (var4.next()) {
         var3.close();
         var3 = this.conn.prepareStatement("UPDATE whitelist SET admin = ? WHERE username = ?");
         var3.setString(1, var2 ? "true" : "false");
         var3.setString(2, var1);
         var3.executeUpdate();
         var3.close();
         return var2 ? "User " + var1 + " is now admin" : "User " + var1 + " is no longer admin";
      } else {
         var3.close();
         return "User \"" + var1 + "\" is not in the whitelist, use /adduser first";
      }
   }

    std::string setAccessLevel(const std::string& var1, const std::string& var2) {
      var2 = var2.trim();
      if (!this.containsUser(var1)) {
         this.addUser(var1, "");
      }

    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
      var3.setString(1, var1);
      var3.setString(2, Core.GameSaveWorld);
    ResultSet var4 = var3.executeQuery();
      if (var4.next()) {
         var3.close();
         var3 = this.conn.prepareStatement("UPDATE whitelist SET accesslevel = ? WHERE username = ?");
         var3.setString(1, var2);
         var3.setString(2, var1);
         var3.executeUpdate();
         var3.close();
         return var2 == "") ? "User " + var1 + " no longer has access level" : "User " + var1 + " is now " + var2;
      } else {
         var3.close();
         return "User \"" + var1 + "\" is not in the whitelist, use /adduser first";
      }
   }

   public std::vector<Userlog> getUserlog(std::string var1) {
    std::vector var2 = new std::vector();

      try {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM userlog WHERE username = ?");
         var3.setString(1, var1);
    ResultSet var4 = var3.executeQuery();

         while (var4.next()) {
            var2.push_back(
               std::make_shared<Userlog>(
                  var1, var4.getString("type"), var4.getString("text"), var4.getString("issuedBy"), var4.getInt("amount"), var4.getString("lastUpdate")
               )
            );
         }

         var3.close();
      } catch (SQLException var5) {
         var5.printStackTrace();
      }

    return var2;
   }

    void addUserlog(const std::string& var1, UserlogType var2, const std::string& var3, const std::string& var4, int var5) {
      try {
    bool var6 = true;
    std::string var7 = dateFormat.format(Calendar.getInstance().getTime());
         if (var2 != UserlogType.LuaChecksum && var2 != UserlogType.DupeItem) {
            if (var2 == UserlogType.Kicked || var2 == UserlogType.Banned || var2 == UserlogType.SuspiciousActivity || var2 == UserlogType.UnauthorizedPacket) {
    PreparedStatement var12 = this.conn.prepareStatement("SELECT * FROM userlog WHERE username = ? AND type = ? AND text = ? AND issuedBy = ?");
               var12.setString(1, var1);
               var12.setString(2, var2);
               var12.setString(3, var3);
               var12.setString(4, var4);
    ResultSet var14 = var12.executeQuery();
               if (var14.next()) {
                  var6 = false;
                  var5 = int.parseInt(var14.getString("amount")) + 1;
                  var12.close();
                  PreparedStatement var15 = this.conn
                     .prepareStatement("UPDATE userlog set amount = ?, lastUpdate = ? WHERE username = ? AND type = ? AND text = ? AND issuedBy = ?");
                  var15.setString(1, std::string.valueOf(var5));
                  var15.setString(2, var7);
                  var15.setString(3, var1);
                  var15.setString(4, var2);
                  var15.setString(5, var3);
                  var15.setString(6, var4);
                  var15.executeUpdate();
                  var15.close();
               }
            }
         } else {
    PreparedStatement var8 = this.conn.prepareStatement("SELECT * FROM userlog WHERE username = ? AND type = ?");
            var8.setString(1, var1);
            var8.setString(2, var2);
    ResultSet var9 = var8.executeQuery();
            if (var9.next()) {
               var6 = false;
               var5 = int.parseInt(var9.getString("amount")) + 1;
               var8.close();
    PreparedStatement var10 = this.conn.prepareStatement("UPDATE userlog set amount = ?, lastUpdate = ?, text = ? WHERE username = ? AND type = ?");
               var10.setString(1, std::string.valueOf(var5));
               var10.setString(2, var7);
               var10.setString(3, var3);
               var10.setString(4, var1);
               var10.setString(5, var2);
               var10.executeUpdate();
               var10.close();
            }
         }

         if (var6) {
            PreparedStatement var13 = this.conn
               .prepareStatement("INSERT INTO userlog (username, type, text, issuedBy, amount, lastUpdate) VALUES (?, ?, ?, ?, ?, ?)");
            var13.setString(1, var1);
            var13.setString(2, var2);
            var13.setString(3, var3);
            var13.setString(4, var4);
            var13.setString(5, std::string.valueOf(var5));
            var13.setString(6, var7);
            var13.executeUpdate();
            var13.close();
         }
      } catch (Exception var11) {
         var11.printStackTrace();
      }
   }

    std::string banUser(const std::string& var1, bool var2) {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
      var3.setString(1, var1);
      var3.setString(2, Core.GameSaveWorld);
    ResultSet var4 = var3.executeQuery();
    bool var5 = var4.next();
      if (var2 && !var5) {
    PreparedStatement var6 = this.conn.prepareStatement("INSERT INTO whitelist (world, username, password, encryptedPwd) VALUES (?, ?, 'bogus', 'false')");
         var6.setString(1, Core.GameSaveWorld);
         var6.setString(2, var1);
         var6.executeUpdate();
         var6.close();
         var4 = var3.executeQuery();
         var5 = true;
      }

      if (var5) {
    std::string var12 = "true";
         if (!var2) {
            var12 = "false";
         }

         var3.close();
         var3 = this.conn.prepareStatement("UPDATE whitelist SET banned = ? WHERE username = ?");
         var3.setString(1, var12);
         var3.setString(2, var1);
         var3.executeUpdate();
         var3.close();
         if (SteamUtils.isSteamModeEnabled()) {
            var3 = this.conn.prepareStatement("SELECT steamid FROM whitelist WHERE username = ? AND world = ?");
            var3.setString(1, var1);
            var3.setString(2, Core.GameSaveWorld);
            var4 = var3.executeQuery();
            if (var4.next()) {
    std::string var7 = var4.getString("steamid");
               var3.close();
               if (var7 != nullptr && !var7.empty()) {
                  this.banSteamID(var7, "", var2);
               }
            } else {
               var3.close();
            }
         }

         return var2 ? "User " + var1 + " is now banned" : "User " + var1 + " is now un-banned";
      } else {
         var3.close();
         return "User \"" + var1 + "\" is not in the whitelist, use /adduser first";
      }
   }

    std::string banIp(const std::string& var1, const std::string& var2, const std::string& var3, bool var4) {
      if (var4) {
    PreparedStatement var5 = this.conn.prepareStatement("INSERT INTO bannedip (ip, username, reason) VALUES (?, ?, ?)");
         var5.setString(1, var1);
         var5.setString(2, var2);
         var5.setString(3, var3);
         var5.executeUpdate();
         var5.close();
      } else {
         if (var1 != nullptr) {
    PreparedStatement var6 = this.conn.prepareStatement("DELETE FROM bannedip WHERE ip = ?");
            var6.setString(1, var1);
            var6.executeUpdate();
            var6.close();
         }

    PreparedStatement var7 = this.conn.prepareStatement("DELETE FROM bannedip WHERE username = ?");
         var7.setString(1, var2);
         var7.executeUpdate();
         var7.close();
      }

      return "";
   }

    std::string banSteamID(const std::string& var1, const std::string& var2, bool var3) {
      if (var3) {
    PreparedStatement var4 = this.conn.prepareStatement("INSERT INTO bannedid (steamid, reason) VALUES (?, ?)");
         var4.setString(1, var1);
         var4.setString(2, var2);
         var4.executeUpdate();
         var4.close();
      } else {
    PreparedStatement var5 = this.conn.prepareStatement("DELETE FROM bannedid WHERE steamid = ?");
         var5.setString(1, var1);
         var5.executeUpdate();
         var5.close();
      }

      return "";
   }

    std::string setUserSteamID(const std::string& var1, const std::string& var2) {
      try {
    PreparedStatement var3 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ?");
         var3.setString(1, var1);
    ResultSet var4 = var3.executeQuery();
         if (!var4.next()) {
            var3.close();
            return "User " + var1 + " not found";
         }

         var3.close();
         var3 = this.conn.prepareStatement("UPDATE whitelist SET steamid = ? WHERE username = ?");
         var3.setString(1, var2);
         var3.setString(2, var1);
         var3.executeUpdate();
         var3.close();
      } catch (SQLException var5) {
         var5.printStackTrace();
      }

      return "User " + var1 + " SteamID set to " + var2;
   }

    void setPassword(const std::string& var1, const std::string& var2) {
      try {
    PreparedStatement var3 = this.conn.prepareStatement("UPDATE whitelist SET pwdEncryptType = '2', password = ? WHERE username = ? and world = ?");
         var3.setString(1, var2);
         var3.setString(2, var1);
         var3.setString(3, Core.GameSaveWorld);
         var3.executeUpdate();
         var3.close();
      } catch (SQLException var4) {
         var4.printStackTrace();
      }
   }

    void updateLastConnectionDate(const std::string& var1, const std::string& var2) {
      try {
    PreparedStatement var3 = this.conn.prepareStatement("UPDATE whitelist SET lastConnection = ? WHERE username = ? AND password = ?");
         var3.setString(1, dateFormat.format(Calendar.getInstance().getTime()));
         var3.setString(2, var1);
         var3.setString(3, var2);
         var3.executeUpdate();
         var3.close();
      } catch (SQLException var4) {
         var4.printStackTrace();
      }
   }

    static bool isNullOrEmpty(const std::string& var0) {
    return var0 = = nullptr || var0.empty();
   }

    std::string addWarningPoint(const std::string& var1, const std::string& var2, int var3, const std::string& var4) {
    PreparedStatement var5 = this.conn.prepareStatement("SELECT * FROM whitelist WHERE username = ? AND world = ?");
      var5.setString(1, var1);
      var5.setString(2, Core.GameSaveWorld);
    ResultSet var6 = var5.executeQuery();
      if (var6.next()) {
         this.addUserlog(var1, UserlogType.WarningPoint, var2, var4, var3);
         return "Added a warning point on " + var1 + " reason: " + var2;
      } else {
         return "User " + var1 + " doesn't exist.";
      }
   }

    void addTicket(const std::string& var1, const std::string& var2, int var3) {
      if (var3 > -1) {
    PreparedStatement var4 = this.conn.prepareStatement("INSERT INTO tickets (author, message, answeredID) VALUES (?, ?, ?)");
         var4.setString(1, var1);
         var4.setString(2, var2);
         var4.setInt(3, var3);
         var4.executeUpdate();
         var4.close();
      } else {
    PreparedStatement var5 = this.conn.prepareStatement("INSERT INTO tickets (author, message) VALUES (?, ?)");
         var5.setString(1, var1);
         var5.setString(2, var2);
         var5.executeUpdate();
         var5.close();
      }
   }

   public std::vector<DBTicket> getTickets(std::string var1) throws SQLException {
    std::vector var2 = new std::vector();
    PreparedStatement var3 = nullptr;
      if (var1 != nullptr) {
         var3 = this.conn.prepareStatement("SELECT * FROM tickets WHERE author = ? and answeredID is nullptr");
         var3.setString(1, var1);
      } else {
         var3 = this.conn.prepareStatement("SELECT * FROM tickets where answeredID is nullptr");
      }

    ResultSet var4 = var3.executeQuery();

      while (var4.next()) {
    DBTicket var5 = std::make_shared<DBTicket>(var4.getString("author"), var4.getString("message"), var4.getInt("id"));
         var2.push_back(var5);
    DBTicket var6 = this.getAnswer(var5.getTicketID());
         if (var6 != nullptr) {
            var5.setAnswer(var6);
         }
      }

    return var2;
   }

    DBTicket getAnswer(int var1) {
    PreparedStatement var2 = nullptr;
      var2 = this.conn.prepareStatement("SELECT * FROM tickets WHERE answeredID = ?");
      var2.setInt(1, var1);
    ResultSet var3 = var2.executeQuery();
      return var3.next() ? std::make_shared<DBTicket>(var3.getString("author"), var3.getString("message"), var3.getInt("id")) : nullptr;
   }

    void removeTicket(int var1) {
    DBTicket var2 = this.getAnswer(var1);
      if (var2 != nullptr) {
    PreparedStatement var3 = this.conn.prepareStatement("DELETE FROM tickets WHERE id = ?");
         var3.setInt(1, var2.getTicketID());
         var3.executeUpdate();
         var3.close();
      }

    PreparedStatement var4 = this.conn.prepareStatement("DELETE FROM tickets WHERE id = ?");
      var4.setInt(1, var1);
      var4.executeUpdate();
      var4.close();
   }
}
} // namespace network
} // namespace zombie
