package zombie.vehicles;

import zombie.vehicles.CircleLineIntersect.Vector;

class CircleLineIntersect$Collider {
   private Object collideobj;
   private Integer collideindex;
   private Vector collideforce;

   public CircleLineIntersect$Collider(Vector var1, Integer var2) {
      this.collideobj = var1;
      this.collideindex = var2;
      this.collideforce = var1;
   }

   public CircleLineIntersect$Collider(Object var1, Integer var2, Vector var3) {
      this.collideobj = var1;
      this.collideindex = var2;
      this.collideforce = var3;
   }

   public Object getCollideobj() {
      return this.collideobj;
   }

   public Integer getCollidewith() {
      return this.collideindex;
   }

   public Vector getCollideforce() {
      return this.collideforce;
   }

   public void setCollideforce(Vector var1) {
      this.collideforce = var1;
   }

   @Override
   public String toString() {
      return this.collideobj.getClass().getSimpleName() + " @ " + this.collideindex + " hit with " + this.collideforce.toString();
   }
}
