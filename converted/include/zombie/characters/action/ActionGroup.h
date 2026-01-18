#pragma once
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ActionGroup {
public:
 private static Map<String, ActionGroup> actionGroupMap = std::make_unique<HashMap<>>();
 std::string initialState;
 private List<ActionState> states = std::make_unique<ArrayList<>>();
 private Map<String, ActionState> stateLookup;

 static ActionGroup getActionGroup(const std::string& name) {
 name = name.toLowerCase();
 ActionGroup actionGroup = actionGroupMap.get(name);
 if (actionGroup == nullptr && !actionGroupMap.containsKey(name) {
 actionGroup = std::make_unique<ActionGroup>();
 actionGroupMap.put(name, actionGroup);

 try {
 actionGroup.load(name);
 } catch (Exception exception) {
 DebugLog.ActionSystem.error("Error loading action group: " + name);
 exception.printStackTrace(DebugLog.ActionSystem);
 }

 return actionGroup;
 } else {
 return actionGroup;
 }
 }

 static void reloadAll() {
 for (Entry entry : actionGroupMap.entrySet()) {
 ActionGroup actionGroup = (ActionGroup)entry.getValue();

 for (ActionState actionState : actionGroup.states) {
 actionState.resetForReload();
 }

 actionGroup.load((String)entry.getKey());
 }
 }

 void load(const std::string& string0) {
 if (DebugLog.isEnabled(DebugType.ActionSystem) {
 DebugLog.ActionSystem.debugln("Loading ActionGroup: " + string0);
 }

 File file0 = ZomboidFileSystem.instance.getMediaFile("actiongroups/" + string0 + "/actionGroup.xml");
 if (file0.exists() && file0.canRead()) {
 this->loadGroupData(file0);
 }

 File file1 = ZomboidFileSystem.instance.getMediaFile("actiongroups/" + string0);
 File[] files = file1.listFiles();
 if (files != nullptr) {
 for (auto& file2 : files) if (file2.isDirectory()) {
 std::string string1 = file2.getPath();
 ActionState actionState = this->getOrCreate(file2.getName());
 actionState.load(string1);
 }
 }
 }
 }

 void loadGroupData(File file) {
 Document document;
 try {
 DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
 DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
 document = documentBuilder.parse(file);
 } catch (SAXException | IOException | ParserConfigurationException parserConfigurationException) {
 DebugLog.ActionSystem.error("Error loading: " + file.getPath());
 parserConfigurationException.printStackTrace(DebugLog.ActionSystem);
 return;
 }

 document.getDocumentElement().normalize();
 Element element0 = document.getDocumentElement();
 if (!element0.getNodeName() == "actiongroup")) {
 DebugLog.ActionSystem
 .error("Error loading: " + file.getPath() + ", expected root element '<actiongroup>', received '<" + element0.getNodeName() + ">'");
 } else {
 for (Node node0 = element0.getFirstChild(); node0 != nullptr; node0 = node0.getNextSibling()) {
 if (node0.getNodeName() == "inherit") && node0 instanceof Element) {
 std::string string0 = node0.getTextContent().trim();
 this->inherit(getActionGroup(string0);
 }
 }

 for (Node node1 = element0.getFirstChild(); node1 != nullptr; node1 = node1.getNextSibling()) {
 if (node1 instanceof Element element1) {
 std::string string1 = element1.getNodeName();
 switch (string1) {
 case "initial":
 this->initialState = element1.getTextContent().trim();
 case "inherit":
 break;
 default:
 DebugLog.ActionSystem.warn("Warning: Unknown element '<>' in '" + file.getPath() + "'");
 }
 }
 }
 }
 }

 void inherit(ActionGroup actionGroup0) {
 if (actionGroup0 != nullptr) {
 if (actionGroup0.initialState != nullptr) {
 this->initialState = actionGroup0.initialState;
 }

 for (ActionState actionState0 : actionGroup0.states) {
 ActionState actionState1 = this->getOrCreate(actionState0.name);

 for (ActionTransition actionTransition : actionState0.transitions) {
 actionState1.transitions.add(actionTransition.clone());
 actionState1.sortTransitions();
 }
 }
 }
 }

 void rebuildLookup() {
 std::unordered_map hashMap = new HashMap();

 for (ActionState actionState : this->states) {
 hashMap.put(actionState.name.toLowerCase(), actionState);
 }

 this->stateLookup = hashMap;
 }

 void addState(ActionState state) {
 this->states.add(state);
 this->stateLookup = nullptr;
 }

 ActionState get(const std::string& state) {
 if (this->stateLookup == nullptr) {
 this->rebuildLookup();
 }

 return this->stateLookup.get(state.toLowerCase());
 }

 ActionState getOrCreate(const std::string& string) {
 if (this->stateLookup == nullptr) {
 this->rebuildLookup();
 }

 string = string.toLowerCase();
 ActionState actionState = this->stateLookup.get(string);
 if (actionState == nullptr) {
 actionState = new ActionState(string);
 this->states.add(actionState);
 this->stateLookup.put(string, actionState);
 }

 return actionState;
 }

 ActionState getInitialState() {
 ActionState actionState = nullptr;
 if (this->initialState != nullptr) {
 actionState = this->get(this->initialState);
 }

 if (actionState == nullptr && this->states.size() > 0) {
 actionState = this->states.get(0);
 }

 return actionState;
 }

 ActionState getDefaultState() {
 return this->getInitialState();
 }
}
} // namespace action
} // namespace characters
} // namespace zombie
