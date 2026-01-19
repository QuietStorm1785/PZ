package zombie.gameStates;

import zombie.gameStates.GameStateMachine.StateAction;

public class GameState {
   public void enter() {
   }

   public void exit() {
   }

   public void render() {
   }

   public GameState redirectState() {
      return null;
   }

   public StateAction update() {
      return StateAction.Continue;
   }

   public void yield() {
   }

   public void reenter() {
   }
}
