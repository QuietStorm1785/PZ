package zombie.network;

final class GameServer$CCFilter {
   String command;
   boolean allow;
   GameServer$CCFilter next;

   private GameServer$CCFilter() {
   }

   boolean matches(String var1) {
      return this.command.equals(var1) || "*".equals(this.command);
   }

   boolean passes(String var1) {
      if (this.matches(var1)) {
         return this.allow;
      } else {
         return this.next == null ? true : this.next.passes(var1);
      }
   }
}
