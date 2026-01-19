package zombie.iso;

import zombie.core.Core;
import zombie.core.textures.Texture;

public class WorldMarkers$PlayerHomingPoint {
   private int ID;
   private Texture texture;
   private int x;
   private int y;
   private float r;
   private float g;
   private float b;
   private float a;
   private float angle = 0.0F;
   private float targetAngle = 0.0F;
   private boolean customTargetAngle = false;
   private float angleLerpVal = 0.25F;
   private float movementLerpVal = 0.25F;
   private int dist = 0;
   private float targRenderX = Core.getInstance().getScreenWidth() / 2.0F;
   private float targRenderY = Core.getInstance().getScreenHeight() / 2.0F;
   private float renderX = this.targRenderX;
   private float renderY = this.targRenderY;
   private float renderOffsetX = 0.0F;
   private float renderOffsetY = 50.0F;
   private float renderWidth = 32.0F;
   private float renderHeight = 32.0F;
   private float renderSizeMod = 1.0F;
   private float targetScreenX;
   private float targetScreenY;
   private boolean targetOnScreen = false;
   private float stickToCharDist = 130.0F;
   private boolean active;
   private boolean homeOnTargetInView = true;
   private int homeOnTargetDist = 20;
   private float homeOnOffsetX = 0.0F;
   private float homeOnOffsetY = 0.0F;
   private boolean isRemoved = false;

   public WorldMarkers$PlayerHomingPoint(int var1) {
      this.ID = WorldMarkers.NextHomingPointID++;
      float var2 = IsoCamera.getScreenLeft(var1);
      float var3 = IsoCamera.getScreenTop(var1);
      float var4 = IsoCamera.getScreenWidth(var1);
      float var5 = IsoCamera.getScreenHeight(var1);
      this.targRenderX = var2 + var4 / 2.0F;
      this.targRenderY = var3 + var5 / 2.0F;
   }

   public void setTexture(String var1) {
      if (var1 == null) {
         var1 = "arrow_triangle";
      }

      this.texture = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

   public void remove() {
      this.isRemoved = true;
   }

   public boolean isRemoved() {
      return this.isRemoved;
   }

   public boolean isActive() {
      return this.active;
   }

   public void setActive(boolean var1) {
      this.active = var1;
   }

   public float getR() {
      return this.r;
   }

   public void setR(float var1) {
      this.r = var1;
   }

   public float getB() {
      return this.b;
   }

   public void setB(float var1) {
      this.b = var1;
   }

   public float getG() {
      return this.g;
   }

   public void setG(float var1) {
      this.g = var1;
   }

   public float getA() {
      return this.a;
   }

   public void setA(float var1) {
      this.a = var1;
   }

   public int getHomeOnTargetDist() {
      return this.homeOnTargetDist;
   }

   public void setHomeOnTargetDist(int var1) {
      this.homeOnTargetDist = var1;
   }

   public int getID() {
      return this.ID;
   }

   public float getTargetAngle() {
      return this.targetAngle;
   }

   public void setTargetAngle(float var1) {
      this.targetAngle = var1;
   }

   public boolean isCustomTargetAngle() {
      return this.customTargetAngle;
   }

   public void setCustomTargetAngle(boolean var1) {
      this.customTargetAngle = var1;
   }

   public int getX() {
      return this.x;
   }

   public void setX(int var1) {
      this.x = var1;
   }

   public int getY() {
      return this.y;
   }

   public void setY(int var1) {
      this.y = var1;
   }

   public float getAngleLerpVal() {
      return this.angleLerpVal;
   }

   public void setAngleLerpVal(float var1) {
      this.angleLerpVal = var1;
   }

   public float getMovementLerpVal() {
      return this.movementLerpVal;
   }

   public void setMovementLerpVal(float var1) {
      this.movementLerpVal = var1;
   }

   public boolean isHomeOnTargetInView() {
      return this.homeOnTargetInView;
   }

   public void setHomeOnTargetInView(boolean var1) {
      this.homeOnTargetInView = var1;
   }

   public float getRenderWidth() {
      return this.renderWidth;
   }

   public void setRenderWidth(float var1) {
      this.renderWidth = var1;
   }

   public float getRenderHeight() {
      return this.renderHeight;
   }

   public void setRenderHeight(float var1) {
      this.renderHeight = var1;
   }

   public float getStickToCharDist() {
      return this.stickToCharDist;
   }

   public void setStickToCharDist(float var1) {
      this.stickToCharDist = var1;
   }

   public float getRenderOffsetX() {
      return this.renderOffsetX;
   }

   public void setRenderOffsetX(float var1) {
      this.renderOffsetX = var1;
   }

   public float getRenderOffsetY() {
      return this.renderOffsetY;
   }

   public void setRenderOffsetY(float var1) {
      this.renderOffsetY = var1;
   }

   public float getHomeOnOffsetX() {
      return this.homeOnOffsetX;
   }

   public void setHomeOnOffsetX(float var1) {
      this.homeOnOffsetX = var1;
   }

   public float getHomeOnOffsetY() {
      return this.homeOnOffsetY;
   }

   public void setHomeOnOffsetY(float var1) {
      this.homeOnOffsetY = var1;
   }

   public void setTableSurface() {
      this.homeOnOffsetY = -30.0F * Core.TileScale;
   }

   public void setHighCounter() {
      this.homeOnOffsetY = -50.0F * Core.TileScale;
   }

   public void setYOffsetScaled(float var1) {
      this.homeOnOffsetY = var1 * Core.TileScale;
   }

   public void setXOffsetScaled(float var1) {
      this.homeOnOffsetX = var1 * Core.TileScale;
   }
}
