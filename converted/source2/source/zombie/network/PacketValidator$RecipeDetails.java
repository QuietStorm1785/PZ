package zombie.network;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.stream.Collectors;
import zombie.GameWindow;
import zombie.core.network.ByteBufferWriter;
import zombie.network.PacketValidator.RecipeDetails.Skill;
import zombie.scripting.objects.Recipe.RequiredSkill;
import zombie.scripting.objects.Recipe.Source;

public class PacketValidator$RecipeDetails {
   private final String name;
   private final long crc;
   private final int timeToMake;
   private final ArrayList<Skill> skills = new ArrayList<>();
   private final ArrayList<String> items = new ArrayList<>();
   private final String type;
   private final String module;
   private final int count;

   public long getCRC() {
      return this.crc;
   }

   public PacketValidator$RecipeDetails(
      String var1, long var2, int var4, ArrayList<RequiredSkill> var5, ArrayList<Source> var6, String var7, String var8, int var9
   ) {
      this.name = var1;
      this.crc = var2;
      this.timeToMake = var4;
      this.type = var7;
      this.module = var8;
      this.count = var9;
      if (var5 != null) {
         for (RequiredSkill var11 : var5) {
            this.skills.add(new Skill(var11.getPerk().getName(), var11.getLevel()));
         }
      }

      for (Source var13 : var6) {
         this.items.addAll(var13.getItems());
      }
   }

   public PacketValidator$RecipeDetails(ByteBuffer var1) {
      this.name = GameWindow.ReadString(var1);
      this.crc = var1.getLong();
      this.timeToMake = var1.getInt();
      this.type = GameWindow.ReadString(var1);
      this.module = GameWindow.ReadString(var1);
      this.count = var1.getInt();
      int var2 = var1.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
         this.items.add(GameWindow.ReadString(var1));
      }

      int var5 = var1.getInt();

      for (int var4 = 0; var4 < var5; var4++) {
         this.skills.add(new Skill(GameWindow.ReadString(var1), var1.getInt()));
      }
   }

   public void write(ByteBufferWriter var1) {
      var1.putUTF(this.name);
      var1.putLong(this.crc);
      var1.putInt(this.timeToMake);
      var1.putUTF(this.type);
      var1.putUTF(this.module);
      var1.putInt(this.count);
      var1.putInt(this.items.size());

      for (String var3 : this.items) {
         var1.putUTF(var3);
      }

      var1.putInt(this.skills.size());

      for (Skill var5 : this.skills) {
         var1.putUTF(var5.name);
         var1.putInt(var5.value);
      }
   }

   public String getDescription() {
      return "\n\tRecipe: name=\""
         + this.name
         + "\" crc="
         + this.crc
         + " time="
         + this.timeToMake
         + " type=\""
         + this.type
         + "\" module=\""
         + this.module
         + "\" count="
         + this.count
         + " items=["
         + String.join(",", this.items)
         + "] skills=["
         + this.skills.stream().map(var0 -> "\"" + var0.name + "\": " + var0.value).collect(Collectors.joining(","))
         + "]";
   }
}
