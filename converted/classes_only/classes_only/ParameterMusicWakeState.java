package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.audio.parameters.ParameterMusicWakeState.State;
import zombie.characters.IsoPlayer;

public final class ParameterMusicWakeState extends FMODGlobalParameter {
   private int m_playerIndex = -1;
   private State m_state = State.Awake;

   public ParameterMusicWakeState() {
      super("MusicWakeState");
   }

   public float calculateCurrentValue() {
      IsoPlayer var1 = this.choosePlayer();
      if (var1 != null && this.m_state == State.Awake && var1.isAsleep()) {
         this.m_state = State.Sleeping;
      }

      return this.m_state.label;
   }

   public void setState(IsoPlayer var1, State var2) {
      if (var1 == this.choosePlayer()) {
         this.m_state = var2;
      }
   }

   private IsoPlayer choosePlayer() {
      if (this.m_playerIndex != -1) {
         IsoPlayer var1 = IsoPlayer.players[this.m_playerIndex];
         if (var1 == null || var1.isDead()) {
            this.m_playerIndex = -1;
         }
      }

      if (this.m_playerIndex != -1) {
         return IsoPlayer.players[this.m_playerIndex];
      } else {
         for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
            IsoPlayer var2 = IsoPlayer.players[var3];
            if (var2 != null && !var2.isDead()) {
               this.m_playerIndex = var3;
               this.m_state = var2.isAsleep() ? State.Sleeping : State.Awake;
               return var2;
            }
         }

         return null;
      }
   }
}
