package zombie.scripting;

import zombie.scripting.ScriptParser.Block;
import zombie.scripting.ScriptParser.Value;

public interface ScriptParser$BlockElement {
   Block asBlock();

   Value asValue();

   void prettyPrint(int var1, StringBuilder var2, String var3);
}
