#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/CollisionManager/Contact.h"
#include "zombie/CollisionManager/PolygonCollisionResult.h"
#include "zombie/CollisionManager/l_ResolveContacts.h"
#include "zombie/CollisionManager/s_performance.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/ZombieFootstepManager.h"
#include "zombie/characters/ZombieThumpManager.h"
#include "zombie/characters/ZombieVocalsManager.h"
#include "zombie/core/collision/Polygon.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoPushableObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include <algorithm>

namespace zombie {


class CollisionManager {
:
    static Vector2 temp = new Vector2();
    static Vector2 axis = new Vector2();
    static Polygon polygonA = new Polygon();
    static Polygon polygonB = new Polygon();
    float minA = 0.0F;
    float minB = 0.0F;
    float maxA = 0.0F;
    float maxB = 0.0F;
    PolygonCollisionResult result = new PolygonCollisionResult(this);
    ArrayList<Contact> ContactMap = std::make_unique<ArrayList<>>();
   Long[] longArray = new Long[1000];
   Stack<Contact> contacts = std::make_unique<Stack<>>();
    static const CollisionManager instance = new CollisionManager();

    void ProjectPolygonA(Vector2 var1, Polygon var2) {
    float var3 = var1.dot((Vector2)var2.points.get(0));
      this.minA = var3;
      this.maxA = var3;

      for (int var4 = 0; var4 < var2.points.size(); var4++) {
         var3 = ((Vector2)var2.points.get(var4)).dot(var1);
         if (var3 < this.minA) {
            this.minA = var3;
         } else if (var3 > this.maxA) {
            this.maxA = var3;
         }
      }
   }

    void ProjectPolygonB(Vector2 var1, Polygon var2) {
    float var3 = var1.dot((Vector2)var2.points.get(0));
      this.minB = var3;
      this.maxB = var3;

      for (int var4 = 0; var4 < var2.points.size(); var4++) {
         var3 = ((Vector2)var2.points.get(var4)).dot(var1);
         if (var3 < this.minB) {
            this.minB = var3;
         } else if (var3 > this.maxB) {
            this.maxB = var3;
         }
      }
   }

    PolygonCollisionResult PolygonCollision(Vector2 var1) {
      this.result.Intersect = true;
      this.result.WillIntersect = true;
      this.result.MinimumTranslationVector.x = 0.0F;
      this.result.MinimumTranslationVector.y = 0.0F;
    int var2 = polygonA.edges.size();
    int var3 = polygonB.edges.size();
    float var4 = Float.POSITIVE_INFINITY;
    Vector2 var5 = new Vector2();

      for (int var7 = 0; var7 < var2 + var3; var7++) {
    Vector2 var6;
         if (var7 < var2) {
            var6 = (Vector2)polygonA.edges.get(var7);
         } else {
            var6 = (Vector2)polygonB.edges.get(var7 - var2);
         }

         axis.x = -var6.y;
         axis.y = var6.x;
         axis.normalize();
         this.minA = 0.0F;
         this.minB = 0.0F;
         this.maxA = 0.0F;
         this.maxB = 0.0F;
         this.ProjectPolygonA(axis, polygonA);
         this.ProjectPolygonB(axis, polygonB);
         if (this.IntervalDistance(this.minA, this.maxA, this.minB, this.maxB) > 0.0F) {
            this.result.Intersect = false;
         }

    float var8 = axis.dot(var1);
         if (var8 < 0.0F) {
            this.minA += var8;
         } else {
            this.maxA += var8;
         }

    float var9 = this.IntervalDistance(this.minA, this.maxA, this.minB, this.maxB);
         if (var9 > 0.0F) {
            this.result.WillIntersect = false;
         }

         if (!this.result.Intersect && !this.result.WillIntersect) {
            break;
         }

         var9 = Math.abs(var9);
         if (var9 < var4) {
            var4 = var9;
            var5.x = axis.x;
            var5.y = axis.y;
            temp.x = polygonA.Center().x - polygonB.Center().x;
            temp.y = polygonA.Center().y - polygonB.Center().y;
            if (temp.dot(var5) < 0.0F) {
               var5.x = -var5.x;
               var5.y = -var5.y;
            }
         }
      }

      if (this.result.WillIntersect) {
         this.result.MinimumTranslationVector.x = var5.x * var4;
         this.result.MinimumTranslationVector.y = var5.y * var4;
      }

      return this.result;
   }

    float IntervalDistance(float var1, float var2, float var3, float var4) {
      return var1 < var3 ? var3 - var2 : var1 - var4;
   }

    void initUpdate() {
      if (this.longArray[0] == nullptr) {
         for (int var1 = 0; var1 < this.longArray.length; var1++) {
            this.longArray[var1] = new Long(0L);
         }
      }

      for (int var2 = 0; var2 < this.ContactMap.size(); var2++) {
         this.ContactMap.get(var2).a = nullptr;
         this.ContactMap.get(var2).b = nullptr;
         this.contacts.push(this.ContactMap.get(var2));
      }

      this.ContactMap.clear();
   }

    void AddContact(IsoMovingObject var1, IsoMovingObject var2) {
      if (!(var1 instanceof IsoSurvivor) && !(var2 instanceof IsoSurvivor) || !(var1 instanceof IsoPushableObject) && !(var2 instanceof IsoPushableObject)) {
         if (var1.getID() < var2.getID()) {
            this.ContactMap.add(this.contact(var1, var2));
         }
      }
   }

    Contact contact(IsoMovingObject var1, IsoMovingObject var2) {
      if (this.contacts.isEmpty()) {
         for (int var3 = 0; var3 < 50; var3++) {
            this.contacts.push(new Contact(this, nullptr, nullptr));
         }
      }

    Contact var4 = this.contacts.pop();
      var4.a = var1;
      var4.b = var2;
    return var4;
   }

    void ResolveContacts() {
      s_performance.profile_ResolveContacts.invokeAndMeasure(this, CollisionManager::resolveContactsInternal);
   }

    void resolveContactsInternal() {
    Vector2 var1 = l_ResolveContacts.vel;
    Vector2 var2 = l_ResolveContacts.vel2;
    std::vector var3 = l_ResolveContacts.pushables;
    std::vector var4 = IsoWorld.instance.CurrentCell.getPushableObjectList();
    int var5 = var4.size();

      for (int var6 = 0; var6 < var5; var6++) {
    IsoPushableObject var7 = (IsoPushableObject)var4.get(var6);
         if (var7.getImpulsex() != 0.0F || var7.getImpulsey() != 0.0F) {
            if (var7.connectList != nullptr) {
               var3.add(var7);
            } else {
               var7.setNx(var7.getNx() + var7.getImpulsex());
               var7.setNy(var7.getNy() + var7.getImpulsey());
               var7.setImpulsex(var7.getNx() - var7.getX());
               var7.setImpulsey(var7.getNy() - var7.getY());
               var7.setNx(var7.getX());
               var7.setNy(var7.getY());
            }
         }
      }

    int var24 = var3.size();

      for (int var25 = 0; var25 < var24; var25++) {
    IsoPushableObject var8 = (IsoPushableObject)var3.get(var25);
    float var9 = 0.0F;
    float var10 = 0.0F;

         for (int var11 = 0; var11 < var8.connectList.size(); var11++) {
            var9 += ((IsoPushableObject)var8.connectList.get(var11)).getImpulsex();
            var10 += ((IsoPushableObject)var8.connectList.get(var11)).getImpulsey();
         }

         var9 /= var8.connectList.size();
         var10 /= var8.connectList.size();

         for (int var34 = 0; var34 < var8.connectList.size(); var34++) {
            ((IsoPushableObject)var8.connectList.get(var34)).setImpulsex(var9);
            ((IsoPushableObject)var8.connectList.get(var34)).setImpulsey(var10);
    int var12 = var3.indexOf(var8.connectList.get(var34));
            var3.remove(var8.connectList.get(var34));
            if (var12 <= var25) {
               var25--;
            }
         }

         if (var25 < 0) {
            var25 = 0;
         }
      }

      var3.clear();
    int var26 = this.ContactMap.size();

      for (int var27 = 0; var27 < var26; var27++) {
    Contact var30 = this.ContactMap.get(var27);
         if (!(Math.abs(var30.a.getZ() - var30.b.getZ()) > 0.3F)) {
            var1.x = var30.a.getNx() - var30.a.getX();
            var1.y = var30.a.getNy() - var30.a.getY();
            var2.x = var30.b.getNx() - var30.b.getX();
            var2.y = var30.b.getNy() - var30.b.getY();
            if (var1.x != 0.0F
               || var1.y != 0.0F
               || var2.x != 0.0F
               || var2.y != 0.0F
               || var30.a.getImpulsex() != 0.0F
               || var30.a.getImpulsey() != 0.0F
               || var30.b.getImpulsex() != 0.0F
               || var30.b.getImpulsey() != 0.0F) {
    float var33 = var30.a.getX() - var30.a.getWidth();
    float var35 = var30.a.getX() + var30.a.getWidth();
    float var36 = var30.a.getY() - var30.a.getWidth();
    float var13 = var30.a.getY() + var30.a.getWidth();
    float var14 = var30.b.getX() - var30.b.getWidth();
    float var15 = var30.b.getX() + var30.b.getWidth();
    float var16 = var30.b.getY() - var30.b.getWidth();
    float var17 = var30.b.getY() + var30.b.getWidth();
               polygonA.Set(var33, var36, var35, var13);
               polygonB.Set(var14, var16, var15, var17);
    PolygonCollisionResult var18 = this.PolygonCollision(var1);
               if (var18.WillIntersect) {
                  var30.a.collideWith(var30.b);
                  var30.b.collideWith(var30.a);
                  float var19 = 1.0F
                     - var30.a.getWeight(var18.MinimumTranslationVector.x, var18.MinimumTranslationVector.y)
                        / (
                           var30.a.getWeight(var18.MinimumTranslationVector.x, var18.MinimumTranslationVector.y)
                              + var30.b.getWeight(var18.MinimumTranslationVector.x, var18.MinimumTranslationVector.y)
                        );
                  if (var30.a instanceof IsoPushableObject && var30.b instanceof IsoSurvivor) {
                     ((IsoSurvivor)var30.b).bCollidedWithPushable = true;
                     ((IsoSurvivor)var30.b).collidePushable = (IsoPushableObject)var30.a;
                  } else if (var30.b instanceof IsoPushableObject && var30.a instanceof IsoSurvivor) {
                     ((IsoSurvivor)var30.a).bCollidedWithPushable = true;
                     ((IsoSurvivor)var30.a).collidePushable = (IsoPushableObject)var30.b;
                  }

                  if (var30.a instanceof IsoPushableObject) {
    std::vector var20 = ((IsoPushableObject)var30.a).connectList;
                     if (var20 != nullptr) {
    int var21 = var20.size();

                        for (int var22 = 0; var22 < var21; var22++) {
    IsoPushableObject var23 = (IsoPushableObject)var20.get(var22);
                           var23.setImpulsex(var23.getImpulsex() + var18.MinimumTranslationVector.x * var19);
                           var23.setImpulsey(var23.getImpulsey() + var18.MinimumTranslationVector.y * var19);
                        }
                     }
                  } else {
                     var30.a.setImpulsex(var30.a.getImpulsex() + var18.MinimumTranslationVector.x * var19);
                     var30.a.setImpulsey(var30.a.getImpulsey() + var18.MinimumTranslationVector.y * var19);
                  }

                  if (var30.b instanceof IsoPushableObject) {
    std::vector var37 = ((IsoPushableObject)var30.b).connectList;
                     if (var37 != nullptr) {
    int var38 = var37.size();

                        for (int var39 = 0; var39 < var38; var39++) {
    IsoPushableObject var40 = (IsoPushableObject)var37.get(var39);
                           var40.setImpulsex(var40.getImpulsex() - var18.MinimumTranslationVector.x * (1.0F - var19));
                           var40.setImpulsey(var40.getImpulsey() - var18.MinimumTranslationVector.y * (1.0F - var19));
                        }
                     }
                  } else {
                     var30.b.setImpulsex(var30.b.getImpulsex() - var18.MinimumTranslationVector.x * (1.0F - var19));
                     var30.b.setImpulsey(var30.b.getImpulsey() - var18.MinimumTranslationVector.y * (1.0F - var19));
                  }
               }
            }
         }
      }

    std::vector var28 = IsoWorld.instance.CurrentCell.getObjectList();
    int var31 = var28.size();
      MovingObjectUpdateScheduler.instance.postupdate();
      IsoMovingObject.treeSoundMgr.update();
      ZombieFootstepManager.instance.update();
      ZombieThumpManager.instance.update();
      ZombieVocalsManager.instance.update();
   }
}
} // namespace zombie
