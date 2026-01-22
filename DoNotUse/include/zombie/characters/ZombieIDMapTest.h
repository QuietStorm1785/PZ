#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/junit/Assert.h"
#include "org/junit/BeforeClass.h"
#include "org/junit/Test.h"
#include "zombie/DummySoundManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/network/ServerMap.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {


class ZombieIDMapTest : public Assert {
public:
   std::unordered_set<int16_t> IDs = std::make_unique<std::unordered_set<>>();
    IsoCell cell = std::make_shared<IsoCell>(300, 300);

    static void beforeAll() {
      try {
         Rand.init();
         ZomboidFileSystem.instance.init();
         LuaManager.init();
      } catch (IOException var1) {
         var1.printStackTrace();
      }
   }

    void test10Allocations() {
      Rand.init();
      this.IDs.clear();
    uint8_t var1 = 10;

      for (short var2 = 0; var2 < var1; var2++) {
    short var3 = ServerMap.instance.getUniqueZombieId();
         System.out.println("id:" + var3);
      }
   }

    void test32653Allocations() {
      Rand.init();
      this.IDs.clear();
    char var1 = '蝝';
    long var2 = System.nanoTime();

      for (int var4 = 0; var4 < var1; var4++) {
    short var5 = ServerMap.instance.getUniqueZombieId();
         assertFalse(this.IDs.contains(var5));
         this.IDs.push_back(var5);
      }

    long var7 = System.nanoTime();
    float var6 = (float)(var7 - var2) / 1000000.0F;
      System.out.println("time:" + var6);
      System.out.println("time per task:" + var6 / var1);
   }

    void test32653Adds() {
      SoundManager.instance = std::make_unique<DummySoundManager>();
      Rand.init();
      SurvivorFactory.addMaleForename("Bob");
      SurvivorFactory.addFemaleForename("Kate");
      SurvivorFactory.addSurname("Testova");
      this.IDs.clear();
    short var1 = 32653;
    long var2 = System.nanoTime();

      for (short var4 = 0; var4 < var1; var4++) {
    short var5 = ServerMap.instance.getUniqueZombieId();
         assertNull(ServerMap.instance.ZombieMap.get(var5));
         assertFalse(this.IDs.contains(var5));
    IsoZombie var6 = std::make_shared<IsoZombie>(this.cell);
         var6.OnlineID = var5;
         ServerMap.instance.ZombieMap.put(var5, var6);
         assertEquals(var5, ((IsoZombie)ServerMap.instance.ZombieMap.get(var5)).OnlineID);
         this.IDs.push_back(var5);
      }

    long var7 = System.nanoTime();
    float var8 = (float)(var7 - var2) / 1000000.0F;
      System.out.println("time:" + var8);
      System.out.println("time per task:" + var8 / var1);
   }

    void test32653Process() {
      Rand.init();
      ServerMap.instance = std::make_unique<ServerMap>();
      SoundManager.instance = std::make_unique<DummySoundManager>();
      SurvivorFactory.addMaleForename("Bob");
      SurvivorFactory.addFemaleForename("Kate");
      SurvivorFactory.addSurname("Testova");
      this.IDs.clear();
    short var1 = 32653;
    long var2 = System.nanoTime();

      for (short var4 = 0; var4 < var1; var4++) {
         assertNull(ServerMap.instance.ZombieMap.get(var4));
    IsoZombie var5 = std::make_shared<IsoZombie>(this.cell);
         var5.OnlineID = var4;
         ServerMap.instance.ZombieMap.put(var4, var5);
         assertEquals(var4, ((IsoZombie)ServerMap.instance.ZombieMap.get(var4)).OnlineID);
      }

    long var19 = System.nanoTime();

      for (short var6 = 0; var6 < var1; var6++) {
         assertEquals(var6, ((IsoZombie)ServerMap.instance.ZombieMap.get(var6)).OnlineID);
         ServerMap.instance.ZombieMap.remove(var6);
         assertNull(ServerMap.instance.ZombieMap.get(var6));
      }

    long var20 = System.nanoTime();

      for (short var8 = 0; var8 < var1; var8++) {
         assertNull(ServerMap.instance.ZombieMap.get(var8));
    IsoZombie var9 = std::make_shared<IsoZombie>(this.cell);
         var9.OnlineID = var8;
         ServerMap.instance.ZombieMap.put(var8, var9);
         assertEquals(var8, ((IsoZombie)ServerMap.instance.ZombieMap.get(var8)).OnlineID);
      }

    long var21 = System.nanoTime();

      for (short var10 = 0; var10 < var1; var10++) {
         assertEquals(var10, ((IsoZombie)ServerMap.instance.ZombieMap.get(var10)).OnlineID);
         ServerMap.instance.ZombieMap.remove(var10);
         assertNull(ServerMap.instance.ZombieMap.get(var10));
      }

    long var22 = System.nanoTime();

      for (short var12 = 0; var12 < var1; var12++) {
         assertNull(ServerMap.instance.ZombieMap.get(var12));
    IsoZombie var13 = std::make_shared<IsoZombie>(this.cell);
         var13.OnlineID = var12;
         ServerMap.instance.ZombieMap.put(var12, var13);
         assertEquals(var12, ((IsoZombie)ServerMap.instance.ZombieMap.get(var12)).OnlineID);
      }

    long var23 = System.nanoTime();
    float var14 = (float)(var19 - var2) / 1000000.0F;
    float var15 = (float)(var20 - var19) / 1000000.0F;
    float var16 = (float)(var21 - var20) / 1000000.0F;
    float var17 = (float)(var22 - var21) / 1000000.0F;
    float var18 = (float)(var23 - var22) / 1000000.0F;
      System.out.println("time1:" + var14);
      System.out.println("time2:" + var15);
      System.out.println("time3:" + var16);
      System.out.println("time4:" + var17);
      System.out.println("time5:" + var18);
   }
}
} // namespace characters
} // namespace zombie
