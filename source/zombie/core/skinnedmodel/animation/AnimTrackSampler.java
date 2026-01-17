// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.animation;

import org.lwjgl.util.vector.Matrix4f;

public interface AnimTrackSampler {
    float getTotalTime();

    boolean isLooped();

    void moveToTime(float time);

    float getCurrentTime();

    void getBoneMatrix(int boneIdx, Matrix4f out_matrix);

    int getNumBones();
}
