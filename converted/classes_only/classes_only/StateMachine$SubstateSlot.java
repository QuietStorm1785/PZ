package zombie.ai;

public class StateMachine$SubstateSlot {
   private State state;
   boolean shouldBeActive;

   StateMachine$SubstateSlot(State var1) {
      this.state = var1;
      this.shouldBeActive = true;
   }

   public State getState() {
      return this.state;
   }

   void setState(State var1) {
      this.state = var1;
   }

   public boolean isEmpty() {
      return this.state == null;
   }
}
