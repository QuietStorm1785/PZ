#include "zombie/vehicles/UI3DScene.h"

namespace zombie {
namespace vehicles {

public UI3DScene::UI3DScene(KahluaTable table) {
 // TODO: Implement UI3DScene
 return nullptr;
}

void UI3DScene::render() {
 // TODO: Implement render
}

float UI3DScene::gridMult() {
 // TODO: Implement gridMult
 return 0;
}

float UI3DScene::zoomMult() {
 // TODO: Implement zoomMult
 return 0;
}

Matrix4f UI3DScene::allocMatrix4f() {
 // TODO: Implement allocMatrix4f
 return nullptr;
}

void UI3DScene::releaseMatrix4f(Matrix4f matrix4f) {
 // TODO: Implement releaseMatrix4f
}

Quaternionf UI3DScene::allocQuaternionf() {
 // TODO: Implement allocQuaternionf
 return nullptr;
}

void UI3DScene::releaseQuaternionf(Quaternionf quaternionf) {
 // TODO: Implement releaseQuaternionf
}

void UI3DScene::releaseRay(UI3DScene.Ray ray) {
 // TODO: Implement releaseRay
}

void UI3DScene::releasePlane(UI3DScene.Plane plane) {
 // TODO: Implement releasePlane
}

Vector2 UI3DScene::allocVector2() {
 // TODO: Implement allocVector2
 return nullptr;
}

void UI3DScene::releaseVector2(Vector2 vector) {
 // TODO: Implement releaseVector2
}

Vector3f UI3DScene::allocVector3f() {
 // TODO: Implement allocVector3f
 return nullptr;
}

void UI3DScene::releaseVector3f(Vector3f vector3f) {
 // TODO: Implement releaseVector3f
}

void* UI3DScene::fromLua0(const std::string& func) {
 // TODO: Implement fromLua0
 return nullptr;
}

void* UI3DScene::fromLua1(const std::string& func, void* arg0) {
 // TODO: Implement fromLua1
 return nullptr;
}

void* UI3DScene::fromLua2(const std::string& func, void* arg0, void* arg1) {
 // TODO: Implement fromLua2
 return nullptr;
}

void* UI3DScene::fromLua3(const std::string& func, void* arg0, void* arg1, void* arg2) {
 // TODO: Implement fromLua3
 return nullptr;
}

void* UI3DScene::fromLua4(const std::string& func, void* arg0, void* arg1, void* arg2, void* arg3) {
 // TODO: Implement fromLua4
 return nullptr;
}

void* UI3DScene::fromLua6(const std::string& func, void* arg0, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5) {
 // TODO: Implement fromLua6
 return nullptr;
}

void* UI3DScene::fromLua9(const std::string& func, void* arg0, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6, void* arg7, void* arg8) {
 // TODO: Implement fromLua9
 return nullptr;
}

int UI3DScene::screenWidth() {
 // TODO: Implement screenWidth
 return 0;
}

int UI3DScene::screenHeight() {
 // TODO: Implement screenHeight
 return 0;
}

float UI3DScene::uiToSceneX(float uiX, float uiY) {
 // TODO: Implement uiToSceneX
 return 0;
}

float UI3DScene::uiToSceneY(float uiX, float uiY) {
 // TODO: Implement uiToSceneY
 return 0;
}

Vector3f UI3DScene::uiToScene(float uiX, float uiY, float uiZ, Vector3f out) {
 // TODO: Implement uiToScene
 return nullptr;
}

Vector3f UI3DScene::uiToScene(Matrix4f modelTransform, float uiX, float uiY, float uiZ, Vector3f out) {
 // TODO: Implement uiToScene
 return nullptr;
}

float UI3DScene::sceneToUIX(float sceneX, float sceneY, float sceneZ) {
 // TODO: Implement sceneToUIX
 return 0;
}

float UI3DScene::sceneToUIY(float sceneX, float sceneY, float sceneZ) {
 // TODO: Implement sceneToUIY
 return 0;
}

void UI3DScene::renderGridXY(int int2) {
 // TODO: Implement renderGridXY
}

void UI3DScene::renderGridXZ(int int2) {
 // TODO: Implement renderGridXZ
}

void UI3DScene::renderGridYZ(int int2) {
 // TODO: Implement renderGridYZ
}

void UI3DScene::renderGrid() {
 // TODO: Implement renderGrid
}

void UI3DScene::renderAxis(UI3DScene.PositionRotation positionRotation) {
 // TODO: Implement renderAxis
}

void UI3DScene::renderAxis(Vector3f vector3f0, Vector3f vector3f1) {
 // TODO: Implement renderAxis
}

void UI3DScene::renderAABB(float float6, float float7, float float8, float float1, float float3, float float5, float float10, float float11, float float12) {
 // TODO: Implement renderAABB
}

void UI3DScene::renderAABB(float float0, float float1, float float2, Vector3f vector3f1, Vector3f vector3f0, float float4, float float5, float float6) {
 // TODO: Implement renderAABB
}

void UI3DScene::calcMatrices(Matrix4f matrix4f0, Matrix4f matrix4f1) {
 // TODO: Implement calcMatrices
}

float UI3DScene::closest_distance_between_lines(UI3DScene.Ray ray0, UI3DScene.Ray ray1) {
 // TODO: Implement closest_distance_between_lines
 return 0;
}

Vector3f UI3DScene::project(Vector3f vector3f1, Vector3f vector3f0, Vector3f vector3f2) {
 // TODO: Implement project
 return nullptr;
}

Vector3f UI3DScene::reject(Vector3f vector3f1, Vector3f vector3f2, Vector3f vector3f3) {
 // TODO: Implement reject
 return nullptr;
}

int UI3DScene::intersect_ray_plane(UI3DScene.Plane Pn, UI3DScene.Ray S, Vector3f out) {
 // TODO: Implement intersect_ray_plane
 return 0;
}

float UI3DScene::distance_between_point_ray(Vector3f vector3f2, UI3DScene.Ray ray) {
 // TODO: Implement distance_between_point_ray
 return 0;
}

float UI3DScene::closest_distance_line_circle(UI3DScene.Ray ray, UI3DScene.Circle circle, Vector3f vector3f1) {
 // TODO: Implement closest_distance_line_circle
 return 0;
}

void UI3DScene::init(UI3DScene.SceneCharacter sceneCharacter, UI3DScene.CharacterRenderData characterRenderData) {
 // TODO: Implement init
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::postRender() {
 // TODO: Implement postRender
}

void UI3DScene::release() {
 // TODO: Implement release
}

void UI3DScene::Begin() {
 // TODO: Implement Begin
}

void UI3DScene::End() {
 // TODO: Implement End
}

Vector3f UI3DScene::getPointOnAxis(float float1, float float0, UI3DScene.Axis axis, Matrix4f matrix4f, Vector3f vector3f) {
 // TODO: Implement getPointOnAxis
 return nullptr;
}

bool UI3DScene::hitTestRect(float float17, float float16, float float1, float float2, float float3, float float6, float float7, float float8) {
 // TODO: Implement hitTestRect
 return false;
}

void UI3DScene::renderLineToOrigin() {
 // TODO: Implement renderLineToOrigin
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::init(UI3DScene.SceneModel sceneModel, UI3DScene.ModelRenderData modelRenderData) {
 // TODO: Implement init
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::postRender() {
 // TODO: Implement postRender
}

void UI3DScene::release() {
 // TODO: Implement release
}

Matrix4f UI3DScene::getGlobalTransform(Matrix4f matrix4f) {
 // TODO: Implement getGlobalTransform
 return nullptr;
}

Matrix4f UI3DScene::getGlobalTransform(Matrix4f matrix4f) {
 // TODO: Implement getGlobalTransform
 return nullptr;
}

void UI3DScene::init() {
 // TODO: Implement init
}

void UI3DScene::render() {
 // TODO: Implement render
}

public UI3DScene::Plane() {
 // TODO: Implement Plane
 return nullptr;
}

public UI3DScene::Plane(Vector3f _normal, Vector3f _point) {
 // TODO: Implement Plane
 return nullptr;
}

public UI3DScene::PlaneObjectPool() {
 // TODO: Implement PlaneObjectPool
 return nullptr;
}

public UI3DScene::Ray() {
 // TODO: Implement Ray
 return nullptr;
}

public UI3DScene::RayObjectPool() {
 // TODO: Implement RayObjectPool
 return nullptr;
}

void UI3DScene::startTracking(float float0, float float1, UI3DScene.Axis axis) {
 // TODO: Implement startTracking
}

void UI3DScene::updateTracking(float float0, float float1) {
 // TODO: Implement updateTracking
}

void UI3DScene::stopTracking() {
 // TODO: Implement stopTracking
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::getCircleSegments(Vector3f vector3f4, float float0, Vector3f vector3f2, Vector3f vector3f3, ArrayList<Vector3f> arrayList) {
 // TODO: Implement getCircleSegments
}

float UI3DScene::hitTestCircle(UI3DScene.Ray ray1, ArrayList<Vector3f> arrayList, Vector2 vector) {
 // TODO: Implement hitTestCircle
 return 0;
}

void UI3DScene::renderAxis(Vector3f vector3f0, float float0, Vector3f vector3f1, Vector3f vector3f2, float float2, float float3, float float4, UI3DScene.Ray ray) {
 // TODO: Implement renderAxis
}

Vector3f UI3DScene::getPointOnAxis(float float3, float float4, UI3DScene.Axis var3, UI3DScene.Circle circle, Matrix4f matrix4f, Vector3f vector3f) {
 // TODO: Implement getPointOnAxis
 return nullptr;
}

float UI3DScene::calculateRotation(Vector3f vector3f0, Vector3f vector3f1, UI3DScene.Circle circle) {
 // TODO: Implement calculateRotation
 return 0;
}

void UI3DScene::startTracking(float float0, float float1, UI3DScene.Axis axis) {
 // TODO: Implement startTracking
}

void UI3DScene::updateTracking(float float0, float float1) {
 // TODO: Implement updateTracking
}

void UI3DScene::stopTracking() {
 // TODO: Implement stopTracking
}

void UI3DScene::render() {
 // TODO: Implement render
}

Matrix4f UI3DScene::getLocalTransform(Matrix4f matrix4f) {
 // TODO: Implement getLocalTransform
 return nullptr;
}

Matrix4f UI3DScene::getAttachmentTransform(const std::string& string, Matrix4f matrix4f0) {
 // TODO: Implement getAttachmentTransform
 return nullptr;
}

int UI3DScene::hitTestBone(int int1, UI3DScene.Ray ray0, UI3DScene.Ray ray1, Matrix4f matrix4f1) {
 // TODO: Implement hitTestBone
 return 0;
}

std::string UI3DScene::pickBone(float float1, float float0) {
 // TODO: Implement pickBone
 return "";
}

Matrix4f UI3DScene::getBoneMatrix(const std::string& string, Matrix4f matrix4f) {
 // TODO: Implement getBoneMatrix
 return nullptr;
}

Matrix4f UI3DScene::getLocalTransform(Matrix4f matrix4f) {
 // TODO: Implement getLocalTransform
 return nullptr;
}

Matrix4f UI3DScene::getAttachmentTransform(const std::string& string, Matrix4f matrix4f) {
 // TODO: Implement getAttachmentTransform
 return nullptr;
}

Matrix4f UI3DScene::getLocalTransform(Matrix4f matrix4f0) {
 // TODO: Implement getLocalTransform
 return nullptr;
}

Matrix4f UI3DScene::getGlobalTransform(Matrix4f matrix4f0) {
 // TODO: Implement getGlobalTransform
 return nullptr;
}

Matrix4f UI3DScene::getAttachmentTransform(const std::string& var1, Matrix4f matrix4f) {
 // TODO: Implement getAttachmentTransform
 return nullptr;
}

void UI3DScene::release() {
 // TODO: Implement release
}

void UI3DScene::setScriptName(const std::string& string) {
 // TODO: Implement setScriptName
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::postRender() {
 // TODO: Implement postRender
}

float UI3DScene::zoomMult() {
 // TODO: Implement zoomMult
 return 0;
}

void UI3DScene::startTracking(float float0, float float1, UI3DScene.Axis axis) {
 // TODO: Implement startTracking
}

void UI3DScene::updateTracking(float float0, float float1) {
 // TODO: Implement updateTracking
}

void UI3DScene::stopTracking() {
 // TODO: Implement stopTracking
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::init(UI3DScene.SceneVehicle sceneVehicle, UI3DScene.VehicleRenderData vehicleRenderData) {
 // TODO: Implement init
}

void UI3DScene::render() {
 // TODO: Implement render
}

void UI3DScene::render(int int0) {
 // TODO: Implement render
}

void UI3DScene::postRender() {
 // TODO: Implement postRender
}

void UI3DScene::initVehicleModel(UI3DScene.SceneVehicle sceneVehicle) {
 // TODO: Implement initVehicleModel
}

void UI3DScene::initWheelModel(UI3DScene.SceneVehicle sceneVehicle, VehicleScript.Part part, Matrix4f matrix4f2) {
 // TODO: Implement initWheelModel
}

void UI3DScene::release() {
 // TODO: Implement release
}

void UI3DScene::Begin() {
 // TODO: Implement Begin
}

void UI3DScene::End() {
 // TODO: Implement End
}

} // namespace vehicles
} // namespace zombie
