package zombie.ui;

import zombie.GameTime;
import zombie.SoundManager;
import zombie.core.Core;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.ui.SpeedControls.SCButton;

public final class SpeedControls extends UIElement {
   public static SpeedControls instance = null;
   public int CurrentSpeed = 1;
   public int SpeedBeforePause = 1;
   public float MultiBeforePause = 1.0F;
   float alpha = 1.0F;
   boolean MouseOver = false;
   public static HUDButton Play;
   public static HUDButton Pause;
   public static HUDButton FastForward;
   public static HUDButton FasterForward;
   public static HUDButton Wait;

   public SpeedControls() {
      this.x = 0.0;
      this.y = 0.0;
      byte var1 = 2;
      Pause = new SCButton("Pause", 1.0F, 0.0F, "media/ui/Time_Pause_Off.png", "media/ui/Time_Pause_On.png", this);
      Play = new SCButton("Play", (float)(Pause.x + Pause.width + var1), 0.0F, "media/ui/Time_Play_Off.png", "media/ui/Time_Play_On.png", this);
      FastForward = new SCButton(
         "Fast Forward x 1", (float)(Play.x + Play.width + var1), 0.0F, "media/ui/Time_FFwd1_Off.png", "media/ui/Time_FFwd1_On.png", this
      );
      FasterForward = new SCButton(
         "Fast Forward x 2", (float)(FastForward.x + FastForward.width + var1), 0.0F, "media/ui/Time_FFwd2_Off.png", "media/ui/Time_FFwd2_On.png", this
      );
      Wait = new SCButton("Wait", (float)(FasterForward.x + FasterForward.width + var1), 0.0F, "media/ui/Time_Wait_Off.png", "media/ui/Time_Wait_On.png", this);
      this.width = (int)Wait.x + Wait.width;
      this.height = Wait.height;
      this.AddChild(Pause);
      this.AddChild(Play);
      this.AddChild(FastForward);
      this.AddChild(FasterForward);
      this.AddChild(Wait);
   }

   public void ButtonClicked(String var1) {
      GameTime.instance.setMultiplier(1.0F);
      if ("Pause".equals(var1)) {
         if (this.CurrentSpeed > 0) {
            this.SetCurrentGameSpeed(0);
         } else {
            this.SetCurrentGameSpeed(5);
         }
      }

      if ("Play".equals(var1)) {
         this.SetCurrentGameSpeed(1);
         GameTime.instance.setMultiplier(1.0F);
      }

      if ("Fast Forward x 1".equals(var1)) {
         this.SetCurrentGameSpeed(2);
         GameTime.instance.setMultiplier(5.0F);
      }

      if ("Fast Forward x 2".equals(var1)) {
         this.SetCurrentGameSpeed(3);
         GameTime.instance.setMultiplier(20.0F);
      }

      if ("Wait".equals(var1)) {
         this.SetCurrentGameSpeed(4);
         GameTime.instance.setMultiplier(40.0F);
      }
   }

   public int getCurrentGameSpeed() {
      return !GameClient.bClient && !GameServer.bServer ? this.CurrentSpeed : 1;
   }

   public void SetCorrectIconStates() {
      if (this.CurrentSpeed == 0) {
         super.ButtonClicked("Pause");
      }

      if (this.CurrentSpeed == 1) {
         super.ButtonClicked("Play");
      }

      if (GameTime.instance.getTrueMultiplier() == 5.0F) {
         super.ButtonClicked("Fast Forward x 1");
      }

      if (GameTime.instance.getTrueMultiplier() == 20.0F) {
         super.ButtonClicked("Fast Forward x 2");
      }

      if (GameTime.instance.getTrueMultiplier() == 40.0F) {
         super.ButtonClicked("Wait");
      }
   }

   public void SetCurrentGameSpeed(int var1) {
      if (this.CurrentSpeed > 0 && var1 == 0) {
         SoundManager.instance.pauseSoundAndMusic();
         SoundManager.instance.setMusicState("PauseMenu");
      } else if (this.CurrentSpeed == 0 && var1 > 0) {
         SoundManager.instance.setMusicState("InGame");
         SoundManager.instance.resumeSoundAndMusic();
      }

      GameTime.instance.setMultiplier(1.0F);
      if (var1 == 0) {
         this.SpeedBeforePause = this.CurrentSpeed;
         this.MultiBeforePause = GameTime.instance.getMultiplier();
      }

      if (var1 == 5) {
         var1 = this.SpeedBeforePause;
         GameTime.instance.setMultiplier(this.MultiBeforePause);
      }

      this.CurrentSpeed = var1;
      this.SetCorrectIconStates();
   }

   public Boolean onMouseMove(double var1, double var3) {
      if (!this.isVisible()) {
         return false;
      } else {
         this.MouseOver = true;
         super.onMouseMove(var1, var3);
         this.SetCorrectIconStates();
         return Boolean.TRUE;
      }
   }

   public void onMouseMoveOutside(double var1, double var3) {
      super.onMouseMoveOutside(var1, var3);
      this.MouseOver = false;
      this.SetCorrectIconStates();
   }

   public void render() {
      super.render();
      if ("Tutorial".equals(Core.GameMode)) {
         Pause.setVisible(false);
         Play.setVisible(false);
         FastForward.setVisible(false);
         FasterForward.setVisible(false);
         Wait.setVisible(false);
      }

      this.SetCorrectIconStates();
   }

   public void update() {
      super.update();
      this.SetCorrectIconStates();
   }
}
