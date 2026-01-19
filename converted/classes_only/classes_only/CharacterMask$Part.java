package zombie.core.skinnedmodel.model;

import java.util.ArrayList;
import zombie.characterTextures.BloodBodyPartType;
import zombie.core.skinnedmodel.model.CharacterMask.1;

public enum CharacterMask$Part {
   Head(0),
   Torso(1, true),
   Pelvis(2, true),
   LeftArm(3),
   LeftHand(4),
   RightArm(5),
   RightHand(6),
   LeftLeg(7),
   LeftFoot(8),
   RightLeg(9),
   RightFoot(10),
   Dress(11),
   Chest(12, Torso),
   Waist(13, Torso),
   Belt(14, Pelvis),
   Crotch(15, Pelvis);

   private final int value;
   private final CharacterMask$Part parent;
   private final boolean isSubdivided;
   private CharacterMask$Part[] subDivisions;
   private BloodBodyPartType[] m_bloodBodyPartTypes;
   private static final CharacterMask$Part[] s_leaves = leavesInternal();

   private CharacterMask$Part(int var3) {
      this.value = var3;
      this.parent = null;
      this.isSubdivided = false;
   }

   private CharacterMask$Part(int var3, CharacterMask$Part var4) {
      this.value = var3;
      this.parent = var4;
      this.isSubdivided = false;
   }

   private CharacterMask$Part(int var3, boolean var4) {
      this.value = var3;
      this.parent = null;
      this.isSubdivided = var4;
   }

   public static int count() {
      return values().length;
   }

   public static CharacterMask$Part[] leaves() {
      return s_leaves;
   }

   public static CharacterMask$Part fromInt(int var0) {
      return var0 >= 0 && var0 < count() ? values()[var0] : null;
   }

   public int getValue() {
      return this.value;
   }

   public CharacterMask$Part getParent() {
      return this.parent;
   }

   public boolean isSubdivision() {
      return this.parent != null;
   }

   public boolean hasSubdivisions() {
      return this.isSubdivided;
   }

   public CharacterMask$Part[] subDivisions() {
      if (this.subDivisions != null) {
         return this.subDivisions;
      } else {
         if (!this.isSubdivided) {
            this.subDivisions = new CharacterMask$Part[0];
         }

         ArrayList var1 = new ArrayList();

         for (CharacterMask$Part var5 : values()) {
            if (var5.parent == this) {
               var1.add(var5);
            }
         }

         this.subDivisions = var1.toArray(new CharacterMask$Part[0]);
         return this.subDivisions;
      }
   }

   private static CharacterMask$Part[] leavesInternal() {
      ArrayList var0 = new ArrayList();

      for (CharacterMask$Part var4 : values()) {
         if (!var4.hasSubdivisions()) {
            var0.add(var4);
         }
      }

      return var0.toArray(new CharacterMask$Part[0]);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public BloodBodyPartType[] getBloodBodyPartTypes() {
      if (this.m_bloodBodyPartTypes != null) {
         return this.m_bloodBodyPartTypes;
      } else {
         ArrayList var1 = new ArrayList();
         switch (1.$SwitchMap$zombie$core$skinnedmodel$model$CharacterMask$Part[this.ordinal()]) {
            case 1:
               var1.add(BloodBodyPartType.Head);
               break;
            case 2:
               var1.add(BloodBodyPartType.Torso_Upper);
               var1.add(BloodBodyPartType.Torso_Lower);
               break;
            case 3:
               var1.add(BloodBodyPartType.UpperLeg_L);
               var1.add(BloodBodyPartType.UpperLeg_R);
               var1.add(BloodBodyPartType.Groin);
               break;
            case 4:
               var1.add(BloodBodyPartType.UpperArm_L);
               var1.add(BloodBodyPartType.ForeArm_L);
               break;
            case 5:
               var1.add(BloodBodyPartType.Hand_L);
               break;
            case 6:
               var1.add(BloodBodyPartType.UpperArm_R);
               var1.add(BloodBodyPartType.ForeArm_R);
               break;
            case 7:
               var1.add(BloodBodyPartType.Hand_R);
               break;
            case 8:
               var1.add(BloodBodyPartType.UpperLeg_L);
               var1.add(BloodBodyPartType.LowerLeg_L);
               break;
            case 9:
               var1.add(BloodBodyPartType.Foot_L);
               break;
            case 10:
               var1.add(BloodBodyPartType.UpperLeg_R);
               var1.add(BloodBodyPartType.LowerLeg_R);
               break;
            case 11:
               var1.add(BloodBodyPartType.Foot_R);
            case 12:
            default:
               break;
            case 13:
               var1.add(BloodBodyPartType.Torso_Upper);
               break;
            case 14:
               var1.add(BloodBodyPartType.Torso_Lower);
               break;
            case 15:
               var1.add(BloodBodyPartType.UpperLeg_L);
               var1.add(BloodBodyPartType.UpperLeg_R);
               break;
            case 16:
               var1.add(BloodBodyPartType.Groin);
         }

         this.m_bloodBodyPartTypes = new BloodBodyPartType[var1.size()];

         for (int var2 = 0; var2 < var1.size(); var2++) {
            this.m_bloodBodyPartTypes[var2] = (BloodBodyPartType)var1.get(var2);
         }

         return this.m_bloodBodyPartTypes;
      }
   }
}
