package zombie.audio.parameters;

public enum ParameterMusicState$State {
   MainMenu(0),
   Loading(1),
   InGame(2),
   PauseMenu(3),
   Tutorial(4);

   final int label;

   private ParameterMusicState$State(int var3) {
      this.label = var3;
   }
}
