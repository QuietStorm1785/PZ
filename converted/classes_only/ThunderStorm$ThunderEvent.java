package zombie.iso.weather;

import zombie.GameTime.AnimTimer;

class ThunderStorm$ThunderEvent {
   private int eventX;
   private int eventY;
   private boolean doLightning = false;
   private boolean doRumble = false;
   private boolean doStrike = false;
   private AnimTimer soundDelay = new AnimTimer();
   private boolean isRunning = false;

   private ThunderStorm$ThunderEvent() {
   }
}
