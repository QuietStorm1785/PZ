#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ASearchNode.h"
#include "astar/ISearchNode.h"

namespace astar {
namespace tests {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SearchNodeCity : public ASearchNode {
public:
 std::string name;
 SearchNodeCity parent;
 SearchNodeCity goal;
 private HashMap<String, HashMap<String, Integer>> adjacencyMatrix = std::make_unique<HashMap<>>();

 public SearchNodeCity(const std::string& string) {
 this->name = string;
 this->fillAdjacencyMatrix();
 }

 void fillAdjacencyMatrix() {
 std::unordered_map hashMap0 = new HashMap();
 hashMap0.put("Kaiserslautern", 70);
 hashMap0.put("Karlsruhe", 145);
 std::unordered_map hashMap1 = new HashMap();
 hashMap1.put("Frankfurt", 103);
 hashMap1.put("Ludwigshafen", 53);
 std::unordered_map hashMap2 = new HashMap();
 hashMap2.put("Heilbronn", 84);
 std::unordered_map hashMap3 = new HashMap();
 hashMap3.put("W\u00c3\u00bcrzburg", 116);
 std::unordered_map hashMap4 = new HashMap();
 hashMap4.put("W\u00c3\u00bcrzburg", 183);
 std::unordered_map hashMap5 = new HashMap();
 hashMap5.put("W\u00c3\u00bcrzburg", 102);
 this->adjacencyMatrix.put("Saarbr\u00c3\u00bccken", hashMap0);
 this->adjacencyMatrix.put("Kaiserslautern", hashMap1);
 this->adjacencyMatrix.put("Frankfurt", hashMap3);
 this->adjacencyMatrix.put("Karlsruhe", hashMap2);
 this->adjacencyMatrix.put("Ludwigshafen", hashMap4);
 this->adjacencyMatrix.put("Heilbronn", hashMap5);
 }

 double h() {
 std::string string = this->name;
 switch (string) {
 case "Saarbr\u00c3\u00bccken":
 return 222.0;
 case "Kaiserslautern":
 return 158.0;
 case "Karlsruhe":
 return 140.0;
 case "Frankfurt":
 return 96.0;
 case "Ludwigshafen":
 return 108.0;
 case "Heilbronn":
 return 87.0;
 case "W\u00c3\u00bcrzburg":
 return 0.0;
 default:
 return 0.0;
 }
 }

 double c(ISearchNode iSearchNode) {
 return this->adjacencyMatrix.get(this->name).get(this->castToSearchNodeCity(iSearchNode).getName()).intValue();
 }

 void getSuccessors(ArrayList<ISearchNode> arrayList) {
 for (String string : this->adjacencyMatrix.get(this->name).keySet()) {
 arrayList.add(new SearchNodeCity(string);
 }
 }

 public ArrayList<ISearchNode> getSuccessors() {
 std::vector arrayList = new ArrayList();

 for (String string : this->adjacencyMatrix.get(this->name).keySet()) {
 arrayList.add(new SearchNodeCity(string);
 }

 return arrayList;
 }

 SearchNodeCity getParent() {
 return this->parent;
 }

 void setParent(ISearchNode iSearchNode) {
 this->parent = this->castToSearchNodeCity(iSearchNode);
 }

 int keyCode() {
 return this->name.hashCode();
 }

 bool equals(void* object) {
 return object instanceof SearchNodeCity searchNodeCity0 ? this->name == searchNodeCity0.getName() : false;
 }

 int hashCode() {
 return this->name.hashCode();
 }

 std::string getName() {
 return this->name;
 }

 SearchNodeCity castToSearchNodeCity(ISearchNode iSearchNode) {
 return (SearchNodeCity)iSearchNode;
 }

 std::string toString() {
 return this->name + ",f:" + this->f();
 }
}
} // namespace tests
} // namespace astar
