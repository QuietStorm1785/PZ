#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiBone.h"
#include "jassimp/AiBoneWeight.h"
#include "jassimp/AiMesh.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexArray.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexFormat.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class ImportedSkinnedMesh {
public:
    const ImportedSkeleton skeleton;
    std::string name;
    VertexArray vertices = nullptr;
   int[] elements = nullptr;

    public ImportedSkinnedMesh(ImportedSkeleton var1, AiMesh var2) {
      this.skeleton = var1;
      this.processAiScene(var2);
   }

    void processAiScene(AiMesh var1) {
      this.name = var1.getName();
    int var2 = var1.getNumVertices();
    int var3 = var2 * 4;
      int[] var4 = new int[var3];
      float[] var5 = new float[var3];

      for (int var6 = 0; var6 < var3; var6++) {
         var5[var6] = 0.0F;
      }

    std::vector var17 = var1.getBones();
    int var7 = var17.size();

      for (int var8 = 0; var8 < var7; var8++) {
    AiBone var9 = (AiBone)var17.get(var8);
    std::string var10 = var9.getName();
    int var11 = (int)this.skeleton.boneIndices.get(var10);
    std::vector var12 = var9.getBoneWeights();

         for (int var13 = 0; var13 < var9.getNumWeights(); var13++) {
    AiBoneWeight var14 = (AiBoneWeight)var12.get(var13);
    int var15 = var14.getVertexId() * 4;

            for (int var16 = 0; var16 < 4; var16++) {
               if (var5[var15 + var16] == 0.0F) {
                  var5[var15 + var16] = var14.getWeight();
                  var4[var15 + var16] = var11;
                  break;
               }
            }
         }
      }

    int var18 = getNumUVs(var1);
    VertexFormat var19 = std::make_shared<VertexFormat>(5 + var18);
      var19.setElement(0, VertexType.VertexArray, 12);
      var19.setElement(1, VertexType.NormalArray, 12);
      var19.setElement(2, VertexType.TangentArray, 12);
      var19.setElement(3, VertexType.BlendWeightArray, 16);
      var19.setElement(4, VertexType.BlendIndexArray, 16);

      for (int var20 = 0; var20 < var18; var20++) {
         var19.setElement(5 + var20, VertexType.TextureCoordArray, 8);
      }

      var19.calculate();
      this.vertices = std::make_shared<VertexArray>(var19, var2);

      for (int var21 = 0; var21 < var2; var21++) {
         this.vertices.setElement(var21, 0, var1.getPositionX(var21), var1.getPositionY(var21), var1.getPositionZ(var21));
         if (var1.hasNormals()) {
            this.vertices.setElement(var21, 1, var1.getNormalX(var21), var1.getNormalY(var21), var1.getNormalZ(var21));
         } else {
            this.vertices.setElement(var21, 1, 0.0F, 1.0F, 0.0F);
         }

         if (var1.hasTangentsAndBitangents()) {
            this.vertices.setElement(var21, 2, var1.getTangentX(var21), var1.getTangentY(var21), var1.getTangentZ(var21));
         } else {
            this.vertices.setElement(var21, 2, 0.0F, 0.0F, 1.0F);
         }

         this.vertices.setElement(var21, 3, var5[var21 * 4], var5[var21 * 4 + 1], var5[var21 * 4 + 2], var5[var21 * 4 + 3]);
         this.vertices.setElement(var21, 4, var4[var21 * 4], var4[var21 * 4 + 1], var4[var21 * 4 + 2], var4[var21 * 4 + 3]);
         if (var18 > 0) {
    int var23 = 0;

            for (int var25 = 0; var25 < 8; var25++) {
               if (var1.hasTexCoords(var25)) {
                  this.vertices.setElement(var21, 5 + var23, var1.getTexCoordU(var21, var25), 1.0F - var1.getTexCoordV(var21, var25));
                  var23++;
               }
            }
         }
      }

    int var22 = var1.getNumFaces();
      this.elements = new int[var22 * 3];

      for (int var24 = 0; var24 < var22; var24++) {
         this.elements[var24 * 3 + 2] = var1.getFaceVertex(var24, 0);
         this.elements[var24 * 3 + 1] = var1.getFaceVertex(var24, 1);
         this.elements[var24 * 3 + 0] = var1.getFaceVertex(var24, 2);
      }
   }

    static int getNumUVs(AiMesh var0) {
    int var1 = 0;

      for (int var2 = 0; var2 < 8; var2++) {
         if (var0.hasTexCoords(var2)) {
            var1++;
         }
      }

    return var1;
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
