package zombie.network;

public enum NetworkVariables$ZombieState {
   Attack("attack"),
   AttackNetwork("attack-network"),
   AttackVehicle("attackvehicle"),
   AttackVehicleNetwork("attackvehicle-network"),
   Bumped("bumped"),
   ClimbFence("climbfence"),
   ClimbWindow("climbwindow"),
   EatBody("eatbody"),
   FaceTarget("face-target"),
   FakeDead("fakedead"),
   FakeDeadAttack("fakedead-attack"),
   FakeDeadAttackNetwork("fakedead-attack-network"),
   FallDown("falldown"),
   Falling("falling"),
   GetDown("getdown"),
   Getup("getup"),
   HitReaction("hitreaction"),
   HitReactionHit("hitreaction-hit"),
   HitWhileStaggered("hitwhilestaggered"),
   Idle("idle"),
   Lunge("lunge"),
   LungeNetwork("lunge-network"),
   OnGround("onground"),
   PathFind("pathfind"),
   Sitting("sitting"),
   StaggerBack("staggerback"),
   Thump("thump"),
   TurnAlerted("turnalerted"),
   WalkToward("walktoward"),
   WalkTowardNetwork("walktoward-network"),
   FakeZombieStay("fakezombie-stay"),
   FakeZombieNormal("fakezombie-normal"),
   FakeZombieAttack("fakezombie-attack");

   private final String zombieState;

   private NetworkVariables$ZombieState(String var3) {
      this.zombieState = var3;
   }

   @Override
   public String toString() {
      return this.zombieState;
   }

   public static NetworkVariables$ZombieState fromString(String var0) {
      for (NetworkVariables$ZombieState var4 : values()) {
         if (var4.zombieState.equalsIgnoreCase(var0)) {
            return var4;
         }
      }

      return Idle;
   }

   public static NetworkVariables$ZombieState fromByte(Byte var0) {
      for (NetworkVariables$ZombieState var4 : values()) {
         if (var4.ordinal() == var0) {
            return var4;
         }
      }

      return Idle;
   }
}
