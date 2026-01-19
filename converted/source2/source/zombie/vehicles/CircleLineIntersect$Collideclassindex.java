package zombie.vehicles;

import java.util.ArrayList;
import zombie.vehicles.CircleLineIntersect.Collider;
import zombie.vehicles.CircleLineIntersect.ForceCircle;
import zombie.vehicles.CircleLineIntersect.Vector;

class CircleLineIntersect$Collideclassindex {
   private ArrayList<Collider> colliders = new ArrayList<>(1);
   private int numforcecircles;

   public CircleLineIntersect$Collideclassindex() {
      this.numforcecircles = 0;
   }

   public CircleLineIntersect$Collideclassindex(Object var1, int var2, Vector var3) {
      this.colliders.add(new Collider(var1, var2, var3));
   }

   public boolean collided() {
      return this.size() > 0;
   }

   public void reset() {
      this.colliders.trimToSize();
      this.colliders.clear();
      this.numforcecircles = 0;
   }

   public void setCollided(Object var1, int var2, Vector var3) {
      if (this.size() > 0) {
         this.reset();
      }

      if (var1 instanceof ForceCircle && !((ForceCircle)var1).isFrozen()) {
         this.numforcecircles++;
      }

      this.colliders.add(new Collider(var1, var2, var3));
   }

   public void addCollided(Object var1, int var2, Vector var3) {
      if (var1 instanceof ForceCircle && !((ForceCircle)var1).isFrozen()) {
         this.numforcecircles++;
      }

      this.colliders.add(new Collider(var1, var2, var3));
   }

   public ArrayList<Collider> getColliders() {
      return this.colliders;
   }

   public int getNumforcecircles() {
      return this.numforcecircles;
   }

   public Collider contains(Object var1) {
      for (Collider var3 : this.colliders) {
         if (var3.getCollideobj().equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public int size() {
      return this.colliders.size();
   }

   @Override
   public String toString() {
      String var1 = "";

      for (Collider var3 : this.colliders) {
         var1 = var1 + var3.toString() + "\n";
      }

      return var1;
   }
}
