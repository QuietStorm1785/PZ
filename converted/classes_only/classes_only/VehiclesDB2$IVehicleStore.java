package zombie.vehicles;

import gnu.trove.set.hash.TIntHashSet;
import java.io.IOException;
import zombie.iso.IsoChunk;
import zombie.vehicles.VehiclesDB2.ThrowingBiConsumer;
import zombie.vehicles.VehiclesDB2.ThrowingConsumer;
import zombie.vehicles.VehiclesDB2.VehicleBuffer;

abstract class VehiclesDB2$IVehicleStore {
   private VehiclesDB2$IVehicleStore() {
   }

   abstract void init(TIntHashSet var1, TIntHashSet var2);

   abstract void Reset();

   abstract void loadChunk(IsoChunk var1, ThrowingBiConsumer<IsoChunk, VehicleBuffer, IOException> var2) throws IOException;

   abstract void loadChunk(int var1, int var2, ThrowingConsumer<VehicleBuffer, IOException> var3) throws IOException;

   abstract void updateVehicle(VehicleBuffer var1);

   abstract void removeVehicle(int var1);
}
