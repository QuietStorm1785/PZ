package zombie.iso;

import zombie.GameTime;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.iso.areas.IsoRoom;

public class IsoCamera$FrameState {
   public int frameCount;
   public boolean Paused;
   public int playerIndex;
   public float CamCharacterX;
   public float CamCharacterY;
   public float CamCharacterZ;
   public IsoGameCharacter CamCharacter;
   public IsoGridSquare CamCharacterSquare;
   public IsoRoom CamCharacterRoom;
   public float OffX;
   public float OffY;
   public int OffscreenWidth;
   public int OffscreenHeight;

   public void set(int var1) {
      this.Paused = GameTime.isGamePaused();
      this.playerIndex = var1;
      this.CamCharacter = IsoPlayer.players[var1];
      this.CamCharacterX = this.CamCharacter.getX();
      this.CamCharacterY = this.CamCharacter.getY();
      this.CamCharacterZ = this.CamCharacter.getZ();
      this.CamCharacterSquare = this.CamCharacter.getCurrentSquare();
      this.CamCharacterRoom = this.CamCharacterSquare == null ? null : this.CamCharacterSquare.getRoom();
      this.OffX = IsoCamera.getOffX();
      this.OffY = IsoCamera.getOffY();
      this.OffscreenWidth = IsoCamera.getOffscreenWidth(var1);
      this.OffscreenHeight = IsoCamera.getOffscreenHeight(var1);
   }
}
