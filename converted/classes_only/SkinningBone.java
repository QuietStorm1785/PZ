package zombie.core.skinnedmodel.model;

import java.util.function.Consumer;

public final class SkinningBone {
   public SkinningBone Parent;
   public String Name;
   public int Index;
   public SkinningBone[] Children;

   public void forEachDescendant(Consumer<SkinningBone> var1) {
      forEachDescendant(this, var1);
   }

   private static void forEachDescendant(SkinningBone var0, Consumer<SkinningBone> var1) {
      if (var0.Children != null && var0.Children.length != 0) {
         for (SkinningBone var5 : var0.Children) {
            var1.accept(var5);
         }

         for (SkinningBone var9 : var0.Children) {
            forEachDescendant(var9, var1);
         }
      }
   }

   @Override
   public String toString() {
      String var1 = System.lineSeparator();
      return this.getClass().getName() + var1 + "{" + var1 + "\tName:\"" + this.Name + "\"" + var1 + "\tIndex:" + this.Index + var1 + "}";
   }
}
