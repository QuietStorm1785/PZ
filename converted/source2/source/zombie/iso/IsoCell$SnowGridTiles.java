package zombie.iso;

import java.util.ArrayList;
import zombie.core.Rand;
import zombie.core.textures.Texture;

public class IsoCell$SnowGridTiles {
   protected byte ID;
   private int counter;
   private final ArrayList<Texture> textures;

   public IsoCell$SnowGridTiles(IsoCell var1, byte var2) {
      this.this$0 = var1;
      this.ID = -1;
      this.counter = -1;
      this.textures = new ArrayList<>();
      this.ID = var2;
   }

   protected void add(Texture var1) {
      this.textures.add(var1);
   }

   protected Texture getNext() {
      this.counter++;
      if (this.counter >= this.textures.size()) {
         this.counter = 0;
      }

      return this.textures.get(this.counter);
   }

   protected Texture get(int var1) {
      return this.textures.get(var1);
   }

   protected int size() {
      return this.textures.size();
   }

   protected Texture getRand() {
      return this.textures.get(Rand.Next(4));
   }

   protected boolean contains(Texture var1) {
      return this.textures.contains(var1);
   }

   protected void resetCounter() {
      this.counter = 0;
   }
}
