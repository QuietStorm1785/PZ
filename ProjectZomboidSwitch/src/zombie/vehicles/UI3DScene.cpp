#include <string>
#include "zombie/vehicles/UI3DScene.h"

namespace zombie {
namespace vehicles {

public UI3DScene::UI3DScene(KahluaTable var1) {
    // TODO: Implement UI3DScene
    return nullptr;
}

SceneObject UI3DScene::getSceneObjectById(const std::string& var1, bool var2) {
    // TODO: Implement getSceneObjectById
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

void UI3DScene::releaseMatrix4f(Matrix4f var0) {
    // TODO: Implement releaseMatrix4f
}

Quaternionf UI3DScene::allocQuaternionf() {
    // TODO: Implement allocQuaternionf
    return nullptr;
}

void UI3DScene::releaseQuaternionf(Quaternionf var0) {
    // TODO: Implement releaseQuaternionf
}

Ray UI3DScene::allocRay() {
    // TODO: Implement allocRay
    return nullptr;
}

void UI3DScene::releaseRay(Ray var0) {
    // TODO: Implement releaseRay
}

Plane UI3DScene::allocPlane() {
    // TODO: Implement allocPlane
    return nullptr;
}

void UI3DScene::releasePlane(Plane var0) {
    // TODO: Implement releasePlane
}

Vector2 UI3DScene::allocVector2() {
    // TODO: Implement allocVector2
    return nullptr;
}

void UI3DScene::releaseVector2(Vector2 var0) {
    // TODO: Implement releaseVector2
}

Vector3f UI3DScene::allocVector3f() {
    // TODO: Implement allocVector3f
    return nullptr;
}

void UI3DScene::releaseVector3f(Vector3f var0) {
    // TODO: Implement releaseVector3f
}

void* UI3DScene::fromLua0(const std::string& var1) {
    // TODO: Implement fromLua0
    return nullptr;
}

void* UI3DScene::fromLua1(const std::string& var1, void* var2) {
    // TODO: Implement fromLua1
    return nullptr;
}

void* UI3DScene::fromLua2(const std::string& var1, void* var2, void* var3) {
    // TODO: Implement fromLua2
    return nullptr;
}

void* UI3DScene::fromLua3(const std::string& var1, void* var2, void* var3, void* var4) {
    // TODO: Implement fromLua3
    return nullptr;
}

void* UI3DScene::fromLua4(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
    // TODO: Implement fromLua4
    return nullptr;
}

void* UI3DScene::fromLua6(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7) {
    // TODO: Implement fromLua6
    return nullptr;
}

void* UI3DScene::fromLua9(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7, void* var8, void* var9, void* var10) {
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

float UI3DScene::uiToSceneX(float var1, float var2) {
    // TODO: Implement uiToSceneX
    return 0;
}

float UI3DScene::uiToSceneY(float var1, float var2) {
    // TODO: Implement uiToSceneY
    return 0;
}

Vector3f UI3DScene::uiToScene(float var1, float var2, float var3, Vector3f var4) {
    // TODO: Implement uiToScene
    return nullptr;
}

Vector3f UI3DScene::uiToScene(Matrix4f var1, float var2, float var3, float var4, Vector3f var5) {
    // TODO: Implement uiToScene
    return nullptr;
}

float UI3DScene::sceneToUIX(float var1, float var2, float var3) {
    // TODO: Implement sceneToUIX
    return 0;
}

float UI3DScene::sceneToUIY(float var1, float var2, float var3) {
    // TODO: Implement sceneToUIY
    return 0;
}

void UI3DScene::renderGridXY(int var1) {
    // TODO: Implement renderGridXY
}

void UI3DScene::renderGridXZ(int var1) {
    // TODO: Implement renderGridXZ
}

void UI3DScene::renderGridYZ(int var1) {
    // TODO: Implement renderGridYZ
}

void UI3DScene::renderGrid() {
    // TODO: Implement renderGrid
}

void UI3DScene::renderAxis(PositionRotation var1) {
    // TODO: Implement renderAxis
}

void UI3DScene::renderAxis(Vector3f var1, Vector3f var2) {
    // TODO: Implement renderAxis
}

void UI3DScene::renderAABB(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9) {
    // TODO: Implement renderAABB
}

void UI3DScene::renderAABB(float var1, float var2, float var3, Vector3f var4, Vector3f var5, float var6, float var7, float var8) {
    // TODO: Implement renderAABB
}

void UI3DScene::calcMatrices(Matrix4f var1, Matrix4f var2) {
    // TODO: Implement calcMatrices
}

Ray UI3DScene::getCameraRay(float var1, float var2, Ray var3) {
    // TODO: Implement getCameraRay
    return nullptr;
}

Ray UI3DScene::getCameraRay(float var1, float var2, Matrix4f var3, Matrix4f var4, Ray var5) {
    // TODO: Implement getCameraRay
    return nullptr;
}

float UI3DScene::closest_distance_between_lines(Ray var1, Ray var2) {
    // TODO: Implement closest_distance_between_lines
    return 0;
}

Vector3f UI3DScene::project(Vector3f var1, Vector3f var2, Vector3f var3) {
    // TODO: Implement project
    return nullptr;
}

Vector3f UI3DScene::reject(Vector3f var1, Vector3f var2, Vector3f var3) {
    // TODO: Implement reject
    return nullptr;
}

int UI3DScene::intersect_ray_plane(Plane var0, Ray var1, Vector3f var2) {
    // TODO: Implement intersect_ray_plane
    return 0;
}

float UI3DScene::distance_between_point_ray(Vector3f var1, Ray var2) {
    // TODO: Implement distance_between_point_ray
    return 0;
}

float UI3DScene::closest_distance_line_circle(Ray var1, Circle var2, Vector3f var3) {
    // TODO: Implement closest_distance_line_circle
    return 0;
}

StateData UI3DScene::stateDataMain() {
    // TODO: Implement stateDataMain
    return nullptr;
}

StateData UI3DScene::stateDataRender() {
    // TODO: Implement stateDataRender
    return nullptr;
}

} // namespace vehicles
} // namespace zombie
