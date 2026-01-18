// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.randomizedWorld.randomizedDeadSurvivor;

import zombie.iso.BuildingDef;
import zombie.iso.SpawnPoints;
import zombie.randomizedWorld.randomizedBuilding.RandomizedBuildingBase;

public class RandomizedDeadSurvivorBase extends RandomizedBuildingBase {
    public void randomizeDeadSurvivor(BuildingDef def) {
    }

    @Override
    public boolean isValid(BuildingDef buildingDef, boolean var2) {
        return !SpawnPoints.instance.isSpawnBuilding(buildingDef);
    }
}
