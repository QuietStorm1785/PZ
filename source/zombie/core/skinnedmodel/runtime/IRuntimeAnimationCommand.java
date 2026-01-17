// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.core.skinnedmodel.runtime;

import java.util.List;
import zombie.core.skinnedmodel.animation.Keyframe;
import zombie.scripting.ScriptParser;

public interface IRuntimeAnimationCommand {
    void parse(ScriptParser.Block var1);

    void exec(List<Keyframe> var1);
}
