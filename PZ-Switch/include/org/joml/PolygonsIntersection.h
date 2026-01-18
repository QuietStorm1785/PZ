#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PolygonsIntersection {
public:
private
 static PolygonsIntersection.ByStartComparator byStartComparator =
 new PolygonsIntersection.ByStartComparator();
private
 static PolygonsIntersection.ByEndComparator byEndComparator =
 new PolygonsIntersection.ByEndComparator();
protected
 float[] verticesXY;
 float minX;
 float minY;
 float maxX;
 float maxY;
 float centerX;
 float centerY;
 float radiusSquared;
private
 PolygonsIntersection.IntervalTreeNode tree;

public
 PolygonsIntersection(float[] floats, int[] ints, int int0) {
 this->verticesXY = floats;
 this->preprocess(int0, ints);
 }

private
 PolygonsIntersection.IntervalTreeNode buildNode(List list, float float6) {
 std::vector arrayList0 = nullptr;
 std::vector arrayList1 = nullptr;
 std::vector arrayList2 = nullptr;
 std::vector arrayList3 = nullptr;
 float float0 = 1.0E38F;
 float float1 = -1.0E38F;
 float float2 = 1.0E38F;
 float float3 = -1.0E38F;
 float float4 = 1.0E38F;
 float float5 = -1.0E38F;

 for (int int0 = 0; int0 < list.size(); int0++) {
 PolygonsIntersection.Interval interval =
 (PolygonsIntersection.Interval)list.get(int0);
 if (interval.start < float6 && interval.end < float6) {
 if (arrayList0.empty()) {
 arrayList0 = std::make_unique<ArrayList>();
 }

 arrayList0.add(interval);
 float0 = float0 < interval.start ? float0 : interval.start;
 float1 = float1 > interval.end ? float1 : interval.end;
 } else if (interval.start > float6 && interval.end > float6) {
 if (arrayList1.empty()) {
 arrayList1 = std::make_unique<ArrayList>();
 }

 arrayList1.add(interval);
 float2 = float2 < interval.start ? float2 : interval.start;
 float3 = float3 > interval.end ? float3 : interval.end;
 } else {
 if (arrayList2.empty() || arrayList3.empty()) {
 arrayList2 = std::make_unique<ArrayList>();
 arrayList3 = std::make_unique<ArrayList>();
 }

 float4 = interval.start < float4 ? interval.start : float4;
 float5 = interval.end > float5 ? interval.end : float5;
 arrayList2.add(interval);
 arrayList3.add(interval);
 }
 }

 if (arrayList2 != nullptr) {
 Collections.sort(arrayList2, byStartComparator);
 Collections.sort(arrayList3, byEndComparator);
 }

 PolygonsIntersection.IntervalTreeNode intervalTreeNode =
 new PolygonsIntersection.IntervalTreeNode();
 intervalTreeNode.byBeginning = arrayList2;
 intervalTreeNode.byEnding = arrayList3;
 intervalTreeNode.center = float6;
 if (arrayList0 != nullptr) {
 intervalTreeNode.left =
 this->buildNode(arrayList0, (float0 + float1) / 2.0F);
 intervalTreeNode.left.childrenMinMax = float1;
 }

 if (arrayList1 != nullptr) {
 intervalTreeNode.right =
 this->buildNode(arrayList1, (float2 + float3) / 2.0F);
 intervalTreeNode.right.childrenMinMax = float2;
 }

 return intervalTreeNode;
 }

 void preprocess(int int1, int[] ints) {
 int int0 = 0;
 this->minX = this->minY = 1.0E38F;
 this->maxX = this->maxY = -1.0E38F;
 std::vector arrayList = new ArrayList(int1);
 int int2 = 0;
 int int3 = 0;

 int int4;
 for (int4 = 1; int4 < int1; int0 = int4++) {
 if (ints != nullptr && ints.length > int3 && ints[int3] == int4) {
 float float0 = this->verticesXY[2 * (int4 - 1) + 1];
 float float1 = this->verticesXY[2 * int2 + 1];
 PolygonsIntersection.Interval interval0 =
 new PolygonsIntersection.Interval();
 interval0.start = float0 < float1 ? float0 : float1;
 interval0.end = float1 > float0 ? float1 : float0;
 interval0.i = int4 - 1;
 interval0.j = int2;
 interval0.polyIndex = int3;
 arrayList.add(interval0);
 int2 = int4;
 int3++;
 int4++;
 int0 = int4 - 1;
 }

 float float2 = this->verticesXY[2 * int4 + 1];
 float float3 = this->verticesXY[2 * int4 + 0];
 float float4 = this->verticesXY[2 * int0 + 1];
 this->minX = float3 < this->minX ? float3 : this->minX;
 this->minY = float2 < this->minY ? float2 : this->minY;
 this->maxX = float3 > this->maxX ? float3 : this->maxX;
 this->maxY = float2 > this->maxY ? float2 : this->maxY;
 PolygonsIntersection.Interval interval1 =
 new PolygonsIntersection.Interval();
 interval1.start = float2 < float4 ? float2 : float4;
 interval1.end = float4 > float2 ? float4 : float2;
 interval1.i = int4;
 interval1.j = int0;
 interval1.polyIndex = int3;
 arrayList.add(interval1);
 }

 float float5 = this->verticesXY[2 * (int4 - 1) + 1];
 float float6 = this->verticesXY[2 * (int4 - 1) + 0];
 float float7 = this->verticesXY[2 * int2 + 1];
 this->minX = float6 < this->minX ? float6 : this->minX;
 this->minY = float5 < this->minY ? float5 : this->minY;
 this->maxX = float6 > this->maxX ? float6 : this->maxX;
 this->maxY = float5 > this->maxY ? float5 : this->maxY;
 PolygonsIntersection.Interval interval2 =
 new PolygonsIntersection.Interval();
 interval2.start = float5 < float7 ? float5 : float7;
 interval2.end = float7 > float5 ? float7 : float5;
 interval2.i = int4 - 1;
 interval2.j = int2;
 interval2.polyIndex = int3;
 arrayList.add(interval2);
 this->centerX = (this->maxX + this->minX) * 0.5F;
 this->centerY = (this->maxY + this->minY) * 0.5F;
 float float8 = this->maxX - this->centerX;
 float float9 = this->maxY - this->centerY;
 this->radiusSquared = float8 * float8 + float9 * float9;
 this->tree = this->buildNode(arrayList, this->centerY);
 }

 bool testPoint(float float0, float float1) {
 return this->testPoint(float0, float1, nullptr);
 }

 bool testPoint(float float1, float float3, BitSet bitSet) {
 float float0 = float1 - this->centerX;
 float float2 = float3 - this->centerY;
 if (bitSet != nullptr) {
 bitSet.clear();
 }

 if (float0 * float0 + float2 * float2 > this->radiusSquared) {
 return false;
 } else {
 return !(this->maxX < float1) && !(this->maxY < float3) &&
 !(this->minX > float1) && !(this->minY > float3)
 ? this->tree.traverse(this->verticesXY, float1, float3, false,
 bitSet)
 : false;
 }
 }

 static class ByEndComparator implements Comparator {
 int compare(void *object0, void *object1) {
 PolygonsIntersection.Interval interval0 =
 (PolygonsIntersection.Interval)object0;
 PolygonsIntersection.Interval interval1 =
 (PolygonsIntersection.Interval)object1;
 return Float.compare(interval1.end, interval0.end);
 }
 }

 static class ByStartComparator implements Comparator {
 int compare(void *object0, void *object1) {
 PolygonsIntersection.Interval interval0 =
 (PolygonsIntersection.Interval)object0;
 PolygonsIntersection.Interval interval1 =
 (PolygonsIntersection.Interval)object1;
 return Float.compare(interval0.start, interval1.start);
 }
 }

 static class Interval {
 float start;
 float end;
 int i;
 int j;
 int polyIndex;
 }

 static class IntervalTreeNode {
 float center;
 float childrenMinMax;
 PolygonsIntersection.IntervalTreeNode left;
 PolygonsIntersection.IntervalTreeNode right;
 std::vector byBeginning;
 std::vector byEnding;

 static bool computeEvenOdd(float[] floats,
 PolygonsIntersection.Interval interval,
 float float4, float float5, bool boolean1,
 BitSet bitSet) {
 bool boolean0 = boolean1;
 int int0 = interval.i;
 int int1 = interval.j;
 float float0 = floats[2 * int0 + 1];
 float float1 = floats[2 * int1 + 1];
 float float2 = floats[2 * int0 + 0];
 float float3 = floats[2 * int1 + 0];
 if ((float0 < float5 && float1 >= float5 ||
 float1 < float5 && float0 >= float5) &&
 (float2 <= float4 || float3 <= float4) {
 float float6 =
 float2 + (float5 - float0) / (float1 - float0) * (float3 - float2) -
 float4;
 boolean0 = boolean1 ^ float6 < 0.0F;
 if (boolean0 != boolean1 && bitSet != nullptr) {
 bitSet.flip(interval.polyIndex);
 }
 }

 return boolean0;
 }

 bool traverse(float[] floats, float float1, float float0, bool boolean1,
 BitSet bitSet) {
 bool boolean0 = boolean1;
 if (float0 == this->center && this->byBeginning != nullptr) {
 int int0 = this->byBeginning.size();

 for (int int1 = 0; int1 < int0; int1++) {
 PolygonsIntersection.Interval interval0 =
 (PolygonsIntersection.Interval)this->byBeginning.get(int1);
 boolean0 = computeEvenOdd(floats, interval0, float1, float0, boolean0,
 bitSet);
 }
 } else if (float0 < this->center) {
 if (this->left != nullptr && this->left.childrenMinMax >= float0) {
 boolean0 =
 this->left.traverse(floats, float1, float0, boolean1, bitSet);
 }

 if (this->byBeginning != nullptr) {
 int int2 = this->byBeginning.size();

 for (int int3 = 0; int3 < int2; int3++) {
 PolygonsIntersection.Interval interval1 =
 (PolygonsIntersection.Interval)this->byBeginning.get(int3);
 if (interval1.start > float0) {
 break;
 }

 boolean0 = computeEvenOdd(floats, interval1, float1, float0,
 boolean0, bitSet);
 }
 }
 } else if (float0 > this->center) {
 if (this->right != nullptr && this->right.childrenMinMax <= float0) {
 boolean0 =
 this->right.traverse(floats, float1, float0, boolean1, bitSet);
 }

 if (this->byEnding != nullptr) {
 int int4 = this->byEnding.size();

 for (int int5 = 0; int5 < int4; int5++) {
 PolygonsIntersection.Interval interval2 =
 (PolygonsIntersection.Interval)this->byEnding.get(int5);
 if (interval2.end < float0) {
 break;
 }

 boolean0 = computeEvenOdd(floats, interval2, float1, float0,
 boolean0, bitSet);
 }
 }
 }

 return boolean0;
 }
 }
}
} // namespace joml
} // namespace org
