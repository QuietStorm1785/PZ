#pragma once
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
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieIDMapTest : public Assert {
public:
 HashSet<Short> IDs = std::make_unique<HashSet<>>();
 IsoCell cell = new IsoCell(300, 300);

 static void beforeAll() {
 try {
 Rand.init();
 ZomboidFileSystem.instance.init();
 LuaManager.init();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 void test10Allocations() {
 Rand.init();
 this->IDs.clear();
 uint8_t byte0 = 10;

 for (short short0 = 0; short0 < byte0; short0++) {
 short short1 = ServerMap.instance.getUniqueZombieId();
 System.out.println("id:" + short1);
 }
 }

 void test32653Allocations() {
 Rand.init();
 this->IDs.clear();
 char char0 = '\u875d';
 long long0 = System.nanoTime();

 for (int int0 = 0; int0 < char0; int0++) {
 short short0 = ServerMap.instance.getUniqueZombieId();
 assertFalse(this->IDs.contains(short0);
 this->IDs.add(short0);
 }

 long long1 = System.nanoTime();
 float float0 = (float)(long1 - long0) / 1000000.0F;
 System.out.println("time:" + float0);
 System.out.println("time per task:" + float0 / char0);
 }

 void test32653Adds() {
 SoundManager.instance = std::make_unique<DummySoundManager>();
 Rand.init();
 SurvivorFactory.addMaleForename("Bob");
 SurvivorFactory.addFemaleForename("Kate");
 SurvivorFactory.addSurname("Testova");
 this->IDs.clear();
 short short0 = 32653;
 long long0 = System.nanoTime();

 for (short short1 = 0; short1 < short0; short1++) {
 short short2 = ServerMap.instance.getUniqueZombieId();
 assertNull(ServerMap.instance.ZombieMap.get(short2);
 assertFalse(this->IDs.contains(short2);
 IsoZombie zombie0 = new IsoZombie(this->cell);
 zombie0.OnlineID = short2;
 ServerMap.instance.ZombieMap.put(short2, zombie0);
 assertEquals(short2, ServerMap.instance.ZombieMap.get(short2).OnlineID);
 this->IDs.add(short2);
 }

 long long1 = System.nanoTime();
 float float0 = (float)(long1 - long0) / 1000000.0F;
 System.out.println("time:" + float0);
 System.out.println("time per task:" + float0 / short0);
 }

 void test32653Process() {
 Rand.init();
 ServerMap.instance = std::make_unique<ServerMap>();
 SoundManager.instance = std::make_unique<DummySoundManager>();
 SurvivorFactory.addMaleForename("Bob");
 SurvivorFactory.addFemaleForename("Kate");
 SurvivorFactory.addSurname("Testova");
 this->IDs.clear();
 short short0 = 32653;
 long long0 = System.nanoTime();

 for (short short1 = 0; short1 < short0; short1++) {
 assertNull(ServerMap.instance.ZombieMap.get(short1);
 IsoZombie zombie0 = new IsoZombie(this->cell);
 zombie0.OnlineID = short1;
 ServerMap.instance.ZombieMap.put(short1, zombie0);
 assertEquals(short1, ServerMap.instance.ZombieMap.get(short1).OnlineID);
 }

 long long1 = System.nanoTime();

 for (short short2 = 0; short2 < short0; short2++) {
 assertEquals(short2, ServerMap.instance.ZombieMap.get(short2).OnlineID);
 ServerMap.instance.ZombieMap.remove(short2);
 assertNull(ServerMap.instance.ZombieMap.get(short2);
 }

 long long2 = System.nanoTime();

 for (short short3 = 0; short3 < short0; short3++) {
 assertNull(ServerMap.instance.ZombieMap.get(short3);
 IsoZombie zombie1 = new IsoZombie(this->cell);
 zombie1.OnlineID = short3;
 ServerMap.instance.ZombieMap.put(short3, zombie1);
 assertEquals(short3, ServerMap.instance.ZombieMap.get(short3).OnlineID);
 }

 long long3 = System.nanoTime();

 for (short short4 = 0; short4 < short0; short4++) {
 assertEquals(short4, ServerMap.instance.ZombieMap.get(short4).OnlineID);
 ServerMap.instance.ZombieMap.remove(short4);
 assertNull(ServerMap.instance.ZombieMap.get(short4);
 }

 long long4 = System.nanoTime();

 for (short short5 = 0; short5 < short0; short5++) {
 assertNull(ServerMap.instance.ZombieMap.get(short5);
 IsoZombie zombie2 = new IsoZombie(this->cell);
 zombie2.OnlineID = short5;
 ServerMap.instance.ZombieMap.put(short5, zombie2);
 assertEquals(short5, ServerMap.instance.ZombieMap.get(short5).OnlineID);
 }

 long long5 = System.nanoTime();
 float float0 = (float)(long1 - long0) / 1000000.0F;
 float float1 = (float)(long2 - long1) / 1000000.0F;
 float float2 = (float)(long3 - long2) / 1000000.0F;
 float float3 = (float)(long4 - long3) / 1000000.0F;
 float float4 = (float)(long5 - long4) / 1000000.0F;
 System.out.println("time1:" + float0);
 System.out.println("time2:" + float1);
 System.out.println("time3:" + float2);
 System.out.println("time4:" + float3);
 System.out.println("time5:" + float4);
 }
}
} // namespace characters
} // namespace zombie
