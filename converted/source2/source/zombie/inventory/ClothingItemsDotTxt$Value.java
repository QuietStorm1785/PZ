package zombie.inventory;

import zombie.inventory.ClothingItemsDotTxt.Block;
import zombie.inventory.ClothingItemsDotTxt.BlockElement;

class ClothingItemsDotTxt$Value implements BlockElement {
   String string;

   private ClothingItemsDotTxt$Value() {
   }

   public Block asBlock() {
      return null;
   }

   public ClothingItemsDotTxt$Value asValue() {
      return this;
   }

   @Override
   public String toString() {
      return this.string + ",\n";
   }

   public String toXML() {
      return "<Value>" + this.string + "</Value>\n";
   }
}
