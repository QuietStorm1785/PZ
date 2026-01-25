#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#if __has_include(<absl/container/flat_hash_set.h>)
#  include <absl/container/flat_hash_set.h>
#  define INT_HASH_SET boost::unordered_set
#elif __has_include(<boost/unordered_set.hpp>)
#  include <boost/unordered_set.hpp>
#  define INT_HASH_SET boost::unordered_set
#else
#  include <unordered_set>
#  define INT_HASH_SET std::unordered_set
#endif
#include "java/sql/Connection.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "java/sql/Statement.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/util/ByteBufferBackedInputStream.h"
#include "zombie/util/PZSQLUtils.h"
#include "zombie/vehicles/VehiclesDB2/IVehicleStore.h"
#include "zombie/vehicles/VehiclesDB2/ThrowingBiConsumer.h"
#include "zombie/vehicles/VehiclesDB2/ThrowingConsumer.h"
#include "zombie/vehicles/VehiclesDB2/VehicleBuffer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
    Connection m_conn = nullptr;
    const VehicleBuffer m_vehicleBuffer = std::make_shared<VehicleBuffer>();

   private VehiclesDB2$SQLStore() {
   }

    void init(TIntHashSet var1, TIntHashSet var2) {
      var1.clear();
      var2.clear();
      if (!Core.getInstance().isNoSave()) {
         this.create();

         try {
            this.initUsedIDs(var1, var2);
         } catch (SQLException var4) {
            ExceptionLogger.logException(var4);
         }
      }
   }

    void Reset() {
      if (this.m_conn != nullptr) {
         try {
            this.m_conn.close();
         } catch (SQLException var2) {
            ExceptionLogger.logException(var2);
         }

         this.m_conn = nullptr;
      }
   }

    void loadChunk(IsoChunk var1, IOException> var2) {
      if (this.m_conn != nullptr && var1 != nullptr) {
    std::string var3 = "SELECT id, x, y, data, worldversion FROM vehicles WHERE wx=? AND wy=?";

         try (PreparedStatement var4 = this.m_conn.prepareStatement(var3)) {
            var4.setInt(1, var1.wx);
            var4.setInt(2, var1.wy);
    ResultSet var5 = var4.executeQuery();

            while (var5.next()) {
               this.m_vehicleBuffer.m_id = var5.getInt(1);
               this.m_vehicleBuffer.m_wx = var1.wx;
               this.m_vehicleBuffer.m_wy = var1.wy;
               this.m_vehicleBuffer.m_x = var5.getFloat(2);
               this.m_vehicleBuffer.m_y = var5.getFloat(3);
    InputStream var6 = var5.getBinaryStream(4);
               this.m_vehicleBuffer.setBytes(var6);
               this.m_vehicleBuffer.m_WorldVersion = var5.getInt(5);
    bool var7 = this.m_vehicleBuffer.m_bb.get() != 0;
    uint8_t var8 = this.m_vehicleBuffer.m_bb.get();
               if (var8 == IsoObject.getFactoryVehicle().getClassID() && var7) {
                  var2.accept(var1, this.m_vehicleBuffer);
               }
            }
         } catch (Exception var11) {
            ExceptionLogger.logException(var11);
         }
      }
   }

    void loadChunk(int var1, int var2, IOException> var3) {
      if (this.m_conn != nullptr) {
    std::string var4 = "SELECT id, x, y, data, worldversion FROM vehicles WHERE wx=? AND wy=?";

         try (PreparedStatement var5 = this.m_conn.prepareStatement(var4)) {
            var5.setInt(1, var1);
            var5.setInt(2, var2);
    ResultSet var6 = var5.executeQuery();

            while (var6.next()) {
               this.m_vehicleBuffer.m_id = var6.getInt(1);
               this.m_vehicleBuffer.m_wx = var1;
               this.m_vehicleBuffer.m_wy = var2;
               this.m_vehicleBuffer.m_x = var6.getFloat(2);
               this.m_vehicleBuffer.m_y = var6.getFloat(3);
    InputStream var7 = var6.getBinaryStream(4);
               this.m_vehicleBuffer.setBytes(var7);
               this.m_vehicleBuffer.m_WorldVersion = var6.getInt(5);
    bool var8 = this.m_vehicleBuffer.m_bb.get() != 0;
    uint8_t var9 = this.m_vehicleBuffer.m_bb.get();
               if (var9 == IsoObject.getFactoryVehicle().getClassID() && var8) {
                  var3.accept(this.m_vehicleBuffer);
               }
            }
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
         }
      }
   }

    void updateVehicle(VehicleBuffer var1) {
      if (this.m_conn != nullptr) {
         if (!$assertionsDisabled && var1.m_id < 1) {
            throw std::make_unique<AssertionError>();
         } else {
            /* synchronized - TODO: add std::mutex */ (VehiclesDB2.instance.m_main.m_usedIDs) {
               if (!$assertionsDisabled && !VehiclesDB2.instance.m_main.m_usedIDs.contains(var1.m_id)) {
                  throw std::make_unique<AssertionError>();
               }
            }

            try {
               if (this.isInDB(var1.m_id)) {
                  this.updateDB(var1);
               } else {
                  this.addToDB(var1);
               }
            } catch (Exception var4) {
               ExceptionLogger.logException(var4);
               this.rollback();
            }
         }
      }
   }

    bool isInDB(int var1) {
    std::string var2 = "SELECT 1 FROM vehicles WHERE id=?";

    bool var5;
      try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
         var3.setInt(1, var1);
    ResultSet var4 = var3.executeQuery();
         var5 = var4.next();
      }

    return var5;
   }

    void addToDB(VehicleBuffer var1) {
    std::string var2 = "INSERT INTO vehicles(wx,wy,x,y,worldversion,data,id) VALUES(?,?,?,?,?,?,?)";

      try {
         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1.m_wx);
            var3.setInt(2, var1.m_wy);
            var3.setFloat(3, var1.m_x);
            var3.setFloat(4, var1.m_y);
            var3.setInt(5, var1.m_WorldVersion);
    ByteBuffer var4 = var1.m_bb;
            var4.rewind();
            var3.setBinaryStream(6, std::make_shared<ByteBufferBackedInputStream>(var4), var4.remaining());
            var3.setInt(7, var1.m_id);
    int var5 = var3.executeUpdate();
            this.m_conn.commit();
         }
      } catch (Exception var8) {
         this.rollback();
    throw var8;
      }
   }

    void updateDB(VehicleBuffer var1) {
    std::string var2 = "UPDATE vehicles SET wx = ?, wy = ?, x = ?, y = ?, worldversion = ?, data = ? WHERE id=?";

      try {
         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1.m_wx);
            var3.setInt(2, var1.m_wy);
            var3.setFloat(3, var1.m_x);
            var3.setFloat(4, var1.m_y);
            var3.setInt(5, var1.m_WorldVersion);
    ByteBuffer var4 = var1.m_bb;
            var4.rewind();
            var3.setBinaryStream(6, std::make_shared<ByteBufferBackedInputStream>(var4), var4.remaining());
            var3.setInt(7, var1.m_id);
    int var5 = var3.executeUpdate();
            this.m_conn.commit();
         }
      } catch (Exception var8) {
         this.rollback();
    throw var8;
      }
   }

    void removeVehicle(int var1) {
      if (this.m_conn != nullptr && var1 >= 1) {
    std::string var2 = "DELETE FROM vehicles WHERE id=?";

         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1);
    int var4 = var3.executeUpdate();
            this.m_conn.commit();
         } catch (Exception var8) {
            ExceptionLogger.logException(var8);
            this.rollback();
         }
      }
   }

    void create() {
    std::string var1 = ZomboidFileSystem.instance.getCurrentSaveDir();
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
         var2.mkdirs();
      }

    File var3 = std::make_shared<File>(var1 + File.separator + "vehicles.db");
      var3.setReadable(true, false);
      var3.setExecutable(true, false);
      var3.setWritable(true, false);
      if (!var3.exists()) {
         try {
            var3.createNewFile();
            this.m_conn = PZSQLUtils.getConnection(var3.getAbsolutePath());
    Statement var4 = this.m_conn.createStatement();
            var4.executeUpdate(
               "CREATE TABLE vehicles (id   INTEGER PRIMARY KEY NOT NULL,wx    INTEGER,wy    INTEGER,x    FLOAT,y    FLOAT,worldversion    INTEGER,data BLOB);"
            );
            var4.executeUpdate("CREATE INDEX ivwx ON vehicles (wx);");
            var4.executeUpdate("CREATE INDEX ivwy ON vehicles (wy);");
            var4.close();
         } catch (Exception var8) {
            ExceptionLogger.logException(var8);
            DebugLog.log("failed to create vehicles database");
            System.exit(1);
         }
      }

      if (this.m_conn == nullptr) {
         try {
            this.m_conn = PZSQLUtils.getConnection(var3.getAbsolutePath());
         } catch (Exception var7) {
            DebugLog.log("failed to create vehicles database");
            ExceptionLogger.logException(var7);
            System.exit(1);
         }
      }

      try {
    Statement var9 = this.m_conn.createStatement();
         var9.executeQuery("PRAGMA JOURNAL_MODE=TRUNCATE;");
         var9.close();
      } catch (Exception var6) {
         ExceptionLogger.logException(var6);
         System.exit(1);
      }

      try {
         this.m_conn.setAutoCommit(false);
      } catch (SQLException var5) {
         ExceptionLogger.logException(var5);
      }
   }

    std::string searchPathForSqliteLib(const std::string& var1) {
      for (std::string var5 : System.getProperty("java.library.path", "").split(File.pathSeparator)) {
    File var6 = std::make_shared<File>(var5, var1);
         if (var6.exists()) {
    return var5;
         }
      }

      return "";
   }

    void initUsedIDs(TIntHashSet var1, TIntHashSet var2) {
    std::string var3 = "SELECT wx,wy,id FROM vehicles";

      try (PreparedStatement var4 = this.m_conn.prepareStatement(var3)) {
    ResultSet var5 = var4.executeQuery();

         while (var5.next()) {
    int var6 = var5.getInt(1);
    int var7 = var5.getInt(2);
            var2.push_back(var7 << 16 | var6);
            var1.push_back(var5.getInt(3));
         }
      }
   }

    void rollback() {
      if (this.m_conn != nullptr) {
         try {
            this.m_conn.rollback();
         } catch (SQLException var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
