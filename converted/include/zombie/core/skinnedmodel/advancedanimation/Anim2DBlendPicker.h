#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Anim2DBlendPicker {
public:
 private List<Anim2DBlendTriangle> m_tris;
 private List<Anim2DBlend> m_hull;
 private Anim2DBlendPicker.HullComparer m_hullComparer;

 void SetPickTriangles(List<Anim2DBlendTriangle> tris) {
 this->m_tris = tris;
 this->BuildHull();
 }

 void BuildHull() {
 std::unordered_map hashMap = new HashMap();
 Anim2DBlendPicker.Counter counter0 = new Anim2DBlendPicker.Counter();

 for (Anim2DBlendTriangle anim2DBlendTriangle : this->m_tris) {
 Anim2DBlendPicker.Counter counter1 = hashMap.putIfAbsent(new Anim2DBlendPicker.Edge(anim2DBlendTriangle.node1, anim2DBlendTriangle.node2), counter0);
 if (counter1 == nullptr) {
 counter1 = counter0;
 counter0 = new Anim2DBlendPicker.Counter();
 }

 counter1.Increment();
 counter1 = hashMap.putIfAbsent(new Anim2DBlendPicker.Edge(anim2DBlendTriangle.node2, anim2DBlendTriangle.node3), counter0);
 if (counter1 == nullptr) {
 counter1 = counter0;
 counter0 = new Anim2DBlendPicker.Counter();
 }

 counter1.Increment();
 counter1 = hashMap.putIfAbsent(new Anim2DBlendPicker.Edge(anim2DBlendTriangle.node3, anim2DBlendTriangle.node1), counter0);
 if (counter1 == nullptr) {
 counter1 = counter0;
 counter0 = new Anim2DBlendPicker.Counter();
 }

 counter1.Increment();
 }

 std::unordered_set hashSet = new HashSet();
 hashMap.forEach((edge, counter) -> {
 if (counter.count == 1) {
 hashSet.add(edge.a);
 hashSet.add(edge.b);
 }
 });
 std::vector arrayList = new ArrayList(hashSet);
 float float0 = 0.0F;
 float float1 = 0.0F;

 for (auto& anim2DBlend : arrayList) float0 += anim2DBlend.m_XPos;
 float1 += anim2DBlend.m_YPos;
 }

 float0 /= arrayList.size();
 float1 /= arrayList.size();
 this->m_hullComparer = new Anim2DBlendPicker.HullComparer(float0, float1);
 arrayList.sort(this->m_hullComparer);
 this->m_hull = arrayList;
 }

 static <T> int LowerBoundIdx(List<T> list, T object, Comparator<? super T> comparator) {
 int int0 = 0;
 int int1 = list.size();

 while (int0 != int1) {
 int int2 = (int0 + int1) / 2;
 if (comparator.compare(object, list.get(int2) < 0) {
 int1 = int2;
 } else {
 int0 = int2 + 1;
 }
 }

 return int0;
 }

 static float ProjectPointToLine(float float1, float float4, float float2, float float5, float float7, float float9) {
 float float0 = float1 - float2;
 float float3 = float4 - float5;
 float float6 = float7 - float2;
 float float8 = float9 - float5;
 return (float6 * float0 + float8 * float3) / (float6 * float6 + float8 * float8);
 }

 public Anim2DBlendPicker.PickResults Pick(float x, float y) {
 Anim2DBlendPicker.PickResults pickResults = new Anim2DBlendPicker.PickResults();

 for (Anim2DBlendTriangle anim2DBlendTriangle : this->m_tris) {
 if (anim2DBlendTriangle.Contains(x, y) {
 pickResults.numNodes = 3;
 pickResults.node1 = anim2DBlendTriangle.node1;
 pickResults.node2 = anim2DBlendTriangle.node2;
 pickResults.node3 = anim2DBlendTriangle.node3;
 float float0 = pickResults.node1.m_XPos;
 float float1 = pickResults.node1.m_YPos;
 float float2 = pickResults.node2.m_XPos;
 float float3 = pickResults.node2.m_YPos;
 float float4 = pickResults.node3.m_XPos;
 float float5 = pickResults.node3.m_YPos;
 pickResults.scale1 = ((float3 - float5) * (x - float4) + (float4 - float2) * (y - float5)
 / ((float3 - float5) * (float0 - float4) + (float4 - float2) * (float1 - float5);
 pickResults.scale2 = ((float5 - float1) * (x - float4) + (float0 - float4) * (y - float5)
 / ((float3 - float5) * (float0 - float4) + (float4 - float2) * (float1 - float5);
 pickResults.scale3 = 1.0F - pickResults.scale1 - pickResults.scale2;
 return pickResults;
 }
 }

 x *= 1.1F;
 y *= 1.1F;
 Anim2DBlend anim2DBlend0 = new Anim2DBlend();
 anim2DBlend0.m_XPos = x;
 anim2DBlend0.m_YPos = y;
 int int0 = LowerBoundIdx(this->m_hull, anim2DBlend0, this->m_hullComparer);
 if (int0 == this->m_hull.size()) {
 int0 = 0;
 }

 int int1 = int0 > 0 ? int0 - 1 : this->m_hull.size() - 1;
 Anim2DBlend anim2DBlend1 = this->m_hull.get(int0);
 Anim2DBlend anim2DBlend2 = this->m_hull.get(int1);
 float float6 = ProjectPointToLine(x, y, anim2DBlend1.m_XPos, anim2DBlend1.m_YPos, anim2DBlend2.m_XPos, anim2DBlend2.m_YPos);
 if (float6 < 0.0F) {
 pickResults.numNodes = 1;
 pickResults.node1 = anim2DBlend1;
 pickResults.scale1 = 1.0F;
 } else if (float6 > 1.0F) {
 pickResults.numNodes = 1;
 pickResults.node1 = anim2DBlend2;
 pickResults.scale1 = 1.0F;
 } else {
 pickResults.numNodes = 2;
 pickResults.node1 = anim2DBlend1;
 pickResults.node2 = anim2DBlend2;
 pickResults.scale1 = 1.0F - float6;
 pickResults.scale2 = float6;
 }

 return pickResults;
 }

 void render(float float1, float float2) {
 short short0 = 200;
 int int0 = Core.getInstance().getScreenWidth() - short0 - 100;
 int int1 = Core.getInstance().getScreenHeight() - short0 - 100;
 SpriteRenderer.instance.renderi(nullptr, int0 - 20, int1 - 20, short0 + 40, short0 + 40, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);

 for (int int2 = 0; int2 < this->m_tris.size(); int2++) {
 Anim2DBlendTriangle anim2DBlendTriangle = this->m_tris.get(int2);
 SpriteRenderer.instance
 .renderline(
 nullptr,
 (int)(int0 + short0 / 2 + anim2DBlendTriangle.node1.m_XPos * short0 / 2.0F),
 (int)(int1 + short0 / 2 - anim2DBlendTriangle.node1.m_YPos * short0 / 2.0F),
 (int)(int0 + short0 / 2 + anim2DBlendTriangle.node2.m_XPos * short0 / 2.0F),
 (int)(int1 + short0 / 2 - anim2DBlendTriangle.node2.m_YPos * short0 / 2.0F),
 0.5F,
 0.5F,
 0.5F,
 1.0F
 );
 SpriteRenderer.instance
 .renderline(
 nullptr,
 (int)(int0 + short0 / 2 + anim2DBlendTriangle.node2.m_XPos * short0 / 2.0F),
 (int)(int1 + short0 / 2 - anim2DBlendTriangle.node2.m_YPos * short0 / 2.0F),
 (int)(int0 + short0 / 2 + anim2DBlendTriangle.node3.m_XPos * short0 / 2.0F),
 (int)(int1 + short0 / 2 - anim2DBlendTriangle.node3.m_YPos * short0 / 2.0F),
 0.5F,
 0.5F,
 0.5F,
 1.0F
 );
 SpriteRenderer.instance
 .renderline(
 nullptr,
 (int)(int0 + short0 / 2 + anim2DBlendTriangle.node3.m_XPos * short0 / 2.0F),
 (int)(int1 + short0 / 2 - anim2DBlendTriangle.node3.m_YPos * short0 / 2.0F),
 (int)(int0 + short0 / 2 + anim2DBlendTriangle.node1.m_XPos * short0 / 2.0F),
 (int)(int1 + short0 / 2 - anim2DBlendTriangle.node1.m_YPos * short0 / 2.0F),
 0.5F,
 0.5F,
 0.5F,
 1.0F
 );
 }

 float float0 = 8.0F;
 Anim2DBlendPicker.PickResults pickResults = this->Pick(float1, float2);
 if (pickResults.node1 != nullptr) {
 SpriteRenderer.instance
 .render(
 nullptr,
 int0 + short0 / 2 + pickResults.node1.m_XPos * short0 / 2.0F - float0 / 2.0F,
 int1 + short0 / 2 - pickResults.node1.m_YPos * short0 / 2.0F - float0 / 2.0F,
 float0,
 float0,
 0.0F,
 1.0F,
 0.0F,
 1.0F,
 nullptr
 );
 }

 if (pickResults.node2 != nullptr) {
 SpriteRenderer.instance
 .render(
 nullptr,
 int0 + short0 / 2 + pickResults.node2.m_XPos * short0 / 2.0F - float0 / 2.0F,
 int1 + short0 / 2 - pickResults.node2.m_YPos * short0 / 2.0F - float0 / 2.0F,
 float0,
 float0,
 0.0F,
 1.0F,
 0.0F,
 1.0F,
 nullptr
 );
 }

 if (pickResults.node3 != nullptr) {
 SpriteRenderer.instance
 .render(
 nullptr,
 int0 + short0 / 2 + pickResults.node3.m_XPos * short0 / 2.0F - float0 / 2.0F,
 int1 + short0 / 2 - pickResults.node3.m_YPos * short0 / 2.0F - float0 / 2.0F,
 float0,
 float0,
 0.0F,
 1.0F,
 0.0F,
 1.0F,
 nullptr
 );
 }

 float0 = 4.0F;
 SpriteRenderer.instance
 .render(
 nullptr,
 int0 + short0 / 2 + float1 * short0 / 2.0F - float0 / 2.0F,
 int1 + short0 / 2 - float2 * short0 / 2.0F - float0 / 2.0F,
 float0,
 float0,
 0.0F,
 0.0F,
 1.0F,
 1.0F,
 nullptr
 );
 }

 static class Counter {
 int count = 0;

 int Increment() {
 return ++this->count;
 }
 }

 static class Edge {
 Anim2DBlend a;
 Anim2DBlend b;

 public Edge(Anim2DBlend anim2DBlend1, Anim2DBlend anim2DBlend0) {
 bool boolean0;
 if (anim2DBlend1.m_XPos != anim2DBlend0.m_XPos) {
 boolean0 = anim2DBlend1.m_XPos > anim2DBlend0.m_XPos;
 } else {
 boolean0 = anim2DBlend1.m_YPos > anim2DBlend0.m_YPos;
 }

 if (boolean0) {
 this->a = anim2DBlend0;
 this->b = anim2DBlend1;
 } else {
 this->a = anim2DBlend1;
 this->b = anim2DBlend0;
 }
 }

 int hashCode() {
 int int0 = this->a.hashCode();
 int int1 = this->b.hashCode();
 return (int0 << 5) + int0 ^ int1;
 }

 bool equals(void* object) {
 return !(object instanceof Anim2DBlendPicker.Edge)
 ? false
 : this->a == ((Anim2DBlendPicker.Edge)object).a && this->b == ((Anim2DBlendPicker.Edge)object).b;
 }
 }

 static class HullComparer implements Comparator<Anim2DBlend> {
 int centerX;
 int centerY;

 public HullComparer(float arg0, float arg1) {
 this->centerX = (int)(arg0 * 1000.0F);
 this->centerY = (int)(arg1 * 1000.0F);
 }

 bool isLessThan(Anim2DBlend arg0, Anim2DBlend arg1) {
 int int0 = (int)(arg0.m_XPos * 1000.0F);
 int int1 = (int)(arg0.m_YPos * 1000.0F);
 int int2 = (int)(arg1.m_XPos * 1000.0F);
 int int3 = (int)(arg1.m_YPos * 1000.0F);
 int int4 = int0 - this->centerX;
 int int5 = int1 - this->centerY;
 int int6 = int2 - this->centerX;
 int int7 = int3 - this->centerY;
 if (int5 == 0 && int4 > 0) {
 return true;
 } else if (int7 == 0 && int6 > 0) {
 return false;
 } else if (int5 > 0 && int7 < 0) {
 return true;
 } else if (int5 < 0 && int7 > 0) {
 return false;
 } else {
 int int8 = int4 * int7 - int5 * int6;
 return int8 > 0;
 }
 }

 int compare(Anim2DBlend arg0, Anim2DBlend arg1) {
 if (this->isLessThan(arg0, arg1) {
 return -1;
 } else {
 return this->isLessThan(arg1, arg0) ? 1 : 0;
 }
 }
 }

 public static class PickResults {
 int numNodes;
 Anim2DBlend node1;
 Anim2DBlend node2;
 Anim2DBlend node3;
 float scale1;
 float scale2;
 float scale3;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
