#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiMesh.h"
#include "org/joml/Vector3f.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexArray.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexFormat.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class ImportedStaticMesh {
public:
    VertexArray verticesUnskinned = nullptr;
   int[] elements = nullptr;
    const Vector3f minXYZ = std::make_shared<Vector3f>(float.MAX_VALUE);
    const Vector3f maxXYZ = std::make_shared<Vector3f>(-float.MAX_VALUE);

    public ImportedStaticMesh(AiMesh var1) {
      this.processAiScene(var1);
   }

    void processAiScene(AiMesh var1) {
    int var2 = var1.getNumVertices();
    int var3 = 0;

      for (int var4 = 0; var4 < 8; var4++) {
         if (var1.hasTexCoords(var4)) {
            var3++;
         }
      }

    VertexFormat var12 = std::make_shared<VertexFormat>(3 + var3);
      var12.setElement(0, VertexType.VertexArray, 12);
      var12.setElement(1, VertexType.NormalArray, 12);
      var12.setElement(2, VertexType.TangentArray, 12);

      for (int var5 = 0; var5 < var3; var5++) {
         var12.setElement(3 + var5, VertexType.TextureCoordArray, 8);
      }

      var12.calculate();
      this.verticesUnskinned = std::make_shared<VertexArray>(var12, var2);
    Vector3f var13 = std::make_shared<Vector3f>();

      for (int var6 = 0; var6 < var2; var6++) {
    float var7 = var1.getPositionX(var6);
    float var8 = var1.getPositionY(var6);
    float var9 = var1.getPositionZ(var6);
         this.minXYZ.min(var13.set(var7, var8, var9));
         this.maxXYZ.max(var13.set(var7, var8, var9));
         this.verticesUnskinned.setElement(var6, 0, var1.getPositionX(var6), var1.getPositionY(var6), var1.getPositionZ(var6));
         if (var1.hasNormals()) {
            this.verticesUnskinned.setElement(var6, 1, var1.getNormalX(var6), var1.getNormalY(var6), var1.getNormalZ(var6));
         } else {
            this.verticesUnskinned.setElement(var6, 1, 0.0F, 1.0F, 0.0F);
         }

         if (var1.hasTangentsAndBitangents()) {
            this.verticesUnskinned.setElement(var6, 2, var1.getTangentX(var6), var1.getTangentY(var6), var1.getTangentZ(var6));
         } else {
            this.verticesUnskinned.setElement(var6, 2, 0.0F, 0.0F, 1.0F);
         }

         if (var3 > 0) {
    int var10 = 0;

            for (int var11 = 0; var11 < 8; var11++) {
               if (var1.hasTexCoords(var11)) {
                  this.verticesUnskinned.setElement(var6, 3 + var10, var1.getTexCoordU(var6, var11), 1.0F - var1.getTexCoordV(var6, var11));
                  var10++;
               }
            }
         }
      }

    int var14 = var1.getNumFaces();
      this.elements = new int[var14 * 3];

      for (int var15 = 0; var15 < var14; var15++) {
         this.elements[var15 * 3 + 2] = var1.getFaceVertex(var15, 0);
         this.elements[var15 * 3 + 1] = var1.getFaceVertex(var15, 1);
         this.elements[var15 * 3 + 0] = var1.getFaceVertex(var15, 2);
      }
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
