// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.advancedanimation;

import zombie.characters.action.ActionContext;
import zombie.core.skinnedmodel.animation.AnimationPlayer;
import zombie.core.skinnedmodel.animation.debug.AnimationPlayerRecorder;
import zombie.core.skinnedmodel.model.ModelInstance;

public interface IAnimatable extends IAnimationVariableSource {
    ActionContext getActionContext();

    AnimationPlayer getAnimationPlayer();

    AnimationPlayerRecorder getAnimationPlayerRecorder();

    boolean isAnimationRecorderActive();

    AdvancedAnimator getAdvancedAnimator();

    ModelInstance getModelInstance();

    String GetAnimSetName();

    String getUID();

    default short getOnlineID() {
        return -1;
    }
}
