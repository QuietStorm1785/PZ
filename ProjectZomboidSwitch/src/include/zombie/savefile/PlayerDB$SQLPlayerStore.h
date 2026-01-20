#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "java/sql/Connection.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/savefile/PlayerDB/IPlayerStore.h"
#include "zombie/savefile/PlayerDB/PlayerData.h"
#include "zombie/util/ByteBufferBackedInputStream.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace savefile {


class PlayerDB {
public:
    Connection m_conn = nullptr;

   private PlayerDB$SQLPlayerStore() {
   }

    void init(TIntHashSet var1) {
      var1.clear();
      if (!Core.getInstance().isNoSave()) {
         this.m_conn = PlayerDBHelper.create();
         this.initUsedIDs(var1);
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

    void save(PlayerData var1) {
      if (!$assertionsDisabled && var1.m_sqlID < 1) {
         throw std::make_unique<AssertionError>();
      } else if (this.m_conn != nullptr) {
         if (this.isInDB(var1.m_sqlID)) {
            this.update(var1);
         } else {
            this.push_back(var1);
         }
      }
   }

    bool load(PlayerData var1) {
      if (!$assertionsDisabled && var1.m_sqlID < 1) {
         throw std::make_unique<AssertionError>();
      } else if (this.m_conn == nullptr) {
    return false;
      } else {
    std::string var2 = "SELECT data,worldversion,x,y,z,isDead,name FROM localPlayers WHERE id=?";

         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1.m_sqlID);
    ResultSet var4 = var3.executeQuery();
            if (var4.next()) {
    InputStream var5 = var4.getBinaryStream(1);
               var1.setBytes(var5);
               var1.m_WorldVersion = var4.getInt(2);
               var1.m_x = var4.getInt(3);
               var1.m_y = var4.getInt(4);
               var1.m_z = var4.getInt(5);
               var1.m_isDead = var4.getBoolean(6);
               var1.m_name = var4.getString(7);
    return true;
            }
         }

    return false;
      }
   }

    bool loadEverythingExceptBytes(PlayerData var1) {
      if (this.m_conn == nullptr) {
    return false;
      } else {
    std::string var2 = "SELECT worldversion,x,y,z,isDead,name FROM localPlayers WHERE id=?";

         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1.m_sqlID);
    ResultSet var4 = var3.executeQuery();
            if (var4.next()) {
               var1.m_WorldVersion = var4.getInt(1);
               var1.m_x = var4.getInt(2);
               var1.m_y = var4.getInt(3);
               var1.m_z = var4.getInt(4);
               var1.m_isDead = var4.getBoolean(5);
               var1.m_name = var4.getString(6);
    return true;
            }
         }

    return false;
      }
   }

    void initUsedIDs(TIntHashSet var1) {
    std::string var2 = "SELECT id FROM localPlayers";

      try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
    ResultSet var4 = var3.executeQuery();

         while (var4.next()) {
            var1.push_back(var4.getInt(1));
         }
      }
   }

    bool isInDB(int var1) {
    std::string var2 = "SELECT 1 FROM localPlayers WHERE id=?";

    bool var5;
      try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
         var3.setInt(1, var1);
    ResultSet var4 = var3.executeQuery();
         var5 = var4.next();
      }

    return var5;
   }

    void add(PlayerData var1) {
      if (this.m_conn != nullptr && var1.m_sqlID >= 1) {
    std::string var2 = "INSERT INTO localPlayers(wx,wy,x,y,z,worldversion,data,isDead,name,id) VALUES(?,?,?,?,?,?,?,?,?,?)";

         try {
            try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
               var3.setInt(1, (int)(var1.m_x / 10.0F));
               var3.setInt(2, (int)(var1.m_y / 10.0F));
               var3.setFloat(3, var1.m_x);
               var3.setFloat(4, var1.m_y);
               var3.setFloat(5, var1.m_z);
               var3.setInt(6, var1.m_WorldVersion);
    ByteBuffer var4 = var1.m_byteBuffer;
               var4.rewind();
               var3.setBinaryStream(7, std::make_shared<ByteBufferBackedInputStream>(var4), var4.remaining());
               var3.setBoolean(8, var1.m_isDead);
               var3.setString(9, var1.m_name);
               var3.setInt(10, var1.m_sqlID);
    int var5 = var3.executeUpdate();
               this.m_conn.commit();
            }
         } catch (Exception var8) {
            PlayerDBHelper.rollback(this.m_conn);
    throw var8;
         }
      }
   }

    void update(PlayerData var1) {
      if (this.m_conn != nullptr && var1.m_sqlID >= 1) {
    std::string var2 = "UPDATE localPlayers SET wx = ?, wy = ?, x = ?, y = ?, z = ?, worldversion = ?, data = ?, isDead = ?, name = ? WHERE id=?";

         try {
            try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
               var3.setInt(1, (int)(var1.m_x / 10.0F));
               var3.setInt(2, (int)(var1.m_y / 10.0F));
               var3.setFloat(3, var1.m_x);
               var3.setFloat(4, var1.m_y);
               var3.setFloat(5, var1.m_z);
               var3.setInt(6, var1.m_WorldVersion);
    ByteBuffer var4 = var1.m_byteBuffer;
               var4.rewind();
               var3.setBinaryStream(7, std::make_shared<ByteBufferBackedInputStream>(var4), var4.remaining());
               var3.setBoolean(8, var1.m_isDead);
               var3.setString(9, var1.m_name);
               var3.setInt(10, var1.m_sqlID);
    int var5 = var3.executeUpdate();
               this.m_conn.commit();
            }
         } catch (Exception var8) {
            PlayerDBHelper.rollback(this.m_conn);
    throw var8;
         }
      }
   }
}
} // namespace savefile
} // namespace zombie
