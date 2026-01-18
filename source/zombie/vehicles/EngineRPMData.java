// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.vehicles;

public final class EngineRPMData {
    public float gearChange;
    public float afterGearChange;

    public EngineRPMData() {
    }

    public EngineRPMData(float _gearChange, float _afterGearChange) {
        this.gearChange = _gearChange;
        this.afterGearChange = _afterGearChange;
    }

    public void reset() {
        this.gearChange = 0.0F;
        this.afterGearChange = 0.0F;
    }
}
