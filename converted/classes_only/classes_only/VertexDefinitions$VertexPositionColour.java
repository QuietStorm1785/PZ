package zombie.core.skinnedmodel.model;

import zombie.core.Color;
import zombie.core.skinnedmodel.HelperFunctions;
import zombie.core.skinnedmodel.Vector3;

class VertexDefinitions$VertexPositionColour {
   public Vector3 Position;
   public int Colour;

   public VertexDefinitions$VertexPositionColour(VertexDefinitions var1, Vector3 var2, Color var3) {
      this.this$0 = var1;
      this.Position = var2;
      this.Colour = HelperFunctions.ToRgba(var3);
   }

   public VertexDefinitions$VertexPositionColour(VertexDefinitions var1, float var2, float var3, float var4, Color var5) {
      this.this$0 = var1;
      this.Position = new Vector3(var2, var3, var4);
      this.Colour = HelperFunctions.ToRgba(var5);
   }
}
