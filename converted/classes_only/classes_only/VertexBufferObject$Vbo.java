package zombie.core.skinnedmodel.model;

import java.nio.IntBuffer;
import org.lwjglx.BufferUtils;

public final class VertexBufferObject$Vbo {
   public final IntBuffer b = BufferUtils.createIntBuffer(4);
   public int VboID;
   public int EboID;
   public int NumElements;
   public int VertexStride;
   public boolean FaceDataOnly;
}
