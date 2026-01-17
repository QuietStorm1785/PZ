#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace action {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ActionTransition {
public:
  std::string transitionTo;
  bool asSubstate;
  bool transitionOut;
  bool forceParent;
  final List<IActionCondition> conditions = std::make_unique<ArrayList<>>();

  static bool parse(Element element, const std::string &string,
                    List<ActionTransition> list) {
    if (element.getNodeName() == "transitions")) {
        parseTransitions(element, string, list);
        return true;
      }
    else if (element.getNodeName() == "transition")) {
        parseTransition(element, list);
        return true;
      }
    else {
      return false;
    }
  }

  static void parseTransition(Element element, List<ActionTransition> list) {
    list.clear();
    ActionTransition actionTransition = new ActionTransition();
    if (actionTransition.load(element)) {
      list.add(actionTransition);
    }
  }

  static void parseTransitions(Element element, const std::string &string,
                               List<ActionTransition> list) {
    list.clear();
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, string, list,
        (elementx, stringx, listx)->{
          if (!elementx.getNodeName() == "transition")) {
              DebugLog.ActionSystem.warn("Warning: Unrecognised element '" +
                                         elementx.getNodeName() + "' in " +
                                         stringx);
            }
          else {
            ActionTransition actionTransition = new ActionTransition();
            if (actionTransition.load(elementx)) {
              listx.add(actionTransition);
            }
          }
        });
  }

  bool load(Element element) {
    try {
      PZXmlUtil.forEachElement(
          element, elementx->{
            try {
              std::string string = elementx.getNodeName();
              if ("transitionTo".equalsIgnoreCase(string)) {
                this.transitionTo = elementx.getTextContent();
              } else if ("transitionOut".equalsIgnoreCase(string)) {
                this.transitionOut =
                    StringUtils.tryParseBoolean(elementx.getTextContent());
              } else if ("forceParent".equalsIgnoreCase(string)) {
                this.forceParent =
                    StringUtils.tryParseBoolean(elementx.getTextContent());
              } else if ("asSubstate".equalsIgnoreCase(string)) {
                this.asSubstate =
                    StringUtils.tryParseBoolean(elementx.getTextContent());
              } else if ("conditions".equalsIgnoreCase(string)) {
                PZXmlUtil.forEachElement(
                    elementx, elementxx->{
                      IActionCondition iActionCondition =
                          IActionCondition.createInstance(elementxx);
                      if (iActionCondition != nullptr) {
                        this.conditions.add(iActionCondition);
                      }
                    });
              }
            } catch (Exception exceptionx) {
              DebugLog.ActionSystem.error("Error while parsing xml element: " +
                                          elementx.getNodeName());
              DebugLog.ActionSystem.error(exceptionx);
            }
          });
      return true;
    } catch (Exception exception) {
      DebugLog.ActionSystem.error(
          "Error while loading an ActionTransition element");
      DebugLog.ActionSystem.error(exception);
      return false;
    }
  }

  std::string getTransitionTo() { return this.transitionTo; }

  bool passes(ActionContext actionContext, int int1) {
    for (int int0 = 0; int0 < this.conditions.size(); int0++) {
      IActionCondition iActionCondition0 = this.conditions.get(int0);
      if (!iActionCondition0.passes(actionContext, int1)) {
        return false;
      }
    }

    if (Core.bDebug && GameClient.bClient &&
        (DebugOptions.instance.MultiplayerShowPlayerStatus.getValue() &&
             actionContext.getOwner()
             instanceof
         IsoPlayer && !((IsoPlayer)actionContext.getOwner()).isGodMod() ||
             DebugOptions.instance.MultiplayerShowZombieStatus.getValue() &&
                 actionContext.getOwner()
             instanceof IsoZombie)) {
      StringBuilder stringBuilder =
          new StringBuilder("Character ")
              .append(actionContext.getOwner().getClass().getSimpleName())
              .append(" ")
              .append("id=")
              .append(actionContext.getOwner().getOnlineID())
              .append(" transition to \"")
              .append(this.transitionTo)
              .append("\":");

      for (IActionCondition iActionCondition1 : this.conditions) {
        stringBuilder.append(" [")
            .append(iActionCondition1.getDescription())
            .append("]");
      }

      DebugLog.log(DebugType.ActionSystem, stringBuilder.toString());
    }

    return true;
  }

  ActionTransition clone() {
    ActionTransition actionTransition0 = new ActionTransition();
    actionTransition0.transitionTo = this.transitionTo;
    actionTransition0.asSubstate = this.asSubstate;
    actionTransition0.transitionOut = this.transitionOut;
    actionTransition0.forceParent = this.forceParent;

    for (IActionCondition iActionCondition : this.conditions) {
      actionTransition0.conditions.add(iActionCondition.clone());
    }

    return actionTransition0;
  }
}
} // namespace action
} // namespace characters
} // namespace zombie
