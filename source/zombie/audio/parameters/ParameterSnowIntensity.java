// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.iso.weather.ClimateManager;

public final class ParameterSnowIntensity extends FMODGlobalParameter {
    public ParameterSnowIntensity() {
        super("SnowIntensity");
    }

    @Override
    public float calculateCurrentValue() {
        return ClimateManager.getInstance().isSnowing() ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
    }
}
