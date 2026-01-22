#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPartContacts/ContactNode.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace characters {
namespace BodyDamage {


class BodyPartContacts {
public:
    static const ContactNode root;
   private static const ContactNode[] nodes;

   public static BodyPartType[] getAllContacts(BodyPartType var0) {
      for (int var2 = 0; var2 < nodes.length; var2++) {
    ContactNode var1 = nodes[var2];
         if (var1.bodyPart == var0) {
            return var1.bodyPartAllContacts;
         }
      }

    return nullptr;
   }

   public static BodyPartType[] getChildren(BodyPartType var0) {
      for (int var2 = 0; var2 < nodes.length; var2++) {
    ContactNode var1 = nodes[var2];
         if (var1.bodyPart == var0) {
            return var1.bodyPartChildren;
         }
      }

    return nullptr;
   }

    static BodyPartType getParent(BodyPartType var0) {
      for (int var2 = 0; var2 < nodes.length; var2++) {
    ContactNode var1 = nodes[var2];
         if (var1.bodyPart == var0) {
            if (var1.depth == 0) {
               DebugLog.log("Warning, root node parent is always nullptr.");
            }

            return var1.bodyPartParent;
         }
      }

    return nullptr;
   }

    static int getNodeDepth(BodyPartType var0) {
      for (int var2 = 0; var2 < nodes.length; var2++) {
    ContactNode var1 = nodes[var2];
         if (var1.bodyPart == var0) {
            if (!var1.initialised) {
               DebugLog.log("Warning: attempting to get depth for non initialised node '" + var1.bodyPart + "'.");
            }

            return var1.depth;
         }
      }

      return -1;
   }

    static ContactNode getNodeForBodyPart(BodyPartType var0) {
      for (int var1 = 0; var1 < nodes.length; var1++) {
         if (nodes[var1].bodyPart == var0) {
            return nodes[var1];
         }
      }

    return nullptr;
   }

    static void initNodes(ContactNode var0, int var1, ContactNode var2) {
      var0.parent = var2;
      var0.depth = var1;
    std::vector var3 = new std::vector();
      if (var0.parent != nullptr) {
         var3.push_back(var0.parent);
      }

      if (var0.children != nullptr) {
         for (ContactNode var7 : var0.children) {
            var3.push_back(var7);
            initNodes(var7, var1 + 1, var0);
         }
      }

      var0.allContacts = new ContactNode[var3.size()];
      var3.toArray(var0.allContacts);
      var0.initialised = true;
   }

    static void postInit() {
    for (auto& var3 : nodes)         if (var3.parent != nullptr) {
            var3.bodyPartParent = var3.parent.bodyPart;
         }

         if (var3.children != nullptr && var3.children.length > 0) {
            var3.bodyPartChildren = new BodyPartType[var3.children.length];

            for (int var4 = 0; var4 < var3.children.length; var4++) {
               var3.bodyPartChildren[var4] = var3.children[var4].bodyPart;
            }
         } else {
            var3.bodyPartChildren = new BodyPartType[0];
         }

         if (var3.allContacts != nullptr && var3.allContacts.length > 0) {
            var3.bodyPartAllContacts = new BodyPartType[var3.allContacts.length];

            for (int var5 = 0; var5 < var3.allContacts.length; var5++) {
               var3.bodyPartAllContacts[var5] = var3.allContacts[var5].bodyPart;
            }
         } else {
            var3.bodyPartAllContacts = new BodyPartType[0];
         }

         if (!var3.initialised) {
            DebugLog.log("Warning: node for '" + var3.bodyPart + "' is not initialised!");
         }
      }
   }

   static {
    int var0 = BodyPartType.ToIndex(BodyPartType.MAX);
      nodes = new ContactNode[var0];

      for (int var1 = 0; var1 < var0; var1++) {
         nodes[var1] = std::make_shared<ContactNode>(BodyPartType.FromIndex(var1));
      }

      root = getNodeForBodyPart(BodyPartType.Torso_Upper);
      root.children = new ContactNode[]{
         getNodeForBodyPart(BodyPartType.Neck),
         getNodeForBodyPart(BodyPartType.Torso_Lower),
         getNodeForBodyPart(BodyPartType.UpperArm_L),
         getNodeForBodyPart(BodyPartType.UpperArm_R)
      };
    ContactNode var2 = getNodeForBodyPart(BodyPartType.Neck);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.Head)};
      var2 = getNodeForBodyPart(BodyPartType.UpperArm_L);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.ForeArm_L)};
      var2 = getNodeForBodyPart(BodyPartType.ForeArm_L);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.Hand_L)};
      var2 = getNodeForBodyPart(BodyPartType.UpperArm_R);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.ForeArm_R)};
      var2 = getNodeForBodyPart(BodyPartType.ForeArm_R);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.Hand_R)};
      var2 = getNodeForBodyPart(BodyPartType.Torso_Lower);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.Groin)};
      var2 = getNodeForBodyPart(BodyPartType.Groin);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.UpperLeg_L), getNodeForBodyPart(BodyPartType.UpperLeg_R)};
      var2 = getNodeForBodyPart(BodyPartType.UpperLeg_L);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.LowerLeg_L)};
      var2 = getNodeForBodyPart(BodyPartType.LowerLeg_L);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.Foot_L)};
      var2 = getNodeForBodyPart(BodyPartType.UpperLeg_R);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.LowerLeg_R)};
      var2 = getNodeForBodyPart(BodyPartType.LowerLeg_R);
      var2.children = new ContactNode[]{getNodeForBodyPart(BodyPartType.Foot_R)};
      initNodes(root, 0, nullptr);
      postInit();
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
