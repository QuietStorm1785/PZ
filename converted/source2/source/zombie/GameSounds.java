package zombie;

import fmod.javafmod;
import fmod.javafmodJNI;
import fmod.fmod.FMODFootstep;
import fmod.fmod.FMODManager;
import fmod.fmod.FMODSoundBank;
import fmod.fmod.FMODVoice;
import fmod.fmod.FMOD_STUDIO_EVENT_DESCRIPTION;
import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import zombie.GameSounds.BankPreviewSound;
import zombie.GameSounds.FilePreviewSound;
import zombie.GameSounds.IPreviewSound;
import zombie.audio.BaseSoundBank;
import zombie.audio.GameSound;
import zombie.audio.GameSoundClip;
import zombie.characters.IsoPlayer;
import zombie.config.ConfigFile;
import zombie.config.ConfigOption;
import zombie.config.DoubleConfigOption;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.debug.DebugLog;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.GameSoundScript;
import zombie.util.StringUtils;

public final class GameSounds {
   public static final int VERSION = 1;
   protected static final HashMap<String, GameSound> soundByName = new HashMap<>();
   protected static final ArrayList<GameSound> sounds = new ArrayList<>();
   private static final BankPreviewSound previewBank = new BankPreviewSound();
   private static final FilePreviewSound previewFile = new FilePreviewSound();
   public static boolean soundIsPaused = false;
   private static IPreviewSound previewSound;

   public static void addSound(GameSound var0) {
      initClipEvents(var0);

      assert !sounds.contains(var0);

      int var1 = sounds.size();
      if (soundByName.containsKey(var0.getName())) {
         var1 = 0;

         while (var1 < sounds.size() && !sounds.get(var1).getName().equals(var0.getName())) {
            var1++;
         }

         sounds.remove(var1);
      }

      sounds.add(var1, var0);
      soundByName.put(var0.getName(), var0);
   }

   private static void initClipEvents(GameSound var0) {
      if (!GameServer.bServer) {
         for (GameSoundClip var2 : var0.clips) {
            if (var2.event != null && var2.eventDescription == null) {
               var2.eventDescription = FMODManager.instance.getEventDescription("event:/" + var2.event);
               if (var2.eventDescription == null) {
                  DebugLog.Sound.warn("No such FMOD event \"%s\" for GameSound \"%s\"", new Object[]{var2.event, var0.getName()});
               }

               var2.eventDescriptionMP = FMODManager.instance.getEventDescription("event:/Remote/" + var2.event);
               if (var2.eventDescriptionMP != null) {
                  DebugLog.Sound.println("MP event %s", var2.eventDescriptionMP.path);
               }
            }
         }
      }
   }

   public static boolean isKnownSound(String var0) {
      return soundByName.containsKey(var0);
   }

   public static GameSound getSound(String var0) {
      return getOrCreateSound(var0);
   }

   public static GameSound getOrCreateSound(String var0) {
      if (StringUtils.isNullOrEmpty(var0)) {
         return null;
      } else {
         GameSound var1 = soundByName.get(var0);
         if (var1 == null) {
            DebugLog.General.warn("no GameSound called \"" + var0 + "\", adding a new one");
            var1 = new GameSound();
            var1.name = var0;
            var1.category = "AUTO";
            GameSoundClip var2 = new GameSoundClip(var1);
            var1.clips.add(var2);
            sounds.add(var1);
            soundByName.put(var0.replace(".wav", "").replace(".ogg", ""), var1);
            if (BaseSoundBank.instance instanceof FMODSoundBank) {
               FMOD_STUDIO_EVENT_DESCRIPTION var3 = FMODManager.instance.getEventDescription("event:/" + var0);
               if (var3 != null) {
                  var2.event = var0;
                  var2.eventDescription = var3;
                  var2.eventDescriptionMP = FMODManager.instance.getEventDescription("event:/Remote/" + var0);
               } else {
                  String var4 = null;
                  if (ZomboidFileSystem.instance.getAbsolutePath("media/sound/" + var0 + ".ogg") != null) {
                     var4 = "media/sound/" + var0 + ".ogg";
                  } else if (ZomboidFileSystem.instance.getAbsolutePath("media/sound/" + var0 + ".wav") != null) {
                     var4 = "media/sound/" + var0 + ".wav";
                  }

                  if (var4 != null) {
                     long var5 = FMODManager.instance.loadSound(var4);
                     if (var5 != 0L) {
                        var2.file = var4;
                     }
                  }
               }

               if (var2.event == null && var2.file == null) {
                  DebugLog.General.warn("couldn't find an FMOD event or .ogg or .wav file for sound \"" + var0 + "\"");
               }
            }
         }

         return var1;
      }
   }

   private static void loadNonBankSounds() {
      if (BaseSoundBank.instance instanceof FMODSoundBank) {
         for (GameSound var1 : sounds) {
            for (GameSoundClip var3 : var1.clips) {
               if (var3.getFile() != null && var3.getFile().isEmpty()) {
               }
            }
         }
      }
   }

   public static void ScriptsLoaded() {
      ArrayList var0 = ScriptManager.instance.getAllGameSounds();

      for (int var1 = 0; var1 < var0.size(); var1++) {
         GameSoundScript var2 = (GameSoundScript)var0.get(var1);
         if (!var2.gameSound.clips.isEmpty()) {
            addSound(var2.gameSound);
         }
      }

      var0.clear();
      loadNonBankSounds();
      loadINI();
      if (Core.bDebug && BaseSoundBank.instance instanceof FMODSoundBank) {
         HashSet var12 = new HashSet();

         for (GameSound var3 : sounds) {
            for (GameSoundClip var5 : var3.clips) {
               if (var5.getEvent() != null && !var5.getEvent().isEmpty()) {
                  var12.add(var5.getEvent());
               }
            }
         }

         FMODSoundBank var14 = (FMODSoundBank)BaseSoundBank.instance;

         for (FMODFootstep var18 : var14.footstepMap.values()) {
            var12.add(var18.wood);
            var12.add(var18.concrete);
            var12.add(var18.grass);
            var12.add(var18.upstairs);
            var12.add(var18.woodCreak);
         }

         for (FMODVoice var19 : var14.voiceMap.values()) {
            var12.add(var19.sound);
         }

         ArrayList var17 = new ArrayList();
         long[] var20 = new long[32];
         long[] var21 = new long[1024];
         int var6 = javafmodJNI.FMOD_Studio_System_GetBankList(var20);

         for (int var7 = 0; var7 < var6; var7++) {
            int var8 = javafmodJNI.FMOD_Studio_Bank_GetEventList(var20[var7], var21);

            for (int var9 = 0; var9 < var8; var9++) {
               try {
                  String var10 = javafmodJNI.FMOD_Studio_EventDescription_GetPath(var21[var9]);
                  var10 = var10.replace("event:/", "");
                  if (!var12.contains(var10)) {
                     var17.add(var10);
                  }
               } catch (Exception var11) {
                  DebugLog.General.warn("FMOD cannot get path for " + var21[var9] + " event");
               }
            }
         }

         var17.sort(String::compareTo);

         for (String var23 : var17) {
            DebugLog.General.warn("FMOD event \"%s\" not used by any GameSound", new Object[]{var23});
         }
      }
   }

   public static void ReloadFile(String var0) {
      try {
         ScriptManager.instance.LoadFile(var0, true);
         ArrayList var1 = ScriptManager.instance.getAllGameSounds();

         for (int var2 = 0; var2 < var1.size(); var2++) {
            GameSoundScript var3 = (GameSoundScript)var1.get(var2);
            if (sounds.contains(var3.gameSound)) {
               initClipEvents(var3.gameSound);
            } else if (!var3.gameSound.clips.isEmpty()) {
               addSound(var3.gameSound);
            }
         }
      } catch (Throwable var4) {
         ExceptionLogger.logException(var4);
      }
   }

   public static ArrayList<String> getCategories() {
      HashSet var0 = new HashSet();

      for (GameSound var2 : sounds) {
         var0.add(var2.getCategory());
      }

      ArrayList var3 = new ArrayList(var0);
      Collections.sort(var3);
      return var3;
   }

   public static ArrayList<GameSound> getSoundsInCategory(String var0) {
      ArrayList var1 = new ArrayList();

      for (GameSound var3 : sounds) {
         if (var3.getCategory().equals(var0)) {
            var1.add(var3);
         }
      }

      return var1;
   }

   public static void loadINI() {
      String var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "sounds.ini";
      ConfigFile var1 = new ConfigFile();
      if (var1.read(var0)) {
         if (var1.getVersion() <= 1) {
            for (ConfigOption var3 : var1.getOptions()) {
               GameSound var4 = soundByName.get(var3.getName());
               if (var4 != null) {
                  var4.setUserVolume(PZMath.tryParseFloat(var3.getValueAsString(), 1.0F));
               }
            }
         }
      }
   }

   public static void saveINI() {
      ArrayList var0 = new ArrayList();

      for (GameSound var2 : sounds) {
         DoubleConfigOption var3 = new DoubleConfigOption(var2.getName(), 0.0, 2.0, 0.0);
         var3.setValue(var2.getUserVolume());
         var0.add(var3);
      }

      String var4 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "sounds.ini";
      ConfigFile var5 = new ConfigFile();
      if (var5.write(var4, 1, var0)) {
         var0.clear();
      }
   }

   public static void previewSound(String var0) {
      if (!Core.SoundDisabled) {
         if (isKnownSound(var0)) {
            GameSound var1 = getSound(var0);
            if (var1 == null) {
               DebugLog.log("no such GameSound " + var0);
            } else {
               GameSoundClip var2 = var1.getRandomClip();
               if (var2 == null) {
                  DebugLog.log("GameSound.clips is empty");
               } else {
                  if (soundIsPaused) {
                     if (!GameClient.bClient) {
                        long var3 = javafmod.FMOD_System_GetMasterChannelGroup();
                        javafmod.FMOD_ChannelGroup_SetVolume(var3, 1.0F);
                     }

                     soundIsPaused = false;
                  }

                  if (previewSound != null) {
                     previewSound.stop();
                  }

                  if (var2.getEvent() != null) {
                     if (previewBank.play(var2)) {
                        previewSound = previewBank;
                     }
                  } else if (var2.getFile() != null && previewFile.play(var2)) {
                     previewSound = previewFile;
                  }
               }
            }
         }
      }
   }

   public static void stopPreview() {
      if (previewSound != null) {
         previewSound.stop();
         previewSound = null;
      }
   }

   public static boolean isPreviewPlaying() {
      if (previewSound == null) {
         return false;
      } else if (previewSound.update()) {
         previewSound = null;
         return false;
      } else {
         return previewSound.isPlaying();
      }
   }

   public static void fix3DListenerPosition(boolean var0) {
      if (!Core.SoundDisabled) {
         if (var0) {
            javafmod.FMOD_Studio_Listener3D(0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, 1.0F);
         } else {
            for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
               IsoPlayer var2 = IsoPlayer.players[var1];
               if (var2 != null && !var2.Traits.Deaf.isSet()) {
                  javafmod.FMOD_Studio_Listener3D(
                     var1,
                     var2.x,
                     var2.y,
                     var2.z * 3.0F,
                     0.0F,
                     0.0F,
                     0.0F,
                     -1.0F / (float)Math.sqrt(2.0),
                     -1.0F / (float)Math.sqrt(2.0),
                     0.0F,
                     0.0F,
                     0.0F,
                     1.0F
                  );
               }
            }
         }
      }
   }

   public static void Reset() {
      sounds.clear();
      soundByName.clear();
      if (previewSound != null) {
         previewSound.stop();
         previewSound = null;
      }
   }
}
