package zombie.inventory;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

class CompressIdenticalItems$PerCallData {
   final ArrayList<String> types = new ArrayList<>();
   final HashMap<String, ArrayList<InventoryItem>> typeToItems = new HashMap<>();
   final ArrayDeque<ArrayList<InventoryItem>> itemLists = new ArrayDeque<>();
   final ArrayList<InventoryItem> savedItems = new ArrayList<>();
   CompressIdenticalItems$PerCallData next;

   private CompressIdenticalItems$PerCallData() {
   }

   void reset() {
      for (int var1 = 0; var1 < this.types.size(); var1++) {
         ArrayList var2 = this.typeToItems.get(this.types.get(var1));
         var2.clear();
         this.itemLists.push(var2);
      }

      this.types.clear();
      this.typeToItems.clear();
      this.savedItems.clear();
   }

   ArrayList<InventoryItem> allocItemList() {
      return this.itemLists.isEmpty() ? new ArrayList<>() : this.itemLists.pop();
   }
}
