#include "zombie/core/physics/PhysicsDebugRenderer.h"

namespace zombie {
namespace core {
namespace physics {

PhysicsDebugRenderer PhysicsDebugRenderer::alloc() {
 // TODO: Implement alloc
 return nullptr;
}

void PhysicsDebugRenderer::release() {
 // TODO: Implement release
}

void PhysicsDebugRenderer::init(IsoPlayer player) {
 // TODO: Implement init
}

void PhysicsDebugRenderer::render() {
 // TODO: Implement render
}

void PhysicsDebugRenderer::postRender() {
 // TODO: Implement postRender
}

float PhysicsDebugRenderer::YToScreenExact(float objectX, float objectY,
 float objectZ, int screenZ) {
 // TODO: Implement YToScreenExact
 return 0;
}

float PhysicsDebugRenderer::XToScreenExact(float objectX, float objectY,
 float objectZ, int screenZ) {
 // TODO: Implement XToScreenExact
 return 0;
}

void PhysicsDebugRenderer::drawSphere(float pX, float pY, float pZ,
 float radius, float r, float g, float b) {
 // TODO: Implement drawSphere
}

void PhysicsDebugRenderer::drawTriangle(float aX, float aY, float aZ, float bX,
 float bY, float bZ, float cX, float cY,
 float cZ, float r, float g, float b,
 float alpha) {
 // TODO: Implement drawTriangle
}

} // namespace physics
} // namespace core
} // namespace zombie
