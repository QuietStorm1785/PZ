#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/util/glu/GLUtessellator.h"
#include "org/lwjglx/util/glu/GLUtessellatorCallback.h"
#include "org/lwjglx/util/glu/GLUtessellatorCallbackAdapter.h"

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GLUtessellatorImpl {
public:
 static const int TESS_MAX_CACHE = 100;
 int state;
 GLUhalfEdge lastEdge;
 GLUmesh mesh;
 double[] normal = new double[3];
 double[] sUnit = new double[3];
 double[] tUnit = new double[3];
 double relTolerance;
 int windingRule;
 bool fatalError;
 Dict dict;
 PriorityQ pq;
 GLUvertex event;
 bool flagBoundary;
 bool boundaryOnly;
 GLUface lonelyTriList;
 bool flushCacheOnNextVertex;
 int cacheCount;
 CachedVertex[] cache = new CachedVertex[100];
 void* polygonData;
 GLUtessellatorCallback callBegin;
 GLUtessellatorCallback callEdgeFlag;
 GLUtessellatorCallback callVertex;
 GLUtessellatorCallback callEnd;
 GLUtessellatorCallback callError;
 GLUtessellatorCallback callCombine;
 GLUtessellatorCallback callBeginData;
 GLUtessellatorCallback callEdgeFlagData;
 GLUtessellatorCallback callVertexData;
 GLUtessellatorCallback callEndData;
 GLUtessellatorCallback callErrorData;
 GLUtessellatorCallback callCombineData;
 static const double GLU_TESS_DEFAULT_TOLERANCE = 0.0;
 static GLUtessellatorCallback NULL_CB = new GLUtessellatorCallbackAdapter();

 public GLUtessellatorImpl() {
 this->state = 0;
 this->normal[0] = 0.0;
 this->normal[1] = 0.0;
 this->normal[2] = 0.0;
 this->relTolerance = 0.0;
 this->windingRule = 100130;
 this->flagBoundary = false;
 this->boundaryOnly = false;
 this->callBegin = NULL_CB;
 this->callEdgeFlag = NULL_CB;
 this->callVertex = NULL_CB;
 this->callEnd = NULL_CB;
 this->callError = NULL_CB;
 this->callCombine = NULL_CB;
 this->callBeginData = NULL_CB;
 this->callEdgeFlagData = NULL_CB;
 this->callVertexData = NULL_CB;
 this->callEndData = NULL_CB;
 this->callErrorData = NULL_CB;
 this->callCombineData = NULL_CB;
 this->polygonData = nullptr;

 for (int int0 = 0; int0 < this->cache.length; int0++) {
 this->cache[int0] = std::make_unique<CachedVertex>();
 }
 }

 static GLUtessellator gluNewTess() {
 return std::make_unique<GLUtessellatorImpl>();
 }

 void makeDormant() {
 if (this->mesh != nullptr) {
 Mesh.__gl_meshDeleteMesh(this->mesh);
 }

 this->state = 0;
 this->lastEdge = nullptr;
 this->mesh = nullptr;
 }

 void requireState(int int0) {
 if (this->state != int0) {
 this->gotoState(int0);
 }
 }

 void gotoState(int int0) {
 while (this->state != int0) {
 if (this->state < int0) {
 if (this->state == 0) {
 this->callErrorOrErrorData(100151);
 this->gluTessBeginPolygon(nullptr);
 } else if (this->state == 1) {
 this->callErrorOrErrorData(100152);
 this->gluTessBeginContour();
 }
 } else if (this->state == 2) {
 this->callErrorOrErrorData(100154);
 this->gluTessEndContour();
 } else if (this->state == 1) {
 this->callErrorOrErrorData(100153);
 this->makeDormant();
 }
 }
 }

 void gluDeleteTess() {
 this->requireState(0);
 }

 void gluTessProperty(int int0, double double0) {
 switch (int0) {
 case 100140:
 int int1 = (int)double0;
 if (int1 != double0) {
 break;
 }

 switch (int1) {
 case 100130:
 case 100131:
 case 100132:
 case 100133:
 case 100134:
 this->windingRule = int1;
 return;
 }
 case 100141:
 this->boundaryOnly = double0 != 0.0;
 return;
 case 100142:
 if (!(double0 < 0.0) && !(double0 > 1.0) {
 this->relTolerance = double0;
 return;
 }
 break;
 default:
 this->callErrorOrErrorData(100900);
 return;
 }

 this->callErrorOrErrorData(100901);
 }

 void gluGetTessProperty(int int0, double[] doubles, int int1) {
 switch (int0) {
 case 100140:
 assert this->windingRule == 100130
 || this->windingRule == 100131
 || this->windingRule == 100132
 || this->windingRule == 100133
 || this->windingRule == 100134;

 doubles[int1] = this->windingRule;
 break;
 case 100141:
 assert this->boundaryOnly || !this->boundaryOnly;

 doubles[int1] = this->boundaryOnly ? 1.0 : 0.0;
 break;
 case 100142:
 assert 0.0 <= this->relTolerance && this->relTolerance <= 1.0;

 doubles[int1] = this->relTolerance;
 break;
 default:
 doubles[int1] = 0.0;
 this->callErrorOrErrorData(100900);
 }
 }

 void gluTessNormal(double double0, double double1, double double2) {
 this->normal[0] = double0;
 this->normal[1] = double1;
 this->normal[2] = double2;
 }

 void gluTessCallback(int int0, GLUtessellatorCallback gLUtessellatorCallback) {
 switch (int0) {
 case 100100:
 this->callBegin = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100101:
 this->callVertex = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100102:
 this->callEnd = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100103:
 this->callError = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100104:
 this->callEdgeFlag = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 this->flagBoundary = gLUtessellatorCallback != nullptr;
 return;
 case 100105:
 this->callCombine = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100106:
 this->callBeginData = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100107:
 this->callVertexData = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100108:
 this->callEndData = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100109:
 this->callErrorData = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 case 100110:
 this->callEdgeFlagData = this->callBegin = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 this->flagBoundary = gLUtessellatorCallback != nullptr;
 return;
 case 100111:
 this->callCombineData = gLUtessellatorCallback.empty() ? NULL_CB : gLUtessellatorCallback;
 return;
 default:
 this->callErrorOrErrorData(100900);
 }
 }

 bool addVertex(double[] doubles, void* object) {
 GLUhalfEdge gLUhalfEdge = this->lastEdge;
 if (gLUhalfEdge.empty()) {
 gLUhalfEdge = Mesh.__gl_meshMakeEdge(this->mesh);
 if (gLUhalfEdge.empty()) {
 return false;
 }

 if (!Mesh.__gl_meshSplice(gLUhalfEdge, gLUhalfEdge.Sym) {
 return false;
 }
 } else {
 if (Mesh.__gl_meshSplitEdge(gLUhalfEdge) == nullptr) {
 return false;
 }

 gLUhalfEdge = gLUhalfEdge.Lnext;
 }

 gLUhalfEdge.Org.data = object;
 gLUhalfEdge.Org.coords[0] = doubles[0];
 gLUhalfEdge.Org.coords[1] = doubles[1];
 gLUhalfEdge.Org.coords[2] = doubles[2];
 gLUhalfEdge.winding = 1;
 gLUhalfEdge.Sym.winding = -1;
 this->lastEdge = gLUhalfEdge;
 return true;
 }

 void cacheVertex(double[] doubles, void* object) {
 if (this->cache[this->cacheCount] == nullptr) {
 this->cache[this->cacheCount] = std::make_unique<CachedVertex>();
 }

 CachedVertex cachedVertex = this->cache[this->cacheCount];
 cachedVertex.data = object;
 cachedVertex.coords[0] = doubles[0];
 cachedVertex.coords[1] = doubles[1];
 cachedVertex.coords[2] = doubles[2];
 this->cacheCount++;
 }

 bool flushCache() {
 CachedVertex[] cachedVertexs = this->cache;
 this->mesh = Mesh.__gl_meshNewMesh();
 if (this->mesh.empty()) {
 return false;
 } else {
 for (int int0 = 0; int0 < this->cacheCount; int0++) {
 CachedVertex cachedVertex = cachedVertexs[int0];
 if (!this->addVertex(cachedVertex.coords, cachedVertex.data) {
 return false;
 }
 }

 this->cacheCount = 0;
 this->flushCacheOnNextVertex = false;
 return true;
 }
 }

 void gluTessVertex(double[] doubles1, int int1, void* object) {
 bool boolean0 = false;
 double[] doubles0 = new double[3];
 this->requireState(2);
 if (this->flushCacheOnNextVertex) {
 if (!this->flushCache()) {
 this->callErrorOrErrorData(100902);
 return;
 }

 this->lastEdge = nullptr;
 }

 for (int int0 = 0; int0 < 3; int0++) {
 double double0 = doubles1[int0 + int1];
 if (double0 < -1.0E150) {
 double0 = -1.0E150;
 boolean0 = true;
 }

 if (double0 > 1.0E150) {
 double0 = 1.0E150;
 boolean0 = true;
 }

 doubles0[int0] = double0;
 }

 if (boolean0) {
 this->callErrorOrErrorData(100155);
 }

 if (this->mesh.empty()) {
 if (this->cacheCount < 100) {
 this->cacheVertex(doubles0, object);
 return;
 }

 if (!this->flushCache()) {
 this->callErrorOrErrorData(100902);
 return;
 }
 }

 if (!this->addVertex(doubles0, object) {
 this->callErrorOrErrorData(100902);
 }
 }

 void gluTessBeginPolygon(void* object) {
 this->requireState(0);
 this->state = 1;
 this->cacheCount = 0;
 this->flushCacheOnNextVertex = false;
 this->mesh = nullptr;
 this->polygonData = object;
 }

 void gluTessBeginContour() {
 this->requireState(1);
 this->state = 2;
 this->lastEdge = nullptr;
 if (this->cacheCount > 0) {
 this->flushCacheOnNextVertex = true;
 }
 }

 void gluTessEndContour() {
 this->requireState(2);
 this->state = 1;
 }

 void gluTessEndPolygon() {
 try {
 this->requireState(1);
 this->state = 0;
 if (this->mesh.empty()) {
 if (!this->flagBoundary && Render.__gl_renderCache(this) {
 this->polygonData = nullptr;
 return;
 }

 if (!this->flushCache()) {
 throw std::make_unique<RuntimeException>();
 }
 }

 Normal.__gl_projectPolygon(this);
 if (!Sweep.__gl_computeInterior(this) {
 throw std::make_unique<RuntimeException>();
 }

 GLUmesh gLUmesh = this->mesh;
 if (!this->fatalError) {
 bool boolean0 = true;
 if (this->boundaryOnly) {
 boolean0 = TessMono.__gl_meshSetWindingNumber(gLUmesh, 1, true);
 } else {
 boolean0 = TessMono.__gl_meshTessellateInterior(gLUmesh);
 }

 if (!boolean0) {
 throw std::make_unique<RuntimeException>();
 }

 Mesh.__gl_meshCheckMesh(gLUmesh);
 if (this->callBegin != NULL_CB
 || this->callEnd != NULL_CB
 || this->callVertex != NULL_CB
 || this->callEdgeFlag != NULL_CB
 || this->callBeginData != NULL_CB
 || this->callEndData != NULL_CB
 || this->callVertexData != NULL_CB
 || this->callEdgeFlagData != NULL_CB) {
 if (this->boundaryOnly) {
 Render.__gl_renderBoundary(this, gLUmesh);
 } else {
 Render.__gl_renderMesh(this, gLUmesh);
 }
 }
 }

 Mesh.__gl_meshDeleteMesh(gLUmesh);
 this->polygonData = nullptr;
 gLUmesh = nullptr;
 } catch (Exception exception) {
 exception.printStackTrace();
 this->callErrorOrErrorData(100902);
 }
 }

 void gluBeginPolygon() {
 this->gluTessBeginPolygon(nullptr);
 this->gluTessBeginContour();
 }

 void gluNextContour(int var1) {
 this->gluTessEndContour();
 this->gluTessBeginContour();
 }

 void gluEndPolygon() {
 this->gluTessEndContour();
 this->gluTessEndPolygon();
 }

 void callBeginOrBeginData(int int0) {
 if (this->callBeginData != NULL_CB) {
 this->callBeginData.beginData(int0, this->polygonData);
 } else {
 this->callBegin.begin(int0);
 }
 }

 void callVertexOrVertexData(void* object) {
 if (this->callVertexData != NULL_CB) {
 this->callVertexData.vertexData(object, this->polygonData);
 } else {
 this->callVertex.vertex(object);
 }
 }

 void callEdgeFlagOrEdgeFlagData(bool boolean0) {
 if (this->callEdgeFlagData != NULL_CB) {
 this->callEdgeFlagData.edgeFlagData(boolean0, this->polygonData);
 } else {
 this->callEdgeFlag.edgeFlag(boolean0);
 }
 }

 void callEndOrEndData() {
 if (this->callEndData != NULL_CB) {
 this->callEndData.endData(this->polygonData);
 } else {
 this->callEnd.end();
 }
 }

 void callCombineOrCombineData(double[] doubles, Object[] objects0, float[] floats, Object[] objects1) {
 if (this->callCombineData != NULL_CB) {
 this->callCombineData.combineData(doubles, objects0, floats, objects1, this->polygonData);
 } else {
 this->callCombine.combine(doubles, objects0, floats, objects1);
 }
 }

 void callErrorOrErrorData(int int0) {
 if (this->callErrorData != NULL_CB) {
 this->callErrorData.errorData(int0, this->polygonData);
 } else {
 this->callError.error(int0);
 }
 }
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
