package zombie.vehicles;

import java.util.ArrayList;
import org.joml.Matrix4f;
import org.joml.Vector3f;
import zombie.vehicles.UI3DScene.AABB;
import zombie.vehicles.UI3DScene.Axis;
import zombie.vehicles.UI3DScene.Box3D;
import zombie.vehicles.UI3DScene.Gizmo;
import zombie.vehicles.UI3DScene.GridPlaneDrawer;
import zombie.vehicles.UI3DScene.OverlaysDrawer;
import zombie.vehicles.UI3DScene.PositionRotation;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;
import zombie.vehicles.UI3DScene.TranslateGizmoRenderData;

final class UI3DScene$StateData {
   final Matrix4f m_projection = new Matrix4f();
   final Matrix4f m_modelView = new Matrix4f();
   int m_zoom;
   GridPlaneDrawer m_gridPlaneDrawer;
   OverlaysDrawer m_overlaysDrawer;
   final ArrayList<SceneObjectRenderData> m_objectData = new ArrayList<>();
   Gizmo m_gizmo = null;
   final Vector3f m_gizmoTranslate = new Vector3f();
   final Vector3f m_gizmoRotate = new Vector3f();
   final Matrix4f m_gizmoParentTransform = new Matrix4f();
   final Matrix4f m_gizmoOriginTransform = new Matrix4f();
   final Matrix4f m_gizmoChildTransform = new Matrix4f();
   final Matrix4f m_gizmoTransform = new Matrix4f();
   boolean m_hasGizmoOrigin;
   boolean m_selectedAttachmentIsChildAttachment;
   Axis m_gizmoAxis = Axis.None;
   final TranslateGizmoRenderData m_translateGizmoRenderData = new TranslateGizmoRenderData();
   final ArrayList<PositionRotation> m_axes = new ArrayList<>();
   final ArrayList<AABB> m_aabb = new ArrayList<>();
   final ArrayList<Box3D> m_box3D = new ArrayList<>();

   private UI3DScene$StateData() {
   }

   private float zoomMult() {
      return (float)Math.exp(this.m_zoom * 0.2F) * 160.0F / Math.max(1.82F, 1.0F);
   }
}
