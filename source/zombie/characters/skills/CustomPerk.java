// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.characters.skills;

public final class CustomPerk {
    public String m_id;
    public String m_parent = "None";
    public String m_translation;
    public boolean m_bPassive = false;
    public final int[] m_xp = new int[10];

    public CustomPerk(String string) {
        this.m_id = string;
    }
}
