package zombie.core.skinnedmodel.model;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import org.lwjgl.opengl.GL11;
import org.lwjglx.BufferUtils;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.core.PerformanceSettings;
import zombie.core.Rand;
import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.Vector3;
import zombie.core.textures.Texture;
import zombie.creative.creativerects.OpenSimplexNoise;
import zombie.iso.IsoCamera;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.Vector2;

public final class HeightTerrain {
   private final ByteBuffer buffer;
   public VertexBufferObject vb;
   public static float isoAngle = 62.65607F;
   public static float scale = 0.047085002F;
   OpenSimplexNoise noise = new OpenSimplexNoise(Rand.Next(10000000));
   static float[] lightAmbient = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] lightDiffuse = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] lightPosition = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] specular = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] shininess = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] emission = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] ambient = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static float[] diffuse = new float[]{1.0F, 1.0F, 1.0F, 1.0F};
   static ByteBuffer temp = ByteBuffer.allocateDirect(16);

   public HeightTerrain(int var1, int var2) {
      ArrayList var5 = new ArrayList();
      int var6 = var1 * var2;
      int var7 = var1;
      int var8 = var2;
      ArrayList var9 = new ArrayList();
      Vector2 var10 = new Vector2(2.0F, 0.0F);
      int var11 = 0;

      for (int var12 = 0; var12 < var7; var12++) {
         for (int var13 = 0; var13 < var8; var13++) {
            float var14 = (float)this.calc(var12, var13);
            var14 *= 1.0F;
            var14++;
            VertexPositionNormalTangentTextureSkin var15 = null;
            var15 = new VertexPositionNormalTangentTextureSkin();
            var15.Position = new Vector3();
            var15.Position.set(-var12, var14 * 30.0F, -var13);
            var15.Normal = new Vector3();
            var15.Normal.set(0.0F, 1.0F, 0.0F);
            var15.Normal.normalize();
            var15.TextureCoordinates = new Vector2();
            var15.TextureCoordinates = new Vector2((float)var12 / (var7 - 1) * 16.0F, (float)var13 / (var8 - 1) * 16.0F);
            var5.add(var15);
         }
      }

      var11 = 0;

      for (int var32 = 0; var32 < var7; var32++) {
         for (int var35 = 0; var35 < var8; var35++) {
            float var42 = (float)this.calc(var32, var35);
            var42 *= 1.0F;
            var42 = Math.max(0.0F, ++var42);
            var42 = Math.min(1.0F, var42);
            Object var50 = null;
            var50 = (VertexPositionNormalTangentTextureSkin)var5.get(var11);
            Vector3 var16 = new Vector3();
            Vector3 var17 = new Vector3();
            float var18 = (float)this.calc(var32 + 1, var35);
            var18 *= 1.0F;
            var18++;
            float var19 = (float)this.calc(var32 - 1, var35);
            var19 *= 1.0F;
            var19++;
            float var20 = (float)this.calc(var32, var35 + 1);
            var20 *= 1.0F;
            var20++;
            float var21 = (float)this.calc(var32, var35 - 1);
            var21 *= 1.0F;
            var21++;
            float var22 = var18 * 700.0F;
            float var23 = var19 * 700.0F;
            float var24 = var20 * 700.0F;
            float var25 = var21 * 700.0F;
            var16.set(var10.x, var10.y, var22 - var23);
            var17.set(var10.y, var10.x, var24 - var25);
            var16.normalize();
            var17.normalize();
            Vector3 var26 = var16.cross(var17);
            ((VertexPositionNormalTangentTextureSkin)var50).Normal.x(var26.x());
            ((VertexPositionNormalTangentTextureSkin)var50).Normal.y(var26.z());
            ((VertexPositionNormalTangentTextureSkin)var50).Normal.z(var26.y());
            ((VertexPositionNormalTangentTextureSkin)var50).Normal.normalize();
            System.out
               .println(
                  ((VertexPositionNormalTangentTextureSkin)var50).Normal.x()
                     + " , "
                     + ((VertexPositionNormalTangentTextureSkin)var50).Normal.y()
                     + ", "
                     + ((VertexPositionNormalTangentTextureSkin)var50).Normal.z()
               );
            ((VertexPositionNormalTangentTextureSkin)var50).Normal.normalize();
            var11++;
         }
      }

      var11 = 0;

      for (int var33 = 0; var33 < var8 - 1; var33++) {
         if ((var33 & 1) == 0) {
            for (int var37 = 0; var37 < var7; var37++) {
               var9.add(var37 + (var33 + 1) * var7);
               var9.add(var37 + var33 * var7);
               var11++;
               var11++;
            }
         } else {
            for (int var36 = var7 - 1; var36 > 0; var36--) {
               var9.add(var36 - 1 + var33 * var7);
               var9.add(var36 + (var33 + 1) * var7);
               var11++;
               var11++;
            }
         }
      }

      if ((var7 & 1) > 0 && var8 > 2) {
         var9.add((var8 - 1) * var7);
         var11++;
      }

      this.vb = new VertexBufferObject();
      ByteBuffer var34 = BufferUtils.createByteBuffer(var5.size() * 36);

      for (int var38 = 0; var38 < var5.size(); var38++) {
         VertexPositionNormalTangentTextureSkin var47 = (VertexPositionNormalTangentTextureSkin)var5.get(var38);
         var34.putFloat(var47.Position.x());
         var34.putFloat(var47.Position.y());
         var34.putFloat(var47.Position.z());
         var34.putFloat(var47.Normal.x());
         var34.putFloat(var47.Normal.y());
         var34.putFloat(var47.Normal.z());
         byte var52 = -1;
         var34.putInt(var52);
         var34.putFloat(var47.TextureCoordinates.x);
         var34.putFloat(var47.TextureCoordinates.y);
      }

      var34.flip();
      int[] var39 = new int[var9.size()];

      for (int var48 = 0; var48 < var9.size(); var48++) {
         Integer var53 = (Integer)var9.get(var9.size() - 1 - var48);
         var39[var48] = var53;
      }

      this.vb._handle = this.vb.LoadSoftwareVBO(var34, this.vb._handle, var39);
      this.buffer = var34;
   }

   double calcTerrain(float var1, float var2) {
      var1 *= 10.0F;
      var2 *= 10.0F;
      double var3 = this.noise.eval(var1 / 900.0F, var2 / 600.0F, 0.0);
      var3 += this.noise.eval(var1 / 600.0F, var2 / 600.0F, 0.0) / 4.0;
      var3 += (this.noise.eval(var1 / 300.0F, var2 / 300.0F, 0.0) + 1.0) / 8.0;
      var3 += (this.noise.eval(var1 / 150.0F, var2 / 150.0F, 0.0) + 1.0) / 16.0;
      var3 += (this.noise.eval(var1 / 75.0F, var2 / 75.0F, 0.0) + 1.0) / 32.0;
      double var5 = (this.noise.eval(var1, var2, 0.0) + 1.0) / 2.0;
      var5 *= (this.noise.eval(var1, var2, 0.0) + 1.0) / 2.0;
      return var3;
   }

   double calc(float var1, float var2) {
      return this.calcTerrain(var1, var2);
   }

   public void pushView(int var1, int var2, int var3) {
      GL11.glDepthMask(false);
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      float var4 = 0.6F;
      byte var5 = 0;
      byte var6 = 0;
      int var7 = var5 + IsoCamera.getOffscreenWidth(IsoPlayer.getPlayerIndex());
      int var8 = var6 + IsoCamera.getOffscreenHeight(IsoPlayer.getPlayerIndex());
      double var9 = IsoUtils.XToIso(var5, var6, 0.0F);
      double var11 = IsoUtils.YToIso(0.0F, 0.0F, 0.0F);
      double var13 = IsoUtils.XToIso(Core.getInstance().getOffscreenWidth(IsoPlayer.getPlayerIndex()), 0.0F, 0.0F);
      double var15 = IsoUtils.YToIso(var7, var6, 0.0F);
      double var17 = IsoUtils.XToIso(var7, var8, 0.0F);
      double var19 = IsoUtils.YToIso(
         Core.getInstance().getOffscreenWidth(IsoPlayer.getPlayerIndex()), Core.getInstance().getOffscreenHeight(IsoPlayer.getPlayerIndex()), 6.0F
      );
      double var21 = IsoUtils.XToIso(-128.0F, Core.getInstance().getOffscreenHeight(IsoPlayer.getPlayerIndex()), 6.0F);
      double var23 = IsoUtils.YToIso(var5, var8, 0.0F);
      double var25 = var17 - var9;
      double var27 = var23 - var15;
      var25 = Math.abs(Core.getInstance().getOffscreenWidth(0)) / 1920.0F;
      var27 = Math.abs(Core.getInstance().getOffscreenHeight(0)) / 1080.0F;
      GL11.glLoadIdentity();
      GL11.glOrtho(-var25 / 2.0, var25 / 2.0, -var27 / 2.0, var27 / 2.0, -10.0, 10.0);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      GL11.glScaled(scale, scale, scale);
      GL11.glRotatef(isoAngle, 1.0F, 0.0F, 0.0F);
      GL11.glRotatef(135.0F, 0.0F, 1.0F, 0.0F);
      GL11.glTranslated(IsoWorld.instance.CurrentCell.ChunkMap[0].getWidthInTiles() / 2, 0.0, IsoWorld.instance.CurrentCell.ChunkMap[0].getWidthInTiles() / 2);
      GL11.glDepthRange(-100.0, 100.0);
   }

   public void popView() {
      GL11.glEnable(3008);
      GL11.glDepthFunc(519);
      GL11.glDepthMask(false);
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      GL11.glMatrixMode(5888);
      GL11.glPopMatrix();
   }

   public void render() {
      GL11.glPushClientAttrib(-1);
      GL11.glPushAttrib(1048575);
      GL11.glDisable(2884);
      GL11.glEnable(2929);
      GL11.glDepthFunc(519);
      GL11.glColorMask(true, true, true, true);
      GL11.glAlphaFunc(519, 0.0F);
      GL11.glDepthFunc(519);
      GL11.glDepthRange(-10.0, 10.0);
      GL11.glEnable(2903);
      GL11.glEnable(2896);
      GL11.glEnable(16384);
      GL11.glEnable(16385);
      GL11.glEnable(2929);
      GL11.glDisable(3008);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glDisable(3008);
      GL11.glAlphaFunc(519, 0.0F);
      GL11.glDisable(3089);
      this.doLighting();
      GL11.glDisable(2929);
      GL11.glEnable(3553);
      GL11.glBlendFunc(770, 771);
      GL11.glCullFace(1029);
      this.pushView(IsoPlayer.getInstance().getCurrentSquare().getChunk().wx / 30 * 300, IsoPlayer.getInstance().getCurrentSquare().getChunk().wy / 30 * 300, 0);
      Texture.getSharedTexture("media/textures/grass.png").bind();
      this.vb.DrawStrip(null);
      this.popView();
      GL11.glEnable(3042);
      GL11.glDisable(3008);
      GL11.glDisable(2929);
      GL11.glEnable(6144);
      if (PerformanceSettings.ModelLighting) {
         GL11.glDisable(2903);
         GL11.glDisable(2896);
         GL11.glDisable(16384);
         GL11.glDisable(16385);
      }

      GL11.glDepthRange(0.0, 100.0);
      SpriteRenderer.ringBuffer.restoreVBOs = true;
      GL11.glEnable(2929);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(3008);
      GL11.glAlphaFunc(516, 0.0F);
      GL11.glEnable(3553);
      GL11.glPopAttrib();
      GL11.glPopClientAttrib();
   }

   private void doLighting() {
      temp.order(ByteOrder.nativeOrder());
      temp.clear();
      GL11.glColorMaterial(1032, 5634);
      GL11.glDisable(2903);
      GL11.glEnable(3042);
      GL11.glBlendFunc(770, 771);
      GL11.glEnable(2896);
      GL11.glEnable(16384);
      GL11.glDisable(16385);
      lightAmbient[0] = 0.7F;
      lightAmbient[1] = 0.7F;
      lightAmbient[2] = 0.7F;
      lightAmbient[3] = 0.5F;
      lightDiffuse[0] = 0.5F;
      lightDiffuse[1] = 0.5F;
      lightDiffuse[2] = 0.5F;
      lightDiffuse[3] = 1.0F;
      Vector3 var1 = new Vector3(1.0F, 1.0F, 1.0F);
      var1.normalize();
      lightPosition[0] = -var1.x();
      lightPosition[1] = var1.y();
      lightPosition[2] = -var1.z();
      lightPosition[3] = 0.0F;
      GL11.glLightfv(16384, 4608, temp.asFloatBuffer().put(lightAmbient).flip());
      GL11.glLightfv(16384, 4609, temp.asFloatBuffer().put(lightDiffuse).flip());
      GL11.glLightfv(16384, 4611, temp.asFloatBuffer().put(lightPosition).flip());
      GL11.glLightf(16384, 4615, 0.0F);
      GL11.glLightf(16384, 4616, 0.0F);
      GL11.glLightf(16384, 4617, 0.0F);
      specular[0] = 0.0F;
      specular[1] = 0.0F;
      specular[2] = 0.0F;
      specular[3] = 0.0F;
      GL11.glMaterialfv(1032, 4610, temp.asFloatBuffer().put(specular).flip());
      GL11.glMaterialfv(1032, 5633, temp.asFloatBuffer().put(specular).flip());
      GL11.glMaterialfv(1032, 5632, temp.asFloatBuffer().put(specular).flip());
      ambient[0] = 0.6F;
      ambient[1] = 0.6F;
      ambient[2] = 0.6F;
      ambient[3] = 1.0F;
      diffuse[0] = 0.6F;
      diffuse[1] = 0.6F;
      diffuse[2] = 0.6F;
      diffuse[3] = 0.6F;
      GL11.glMaterialfv(1032, 4608, temp.asFloatBuffer().put(ambient).flip());
      GL11.glMaterialfv(1032, 4609, temp.asFloatBuffer().put(diffuse).flip());
   }
}
