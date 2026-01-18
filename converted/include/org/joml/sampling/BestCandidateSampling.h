#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Random.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include <filesystem>

namespace org {
namespace joml {
namespace sampling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BestCandidateSampling {
public:
 public static class Cube {
 int numSamples;
 int numCandidates = 60;
 long seed;

 public BestCandidateSampling.Cube seed(long long0) {
 this->seed = long0;
 return this;
 }

 public BestCandidateSampling.Cube numSamples(int int0) {
 this->numSamples = int0;
 return this;
 }

 public BestCandidateSampling.Cube numCandidates(int int0) {
 this->numCandidates = int0;
 return this;
 }

 public BestCandidateSampling.Cube generate( float[] floats) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 return this->generate(std::make_unique<Callback3d>() {
 void onNewSample(float float0, float float1, float float2) {
 floats[3 * intHolder.value + 0] = float0;
 floats[3 * intHolder.value + 1] = float1;
 floats[3 * intHolder.value + 2] = float2;
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Cube generate( FloatBuffer floatBuffer) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 const int int0 = floatBuffer.position();
 return this->generate(std::make_unique<Callback3d>() {
 void onNewSample(float float0, float float1, float float2) {
 floatBuffer.put(int0 + 3 * intHolder.value + 0, float0);
 floatBuffer.put(int0 + 3 * intHolder.value + 1, float1);
 floatBuffer.put(int0 + 3 * intHolder.value + 2, float2);
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Cube generate(Callback3d callback3d) {
 BestCandidateSampling.Octree octree = new BestCandidateSampling.Octree(-1.0F, -1.0F, -1.0F, 2.0F);
 Random random = new Random(this->seed);

 for (int int0 = 0; int0 < this->numSamples; int0++) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;
 float float3 = 0.0F;

 for (int int1 = 0; int1 < this->numCandidates; int1++) {
 float float4 = random.nextFloat() * 2.0F - 1.0F;
 float float5 = random.nextFloat() * 2.0F - 1.0F;
 float float6 = random.nextFloat() * 2.0F - 1.0F;
 float float7 = octree.nearest(float4, float5, float6, float3, Float.POSITIVE_INFINITY);
 if (float7 > float3) {
 float3 = float7;
 float0 = float4;
 float1 = float5;
 float2 = float6;
 }
 }

 callback3d.onNewSample(float0, float1, float2);
 octree.insert(new Vector3f(float0, float1, float2);
 }

 return this;
 }
 }

 public static class Disk {
 int numSamples;
 int numCandidates = 60;
 long seed;

 public BestCandidateSampling.Disk seed(long long0) {
 this->seed = long0;
 return this;
 }

 public BestCandidateSampling.Disk numSamples(int int0) {
 this->numSamples = int0;
 return this;
 }

 public BestCandidateSampling.Disk numCandidates(int int0) {
 this->numCandidates = int0;
 return this;
 }

 public BestCandidateSampling.Disk generate( float[] floats) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 return this->generate(std::make_unique<Callback2d>() {
 void onNewSample(float float0, float float1) {
 floats[2 * intHolder.value + 0] = float0;
 floats[2 * intHolder.value + 1] = float1;
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Disk generate( FloatBuffer floatBuffer) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 const int int0 = floatBuffer.position();
 return this->generate(std::make_unique<Callback2d>() {
 void onNewSample(float float0, float float1) {
 floatBuffer.put(int0 + 3 * intHolder.value + 0, float0);
 floatBuffer.put(int0 + 3 * intHolder.value + 1, float1);
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Disk generate(Callback2d callback2d) {
 BestCandidateSampling.QuadTree quadTree = new BestCandidateSampling.QuadTree(-1.0F, -1.0F, 2.0F);
 Random random = new Random(this->seed);

 for (int int0 = 0; int0 < this->numSamples; int0++) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;

 for (int int1 = 0; int1 < this->numCandidates; int1++) {
 float float3;
 float float4;
 do {
 float3 = random.nextFloat() * 2.0F - 1.0F;
 float4 = random.nextFloat() * 2.0F - 1.0F;
 } while (float3 * float3 + float4 * float4 > 1.0F);

 float float5 = quadTree.nearest(float3, float4, float2, Float.POSITIVE_INFINITY);
 if (float5 > float2) {
 float2 = float5;
 float0 = float3;
 float1 = float4;
 }
 }

 callback2d.onNewSample(float0, float1);
 quadTree.insert(new Vector2f(float0, float1);
 }

 return this;
 }
 }

 private static class IntHolder {
 int value;
 }

 private static class Octree {
 static const int MAX_OBJECTS_PER_NODE = 32;
 static const int PXNYNZ = 0;
 static const int NXNYNZ = 1;
 static const int NXPYNZ = 2;
 static const int PXPYNZ = 3;
 static const int PXNYPZ = 4;
 static const int NXNYPZ = 5;
 static const int NXPYPZ = 6;
 static const int PXPYPZ = 7;
 float minX;
 float minY;
 float minZ;
 float hs;
 std::vector objects;
 private BestCandidateSampling.Octree[] children;

 Octree(float float0, float float1, float float2, float float3) {
 this->minX = float0;
 this->minY = float1;
 this->minZ = float2;
 this->hs = float3 * 0.5F;
 }

 void split() {
 this->children = new BestCandidateSampling.Octree[8];
 this->children[1] = new BestCandidateSampling.Octree(this->minX, this->minY, this->minZ, this->hs);
 this->children[0] = new BestCandidateSampling.Octree(this->minX + this->hs, this->minY, this->minZ, this->hs);
 this->children[2] = new BestCandidateSampling.Octree(this->minX, this->minY + this->hs, this->minZ, this->hs);
 this->children[3] = new BestCandidateSampling.Octree(this->minX + this->hs, this->minY + this->hs, this->minZ, this->hs);
 this->children[5] = new BestCandidateSampling.Octree(this->minX, this->minY, this->minZ + this->hs, this->hs);
 this->children[4] = new BestCandidateSampling.Octree(this->minX + this->hs, this->minY, this->minZ + this->hs, this->hs);
 this->children[6] = new BestCandidateSampling.Octree(this->minX, this->minY + this->hs, this->minZ + this->hs, this->hs);
 this->children[7] = new BestCandidateSampling.Octree(this->minX + this->hs, this->minY + this->hs, this->minZ + this->hs, this->hs);
 }

 void insertIntoChild(Vector3f vector3f) {
 this->children[this->octant(vector3f.x, vector3f.y, vector3f.z)].insert(vector3f);
 }

 void insert(Vector3f vector3f) {
 if (this->children != nullptr) {
 this->insertIntoChild(vector3f);
 } else {
 if (this->objects != nullptr && this->objects.size() == 32) {
 this->split();

 for (int int0 = 0; int0 < this->objects.size(); int0++) {
 this->insertIntoChild((Vector3f)this->objects.get(int0);
 }

 this->objects = nullptr;
 this->insertIntoChild(vector3f);
 } else {
 if (this->objects.empty()) {
 this->objects = new ArrayList(32);
 }

 this->objects.add(vector3f);
 }
 }
 }

 int octant(float float0, float float1, float float2) {
 if (float0 < this->minX + this->hs) {
 if (float1 < this->minY + this->hs) {
 return float2 < this->minZ + this->hs ? 1 : 5;
 } else {
 return float2 < this->minZ + this->hs ? 2 : 6;
 }
 } else if (float1 < this->minY + this->hs) {
 return float2 < this->minZ + this->hs ? 0 : 4;
 } else {
 return float2 < this->minZ + this->hs ? 3 : 7;
 }
 }

 float nearest(float float4, float float3, float float2, float float6, float float1) {
 float float0 = float1;
 if (!(float4 < this->minX - float1)
 && !(float4 > this->minX + this->hs * 2.0F + float1)
 && !(float3 < this->minY - float1)
 && !(float3 > this->minY + this->hs * 2.0F + float1)
 && !(float2 < this->minZ - float1)
 && !(float2 > this->minZ + this->hs * 2.0F + float1) {
 if (this->children != nullptr) {
 int int0 = this->octant(float4, float3, float2);

 for (int int1 = 0; int1 < 8; int1++) {
 float float5 = this->children[int0].nearest(float4, float3, float2, float6, float0);
 float0 = Math.min(float5, float0);
 if (float0 <= float6) {
 return float6;
 }

 int0 = int0 + 1 & 7;
 }

 return float0;
 } else {
 float float7 = float1 * float1;
 float float8 = float6 * float6;

 for (int int2 = 0; this->objects != nullptr && int2 < this->objects.size(); int2++) {
 Vector3f vector3f = (Vector3f)this->objects.get(int2);
 float float9 = vector3f.distanceSquared(float4, float3, float2);
 if (float9 <= float8) {
 return float6;
 }

 if (float9 < float7) {
 float7 = float9;
 }
 }

 return Math.sqrt(float7);
 }
 } else {
 return float1;
 }
 }
 }

 public static class Quad {
 int numSamples;
 int numCandidates = 60;
 long seed;

 public BestCandidateSampling.Quad seed(long long0) {
 this->seed = long0;
 return this;
 }

 public BestCandidateSampling.Quad numSamples(int int0) {
 this->numSamples = int0;
 return this;
 }

 public BestCandidateSampling.Quad numCandidates(int int0) {
 this->numCandidates = int0;
 return this;
 }

 public BestCandidateSampling.Quad generate( float[] floats) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 return this->generate(std::make_unique<Callback2d>() {
 void onNewSample(float float0, float float1) {
 floats[2 * intHolder.value + 0] = float0;
 floats[2 * intHolder.value + 1] = float1;
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Quad generate( FloatBuffer floatBuffer) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 const int int0 = floatBuffer.position();
 return this->generate(std::make_unique<Callback2d>() {
 void onNewSample(float float0, float float1) {
 floatBuffer.put(int0 + 3 * intHolder.value + 0, float0);
 floatBuffer.put(int0 + 3 * intHolder.value + 1, float1);
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Quad generate(Callback2d callback2d) {
 BestCandidateSampling.QuadTree quadTree = new BestCandidateSampling.QuadTree(-1.0F, -1.0F, 2.0F);
 Random random = new Random(this->seed);

 for (int int0 = 0; int0 < this->numSamples; int0++) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;

 for (int int1 = 0; int1 < this->numCandidates; int1++) {
 float float3 = random.nextFloat() * 2.0F - 1.0F;
 float float4 = random.nextFloat() * 2.0F - 1.0F;
 float float5 = quadTree.nearest(float3, float4, float2, Float.POSITIVE_INFINITY);
 if (float5 > float2) {
 float2 = float5;
 float0 = float3;
 float1 = float4;
 }
 }

 callback2d.onNewSample(float0, float1);
 quadTree.insert(new Vector2f(float0, float1);
 }

 return this;
 }
 }

 private static class QuadTree {
 static const int MAX_OBJECTS_PER_NODE = 32;
 static const int PXNY = 0;
 static const int NXNY = 1;
 static const int NXPY = 2;
 static const int PXPY = 3;
 float minX;
 float minY;
 float hs;
 std::vector objects;
 private BestCandidateSampling.QuadTree[] children;

 QuadTree(float float0, float float1, float float2) {
 this->minX = float0;
 this->minY = float1;
 this->hs = float2 * 0.5F;
 }

 void split() {
 this->children = new BestCandidateSampling.QuadTree[4];
 this->children[1] = new BestCandidateSampling.QuadTree(this->minX, this->minY, this->hs);
 this->children[0] = new BestCandidateSampling.QuadTree(this->minX + this->hs, this->minY, this->hs);
 this->children[2] = new BestCandidateSampling.QuadTree(this->minX, this->minY + this->hs, this->hs);
 this->children[3] = new BestCandidateSampling.QuadTree(this->minX + this->hs, this->minY + this->hs, this->hs);
 }

 void insertIntoChild(Vector2f vector2f) {
 this->children[this->quadrant(vector2f.x, vector2f.y)].insert(vector2f);
 }

 void insert(Vector2f vector2f) {
 if (this->children != nullptr) {
 this->insertIntoChild(vector2f);
 } else {
 if (this->objects != nullptr && this->objects.size() == 32) {
 this->split();

 for (int int0 = 0; int0 < this->objects.size(); int0++) {
 this->insertIntoChild((Vector2f)this->objects.get(int0);
 }

 this->objects = nullptr;
 this->insertIntoChild(vector2f);
 } else {
 if (this->objects.empty()) {
 this->objects = new ArrayList(32);
 }

 this->objects.add(vector2f);
 }
 }
 }

 int quadrant(float float0, float float1) {
 if (float0 < this->minX + this->hs) {
 return float1 < this->minY + this->hs ? 1 : 2;
 } else {
 return float1 < this->minY + this->hs ? 0 : 3;
 }
 }

 float nearest(float float3, float float2, float float5, float float1) {
 float float0 = float1;
 if (!(float3 < this->minX - float1)
 && !(float3 > this->minX + this->hs * 2.0F + float1)
 && !(float2 < this->minY - float1)
 && !(float2 > this->minY + this->hs * 2.0F + float1) {
 if (this->children != nullptr) {
 int int0 = this->quadrant(float3, float2);

 for (int int1 = 0; int1 < 4; int1++) {
 float float4 = this->children[int0].nearest(float3, float2, float5, float0);
 float0 = Math.min(float4, float0);
 if (float0 <= float5) {
 return float5;
 }

 int0 = int0 + 1 & 3;
 }

 return float0;
 } else {
 float float6 = float1 * float1;
 float float7 = float5 * float5;

 for (int int2 = 0; this->objects != nullptr && int2 < this->objects.size(); int2++) {
 Vector2f vector2f = (Vector2f)this->objects.get(int2);
 float float8 = vector2f.distanceSquared(float3, float2);
 if (float8 <= float7) {
 return float5;
 }

 if (float8 < float6) {
 float6 = float8;
 }
 }

 return Math.sqrt(float6);
 }
 } else {
 return float1;
 }
 }
 }

 public static class Sphere {
 bool onHemisphere;
 int numSamples;
 int numCandidates = 60;
 long seed;

 public BestCandidateSampling.Sphere generate( float[] floats) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 return this->generate(std::make_unique<Callback3d>() {
 void onNewSample(float float0, float float1, float float2) {
 floats[3 * intHolder.value + 0] = float0;
 floats[3 * intHolder.value + 1] = float1;
 floats[3 * intHolder.value + 2] = float2;
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Sphere generate( FloatBuffer floatBuffer) {
 BestCandidateSampling.IntHolder intHolder = new BestCandidateSampling.IntHolder();
 const int int0 = floatBuffer.position();
 return this->generate(std::make_unique<Callback3d>() {
 void onNewSample(float float0, float float1, float float2) {
 floatBuffer.put(int0 + 3 * intHolder.value + 0, float0);
 floatBuffer.put(int0 + 3 * intHolder.value + 1, float1);
 floatBuffer.put(int0 + 3 * intHolder.value + 2, float2);
 intHolder.value++;
 }
 });
 }

 public BestCandidateSampling.Sphere seed(long long0) {
 this->seed = long0;
 return this;
 }

 public BestCandidateSampling.Sphere numSamples(int int0) {
 this->numSamples = int0;
 return this;
 }

 public BestCandidateSampling.Sphere numCandidates(int int0) {
 this->numCandidates = int0;
 return this;
 }

 public BestCandidateSampling.Sphere onHemisphere(boolean boolean0) {
 this->onHemisphere = boolean0;
 return this;
 }

 public BestCandidateSampling.Sphere generate(Callback3d callback3d) {
 Random random = new Random(this->seed);
 BestCandidateSampling.Sphere.Node node = new BestCandidateSampling.Sphere.Node();

 for (int int0 = 0; int0 < this->numSamples; int0++) {
 float float0 = Float.NaN;
 float float1 = Float.NaN;
 float float2 = Float.NaN;
 float float3 = 0.0F;

 for (int int1 = 0; int1 < this->numCandidates; int1++) {
 float float4;
 float float5;
 do {
 float4 = random.nextFloat() * 2.0F - 1.0F;
 float5 = random.nextFloat() * 2.0F - 1.0F;
 } while (float4 * float4 + float5 * float5 > 1.0F);

 float float6 = (float)Math.sqrt(1.0 - float4 * float4 - float5 * float5);
 float float7 = 2.0F * float4 * float6;
 float float8 = 2.0F * float5 * float6;
 float float9 = 1.0F - 2.0F * (float4 * float4 + float5 * float5);
 if (this->onHemisphere) {
 float9 = Math.abs(float9);
 }

 float float10 = node.nearest(float7, float8, float9);
 if (float10 > float3) {
 float3 = float10;
 float0 = float7;
 float1 = float8;
 float2 = float9;
 }
 }

 callback3d.onNewSample(float0, float1, float2);
 node.insert(new Vector3f(float0, float1, float2);
 }

 return this;
 }

 private static class Node {
 static const int MAX_OBJECTS_PER_NODE = 32;
 float v0x;
 float v0y;
 float v0z;
 float v1x;
 float v1y;
 float v1z;
 float v2x;
 float v2y;
 float v2z;
 float cx;
 float cy;
 float cz;
 float arc;
 std::vector objects;
 private BestCandidateSampling.Sphere.Node[] children;

 Node() {
 this->children = new BestCandidateSampling.Sphere.Node[8];
 float float0 = 1.0F;
 this->arc = (float) (java.lang.Math.PI * 2);
 this->children[0] = new BestCandidateSampling.Sphere.Node(-float0, 0.0F, 0.0F, 0.0F, 0.0F, float0, 0.0F, float0, 0.0F);
 this->children[1] = new BestCandidateSampling.Sphere.Node(0.0F, 0.0F, float0, float0, 0.0F, 0.0F, 0.0F, float0, 0.0F);
 this->children[2] = new BestCandidateSampling.Sphere.Node(float0, 0.0F, 0.0F, 0.0F, 0.0F, -float0, 0.0F, float0, 0.0F);
 this->children[3] = new BestCandidateSampling.Sphere.Node(0.0F, 0.0F, -float0, -float0, 0.0F, 0.0F, 0.0F, float0, 0.0F);
 this->children[4] = new BestCandidateSampling.Sphere.Node(-float0, 0.0F, 0.0F, 0.0F, -float0, 0.0F, 0.0F, 0.0F, float0);
 this->children[5] = new BestCandidateSampling.Sphere.Node(0.0F, 0.0F, float0, 0.0F, -float0, 0.0F, float0, 0.0F, 0.0F);
 this->children[6] = new BestCandidateSampling.Sphere.Node(float0, 0.0F, 0.0F, 0.0F, -float0, 0.0F, 0.0F, 0.0F, -float0);
 this->children[7] = new BestCandidateSampling.Sphere.Node(0.0F, 0.0F, -float0, 0.0F, -float0, 0.0F, -float0, 0.0F, 0.0F);
 }

 private Node(float float0, float float1, float float2, float float3, float float4, float float5, float float6, float float7, float float8) {
 this->v0x = float0;
 this->v0y = float1;
 this->v0z = float2;
 this->v1x = float3;
 this->v1y = float4;
 this->v1z = float5;
 this->v2x = float6;
 this->v2y = float7;
 this->v2z = float8;
 this->cx = (this->v0x + this->v1x + this->v2x) / 3.0F;
 this->cy = (this->v0y + this->v1y + this->v2y) / 3.0F;
 this->cz = (this->v0z + this->v1z + this->v2z) / 3.0F;
 float float9 = Math.invsqrt(this->cx * this->cx + this->cy * this->cy + this->cz * this->cz);
 this->cx *= float9;
 this->cy *= float9;
 this->cz *= float9;
 float float10 = this->greatCircleDist(this->cx, this->cy, this->cz, this->v0x, this->v0y, this->v0z);
 float float11 = this->greatCircleDist(this->cx, this->cy, this->cz, this->v1x, this->v1y, this->v1z);
 float float12 = this->greatCircleDist(this->cx, this->cy, this->cz, this->v2x, this->v2y, this->v2z);
 float float13 = Math.max(Math.max(float10, float11), float12);
 float13 *= 1.7F;
 this->arc = float13;
 }

 void split() {
 float float0 = this->v1x + this->v2x;
 float float1 = this->v1y + this->v2y;
 float float2 = this->v1z + this->v2z;
 float float3 = Math.invsqrt(float0 * float0 + float1 * float1 + float2 * float2);
 float0 *= float3;
 float1 *= float3;
 float2 *= float3;
 float float4 = this->v0x + this->v2x;
 float float5 = this->v0y + this->v2y;
 float float6 = this->v0z + this->v2z;
 float float7 = Math.invsqrt(float4 * float4 + float5 * float5 + float6 * float6);
 float4 *= float7;
 float5 *= float7;
 float6 *= float7;
 float float8 = this->v0x + this->v1x;
 float float9 = this->v0y + this->v1y;
 float float10 = this->v0z + this->v1z;
 float float11 = Math.invsqrt(float8 * float8 + float9 * float9 + float10 * float10);
 float8 *= float11;
 float9 *= float11;
 float10 *= float11;
 this->children = new BestCandidateSampling.Sphere.Node[4];
 this->children[0] = new BestCandidateSampling.Sphere.Node(this->v0x, this->v0y, this->v0z, float8, float9, float10, float4, float5, float6);
 this->children[1] = new BestCandidateSampling.Sphere.Node(this->v1x, this->v1y, this->v1z, float0, float1, float2, float8, float9, float10);
 this->children[2] = new BestCandidateSampling.Sphere.Node(this->v2x, this->v2y, this->v2z, float4, float5, float6, float0, float1, float2);
 this->children[3] = new BestCandidateSampling.Sphere.Node(float0, float1, float2, float4, float5, float6, float8, float9, float10);
 }

 void insertIntoChild(Vector3f vector3f) {
 for (int int0 = 0; int0 < this->children.length; int0++) {
 BestCandidateSampling.Sphere.Node node1 = this->children[int0];
 if (isPointOnSphericalTriangle(
 vector3f.x,
 vector3f.y,
 vector3f.z,
 node1.v0x,
 node1.v0y,
 node1.v0z,
 node1.v1x,
 node1.v1y,
 node1.v1z,
 node1.v2x,
 node1.v2y,
 node1.v2z,
 1.0E-6F
 )) {
 node1.insert(vector3f);
 return;
 }
 }
 }

 void insert(Vector3f vector3f) {
 if (this->children != nullptr) {
 this->insertIntoChild(vector3f);
 } else {
 if (this->objects != nullptr && this->objects.size() == 32) {
 this->split();

 for (int int0 = 0; int0 < 32; int0++) {
 this->insertIntoChild((Vector3f)this->objects.get(int0);
 }

 this->objects = nullptr;
 this->insertIntoChild(vector3f);
 } else {
 if (this->objects.empty()) {
 this->objects = new ArrayList(32);
 }

 this->objects.add(vector3f);
 }
 }
 }

 private static boolean isPointOnSphericalTriangle(
 float float19,
 float float17,
 float float16,
 float float2,
 float float5,
 float float8,
 float float1,
 float float4,
 float float7,
 float float10,
 float float12,
 float float14,
 float float22
 ) {
 float float0 = float1 - float2;
 float float3 = float4 - float5;
 float float6 = float7 - float8;
 float float9 = float10 - float2;
 float float11 = float12 - float5;
 float float13 = float14 - float8;
 float float15 = float17 * float13 - float16 * float11;
 float float18 = float16 * float9 - float19 * float13;
 float float20 = float19 * float11 - float17 * float9;
 float float21 = float0 * float15 + float3 * float18 + float6 * float20;
 if (float21 > -float22 && float21 < float22) {
 return false;
 } else {
 float float23 = -float2;
 float float24 = -float5;
 float float25 = -float8;
 float float26 = 1.0F / float21;
 float float27 = (float23 * float15 + float24 * float18 + float25 * float20) * float26;
 if (!(float27 < 0.0F) && !(float27 > 1.0F) {
 float float28 = float24 * float6 - float25 * float3;
 float float29 = float25 * float0 - float23 * float6;
 float float30 = float23 * float3 - float24 * float0;
 float float31 = (float19 * float28 + float17 * float29 + float16 * float30) * float26;
 if (!(float31 < 0.0F) && !(float27 + float31 > 1.0F) {
 float float32 = (float9 * float28 + float11 * float29 + float13 * float30) * float26;
 return float32 >= float22;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }
 }

 int child(float float0, float float1, float float2) {
 for (int int0 = 0; int0 < this->children.length; int0++) {
 BestCandidateSampling.Sphere.Node node1 = this->children[int0];
 if (isPointOnSphericalTriangle(
 float0, float1, float2, node1.v0x, node1.v0y, node1.v0z, node1.v1x, node1.v1y, node1.v1z, node1.v2x, node1.v2y, node1.v2z, 1.0E-5F
 )) {
 return int0;
 }
 }

 return 0;
 }

 float greatCircleDist(float float5, float float3, float float1, float float6, float float4, float float2) {
 float float0 = float5 * float6 + float3 * float4 + float1 * float2;
 return (float)((-java.lang.Math.PI / 2) * float0 + (java.lang.Math.PI / 2);
 }

 float nearest(float float0, float float1, float float2) {
 return this->nearest(float0, float1, float2, Float.POSITIVE_INFINITY);
 }

 float nearest(float float1, float float2, float float3, float float4) {
 float float0 = this->greatCircleDist(float1, float2, float3, this->cx, this->cy, this->cz);
 if (float0 - this->arc > float4) {
 return float4;
 } else {
 float float5 = float4;
 if (this->children != nullptr) {
 int int0 = this->children.length;
 int int1 = int0 - 1;
 int int2 = this->child(float1, float2, float3);

 for (int int3 = 0; int3 < int0; int3++) {
 float float6 = this->children[int2].nearest(float1, float2, float3, float5);
 float5 = Math.min(float6, float5);
 int2 = int2 + 1 & int1;
 }

 return float5;
 } else {
 for (int int4 = 0; this->objects != nullptr && int4 < this->objects.size(); int4++) {
 Vector3f vector3f = (Vector3f)this->objects.get(int4);
 float float7 = this->greatCircleDist(vector3f.x, vector3f.y, vector3f.z, float1, float2, float3);
 if (float7 < float5) {
 float5 = float7;
 }
 }

 return float5;
 }
 }
 }
 }
 }
}
} // namespace sampling
} // namespace joml
} // namespace org
