package zombie.scripting.objects;

import zombie.core.textures.Texture;

public final class VehicleScript$Skin {
   public String texture;
   public String textureRust = null;
   public String textureMask = null;
   public String textureLights = null;
   public String textureDamage1Overlay = null;
   public String textureDamage1Shell = null;
   public String textureDamage2Overlay = null;
   public String textureDamage2Shell = null;
   public String textureShadow = null;
   public Texture textureData;
   public Texture textureDataRust;
   public Texture textureDataMask;
   public Texture textureDataLights;
   public Texture textureDataDamage1Overlay;
   public Texture textureDataDamage1Shell;
   public Texture textureDataDamage2Overlay;
   public Texture textureDataDamage2Shell;
   public Texture textureDataShadow;

   public void copyMissingFrom(VehicleScript$Skin var1) {
      if (this.textureRust == null) {
         this.textureRust = var1.textureRust;
      }

      if (this.textureMask == null) {
         this.textureMask = var1.textureMask;
      }

      if (this.textureLights == null) {
         this.textureLights = var1.textureLights;
      }

      if (this.textureDamage1Overlay == null) {
         this.textureDamage1Overlay = var1.textureDamage1Overlay;
      }

      if (this.textureDamage1Shell == null) {
         this.textureDamage1Shell = var1.textureDamage1Shell;
      }

      if (this.textureDamage2Overlay == null) {
         this.textureDamage2Overlay = var1.textureDamage2Overlay;
      }

      if (this.textureDamage2Shell == null) {
         this.textureDamage2Shell = var1.textureDamage2Shell;
      }

      if (this.textureShadow == null) {
         this.textureShadow = var1.textureShadow;
      }
   }
}
