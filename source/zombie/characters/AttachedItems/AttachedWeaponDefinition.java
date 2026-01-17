// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.characters.AttachedItems;

import java.util.ArrayList;
import zombie.characterTextures.BloodBodyPartType;

public final class AttachedWeaponDefinition {
    public String id;
    public int chance;
    public final ArrayList<String> outfit = new ArrayList<>();
    public final ArrayList<String> weaponLocation = new ArrayList<>();
    public final ArrayList<BloodBodyPartType> bloodLocations = new ArrayList<>();
    public boolean addHoles;
    public int daySurvived;
    public String ensureItem;
    public final ArrayList<String> weapons = new ArrayList<>();
}
