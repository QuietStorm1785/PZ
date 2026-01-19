package zombie;

import zombie.audio.GameSoundClip;

interface GameSounds$IPreviewSound {
   boolean play(GameSoundClip var1);

   boolean isPlaying();

   boolean update();

   void stop();
}
