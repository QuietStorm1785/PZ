package zombie.scripting.objects;

import java.util.ArrayList;
import zombie.core.skinnedmodel.model.ModelMesh;
import zombie.scripting.ScriptParser;
import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;

public final class AnimationsMesh extends BaseScriptObject {
   public String name = null;
   public String meshFile = null;
   public final ArrayList<String> animationDirectories = new ArrayList<>();
   public ModelMesh modelMesh = null;

   public void Load(String var1, String var2) {
      this.name = var1;
      Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
         String var6 = var5.getKey().trim();
         String var7 = var5.getValue().trim();
         if ("meshFile".equalsIgnoreCase(var6)) {
            this.meshFile = var7;
         } else if ("animationDirectory".equalsIgnoreCase(var6)) {
            this.animationDirectories.add(var7);
         }
      }
   }

   public void reset() {
      this.meshFile = null;
      this.animationDirectories.clear();
      this.modelMesh = null;
   }
}
