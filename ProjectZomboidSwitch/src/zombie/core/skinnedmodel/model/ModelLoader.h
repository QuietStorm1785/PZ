#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/core/skinnedmodel/animation/StaticAnimation.h"
#include "zombie/core/skinnedmodel/model/ModelLoader/1.h"
#include "zombie/core/skinnedmodel/model/ModelLoader/LoadMode.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexArray.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexFormat.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"
#include "zombie/util/SharedStrings.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelLoader {
public:
    static const ModelLoader instance = std::make_shared<ModelLoader>();
   private const ThreadLocal<SharedStrings> sharedStrings = ThreadLocal.withInitial(SharedStrings::new);

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    ModelTxt loadTxt(const std::string& var1, bool var2, bool var3, SkinningData var4) {
    ModelTxt var5 = std::make_shared<ModelTxt>();
      var5.bStatic = var2;
      var5.bReverse = var3;
    VertexFormat var6 = std::make_shared<VertexFormat>(var2 ? 4 : 6);
      var6.setElement(0, VertexType.VertexArray, 12);
      var6.setElement(1, VertexType.NormalArray, 12);
      var6.setElement(2, VertexType.TangentArray, 12);
      var6.setElement(3, VertexType.TextureCoordArray, 8);
      if (!var2) {
         var6.setElement(4, VertexType.BlendWeightArray, 16);
         var6.setElement(5, VertexType.BlendIndexArray, 16);
      }

      var6.calculate();

      try (
    FileReader var7 = std::make_shared<FileReader>(var1);
    BufferedReader var8 = std::make_shared<BufferedReader>(var7);
      ) {
    SharedStrings var9 = this.sharedStrings.get();
    LoadMode var10 = LoadMode.Version;
    std::string var11 = nullptr;
    int var12 = 0;
    int var13 = 0;
    int var14 = 0;
    int var15 = 0;
    int var16 = 0;
    bool var17 = false;

         while ((var11 = var8.readLine()) != nullptr) {
            if (var11.indexOf(35) != 0) {
               if (var11.contains("Tangent")) {
                  if (var2) {
                     var12 += 2;
                  }

                  var17 = true;
               }

               if (var12 > 0) {
                  var12--;
               } else {
                  switch (1.$SwitchMap$zombie$core$skinnedmodel$model$ModelLoader$LoadMode[var10.ordinal()]) {
                     case 1:
                        var10 = LoadMode.ModelName;
                        break;
                     case 2:
                        var10 = LoadMode.VertexStrideElementCount;
                        break;
                     case 3:
                        var10 = LoadMode.VertexCount;
                        if (var2) {
                           var12 = 7;
                        } else {
                           var12 = 13;
                        }
                        break;
                     case 4:
                        var13 = int.parseInt(var11);
                        var10 = LoadMode.VertexBuffer;
                        var5.vertices = std::make_shared<VertexArray>(var6, var13);
                        break;
                     case 5:
    int var69 = 0;

                        for (; var69 < var13; var69++) {
                           std::string[] var76 = var11.split(",");
    float var90 = float.parseFloat(var76[0].trim());
    float var99 = float.parseFloat(var76[1].trim());
    float var105 = float.parseFloat(var76[2].trim());
                           var11 = var8.readLine();
                           var76 = var11.split(",");
    float var109 = float.parseFloat(var76[0].trim());
    float var112 = float.parseFloat(var76[1].trim());
    float var114 = float.parseFloat(var76[2].trim());
    float var115 = 0.0F;
    float var116 = 0.0F;
    float var117 = 0.0F;
                           if (var17) {
                              var11 = var8.readLine();
                              var76 = var11.split(",");
                              var115 = float.parseFloat(var76[0].trim());
                              var116 = float.parseFloat(var76[1].trim());
                              var117 = float.parseFloat(var76[2].trim());
                           }

                           var11 = var8.readLine();
                           var76 = var11.split(",");
    float var118 = float.parseFloat(var76[0].trim());
    float var30 = float.parseFloat(var76[1].trim());
    float var31 = 0.0F;
    float var32 = 0.0F;
    float var33 = 0.0F;
    float var34 = 0.0F;
    int var35 = 0;
    int var36 = 0;
    int var37 = 0;
    int var38 = 0;
                           if (!var2) {
                              var11 = var8.readLine();
                              var76 = var11.split(",");
                              var31 = float.parseFloat(var76[0].trim());
                              var32 = float.parseFloat(var76[1].trim());
                              var33 = float.parseFloat(var76[2].trim());
                              var34 = float.parseFloat(var76[3].trim());
                              var11 = var8.readLine();
                              var76 = var11.split(",");
                              var35 = int.parseInt(var76[0].trim());
                              var36 = int.parseInt(var76[1].trim());
                              var37 = int.parseInt(var76[2].trim());
                              var38 = int.parseInt(var76[3].trim());
                           }

                           var11 = var8.readLine();
                           var5.vertices.setElement(var69, 0, var90, var99, var105);
                           var5.vertices.setElement(var69, 1, var109, var112, var114);
                           var5.vertices.setElement(var69, 2, var115, var116, var117);
                           var5.vertices.setElement(var69, 3, var118, var30);
                           if (!var2) {
                              var5.vertices.setElement(var69, 4, var31, var32, var33, var34);
                              var5.vertices.setElement(var69, 5, var35, var36, var37, var38);
                           }
                        }

                        var10 = LoadMode.NumberOfFaces;
                        break;
                     case 6:
                        var14 = int.parseInt(var11);
                        var5.elements = new int[var14 * 3];
                        var10 = LoadMode.FaceData;
                        break;
                     case 7:
                        for (int var68 = 0; var68 < var14; var68++) {
                           std::string[] var75 = var11.split(",");
    int var89 = int.parseInt(var75[0].trim());
    int var98 = int.parseInt(var75[1].trim());
    int var104 = int.parseInt(var75[2].trim());
                           if (var3) {
                              var5.elements[var68 * 3 + 2] = var89;
                              var5.elements[var68 * 3 + 1] = var98;
                              var5.elements[var68 * 3 + 0] = var104;
                           } else {
                              var5.elements[var68 * 3 + 0] = var89;
                              var5.elements[var68 * 3 + 1] = var98;
                              var5.elements[var68 * 3 + 2] = var104;
                           }

                           var11 = var8.readLine();
                        }

                        var10 = LoadMode.NumberOfBones;
                        break;
                     case 8:
                        var16 = int.parseInt(var11);
                        var10 = LoadMode.SkeletonHierarchy;
                        break;
                     case 9:
                        for (int var67 = 0; var67 < var16; var67++) {
    int var74 = int.parseInt(var11);
                           var11 = var8.readLine();
    int var88 = int.parseInt(var11);
                           var11 = var8.readLine();
    std::string var97 = var9.get(var11);
                           var11 = var8.readLine();
                           var5.SkeletonHierarchy.push_back(var88);
                           var5.boneIndices.put(var97, var74);
                        }

                        var10 = LoadMode.BindPose;
                        break;
                     case 10:
                        for (int var66 = 0; var66 < var16; var66++) {
                           var11 = var8.readLine();
    std::string var73 = var8.readLine();
    std::string var87 = var8.readLine();
    std::string var96 = var8.readLine();
                           var5.bindPose.push_back(var66, this.getMatrix(var11, var73, var87, var96));
                           var11 = var8.readLine();
                        }

                        var10 = LoadMode.InvBindPose;
                        break;
                     case 11:
                        for (int var65 = 0; var65 < var16; var65++) {
                           var11 = var8.readLine();
    std::string var72 = var8.readLine();
    std::string var86 = var8.readLine();
    std::string var95 = var8.readLine();
                           var5.invBindPose.push_back(var65, this.getMatrix(var11, var72, var86, var95));
                           var11 = var8.readLine();
                        }

                        var10 = LoadMode.SkinOffsetMatrices;
                        break;
                     case 12:
                        for (int var64 = 0; var64 < var16; var64++) {
                           var11 = var8.readLine();
    std::string var71 = var8.readLine();
    std::string var85 = var8.readLine();
    std::string var94 = var8.readLine();
                           var5.skinOffsetMatrices.push_back(var64, this.getMatrix(var11, var71, var85, var94));
                           var11 = var8.readLine();
                        }

                        var10 = LoadMode.NumberOfAnims;
                        break;
                     case 13:
                        var15 = int.parseInt(var11);
                        var10 = LoadMode.Anim;
                        break;
                     case 14:
    std::vector var18 = new std::vector();
                        var11 = var8.readLine();
    float var20 = float.parseFloat(var11);
                        var11 = var8.readLine();
    int var21 = int.parseInt(var11);
                        var11 = var8.readLine();

                        for (int var22 = 0; var22 < var21; var22++) {
    Keyframe var23 = std::make_shared<Keyframe>();
    int var24 = int.parseInt(var11);
    std::string var48 = var8.readLine();
    std::string var25 = var9.get(var48);
    std::string var49 = var8.readLine();
    float var26 = float.parseFloat(var49);
                           var11 = var8.readLine();
    std::string var27 = var8.readLine();
    Vector3f var28 = this.getVector(var11);
    Quaternion var29 = this.getQuaternion(var27);
                           if (var22 < var21 - 1) {
                              var11 = var8.readLine();
                           }

                           var23.Bone = var24;
                           var23.BoneName = var25;
                           var23.Time = var26;
                           var23.Rotation = var29;
                           var23.Position = std::make_shared<Vector3f>(var28);
                           var18.push_back(var23);
                        }

    AnimationClip var103 = std::make_shared<AnimationClip>(var20, var18, var11, false);
                        var18.clear();
                        if (ModelManager.instance.bCreateSoftwareMeshes) {
                           var103.staticClip = std::make_shared<StaticAnimation>(var103);
                        }

                        var5.clips.put(var11, var103);
                  }
               }
            }
         }

         if (!var2 && var4 != nullptr) {
            try {
               int[] var70 = new int[var5.boneIndices.size()];
    std::vector var82 = var5.SkeletonHierarchy;
    std::unordered_map var91 = var5.boneIndices;
    std::unordered_map var100 = new std::unordered_map(var4.BoneIndices);
    std::vector var106 = new std::vector(var4.SkeletonHierarchy);
               var91.forEach((var4x, var5x) -> {
    int var6x = var100.getOrDefault(var4x, -1);
                  if (var6x == -1) {
                     var6x = var100.size();
                     var100.put(var4x, var6x);
    int var7x = (int)var82.get(var5x);
                     if (var7x >= 0) {
                        var106.push_back(var70[var7x]);
                     } else {
    uint8_t var8x = -2;
                     }
                  }

                  var70[var5x] = var6x;
               });
               var5.boneIndices = var100;
               var5.SkeletonHierarchy = var106;

               for (int var83 = 0; var83 < var5.vertices.m_numVertices; var83++) {
    int var92 = (int)var5.vertices.getElementFloat(var83, 5, 0);
    int var101 = (int)var5.vertices.getElementFloat(var83, 5, 1);
    int var107 = (int)var5.vertices.getElementFloat(var83, 5, 2);
    int var110 = (int)var5.vertices.getElementFloat(var83, 5, 3);
                  if (var92 >= 0) {
                     var92 = var70[var92];
                  }

                  if (var101 >= 0) {
                     var101 = var70[var101];
                  }

                  if (var107 >= 0) {
                     var107 = var70[var107];
                  }

                  if (var110 >= 0) {
                     var110 = var70[var110];
                  }

                  var5.vertices.setElement(var83, 5, var92, var101, var107, var110);
               }

               for (AnimationClip var93 : var5.clips.values()) {
                  for (Keyframe var113 : var93.getKeyframes()) {
                     var113.Bone = var70[var113.Bone];
                  }
               }

               var5.skinOffsetMatrices = this.RemapMatrices(var70, var5.skinOffsetMatrices, var5.boneIndices.size());
               var5.bindPose = this.RemapMatrices(var70, var5.bindPose, var5.boneIndices.size());
               var5.invBindPose = this.RemapMatrices(var70, var5.invBindPose, var5.boneIndices.size());
            } catch (Exception var41) {
               var41;
            }
         }
      }

    return var5;
   }

    void applyToMesh(ModelTxt var1, ModelMesh var2, SkinningData var3) {
      if (var1.bStatic) {
         if (!ModelManager.NoOpenGL) {
            var2.m_bHasVBO = true;
            RenderThread.queueInvokeOnRenderContext(() -> {
               var2.SetVertexBuffer(std::make_shared<VertexBufferObject>(var1.vertices, var1.elements));
               if (ModelManager.instance.bCreateSoftwareMeshes) {
                  var2.softwareMesh.vb = var2.vb;
               }
            });
         }
      } else {
         var2.skinningData = std::make_shared<SkinningData>(var1.clips, var1.bindPose, var1.invBindPose, var1.skinOffsetMatrices, var1.SkeletonHierarchy, var1.boneIndices);
         if (!ModelManager.NoOpenGL) {
            var2.m_bHasVBO = true;
            RenderThread.queueInvokeOnRenderContext(() -> {
               var2.SetVertexBuffer(std::make_shared<VertexBufferObject>(var1.vertices, var1.elements, var1.bReverse));
               if (ModelManager.instance.bCreateSoftwareMeshes) {
               }
            });
         }
      }

      if (var3 != nullptr) {
         var2.skinningData.AnimationClips = var3.AnimationClips;
      }
   }

    void applyToAnimation(ModelTxt var1, AnimationAsset var2) {
      var2.AnimationClips = var1.clips;
      var2.assetParams.animationsMesh.skinningData.AnimationClips.putAll(var1.clips);
   }

   private std::vector<Matrix4f> RemapMatrices(int[] var1, std::vector<Matrix4f> var2, int var3) {
    std::vector var4 = new std::vector(var3);
    Matrix4f var5 = std::make_shared<Matrix4f>();

      for (int var6 = 0; var6 < var3; var6++) {
         var4.push_back(var5);
      }

      for (int var7 = 0; var7 < var1.length; var7++) {
         var4.set(var1[var7], (Matrix4f)var2.get(var7));
      }

    return var4;
   }

    Vector3f getVector(const std::string& var1) {
    Vector3f var2 = std::make_shared<Vector3f>();
      std::string[] var3 = var1.split(",");
      var2.x = float.parseFloat(var3[0]);
      var2.y = float.parseFloat(var3[1]);
      var2.z = float.parseFloat(var3[2]);
    return var2;
   }

    Quaternion getQuaternion(const std::string& var1) {
    Quaternion var2 = std::make_shared<Quaternion>();
      std::string[] var3 = var1.split(",");
      var2.x = float.parseFloat(var3[0]);
      var2.y = float.parseFloat(var3[1]);
      var2.z = float.parseFloat(var3[2]);
      var2.w = float.parseFloat(var3[3]);
    return var2;
   }

    Matrix4f getMatrix(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    Matrix4f var5 = std::make_shared<Matrix4f>();
    bool var6 = false;
      std::string[] var7 = var1.split(",");
      var5.m00 = float.parseFloat(var7[0]);
      var5.m01 = float.parseFloat(var7[1]);
      var5.m02 = float.parseFloat(var7[2]);
      var5.m03 = float.parseFloat(var7[3]);
      var7 = var2.split(",");
      var5.m10 = float.parseFloat(var7[0]);
      var5.m11 = float.parseFloat(var7[1]);
      var5.m12 = float.parseFloat(var7[2]);
      var5.m13 = float.parseFloat(var7[3]);
      var7 = var3.split(",");
      var5.m20 = float.parseFloat(var7[0]);
      var5.m21 = float.parseFloat(var7[1]);
      var5.m22 = float.parseFloat(var7[2]);
      var5.m23 = float.parseFloat(var7[3]);
      var7 = var4.split(",");
      var5.m30 = float.parseFloat(var7[0]);
      var5.m31 = float.parseFloat(var7[1]);
      var5.m32 = float.parseFloat(var7[2]);
      var5.m33 = float.parseFloat(var7[3]);
    return var5;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
