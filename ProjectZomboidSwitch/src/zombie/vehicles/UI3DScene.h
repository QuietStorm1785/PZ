#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "zombie/IndieGL.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/VBOLines.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/AnimationMultiTrack.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/VehicleScript/Passenger.h"
#include "zombie/scripting/objects/VehicleScript/Position.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include "zombie/vehicles/BaseVehicle/QuaternionfObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/UI3DScene/1.h"
#include "zombie/vehicles/UI3DScene/AABB.h"
#include "zombie/vehicles/UI3DScene/Axis.h"
#include "zombie/vehicles/UI3DScene/Box3D.h"
#include "zombie/vehicles/UI3DScene/CharacterSceneModelCamera.h"
#include "zombie/vehicles/UI3DScene/Circle.h"
#include "zombie/vehicles/UI3DScene/Gizmo.h"
#include "zombie/vehicles/UI3DScene/GridPlane.h"
#include "zombie/vehicles/UI3DScene/GridPlaneDrawer.h"
#include "zombie/vehicles/UI3DScene/OriginAttachment.h"
#include "zombie/vehicles/UI3DScene/OriginBone.h"
#include "zombie/vehicles/UI3DScene/OriginGizmo.h"
#include "zombie/vehicles/UI3DScene/OverlaysDrawer.h"
#include "zombie/vehicles/UI3DScene/Plane.h"
#include "zombie/vehicles/UI3DScene/PlaneObjectPool.h"
#include "zombie/vehicles/UI3DScene/PositionRotation.h"
#include "zombie/vehicles/UI3DScene/Ray.h"
#include "zombie/vehicles/UI3DScene/RayObjectPool.h"
#include "zombie/vehicles/UI3DScene/RotateGizmo.h"
#include "zombie/vehicles/UI3DScene/ScaleGizmo.h"
#include "zombie/vehicles/UI3DScene/SceneCharacter.h"
#include "zombie/vehicles/UI3DScene/SceneModel.h"
#include "zombie/vehicles/UI3DScene/SceneObject.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"
#include "zombie/vehicles/UI3DScene/SceneVehicle.h"
#include "zombie/vehicles/UI3DScene/SetModelCamera.h"
#include "zombie/vehicles/UI3DScene/StateData.h"
#include "zombie/vehicles/UI3DScene/TransformMode.h"
#include "zombie/vehicles/UI3DScene/TranslateGizmo.h"
#include "zombie/vehicles/UI3DScene/VehicleSceneModelCamera.h"
#include "zombie/vehicles/UI3DScene/View.h"

namespace zombie {
namespace vehicles {


class UI3DScene : public UIElement {
public:
   private const std::vector<SceneObject> m_objects = std::make_unique<std::vector<>>();
    View m_view = View.Right;
    TransformMode m_transformMode = TransformMode.Local;
    int m_view_x = 0;
    int m_view_y = 0;
    const Vector3f m_viewRotation = std::make_shared<Vector3f>();
    int m_zoom = 3;
    int m_zoomMax = 10;
    int m_gridDivisions = 1;
    GridPlane m_gridPlane = GridPlane.YZ;
    const Matrix4f m_projection = std::make_shared<Matrix4f>();
    const Matrix4f m_modelView = std::make_shared<Matrix4f>();
    long VIEW_CHANGE_TIME = 350L;
    long m_viewChangeTime;
    const Quaternionf m_modelViewChange = std::make_shared<Quaternionf>();
    bool m_bDrawGrid = true;
    bool m_bDrawGridAxes = false;
    bool m_bDrawGridPlane = false;
    const CharacterSceneModelCamera m_CharacterSceneModelCamera = std::make_shared<CharacterSceneModelCamera>(this);
    const VehicleSceneModelCamera m_VehicleSceneModelCamera = std::make_shared<VehicleSceneModelCamera>(this);
   private static const ObjectPool<SetModelCamera> s_SetModelCameraPool = std::make_shared<ObjectPool>(SetModelCamera::new);
   private const StateData[] m_stateData = new StateData[3];
    Gizmo m_gizmo;
    const RotateGizmo m_rotateGizmo = std::make_shared<RotateGizmo>(this);
    const ScaleGizmo m_scaleGizmo = std::make_shared<ScaleGizmo>(this);
    const TranslateGizmo m_translateGizmo = std::make_shared<TranslateGizmo>(this);
    const Vector3f m_gizmoPos = std::make_shared<Vector3f>();
    const Vector3f m_gizmoRotate = std::make_shared<Vector3f>();
    SceneObject m_gizmoParent = nullptr;
    SceneObject m_gizmoOrigin = nullptr;
    SceneObject m_gizmoChild = nullptr;
    const OriginAttachment m_originAttachment = std::make_shared<OriginAttachment>(this);
    const OriginBone m_originBone = std::make_shared<OriginBone>(this);
    const OriginGizmo m_originGizmo = std::make_shared<OriginGizmo>(this);
    float m_gizmoScale = 1.0F;
    std::string m_selectedAttachment = nullptr;
   private const std::vector<PositionRotation> m_axes = std::make_unique<std::vector<>>();
    const OriginBone m_highlightBone = std::make_shared<OriginBone>(this);
   private static const ObjectPool<PositionRotation> s_posRotPool = std::make_shared<ObjectPool>(PositionRotation::new);
   private const std::vector<AABB> m_aabb = std::make_unique<std::vector<>>();
   private static const ObjectPool<AABB> s_aabbPool = std::make_shared<ObjectPool>(AABB::new);
   private const std::vector<Box3D> m_box3D = std::make_unique<std::vector<>>();
   private static const ObjectPool<Box3D> s_box3DPool = std::make_shared<ObjectPool>(Box3D::new);
    const Vector3f tempVector3f = std::make_shared<Vector3f>();
    const Vector4f tempVector4f = std::make_shared<Vector4f>();
   const int[] m_viewport = new int[]{0, 0, 0, 0};
    const float GRID_DARK = 0.1F;
    const float GRID_LIGHT = 0.2F;
    float GRID_ALPHA = 1.0F;
    const int HALF_GRID = 5;
    static const VBOLines vboLines = std::make_shared<VBOLines>();
   private static const ThreadLocal<ObjectPool<Ray>> TL_Ray_pool = ThreadLocal.withInitial(RayObjectPool::new);
   private static const ThreadLocal<ObjectPool<Plane>> TL_Plane_pool = ThreadLocal.withInitial(PlaneObjectPool::new);
    static const float SMALL_NUM = 1.0E-8F;

    public UI3DScene(KahluaTable var1) {
      super(var1);

      for (int var2 = 0; var2 < this.m_stateData.length; var2++) {
         this.m_stateData[var2] = std::make_unique<StateData>();
         this.m_stateData[var2].m_gridPlaneDrawer = std::make_shared<GridPlaneDrawer>(this, this);
         this.m_stateData[var2].m_overlaysDrawer = std::make_shared<OverlaysDrawer>(this);
      }
   }

    SceneObject getSceneObjectById(const std::string& var1, bool var2) {
      for (int var3 = 0; var3 < this.m_objects.size(); var3++) {
    SceneObject var4 = this.m_objects.get(var3);
         if (var4.m_id.equalsIgnoreCase(var1)) {
    return var4;
         }
      }

      if (var2) {
         throw NullPointerException("scene object \"" + var1 + "\" not found");
      } else {
    return nullptr;
      }
   }

   <C> C getSceneObjectById(std::string var1, Class<C> var2, boolean var3) {
      for (int var4 = 0; var4 < this.m_objects.size(); var4++) {
    SceneObject var5 = this.m_objects.get(var4);
         if (var5.m_id.equalsIgnoreCase(var1)) {
            if (var5.getClass() == var2) {
               return (C)var2.cast(var5);
            }

            if (var3) {
               throw ClassCastException("scene object \"" + var1 + "\" is " + var5.getClass().getSimpleName() + " expected " + var2.getSimpleName());
            }
         }
      }

      if (var3) {
         throw NullPointerException("scene object \"" + var1 + "\" not found");
      } else {
    return nullptr;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void render() {
      if (this.isVisible()) {
         super.render();
         IndieGL.glClear(256);
    StateData var1 = this.stateDataMain();
         this.calcMatrices(this.m_projection, this.m_modelView);
         var1.m_projection.set(this.m_projection);
    long var2 = System.currentTimeMillis();
         if (this.m_viewChangeTime + this.VIEW_CHANGE_TIME > var2) {
    float var4 = (float)(this.m_viewChangeTime + this.VIEW_CHANGE_TIME - var2) / (float)this.VIEW_CHANGE_TIME;
    Quaternionf var5 = allocQuaternionf().setFromUnnormalized(this.m_modelView);
            var1.m_modelView.set(this.m_modelViewChange.slerp(var5, 1.0F - var4));
            releaseQuaternionf(var5);
         } else {
            var1.m_modelView.set(this.m_modelView);
         }

         var1.m_zoom = this.m_zoom;
         if (this.m_bDrawGridPlane) {
            SpriteRenderer.instance.drawGeneric(var1.m_gridPlaneDrawer);
         }

         PZArrayUtil.forEach(var1.m_objectData, SceneObjectRenderData::release);
         var1.m_objectData.clear();

         for (int var11 = 0; var11 < this.m_objects.size(); var11++) {
    SceneObject var13 = this.m_objects.get(var11);
            if (var13.m_visible) {
               if (var13.m_autoRotate) {
                  var13.m_autoRotateAngle = (float)(var13.m_autoRotateAngle + UIManager.getMillisSinceLastRender() / 30.0);
                  if (var13.m_autoRotateAngle > 360.0F) {
                     var13.m_autoRotateAngle = 0.0F;
                  }
               }

    SceneObjectRenderData var6 = var13.renderMain();
               if (var6 != nullptr) {
                  var1.m_objectData.push_back(var6);
               }
            }
         }

    float var12 = Mouse.getXA() - this.getAbsoluteX().intValue();
    float var14 = Mouse.getYA() - this.getAbsoluteY().intValue();
         var1.m_gizmo = this.m_gizmo;
         if (this.m_gizmo != nullptr) {
            var1.m_gizmoTranslate.set(this.m_gizmoPos);
            var1.m_gizmoRotate.set(this.m_gizmoRotate);
            var1.m_gizmoTransform.translation(this.m_gizmoPos);
            var1.m_gizmoTransform
               .rotateXYZ(
                  this.m_gizmoRotate.x * (float) (Math.PI / 180.0),
                  this.m_gizmoRotate.y * (float) (Math.PI / 180.0),
                  this.m_gizmoRotate.z * (float) (Math.PI / 180.0)
               );
            var1.m_gizmoAxis = this.m_gizmo.hitTest(var12, var14);
         }

         var1.m_gizmoChildTransform.identity();
         var1.m_selectedAttachmentIsChildAttachment = this.m_gizmoChild != nullptr
            && this.m_gizmoChild.m_attachment != nullptr
            && this.m_gizmoChild.m_attachment == this.m_selectedAttachment);
         if (this.m_gizmoChild != nullptr) {
            this.m_gizmoChild.getLocalTransform(var1.m_gizmoChildTransform);
         }

         var1.m_gizmoOriginTransform.identity();
         var1.m_hasGizmoOrigin = this.m_gizmoOrigin != nullptr;
         if (this.m_gizmoOrigin != nullptr && this.m_gizmoOrigin != this.m_gizmoParent) {
            this.m_gizmoOrigin.getGlobalTransform(var1.m_gizmoOriginTransform);
         }

         var1.m_gizmoParentTransform.identity();
         if (this.m_gizmoParent != nullptr) {
            this.m_gizmoParent.getGlobalTransform(var1.m_gizmoParentTransform);
         }

         var1.m_overlaysDrawer.init();
         SpriteRenderer.instance.drawGeneric(var1.m_overlaysDrawer);
         if (this.m_bDrawGrid) {
    Vector3f var15 = this.uiToScene(var12, var14, 0.0F, this.tempVector3f);
            if (this.m_view == View.UserDefined) {
    Vector3f var7 = allocVector3f();
               switch (1.$SwitchMap$zombie$vehicles$UI3DScene$GridPlane[this.m_gridPlane.ordinal()]) {
                  case 1:
                     var7.set(0.0F, 0.0F, 1.0F);
                     break;
                  case 2:
                     var7.set(0.0F, 1.0F, 0.0F);
                     break;
                  case 3:
                     var7.set(1.0F, 0.0F, 0.0F);
               }

    Vector3f var8 = allocVector3f().set(0.0F);
    Plane var9 = allocPlane().set(var7, var8);
               releaseVector3f(var7);
               releaseVector3f(var8);
    Ray var10 = this.getCameraRay(var12, this.screenHeight() - var14, allocRay());
               if (intersect_ray_plane(var9, var10, var15) != 1) {
                  var15.set(0.0F);
               }

               releasePlane(var9);
               releaseRay(var10);
            }

            var15.x = Math.round(var15.x * this.gridMult()) / this.gridMult();
            var15.y = Math.round(var15.y * this.gridMult()) / this.gridMult();
            var15.z = Math.round(var15.z * this.gridMult()) / this.gridMult();
            this.DrawText(UIFont.Small, std::string.valueOf(var15.x), this.width - 200.0F, 10.0, 1.0, 0.0, 0.0, 1.0);
            this.DrawText(UIFont.Small, std::string.valueOf(var15.y), this.width - 150.0F, 10.0, 0.0, 1.0, 0.0, 1.0);
            this.DrawText(UIFont.Small, std::string.valueOf(var15.z), this.width - 100.0F, 10.0, 0.0, 0.5, 1.0, 1.0);
         }

         if (this.m_gizmo == this.m_rotateGizmo && this.m_rotateGizmo.m_trackAxis != Axis.None) {
    Vector3f var16 = this.m_rotateGizmo.m_startXfrm.getTranslation(allocVector3f());
    float var18 = this.sceneToUIX(var16.x, var16.y, var16.z);
    float var20 = this.sceneToUIY(var16.x, var16.y, var16.z);
            LineDrawer.drawLine(var18, var20, var12, var14, 0.5F, 0.5F, 0.5F, 1.0F, 1);
            releaseVector3f(var16);
         }

         if (this.m_highlightBone.m_boneName != nullptr) {
    Matrix4f var17 = this.m_highlightBone.getGlobalTransform(allocMatrix4f());
            this.m_highlightBone.m_character.getGlobalTransform(allocMatrix4f()).mul(var17, var17);
    Vector3f var19 = var17.getTranslation(allocVector3f());
    float var21 = this.sceneToUIX(var19.x, var19.y, var19.z);
    float var22 = this.sceneToUIY(var19.x, var19.y, var19.z);
            LineDrawer.drawCircle(var21, var22, 10.0F, 16, 1.0F, 1.0F, 1.0F);
            releaseVector3f(var19);
            releaseMatrix4f(var17);
         }
      }
   }

    float gridMult() {
      return 100 * this.m_gridDivisions;
   }

    float zoomMult() {
      return (float)Math.exp(this.m_zoom * 0.2F) * 160.0F / Math.max(1.82F, 1.0F);
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

    void* fromLua0(const std::string& var1) {
      switch (var1) {
         case "clearAABBs":
            s_aabbPool.release(this.m_aabb);
            this.m_aabb.clear();
    return nullptr;
         case "clearAxes":
            s_posRotPool.release(this.m_axes);
            this.m_axes.clear();
    return nullptr;
         case "clearBox3Ds":
            s_box3DPool.release(this.m_box3D);
            this.m_box3D.clear();
    return nullptr;
         case "clearGizmoRotate":
            this.m_gizmoRotate.set(0.0F);
    return nullptr;
         case "clearHighlightBone":
            this.m_highlightBone.m_boneName = nullptr;
    return nullptr;
         case "getGizmoPos":
            return this.m_gizmoPos;
         case "getGridMult":
            return BoxedStaticValues.toDouble(this.gridMult());
         case "getView":
            return this.m_view.name();
         case "getViewRotation":
            return this.m_viewRotation;
         case "getModelCount":
    int var4 = 0;

            for (int var5 = 0; var5 < this.m_objects.size(); var5++) {
               if (this.m_objects.get(var5) instanceof SceneModel) {
                  var4++;
               }
            }

            return BoxedStaticValues.toDouble(var4);
         case "stopGizmoTracking":
            if (this.m_gizmo != nullptr) {
               this.m_gizmo.stopTracking();
            }

    return nullptr;
         default:
            throw IllegalArgumentException("unhandled \"" + var1 + "\"");
      }
   }

    void* fromLua1(const std::string& var1, void* var2) {
      switch (var1) {
         case "createCharacter":
    SceneObject var30 = this.getSceneObjectById((std::string)var2, false);
            if (var30 != nullptr) {
               throw IllegalStateException("scene object \"" + var2 + "\" exists");
            }

    SceneCharacter var37 = std::make_shared<SceneCharacter>(this, (std::string)var2);
            this.m_objects.push_back(var37);
    return var37;
         case "createVehicle":
    SceneObject var29 = this.getSceneObjectById((std::string)var2, false);
            if (var29 != nullptr) {
               throw IllegalStateException("scene object \"" + var2 + "\" exists");
            }

    SceneVehicle var36 = std::make_shared<SceneVehicle>(this, (std::string)var2);
            this.m_objects.push_back(var36);
    return nullptr;
         case "getCharacterAnimationDuration":
    SceneCharacter var28 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    AnimationPlayer var35 = var28.m_animatedModel.getAnimationPlayer();
            if (var35 == nullptr) {
    return nullptr;
            } else {
    AnimationMultiTrack var43 = var35.getMultiTrack();
               if (var43 != nullptr && !var43.getTracks().empty()) {
                  return KahluaUtil.toDouble(((AnimationTrack)var43.getTracks().get(0)).getDuration());
               }

    return nullptr;
            }
         case "getCharacterAnimationTime":
    SceneCharacter var27 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    AnimationPlayer var34 = var27.m_animatedModel.getAnimationPlayer();
            if (var34 == nullptr) {
    return nullptr;
            } else {
    AnimationMultiTrack var42 = var34.getMultiTrack();
               if (var42 != nullptr && !var42.getTracks().empty()) {
                  return KahluaUtil.toDouble(((AnimationTrack)var42.getTracks().get(0)).getCurrentTimeValue());
               }

    return nullptr;
            }
         case "getModelScript":
    int var26 = 0;

            for (int var33 = 0; var33 < this.m_objects.size(); var33++) {
    SceneModel var41 = (SceneModel)Type.tryCastTo(this.m_objects.get(var33), SceneModel.class);
               if (var41 != nullptr && var26++ == ((double)var2).intValue()) {
                  return var41.m_modelScript;
               }
            }

    return nullptr;
         case "getObjectAutoRotate":
    SceneObject var25 = this.getSceneObjectById((std::string)var2, true);
            return var25.m_autoRotate ? bool.TRUE : bool.FALSE;
         case "getObjectParent":
    SceneObject var24 = this.getSceneObjectById((std::string)var2, true);
            return var24.m_parent == nullptr ? nullptr : var24.m_parent.m_id;
         case "getObjectParentAttachment":
    SceneObject var23 = this.getSceneObjectById((std::string)var2, true);
            return var23.m_parentAttachment;
         case "getObjectRotation":
    SceneObject var22 = this.getSceneObjectById((std::string)var2, true);
            return var22.m_rotate;
         case "getObjectTranslation":
    SceneObject var21 = this.getSceneObjectById((std::string)var2, true);
            return var21.m_translate;
         case "getVehicleScript":
    SceneVehicle var20 = this.getSceneObjectById((std::string)var2, SceneVehicle.class, true);
            return var20.m_script;
         case "isCharacterFemale":
    SceneCharacter var19 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            return var19.m_animatedModel.isFemale();
         case "isObjectVisible":
    SceneObject var18 = this.getSceneObjectById((std::string)var2, true);
            return var18.m_visible ? bool.TRUE : bool.FALSE;
         case "removeModel":
    SceneModel var17 = this.getSceneObjectById((std::string)var2, SceneModel.class, true);
            this.m_objects.remove(var17);

            for (SceneObject var40 : this.m_objects) {
               if (var40.m_parent == var17) {
                  var40.m_attachment = nullptr;
                  var40.m_parent = nullptr;
                  var40.m_parentAttachment = nullptr;
               }
            }

    return nullptr;
         case "setDrawGrid":
            this.m_bDrawGrid = (bool)var2;
    return nullptr;
         case "setDrawGridAxes":
            this.m_bDrawGridAxes = (bool)var2;
    return nullptr;
         case "setDrawGridPlane":
            this.m_bDrawGridPlane = (bool)var2;
    return nullptr;
         case "setGizmoOrigin":
    std::string var16 = (std::string)var2;
    uint8_t var39 = -1;
            switch (var16.hashCode()) {
               case 3387192:
                  if (var16 == "none")) {
                     var39 = 0;
                  }
               default:
                  switch (var39) {
                     case 0:
                        this.m_gizmoParent = nullptr;
                        this.m_gizmoOrigin = nullptr;
                        this.m_gizmoChild = nullptr;
                     default:
    return nullptr;
                  }
            }
         case "setGizmoPos":
    Vector3f var15 = (Vector3f)var2;
            if (!this.m_gizmoPos == var15)) {
               this.m_gizmoPos.set(var15);
            }

    return nullptr;
         case "setGizmoRotate":
    Vector3f var14 = (Vector3f)var2;
            if (!this.m_gizmoRotate == var14)) {
               this.m_gizmoRotate.set(var14);
            }

    return nullptr;
         case "setGizmoScale":
            this.m_gizmoScale = Math.max(((double)var2).floatValue(), 0.01F);
    return nullptr;
         case "setGizmoVisible":
    std::string var13 = (std::string)var2;
            this.m_rotateGizmo.m_visible = "rotate".equalsIgnoreCase(var13);
            this.m_scaleGizmo.m_visible = "scale".equalsIgnoreCase(var13);
            this.m_translateGizmo.m_visible = "translate".equalsIgnoreCase(var13);
            switch (var13) {
               case "rotate":
                  this.m_gizmo = this.m_rotateGizmo;
                  break;
               case "scale":
                  this.m_gizmo = this.m_scaleGizmo;
                  break;
               case "translate":
                  this.m_gizmo = this.m_translateGizmo;
                  break;
               default:
                  this.m_gizmo = nullptr;
            }

    return nullptr;
         case "setGridMult":
            this.m_gridDivisions = PZMath.clamp(((double)var2).intValue(), 1, 100);
    return nullptr;
         case "setGridPlane":
            this.m_gridPlane = GridPlane.valueOf((std::string)var2);
    return nullptr;
         case "setMaxZoom":
            this.m_zoomMax = PZMath.clamp(((double)var2).intValue(), 1, 20);
    return nullptr;
         case "setSelectedAttachment":
            this.m_selectedAttachment = (std::string)var2;
    return nullptr;
         case "setTransformMode":
            this.m_transformMode = TransformMode.valueOf((std::string)var2);
    return nullptr;
         case "setZoom":
            this.m_zoom = PZMath.clamp(((double)var2).intValue(), 1, this.m_zoomMax);
            this.calcMatrices(this.m_projection, this.m_modelView);
    return nullptr;
         case "setView":
    View var12 = this.m_view;
            this.m_view = View.valueOf((std::string)var2);
            if (var12 != this.m_view) {
    long var31 = System.currentTimeMillis();
               if (this.m_viewChangeTime + this.VIEW_CHANGE_TIME < var31) {
                  this.m_modelViewChange.setFromUnnormalized(this.m_modelView);
               }

               this.m_viewChangeTime = var31;
            }

            this.calcMatrices(this.m_projection, this.m_modelView);
    return nullptr;
         case "zoom":
    int var5 = -((double)var2).intValue();
    float var6 = Mouse.getXA() - this.getAbsoluteX().intValue();
    float var7 = Mouse.getYA() - this.getAbsoluteY().intValue();
    float var8 = this.uiToSceneX(var6, var7);
    float var9 = this.uiToSceneY(var6, var7);
            this.m_zoom = PZMath.clamp(this.m_zoom + var5, 1, this.m_zoomMax);
            this.calcMatrices(this.m_projection, this.m_modelView);
    float var10 = this.uiToSceneX(var6, var7);
    float var11 = this.uiToSceneY(var6, var7);
            this.m_view_x = (int)(this.m_view_x - (var10 - var8) * this.zoomMult());
            this.m_view_y = (int)(this.m_view_y + (var11 - var9) * this.zoomMult());
            this.calcMatrices(this.m_projection, this.m_modelView);
    return nullptr;
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\"", var1, var2));
      }
   }

    void* fromLua2(const std::string& var1, void* var2, void* var3) {
      switch (var1) {
         case "addAttachment":
    SceneModel var41 = this.getSceneObjectById((std::string)var2, SceneModel.class, true);
            if (var41.m_modelScript.getAttachmentById((std::string)var3) != nullptr) {
               throw IllegalArgumentException("model script \"" + var2 + "\" already has attachment named \"" + var3 + "\"");
            }

    ModelAttachment var55 = std::make_shared<ModelAttachment>((std::string)var3);
            var41.m_modelScript.addAttachment(var55);
    return var55;
         case "addBoneAxis":
    SceneCharacter var40 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    std::string var54 = (std::string)var3;
    PositionRotation var62 = var40.getBoneAxis(var54, (PositionRotation)s_posRotPool.alloc());
            this.m_axes.push_back(var62);
    return nullptr;
         case "applyDeltaRotation":
    Vector3f var39 = (Vector3f)var2;
    Vector3f var53 = (Vector3f)var3;
            Quaternionf var61 = allocQuaternionf()
               .rotationXYZ(var39.x * (float) (Math.PI / 180.0), var39.y * (float) (Math.PI / 180.0), var39.z * (float) (Math.PI / 180.0));
            Quaternionf var70 = allocQuaternionf()
               .rotationXYZ(var53.x * (float) (Math.PI / 180.0), var53.y * (float) (Math.PI / 180.0), var53.z * (float) (Math.PI / 180.0));
            var61.mul(var70);
            var61.getEulerAnglesXYZ(var39);
            releaseQuaternionf(var61);
            releaseQuaternionf(var70);
            var39.mul(180.0F / (float)Math.PI);
            var39.x = (float)Math.floor(var39.x + 0.5F);
            var39.y = (float)Math.floor(var39.y + 0.5F);
            var39.z = (float)Math.floor(var39.z + 0.5F);
    return var39;
         case "createModel":
    SceneObject var38 = this.getSceneObjectById((std::string)var2, false);
            if (var38 != nullptr) {
               throw IllegalStateException("scene object \"" + var2 + "\" exists");
            } else {
    ModelScript var52 = ScriptManager.instance.getModelScript((std::string)var3);
               if (var52 == nullptr) {
                  throw NullPointerException("model script \"" + var3 + "\" not found");
               } else {
    Model var60 = ModelManager.instance.getLoadedModel((std::string)var3);
                  if (var60 == nullptr) {
                     throw NullPointerException("model \"" + var3 + "\" not found");
                  }

    SceneModel var69 = std::make_shared<SceneModel>(this, (std::string)var2, var52, var60);
                  this.m_objects.push_back(var69);
    return nullptr;
               }
            }
         case "dragGizmo":
    float var37 = ((double)var2).floatValue();
    float var51 = ((double)var3).floatValue();
            if (this.m_gizmo == nullptr) {
               throw NullPointerException("gizmo is nullptr");
            }

            this.m_gizmo.updateTracking(var37, var51);
    return nullptr;
         case "dragView":
    int var36 = ((double)var2).intValue();
    int var50 = ((double)var3).intValue();
            this.m_view_x -= var36;
            this.m_view_y -= var50;
            this.calcMatrices(this.m_projection, this.m_modelView);
    return nullptr;
         case "getCharacterAnimationKeyframeTimes":
    SceneCharacter var35 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    AnimationPlayer var49 = var35.m_animatedModel.getAnimationPlayer();
            if (var49 == nullptr) {
    return nullptr;
            } else {
    AnimationMultiTrack var59 = var49.getMultiTrack();
               if (var59 != nullptr && !var59.getTracks().empty()) {
    AnimationTrack var68 = (AnimationTrack)var59.getTracks().get(0);
    AnimationClip var10 = var68.getClip();
                  if (var10 == nullptr) {
    return nullptr;
                  }

                  if (var3 == nullptr) {
                     var3 = std::make_unique<std::vector>();
                  }

    std::vector var11 = (std::vector)var3;
                  var11.clear();
                  Keyframe[] var12 = var10.getKeyframes();

                  for (int var13 = 0; var13 < var12.length; var13++) {
    Keyframe var14 = var12[var13];
    double var15 = KahluaUtil.toDouble(var14.Time);
                     if (!var11.contains(var15)) {
                        var11.push_back(var15);
                     }
                  }

    return var11;
               }

    return nullptr;
            }
         case "removeAttachment":
    SceneModel var34 = this.getSceneObjectById((std::string)var2, SceneModel.class, true);
    ModelAttachment var48 = var34.m_modelScript.getAttachmentById((std::string)var3);
            if (var48 == nullptr) {
               throw IllegalArgumentException("model script \"" + var2 + "\" attachment \"" + var3 + "\" not found");
            }

            var34.m_modelScript.removeAttachment(var48);
    return nullptr;
         case "setCharacterAlpha":
    SceneCharacter var33 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var33.m_animatedModel.setAlpha(((double)var3).floatValue());
    return nullptr;
         case "setCharacterAnimate":
    SceneCharacter var32 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var32.m_animatedModel.setAnimate((bool)var3);
    return nullptr;
         case "setCharacterAnimationClip":
    SceneCharacter var31 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    AnimationSet var47 = AnimationSet.GetAnimationSet(var31.m_animatedModel.GetAnimSetName(), false);
            if (var47 == nullptr) {
    return nullptr;
            } else {
    AnimState var58 = var47.GetState(var31.m_animatedModel.getState());
               if (var58 != nullptr && !var58.m_Nodes.empty()) {
    AnimNode var67 = (AnimNode)var58.m_Nodes.get(0);
                  var67.m_AnimName = (std::string)var3;
                  var31.m_animatedModel.getAdvancedAnimator().OnAnimDataChanged(false);
                  var31.m_animatedModel.getAdvancedAnimator().SetState(var58.m_Name);
    return nullptr;
               }

    return nullptr;
            }
         case "setCharacterAnimationSpeed":
    SceneCharacter var30 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    AnimationMultiTrack var46 = var30.m_animatedModel.getAnimationPlayer().getMultiTrack();
            if (var46.getTracks().empty()) {
    return nullptr;
            }

            ((AnimationTrack)var46.getTracks().get(0)).SpeedDelta = PZMath.clamp(((double)var3).floatValue(), 0.0F, 10.0F);
    return nullptr;
         case "setCharacterAnimationTime":
    SceneCharacter var29 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var29.m_animatedModel.setTrackTime(((double)var3).floatValue());
    AnimationPlayer var45 = var29.m_animatedModel.getAnimationPlayer();
            if (var45 == nullptr) {
    return nullptr;
            } else {
    AnimationMultiTrack var57 = var45.getMultiTrack();
               if (var57 != nullptr && !var57.getTracks().empty()) {
                  ((AnimationTrack)var57.getTracks().get(0)).setCurrentTimeValue(((double)var3).floatValue());
    return nullptr;
               }

    return nullptr;
            }
         case "setCharacterAnimSet":
    SceneCharacter var28 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    std::string var44 = (std::string)var3;
            if (!var44 == var28.m_animatedModel.GetAnimSetName())) {
               var28.m_animatedModel.setAnimSetName(var44);
               var28.m_animatedModel.getAdvancedAnimator().OnAnimDataChanged(false);
    ActionGroup var56 = ActionGroup.getActionGroup(var28.m_animatedModel.GetAnimSetName());
    ActionContext var66 = var28.m_animatedModel.getActionContext();
               if (var56 != var66.getGroup()) {
                  var66.setGroup(var56);
               }

               var28.m_animatedModel
                  .getAdvancedAnimator()
                  .SetState(var66.getCurrentStateName(), PZArrayUtil.listConvert(var66.getChildStates(), var0 -> var0.name));
            }

    return nullptr;
         case "setCharacterClearDepthBuffer":
    SceneCharacter var27 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var27.m_bClearDepthBuffer = (bool)var3;
    return nullptr;
         case "setCharacterFemale":
    SceneCharacter var26 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    bool var43 = (bool)var3;
            if (var43 != var26.m_animatedModel.isFemale()) {
               var26.m_animatedModel.setOutfitName("Naked", var43, false);
            }

    return nullptr;
         case "setCharacterShowBones":
    SceneCharacter var25 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var25.m_bShowBones = (bool)var3;
    return nullptr;
         case "setCharacterUseDeferredMovement":
    SceneCharacter var24 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var24.m_bUseDeferredMovement = (bool)var3;
    return nullptr;
         case "setGizmoOrigin":
    std::string var23 = (std::string)var2;
            switch (var23) {
               case "centerOfMass":
                  this.m_gizmoParent = (SceneObject)this.getSceneObjectById((std::string)var3, SceneVehicle.class, true);
                  this.m_gizmoOrigin = this.m_gizmoParent;
                  this.m_gizmoChild = nullptr;
                  break;
               case "chassis":
    SceneVehicle var65 = this.getSceneObjectById((std::string)var3, SceneVehicle.class, true);
                  this.m_gizmoParent = var65;
                  this.m_originGizmo.m_translate.set(var65.m_script.getCenterOfMassOffset());
                  this.m_originGizmo.m_rotate.zero();
                  this.m_gizmoOrigin = this.m_originGizmo;
                  this.m_gizmoChild = nullptr;
                  break;
               case "character":
    SceneCharacter var64 = this.getSceneObjectById((std::string)var3, SceneCharacter.class, true);
                  this.m_gizmoParent = var64;
                  this.m_gizmoOrigin = this.m_gizmoParent;
                  this.m_gizmoChild = nullptr;
                  break;
               case "model":
    SceneModel var63 = this.getSceneObjectById((std::string)var3, SceneModel.class, true);
                  this.m_gizmoParent = var63;
                  this.m_gizmoOrigin = this.m_gizmoParent;
                  this.m_gizmoChild = nullptr;
                  break;
               case "vehicleModel":
    SceneVehicle var9 = this.getSceneObjectById((std::string)var3, SceneVehicle.class, true);
                  this.m_gizmoParent = var9;
                  this.m_originGizmo.m_translate.set(var9.m_script.getModel().getOffset());
                  this.m_originGizmo.m_rotate.zero();
                  this.m_gizmoOrigin = this.m_originGizmo;
                  this.m_gizmoChild = nullptr;
            }

    return nullptr;
         case "setCharacterState":
    SceneCharacter var22 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
            var22.m_animatedModel.setState((std::string)var3);
    return nullptr;
         case "setHighlightBone":
    SceneCharacter var21 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    std::string var42 = (std::string)var3;
            this.m_highlightBone.m_character = var21;
            this.m_highlightBone.m_boneName = var42;
    return nullptr;
         case "setModelUseWorldAttachment":
    SceneModel var20 = this.getSceneObjectById((std::string)var2, SceneModel.class, true);
            var20.m_useWorldAttachment = (bool)var3;
    return nullptr;
         case "setModelWeaponRotationHack":
    SceneModel var19 = this.getSceneObjectById((std::string)var2, SceneModel.class, true);
            var19.m_weaponRotationHack = (bool)var3;
    return nullptr;
         case "setObjectAutoRotate":
    SceneObject var18 = this.getSceneObjectById((std::string)var2, true);
            var18.m_autoRotate = (bool)var3;
            if (!var18.m_autoRotate) {
               var18.m_autoRotateAngle = 0.0F;
            }

    return nullptr;
         case "setObjectVisible":
    SceneObject var17 = this.getSceneObjectById((std::string)var2, true);
            var17.m_visible = (bool)var3;
    return nullptr;
         case "setVehicleScript":
    SceneVehicle var16 = this.getSceneObjectById((std::string)var2, SceneVehicle.class, true);
            var16.setScriptName((std::string)var3);
    return nullptr;
         case "testGizmoAxis":
    int var6 = ((double)var2).intValue();
    int var7 = ((double)var3).intValue();
            if (this.m_gizmo == nullptr) {
               return "None";
            }

            return this.m_gizmo.hitTest(var6, var7);
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\" \"%s\"", var1, var2, var3));
      }
   }

    void* fromLua3(const std::string& var1, void* var2, void* var3, void* var4) {
      switch (var1) {
         case "addAxis":
    float var16 = ((double)var2).floatValue();
    float var21 = ((double)var3).floatValue();
    float var27 = ((double)var4).floatValue();
            this.m_axes.push_back(((PositionRotation)s_posRotPool.alloc()).set(var16, var21, var27));
    return nullptr;
         case "pickCharacterBone":
    SceneCharacter var15 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    float var20 = ((double)var3).floatValue();
    float var26 = ((double)var4).floatValue();
            return var15.pickBone(var20, var26);
         case "setGizmoOrigin":
    std::string var14 = (std::string)var2;
    uint8_t var25 = -1;
            switch (var14.hashCode()) {
               case 3029700:
                  if (var14 == "bone")) {
                     var25 = 0;
                  }
               default:
                  switch (var25) {
                     case 0:
    SceneCharacter var10 = this.getSceneObjectById((std::string)var3, SceneCharacter.class, true);
                        this.m_gizmoParent = var10;
                        this.m_originBone.m_character = var10;
                        this.m_originBone.m_boneName = (std::string)var4;
                        this.m_gizmoOrigin = this.m_originBone;
                        this.m_gizmoChild = nullptr;
                     default:
    return nullptr;
                  }
            }
         case "setGizmoXYZ":
    float var13 = ((double)var2).floatValue();
    float var19 = ((double)var3).floatValue();
    float var24 = ((double)var4).floatValue();
            this.m_gizmoPos.set(var13, var19, var24);
    return nullptr;
         case "startGizmoTracking":
    float var12 = ((double)var2).floatValue();
    float var18 = ((double)var3).floatValue();
    Axis var23 = Axis.valueOf((std::string)var4);
            if (this.m_gizmo != nullptr) {
               this.m_gizmo.startTracking(var12, var18, var23);
            }

    return nullptr;
         case "setViewRotation":
    float var7 = ((double)var2).floatValue();
    float var8 = ((double)var3).floatValue();
    float var9 = ((double)var4).floatValue();
            var7 %= 360.0F;
            var8 %= 360.0F;
            var9 %= 360.0F;
            this.m_viewRotation.set(var7, var8, var9);
    return nullptr;
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\" \"%s\" \"%s\"", var1, var2, var3, var4));
      }
   }

    void* fromLua4(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      switch (var1) {
         case "setGizmoOrigin":
    std::string var17 = (std::string)var2;
    uint8_t var18 = -1;
            switch (var17.hashCode()) {
               case -1963501277:
                  if (var17 == "attachment")) {
                     var18 = 0;
                  }
               default:
                  switch (var18) {
                     case 0:
    SceneObject var19 = this.getSceneObjectById((std::string)var3, true);
                        this.m_gizmoParent = this.getSceneObjectById((std::string)var4, true);
                        this.m_originAttachment.m_object = this.m_gizmoParent;
                        this.m_originAttachment.m_attachmentName = (std::string)var5;
                        this.m_gizmoOrigin = this.m_originAttachment;
                        this.m_gizmoChild = var19;
                     default:
    return nullptr;
                  }
            }
         case "setObjectParent":
    SceneObject var16 = this.getSceneObjectById((std::string)var2, true);
            var16.m_translate.zero();
            var16.m_rotate.zero();
            var16.m_attachment = (std::string)var3;
            var16.m_parent = this.getSceneObjectById((std::string)var4, false);
            var16.m_parentAttachment = (std::string)var5;
            if (var16.m_parent != nullptr && var16.m_parent.m_parent == var16) {
               var16.m_parent.m_parent = nullptr;
            }

    return nullptr;
         case "setObjectPosition":
    SceneObject var15 = this.getSceneObjectById((std::string)var2, true);
            var15.m_translate.set(((double)var3).floatValue(), ((double)var4).floatValue(), ((double)var5).floatValue());
    return nullptr;
         case "setPassengerPosition":
    SceneCharacter var8 = this.getSceneObjectById((std::string)var2, SceneCharacter.class, true);
    SceneVehicle var9 = this.getSceneObjectById((std::string)var3, SceneVehicle.class, true);
    Passenger var10 = var9.m_script.getPassengerById((std::string)var4);
            if (var10 == nullptr) {
    return nullptr;
            }

    Position var11 = var10.getPositionById((std::string)var5);
            if (var11 != nullptr) {
               this.tempVector3f.set(var9.m_script.getModel().getOffset());
               this.tempVector3f.push_back(var11.getOffset());
               this.tempVector3f.z *= -1.0F;
               var8.m_translate.set(this.tempVector3f);
               var8.m_rotate.set(var11.rotate);
               var8.m_parent = var9;
               if (var8.m_animatedModel != nullptr) {
    std::string var12 = "inside".equalsIgnoreCase(var11.getId()) ? "player-vehicle" : "player-editor";
                  if (!var12 == var8.m_animatedModel.GetAnimSetName())) {
                     var8.m_animatedModel.setAnimSetName(var12);
                     var8.m_animatedModel.getAdvancedAnimator().OnAnimDataChanged(false);
    ActionGroup var13 = ActionGroup.getActionGroup(var8.m_animatedModel.GetAnimSetName());
    ActionContext var14 = var8.m_animatedModel.getActionContext();
                     if (var13 != var14.getGroup()) {
                        var14.setGroup(var13);
                     }

                     var8.m_animatedModel
                        .getAdvancedAnimator()
                        .SetState(var14.getCurrentStateName(), PZArrayUtil.listConvert(var14.getChildStates(), var0 -> var0.name));
                  }
               }
            }

    return nullptr;
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\" \"%s\" \"%s\"", var1, var2, var3, var4));
      }
   }

    void* fromLua6(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7) {
      switch (var1) {
         case "addAABB":
    float var17 = ((double)var2).floatValue();
    float var19 = ((double)var3).floatValue();
    float var21 = ((double)var4).floatValue();
    float var23 = ((double)var5).floatValue();
    float var25 = ((double)var6).floatValue();
    float var27 = ((double)var7).floatValue();
            this.m_aabb.push_back(((AABB)s_aabbPool.alloc()).set(var17, var19, var21, var23, var25, var27, 1.0F, 1.0F, 1.0F));
    return nullptr;
         case "addAxis":
    float var16 = ((double)var2).floatValue();
    float var18 = ((double)var3).floatValue();
    float var20 = ((double)var4).floatValue();
    float var22 = ((double)var5).floatValue();
    float var24 = ((double)var6).floatValue();
    float var26 = ((double)var7).floatValue();
            this.m_axes.push_back(((PositionRotation)s_posRotPool.alloc()).set(var16, var18, var20, var22, var24, var26));
    return nullptr;
         case "addBox3D":
    Vector3f var10 = (Vector3f)var2;
    Vector3f var11 = (Vector3f)var3;
    Vector3f var12 = (Vector3f)var4;
    float var13 = ((double)var5).floatValue();
    float var14 = ((double)var6).floatValue();
    float var15 = ((double)var7).floatValue();
            this.m_box3D
               .push_back(((Box3D)s_box3DPool.alloc()).set(var10.x, var10.y, var10.z, var11.x, var11.y, var11.z, var12.x, var12.y, var12.z, var13, var14, var15));
    return nullptr;
         default:
            throw IllegalArgumentException(
               std::string.format("unhandled \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"", var1, var2, var3, var4, var5, var6, var7)
            );
      }
   }

    void* fromLua9(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7, void* var8, void* var9, void* var10) {
    uint8_t var12 = -1;
      switch (var1.hashCode()) {
         case -1149187967:
            if (var1 == "addAABB")) {
               var12 = 0;
            }
         default:
            switch (var12) {
               case 0:
    float var13 = ((double)var2).floatValue();
    float var14 = ((double)var3).floatValue();
    float var15 = ((double)var4).floatValue();
    float var16 = ((double)var5).floatValue();
    float var17 = ((double)var6).floatValue();
    float var18 = ((double)var7).floatValue();
    float var19 = ((double)var8).floatValue();
    float var20 = ((double)var9).floatValue();
    float var21 = ((double)var10).floatValue();
                  this.m_aabb.push_back(((AABB)s_aabbPool.alloc()).set(var13, var14, var15, var16, var17, var18, var19, var20, var21));
    return nullptr;
               default:
                  throw IllegalArgumentException(
                     std::string.format(
                        "unhandled \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"",
                        var1,
                        var2,
                        var3,
                        var4,
                        var5,
                        var6,
                        var7,
                        var8,
                        var9,
                        var10
                     )
                  );
            }
      }
   }

    int screenWidth() {
      return (int)this.width;
   }

    int screenHeight() {
      return (int)this.height;
   }

    float uiToSceneX(float var1, float var2) {
    float var3 = var1 - this.screenWidth() / 2.0F;
      var3 += this.m_view_x;
      return var3 / this.zoomMult();
   }

    float uiToSceneY(float var1, float var2) {
    float var3 = var2 - this.screenHeight() / 2.0F;
      var3 *= -1.0F;
      var3 -= this.m_view_y;
      return var3 / this.zoomMult();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Vector3f uiToScene(float var1, float var2, float var3, Vector3f var4) {
      this.uiToScene(nullptr, var1, var2, var3, var4);
      switch (1.$SwitchMap$zombie$vehicles$UI3DScene$View[this.m_view.ordinal()]) {
         case 1:
         case 2:
            var4.x = 0.0F;
            break;
         case 3:
         case 4:
            var4.y = 0.0F;
            break;
         case 5:
         case 6:
            var4.z = 0.0F;
      }

    return var4;
   }

    Vector3f uiToScene(Matrix4f var1, float var2, float var3, float var4, Vector3f var5) {
      var3 = this.screenHeight() - var3;
    Matrix4f var6 = allocMatrix4f();
      var6.set(this.m_projection);
      var6.mul(this.m_modelView);
      if (var1 != nullptr) {
         var6.mul(var1);
      }

      var6.invert();
      this.m_viewport[2] = this.screenWidth();
      this.m_viewport[3] = this.screenHeight();
      var6.unprojectInv(var2, var3, var4, this.m_viewport, var5);
      releaseMatrix4f(var6);
    return var5;
   }

    float sceneToUIX(float var1, float var2, float var3) {
      this.tempVector4f.set(var1, var2, var3, 1.0F);
    Matrix4f var4 = allocMatrix4f();
      var4.set(this.m_projection);
      var4.mul(this.m_modelView);
      this.m_viewport[2] = this.screenWidth();
      this.m_viewport[3] = this.screenHeight();
      var4.project(var1, var2, var3, this.m_viewport, this.tempVector3f);
      releaseMatrix4f(var4);
      return this.tempVector3f.x();
   }

    float sceneToUIY(float var1, float var2, float var3) {
      this.tempVector4f.set(var1, var2, var3, 1.0F);
    Matrix4f var4 = allocMatrix4f();
      var4.set(this.m_projection);
      var4.mul(this.m_modelView);
      int[] var5 = new int[]{0, 0, this.screenWidth(), this.screenHeight()};
      var4.project(var1, var2, var3, var5, this.tempVector3f);
      releaseMatrix4f(var4);
      return this.screenHeight() - this.tempVector3f.y();
   }

    void renderGridXY(int var1) {
      for (int var2 = -5; var2 < 5; var2++) {
         for (int var3 = 1; var3 < var1; var3++) {
            vboLines.addLine(var2 + (float)var3 / var1, -5.0F, 0.0F, var2 + (float)var3 / var1, 5.0F, 0.0F, 0.2F, 0.2F, 0.2F, this.GRID_ALPHA);
         }
      }

      for (int var4 = -5; var4 < 5; var4++) {
         for (int var9 = 1; var9 < var1; var9++) {
            vboLines.addLine(-5.0F, var4 + (float)var9 / var1, 0.0F, 5.0F, var4 + (float)var9 / var1, 0.0F, 0.2F, 0.2F, 0.2F, this.GRID_ALPHA);
         }
      }

      for (int var5 = -5; var5 <= 5; var5++) {
         vboLines.addLine(var5, -5.0F, 0.0F, var5, 5.0F, 0.0F, 0.1F, 0.1F, 0.1F, this.GRID_ALPHA);
      }

      for (int var6 = -5; var6 <= 5; var6++) {
         vboLines.addLine(-5.0F, var6, 0.0F, 5.0F, var6, 0.0F, 0.1F, 0.1F, 0.1F, this.GRID_ALPHA);
      }

      if (this.m_bDrawGridAxes) {
    uint8_t var7 = 0;
         vboLines.addLine(-5.0F, 0.0F, var7, 5.0F, 0.0F, var7, 1.0F, 0.0F, 0.0F, this.GRID_ALPHA);
         var7 = 0;
         vboLines.addLine(0.0F, -5.0F, var7, 0.0F, 5.0F, var7, 0.0F, 1.0F, 0.0F, this.GRID_ALPHA);
      }
   }

    void renderGridXZ(int var1) {
      for (int var2 = -5; var2 < 5; var2++) {
         for (int var3 = 1; var3 < var1; var3++) {
            vboLines.addLine(var2 + (float)var3 / var1, 0.0F, -5.0F, var2 + (float)var3 / var1, 0.0F, 5.0F, 0.2F, 0.2F, 0.2F, this.GRID_ALPHA);
         }
      }

      for (int var4 = -5; var4 < 5; var4++) {
         for (int var9 = 1; var9 < var1; var9++) {
            vboLines.addLine(-5.0F, 0.0F, var4 + (float)var9 / var1, 5.0F, 0.0F, var4 + (float)var9 / var1, 0.2F, 0.2F, 0.2F, this.GRID_ALPHA);
         }
      }

      for (int var5 = -5; var5 <= 5; var5++) {
         vboLines.addLine(var5, 0.0F, -5.0F, var5, 0.0F, 5.0F, 0.1F, 0.1F, 0.1F, this.GRID_ALPHA);
      }

      for (int var6 = -5; var6 <= 5; var6++) {
         vboLines.addLine(-5.0F, 0.0F, var6, 5.0F, 0.0F, var6, 0.1F, 0.1F, 0.1F, this.GRID_ALPHA);
      }

      if (this.m_bDrawGridAxes) {
    uint8_t var7 = 0;
         vboLines.addLine(-5.0F, 0.0F, var7, 5.0F, 0.0F, var7, 1.0F, 0.0F, 0.0F, this.GRID_ALPHA);
         var7 = 0;
         vboLines.addLine(var7, 0.0F, -5.0F, var7, 0.0F, 5.0F, 0.0F, 0.0F, 1.0F, this.GRID_ALPHA);
      }
   }

    void renderGridYZ(int var1) {
      for (int var2 = -5; var2 < 5; var2++) {
         for (int var3 = 1; var3 < var1; var3++) {
            vboLines.addLine(0.0F, var2 + (float)var3 / var1, -5.0F, 0.0F, var2 + (float)var3 / var1, 5.0F, 0.2F, 0.2F, 0.2F, this.GRID_ALPHA);
         }
      }

      for (int var4 = -5; var4 < 5; var4++) {
         for (int var9 = 1; var9 < var1; var9++) {
            vboLines.addLine(0.0F, -5.0F, var4 + (float)var9 / var1, 0.0F, 5.0F, var4 + (float)var9 / var1, 0.2F, 0.2F, 0.2F, this.GRID_ALPHA);
         }
      }

      for (int var5 = -5; var5 <= 5; var5++) {
         vboLines.addLine(0.0F, var5, -5.0F, 0.0F, var5, 5.0F, 0.1F, 0.1F, 0.1F, this.GRID_ALPHA);
      }

      for (int var6 = -5; var6 <= 5; var6++) {
         vboLines.addLine(0.0F, -5.0F, var6, 0.0F, 5.0F, var6, 0.1F, 0.1F, 0.1F, this.GRID_ALPHA);
      }

      if (this.m_bDrawGridAxes) {
    uint8_t var7 = 0;
         vboLines.addLine(0.0F, -5.0F, var7, 0.0F, 5.0F, var7, 0.0F, 1.0F, 0.0F, this.GRID_ALPHA);
         var7 = 0;
         vboLines.addLine(var7, 0.0F, -5.0F, var7, 0.0F, 5.0F, 0.0F, 0.0F, 1.0F, this.GRID_ALPHA);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void renderGrid() {
      vboLines.setLineWidth(1.0F);
      this.GRID_ALPHA = 1.0F;
    long var1 = System.currentTimeMillis();
      if (this.m_viewChangeTime + this.VIEW_CHANGE_TIME > var1) {
    float var3 = (float)(this.m_viewChangeTime + this.VIEW_CHANGE_TIME - var1) / (float)this.VIEW_CHANGE_TIME;
         this.GRID_ALPHA = 1.0F - var3;
         this.GRID_ALPHA = this.GRID_ALPHA * this.GRID_ALPHA;
      }

      switch (1.$SwitchMap$zombie$vehicles$UI3DScene$View[this.m_view.ordinal()]) {
         case 1:
         case 2:
            this.renderGridYZ(10);
            return;
         case 3:
         case 4:
            this.renderGridXZ(10);
            return;
         case 5:
         case 6:
            this.renderGridXY(10);
            return;
         default:
            switch (1.$SwitchMap$zombie$vehicles$UI3DScene$GridPlane[this.m_gridPlane.ordinal()]) {
               case 1:
                  this.renderGridXY(10);
                  break;
               case 2:
                  this.renderGridXZ(10);
                  break;
               case 3:
                  this.renderGridYZ(10);
            }
      }
   }

    void renderAxis(PositionRotation var1) {
      this.renderAxis(var1.pos, var1.rot);
   }

    void renderAxis(Vector3f var1, Vector3f var2) {
    StateData var3 = this.stateDataRender();
      vboLines.flush();
    Matrix4f var4 = allocMatrix4f();
      var4.set(var3.m_gizmoParentTransform);
      var4.mul(var3.m_gizmoOriginTransform);
      var4.mul(var3.m_gizmoChildTransform);
      var4.translate(var1);
      var4.rotateXYZ(var2.x * (float) (Math.PI / 180.0), var2.y * (float) (Math.PI / 180.0), var2.z * (float) (Math.PI / 180.0));
      var3.m_modelView.mul(var4, var4);
      PZGLUtil.pushAndLoadMatrix(5888, var4);
      releaseMatrix4f(var4);
    float var5 = 0.1F;
      vboLines.setLineWidth(3.0F);
      vboLines.addLine(0.0F, 0.0F, 0.0F, var5, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 1.0F);
      vboLines.addLine(0.0F, 0.0F, 0.0F, 0.0F, 0.0F + var5, 0.0F, 0.0F, 1.0F, 0.0F, 1.0F);
      vboLines.addLine(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F + var5, 0.0F, 0.0F, 1.0F, 1.0F);
      vboLines.flush();
      PZGLUtil.popMatrix(5888);
   }

    void renderAABB(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9) {
    float var10 = var4 / 2.0F;
    float var11 = var5 / 2.0F;
    float var12 = var6 / 2.0F;
      vboLines.setOffset(var1, var2, var3);
      vboLines.setLineWidth(1.0F);
    float var13 = 1.0F;
      vboLines.addLine(var10, var11, var12, -var10, var11, var12, var7, var8, var9, var13);
      vboLines.addLine(var10, var11, var12, var10, -var11, var12, var7, var8, var9, var13);
      vboLines.addLine(var10, var11, var12, var10, var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(-var10, var11, var12, -var10, -var11, var12, var7, var8, var9, var13);
      vboLines.addLine(-var10, var11, var12, -var10, var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(var10, var11, -var12, var10, -var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(var10, var11, -var12, -var10, var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(-var10, var11, -var12, -var10, -var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(var10, -var11, -var12, -var10, -var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(var10, -var11, var12, var10, -var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(-var10, -var11, var12, -var10, -var11, -var12, var7, var8, var9, var13);
      vboLines.addLine(var10, -var11, var12, -var10, -var11, var12, var7, var8, var9, var13);
      vboLines.setOffset(0.0F, 0.0F, 0.0F);
   }

    void renderAABB(float var1, float var2, float var3, Vector3f var4, Vector3f var5, float var6, float var7, float var8) {
      vboLines.setOffset(var1, var2, var3);
      vboLines.setLineWidth(1.0F);
    float var9 = 1.0F;
      vboLines.addLine(var5.x, var5.y, var5.z, var4.x, var5.y, var5.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var5.y, var5.z, var5.x, var4.y, var5.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var5.y, var5.z, var5.x, var5.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var4.x, var5.y, var5.z, var4.x, var4.y, var5.z, var6, var7, var8, var9);
      vboLines.addLine(var4.x, var5.y, var5.z, var4.x, var5.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var5.y, var4.z, var5.x, var4.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var5.y, var4.z, var4.x, var5.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var4.x, var5.y, var4.z, var4.x, var4.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var4.y, var4.z, var4.x, var4.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var4.y, var5.z, var5.x, var4.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var4.x, var4.y, var5.z, var4.x, var4.y, var4.z, var6, var7, var8, var9);
      vboLines.addLine(var5.x, var4.y, var5.z, var4.x, var4.y, var5.z, var6, var7, var8, var9);
      vboLines.setOffset(0.0F, 0.0F, 0.0F);
   }

   private void renderBox3D(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, float var11, float var12
   ) {
    StateData var13 = this.stateDataRender();
      vboLines.flush();
    Matrix4f var14 = allocMatrix4f();
      var14.identity();
      var14.translate(var1, var2, var3);
      var14.rotateXYZ(var7 * (float) (Math.PI / 180.0), var8 * (float) (Math.PI / 180.0), var9 * (float) (Math.PI / 180.0));
      var13.m_modelView.mul(var14, var14);
      PZGLUtil.pushAndLoadMatrix(5888, var14);
      releaseMatrix4f(var14);
      this.renderAABB(var1 * 0.0F, var2 * 0.0F, var3 * 0.0F, var4, var5, var6, var10, var11, var12);
      vboLines.flush();
      PZGLUtil.popMatrix(5888);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void calcMatrices(Matrix4f var1, Matrix4f var2) {
    float var3 = this.screenWidth();
    float var4 = 1366.0F / var3;
    float var5 = this.screenHeight() * var4;
      var3 = 1366.0F;
      var3 /= this.zoomMult();
      var5 /= this.zoomMult();
      var1.setOrtho(-var3 / 2.0F, var3 / 2.0F, -var5 / 2.0F, var5 / 2.0F, -10.0F, 10.0F);
    float var6 = this.m_view_x / this.zoomMult() * var4;
    float var7 = this.m_view_y / this.zoomMult() * var4;
      var1.translate(-var6, var7, 0.0F);
      var2.identity();
    float var8 = 0.0F;
    float var9 = 0.0F;
    float var10 = 0.0F;
      switch (1.$SwitchMap$zombie$vehicles$UI3DScene$View[this.m_view.ordinal()]) {
         case 1:
            var9 = 270.0F;
            break;
         case 2:
            var9 = 90.0F;
            break;
         case 3:
            var9 = 90.0F;
            var10 = 90.0F;
            break;
         case 4:
            var9 = 90.0F;
            var10 = 270.0F;
         case 5:
         default:
            break;
         case 6:
            var9 = 180.0F;
            break;
         case 7:
            var8 = this.m_viewRotation.x;
            var9 = this.m_viewRotation.y;
            var10 = this.m_viewRotation.z;
      }

      var2.rotateXYZ(var8 * (float) (Math.PI / 180.0), var9 * (float) (Math.PI / 180.0), var10 * (float) (Math.PI / 180.0));
   }

    Ray getCameraRay(float var1, float var2, Ray var3) {
      return this.getCameraRay(var1, var2, this.m_projection, this.m_modelView, var3);
   }

    Ray getCameraRay(float var1, float var2, Matrix4f var3, Matrix4f var4, Ray var5) {
    Matrix4f var6 = allocMatrix4f();
      var6.set(var3);
      var6.mul(var4);
      var6.invert();
      this.m_viewport[2] = this.screenWidth();
      this.m_viewport[3] = this.screenHeight();
    Vector3f var7 = var6.unprojectInv(var1, var2, 0.0F, this.m_viewport, allocVector3f());
    Vector3f var8 = var6.unprojectInv(var1, var2, 1.0F, this.m_viewport, allocVector3f());
      var5.origin.set(var7);
      var5.direction.set(var8.sub(var7).normalize());
      releaseVector3f(var8);
      releaseVector3f(var7);
      releaseMatrix4f(var6);
    return var5;
   }

    float closest_distance_between_lines(Ray var1, Ray var2) {
    Vector3f var3 = allocVector3f().set(var1.direction);
    Vector3f var4 = allocVector3f().set(var2.direction);
    Vector3f var5 = allocVector3f().set(var1.origin).sub(var2.origin);
    float var6 = var3.dot(var3);
    float var7 = var3.dot(var4);
    float var8 = var4.dot(var4);
    float var9 = var3.dot(var5);
    float var10 = var4.dot(var5);
    float var11 = var6 * var8 - var7 * var7;
    float var12;
    float var13;
      if (var11 < 1.0E-8F) {
         var12 = 0.0F;
         var13 = var7 > var8 ? var9 / var7 : var10 / var8;
      } else {
         var12 = (var7 * var10 - var8 * var9) / var11;
         var13 = (var6 * var10 - var7 * var9) / var11;
      }

    Vector3f var14 = var5.push_back(var3.mul(var12)).sub(var4.mul(var13));
      var1.t = var12;
      var2.t = var13;
      releaseVector3f(var3);
      releaseVector3f(var4);
      releaseVector3f(var5);
      return var14.length();
   }

    Vector3f project(Vector3f var1, Vector3f var2, Vector3f var3) {
      return var3.set(var2).mul(var1.dot(var2) / var2.dot(var2));
   }

    Vector3f reject(Vector3f var1, Vector3f var2, Vector3f var3) {
    Vector3f var4 = this.project(var1, var2, allocVector3f());
      var3.set(var1).sub(var4);
      releaseVector3f(var4);
    return var3;
   }

    static int intersect_ray_plane(Plane var0, Ray var1, Vector3f var2) {
    Vector3f var3 = allocVector3f().set(var1.direction).mul(100.0F);
    Vector3f var4 = allocVector3f().set(var1.origin).sub(var0.point);

    uint8_t var7;
      try {
    float var5 = var0.normal.dot(var3);
    float var6 = -var0.normal.dot(var4);
         if (!(Math.abs(var5) < 1.0E-8F)) {
    float var13 = var6 / var5;
            if (!(var13 < 0.0F) && !(var13 > 1.0F)) {
               var2.set(var1.origin).push_back(var3.mul(var13));
    return 1;
            }

    return 0;
         }

         if (var6 != 0.0F) {
    return 0;
         }

         var7 = 2;
      } finally {
         releaseVector3f(var3);
         releaseVector3f(var4);
      }

    return var7;
   }

    float distance_between_point_ray(Vector3f var1, Ray var2) {
    Vector3f var3 = allocVector3f().set(var2.direction).mul(100.0F);
    Vector3f var4 = allocVector3f().set(var1).sub(var2.origin);
    float var5 = var4.dot(var3);
    float var6 = var3.dot(var3);
    float var7 = var5 / var6;
    Vector3f var8 = var3.mul(var7).push_back(var2.origin);
    float var9 = var8.sub(var1).length();
      releaseVector3f(var4);
      releaseVector3f(var3);
    return var9;
   }

    float closest_distance_line_circle(Ray var1, Circle var2, Vector3f var3) {
    Plane var4 = allocPlane().set(var2.orientation, var2.center);
    Vector3f var5 = allocVector3f();
    float var6;
      if (intersect_ray_plane(var4, var1, var5) == 1) {
         var3.set(var5).sub(var2.center).normalize().mul(var2.radius).push_back(var2.center);
         var6 = var5.sub(var3).length();
      } else {
    Vector3f var7 = allocVector3f().set(var1.origin).sub(var2.center);
    Vector3f var8 = this.reject(var7, var2.orientation, allocVector3f());
         var3.set(var8.normalize().mul(var2.radius).push_back(var2.center));
         var6 = this.distance_between_point_ray(var3, var1);
         releaseVector3f(var8);
         releaseVector3f(var7);
      }

      releaseVector3f(var5);
      releasePlane(var4);
    return var6;
   }

    StateData stateDataMain() {
      return this.m_stateData[SpriteRenderer.instance.getMainStateIndex()];
   }

    StateData stateDataRender() {
      return this.m_stateData[SpriteRenderer.instance.getRenderStateIndex()];
   }
}
} // namespace vehicles
} // namespace zombie
