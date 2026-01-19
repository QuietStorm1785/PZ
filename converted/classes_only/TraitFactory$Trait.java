package zombie.characters.traits;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import zombie.characters.skills.PerkFactory.Perk;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.textures.Texture;
import zombie.debug.DebugLog;
import zombie.interfaces.IListBoxItem;

public class TraitFactory$Trait implements IListBoxItem {
   public String traitID;
   public String name;
   public int cost;
   public String description;
   public boolean prof;
   public Texture texture = null;
   private boolean removeInMP = false;
   private List<String> freeRecipes = new ArrayList<>();
   public ArrayList<String> MutuallyExclusive = new ArrayList<>(0);
   public HashMap<Perk, Integer> XPBoostMap = new HashMap<>();

   public void addXPBoost(Perk var1, int var2) {
      if (var1 != null && var1 != Perks.None && var1 != Perks.MAX) {
         this.XPBoostMap.put(var1, var2);
      } else {
         DebugLog.General.warn("invalid perk passed to Trait.addXPBoost trait=%s perk=%s", new Object[]{this.name, var1});
      }
   }

   public List<String> getFreeRecipes() {
      return this.freeRecipes;
   }

   public void setFreeRecipes(List<String> var1) {
      this.freeRecipes = var1;
   }

   public TraitFactory$Trait(String var1, String var2, int var3, String var4, boolean var5, boolean var6) {
      this.traitID = var1;
      this.name = var2;
      this.cost = var3;
      this.description = var4;
      this.prof = var5;
      this.texture = Texture.getSharedTexture("media/ui/Traits/trait_" + this.traitID.toLowerCase(Locale.ENGLISH) + ".png");
      if (this.texture == null) {
         this.texture = Texture.getSharedTexture("media/ui/Traits/trait_generic.png");
      }

      this.removeInMP = var6;
   }

   public String getType() {
      return this.traitID;
   }

   public Texture getTexture() {
      return this.texture;
   }

   public String getLabel() {
      return this.name;
   }

   public String getLeftLabel() {
      return this.name;
   }

   public String getRightLabel() {
      int var1 = this.cost;
      if (var1 == 0) {
         return "";
      } else {
         String var2 = "+";
         if (var1 > 0) {
            var2 = "-";
         } else if (var1 == 0) {
            var2 = "";
         }

         if (var1 < 0) {
            var1 = -var1;
         }

         return var2 + new Integer(var1).toString();
      }
   }

   public int getCost() {
      return this.cost;
   }

   public boolean isFree() {
      return this.prof;
   }

   public String getDescription() {
      return this.description;
   }

   public void setDescription(String var1) {
      this.description = var1;
   }

   public ArrayList<String> getMutuallyExclusiveTraits() {
      return this.MutuallyExclusive;
   }

   public HashMap<Perk, Integer> getXPBoostMap() {
      return this.XPBoostMap;
   }

   public boolean isRemoveInMP() {
      return this.removeInMP;
   }

   public void setRemoveInMP(boolean var1) {
      this.removeInMP = var1;
   }
}
