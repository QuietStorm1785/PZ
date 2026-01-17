// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.iso.weather.ClimateManager;

public final class ParameterWindIntensity extends FMODGlobalParameter {
    public ParameterWindIntensity() {
        super("WindIntensity");
    }

    @Override
    public float calculateCurrentValue() {
        float float0 = ClimateManager.getInstance().getWindIntensity();
        return (int)(float0 * 1000.0F) / 1000.0F;
    }
}
