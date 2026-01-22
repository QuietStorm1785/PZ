#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/VBOLines.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include "zombie/vehicles/BaseVehicle/QuaternionfObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/UI3DScene/Plane.h"
#include "zombie/vehicles/UI3DScene/PlaneObjectPool.h"
#include "zombie/vehicles/UI3DScene/Ray.h"
#include "zombie/vehicles/UI3DScene/RayObjectPool.h"
#include "zombie/worldMap/WorldMapRenderer/CharacterModelCamera.h"
#include "zombie/worldMap/WorldMapRenderer/Drawer.h"
#include "zombie/worldMap/WorldMapRenderer/WorldMapBooleanOption.h"
#include "zombie/worldMap/styles/WorldMapStyle.h"

namespace zombie {
namespace worldMap {


class WorldMapRenderer {
public:
    WorldMap m_worldMap;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_zoom = 0;
    float m_zoomF = 0.0F;
    float m_displayZoomF = 0.0F;
    float m_centerWorldX;
    float m_centerWorldY;
    float m_zoomUIX;
    float m_zoomUIY;
    float m_zoomWorldX;
    float m_zoomWorldY;
    const Matrix4f m_projection = std::make_shared<Matrix4f>();
    const Matrix4f m_modelView = std::make_shared<Matrix4f>();
    const Quaternionf m_modelViewChange = std::make_shared<Quaternionf>();
    long m_viewChangeTime;
    static long VIEW_CHANGE_TIME = 350L;
    bool m_isometric;
    bool m_firstUpdate = false;
    WorldMapVisited m_visited;
   private const Drawer[] m_drawer = new Drawer[3];
    const CharacterModelCamera m_CharacterModelCamera = std::make_shared<CharacterModelCamera>();
    int m_dropShadowWidth = 12;
    WorldMapStyle m_style = nullptr;
    static const VBOLines m_vboLines = std::make_shared<VBOLines>();
    static const VBOLinesUV m_vboLinesUV = std::make_shared<VBOLinesUV>();
   private const int[] m_viewport = new int[]{0, 0, 0, 0};
   private static const ThreadLocal<ObjectPool<Plane>> TL_Plane_pool = ThreadLocal.withInitial(PlaneObjectPool::new);
   private static const ThreadLocal<ObjectPool<Ray>> TL_Ray_pool = ThreadLocal.withInitial(RayObjectPool::new);
    static const float SMALL_NUM = 1.0E-8F;
   private const std::vector<ConfigOption> options = std::make_unique<std::vector<>>();
    const WorldMapBooleanOption BlurUnvisited = std::make_shared<WorldMapBooleanOption>(this, "BlurUnvisited", true);
    const WorldMapBooleanOption BuildingsWithoutFeatures = std::make_shared<WorldMapBooleanOption>(this, "BuildingsWithoutFeatures", false);
    const WorldMapBooleanOption DebugInfo = std::make_shared<WorldMapBooleanOption>(this, "DebugInfo", false);
    const WorldMapBooleanOption CellGrid = std::make_shared<WorldMapBooleanOption>(this, "CellGrid", false);
    const WorldMapBooleanOption TileGrid = std::make_shared<WorldMapBooleanOption>(this, "TileGrid", false);
    const WorldMapBooleanOption UnvisitedGrid = std::make_shared<WorldMapBooleanOption>(this, "UnvisitedGrid", true);
    const WorldMapBooleanOption Features = std::make_shared<WorldMapBooleanOption>(this, "Features", true);
    const WorldMapBooleanOption ForestZones = std::make_shared<WorldMapBooleanOption>(this, "ForestZones", false);
    const WorldMapBooleanOption HideUnvisited = std::make_shared<WorldMapBooleanOption>(this, "HideUnvisited", false);
    const WorldMapBooleanOption HitTest = std::make_shared<WorldMapBooleanOption>(this, "HitTest", false);
    const WorldMapBooleanOption ImagePyramid = std::make_shared<WorldMapBooleanOption>(this, "ImagePyramid", false);
    const WorldMapBooleanOption Isometric = std::make_shared<WorldMapBooleanOption>(this, "Isometric", true);
    const WorldMapBooleanOption LineString = std::make_shared<WorldMapBooleanOption>(this, "LineString", true);
    const WorldMapBooleanOption Players = std::make_shared<WorldMapBooleanOption>(this, "Players", false);
    const WorldMapBooleanOption RemotePlayers = std::make_shared<WorldMapBooleanOption>(this, "RemotePlayers", false);
    const WorldMapBooleanOption PlayerNames = std::make_shared<WorldMapBooleanOption>(this, "PlayerNames", false);
    const WorldMapBooleanOption Symbols = std::make_shared<WorldMapBooleanOption>(this, "Symbols", true);
    const WorldMapBooleanOption Wireframe = std::make_shared<WorldMapBooleanOption>(this, "Wireframe", false);
    const WorldMapBooleanOption WorldBounds = std::make_shared<WorldMapBooleanOption>(this, "WorldBounds", true);
    const WorldMapBooleanOption MiniMapSymbols = std::make_shared<WorldMapBooleanOption>(this, "MiniMapSymbols", false);
    const WorldMapBooleanOption VisibleCells = std::make_shared<WorldMapBooleanOption>(this, "VisibleCells", false);

    public WorldMapRenderer() {
      PZArrayUtil.arrayPopulate(this.m_drawer, Drawer::new);
   }

    int getAbsoluteX() {
      return this.m_x;
   }

    int getAbsoluteY() {
      return this.m_y;
   }

    int getWidth() {
      return this.m_width;
   }

    int getHeight() {
      return this.m_height;
   }

    void calcMatrices(float var1, float var2, float var3, Matrix4f var4, Matrix4f var5) {
    int var6 = this.getWidth();
    int var7 = this.getHeight();
      var4.setOrtho(-var6 / 2.0F, var6 / 2.0F, var7 / 2.0F, -var7 / 2.0F, -2000.0F, 2000.0F);
      var5.identity();
      if (this.Isometric.getValue()) {
         var5.rotateXYZ((float) (Math.PI / 3), 0.0F, (float) (Math.PI / 4));
      }
   }

    Vector3f uiToScene(float var1, float var2, Matrix4f var3, Matrix4f var4, Vector3f var5) {
    Plane var6 = allocPlane();
      var6.point.set(0.0F);
      var6.normal.set(0.0F, 0.0F, 1.0F);
    Ray var7 = this.getCameraRay(var1, this.getHeight() - var2, var3, var4, allocRay());
      if (this.intersect_ray_plane(var6, var7, var5) != 1) {
         var5.set(0.0F);
      }

      releasePlane(var6);
      releaseRay(var7);
    return var5;
   }

    Vector3f sceneToUI(float var1, float var2, float var3, Matrix4f var4, Matrix4f var5, Vector3f var6) {
    Matrix4f var7 = allocMatrix4f();
      var7.set(var4);
      var7.mul(var5);
      this.m_viewport[0] = 0;
      this.m_viewport[1] = 0;
      this.m_viewport[2] = this.getWidth();
      this.m_viewport[3] = this.getHeight();
      var7.project(var1, var2, var3, this.m_viewport, var6);
      releaseMatrix4f(var7);
    return var6;
   }

    float uiToWorldX(float var1, float var2, float var3, float var4, float var5) {
    Matrix4f var6 = allocMatrix4f();
    Matrix4f var7 = allocMatrix4f();
      this.calcMatrices(var4, var5, var3, var6, var7);
    float var8 = this.uiToWorldX(var1, var2, var3, var4, var5, var6, var7);
      releaseMatrix4f(var6);
      releaseMatrix4f(var7);
    return var8;
   }

    float uiToWorldY(float var1, float var2, float var3, float var4, float var5) {
    Matrix4f var6 = allocMatrix4f();
    Matrix4f var7 = allocMatrix4f();
      this.calcMatrices(var4, var5, var3, var6, var7);
    float var8 = this.uiToWorldY(var1, var2, var3, var4, var5, var6, var7);
      releaseMatrix4f(var6);
      releaseMatrix4f(var7);
    return var8;
   }

    float uiToWorldX(float var1, float var2, float var3, float var4, float var5, Matrix4f var6, Matrix4f var7) {
    Vector3f var8 = this.uiToScene(var1, var2, var6, var7, allocVector3f());
    float var9 = this.getWorldScale(var3);
      var8.mul(1.0F / var9);
    float var10 = var8.x() + var4;
      releaseVector3f(var8);
    return var10;
   }

    float uiToWorldY(float var1, float var2, float var3, float var4, float var5, Matrix4f var6, Matrix4f var7) {
    Vector3f var8 = this.uiToScene(var1, var2, var6, var7, allocVector3f());
    float var9 = this.getWorldScale(var3);
      var8.mul(1.0F / var9);
    float var10 = var8.y() + var5;
      releaseVector3f(var8);
    return var10;
   }

    float worldToUIX(float var1, float var2, float var3, float var4, float var5, Matrix4f var6, Matrix4f var7) {
    float var8 = this.getWorldScale(var3);
    Vector3f var9 = this.sceneToUI((var1 - var4) * var8, (var2 - var5) * var8, 0.0F, var6, var7, allocVector3f());
    float var10 = var9.x();
      releaseVector3f(var9);
    return var10;
   }

    float worldToUIY(float var1, float var2, float var3, float var4, float var5, Matrix4f var6, Matrix4f var7) {
    float var8 = this.getWorldScale(var3);
    Vector3f var9 = this.sceneToUI((var1 - var4) * var8, (var2 - var5) * var8, 0.0F, var6, var7, allocVector3f());
    float var10 = this.getHeight() - var9.y();
      releaseVector3f(var9);
    return var10;
   }

    float worldOriginUIX(float var1, float var2) {
      return this.worldToUIX(0.0F, 0.0F, var1, var2, this.m_centerWorldY, this.m_projection, this.m_modelView);
   }

    float worldOriginUIY(float var1, float var2) {
      return this.worldToUIY(0.0F, 0.0F, var1, this.m_centerWorldX, var2, this.m_projection, this.m_modelView);
   }

    int getZoom() {
      return this.m_zoom;
   }

    float getZoomF() {
      return this.m_zoomF;
   }

    float getDisplayZoomF() {
      return this.m_displayZoomF;
   }

    float zoomMult() {
      return this.zoomMult(this.m_zoomF);
   }

    float zoomMult(float var1) {
      return (float)Math.pow(2.0, var1);
   }

    float getWorldScale(float var1) {
    int var2 = this.getHeight();
    double var3 = MapProjection.metersPerPixelAtZoom(var1, var2);
      return (float)(1.0 / var3);
   }

    void zoomAt(int var1, int var2, int var3) {
    float var4 = this.uiToWorldX(var1, var2, this.m_displayZoomF, this.m_centerWorldX, this.m_centerWorldY);
    float var5 = this.uiToWorldY(var1, var2, this.m_displayZoomF, this.m_centerWorldX, this.m_centerWorldY);
      this.m_zoomF = PZMath.clamp(this.m_zoomF + var3 / 2.0F, this.getBaseZoom(), 24.0F);
      this.m_zoom = (int)this.m_zoomF;
      this.m_zoomWorldX = var4;
      this.m_zoomWorldY = var5;
      this.m_zoomUIX = var1;
      this.m_zoomUIY = var2;
   }

    float getCenterWorldX() {
      return this.m_centerWorldX;
   }

    float getCenterWorldY() {
      return this.m_centerWorldY;
   }

    void centerOn(float var1, float var2) {
      this.m_centerWorldX = var1;
      this.m_centerWorldY = var2;
      if (this.m_displayZoomF != this.m_zoomF) {
         this.m_zoomWorldX = var1;
         this.m_zoomWorldY = var2;
         this.m_zoomUIX = this.m_width / 2.0F;
         this.m_zoomUIY = this.m_height / 2.0F;
      }
   }

    void moveView(int var1, int var2) {
      this.centerOn(this.m_centerWorldX + var1, this.m_centerWorldY + var2);
   }

    double log2(double var1) {
      return Math.log(var1) / Math.log(2.0);
   }

    float getBaseZoom() {
    double var1 = MapProjection.zoomAtMetersPerPixel((double)this.m_worldMap.getHeightInSquares() / this.getHeight(), this.getHeight());
      if (this.m_worldMap.getWidthInSquares() * this.getWorldScale((float)var1) > this.getWidth()) {
         var1 = MapProjection.zoomAtMetersPerPixel((double)this.m_worldMap.getWidthInSquares() / this.getWidth(), this.getHeight());
      }

      var1 = (int)(var1 * 2.0) / 2.0;
      return (float)var1;
   }

    void setZoom(float var1) {
      this.m_zoomF = PZMath.clamp(var1, this.getBaseZoom(), 24.0F);
      this.m_zoom = (int)this.m_zoomF;
      this.m_displayZoomF = this.m_zoomF;
   }

    void resetView() {
      this.m_zoomF = this.getBaseZoom();
      this.m_zoom = (int)this.m_zoomF;
      this.m_centerWorldX = this.m_worldMap.getMinXInSquares() + this.m_worldMap.getWidthInSquares() / 2.0F;
      this.m_centerWorldY = this.m_worldMap.getMinYInSquares() + this.m_worldMap.getHeightInSquares() / 2.0F;
      this.m_zoomWorldX = this.m_centerWorldX;
      this.m_zoomWorldY = this.m_centerWorldY;
      this.m_zoomUIX = this.getWidth() / 2.0F;
      this.m_zoomUIY = this.getHeight() / 2.0F;
   }

    Matrix4f getProjectionMatrix() {
      return this.m_projection;
   }

    Matrix4f getModelViewMatrix() {
      return this.m_modelView;
   }

    void setMap(WorldMap var1, int var2, int var3, int var4, int var5) {
      this.m_worldMap = var1;
      this.m_x = var2;
      this.m_y = var3;
      this.m_width = var4;
      this.m_height = var5;
   }

    WorldMap getWorldMap() {
      return this.m_worldMap;
   }

    void setVisited(WorldMapVisited var1) {
      this.m_visited = var1;
   }

    void updateView() {
      if (this.m_displayZoomF != this.m_zoomF) {
    float var1 = (float)(UIManager.getMillisSinceLastRender() / 750.0);
    float var2 = Math.abs(this.m_zoomF - this.m_displayZoomF);
    float var3 = var2 > 0.25F ? var2 / 0.25F : 1.0F;
         if (this.m_displayZoomF < this.m_zoomF) {
            this.m_displayZoomF = PZMath.min(this.m_displayZoomF + var1 * var3, this.m_zoomF);
         } else if (this.m_displayZoomF > this.m_zoomF) {
            this.m_displayZoomF = PZMath.max(this.m_displayZoomF - var1 * var3, this.m_zoomF);
         }

    float var4 = this.uiToWorldX(this.m_zoomUIX, this.m_zoomUIY, this.m_displayZoomF, 0.0F, 0.0F);
    float var5 = this.uiToWorldY(this.m_zoomUIX, this.m_zoomUIY, this.m_displayZoomF, 0.0F, 0.0F);
         this.m_centerWorldX = this.m_zoomWorldX - var4;
         this.m_centerWorldY = this.m_zoomWorldY - var5;
      }

      if (!this.m_firstUpdate) {
         this.m_firstUpdate = true;
         this.m_isometric = this.Isometric.getValue();
      }

      if (this.m_isometric != this.Isometric.getValue()) {
         this.m_isometric = this.Isometric.getValue();
    long var6 = System.currentTimeMillis();
         if (this.m_viewChangeTime + VIEW_CHANGE_TIME < var6) {
            this.m_modelViewChange.setFromUnnormalized(this.m_modelView);
         }

         this.m_viewChangeTime = var6;
      }

      this.calcMatrices(this.m_centerWorldX, this.m_centerWorldY, this.m_displayZoomF, this.m_projection, this.m_modelView);
    long var7 = System.currentTimeMillis();
      if (this.m_viewChangeTime + VIEW_CHANGE_TIME > var7) {
    float var8 = (float)(this.m_viewChangeTime + VIEW_CHANGE_TIME - var7) / (float)VIEW_CHANGE_TIME;
    Quaternionf var9 = allocQuaternionf().setFromUnnormalized(this.m_modelView);
         this.m_modelView.set(this.m_modelViewChange.slerp(var9, 1.0F - var8));
         releaseQuaternionf(var9);
      }
   }

    void render(UIWorldMap var1) {
      this.m_style = var1.getAPI().getStyle();
    int var2 = SpriteRenderer.instance.getMainStateIndex();
      this.m_drawer[var2].init(this, var1);
      SpriteRenderer.instance.drawGeneric(this.m_drawer[var2]);
   }

    void setDropShadowWidth(int var1) {
      this.m_dropShadowWidth = var1;
   }

    static Matrix4f allocMatrix4f() {
      return (Matrix4f)((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).alloc();
   }

    static void releaseMatrix4f(Matrix4f var0) {
      ((Matrix4fObjectPool)BaseVehicle.TL_matrix4f_pool.get()).release(var0);
   }

    static Quaternionf allocQuaternionf() {
      return (Quaternionf)((QuaternionfObjectPool)BaseVehicle.TL_quaternionf_pool.get()).alloc();
   }

    static void releaseQuaternionf(Quaternionf var0) {
      ((QuaternionfObjectPool)BaseVehicle.TL_quaternionf_pool.get()).release(var0);
   }

    static Ray allocRay() {
      return (Ray)TL_Ray_pool.get().alloc();
   }

    static void releaseRay(Ray var0) {
      TL_Ray_pool.get().release(var0);
   }

    static Plane allocPlane() {
      return (Plane)TL_Plane_pool.get().alloc();
   }

    static void releasePlane(Plane var0) {
      TL_Plane_pool.get().release(var0);
   }

    static Vector2 allocVector2() {
      return (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
   }

    static void releaseVector2(Vector2 var0) {
      ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var0);
   }

    static Vector3f allocVector3f() {
      return (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();
   }

    static void releaseVector3f(Vector3f var0) {
      ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var0);
   }

    Ray getCameraRay(float var1, float var2, Ray var3) {
      return this.getCameraRay(var1, var2, this.m_projection, this.m_modelView, var3);
   }

    Ray getCameraRay(float var1, float var2, Matrix4f var3, Matrix4f var4, Ray var5) {
    Matrix4f var6 = allocMatrix4f();
      var6.set(var3);
      var6.mul(var4);
      var6.invert();
      this.m_viewport[0] = 0;
      this.m_viewport[1] = 0;
      this.m_viewport[2] = this.getWidth();
      this.m_viewport[3] = this.getHeight();
    Vector3f var7 = var6.unprojectInv(var1, var2, 0.0F, this.m_viewport, allocVector3f());
    Vector3f var8 = var6.unprojectInv(var1, var2, 1.0F, this.m_viewport, allocVector3f());
      var5.origin.set(var7);
      var5.direction.set(var8.sub(var7).normalize());
      releaseVector3f(var8);
      releaseVector3f(var7);
      releaseMatrix4f(var6);
    return var5;
   }

    int intersect_ray_plane(Plane var1, Ray var2, Vector3f var3) {
    Vector3f var4 = allocVector3f().set(var2.direction).mul(10000.0F);
    Vector3f var5 = allocVector3f().set(var2.origin).sub(var1.point);

    uint8_t var8;
      try {
    float var6 = var1.normal.dot(var4);
    float var7 = -var1.normal.dot(var5);
         if (!(Math.abs(var6) < 1.0E-8F)) {
    float var14 = var7 / var6;
            if (!(var14 < 0.0F) && !(var14 > 1.0F)) {
               var3.set(var2.origin).push_back(var4.mul(var14));
    return 1;
            }

    return 0;
         }

         if (var7 != 0.0F) {
    return 0;
         }

         var8 = 2;
      } finally {
         releaseVector3f(var4);
         releaseVector3f(var5);
      }

    return var8;
   }

    ConfigOption getOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.options.size(); var2++) {
    ConfigOption var3 = this.options.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getOptionCount() {
      return this.options.size();
   }

    ConfigOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    void setBoolean(const std::string& var1, bool var2) {
    ConfigOption var3 = this.getOptionByName(var1);
      if (dynamic_cast<BooleanConfigOption*>(var3) != nullptr) {
         ((BooleanConfigOption)var3).setValue(var2);
      }
   }

    bool getBoolean(const std::string& var1) {
    ConfigOption var2 = this.getOptionByName(var1);
      return dynamic_cast<BooleanConfigOption*>(var2) != nullptr ? ((BooleanConfigOption)var2).getValue() : false;
   }

    void setDouble(const std::string& var1, double var2) {
    ConfigOption var4 = this.getOptionByName(var1);
      if (dynamic_cast<DoubleConfigOption*>(var4) != nullptr) {
         ((DoubleConfigOption)var4).setValue(var2);
      }
   }

    double getDouble(const std::string& var1, double var2) {
    ConfigOption var4 = this.getOptionByName(var1);
      return dynamic_cast<DoubleConfigOption*>(var4) != nullptr ? ((DoubleConfigOption)var4).getValue() : var2;
   }
}
} // namespace worldMap
} // namespace zombie
