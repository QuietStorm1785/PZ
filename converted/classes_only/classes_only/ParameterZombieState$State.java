package zombie.audio.parameters;

public enum ParameterZombieState$State {
   Idle(0),
   Eating(1),
   SearchTarget(2),
   LockTarget(3),
   AttackScratch(4),
   AttackLacerate(5),
   AttackBite(6),
   Hit(7),
   Death(8),
   Reanimate(9),
   Pushed(10),
   GettingUp(11),
   Attack(12),
   RunOver(13);

   final int index;

   private ParameterZombieState$State(int var3) {
      this.index = var3;
   }
}
