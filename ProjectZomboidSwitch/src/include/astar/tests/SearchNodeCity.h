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


class SearchNodeCity : public ASearchNode {
public:
    std::string name;
    SearchNodeCity parent;
    SearchNodeCity goal;
   private std::unordered_map<std::string, std::unordered_map<std::string, int>> adjacencyMatrix = std::make_unique<std::unordered_map<>>();

    public SearchNodeCity(const std::string& var1) {
      this.name = var1;
      this.fillAdjacencyMatrix();
   }

    void fillAdjacencyMatrix() {
    std::unordered_map var1 = new std::unordered_map();
      var1.put("Kaiserslautern", 70);
      var1.put("Karlsruhe", 145);
    std::unordered_map var2 = new std::unordered_map();
      var2.put("Frankfurt", 103);
      var2.put("Ludwigshafen", 53);
    std::unordered_map var3 = new std::unordered_map();
      var3.put("Heilbronn", 84);
    std::unordered_map var4 = new std::unordered_map();
      var4.put("WÃ¼rzburg", 116);
    std::unordered_map var5 = new std::unordered_map();
      var5.put("WÃ¼rzburg", 183);
    std::unordered_map var6 = new std::unordered_map();
      var6.put("WÃ¼rzburg", 102);
      this.adjacencyMatrix.put("SaarbrÃ¼cken", var1);
      this.adjacencyMatrix.put("Kaiserslautern", var2);
      this.adjacencyMatrix.put("Frankfurt", var4);
      this.adjacencyMatrix.put("Karlsruhe", var3);
      this.adjacencyMatrix.put("Ludwigshafen", var5);
      this.adjacencyMatrix.put("Heilbronn", var6);
   }

    double h() {
    std::string var1 = this.name;
      switch (var1) {
         case "SaarbrÃ¼cken":
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
         case "WÃ¼rzburg":
            return 0.0;
         default:
            return 0.0;
      }
   }

    double c(ISearchNode var1) {
      return this.adjacencyMatrix.get(this.name).get(this.castToSearchNodeCity(var1).getName()).intValue();
   }

    void getSuccessors(std::vector<ISearchNode> var1) {
      for (std::string var4 : this.adjacencyMatrix.get(this.name).keySet()) {
         var1.push_back(std::make_shared<SearchNodeCity>(var4));
      }
   }

   public std::vector<ISearchNode> getSuccessors() {
    std::vector var1 = new std::vector();

      for (std::string var4 : this.adjacencyMatrix.get(this.name).keySet()) {
         var1.push_back(std::make_shared<SearchNodeCity>(var4));
      }

    return var1;
   }

    SearchNodeCity getParent() {
      return this.parent;
   }

    void setParent(ISearchNode var1) {
      this.parent = this.castToSearchNodeCity(var1);
   }

    int keyCode() {
      return this.name.hashCode();
   }

    bool equals(void* var1) {
      return dynamic_cast<SearchNodeCity*>(var1) != nullptr var2 ? this.name == var2.getName() : false;
   }

    int hashCode() {
      return this.name.hashCode();
   }

    std::string getName() {
      return this.name;
   }

    SearchNodeCity castToSearchNodeCity(ISearchNode var1) {
      return (SearchNodeCity)var1;
   }

    std::string toString() {
      return this.name + ",f:" + this.f();
   }
}
} // namespace tests
} // namespace astar
