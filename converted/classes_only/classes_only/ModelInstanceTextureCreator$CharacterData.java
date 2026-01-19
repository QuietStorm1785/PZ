package zombie.core.skinnedmodel.model;

import zombie.characterTextures.BloodBodyPartType;

final class ModelInstanceTextureCreator$CharacterData {
   ModelInstance modelInstance;
   final CharacterMask mask = new CharacterMask();
   String maskFolder;
   String baseTexture;
   final float[] blood = new float[BloodBodyPartType.MAX.index()];
   final float[] dirt = new float[BloodBodyPartType.MAX.index()];

   private ModelInstanceTextureCreator$CharacterData() {
   }
}
