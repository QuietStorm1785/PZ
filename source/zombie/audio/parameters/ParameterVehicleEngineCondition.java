// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.core.math.PZMath;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.VehiclePart;

public class ParameterVehicleEngineCondition extends FMODLocalParameter {
    private final BaseVehicle vehicle;

    public ParameterVehicleEngineCondition(BaseVehicle _vehicle) {
        super("VehicleEngineCondition");
        this.vehicle = _vehicle;
    }

    @Override
    public float calculateCurrentValue() {
        VehiclePart part = this.vehicle.getPartById("Engine");
        return part == null ? 100.0F : PZMath.clamp(part.getCondition(), 0, 100);
    }
}
