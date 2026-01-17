// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.characters.IsoGameCharacter;

public final class ParameterCharacterInside extends FMODLocalParameter {
    private final IsoGameCharacter character;

    public ParameterCharacterInside(IsoGameCharacter _character) {
        super("CharacterInside");
        this.character = _character;
    }

    @Override
    public float calculateCurrentValue() {
        if (this.character.getVehicle() == null) {
            return this.character.getCurrentBuilding() == null ? 0.0F : 1.0F;
        } else {
            return 2.0F;
        }
    }
}
