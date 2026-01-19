package zombie.ai;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Stack;
import zombie.ai.states.ThumpState;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.characters.Stance;
import zombie.characters.Stats;
import zombie.characters.SurvivorDesc;
import zombie.characters.SurvivorGroup;
import zombie.iso.IsoMovingObject;
import zombie.iso.LosUtil;
import zombie.iso.Vector2;
import zombie.iso.Vector3;

public final class GameCharacterAIBrain {
   private final IsoGameCharacter character;
   public final ArrayList<IsoGameCharacter> spottedCharacters = new ArrayList<>();
   public boolean StepBehaviors;
   public Stance stance;
   public boolean controlledByAdvancedPathfinder;
   public boolean isInMeta;
   public final HashMap<Vector3, ArrayList<Vector3>> BlockedMemories = new HashMap<>();
   public final Vector2 AIFocusPoint = new Vector2();
   public final Vector3 nextPathTarget = new Vector3();
   public IsoMovingObject aiTarget;
   public boolean NextPathNodeInvalidated;
   public final AIBrainPlayerControlVars HumanControlVars = new AIBrainPlayerControlVars();
   String order;
   public ArrayList<IsoZombie> teammateChasingZombies = new ArrayList<>();
   public ArrayList<IsoZombie> chasingZombies = new ArrayList<>();
   public boolean allowLongTermTick = true;
   public boolean isAI = false;
   static ArrayList<IsoZombie> tempZombies = new ArrayList<>();
   static IsoGameCharacter compare;
   private static final Stack<Vector3> Vectors = new Stack<>();

   public IsoGameCharacter getCharacter() {
      return this.character;
   }

   public GameCharacterAIBrain(IsoGameCharacter var1) {
      this.character = var1;
   }

   public void update() {
   }

   public void postUpdateHuman(IsoPlayer var1) {
   }

   public String getOrder() {
      return this.order;
   }

   public void setOrder(String var1) {
      this.order = var1;
   }

   public SurvivorGroup getGroup() {
      return this.character.getDescriptor().getGroup();
   }

   public int getCloseZombieCount() {
      this.character.getStats();
      return Stats.NumCloseZombies;
   }

   public IsoZombie getClosestChasingZombie(boolean var1) {
      IsoZombie var2 = null;
      float var3 = 1.0E7F;

      for (int var4 = 0; var4 < this.chasingZombies.size(); var4++) {
         IsoZombie var5 = this.chasingZombies.get(var4);
         float var6 = var5.DistTo(this.character);
         if (var5.isOnFloor()) {
            var6 += 2.0F;
         }

         if (!LosUtil.lineClearCollide((int)var5.x, (int)var5.y, (int)var5.z, (int)this.character.x, (int)this.character.y, (int)this.character.z, false)
            && var5.getStateMachine().getCurrent() != ThumpState.instance()
            && var6 < var3
            && var5.target == this.character) {
            var3 = var6;
            var2 = this.chasingZombies.get(var4);
         }
      }

      if (var2 == null && var1) {
         for (int var8 = 0; var8 < this.getGroup().Members.size(); var8++) {
            IsoGameCharacter var10 = ((SurvivorDesc)this.getGroup().Members.get(var8)).getInstance();
            IsoZombie var12 = var10.getGameCharacterAIBrain().getClosestChasingZombie(false);
            if (var12 != null) {
               float var7 = var12.DistTo(this.character);
               if (var7 < var3) {
                  var3 = var7;
                  var2 = var12;
               }
            }
         }
      }

      if (var2 == null && var1) {
         for (int var9 = 0; var9 < this.spottedCharacters.size(); var9++) {
            IsoGameCharacter var11 = this.spottedCharacters.get(var9);
            IsoZombie var13 = var11.getGameCharacterAIBrain().getClosestChasingZombie(false);
            if (var13 != null) {
               float var14 = var13.DistTo(this.character);
               if (var14 < var3) {
                  var3 = var14;
                  var2 = var13;
               }
            }
         }
      }

      return var2 != null && var2.DistTo(this.character) > 30.0F ? null : var2;
   }

   public IsoZombie getClosestChasingZombie() {
      return this.getClosestChasingZombie(true);
   }

   public ArrayList<IsoZombie> getClosestChasingZombies(int var1) {
      tempZombies.clear();
      Object var2 = null;
      float var3 = 1.0E7F;

      for (int var4 = 0; var4 < this.chasingZombies.size(); var4++) {
         IsoZombie var5 = this.chasingZombies.get(var4);
         float var6 = var5.DistTo(this.character);
         if (!LosUtil.lineClearCollide((int)var5.x, (int)var5.y, (int)var5.z, (int)this.character.x, (int)this.character.y, (int)this.character.z, false)) {
            tempZombies.add(var5);
         }
      }

      compare = this.character;
      tempZombies.sort((var0, var1x) -> {
         float var2x = compare.DistTo(var0);
         float var3x = compare.DistTo(var1x);
         if (var2x > var3x) {
            return 1;
         } else {
            return var2x < var3x ? -1 : 0;
         }
      });
      int var7 = var1 - tempZombies.size();
      if (var7 > tempZombies.size() - 2) {
         var7 = tempZombies.size() - 2;
      }

      for (int var8 = 0; var8 < var7; var8++) {
         tempZombies.remove(tempZombies.size() - 1);
      }

      return tempZombies;
   }

   public void AddBlockedMemory(int var1, int var2, int var3) {
      synchronized (this.BlockedMemories) {
         Vector3 var5 = new Vector3((int)this.character.x, (int)this.character.y, (int)this.character.z);
         if (!this.BlockedMemories.containsKey(var5)) {
            this.BlockedMemories.put(var5, new ArrayList<>());
         }

         ArrayList var6 = this.BlockedMemories.get(var5);
         Vector3 var7 = new Vector3(var1, var2, var3);
         if (!var6.contains(var7)) {
            var6.add(var7);
         }
      }
   }

   public boolean HasBlockedMemory(int var1, int var2, int var3, int var4, int var5, int var6) {
      synchronized (this.BlockedMemories) {
         synchronized (Vectors) {
            Vector3 var7;
            if (Vectors.isEmpty()) {
               var7 = new Vector3();
            } else {
               var7 = Vectors.pop();
            }

            Vector3 var8;
            if (Vectors.isEmpty()) {
               var8 = new Vector3();
            } else {
               var8 = Vectors.pop();
            }

            var7.x = var1;
            var7.y = var2;
            var7.z = var3;
            var8.x = var4;
            var8.y = var5;
            var8.z = var6;
            if (!this.BlockedMemories.containsKey(var7)) {
               Vectors.push(var7);
               Vectors.push(var8);
               return false;
            }

            if (this.BlockedMemories.get(var7).contains(var8)) {
               Vectors.push(var7);
               Vectors.push(var8);
               return true;
            }

            Vectors.push(var7);
            Vectors.push(var8);
         }

         return false;
      }
   }

   public void renderlast() {
   }
}
