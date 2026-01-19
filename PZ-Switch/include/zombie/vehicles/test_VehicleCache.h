#pragma once
#include "org/junit/Assert.h"
#include "org/junit/Test.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class test_VehicleCache : public Assert {
public:
 void test_getInsertIndex() noexcept{
 VehicleCache.vehicleUpdate((short)1, 10.0F, 20.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)2, 10.0F, 21.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)3, 15.0F, 22.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)4, 1010.0F, 1020.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)5, 2000.0F, 2020.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)6, 3010.0F, 3000.0F, 0.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(1, 2);
 assertEquals(nullptr, VehicleCache.vehicleGet(1, 3);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(10.0F, 20.0F);
 assertEquals(nullptr, VehicleCache.vehicleGet(10.0F, 30.0F);
 assertEquals(3L, VehicleCache.vehicleGet(10.0F, 20.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(1010.0F, 1020.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(2000.0F, 2020.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(3010.0F, 3000.0F).size());
 VehicleCache.vehicleUpdate((short)1, 12.0F, 200.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)2, 10.0F, 210.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)3, 10.0F, 25.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)4, 1020.0F, 1020.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)5, 2000.0F, 2030.0F, 0.0F);
 VehicleCache.vehicleUpdate((short)6, 3010.3F, 3000.1F, 0.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(10.0F, 20.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(10.0F, 200.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(10.0F, 210.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(1020.0F, 1020.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(2000.0F, 2030.0F);
 assertNotEquals(nullptr, VehicleCache.vehicleGet(3010.0F, 3000.0F);
 assertEquals(1L, VehicleCache.vehicleGet(10.0F, 20.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(10.0F, 200.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(10.0F, 210.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(1020.0F, 1020.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(2000.0F, 2030.0F).size());
 assertEquals(1L, VehicleCache.vehicleGet(3010.0F, 3000.0F).size());
 assertEquals(0L, VehicleCache.vehicleGet(1010.0F, 1020.0F).size());
 assertEquals(0L, VehicleCache.vehicleGet(2000.0F, 2020.0F).size());
 assertEquals(3L, VehicleCache.vehicleGet(10.0F, 20.0F).get(0).id);
 assertEquals(1L, VehicleCache.vehicleGet(10.0F, 200.0F).get(0).id);
 assertEquals(2L, VehicleCache.vehicleGet(10.0F, 210.0F).get(0).id);
 assertEquals(4L, VehicleCache.vehicleGet(1020.0F, 1020.0F).get(0).id);
 assertEquals(5L, VehicleCache.vehicleGet(2000.0F, 2030.0F).get(0).id);
 assertEquals(6L, VehicleCache.vehicleGet(3010.0F, 3000.0F).get(0).id);
 }
}
} // namespace vehicles
} // namespace zombie
