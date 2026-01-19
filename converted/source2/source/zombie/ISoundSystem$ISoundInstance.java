package zombie;

public interface ISoundSystem$ISoundInstance {
   boolean isStreamed();

   boolean isLooped();

   boolean isPlaying();

   int countInstances();

   void setLooped(boolean var1);

   void pause();

   void stop();

   void play();

   void blendVolume(float var1, float var2, boolean var3);

   void setVolume(float var1);

   float getVolume();

   void setPanning(float var1);

   float getPanning();

   void setPitch(float var1);

   float getPitch();

   boolean disposed();
}
