// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.vehicles.BaseVehicle;

public class ParameterVehicleLoad extends FMODLocalParameter {
    private final BaseVehicle vehicle;

    public ParameterVehicleLoad(BaseVehicle _vehicle) {
        super("VehicleLoad");
        this.vehicle = _vehicle;
    }

    @Override
    public float calculateCurrentValue() {
        return this.vehicle.getController().isGasPedalPressed() ? 1.0F : 0.0F;
    }
}
