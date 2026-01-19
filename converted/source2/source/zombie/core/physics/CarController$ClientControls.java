package zombie.core.physics;

public final class CarController$ClientControls {
   public float steering;
   public boolean forward;
   public boolean backward;
   public boolean brake;
   public boolean shift;
   public boolean wasUsingParkingBrakes;
   public long forceBrake = 0L;

   public void reset() {
      this.steering = 0.0F;
      this.forward = false;
      this.backward = false;
      this.brake = false;
      this.shift = false;
      this.wasUsingParkingBrakes = false;
      this.forceBrake = 0L;
   }
}
