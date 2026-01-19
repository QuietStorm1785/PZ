package zombie.iso;

import zombie.core.textures.ColorInfo;
import zombie.iso.IsoGridSquare.ResultLight;

public interface IsoGridSquare$ILighting {
   int lightverts(int var1);

   float lampostTotalR();

   float lampostTotalG();

   float lampostTotalB();

   boolean bSeen();

   boolean bCanSee();

   boolean bCouldSee();

   float darkMulti();

   float targetDarkMulti();

   ColorInfo lightInfo();

   void lightverts(int var1, int var2);

   void lampostTotalR(float var1);

   void lampostTotalG(float var1);

   void lampostTotalB(float var1);

   void bSeen(boolean var1);

   void bCanSee(boolean var1);

   void bCouldSee(boolean var1);

   void darkMulti(float var1);

   void targetDarkMulti(float var1);

   int resultLightCount();

   ResultLight getResultLight(int var1);

   void reset();
}
