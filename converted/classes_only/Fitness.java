package zombie.characters.BodyDamage;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;
import se.krka.kahlua.j2se.KahluaTableImpl;
import zombie.GameTime;
import zombie.GameWindow;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.BodyDamage.Fitness.FitnessExercise;
import zombie.characters.Moodles.MoodleType;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.Rand;

public final class Fitness {
   private IsoGameCharacter parent = null;
   private HashMap<String, Float> regularityMap = new HashMap<>();
   private int fitnessLvl = 0;
   private int strLvl = 0;
   private final HashMap<String, Integer> stiffnessTimerMap = new HashMap<>();
   private final HashMap<String, Float> stiffnessIncMap = new HashMap<>();
   private final ArrayList<String> bodypartToIncStiffness = new ArrayList<>();
   private final HashMap<String, FitnessExercise> exercises = new HashMap<>();
   private final HashMap<String, Long> exeTimer = new HashMap<>();
   private int lastUpdate = -1;
   private FitnessExercise currentExe;
   private static final int HOURS_FOR_STIFFNESS = 12;
   private static final float BASE_STIFFNESS_INC = 0.5F;
   private static final float BASE_ENDURANCE_RED = 0.015F;
   private static final float BASE_REGULARITY_INC = 0.08F;
   private static final float BASE_REGULARITY_DEC = 0.002F;
   private static final float BASE_PAIN_INC = 2.5F;

   public Fitness(IsoGameCharacter var1) {
      this.setParent(var1);
   }

   public void update() {
      int var1 = GameTime.getInstance().getMinutes() / 10;
      if (this.lastUpdate == -1) {
         this.lastUpdate = var1;
      }

      if (var1 != this.lastUpdate) {
         this.lastUpdate = var1;
         ArrayList var2 = new ArrayList();
         this.decreaseRegularity();

         for (String var4 : this.stiffnessTimerMap.keySet()) {
            Integer var5 = this.stiffnessTimerMap.get(var4);
            var5 = var5 - 1;
            if (var5 <= 0) {
               var2.add(var4);
               this.bodypartToIncStiffness.add(var4);
            } else {
               this.stiffnessTimerMap.put(var4, var5);
            }
         }

         for (int var8 = 0; var8 < var2.size(); var8++) {
            this.stiffnessTimerMap.remove(var2.get(var8));
         }

         for (int var9 = 0; var9 < this.bodypartToIncStiffness.size(); var9++) {
            String var11 = this.bodypartToIncStiffness.get(var9);
            Float var6 = this.stiffnessIncMap.get(var11);
            if (var6 == null) {
               return;
            }

            var6 = var6 - 1.0F;
            this.increasePain(var11);
            if (var6 <= 0.0F) {
               this.bodypartToIncStiffness.remove(var9);
               this.stiffnessIncMap.remove(var11);
               var9--;
            } else {
               this.stiffnessIncMap.put(var11, var6);
            }
         }
      }
   }

   private void decreaseRegularity() {
      for (String var2 : this.regularityMap.keySet()) {
         if (this.exeTimer.containsKey(var2) && GameTime.getInstance().getCalender().getTimeInMillis() - this.exeTimer.get(var2) > 86400000L) {
            float var3 = this.regularityMap.get(var2);
            var3 -= 0.002F;
            this.regularityMap.put(var2, var3);
         }
      }
   }

   private void increasePain(String var1) {
      if ("arms".equals(var1)) {
         for (int var2 = BodyPartType.ForeArm_L.index(); var2 < BodyPartType.UpperArm_R.index() + 1; var2++) {
            BodyPart var3 = this.parent.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var2));
            var3.setStiffness(var3.getStiffness() + 2.5F);
         }
      }

      if ("legs".equals(var1)) {
         for (int var4 = BodyPartType.UpperLeg_L.index(); var4 < BodyPartType.LowerLeg_R.index() + 1; var4++) {
            BodyPart var7 = this.parent.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4));
            var7.setStiffness(var7.getStiffness() + 2.5F);
         }
      }

      if ("chest".equals(var1)) {
         BodyPart var5 = this.parent.getBodyDamage().getBodyPart(BodyPartType.Torso_Upper);
         var5.setStiffness(var5.getStiffness() + 2.5F);
      }

      if ("abs".equals(var1)) {
         BodyPart var6 = this.parent.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
         var6.setStiffness(var6.getStiffness() + 2.5F);
      }
   }

   public void setCurrentExercise(String var1) {
      this.currentExe = this.exercises.get(var1);
   }

   public void exerciseRepeat() {
      this.fitnessLvl = this.parent.getPerkLevel(Perks.Fitness);
      this.strLvl = this.parent.getPerkLevel(Perks.Strength);
      this.incRegularity();
      this.reduceEndurance();
      this.incFutureStiffness();
      this.incStats();
      this.updateExeTimer();
   }

   private void updateExeTimer() {
      this.exeTimer.put(this.currentExe.type, GameTime.getInstance().getCalender().getTimeInMillis());
   }

   public void incRegularity() {
      float var1 = 0.08F;
      byte var2 = 4;
      double var3 = Math.log(this.fitnessLvl / 5.0F + var2);
      var1 = (float)(var1 * (Math.log(var2 + 1) / var3));
      Float var5 = this.regularityMap.get(this.currentExe.type);
      if (var5 == null) {
         var5 = 0.0F;
      }

      var5 = var5 + var1;
      var5 = Math.min(Math.max(var5, 0.0F), 100.0F);
      this.regularityMap.put(this.currentExe.type, var5);
   }

   public void reduceEndurance() {
      float var1 = 0.015F;
      Float var2 = this.regularityMap.get(this.currentExe.type);
      if (var2 == null) {
         var2 = 0.0F;
      }

      byte var3 = 50;
      double var4 = Math.log(var2 / 50.0F + var3);
      var1 = (float)(var1 * (var4 / Math.log(var3 + 1)));
      if (this.currentExe.metabolics == Metabolics.FitnessHeavy) {
         var1 *= 1.3F;
      }

      var1 *= 1 + this.parent.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) / 3;
      this.parent.getStats().setEndurance(this.parent.getStats().getEndurance() - var1);
   }

   public void incFutureStiffness() {
      Float var1 = this.regularityMap.get(this.currentExe.type);
      if (var1 == null) {
         var1 = 0.0F;
      }

      for (int var2 = 0; var2 < this.currentExe.stiffnessInc.size(); var2++) {
         float var3 = 0.5F;
         String var4 = (String)this.currentExe.stiffnessInc.get(var2);
         if (!this.stiffnessTimerMap.containsKey(var4) && !this.bodypartToIncStiffness.contains(var4)) {
            this.stiffnessTimerMap.put(var4, 72);
         }

         Float var5 = this.stiffnessIncMap.get(var4);
         if (var5 == null) {
            var5 = 0.0F;
         }

         var3 *= (120.0F - var1) / 170.0F;
         if (this.currentExe.metabolics == Metabolics.FitnessHeavy) {
            var3 *= 1.3F;
         }

         var3 *= 1 + this.parent.getMoodles().getMoodleLevel(MoodleType.Tired) / 3;
         var5 = var5 + var3;
         var5 = Math.min(var5, 150.0F);
         this.stiffnessIncMap.put(var4, var5);
      }
   }

   public void incStats() {
      float var1 = 0.0F;
      float var2 = 0.0F;

      for (int var3 = 0; var3 < this.currentExe.stiffnessInc.size(); var3++) {
         String var4 = (String)this.currentExe.stiffnessInc.get(var3);
         if ("arms".equals(var4)) {
            var1 += 4.0F;
         }

         if ("chest".equals(var4)) {
            var1 += 2.0F;
         }

         if ("legs".equals(var4)) {
            var2 += 4.0F;
         }

         if ("abs".equals(var4)) {
            var2 += 2.0F;
         }
      }

      if (this.strLvl > 5) {
         var1 *= 1 + (this.strLvl - 5) / 10;
      }

      if (this.fitnessLvl > 5) {
         var2 *= 1 + (this.fitnessLvl - 5) / 10;
      }

      var1 *= this.currentExe.xpModifier;
      var2 *= this.currentExe.xpModifier;
      this.parent.getXp().AddXP(Perks.Strength, var1);
      this.parent.getXp().AddXP(Perks.Fitness, var2);
   }

   public void resetValues() {
      this.stiffnessIncMap.clear();
      this.stiffnessTimerMap.clear();
      this.regularityMap.clear();
   }

   public void removeStiffnessValue(String var1) {
      this.stiffnessIncMap.remove(var1);
      this.stiffnessTimerMap.remove(var1);
   }

   public void save(ByteBuffer var1) {
      var1.putInt(this.stiffnessIncMap.size());

      for (String var3 : this.stiffnessIncMap.keySet()) {
         GameWindow.WriteString(var1, var3);
         var1.putFloat(this.stiffnessIncMap.get(var3));
      }

      var1.putInt(this.stiffnessTimerMap.size());

      for (String var7 : this.stiffnessTimerMap.keySet()) {
         GameWindow.WriteString(var1, var7);
         var1.putInt(this.stiffnessTimerMap.get(var7));
      }

      var1.putInt(this.regularityMap.size());

      for (String var8 : this.regularityMap.keySet()) {
         GameWindow.WriteString(var1, var8);
         var1.putFloat(this.regularityMap.get(var8));
      }

      var1.putInt(this.bodypartToIncStiffness.size());

      for (int var9 = 0; var9 < this.bodypartToIncStiffness.size(); var9++) {
         GameWindow.WriteString(var1, this.bodypartToIncStiffness.get(var9));
      }

      var1.putInt(this.exeTimer.size());

      for (String var10 : this.exeTimer.keySet()) {
         GameWindow.WriteString(var1, var10);
         var1.putLong(this.exeTimer.get(var10));
      }
   }

   public void load(ByteBuffer var1, int var2) {
      if (var2 >= 167) {
         int var3 = var1.getInt();
         if (var3 > 0) {
            for (int var4 = 0; var4 < var3; var4++) {
               this.stiffnessIncMap.put(GameWindow.ReadString(var1), var1.getFloat());
            }
         }

         var3 = var1.getInt();
         if (var3 > 0) {
            for (int var9 = 0; var9 < var3; var9++) {
               this.stiffnessTimerMap.put(GameWindow.ReadString(var1), var1.getInt());
            }
         }

         var3 = var1.getInt();
         if (var3 > 0) {
            for (int var10 = 0; var10 < var3; var10++) {
               this.regularityMap.put(GameWindow.ReadString(var1), var1.getFloat());
            }
         }

         var3 = var1.getInt();
         if (var3 > 0) {
            for (int var11 = 0; var11 < var3; var11++) {
               this.bodypartToIncStiffness.add(GameWindow.ReadString(var1));
            }
         }

         if (var2 >= 169) {
            var3 = var1.getInt();
            if (var3 > 0) {
               for (int var12 = 0; var12 < var3; var12++) {
                  this.exeTimer.put(GameWindow.ReadString(var1), var1.getLong());
               }
            }
         }
      }
   }

   public boolean onGoingStiffness() {
      return !this.bodypartToIncStiffness.isEmpty();
   }

   public int getCurrentExeStiffnessTimer(String var1) {
      var1 = var1.split(",")[0];
      return this.stiffnessTimerMap.get(var1) != null ? this.stiffnessTimerMap.get(var1) : 0;
   }

   public float getCurrentExeStiffnessInc(String var1) {
      var1 = var1.split(",")[0];
      return this.stiffnessIncMap.get(var1) != null ? this.stiffnessIncMap.get(var1) : 0.0F;
   }

   public IsoGameCharacter getParent() {
      return this.parent;
   }

   public void setParent(IsoGameCharacter var1) {
      this.parent = var1;
   }

   public float getRegularity(String var1) {
      Float var2 = this.regularityMap.get(var1);
      if (var2 == null) {
         var2 = 0.0F;
      }

      return var2;
   }

   public HashMap<String, Float> getRegularityMap() {
      return this.regularityMap;
   }

   public void setRegularityMap(HashMap<String, Float> var1) {
      this.regularityMap = var1;
   }

   public void init() {
      if (this.exercises.isEmpty()) {
         KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("FitnessExercises");
         KahluaTableImpl var2 = (KahluaTableImpl)var1.rawget("exercisesType");

         for (Entry var4 : var2.delegate.entrySet()) {
            this.exercises.put((String)var4.getKey(), new FitnessExercise((KahluaTableImpl)var4.getValue()));
         }

         this.initRegularityMapProfession();
      }
   }

   public void initRegularityMapProfession() {
      if (this.regularityMap.isEmpty()) {
         boolean var1 = false;
         boolean var2 = false;
         boolean var3 = false;
         if (this.parent.getDescriptor().getProfession().equals("fitnessInstructor")) {
            var2 = true;
         }

         if (this.parent.getDescriptor().getProfession().equals("fireofficer")) {
            var1 = true;
         }

         if (this.parent.getDescriptor().getProfession().equals("securityguard")) {
            var3 = true;
         }

         if (var1 || var2 || var3) {
            Iterator var4 = this.exercises.keySet().iterator();

            while (var4.hasNext()) {
               float var5 = Rand.Next(7, 12);
               if (var1) {
                  var5 = Rand.Next(10, 20);
               }

               if (var2) {
                  var5 = Rand.Next(40, 60);
               }

               this.regularityMap.put((String)var4.next(), var5);
            }
         }
      }
   }
}
