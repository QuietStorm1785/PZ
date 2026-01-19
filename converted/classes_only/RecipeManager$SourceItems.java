package zombie.inventory;

import java.util.ArrayList;
import zombie.characters.IsoGameCharacter;
import zombie.inventory.RecipeManager.RMRecipeItemList.Type;
import zombie.scripting.objects.Recipe;

final class RecipeManager$SourceItems {
   InventoryItem selectedItem;
   final ArrayList<InventoryItem> allItems = new ArrayList<>();
   final ArrayList<InventoryItem>[] itemsPerSource;
   final Type[] typePerSource;

   RecipeManager$SourceItems(Recipe var1, IsoGameCharacter var2, InventoryItem var3, ArrayList<InventoryItem> var4) {
      this.itemsPerSource = new ArrayList[var1.getSource().size()];

      for (int var5 = 0; var5 < this.itemsPerSource.length; var5++) {
         this.itemsPerSource[var5] = new ArrayList<>();
      }

      this.typePerSource = new Type[var1.getSource().size()];
      this.selectedItem = var3;
   }

   public ArrayList<InventoryItem> getItems() {
      return this.allItems;
   }
}
