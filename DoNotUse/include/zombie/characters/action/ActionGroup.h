#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/SAXException.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {
namespace action {


class ActionGroup {
public:
   private static const Map<std::string, ActionGroup> actionGroupMap = std::make_unique<std::unordered_map<>>();
    std::string initialState;
   private List<ActionState> states = std::make_unique<std::vector<>>();
   private Map<std::string, ActionState> stateLookup;

    static ActionGroup getActionGroup(const std::string& var0) {
      var0 = var0.toLowerCase();
    ActionGroup var1 = actionGroupMap.get(var0);
      if (var1 == nullptr && !actionGroupMap.containsKey(var0)) {
         var1 = std::make_unique<ActionGroup>();
         actionGroupMap.put(var0, var1);

         try {
            var1.load(var0);
         } catch (Exception var3) {
            DebugLog.ActionSystem.error("Error loading action group: " + var0);
            var3.printStackTrace(DebugLog.ActionSystem);
         }

    return var1;
      } else {
    return var1;
      }
   }

    static void reloadAll() {
      for (Entry var1 : actionGroupMap.entrySet()) {
    ActionGroup var2 = (ActionGroup)var1.getValue();

         for (ActionState var4 : var2.states) {
            var4.resetForReload();
         }

         var2.load((std::string)var1.getKey());
      }
   }

    void load(const std::string& var1) {
      if (DebugLog.isEnabled(DebugType.ActionSystem)) {
         DebugLog.ActionSystem.debugln("Loading ActionGroup: " + var1);
      }

    File var2 = ZomboidFileSystem.instance.getMediaFile("actiongroups/" + var1 + "/actionGroup.xml");
      if (var2.exists() && var2.canRead()) {
         this.loadGroupData(var2);
      }

    File var3 = ZomboidFileSystem.instance.getMediaFile("actiongroups/" + var1);
      File[] var4 = var3.listFiles();
      if (var4 != nullptr) {
    for (auto& var8 : var4)            if (var8.isDirectory()) {
    std::string var9 = var8.getPath();
    ActionState var10 = this.getOrCreate(var8.getName());
               var10.load(var9);
            }
         }
      }
   }

    void loadGroupData(File var1) {
    Document var2;
      try {
    DocumentBuilderFactory var3 = DocumentBuilderFactory.newInstance();
    DocumentBuilder var4 = var3.newDocumentBuilder();
         var2 = var4.parse(var1);
      } catch (SAXException | IOException | ParserConfigurationException var8) {
         DebugLog.ActionSystem.error("Error loading: " + var1.getPath());
         var8.printStackTrace(DebugLog.ActionSystem);
         return;
      }

      var2.getDocumentElement().normalize();
    Element var9 = var2.getDocumentElement();
      if (!var9.getNodeName() == "actiongroup")) {
         DebugLog.ActionSystem.error("Error loading: " + var1.getPath() + ", expected root element '<actiongroup>', received '<" + var9.getNodeName() + ">'");
      } else {
         for (Node var10 = var9.getFirstChild(); var10 != nullptr; var10 = var10.getNextSibling()) {
            if (var10.getNodeName() == "inherit") && dynamic_cast<Element*>(var10) != nullptr) {
    std::string var5 = var10.getTextContent().trim();
               this.inherit(getActionGroup(var5));
            }
         }

         for (Node var11 = var9.getFirstChild(); var11 != nullptr; var11 = var11.getNextSibling()) {
            if (dynamic_cast<Element*>(var11) != nullptr var12) {
    std::string var6 = var12.getNodeName();
               switch (var6) {
                  case "initial":
                     this.initialState = var12.getTextContent().trim();
                  case "inherit":
                     break;
                  default:
                     DebugLog.ActionSystem.warn("Warning: Unknown element '<>' in '" + var1.getPath() + "'");
               }
            }
         }
      }
   }

    void inherit(ActionGroup var1) {
      if (var1 != nullptr) {
         if (var1.initialState != nullptr) {
            this.initialState = var1.initialState;
         }

         for (ActionState var3 : var1.states) {
    ActionState var4 = this.getOrCreate(var3.name);

            for (ActionTransition var6 : var3.transitions) {
               var4.transitions.push_back(var6.clone());
               var4.sortTransitions();
            }
         }
      }
   }

    void rebuildLookup() {
    std::unordered_map var1 = new std::unordered_map();

      for (ActionState var3 : this.states) {
         var1.put(var3.name.toLowerCase(), var3);
      }

      this.stateLookup = var1;
   }

    void addState(ActionState var1) {
      this.states.push_back(var1);
      this.stateLookup = nullptr;
   }

    ActionState get(const std::string& var1) {
      if (this.stateLookup == nullptr) {
         this.rebuildLookup();
      }

      return this.stateLookup.get(var1.toLowerCase());
   }

    ActionState getOrCreate(const std::string& var1) {
      if (this.stateLookup == nullptr) {
         this.rebuildLookup();
      }

      var1 = var1.toLowerCase();
    ActionState var2 = this.stateLookup.get(var1);
      if (var2 == nullptr) {
         var2 = std::make_shared<ActionState>(var1);
         this.states.push_back(var2);
         this.stateLookup.put(var1, var2);
      }

    return var2;
   }

    ActionState getInitialState() {
    ActionState var1 = nullptr;
      if (this.initialState != nullptr) {
         var1 = this.get(this.initialState);
      }

      if (var1 == nullptr && this.states.size() > 0) {
         var1 = this.states.get(0);
      }

    return var1;
   }

    ActionState getDefaultState() {
      return this.getInitialState();
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
