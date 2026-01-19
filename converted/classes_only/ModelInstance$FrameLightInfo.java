package zombie.core.skinnedmodel.model;

import org.lwjgl.util.vector.Vector3f;
import zombie.core.skinnedmodel.model.ModelInstance.FrameLightBlendStatus;

public final class ModelInstance$FrameLightInfo {
   public FrameLightBlendStatus Stage;
   public int id;
   public int x;
   public int y;
   public int z;
   public float distSq;
   public int radius;
   public float r;
   public float g;
   public float b;
   public int flags;
   public final Vector3f currentColor = new Vector3f();
   public final Vector3f targetColor = new Vector3f();
   public boolean active;
   public boolean foundThisFrame;
}
