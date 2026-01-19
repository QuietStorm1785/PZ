package zombie.util;

import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import zombie.core.logger.ExceptionLogger;

public class PZSQLUtils {
   public static void init() {
      try {
         Class.forName("org.sqlite.JDBC");
      } catch (ClassNotFoundException var1) {
         ExceptionLogger.logException(var1);
         System.exit(1);
      }

      setupSqliteVariables();
   }

   private static void setupSqliteVariables() {
      if (!System.getProperty("os.name").contains("OS X")) {
         if (System.getProperty("os.name").startsWith("Win")) {
            if (System.getProperty("sun.arch.data.model").equals("64")) {
               System.setProperty("org.sqlite.lib.path", searchPathForSqliteLib("sqlitejdbc64.dll"));
               System.setProperty("org.sqlite.lib.name", "sqlitejdbc64.dll");
            }
         } else if (System.getProperty("sun.arch.data.model").equals("64")) {
         }
      }
   }

   private static String searchPathForSqliteLib(String var0) {
      for (String var4 : System.getProperty("java.library.path", "").split(File.pathSeparator)) {
         File var5 = new File(var4, var0);
         if (var5.exists()) {
            return var4;
         }
      }

      return "";
   }

   public static Connection getConnection(String var0) throws SQLException {
      return DriverManager.getConnection("jdbc:sqlite:" + var0);
   }
}
