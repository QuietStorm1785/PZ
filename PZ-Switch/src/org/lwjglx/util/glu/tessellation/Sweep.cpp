#include "org/lwjglx/util/glu/tessellation/Sweep.h"

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {

private
Sweep::Sweep() {
 // TODO: Implement Sweep
 return nullptr;
}

void Sweep::DebugEvent(GLUtessellatorImpl var0) {
 // TODO: Implement DebugEvent
}

void Sweep::AddWinding(GLUhalfEdge gLUhalfEdge1, GLUhalfEdge gLUhalfEdge0) {
 // TODO: Implement AddWinding
}

ActiveRegion Sweep::RegionBelow(ActiveRegion activeRegion) {
 // TODO: Implement RegionBelow
 return nullptr;
}

ActiveRegion Sweep::RegionAbove(ActiveRegion activeRegion) {
 // TODO: Implement RegionAbove
 return nullptr;
}

bool Sweep::EdgeLeq(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion0, ActiveRegion activeRegion1) {
 // TODO: Implement EdgeLeq
 return false;
}

void Sweep::DeleteRegion(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion) {
 // TODO: Implement DeleteRegion
}

bool Sweep::FixUpperEdge(ActiveRegion activeRegion, GLUhalfEdge gLUhalfEdge) {
 // TODO: Implement FixUpperEdge
 return false;
}

ActiveRegion Sweep::TopLeftRegion(ActiveRegion activeRegion) {
 // TODO: Implement TopLeftRegion
 return nullptr;
}

ActiveRegion Sweep::TopRightRegion(ActiveRegion activeRegion) {
 // TODO: Implement TopRightRegion
 return nullptr;
}

ActiveRegion Sweep::AddRegionBelow(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion1,
 GLUhalfEdge gLUhalfEdge) {
 // TODO: Implement AddRegionBelow
 return nullptr;
}

bool Sweep::IsWindingInside(GLUtessellatorImpl gLUtessellatorImpl, int int0) {
 // TODO: Implement IsWindingInside
 return false;
}

void Sweep::ComputeWinding(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion) {
 // TODO: Implement ComputeWinding
}

void Sweep::FinishRegion(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion) {
 // TODO: Implement FinishRegion
}

GLUhalfEdge Sweep::FinishLeftRegions(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion1,
 ActiveRegion activeRegion2) {
 // TODO: Implement FinishLeftRegions
 return nullptr;
}

void Sweep::CallCombine(GLUtessellatorImpl gLUtessellatorImpl,
 GLUvertex gLUvertex, Object[] objects1, float[] floats,
 bool boolean0) {
 // TODO: Implement CallCombine
}

void Sweep::SpliceMergeVertices(GLUtessellatorImpl gLUtessellatorImpl,
 GLUhalfEdge gLUhalfEdge0,
 GLUhalfEdge gLUhalfEdge1) {
 // TODO: Implement SpliceMergeVertices
}

void Sweep::VertexWeights(GLUvertex gLUvertex1, GLUvertex gLUvertex0,
 GLUvertex gLUvertex2, float[] floats) {
 // TODO: Implement VertexWeights
}

bool Sweep::CheckForRightSplice(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion1) {
 // TODO: Implement CheckForRightSplice
 return false;
}

bool Sweep::CheckForLeftSplice(GLUtessellatorImpl var0,
 ActiveRegion activeRegion1) {
 // TODO: Implement CheckForLeftSplice
 return false;
}

bool Sweep::CheckForIntersect(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion1) {
 // TODO: Implement CheckForIntersect
 return false;
}

void Sweep::WalkDirtyRegions(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion1) {
 // TODO: Implement WalkDirtyRegions
}

void Sweep::ConnectRightVertex(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion1,
 GLUhalfEdge gLUhalfEdge1) {
 // TODO: Implement ConnectRightVertex
}

void Sweep::ConnectLeftDegenerate(GLUtessellatorImpl gLUtessellatorImpl,
 ActiveRegion activeRegion0,
 GLUvertex gLUvertex) {
 // TODO: Implement ConnectLeftDegenerate
}

void Sweep::ConnectLeftVertex(GLUtessellatorImpl gLUtessellatorImpl,
 GLUvertex gLUvertex) {
 // TODO: Implement ConnectLeftVertex
}

void Sweep::SweepEvent(GLUtessellatorImpl gLUtessellatorImpl,
 GLUvertex gLUvertex) {
 // TODO: Implement SweepEvent
}

void Sweep::AddSentinel(GLUtessellatorImpl gLUtessellatorImpl, double double0) {
 // TODO: Implement AddSentinel
}

void Sweep::InitEdgeDict(const GLUtessellatorImpl) {
 // TODO: Implement InitEdgeDict
}

bool Sweep::leq(void *var1, void *object1, void *object0) {
 // TODO: Implement leq
 return false;
}

void Sweep::DoneEdgeDict(GLUtessellatorImpl gLUtessellatorImpl) {
 // TODO: Implement DoneEdgeDict
}

void Sweep::RemoveDegenerateEdges(GLUtessellatorImpl gLUtessellatorImpl) {
 // TODO: Implement RemoveDegenerateEdges
}

bool Sweep::InitPriorityQ(GLUtessellatorImpl gLUtessellatorImpl) {
 // TODO: Implement InitPriorityQ
 return false;
}

bool Sweep::leq(void *object1, void *object0) {
 // TODO: Implement leq
 return false;
}

void Sweep::DonePriorityQ(GLUtessellatorImpl gLUtessellatorImpl) {
 // TODO: Implement DonePriorityQ
}

bool Sweep::RemoveDegenerateFaces(GLUmesh gLUmesh) {
 // TODO: Implement RemoveDegenerateFaces
 return false;
}

bool Sweep::__gl_computeInterior(GLUtessellatorImpl gLUtessellatorImpl) {
 // TODO: Implement __gl_computeInterior
 return false;
}

} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
