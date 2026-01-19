package zombie.inventory;

import zombie.inventory.ClothingItemsDotTxt.Block;
import zombie.inventory.ClothingItemsDotTxt.Value;

interface ClothingItemsDotTxt$BlockElement {
   Block asBlock();

   Value asValue();

   String toXML();
}
