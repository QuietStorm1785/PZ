package zombie.inventory;

import java.util.ArrayList;
import zombie.inventory.ClothingItemsDotTxt.BlockElement;
import zombie.inventory.ClothingItemsDotTxt.Value;

class ClothingItemsDotTxt$Block implements BlockElement {
   public String type;
   public String id;
   public ArrayList<BlockElement> elements = new ArrayList<>();
   public ArrayList<String> values = new ArrayList<>();
   public ArrayList<ClothingItemsDotTxt$Block> children = new ArrayList<>();

   private ClothingItemsDotTxt$Block() {
   }

   public ClothingItemsDotTxt$Block asBlock() {
      return this;
   }

   public Value asValue() {
      return null;
   }

   @Override
   public String toString() {
      StringBuilder var1 = new StringBuilder();
      var1.append(this.type + (this.id == null ? "" : " " + this.id) + "\n");
      var1.append("{\n");

      for (BlockElement var3 : this.elements) {
         String var4 = var3.toString();

         for (String var8 : var4.split("\n")) {
            var1.append("\t" + var8 + "\n");
         }
      }

      var1.append("}\n");
      return var1.toString();
   }

   public String toXML() {
      StringBuilder var1 = new StringBuilder();
      var1.append("<Block type=\"" + this.type + "\" id=\"" + this.id + "\">\n");

      for (BlockElement var3 : this.elements) {
         String var4 = var3.toXML();

         for (String var8 : var4.split("\n")) {
            var1.append("    " + var8 + "\n");
         }
      }

      var1.append("</Block>\n");
      return var1.toString();
   }
}
