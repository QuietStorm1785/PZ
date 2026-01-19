package zombie.iso;

import zombie.core.Core;
import zombie.core.textures.Texture;
import zombie.iso.WorldMarkers.DirectionArrow.DebugStuff;

public class WorldMarkers$DirectionArrow {
   public static final boolean doDebug = false;
   private DebugStuff debugStuff;
   private int ID;
   private boolean active;
   private boolean isRemoved;
   private boolean isDrawOnWorld;
   private Texture renderTexture;
   private Texture texture;
   private Texture texStairsUp;
   private Texture texStairsDown;
   private Texture texDown;
   private int x;
   private int y;
   private int z;
   private float r;
   private float g;
   private float b;
   private float a;
   private float renderWidth;
   private float renderHeight;
   private float angle;
   private float angleLerpVal;
   private boolean lastWasWithinView;
   private float renderScreenX;
   private float renderScreenY;
   private boolean renderWithAngle;
   private float renderSizeMod;

   public WorldMarkers$DirectionArrow(WorldMarkers var1, int var2) {
      this.this$0 = var1;
      this.active = true;
      this.isRemoved = false;
      this.isDrawOnWorld = false;
      this.renderWidth = 32.0F;
      this.renderHeight = 32.0F;
      this.angleLerpVal = 0.25F;
      this.lastWasWithinView = true;
      this.renderWithAngle = true;
      this.renderSizeMod = 1.0F;
      if (Core.bDebug) {
      }

      this.ID = WorldMarkers.NextHomingPointID++;
   }

   public void setTexture(String var1) {
      if (var1 == null) {
         var1 = "dir_arrow_up";
      }

      this.texture = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

   public void setTexDown(String var1) {
      this.texDown = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

   public void setTexStairsDown(String var1) {
      this.texStairsDown = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
   }

   public void setTexStairsUp(String var1) {
      this.texStairsUp = Texture.getSharedTexture("media/textures/highlights/" + var1 + ".png");
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

   public void setRGBA(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
   }

   public int getID() {
      return this.ID;
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

   public int getZ() {
      return this.z;
   }

   public void setZ(int var1) {
      this.z = var1;
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
}
