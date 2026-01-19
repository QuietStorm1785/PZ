#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include "zombie/GameWindow.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/worldMap/WorldMapGeometry/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace worldMap {


class WorldMapBinary {
:
    static const int VERSION1 = 1;
    static const int VERSION_LATEST = 1;
    const SharedStrings m_sharedStrings = new SharedStrings();
   private TIntObjectHashMap<String> m_stringTable = std::make_unique<TIntObjectHashMap>();
    const WorldMapProperties m_properties = new WorldMapProperties();
   private ArrayList<WorldMapProperties> m_sharedProperties = std::make_unique<ArrayList<>>();

    bool read(std::string_view var1, WorldMapData var2) {
      try (
    FileInputStream var3 = new FileInputStream(var1);
    BufferedInputStream var4 = new BufferedInputStream(var3);
      ) {
    int var5 = var4.read();
    int var6 = var4.read();
    int var7 = var4.read();
    int var8 = var4.read();
         if (var5 == 73 && var6 == 71 && var7 == 77 && var8 == 66) {
    int var9 = this.readInt(var4);
            if (var9 >= 1 && var9 <= 1) {
    int var10 = this.readInt(var4);
    int var11 = this.readInt(var4);
               this.readStringTable(var4);

               for (int var12 = 0; var12 < var11; var12++) {
                  for (int var13 = 0; var13 < var10; var13++) {
    WorldMapCell var14 = this.parseCell(var4);
                     if (var14 != nullptr) {
                        var2.m_cells.add(var14);
                     }
                  }
               }

    return true;
            } else {
               throw IOException("unrecognized version " + var9);
            }
         } else {
            throw IOException("invalid format (magic doesn't match)");
         }
      }
   }

    int readByte(InputStream var1) {
      return var1.read();
   }

    int readInt(InputStream var1) {
    int var2 = var1.read();
    int var3 = var1.read();
    int var4 = var1.read();
    int var5 = var1.read();
      if ((var2 | var3 | var4 | var5) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var2 << 0) + (var3 << 8) + (var4 << 16) + (var5 << 24);
      }
   }

    int readShort(InputStream var1) {
    int var2 = var1.read();
    int var3 = var1.read();
      if ((var2 | var3) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (short)((var2 << 0) + (var3 << 8));
      }
   }

    void readStringTable(InputStream var1) {
    ByteBuffer var2 = ByteBuffer.allocate(1024);
      byte[] var3 = new byte[1024];
    int var4 = this.readInt(var1);

      for (int var5 = 0; var5 < var4; var5++) {
         var2.clear();
    int var6 = this.readShort(var1);
         var2.putShort((short)var6);
         var1.read(var3, 0, var6);
         var2.put(var3, 0, var6);
         var2.flip();
         this.m_stringTable.put(var5, GameWindow.ReadStringUTF(var2));
      }
   }

    std::string readStringIndexed(InputStream var1) {
    int var2 = this.readShort(var1);
      if (!this.m_stringTable.containsKey(var2)) {
         throw IOException("invalid string-table index " + var2);
      } else {
         return (String)this.m_stringTable.get(var2);
      }
   }

    WorldMapCell parseCell(InputStream var1) {
    int var2 = this.readInt(var1);
      if (var2 == -1) {
    return nullptr;
      } else {
    int var3 = this.readInt(var1);
    WorldMapCell var4 = new WorldMapCell();
         var4.m_x = var2;
         var4.m_y = var3;
    int var5 = this.readInt(var1);

         for (int var6 = 0; var6 < var5; var6++) {
    WorldMapFeature var7 = this.parseFeature(var4, var1);
            var4.m_features.add(var7);
         }

    return var4;
      }
   }

    WorldMapFeature parseFeature(WorldMapCell var1, InputStream var2) {
    WorldMapFeature var3 = new WorldMapFeature(var1);
    WorldMapGeometry var4 = this.parseGeometry(var2);
      var3.m_geometries.add(var4);
      this.parseFeatureProperties(var2, var3);
    return var3;
   }

    void parseFeatureProperties(InputStream var1, WorldMapFeature var2) {
      this.m_properties.clear();
    int var3 = this.readByte(var1);

      for (int var4 = 0; var4 < var3; var4++) {
    std::string var5 = this.m_sharedStrings.get(this.readStringIndexed(var1));
    std::string var6 = this.m_sharedStrings.get(this.readStringIndexed(var1));
         this.m_properties.put(var5, var6);
      }

      var2.m_properties = this.getOrCreateProperties(this.m_properties);
   }

    WorldMapProperties getOrCreateProperties(WorldMapProperties var1) {
      for (int var2 = 0; var2 < this.m_sharedProperties.size(); var2++) {
         if (this.m_sharedProperties.get(var2) == var1)) {
            return this.m_sharedProperties.get(var2);
         }
      }

    WorldMapProperties var3 = new WorldMapProperties();
      var3.putAll(var1);
      this.m_sharedProperties.add(var3);
    return var3;
   }

    WorldMapGeometry parseGeometry(InputStream var1) {
    WorldMapGeometry var2 = new WorldMapGeometry();
      var2.m_type = Type.valueOf(this.readStringIndexed(var1));
    int var3 = this.readByte(var1);

      for (int var4 = 0; var4 < var3; var4++) {
    WorldMapPoints var5 = new WorldMapPoints();
         this.parseGeometryCoordinates(var1, var5);
         var2.m_points.add(var5);
      }

      var2.calculateBounds();
    return var2;
   }

    void parseGeometryCoordinates(InputStream var1, WorldMapPoints var2) {
    int var3 = this.readShort(var1);

      for (int var4 = 0; var4 < var3; var4++) {
         var2.add(this.readShort(var1));
         var2.add(this.readShort(var1));
      }
   }
}
} // namespace worldMap
} // namespace zombie
