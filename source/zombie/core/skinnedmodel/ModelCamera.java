// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel;

import zombie.core.opengl.IModelCamera;

public abstract class ModelCamera implements IModelCamera {
    public static ModelCamera instance = null;
    public float m_useAngle;
    public boolean m_bUseWorldIso;
    public float m_x;
    public float m_y;
    public float m_z;
    public boolean m_bInVehicle;
    public boolean bDepthMask = true;
}
