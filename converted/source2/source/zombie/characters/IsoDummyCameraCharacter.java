package zombie.characters;

import zombie.iso.IsoCamera;

public final class IsoDummyCameraCharacter extends IsoGameCharacter {
   public IsoDummyCameraCharacter(float var1, float var2, float var3) {
      super(null, var1, var2, var3);
      IsoCamera.CamCharacter = this;
   }

   public void update() {
   }
}
