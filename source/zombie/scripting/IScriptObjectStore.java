// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.scripting;

import zombie.scripting.objects.Item;
import zombie.scripting.objects.Recipe;

public interface IScriptObjectStore {
    Item getItem(String name);

    Recipe getRecipe(String name);
}
