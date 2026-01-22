#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#if __has_include(<absl/container/flat_hash_set.h>)
#  include <absl/container/flat_hash_set.h>
#  define INT_HASH_SET absl::flat_hash_set
#elif __has_include(<boost/unordered_set.hpp>)
#  include <boost/unordered_set.hpp>
#  define INT_HASH_SET boost::unordered_set
#else
#  include <unordered_set>
#  define INT_HASH_SET std::unordered_set
#endif
#include "zombie/iso/IsoChunk.h"
#include "zombie/vehicles/VehiclesDB2/ThrowingBiConsumer.h"
#include "zombie/vehicles/VehiclesDB2/ThrowingConsumer.h"
#include "zombie/vehicles/VehiclesDB2/VehicleBuffer.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
   private VehiclesDB2$IVehicleStore() {
   }

   virtual void init(INT_HASH_SET<int>& var1, INT_HASH_SET<int>& var2) = 0;

   abstract void Reset();

   abstract void loadChunk(IsoChunk var1, ThrowingBiConsumer<IsoChunk, VehicleBuffer, IOException> var2) throws IOException;

   abstract void loadChunk(int var1, int var2, ThrowingConsumer<VehicleBuffer, IOException> var3) throws IOException;

   abstract void updateVehicle(VehicleBuffer var1);

   abstract void removeVehicle(int var1);
}
} // namespace vehicles
} // namespace zombie
