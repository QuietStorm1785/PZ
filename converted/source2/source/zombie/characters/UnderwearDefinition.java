package zombie.characters;

import java.util.ArrayList;
import se.krka.kahlua.j2se.KahluaTableImpl;
import se.krka.kahlua.vm.KahluaTableIterator;
import zombie.Lua.LuaManager;
import zombie.characters.UnderwearDefinition.OutfitUnderwearDefinition;
import zombie.characters.UnderwearDefinition.StringChance;
import zombie.core.Rand;
import zombie.core.skinnedmodel.population.OutfitRNG;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item;
import zombie.util.Type;

public class UnderwearDefinition {
   public static final UnderwearDefinition instance = new UnderwearDefinition();
   public boolean m_dirty = true;
   private static final ArrayList<OutfitUnderwearDefinition> m_outfitDefinition = new ArrayList<>();
   private static int baseChance = 50;

   public void checkDirty() {
      this.init();
   }

   private void init() {
      m_outfitDefinition.clear();
      KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("UnderwearDefinition");
      if (var1 != null) {
         baseChance = var1.rawgetInt("baseChance");
         KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
            ArrayList var3 = null;
            KahluaTableImpl var4 = (KahluaTableImpl)Type.tryCastTo(var2.getValue(), KahluaTableImpl.class);
            if (var4 != null) {
               KahluaTableImpl var5 = (KahluaTableImpl)Type.tryCastTo(var4.rawget("top"), KahluaTableImpl.class);
               if (var5 != null) {
                  var3 = new ArrayList();
                  KahluaTableIterator var6 = var5.iterator();

                  while (var6.advance()) {
                     KahluaTableImpl var7 = (KahluaTableImpl)Type.tryCastTo(var6.getValue(), KahluaTableImpl.class);
                     if (var7 != null) {
                        var3.add(new StringChance(var7.rawgetStr("name"), var7.rawgetFloat("chance")));
                     }
                  }
               }

               OutfitUnderwearDefinition var8 = new OutfitUnderwearDefinition(
                  var3, var4.rawgetStr("bottom"), var4.rawgetInt("chanceToSpawn"), var4.rawgetStr("gender")
               );
               m_outfitDefinition.add(var8);
            }
         }
      }
   }

   public static void addRandomUnderwear(IsoZombie var0) {
      instance.checkDirty();
      if (Rand.Next(100) <= baseChance) {
         ArrayList var1 = new ArrayList();
         int var2 = 0;

         for (int var3 = 0; var3 < m_outfitDefinition.size(); var3++) {
            OutfitUnderwearDefinition var4 = m_outfitDefinition.get(var3);
            if (var0.isFemale() && var4.female || !var0.isFemale() && !var4.female) {
               var1.add(var4);
               var2 += var4.chanceToSpawn;
            }
         }

         int var11 = OutfitRNG.Next(var2);
         OutfitUnderwearDefinition var13 = null;
         int var5 = 0;

         for (int var6 = 0; var6 < var1.size(); var6++) {
            OutfitUnderwearDefinition var7 = (OutfitUnderwearDefinition)var1.get(var6);
            var5 += var7.chanceToSpawn;
            if (var11 < var5) {
               var13 = var7;
               break;
            }
         }

         if (var13 != null) {
            Item var15 = ScriptManager.instance.FindItem(var13.bottom);
            ItemVisual var17 = null;
            if (var15 != null) {
               var17 = var0.getHumanVisual().addClothingItem(var0.getItemVisuals(), var15);
            }

            if (var13.top != null) {
               String var8 = null;
               var11 = OutfitRNG.Next(var13.topTotalChance);
               var5 = 0;

               for (int var9 = 0; var9 < var13.top.size(); var9++) {
                  StringChance var10 = (StringChance)var13.top.get(var9);
                  var5 = (int)(var5 + var10.chance);
                  if (var11 < var5) {
                     var8 = var10.str;
                     break;
                  }
               }

               if (var8 != null) {
                  var15 = ScriptManager.instance.FindItem(var8);
                  if (var15 != null) {
                     ItemVisual var18 = var0.getHumanVisual().addClothingItem(var0.getItemVisuals(), var15);
                     if (Rand.Next(100) < 60 && var18 != null && var17 != null) {
                        var18.setTint(var17.getTint());
                     }
                  }
               }
            }
         }
      }
   }
}
