// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.iso.areas;

public final class BuildingScore {
    public float weapons;
    public float food;
    public float wood;
    public float defense;
    public IsoBuilding building;
    public int size;
    public int safety;

    public BuildingScore(IsoBuilding buildingx) {
        this.building = buildingx;
    }
}
