#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/network/GameClient.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace characters {
namespace action {


class ActionTransition {
public:
    std::string transitionTo;
    bool asSubstate;
    bool transitionOut;
    bool forceParent;
   const List<IActionCondition> conditions = std::make_unique<std::vector<>>();

    static bool parse(Element var0, const std::string& var1, List<ActionTransition> var2) {
      if (var0.getNodeName() == "transitions")) {
         parseTransitions(var0, var1, var2);
    return true;
      } else if (var0.getNodeName() == "transition")) {
         parseTransition(var0, var2);
    return true;
      } else {
    return false;
      }
   }

    static void parseTransition(Element var0, List<ActionTransition> var1) {
      var1.clear();
    ActionTransition var2 = std::make_shared<ActionTransition>();
      if (var2.load(var0)) {
         var1.push_back(var2);
      }
   }

    static void parseTransitions(Element var0, const std::string& var1, List<ActionTransition> var2) {
      var2.clear();
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var0, var1, var2, (var0x, var1x, var2x) -> {
         if (!var0x.getNodeName() == "transition")) {
            DebugLog.ActionSystem.warn("Warning: Unrecognised element '" + var0x.getNodeName() + "' in " + var1x);
         } else {
    ActionTransition var3 = std::make_shared<ActionTransition>();
            if (var3.load(var0x)) {
               var2x.push_back(var3);
            }
         }
      });
   }

    bool load(Element var1) {
      try {
         PZXmlUtil.forEachElement(var1, var1x -> {
            try {
    std::string var2 = var1x.getNodeName();
               if ("transitionTo".equalsIgnoreCase(var2)) {
                  this.transitionTo = var1x.getTextContent();
               } else if ("transitionOut".equalsIgnoreCase(var2)) {
                  this.transitionOut = StringUtils.tryParseBoolean(var1x.getTextContent());
               } else if ("forceParent".equalsIgnoreCase(var2)) {
                  this.forceParent = StringUtils.tryParseBoolean(var1x.getTextContent());
               } else if ("asSubstate".equalsIgnoreCase(var2)) {
                  this.asSubstate = StringUtils.tryParseBoolean(var1x.getTextContent());
               } else if ("conditions".equalsIgnoreCase(var2)) {
                  PZXmlUtil.forEachElement(var1x, var1xx -> {
    IActionCondition var2x = IActionCondition.createInstance(var1xx);
                     if (var2x != nullptr) {
                        this.conditions.push_back(var2x);
                     }
                  });
               }
            } catch (Exception var3x) {
               DebugLog.ActionSystem.error("Error while parsing xml element: " + var1x.getNodeName());
               DebugLog.ActionSystem.error(var3x);
            }
         });
    return true;
      } catch (Exception var3) {
         DebugLog.ActionSystem.error("Error while loading an ActionTransition element");
         DebugLog.ActionSystem.error(var3);
    return false;
      }
   }

    std::string getTransitionTo() {
      return this.transitionTo;
   }

    bool passes(ActionContext var1, int var2) {
      for (int var3 = 0; var3 < this.conditions.size(); var3++) {
    IActionCondition var4 = this.conditions.get(var3);
         if (!var4.passes(var1, var2)) {
    return false;
         }
      }

      if (Core.bDebug
         && GameClient.bClient
         && (
            DebugOptions.instance.MultiplayerShowPlayerStatus.getValue() && var1.getOwner() instanceof IsoPlayer && !((IsoPlayer)var1.getOwner()).isGodMod()
               || DebugOptions.instance.MultiplayerShowZombieStatus.getValue() && var1.getOwner() instanceof IsoZombie
         )) {
         std::stringstream var6 = new std::stringstream("char ")
            .append(var1.getOwner().getClass().getSimpleName())
            .append(" ")
            .append("id=")
            .append(var1.getOwner().getOnlineID())
            .append(" transition to \"")
            .append(this.transitionTo)
            .append("\":");

         for (IActionCondition var5 : this.conditions) {
            var6.append(" [").append(var5.getDescription()).append("]");
         }

         DebugLog.log(DebugType.ActionSystem, var6);
      }

    return true;
   }

    ActionTransition clone() {
    ActionTransition var1 = std::make_shared<ActionTransition>();
      var1.transitionTo = this.transitionTo;
      var1.asSubstate = this.asSubstate;
      var1.transitionOut = this.transitionOut;
      var1.forceParent = this.forceParent;

      for (IActionCondition var3 : this.conditions) {
         var1.conditions.push_back(var3.clone());
      }

    return var1;
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
