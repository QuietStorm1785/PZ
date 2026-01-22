#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/Element.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner/IElementSpawner.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class VehicleStorySpawner {
public:
    static const VehicleStorySpawner instance = std::make_shared<VehicleStorySpawner>();
    static const Vector2 s_vector2_1 = std::make_shared<Vector2>();
    static const Vector2 s_vector2_2 = std::make_shared<Vector2>();
   private static const ObjectPool<Element> s_elementPool = std::make_shared<ObjectPool>(Element::new);
   private static const int[] s_AABB = new int[4];
   public const std::vector<Element> m_elements = std::make_unique<std::vector<>>();
   public const std::unordered_map<std::string, Object> m_storyParams = std::make_unique<std::unordered_map<>>();

    static VehicleStorySpawner getInstance() {
    return instance;
   }

    void clear() {
      s_elementPool.release(this.m_elements);
      this.m_elements.clear();
      this.m_storyParams.clear();
   }

    Element addElement(const std::string& var1, float var2, float var3, float var4, float var5, float var6) {
    Element var7 = ((Element)s_elementPool.alloc()).init(var1, var2, var3, var4, var5, var6);
      this.m_elements.push_back(var7);
    return var7;
   }

    void setParameter(const std::string& var1, bool var2) {
      this.m_storyParams.put(var1, var2 ? bool.TRUE : bool.FALSE);
   }

    void setParameter(const std::string& var1, float var2) {
      this.m_storyParams.put(var1, var2);
   }

    void setParameter(const std::string& var1, int var2) {
      this.m_storyParams.put(var1, var2);
   }

    void setParameter(const std::string& var1, void* var2) {
      this.m_storyParams.put(var1, var2);
   }

    bool getParameterBoolean(const std::string& var1) {
      return this.getParameter(var1, bool.class);
   }

    float getParameterFloat(const std::string& var1) {
      return this.getParameter(var1, float.class);
   }

    int getParameterInteger(const std::string& var1) {
      return this.getParameter(var1, int.class);
   }

    std::string getParameterString(const std::string& var1) {
      return this.getParameter(var1, std::string.class);
   }

   public <E> E getParameter(std::string var1, Class<E> var2) {
      return (E)Type.tryCastTo(this.m_storyParams.get(var1), var2);
   }

    void spawn(float var1, float var2, float var3, float var4, IElementSpawner var5) {
      for (int var6 = 0; var6 < this.m_elements.size(); var6++) {
    Element var7 = this.m_elements.get(var6);
    Vector2 var8 = s_vector2_1.setLengthAndDirection(var7.direction, 1.0F);
         var8.push_back(var7.position);
         this.rotate(var1, var2, var8, var4);
         this.rotate(var1, var2, var7.position, var4);
         var7.direction = Vector2.getDirection(var8.x - var7.position.x, var8.y - var7.position.y);
         var7.z = var3;
         var7.square = IsoWorld.instance.CurrentCell.getGridSquare(var7.position.x, var7.position.y, var3);
         var5.spawn(this, var7);
      }
   }

    Vector2 rotate(float var1, float var2, Vector2 var3, float var4) {
    float var5 = var3.x;
    float var6 = var3.y;
      var3.x = var1 + (float)(var5 * Math.cos(var4) - var6 * Math.sin(var4));
      var3.y = var2 + (float)(var5 * Math.sin(var4) + var6 * Math.cos(var4));
    return var3;
   }

    void getAABB(float var1, float var2, float var3, float var4, float var5, int[] var6) {
    Vector2 var7 = s_vector2_1.setLengthAndDirection(var5, 1.0F);
    Vector2 var8 = s_vector2_2.set(var7);
      var8.tangent();
      var7.x *= var4 / 2.0F;
      var7.y *= var4 / 2.0F;
      var8.x *= var3 / 2.0F;
      var8.y *= var3 / 2.0F;
    float var9 = var1 + var7.x;
    float var10 = var2 + var7.y;
    float var11 = var1 - var7.x;
    float var12 = var2 - var7.y;
    float var13 = var9 - var8.x;
    float var14 = var10 - var8.y;
    float var15 = var9 + var8.x;
    float var16 = var10 + var8.y;
    float var17 = var11 - var8.x;
    float var18 = var12 - var8.y;
    float var19 = var11 + var8.x;
    float var20 = var12 + var8.y;
    float var21 = PZMath.min(var13, PZMath.min(var15, PZMath.min(var17, var19)));
    float var22 = PZMath.max(var13, PZMath.max(var15, PZMath.max(var17, var19)));
    float var23 = PZMath.min(var14, PZMath.min(var16, PZMath.min(var18, var20)));
    float var24 = PZMath.max(var14, PZMath.max(var16, PZMath.max(var18, var20)));
      var6[0] = (int)PZMath.floor(var21);
      var6[1] = (int)PZMath.floor(var23);
      var6[2] = (int)PZMath.ceil(var22);
      var6[3] = (int)PZMath.ceil(var24);
   }

    void render(float var1, float var2, float var3, float var4, float var5, float var6) {
      LineDrawer.DrawIsoRectRotated(var1, var2, var3, var4, var5, var6, 0.0F, 0.0F, 1.0F, 1.0F);
    float var7 = 1.0F;
    float var8 = 1.0F;
    float var9 = 1.0F;
    float var10 = 1.0F;
    float var11 = float.MAX_VALUE;
    float var12 = float.MAX_VALUE;
    float var13 = -float.MAX_VALUE;
    float var14 = -float.MAX_VALUE;

      for (Element var16 : this.m_elements) {
    Vector2 var17 = s_vector2_1.setLengthAndDirection(var16.direction, 1.0F);
         LineDrawer.DrawIsoLine(
            var16.position.x, var16.position.y, var3, var16.position.x + var17.x, var16.position.y + var17.y, var3, var7, var8, var9, var10, 1
         );
         LineDrawer.DrawIsoRectRotated(var16.position.x, var16.position.y, var3, var16.width, var16.height, var16.direction, var7, var8, var9, var10);
         this.getAABB(var16.position.x, var16.position.y, var16.width, var16.height, var16.direction, s_AABB);
         var11 = PZMath.min(var11, s_AABB[0]);
         var12 = PZMath.min(var12, s_AABB[1]);
         var13 = PZMath.max(var13, s_AABB[2]);
         var14 = PZMath.max(var14, s_AABB[3]);
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
