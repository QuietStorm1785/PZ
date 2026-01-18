#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VehicleStorySpawner {
public:
 static const VehicleStorySpawner instance = new VehicleStorySpawner();
 static const Vector2 s_vector2_1 = new Vector2();
 static const Vector2 s_vector2_2 = new Vector2();
 private static ObjectPool<VehicleStorySpawner.Element> s_elementPool = new ObjectPool<>(VehicleStorySpawner.Element::new);
 private static int[] s_AABB = new int[4];
 public ArrayList<VehicleStorySpawner.Element> m_elements = std::make_unique<ArrayList<>>();
 public HashMap<String, Object> m_storyParams = std::make_unique<HashMap<>>();

 static VehicleStorySpawner getInstance() {
 return instance;
 }

 void clear() {
 s_elementPool.release(this->m_elements);
 this->m_elements.clear();
 this->m_storyParams.clear();
 }

 public VehicleStorySpawner.Element addElement(String id, float x, float y, float direction, float width, float height) {
 VehicleStorySpawner.Element element = s_elementPool.alloc().init(id, x, y, direction, width, height);
 this->m_elements.add(element);
 return element;
 }

 void setParameter(const std::string& key, bool value) {
 this->m_storyParams.put(key, value ? Boolean.TRUE : Boolean.FALSE);
 }

 void setParameter(const std::string& key, float value) {
 this->m_storyParams.put(key, value);
 }

 void setParameter(const std::string& key, int value) {
 this->m_storyParams.put(key, value);
 }

 void setParameter(const std::string& key, void* value) {
 this->m_storyParams.put(key, value);
 }

 bool getParameterBoolean(const std::string& key) {
 return this->getParameter(key, Boolean.class);
 }

 float getParameterFloat(const std::string& key) {
 return this->getParameter(key, Float.class);
 }

 int getParameterInteger(const std::string& key) {
 return this->getParameter(key, Integer.class);
 }

 std::string getParameterString(const std::string& key) {
 return this->getParameter(key, String.class);
 }

 public <E> E getParameter(String string, Class<E> clazz) {
 return Type.tryCastTo(this->m_storyParams.get(string), clazz);
 }

 void spawn(float worldX, float worldY, float worldZ, float angleRadians, VehicleStorySpawner.IElementSpawner spawner) {
 for (int int0 = 0; int0 < this->m_elements.size(); int0++) {
 VehicleStorySpawner.Element element = this->m_elements.get(int0);
 Vector2 vector = s_vector2_1.setLengthAndDirection(element.direction, 1.0F);
 vector.add(element.position);
 this->rotate(worldX, worldY, vector, angleRadians);
 this->rotate(worldX, worldY, element.position, angleRadians);
 element.direction = Vector2.getDirection(vector.x - element.position.x, vector.y - element.position.y);
 element.z = worldZ;
 element.square = IsoWorld.instance.CurrentCell.getGridSquare((double)element.position.x, (double)element.position.y, (double)worldZ);
 spawner.spawn(this, element);
 }
 }

 Vector2 rotate(float centerX, float centerY, Vector2 v, float angleRadians) {
 float float0 = v.x;
 float float1 = v.y;
 v.x = centerX + (float)(float0 * Math.cos(angleRadians) - float1 * Math.sin(angleRadians);
 v.y = centerY + (float)(float0 * Math.sin(angleRadians) + float1 * Math.cos(angleRadians);
 return v;
 }

 void getAABB(float float4, float float6, float float2, float float1, float float0, int[] ints) {
 Vector2 vector0 = s_vector2_1.setLengthAndDirection(float0, 1.0F);
 Vector2 vector1 = s_vector2_2.set(vector0);
 vector1.tangent();
 vector0.x *= float1 / 2.0F;
 vector0.y *= float1 / 2.0F;
 vector1.x *= float2 / 2.0F;
 vector1.y *= float2 / 2.0F;
 float float3 = float4 + vector0.x;
 float float5 = float6 + vector0.y;
 float float7 = float4 - vector0.x;
 float float8 = float6 - vector0.y;
 float float9 = float3 - vector1.x;
 float float10 = float5 - vector1.y;
 float float11 = float3 + vector1.x;
 float float12 = float5 + vector1.y;
 float float13 = float7 - vector1.x;
 float float14 = float8 - vector1.y;
 float float15 = float7 + vector1.x;
 float float16 = float8 + vector1.y;
 float float17 = PZMath.min(float9, PZMath.min(float11, PZMath.min(float13, float15));
 float float18 = PZMath.max(float9, PZMath.max(float11, PZMath.max(float13, float15));
 float float19 = PZMath.min(float10, PZMath.min(float12, PZMath.min(float14, float16));
 float float20 = PZMath.max(float10, PZMath.max(float12, PZMath.max(float14, float16));
 ints[0] = (int)PZMath.floor(float17);
 ints[1] = (int)PZMath.floor(float19);
 ints[2] = (int)PZMath.ceil(float18);
 ints[3] = (int)PZMath.ceil(float20);
 }

 void render(float centerX, float centerY, float z, float width, float height, float angleRadians) {
 LineDrawer.DrawIsoRectRotated(centerX, centerY, z, width, height, angleRadians, 0.0F, 0.0F, 1.0F, 1.0F);
 float float0 = 1.0F;
 float float1 = 1.0F;
 float float2 = 1.0F;
 float float3 = 1.0F;
 float float4 = Float.MAX_VALUE;
 float float5 = Float.MAX_VALUE;
 float float6 = -Float.MAX_VALUE;
 float float7 = -Float.MAX_VALUE;

 for (VehicleStorySpawner.Element element : this->m_elements) {
 Vector2 vector = s_vector2_1.setLengthAndDirection(element.direction, 1.0F);
 LineDrawer.DrawIsoLine(
 element.position.x, element.position.y, z, element.position.x + vector.x, element.position.y + vector.y, z, float0, float1, float2, float3, 1
 );
 LineDrawer.DrawIsoRectRotated(
 element.position.x, element.position.y, z, element.width, element.height, element.direction, float0, float1, float2, float3
 );
 this->getAABB(element.position.x, element.position.y, element.width, element.height, element.direction, s_AABB);
 float4 = PZMath.min(float4, (float)s_AABB[0]);
 float5 = PZMath.min(float5, (float)s_AABB[1]);
 float6 = PZMath.max(float6, (float)s_AABB[2]);
 float7 = PZMath.max(float7, (float)s_AABB[3]);
 }
 }

 public static class Element {
 std::string id;
 const Vector2 position = new Vector2();
 float direction;
 float width;
 float height;
 float z;
 IsoGridSquare square;

 VehicleStorySpawner.Element init(String string, float float0, float float1, float float2, float float3, float float4) {
 this->id = string;
 this->position.set(float0, float1);
 this->direction = float2;
 this->width = float3;
 this->height = float4;
 this->z = 0.0F;
 this->square = nullptr;
 return this;
 }
 }

 public interface IElementSpawner {
 void spawn(VehicleStorySpawner spawner, VehicleStorySpawner.Element element);
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
