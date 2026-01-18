#include "org/lwjglx/util/glu/tessellation/Mesh.h"

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
namespace tessellation {

private Mesh::Mesh() {
 // TODO: Implement Mesh
 return nullptr;
}

GLUhalfEdge Mesh::MakeEdge(GLUhalfEdge gLUhalfEdge2) {
 // TODO: Implement MakeEdge
 return nullptr;
}

void Mesh::Splice(GLUhalfEdge gLUhalfEdge1, GLUhalfEdge gLUhalfEdge3) {
 // TODO: Implement Splice
}

void Mesh::MakeVertex(GLUvertex gLUvertex1, GLUhalfEdge gLUhalfEdge0, GLUvertex gLUvertex3) {
 // TODO: Implement MakeVertex
}

void Mesh::MakeFace(GLUface gLUface1, GLUhalfEdge gLUhalfEdge0, GLUface gLUface3) {
 // TODO: Implement MakeFace
}

void Mesh::KillEdge(GLUhalfEdge gLUhalfEdge0) {
 // TODO: Implement KillEdge
}

void Mesh::KillVertex(GLUvertex gLUvertex0, GLUvertex gLUvertex1) {
 // TODO: Implement KillVertex
}

void Mesh::KillFace(GLUface gLUface0, GLUface gLUface1) {
 // TODO: Implement KillFace
}

GLUhalfEdge Mesh::__gl_meshMakeEdge(GLUmesh gLUmesh) {
 // TODO: Implement __gl_meshMakeEdge
 return nullptr;
}

bool Mesh::__gl_meshSplice(GLUhalfEdge gLUhalfEdge0, GLUhalfEdge gLUhalfEdge1) {
 // TODO: Implement __gl_meshSplice
 return false;
}

bool Mesh::__gl_meshDelete(GLUhalfEdge gLUhalfEdge1) {
 // TODO: Implement __gl_meshDelete
 return false;
}

GLUhalfEdge Mesh::__gl_meshAddEdgeVertex(GLUhalfEdge gLUhalfEdge1) {
 // TODO: Implement __gl_meshAddEdgeVertex
 return nullptr;
}

GLUhalfEdge Mesh::__gl_meshSplitEdge(GLUhalfEdge gLUhalfEdge1) {
 // TODO: Implement __gl_meshSplitEdge
 return nullptr;
}

GLUhalfEdge Mesh::__gl_meshConnect(GLUhalfEdge gLUhalfEdge1, GLUhalfEdge gLUhalfEdge3) {
 // TODO: Implement __gl_meshConnect
 return nullptr;
}

void Mesh::__gl_meshZapFace(GLUface gLUface0) {
 // TODO: Implement __gl_meshZapFace
}

GLUmesh Mesh::__gl_meshNewMesh() {
 // TODO: Implement __gl_meshNewMesh
 return nullptr;
}

GLUmesh Mesh::__gl_meshUnion(GLUmesh gLUmesh0, GLUmesh gLUmesh1) {
 // TODO: Implement __gl_meshUnion
 return nullptr;
}

void Mesh::__gl_meshDeleteMeshZap(GLUmesh gLUmesh) {
 // TODO: Implement __gl_meshDeleteMeshZap
}

void Mesh::__gl_meshDeleteMesh(GLUmesh gLUmesh) {
 // TODO: Implement __gl_meshDeleteMesh
}

void Mesh::__gl_meshCheckMesh(GLUmesh gLUmesh) {
 // TODO: Implement __gl_meshCheckMesh
}

} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
