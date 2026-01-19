package zombie.scripting.objects;

import zombie.core.BoxedStaticValues;

public final class VehicleScript$Area {
   public String id;
   public float x;
   public float y;
   public float w;
   public float h;

   public String getId() {
      return this.id;
   }

   public Double getX() {
      return BoxedStaticValues.toDouble(this.x);
   }

   public Double getY() {
      return BoxedStaticValues.toDouble(this.y);
   }

   public Double getW() {
      return BoxedStaticValues.toDouble(this.w);
   }

   public Double getH() {
      return BoxedStaticValues.toDouble(this.h);
   }

   public void setX(Double var1) {
      this.x = var1.floatValue();
   }

   public void setY(Double var1) {
      this.y = var1.floatValue();
   }

   public void setW(Double var1) {
      this.w = var1.floatValue();
   }

   public void setH(Double var1) {
      this.h = var1.floatValue();
   }

   private VehicleScript$Area makeCopy() {
      VehicleScript$Area var1 = new VehicleScript$Area();
      var1.id = this.id;
      var1.x = this.x;
      var1.y = this.y;
      var1.w = this.w;
      var1.h = this.h;
      return var1;
   }
}
