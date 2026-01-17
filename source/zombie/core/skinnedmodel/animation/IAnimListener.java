// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.animation;

/**
 * Created by LEMMYMAIN on 23/02/2015.
 */
public interface IAnimListener {
    void onAnimStarted(AnimationTrack track);

    void onLoopedAnim(AnimationTrack track);

    void onNonLoopedAnimFadeOut(AnimationTrack track);

    void onNonLoopedAnimFinished(AnimationTrack track);

    void onTrackDestroyed(AnimationTrack track);
}
