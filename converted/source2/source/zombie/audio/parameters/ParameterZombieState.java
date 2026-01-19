package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.audio.parameters.ParameterZombieState.State;
import zombie.characters.IsoZombie;

public final class ParameterZombieState extends FMODLocalParameter {
   private final IsoZombie zombie;
   private State state = State.Idle;

   public ParameterZombieState(IsoZombie var1) {
      super("ZombieState");
      this.zombie = var1;
   }

   public float calculateCurrentValue() {
      if (this.zombie.target == null) {
         if (this.state == State.SearchTarget) {
            this.setState(State.Idle);
         }
      } else if (this.state == State.Idle) {
         this.setState(State.SearchTarget);
      }

      return this.state.index;
   }

   public void setState(State var1) {
      if (var1 != this.state) {
         this.state = var1;
      }
   }

   public boolean isState(State var1) {
      return this.state == var1;
   }
}
