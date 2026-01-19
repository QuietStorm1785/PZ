package zombie.iso.objects;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Stack;
import zombie.WorldSoundManager;
import zombie.characters.IsoGameCharacter;
import zombie.core.Rand;
import zombie.core.network.ByteBufferWriter;
import zombie.core.textures.ColorInfo;
import zombie.debug.DebugLog;
import zombie.iso.IsoCell;
import zombie.iso.IsoGridSquare;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.objects.IsoFireManager.FireSounds;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;

public class IsoFireManager {
   public static double Red_Oscilator = 0.0;
   public static double Green_Oscilator = 0.0;
   public static double Blue_Oscilator = 0.0;
   public static double Red_Oscilator_Rate = 0.1F;
   public static double Green_Oscilator_Rate = 0.13F;
   public static double Blue_Oscilator_Rate = 0.0876F;
   public static double Red_Oscilator_Val = 0.0;
   public static double Green_Oscilator_Val = 0.0;
   public static double Blue_Oscilator_Val = 0.0;
   public static double OscilatorSpeedScalar = 15.6F;
   public static double OscilatorEffectScalar = 0.0039F;
   public static int MaxFireObjects = 75;
   public static int FireRecalcDelay = 25;
   public static int FireRecalc = FireRecalcDelay;
   public static boolean LightCalcFromBurningCharacters = false;
   public static float FireAlpha = 1.0F;
   public static float SmokeAlpha = 0.3F;
   public static float FireAnimDelay = 0.2F;
   public static float SmokeAnimDelay = 0.2F;
   public static ColorInfo FireTintMod = new ColorInfo(1.0F, 1.0F, 1.0F, 1.0F);
   public static ColorInfo SmokeTintMod = new ColorInfo(0.5F, 0.5F, 0.5F, 1.0F);
   public static final ArrayList<IsoFire> FireStack = new ArrayList<>();
   public static final ArrayList<IsoGameCharacter> CharactersOnFire_Stack = new ArrayList<>();
   private static final FireSounds fireSounds = new FireSounds(20);
   private static Stack<IsoFire> updateStack = new Stack<>();
   private static final HashSet<IsoGameCharacter> charactersOnFire = new HashSet<>();

   public static void Add(IsoFire var0) {
      if (FireStack.contains(var0)) {
         System.out.println("IsoFireManager.Add already added fire, ignoring");
      } else {
         if (FireStack.size() < MaxFireObjects) {
            FireStack.add(var0);
         } else {
            IsoFire var1 = null;
            int var2 = 0;

            for (int var3 = 0; var3 < FireStack.size(); var3++) {
               if (FireStack.get(var3).Age > var2) {
                  var2 = FireStack.get(var3).Age;
                  var1 = FireStack.get(var3);
               }
            }

            if (var1 != null && var1.square != null) {
               var1.square.getProperties().UnSet(IsoFlagType.burning);
               var1.square.getProperties().UnSet(IsoFlagType.smoke);
               var1.RemoveAttachedAnims();
               var1.removeFromWorld();
               var1.removeFromSquare();
            }

            FireStack.add(var0);
         }
      }
   }

   public static void AddBurningCharacter(IsoGameCharacter var0) {
      for (int var1 = 0; var1 < CharactersOnFire_Stack.size(); var1++) {
         if (CharactersOnFire_Stack.get(var1) == var0) {
            return;
         }
      }

      CharactersOnFire_Stack.add(var0);
   }

   public static void Fire_LightCalc(IsoGridSquare var0, IsoGridSquare var1, int var2) {
      if (var1 != null && var0 != null) {
         int var3 = 0;
         byte var4 = 8;
         var3 += Math.abs(var1.getX() - var0.getX());
         var3 += Math.abs(var1.getY() - var0.getY());
         var3 += Math.abs(var1.getZ() - var0.getZ());
         if (var3 <= var4) {
            float var5 = 0.199F / var4 * (var4 - var3);
            float var7 = var5 * 0.6F;
            float var8 = var5 * 0.4F;
            if (var1.getLightInfluenceR() == null) {
               var1.setLightInfluenceR(new ArrayList());
            }

            var1.getLightInfluenceR().add(var5);
            if (var1.getLightInfluenceG() == null) {
               var1.setLightInfluenceG(new ArrayList());
            }

            var1.getLightInfluenceG().add(var7);
            if (var1.getLightInfluenceB() == null) {
               var1.setLightInfluenceB(new ArrayList());
            }

            var1.getLightInfluenceB().add(var8);
            ColorInfo var9 = var1.lighting[var2].lightInfo();
            var9.r += var5;
            var9.g += var7;
            var9.b += var8;
            if (var9.r > 1.0F) {
               var9.r = 1.0F;
            }

            if (var9.g > 1.0F) {
               var9.g = 1.0F;
            }

            if (var9.b > 1.0F) {
               var9.b = 1.0F;
            }
         }
      }
   }

   public static void LightTileWithFire(IsoGridSquare var0) {
   }

   public static void explode(IsoCell var0, IsoGridSquare var1, int var2) {
      if (var1 != null) {
         IsoGridSquare var3 = null;
         Object var4 = null;
         FireRecalc = 1;

         for (int var5 = -2; var5 <= 2; var5++) {
            for (int var6 = -2; var6 <= 2; var6++) {
               for (int var7 = 0; var7 <= 1; var7++) {
                  var3 = var0.getGridSquare(var1.getX() + var5, var1.getY() + var6, var1.getZ() + var7);
                  if (var3 != null && Rand.Next(100) < var2 && IsoFire.CanAddFire(var3, true)) {
                     StartFire(var0, var3, true, Rand.Next(100, 250 + var2));
                     var3.BurnWalls(true);
                  }
               }
            }
         }
      }
   }

   @Deprecated
   public static void MolotovSmash(IsoCell var0, IsoGridSquare var1) {
   }

   public static void Remove(IsoFire var0) {
      if (!FireStack.contains(var0)) {
         System.out.println("IsoFireManager.Remove unknown fire, ignoring");
      } else {
         FireStack.remove(var0);
      }
   }

   public static void RemoveBurningCharacter(IsoGameCharacter var0) {
      CharactersOnFire_Stack.remove(var0);
   }

   public static void StartFire(IsoCell var0, IsoGridSquare var1, boolean var2, int var3, int var4) {
      if (var1.getFloor() != null && var1.getFloor().getSprite() != null) {
         var3 -= var1.getFloor().getSprite().firerequirement;
      }

      if (var3 < 5) {
         var3 = 5;
      }

      if (IsoFire.CanAddFire(var1, var2)) {
         if (GameClient.bClient) {
            DebugLog.General.warn("The StartFire function was called on Client");
         } else if (GameServer.bServer) {
            GameServer.startFireOnClient(var1, var3, var2, var4, false);
         } else {
            IsoFire var5 = new IsoFire(var0, var1, var2, var3, var4);
            Add(var5);
            var1.getObjects().add(var5);
            if (Rand.Next(5) == 0) {
               WorldSoundManager.instance.addSound(var5, var1.getX(), var1.getY(), var1.getZ(), 20, 20);
            }
         }
      }
   }

   public static void StartSmoke(IsoCell var0, IsoGridSquare var1, boolean var2, int var3, int var4) {
      if (IsoFire.CanAddSmoke(var1, var2)) {
         if (GameClient.bClient) {
            ByteBufferWriter var6 = GameClient.connection.startPacket();
            PacketType.StartFire.doPacket(var6);
            var6.putInt(var1.getX());
            var6.putInt(var1.getY());
            var6.putInt(var1.getZ());
            var6.putInt(var3);
            var6.putBoolean(var2);
            var6.putInt(var4);
            var6.putBoolean(true);
            PacketType.StartFire.send(GameClient.connection);
         } else if (GameServer.bServer) {
            GameServer.startFireOnClient(var1, var3, var2, var4, true);
         } else {
            IsoFire var5 = new IsoFire(var0, var1, var2, var3, var4, true);
            Add(var5);
            var1.getObjects().add(var5);
         }
      }
   }

   public static void StartFire(IsoCell var0, IsoGridSquare var1, boolean var2, int var3) {
      StartFire(var0, var1, var2, var3, 0);
   }

   public static void addCharacterOnFire(IsoGameCharacter var0) {
      synchronized (charactersOnFire) {
         charactersOnFire.add(var0);
      }
   }

   public static void deleteCharacterOnFire(IsoGameCharacter var0) {
      synchronized (charactersOnFire) {
         charactersOnFire.remove(var0);
      }
   }

   public static void Update() {
      synchronized (charactersOnFire) {
         charactersOnFire.forEach(IsoGameCharacter::SpreadFireMP);
      }

      Red_Oscilator_Val = Math.sin(Red_Oscilator = Red_Oscilator + Blue_Oscilator_Rate * OscilatorSpeedScalar);
      Green_Oscilator_Val = Math.sin(Green_Oscilator = Green_Oscilator + Blue_Oscilator_Rate * OscilatorSpeedScalar);
      Blue_Oscilator_Val = Math.sin(Blue_Oscilator = Blue_Oscilator + Blue_Oscilator_Rate * OscilatorSpeedScalar);
      Red_Oscilator_Val = (Red_Oscilator_Val + 1.0) / 2.0;
      Green_Oscilator_Val = (Green_Oscilator_Val + 1.0) / 2.0;
      Blue_Oscilator_Val = (Blue_Oscilator_Val + 1.0) / 2.0;
      Red_Oscilator_Val = Red_Oscilator_Val * OscilatorEffectScalar;
      Green_Oscilator_Val = Green_Oscilator_Val * OscilatorEffectScalar;
      Blue_Oscilator_Val = Blue_Oscilator_Val * OscilatorEffectScalar;
      updateStack.clear();
      updateStack.addAll(FireStack);

      for (int var3 = 0; var3 < updateStack.size(); var3++) {
         IsoFire var1 = updateStack.get(var3);
         if (var1.getObjectIndex() != -1 && FireStack.contains(var1)) {
            var1.update();
         }
      }

      FireRecalc--;
      if (FireRecalc < 0) {
         FireRecalc = FireRecalcDelay;
      }

      fireSounds.update();
   }

   public static void updateSound(IsoFire var0) {
      fireSounds.addFire(var0);
   }

   public static void stopSound(IsoFire var0) {
      fireSounds.removeFire(var0);
   }

   public static void RemoveAllOn(IsoGridSquare var0) {
      for (int var1 = FireStack.size() - 1; var1 >= 0; var1--) {
         IsoFire var2 = FireStack.get(var1);
         if (var2.square == var0) {
            var2.extinctFire();
         }
      }
   }

   public static void Reset() {
      FireStack.clear();
      CharactersOnFire_Stack.clear();
      fireSounds.Reset();
   }
}
