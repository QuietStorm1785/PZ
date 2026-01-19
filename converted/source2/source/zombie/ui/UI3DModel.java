package zombie.ui;

import se.krka.kahlua.vm.KahluaTable;
import zombie.characters.IsoGameCharacter;
import zombie.characters.SurvivorDesc;
import zombie.core.Rand;
import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.advancedanimation.AnimatedModel;
import zombie.core.skinnedmodel.population.IClothingItemListener;
import zombie.core.skinnedmodel.population.OutfitManager;
import zombie.iso.IsoDirections;
import zombie.ui.UI3DModel.Drawer;
import zombie.util.StringUtils;

public final class UI3DModel extends UIElement implements IClothingItemListener {
   private final AnimatedModel animatedModel = new AnimatedModel();
   private IsoDirections dir = IsoDirections.E;
   private boolean bDoExt = false;
   private long nextExt = -1L;
   private final Drawer[] drawers = new Drawer[3];
   private float zoom = 0.0F;
   private float yOffset = 0.0F;
   private float xOffset = 0.0F;

   public UI3DModel(KahluaTable var1) {
      super(var1);

      for (int var2 = 0; var2 < this.drawers.length; var2++) {
         this.drawers[var2] = new Drawer(this);
      }

      if (OutfitManager.instance != null) {
         OutfitManager.instance.addClothingItemListener(this);
      }
   }

   public void render() {
      if (this.isVisible()) {
         super.render();
         if (this.Parent == null || this.Parent.maxDrawHeight == -1 || !(this.Parent.maxDrawHeight <= this.y)) {
            if (this.bDoExt) {
               long var1 = System.currentTimeMillis();
               if (this.nextExt < 0L) {
                  this.nextExt = var1 + Rand.Next(5000, 10000);
               }

               if (this.nextExt < var1) {
                  this.animatedModel.getActionContext().reportEvent("EventDoExt");
                  this.animatedModel.setVariable("Ext", Rand.Next(0, 6) + 1);
                  this.nextExt = -1L;
               }
            }

            this.animatedModel.update();
            Drawer var3 = this.drawers[SpriteRenderer.instance.getMainStateIndex()];
            var3.init(this.getAbsoluteX().intValue(), this.getAbsoluteY().intValue());
            SpriteRenderer.instance.drawGeneric(var3);
         }
      }
   }

   public void setDirection(IsoDirections var1) {
      this.dir = var1;
      this.animatedModel.setAngle(var1.ToVector());
   }

   public IsoDirections getDirection() {
      return this.dir;
   }

   public void setAnimate(boolean var1) {
      this.animatedModel.setAnimate(var1);
   }

   public void setAnimSetName(String var1) {
      this.animatedModel.setAnimSetName(var1);
   }

   public void setDoRandomExtAnimations(boolean var1) {
      this.bDoExt = var1;
   }

   public void setIsometric(boolean var1) {
      this.animatedModel.setIsometric(var1);
   }

   public void setOutfitName(String var1, boolean var2, boolean var3) {
      this.animatedModel.setOutfitName(var1, var2, var3);
   }

   public void setCharacter(IsoGameCharacter var1) {
      this.animatedModel.setCharacter(var1);
   }

   public void setSurvivorDesc(SurvivorDesc var1) {
      this.animatedModel.setSurvivorDesc(var1);
   }

   public void setState(String var1) {
      this.animatedModel.setState(var1);
   }

   public void reportEvent(String var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.animatedModel.getActionContext().reportEvent(var1);
      }
   }

   public void clothingItemChanged(String var1) {
      this.animatedModel.clothingItemChanged(var1);
   }

   public void setZoom(float var1) {
      this.zoom = var1;
   }

   public void setYOffset(float var1) {
      this.yOffset = var1;
   }

   public void setXOffset(float var1) {
      this.xOffset = var1;
   }
}
