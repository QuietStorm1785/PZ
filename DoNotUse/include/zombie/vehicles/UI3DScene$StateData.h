#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector3f.h"
#include "zombie/vehicles/UI3DScene/AABB.h"
#include "zombie/vehicles/UI3DScene/Axis.h"
#include "zombie/vehicles/UI3DScene/Box3D.h"
#include "zombie/vehicles/UI3DScene/Gizmo.h"
#include "zombie/vehicles/UI3DScene/GridPlaneDrawer.h"
#include "zombie/vehicles/UI3DScene/OverlaysDrawer.h"
#include "zombie/vehicles/UI3DScene/PositionRotation.h"
#include "zombie/vehicles/UI3DScene/SceneObjectRenderData.h"
#include "zombie/vehicles/UI3DScene/TranslateGizmoRenderData.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    const Matrix4f m_projection = std::make_shared<Matrix4f>();
    const Matrix4f m_modelView = std::make_shared<Matrix4f>();
    int m_zoom;
    GridPlaneDrawer m_gridPlaneDrawer;
    OverlaysDrawer m_overlaysDrawer;
   const std::vector<SceneObjectRenderData> m_objectData = std::make_unique<std::vector<>>();
    Gizmo m_gizmo = nullptr;
    const Vector3f m_gizmoTranslate = std::make_shared<Vector3f>();
    const Vector3f m_gizmoRotate = std::make_shared<Vector3f>();
    const Matrix4f m_gizmoParentTransform = std::make_shared<Matrix4f>();
    const Matrix4f m_gizmoOriginTransform = std::make_shared<Matrix4f>();
    const Matrix4f m_gizmoChildTransform = std::make_shared<Matrix4f>();
    const Matrix4f m_gizmoTransform = std::make_shared<Matrix4f>();
    bool m_hasGizmoOrigin;
    bool m_selectedAttachmentIsChildAttachment;
    Axis m_gizmoAxis = Axis.None;
    const TranslateGizmoRenderData m_translateGizmoRenderData = std::make_shared<TranslateGizmoRenderData>();
   const std::vector<PositionRotation> m_axes = std::make_unique<std::vector<>>();
   const std::vector<AABB> m_aabb = std::make_unique<std::vector<>>();
   const std::vector<Box3D> m_box3D = std::make_unique<std::vector<>>();

   private UI3DScene$StateData() {
   }

    float zoomMult() {
      return (float)Math.exp(this.m_zoom * 0.2F) * 160.0F / Math.max(1.82F, 1.0F);
   }
}
} // namespace vehicles
} // namespace zombie
