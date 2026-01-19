package zombie.iso.objects;

import fmod.fmod.FMODManager;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import zombie.GameTime;
import zombie.IndieGL;
import zombie.WorldSoundManager;
import zombie.Lua.LuaEventManager;
import zombie.audio.BaseSoundEmitter;
import zombie.audio.parameters.ParameterMeleeHitSurface.Material;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoGameCharacter.Location;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.core.SpriteRenderer;
import zombie.core.opengl.Shader;
import zombie.core.textures.ColorInfo;
import zombie.core.textures.Texture;
import zombie.inventory.types.HandWeapon;
import zombie.iso.CellLoader;
import zombie.iso.IsoCamera;
import zombie.iso.IsoCell;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoObject;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.LosUtil;
import zombie.iso.SpriteDetails.IsoObjectType;
import zombie.iso.objects.IsoTree.TreeShader;
import zombie.iso.sprite.IsoSprite;
import zombie.iso.sprite.IsoSpriteInstance;
import zombie.util.list.PZArrayUtil;
import zombie.vehicles.BaseVehicle;

public class IsoTree extends IsoObject {
   public static final int MAX_SIZE = 6;
   public int LogYield = 1;
   public int damage = 500;
   public int size = 4;
   public boolean bRenderFlag;
   public float fadeAlpha;
   private static final Location[] s_chopTreeLocation = new Location[4];
   private static final ArrayList<IsoGridSquare> s_chopTreeIndicators = new ArrayList<>();
   private static IsoTree s_chopTreeHighlighted = null;

   public static IsoTree getNew() {
      synchronized (CellLoader.isoTreeCache) {
         if (CellLoader.isoTreeCache.isEmpty()) {
            return new IsoTree();
         } else {
            IsoTree var1 = (IsoTree)CellLoader.isoTreeCache.pop();
            var1.sx = 0.0F;
            return var1;
         }
      }
   }

   public IsoTree() {
   }

   public IsoTree(IsoCell var1) {
      super(var1);
   }

   public void save(ByteBuffer var1, boolean var2) throws IOException {
      super.save(var1, var2);
      var1.put((byte)this.LogYield);
      var1.put((byte)(this.damage / 10));
   }

   public void load(ByteBuffer var1, int var2, boolean var3) throws IOException {
      super.load(var1, var2, var3);
      this.LogYield = var1.get();
      this.damage = var1.get() * 10;
      if (this.sprite != null && this.sprite.getProperties().Val("tree") != null) {
         this.size = Integer.parseInt(this.sprite.getProperties().Val("tree"));
         if (this.size < 1) {
            this.size = 1;
         }

         if (this.size > 6) {
            this.size = 6;
         }
      }
   }

   protected void checkMoveWithWind() {
      this.checkMoveWithWind(true);
   }

   public void reset() {
      super.reset();
   }

   public IsoTree(IsoGridSquare var1, String var2) {
      super(var1, var2, false);
      this.initTree();
   }

   public IsoTree(IsoGridSquare var1, IsoSprite var2) {
      super(var1.getCell(), var1, var2);
      this.initTree();
   }

   public void initTree() {
      this.setType(IsoObjectType.tree);
      if (this.sprite.getProperties().Val("tree") != null) {
         this.size = Integer.parseInt(this.sprite.getProperties().Val("tree"));
         if (this.size < 1) {
            this.size = 1;
         }

         if (this.size > 6) {
            this.size = 6;
         }
      } else {
         this.size = 4;
      }

      switch (this.size) {
         case 1:
         case 2:
            this.LogYield = 1;
            break;
         case 3:
         case 4:
            this.LogYield = 2;
            break;
         case 5:
            this.LogYield = 3;
            break;
         case 6:
            this.LogYield = 4;
      }

      this.damage = this.LogYield * 80;
   }

   public String getObjectName() {
      return "Tree";
   }

   public void Damage(float var1) {
      float var2 = var1 * 0.05F;
      this.damage = (int)(this.damage - var2);
      if (this.damage <= 0) {
         this.square.transmitRemoveItemFromSquare(this);
         this.square.RecalcAllWithNeighbours(true);
         int var3 = this.LogYield;

         for (int var4 = 0; var4 < var3; var4++) {
            this.square.AddWorldInventoryItem("Base.Log", 0.0F, 0.0F, 0.0F);
            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.TreeBranch", 0.0F, 0.0F, 0.0F);
            }

            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.Twigs", 0.0F, 0.0F, 0.0F);
            }
         }

         this.reset();
         CellLoader.isoTreeCache.add(this);

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
            LosUtil.cachecleared[var5] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }
   }

   public void HitByVehicle(BaseVehicle var1, float var2) {
      BaseSoundEmitter var3 = IsoWorld.instance.getFreeEmitter(this.square.x + 0.5F, this.square.y + 0.5F, this.square.z);
      long var4 = var3.playSound("VehicleHitTree");
      var3.setParameterValue(var4, FMODManager.instance.getParameterDescription("VehicleSpeed"), var1.getCurrentSpeedKmHour());
      WorldSoundManager.instance.addSound(null, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      this.Damage(this.damage);
   }

   public void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
      int var3 = var2.getConditionLowerChance() * 2 + var1.getMaintenanceMod();
      if (!var2.getCategories().contains("Axe")) {
         var3 = var2.getConditionLowerChance() / 2 + var1.getMaintenanceMod();
      }

      if (Rand.NextBool(var3)) {
         var2.setCondition(var2.getCondition() - 1);
      }

      if (var1 instanceof IsoPlayer) {
         ((IsoPlayer)var1).setMeleeHitSurface(Material.Tree);
         var1.getEmitter().playSound(var2.getZombieHitSound());
      } else {
         var1.getEmitter().playSound("ChopTree");
      }

      WorldSoundManager.instance.addSound(null, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      this.setRenderEffect(RenderEffectType.Hit_Tree_Shudder, true);
      float var4 = var2.getTreeDamage();
      if (var1.Traits.Axeman.isSet() && var2.getCategories().contains("Axe")) {
         var4 *= 1.5F;
      }

      this.damage = (int)(this.damage - var4);
      if (this.damage <= 0) {
         this.square.transmitRemoveItemFromSquare(this);
         var1.getEmitter().playSound("FallingTree");
         this.square.RecalcAllWithNeighbours(true);
         int var5 = this.LogYield;

         for (int var6 = 0; var6 < var5; var6++) {
            this.square.AddWorldInventoryItem("Base.Log", 0.0F, 0.0F, 0.0F);
            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.TreeBranch", 0.0F, 0.0F, 0.0F);
            }

            if (Rand.Next(4) == 0) {
               this.square.AddWorldInventoryItem("Base.Twigs", 0.0F, 0.0F, 0.0F);
            }
         }

         this.reset();
         CellLoader.isoTreeCache.add(this);

         for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
            LosUtil.cachecleared[var7] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }

      LuaEventManager.triggerEvent("OnWeaponHitTree", var1, var2);
   }

   public void setHealth(int var1) {
      this.damage = Math.max(var1, 0);
   }

   public int getHealth() {
      return this.damage;
   }

   public int getMaxHealth() {
      return this.LogYield * 80;
   }

   public int getSize() {
      return this.size;
   }

   public float getSlowFactor(IsoMovingObject var1) {
      float var2 = 1.0F;
      if (var1 instanceof IsoGameCharacter) {
         if ("parkranger".equals(((IsoGameCharacter)var1).getDescriptor().getProfession())) {
            var2 = 1.5F;
         }

         if ("lumberjack".equals(((IsoGameCharacter)var1).getDescriptor().getProfession())) {
            var2 = 1.2F;
         }
      }

      if (this.size == 1 || this.size == 2) {
         return 0.8F * var2;
      } else {
         return this.size != 3 && this.size != 4 ? 0.3F * var2 : 0.5F * var2;
      }
   }

   public void render(float var1, float var2, float var3, ColorInfo var4, boolean var5, boolean var6, Shader var7) {
      if (this.isHighlighted()) {
         if (this.square != null) {
            s_chopTreeHighlighted = this;
         }
      } else {
         int var8 = IsoCamera.frameState.playerIndex;
         if (!this.bRenderFlag && !(this.fadeAlpha < this.getTargetAlpha(var8))) {
            this.renderInner(var1, var2, var3, var4, var5, false);
         } else {
            IndieGL.enableStencilTest();
            IndieGL.glStencilFunc(517, 128, 128);
            this.renderInner(var1, var2, var3, var4, var5, false);
            float var9 = 0.044999998F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.bRenderFlag && this.fadeAlpha > 0.25F) {
               this.fadeAlpha -= var9;
               if (this.fadeAlpha < 0.25F) {
                  this.fadeAlpha = 0.25F;
               }
            }

            if (!this.bRenderFlag) {
               float var10 = this.getTargetAlpha(var8);
               if (this.fadeAlpha < var10) {
                  this.fadeAlpha += var9;
                  if (this.fadeAlpha > var10) {
                     this.fadeAlpha = var10;
                  }
               }
            }

            float var12 = this.getAlpha(var8);
            float var11 = this.getTargetAlpha(var8);
            this.setAlphaAndTarget(var8, this.fadeAlpha);
            IndieGL.glStencilFunc(514, 128, 128);
            this.renderInner(var1, var2, var3, var4, true, false);
            this.setAlpha(var8, var12);
            this.setTargetAlpha(var8, var11);
            if (TreeShader.instance.StartShader()) {
               TreeShader.instance.setOutlineColor(0.1F, 0.1F, 0.1F, 1.0F - this.fadeAlpha);
               this.renderInner(var1, var2, var3, var4, true, true);
               IndieGL.EndShader();
            }

            IndieGL.glStencilFunc(519, 255, 255);
         }

         this.checkChopTreeIndicator(var1, var2, var3);
      }
   }

   private void renderInner(float var1, float var2, float var3, ColorInfo var4, boolean var5, boolean var6) {
      if (this.sprite != null && this.sprite.name != null && this.sprite.name.contains("JUMBO")) {
         float var12 = this.offsetX;
         float var15 = this.offsetY;
         this.offsetX = 384 * Core.TileScale / 2 - 96 * Core.TileScale;
         this.offsetY = 256 * Core.TileScale - 32 * Core.TileScale;
         if (this.offsetX != var12 || this.offsetY != var15) {
            this.sx = 0.0F;
         }
      } else {
         float var7 = this.offsetX;
         float var8 = this.offsetY;
         this.offsetX = 32 * Core.TileScale;
         this.offsetY = 96 * Core.TileScale;
         if (this.offsetX != var7 || this.offsetY != var8) {
            this.sx = 0.0F;
         }
      }

      if (var6 && this.sprite != null) {
         Texture var13 = this.sprite.getTextureForCurrentFrame(this.dir);
         if (var13 != null) {
            TreeShader.instance.setStepSize(0.25F, var13.getWidth(), var13.getHeight());
         }
      }

      super.render(var1, var2, var3, var4, false, false, null);
      if (this.AttachedAnimSprite != null) {
         int var14 = this.AttachedAnimSprite.size();

         for (int var16 = 0; var16 < var14; var16++) {
            IsoSpriteInstance var9 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var16);
            int var10 = IsoCamera.frameState.playerIndex;
            float var11 = this.getTargetAlpha(var10);
            this.setTargetAlpha(var10, 1.0F);
            var9.render(this, var1, var2, var3, this.dir, this.offsetX, this.offsetY, this.isHighlighted() ? this.getHighlightColor() : var4);
            this.setTargetAlpha(var10, var11);
            var9.update();
         }
      }
   }

   public void setSprite(IsoSprite var1) {
      super.setSprite(var1);
      this.initTree();
   }

   public boolean isMaskClicked(int var1, int var2, boolean var3) {
      if (super.isMaskClicked(var1, var2, var3)) {
         return true;
      } else if (this.AttachedAnimSprite == null) {
         return false;
      } else {
         for (int var4 = 0; var4 < this.AttachedAnimSprite.size(); var4++) {
            if (((IsoSpriteInstance)this.AttachedAnimSprite.get(var4)).parentSprite.isMaskClicked(this.dir, var1, var2, var3)) {
               return true;
            }
         }

         return false;
      }
   }

   public static void setChopTreeCursorLocation(int var0, int var1, int var2, int var3) {
      if (s_chopTreeLocation[var0] == null) {
         s_chopTreeLocation[var0] = new Location(-1, -1, -1);
      }

      Location var4 = s_chopTreeLocation[var0];
      var4.x = var1;
      var4.y = var2;
      var4.z = var3;
   }

   private void checkChopTreeIndicator(float var1, float var2, float var3) {
      if (!this.isHighlighted()) {
         int var4 = IsoCamera.frameState.playerIndex;
         Location var5 = s_chopTreeLocation[var4];
         if (var5 != null && var5.x != -1 && this.square != null) {
            if (this.getCell().getDrag(var4) == null) {
               var5.x = -1;
            } else {
               if (IsoUtils.DistanceToSquared(this.square.x + 0.5F, this.square.y + 0.5F, var5.x + 0.5F, var5.y + 0.5F) < 12.25F) {
                  s_chopTreeIndicators.add(this.square);
               }
            }
         }
      }
   }

   public static void renderChopTreeIndicators() {
      if (!s_chopTreeIndicators.isEmpty()) {
         PZArrayUtil.forEach(s_chopTreeIndicators, IsoTree::renderChopTreeIndicator);
         s_chopTreeIndicators.clear();
      }

      if (s_chopTreeHighlighted != null) {
         IsoTree var0 = s_chopTreeHighlighted;
         s_chopTreeHighlighted = null;
         var0.renderInner(var0.square.x, var0.square.y, var0.square.z, var0.getHighlightColor(), false, false);
      }
   }

   private static void renderChopTreeIndicator(IsoGridSquare var0) {
      Texture var1 = Texture.getSharedTexture("media/ui/chop_tree.png");
      if (var1 != null && var1.isReady()) {
         float var2 = var0.x;
         float var3 = var0.y;
         float var4 = var0.z;
         float var5 = IsoUtils.XToScreen(var2, var3, var4, 0) + IsoSprite.globalOffsetX;
         float var6 = IsoUtils.YToScreen(var2, var3, var4, 0) + IsoSprite.globalOffsetY;
         var5 -= 32 * Core.TileScale;
         var6 -= 96 * Core.TileScale;
         SpriteRenderer.instance.render(var1, var5, var6, 64 * Core.TileScale, 128 * Core.TileScale, 0.0F, 0.5F, 0.0F, 0.75F, null);
      }
   }
}
