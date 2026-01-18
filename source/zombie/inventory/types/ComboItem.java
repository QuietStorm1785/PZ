// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.
package zombie.inventory.types;

import zombie.inventory.InventoryItem;
import zombie.scripting.objects.Item;

public final class ComboItem extends InventoryItem {
    public ComboItem(String module, String name, String itemType, String texName) {
        super(module, name, itemType, texName);
    }

    public ComboItem(String module, String name, String itemType, Item item) {
        super(module, name, itemType, item);
    }

    @Override
    public int getSaveType() {
        return Item.Type.Normal.ordinal();
    }
}
