#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/network/GameClient.h"
#include <filesystem>

namespace zombie {
namespace iso {
namespace areas {


class NonPvpZone {
public:
    int x;
    int y;
    int x2;
    int y2;
    int size;
    std::string title;
   public static const std::vector<NonPvpZone> nonPvpZoneList = std::make_unique<std::vector<>>();

    public NonPvpZone() {
   }

    public NonPvpZone(const std::string& var1, int var2, int var3, int var4, int var5) {
      if (var2 > var4) {
    int var6 = var4;
         var4 = var2;
         var2 = var6;
      }

      if (var3 > var5) {
    int var7 = var5;
         var5 = var3;
         var3 = var7;
      }

      this.setX(var2);
      this.setX2(var4);
      this.setY(var3);
      this.setY2(var5);
      this.title = var1;
      this.size = Math.abs(var2 - var4 + (var3 - var5));
   }

    static NonPvpZone addNonPvpZone(const std::string& var0, int var1, int var2, int var3, int var4) {
    NonPvpZone var5 = std::make_shared<NonPvpZone>(var0, var1, var2, var3, var4);
      nonPvpZoneList.push_back(var5);
      var5.syncNonPvpZone(false);
    return var5;
   }

    static void removeNonPvpZone(const std::string& var0) {
    NonPvpZone var1 = getZoneByTitle(var0);
      if (var1 != nullptr) {
         nonPvpZoneList.remove(var1);
         var1.syncNonPvpZone(true);
      }
   }

    static NonPvpZone getZoneByTitle(const std::string& var0) {
      for (int var1 = 0; var1 < nonPvpZoneList.size(); var1++) {
    NonPvpZone var2 = nonPvpZoneList.get(var1);
         if (var2.getTitle() == var0)) {
    return var2;
         }
      }

    return nullptr;
   }

    static NonPvpZone getNonPvpZone(int var0, int var1) {
      for (int var2 = 0; var2 < nonPvpZoneList.size(); var2++) {
    NonPvpZone var3 = nonPvpZoneList.get(var2);
         if (var0 >= var3.getX() && var0 < var3.getX2() && var1 >= var3.getY() && var1 < var3.getY2()) {
    return var3;
         }
      }

    return nullptr;
   }

   public static std::vector<NonPvpZone> getAllZones() {
    return nonPvpZoneList;
   }

    void syncNonPvpZone(bool var1) {
      if (GameClient.bClient) {
         GameClient.sendNonPvpZone(this, var1);
      }
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.getX());
      var1.putInt(this.getY());
      var1.putInt(this.getX2());
      var1.putInt(this.getY2());
      var1.putInt(this.getSize());
      GameWindow.WriteString(var1, this.getTitle());
   }

    void load(ByteBuffer var1, int var2) {
      this.setX(var1.getInt());
      this.setY(var1.getInt());
      this.setX2(var1.getInt());
      this.setY2(var1.getInt());
      this.setSize(var1.getInt());
      this.setTitle(GameWindow.ReadString(var1));
   }

    int getX() {
      return this.x;
   }

    void setX(int var1) {
      this.x = var1;
   }

    int getY() {
      return this.y;
   }

    void setY(int var1) {
      this.y = var1;
   }

    int getX2() {
      return this.x2;
   }

    void setX2(int var1) {
      this.x2 = var1;
   }

    int getY2() {
      return this.y2;
   }

    void setY2(int var1) {
      this.y2 = var1;
   }

    std::string getTitle() {
      return this.title;
   }

    void setTitle(const std::string& var1) {
      this.title = var1;
   }

    int getSize() {
      return this.size;
   }

    void setSize(int var1) {
      this.size = var1;
   }
}
} // namespace areas
} // namespace iso
} // namespace zombie
