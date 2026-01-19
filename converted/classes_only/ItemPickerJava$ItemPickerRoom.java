package zombie.inventory;

import gnu.trove.map.hash.THashMap;
import zombie.inventory.ItemPickerJava.ItemPickerContainer;

public final class ItemPickerJava$ItemPickerRoom {
   public THashMap<String, ItemPickerContainer> Containers = new THashMap();
   public int fillRand;
   public boolean isShop;
   public String specificId = null;
}
