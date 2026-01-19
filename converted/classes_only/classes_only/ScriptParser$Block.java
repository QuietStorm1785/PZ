package zombie.scripting;

import java.util.ArrayList;
import zombie.scripting.ScriptParser.BlockElement;
import zombie.scripting.ScriptParser.Value;

public class ScriptParser$Block implements BlockElement {
   public String type;
   public String id;
   public final ArrayList<BlockElement> elements = new ArrayList<>();
   public final ArrayList<Value> values = new ArrayList<>();
   public final ArrayList<ScriptParser$Block> children = new ArrayList<>();

   public ScriptParser$Block asBlock() {
      return this;
   }

   public Value asValue() {
      return null;
   }

   public boolean isEmpty() {
      return this.elements.isEmpty();
   }

   public void prettyPrint(int var1, StringBuilder var2, String var3) {
      for (int var4 = 0; var4 < var1; var4++) {
         var2.append('\t');
      }

      var2.append(this.type);
      if (this.id != null) {
         var2.append(" ");
         var2.append(this.id);
      }

      var2.append(var3);

      for (int var5 = 0; var5 < var1; var5++) {
         var2.append('\t');
      }

      var2.append('{');
      var2.append(var3);
      this.prettyPrintElements(var1 + 1, var2, var3);

      for (int var6 = 0; var6 < var1; var6++) {
         var2.append('\t');
      }

      var2.append('}');
      var2.append(var3);
   }

   public void prettyPrintElements(int var1, StringBuilder var2, String var3) {
      BlockElement var4 = null;

      for (BlockElement var6 : this.elements) {
         if (var6.asBlock() != null && var4 != null) {
            var2.append(var3);
         }

         if (var6.asValue() != null && var4 instanceof ScriptParser$Block) {
            var2.append(var3);
         }

         var6.prettyPrint(var1, var2, var3);
         var4 = var6;
      }
   }

   public ScriptParser$Block addBlock(String var1, String var2) {
      ScriptParser$Block var3 = new ScriptParser$Block();
      var3.type = var1;
      var3.id = var2;
      this.elements.add(var3);
      this.children.add(var3);
      return var3;
   }

   public ScriptParser$Block getBlock(String var1, String var2) {
      for (ScriptParser$Block var4 : this.children) {
         if (var4.type.equals(var1) && (var4.id != null && var4.id.equals(var2) || var4.id == null && var2 == null)) {
            return var4;
         }
      }

      return null;
   }

   public Value getValue(String var1) {
      for (Value var3 : this.values) {
         int var4 = var3.string.indexOf(61);
         if (var4 > 0 && var3.getKey().trim().equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public void setValue(String var1, String var2) {
      Value var3 = this.getValue(var1);
      if (var3 == null) {
         this.addValue(var1, var2);
      } else {
         var3.string = var1 + " = " + var2;
      }
   }

   public Value addValue(String var1, String var2) {
      Value var3 = new Value();
      var3.string = var1 + " = " + var2;
      this.elements.add(var3);
      this.values.add(var3);
      return var3;
   }

   public void moveValueAfter(String var1, String var2) {
      Value var3 = this.getValue(var1);
      Value var4 = this.getValue(var2);
      if (var3 != null && var4 != null) {
         this.elements.remove(var3);
         this.values.remove(var3);
         this.elements.add(this.elements.indexOf(var4) + 1, var3);
         this.values.add(this.values.indexOf(var4) + 1, var3);
      }
   }
}
