package zombie.core.skinnedmodel.runtime;

import java.util.List;
import zombie.core.skinnedmodel.animation.Keyframe;
import zombie.scripting.ScriptParser.Block;

public interface IRuntimeAnimationCommand {
   void parse(Block var1);

   void exec(List<Keyframe> var1);
}
