package zombie.core.skinnedmodel.model;

import java.util.ArrayList;
import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.lwjgl.opengl.GL11;
import zombie.core.Core;
import zombie.core.ImmutableColor;
import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.ModelManager;
import zombie.core.skinnedmodel.model.WorldItemModelDrawer.WeaponPartParams;
import zombie.core.skinnedmodel.population.ClothingItem;
import zombie.core.skinnedmodel.shader.Shader;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.core.textures.ColorInfo;
import zombie.core.textures.Texture;
import zombie.core.textures.TextureDraw.GenericDrawer;
import zombie.debug.DebugOptions;
import zombie.input.GameKeyboard;
import zombie.inventory.InventoryItem;
import zombie.inventory.types.Clothing;
import zombie.inventory.types.Food;
import zombie.inventory.types.HandWeapon;
import zombie.inventory.types.WeaponPart;
import zombie.iso.IsoCamera;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoUtils;
import zombie.iso.objects.IsoWorldInventoryObject;
import zombie.iso.sprite.IsoSprite;
import zombie.network.GameServer;
import zombie.network.ServerGUI;
import zombie.popman.ObjectPool;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.ModelAttachment;
import zombie.scripting.objects.ModelScript;
import zombie.scripting.objects.ModelWeaponPart;
import zombie.util.StringUtils;

public final class WorldItemModelDrawer extends GenericDrawer {
   private static final ObjectPool<WorldItemModelDrawer> s_modelDrawerPool = new ObjectPool(WorldItemModelDrawer::new);
   private static final ObjectPool<WeaponPartParams> s_weaponPartParamPool = new ObjectPool(WeaponPartParams::new);
   private static final ArrayList<WeaponPart> s_tempWeaponPartList = new ArrayList<>();
   private static final ColorInfo tempColorInfo = new ColorInfo();
   private static final Matrix4f s_attachmentXfrm = new Matrix4f();
   private static final ImmutableColor ROTTEN_FOOD_COLOR = new ImmutableColor(0.5F, 0.5F, 0.5F);
   public static boolean NEW_WAY = true;
   private Model m_model;
   private ArrayList<WeaponPartParams> m_weaponParts;
   private float m_hue;
   private float m_tintR;
   private float m_tintG;
   private float m_tintB;
   private float m_x;
   private float m_y;
   private float m_z;
   private final Vector3f m_angle = new Vector3f();
   private final Matrix4f m_transform = new Matrix4f();
   private float m_ambientR;
   private float m_ambientG;
   private float m_ambientB;
   private float alpha = 1.0F;
   static final Vector3f tempVector3f = new Vector3f(0.0F, 5.0F, -2.0F);

   public static boolean renderMain(InventoryItem var0, IsoGridSquare var1, float var2, float var3, float var4, float var5) {
      return renderMain(var0, var1, var2, var3, var4, var5, -1.0F);
   }

   public static boolean renderMain(InventoryItem var0, IsoGridSquare var1, float var2, float var3, float var4, float var5, float var6) {
      if (var0 != null && var1 != null) {
         Core.getInstance();
         if (!Core.Option3DGroundItem) {
            return false;
         } else if (renderAtlasTexture(var0, var1, var2, var3, var4, var5, var6)) {
            return true;
         } else {
            if (!StringUtils.isNullOrEmpty(var0.getWorldStaticItem())) {
               ModelScript var7 = ScriptManager.instance.getModelScript(var0.getWorldStaticItem());
               if (var7 != null) {
                  String var8 = var7.getMeshName();
                  String var9 = var7.getTextureName();
                  String var10 = var7.getShaderName();
                  ImmutableColor var11 = ImmutableColor.white;
                  float var12 = 1.0F;
                  if (var0 instanceof Food) {
                     if (((Food)var0).isCooked()) {
                        ModelScript var13 = ScriptManager.instance.getModelScript(var0.getWorldStaticItem() + "Cooked");
                        if (var13 != null) {
                           var9 = var13.getTextureName();
                           var8 = var13.getMeshName();
                           var10 = var13.getShaderName();
                           var7 = var13;
                        }
                     }

                     if (((Food)var0).isBurnt()) {
                        ModelScript var31 = ScriptManager.instance.getModelScript(var0.getWorldStaticItem() + "Burnt");
                        if (var31 != null) {
                           var9 = var31.getTextureName();
                           var8 = var31.getMeshName();
                           var10 = var31.getShaderName();
                           var7 = var31;
                        }
                     }

                     if (((Food)var0).isRotten()) {
                        ModelScript var32 = ScriptManager.instance.getModelScript(var0.getWorldStaticItem() + "Rotten");
                        if (var32 != null) {
                           var9 = var32.getTextureName();
                           var8 = var32.getMeshName();
                           var10 = var32.getShaderName();
                           var7 = var32;
                        } else {
                           var11 = ROTTEN_FOOD_COLOR;
                        }
                     }
                  }

                  if (var0 instanceof Clothing || var0.getClothingItem() != null) {
                     var9 = var7.getTextureName(true);
                     ItemVisual var33 = var0.getVisual();
                     ClothingItem var14 = var0.getClothingItem();
                     var11 = var33.getTint(var14);
                     if (var9 == null) {
                        if (var14.textureChoices.isEmpty()) {
                           var9 = var33.getBaseTexture(var14);
                        } else {
                           var9 = var33.getTextureChoice(var14);
                        }
                     }
                  }

                  boolean var34 = var7.bStatic;
                  Model var37 = ModelManager.instance.tryGetLoadedModel(var8, var9, var34, var10, true);
                  if (var37 == null) {
                     ModelManager.instance.loadAdditionalModel(var8, var9, var34, var10);
                  }

                  var37 = ModelManager.instance.getLoadedModel(var8, var9, var34, var10);
                  if (var37 != null && var37.isReady() && var37.Mesh != null && var37.Mesh.isReady()) {
                     WorldItemModelDrawer var15 = (WorldItemModelDrawer)s_modelDrawerPool.alloc();
                     var15.init(var0, var1, var2, var3, var4, var37, var7, var12, var11, var5, false);
                     if (var7.scale != 1.0F) {
                        var15.m_transform.scale(var7.scale);
                     }

                     if (var0.worldScale != 1.0F) {
                        var15.m_transform.scale(var0.worldScale);
                     }

                     var15.m_angle.x = 0.0F;
                     if (var6 < 0.0F) {
                        var15.m_angle.y = var0.worldZRotation;
                     } else {
                        var15.m_angle.y = var6;
                     }

                     var15.m_angle.z = 0.0F;
                     if (Core.bDebug) {
                     }

                     SpriteRenderer.instance.drawGeneric(var15);
                     return true;
                  }
               }
            } else if (var0 instanceof Clothing) {
               ClothingItem var18 = var0.getClothingItem();
               ItemVisual var20 = var0.getVisual();
               if (var18 != null
                  && var20 != null
                  && "Bip01_Head".equalsIgnoreCase(var18.m_AttachBone)
                  && (!((Clothing)var0).isCosmetic() || "Eyes".equals(var0.getBodyLocation()))) {
                  boolean var22 = false;
                  String var24 = var18.getModel(var22);
                  if (!StringUtils.isNullOrWhitespace(var24)) {
                     String var26 = var20.getTextureChoice(var18);
                     boolean var28 = var18.m_Static;
                     String var35 = var18.m_Shader;
                     Model var39 = ModelManager.instance.tryGetLoadedModel(var24, var26, var28, var35, false);
                     if (var39 == null) {
                        ModelManager.instance.loadAdditionalModel(var24, var26, var28, var35);
                     }

                     var39 = ModelManager.instance.getLoadedModel(var24, var26, var28, var35);
                     if (var39 != null && var39.isReady() && var39.Mesh != null && var39.Mesh.isReady()) {
                        WorldItemModelDrawer var43 = (WorldItemModelDrawer)s_modelDrawerPool.alloc();
                        float var16 = var20.getHue(var18);
                        ImmutableColor var17 = var20.getTint(var18);
                        var43.init(var0, var1, var2, var3, var4, var39, null, var16, var17, var5, false);
                        if (NEW_WAY) {
                           var43.m_angle.x = 180.0F + var5;
                           if (var6 < 0.0F) {
                              var43.m_angle.y = var0.worldZRotation;
                           } else {
                              var43.m_angle.y = var6;
                           }

                           var43.m_angle.z = -90.0F;
                           if (Core.bDebug) {
                           }

                           var43.m_transform.translate(-0.08F, 0.0F, 0.05F);
                        }

                        SpriteRenderer.instance.drawGeneric(var43);
                        return true;
                     }
                  }
               }
            }

            if (var0 instanceof HandWeapon) {
               ModelScript var19 = ScriptManager.instance.getModelScript(var0.getStaticModel());
               if (var19 != null) {
                  String var21 = var19.getMeshName();
                  String var23 = var19.getTextureName();
                  String var25 = var19.getShaderName();
                  boolean var27 = var19.bStatic;
                  Model var29 = ModelManager.instance.tryGetLoadedModel(var21, var23, var27, var25, false);
                  if (var29 == null) {
                     ModelManager.instance.loadAdditionalModel(var21, var23, var27, var25);
                  }

                  var29 = ModelManager.instance.getLoadedModel(var21, var23, var27, var25);
                  if (var29 != null && var29.isReady() && var29.Mesh != null && var29.Mesh.isReady()) {
                     WorldItemModelDrawer var36 = (WorldItemModelDrawer)s_modelDrawerPool.alloc();
                     float var41 = 1.0F;
                     ImmutableColor var42 = ImmutableColor.white;
                     var36.init(var0, var1, var2, var3, var4, var29, var19, var41, var42, var5, true);
                     if (var19.scale != 1.0F) {
                        var36.m_transform.scale(var19.scale);
                     }

                     if (var0.worldScale != 1.0F) {
                        var36.m_transform.scale(var0.worldScale);
                     }

                     var36.m_angle.x = 0.0F;
                     if (!NEW_WAY) {
                        var36.m_angle.y = 180.0F;
                     }

                     if (var6 < 0.0F) {
                        var36.m_angle.y = var0.worldZRotation;
                     } else {
                        var36.m_angle.y = var6;
                     }

                     if (!var36.initWeaponParts((HandWeapon)var0, var19)) {
                        var36.reset();
                        s_modelDrawerPool.release(var36);
                        return false;
                     }

                     SpriteRenderer.instance.drawGeneric(var36);
                     return true;
                  }
               }
            }

            return false;
         }
      } else {
         return false;
      }
   }

   private static boolean renderAtlasTexture(InventoryItem var0, IsoGridSquare var1, float var2, float var3, float var4, float var5, float var6) {
      if (var5 > 0.0F) {
         return false;
      } else if (var6 >= 0.0F) {
         return false;
      } else {
         boolean var7 = !Core.bDebug || !GameKeyboard.isKeyDown(199);
         if (!var7) {
            return false;
         } else {
            if (var0.atlasTexture != null && !var0.atlasTexture.isStillValid(var0)) {
               var0.atlasTexture = null;
            }

            if (var0.atlasTexture == null) {
               var0.atlasTexture = WorldItemAtlas.instance.getItemTexture(var0);
            }

            if (var0.atlasTexture == null) {
               return false;
            } else if (var0.atlasTexture.isTooBig()) {
               return false;
            } else {
               if (IsoSprite.globalOffsetX == -1.0F) {
                  IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
                  IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
               }

               float var8 = IsoUtils.XToScreen(var2, var3, var4, 0);
               float var9 = IsoUtils.YToScreen(var2, var3, var4, 0);
               var8 += IsoSprite.globalOffsetX;
               var9 += IsoSprite.globalOffsetY;
               var1.interpolateLight(tempColorInfo, var2 % 1.0F, var3 % 1.0F);
               float var10 = IsoWorldInventoryObject.getSurfaceAlpha(var1, var4 - (int)var4);
               var0.atlasTexture.render(var8, var9, tempColorInfo.r, tempColorInfo.g, tempColorInfo.b, var10);
               WorldItemAtlas.instance.render();
               return var0.atlasTexture.isRenderMainOK();
            }
         }
      }
   }

   private void init(
      InventoryItem var1,
      IsoGridSquare var2,
      float var3,
      float var4,
      float var5,
      Model var6,
      ModelScript var7,
      float var8,
      ImmutableColor var9,
      float var10,
      boolean var11
   ) {
      this.m_model = var6;
      if (this.m_weaponParts != null) {
         s_weaponPartParamPool.release(this.m_weaponParts);
         this.m_weaponParts.clear();
      }

      this.m_tintR = var9.r;
      this.m_tintG = var9.g;
      this.m_tintB = var9.b;
      this.m_hue = var8;
      this.m_x = var3;
      this.m_y = var4;
      this.m_z = var5;
      this.m_transform.rotationZ((90.0F + var10) * (float) (Math.PI / 180.0));
      if (var1 instanceof Clothing) {
         float var12 = -0.08F;
         float var13 = 0.05F;
         this.m_transform.translate(var12, 0.0F, var13);
      }

      this.m_angle.x = 0.0F;
      this.m_angle.y = 525.0F;
      this.m_angle.z = 0.0F;
      if (NEW_WAY) {
         this.m_transform.identity();
         this.m_angle.y = 0.0F;
         if (var11) {
            this.m_transform.rotateXYZ(0.0F, (float) Math.PI, (float) (Math.PI / 2));
         }

         if (var7 != null) {
            ModelAttachment var14 = var7.getAttachmentById("world");
            if (var14 != null) {
               ModelInstanceRenderData.makeAttachmentTransform(var14, s_attachmentXfrm);
               s_attachmentXfrm.invert();
               this.m_transform.mul(s_attachmentXfrm);
            }
         }

         if (var6.Mesh != null && var6.Mesh.isReady() && var6.Mesh.m_transform != null) {
            var6.Mesh.m_transform.transpose();
            this.m_transform.mul(var6.Mesh.m_transform);
            var6.Mesh.m_transform.transpose();
         }
      }

      var2.interpolateLight(tempColorInfo, this.m_x % 1.0F, this.m_y % 1.0F);
      if (GameServer.bServer && ServerGUI.isCreated()) {
         tempColorInfo.set(1.0F, 1.0F, 1.0F, 1.0F);
      }

      this.m_ambientR = tempColorInfo.r;
      this.m_ambientG = tempColorInfo.g;
      this.m_ambientB = tempColorInfo.b;
      this.alpha = IsoWorldInventoryObject.getSurfaceAlpha(var2, var5 - (int)var5);
   }

   boolean initWeaponParts(HandWeapon var1, ModelScript var2) {
      ArrayList var3 = var1.getModelWeaponPart();
      if (var3 == null) {
         return true;
      } else {
         ArrayList var4 = var1.getAllWeaponParts(s_tempWeaponPartList);

         for (int var5 = 0; var5 < var4.size(); var5++) {
            WeaponPart var6 = (WeaponPart)var4.get(var5);

            for (int var7 = 0; var7 < var3.size(); var7++) {
               ModelWeaponPart var8 = (ModelWeaponPart)var3.get(var7);
               if (var6.getFullType().equals(var8.partType)) {
                  if (!this.initWeaponPart(var8, var2)) {
                     return false;
                  }
                  break;
               }
            }
         }

         return true;
      }
   }

   boolean initWeaponPart(ModelWeaponPart var1, ModelScript var2) {
      String var3 = StringUtils.discardNullOrWhitespace(var1.modelName);
      if (var3 == null) {
         return false;
      } else {
         ModelScript var4 = ScriptManager.instance.getModelScript(var3);
         if (var4 == null) {
            return false;
         } else {
            String var5 = var4.getMeshName();
            String var6 = var4.getTextureName();
            String var7 = var4.getShaderName();
            boolean var8 = var4.bStatic;
            Model var9 = ModelManager.instance.tryGetLoadedModel(var5, var6, var8, var7, false);
            if (var9 == null) {
               ModelManager.instance.loadAdditionalModel(var5, var6, var8, var7);
            }

            var9 = ModelManager.instance.getLoadedModel(var5, var6, var8, var7);
            if (var9 != null && var9.isReady() && var9.Mesh != null && var9.Mesh.isReady()) {
               WeaponPartParams var10 = (WeaponPartParams)s_weaponPartParamPool.alloc();
               var10.m_model = var9;
               var10.m_attachmentNameSelf = var1.attachmentNameSelf;
               var10.m_attachmentNameParent = var1.attachmentParent;
               var10.initTransform(var2, var4);
               this.m_transform.mul(var10.m_transform, var10.m_transform);
               if (this.m_weaponParts == null) {
                  this.m_weaponParts = new ArrayList<>();
               }

               this.m_weaponParts.add(var10);
               return true;
            } else {
               return false;
            }
         }
      }
   }

   public void render() {
      GL11.glPushAttrib(1048575);
      GL11.glPushClientAttrib(-1);
      Core.getInstance().DoPushIsoStuff(this.m_x, this.m_y, this.m_z, 0.0F, false);
      GL11.glRotated(-180.0, 0.0, 1.0, 0.0);
      GL11.glRotated(this.m_angle.x, 1.0, 0.0, 0.0);
      GL11.glRotated(this.m_angle.y, 0.0, 1.0, 0.0);
      GL11.glRotated(this.m_angle.z, 0.0, 0.0, 1.0);
      GL11.glBlendFunc(770, 771);
      GL11.glDepthFunc(513);
      GL11.glDepthMask(true);
      GL11.glDepthRange(0.0, 1.0);
      GL11.glEnable(2929);
      GL11.glColor3f(1.0F, 1.0F, 1.0F);
      this.renderModel(this.m_model, this.m_transform);
      if (this.m_weaponParts != null) {
         for (int var1 = 0; var1 < this.m_weaponParts.size(); var1++) {
            WeaponPartParams var2 = this.m_weaponParts.get(var1);
            this.renderModel(var2.m_model, var2.m_transform);
         }
      }

      if (Core.bDebug && DebugOptions.instance.ModelRenderAxis.getValue()) {
         Model.debugDrawAxis(0.0F, 0.0F, 0.0F, 0.5F, 1.0F);
      }

      Core.getInstance().DoPopIsoStuff();
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
      Texture.lastTextureID = -1;
      SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      SpriteRenderer.ringBuffer.restoreVBOs = true;
   }

   void renderModel(Model var1, Matrix4f var2) {
      if (var1.bStatic) {
         if (var1.Effect == null) {
            var1.CreateShader("basicEffect");
         }

         Shader var3 = var1.Effect;
         if (var3 != null && var1.Mesh != null && var1.Mesh.isReady()) {
            var3.Start();
            if (var1.tex != null) {
               var3.setTexture(var1.tex, "Texture", 0);
            }

            var3.setDepthBias(0.0F);
            var3.setAmbient(this.m_ambientR * 0.4F, this.m_ambientG * 0.4F, this.m_ambientB * 0.4F);
            var3.setLightingAmount(1.0F);
            var3.setHueShift(this.m_hue);
            var3.setTint(this.m_tintR, this.m_tintG, this.m_tintB);
            var3.setAlpha(this.alpha);

            for (int var4 = 0; var4 < 5; var4++) {
               var3.setLight(var4, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, Float.NaN, 0.0F, 0.0F, 0.0F, null);
            }

            Vector3f var6 = tempVector3f;
            var6.x = 0.0F;
            var6.y = 5.0F;
            var6.z = -2.0F;
            var6.rotateY((float)Math.toRadians(this.m_angle.y));
            float var5 = 1.5F;
            var3.setLight(
               4,
               var6.x,
               var6.z,
               var6.y,
               this.m_ambientR / 4.0F * var5,
               this.m_ambientG / 4.0F * var5,
               this.m_ambientB / 4.0F * var5,
               5000.0F,
               Float.NaN,
               0.0F,
               0.0F,
               0.0F,
               null
            );
            var3.setTransformMatrix(var2, false);
            var1.Mesh.Draw(var3);
            var3.End();
         }
      }
   }

   public void postRender() {
      this.reset();
      s_modelDrawerPool.release(this);
   }

   void reset() {
      if (this.m_weaponParts != null) {
         s_weaponPartParamPool.release(this.m_weaponParts);
         this.m_weaponParts.clear();
      }
   }
}
