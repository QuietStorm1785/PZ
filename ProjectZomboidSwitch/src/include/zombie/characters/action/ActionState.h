#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {
namespace action {


class ActionState {
public:
    const std::string name;
   public const std::vector<ActionTransition> transitions = std::make_unique<std::vector<>>();
   private std::string[] m_tags;
   private std::string[] m_childTags;
   private static const Comparator<ActionTransition> transitionComparator = (var0, var1) -> var1.conditions.size() - var0.conditions.size();

    public ActionState(const std::string& var1) {
      this.name = var1;
   }

    bool canHaveSubStates() {
      return !PZArrayUtil.isNullOrEmpty(this.m_childTags);
   }

    bool canBeSubstate() {
      return !PZArrayUtil.isNullOrEmpty(this.m_tags);
   }

    bool canHaveSubState(ActionState var1) {
    return canHaveSubState();
   }

    static bool canHaveSubState(ActionState var0, ActionState var1) {
      std::string[] var2 = var0.m_childTags;
      std::string[] var3 = var1.m_tags;
    return tagsOverlap();
   }

    static bool tagsOverlap(std::string[] var0, std::string[] var1) {
      if (PZArrayUtil.isNullOrEmpty(var0)) {
    return false;
      } else if (PZArrayUtil.isNullOrEmpty(var1)) {
    return false;
      } else {
    bool var2 = false;

         for (int var3 = 0; var3 < var0.length; var3++) {
    std::string var4 = var0[var3];

            for (int var5 = 0; var5 < var1.length; var5++) {
    std::string var6 = var1[var5];
               if (StringUtils.equalsIgnoreCase(var4, var6)) {
                  var2 = true;
                  break;
               }
            }
         }

    return var2;
      }
   }

    std::string getName() {
      return this.name;
   }

    void load(const std::string& var1) {
    File var2 = std::make_shared<File>(var1).getAbsoluteFile();
      File[] var3 = var2.listFiles((var0, var1x) -> var1x.toLowerCase().endsWith(".xml"));
      if (var3 != nullptr) {
    for (auto& var7 : var3)            this.parse(var7);
         }

         this.sortTransitions();
      }
   }

    void parse(File var1) {
    std::vector var2 = new std::vector();
    std::vector var3 = new std::vector();
    std::vector var4 = new std::vector();
    std::string var5 = var1.getPath();

      try {
    Element var6 = PZXmlUtil.parseXml(var5);
         if (ActionTransition.parse(var6, var5, var2)) {
            this.transitions.addAll(var2);
            if (DebugLog.isEnabled(DebugType.ActionSystem)) {
               DebugLog.ActionSystem.debugln("Loaded transitions from file: %s", var5);
            }

            return;
         }

         if (this.parseTags(var6, var3, var4)) {
            this.m_tags = (std::string[])PZArrayUtil.concat(this.m_tags, (std::string[])var3.toArray(new std::string[0]));
            this.m_childTags = (std::string[])PZArrayUtil.concat(this.m_childTags, (std::string[])var4.toArray(new std::string[0]));
            if (DebugLog.isEnabled(DebugType.ActionSystem)) {
               DebugLog.ActionSystem.debugln("Loaded tags from file: %s", var5);
            }

            return;
         }

         if (DebugLog.isEnabled(DebugType.ActionSystem)) {
            DebugLog.ActionSystem.warn("Unrecognized xml file. It does not appear to be a transition nor a tag(s). %s", new Object[]{var5});
         }
      } catch (Exception var7) {
         DebugLog.ActionSystem.error("Error loading: " + var5);
         DebugLog.ActionSystem.error(var7);
      }
   }

    bool parseTags(Element var1, std::vector<std::string> var2, std::vector<std::string> var3) {
      var2.clear();
      var3.clear();
      if (var1.getNodeName() == "tags")) {
         PZXmlUtil.forEachElement(var1, var1x -> {
            if (var1x.getNodeName() == "tag")) {
               var3.push_back(var1x.getTextContent());
            }
         });
    return true;
      } else if (var1.getNodeName() == "childTags")) {
         PZXmlUtil.forEachElement(var1, var1x -> {
            if (var1x.getNodeName() == "tag")) {
               var3.push_back(var1x.getTextContent());
            }
         });
    return true;
      } else {
    return false;
      }
   }

    void sortTransitions() {
      this.transitions.sort(transitionComparator);
   }

    void resetForReload() {
      this.transitions.clear();
      this.m_tags = nullptr;
      this.m_childTags = nullptr;
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
