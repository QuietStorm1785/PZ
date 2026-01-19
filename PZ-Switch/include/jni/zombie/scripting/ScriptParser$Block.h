#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser/BlockElement.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace scripting {


class ScriptParser {
:
    std::string type;
    std::string id;
    ArrayList<BlockElement> elements = std::make_unique<ArrayList<>>();
    ArrayList<Value> values = std::make_unique<ArrayList<>>();
    ArrayList<ScriptParser$Block> children = std::make_unique<ArrayList<>>();

    ScriptParser$Block asBlock() {
    return this;
   }

    Value asValue() {
    return nullptr;
   }

    bool isEmpty() {
      return this.elements.isEmpty();
   }

    void prettyPrint(int var1, StringBuilder var2, const std::string& var3) {
      for (int var4 = 0; var4 < var1; var4++) {
         var2.append('\t');
      }

      var2.append(this.type);
      if (this.id != nullptr) {
         var2.append(" ");
         var2.append(this.id);
      }

      var2.append(var3);

      for (int var5 = 0; var5 < var1; var5++) {
         var2.append('\t');
      }

      var2.append('{');
      var2.append(var3);
      this.prettyPrintElements(var1 + 1, var2, var3);

      for (int var6 = 0; var6 < var1; var6++) {
         var2.append('\t');
      }

      var2.append('}');
      var2.append(var3);
   }

    void prettyPrintElements(int var1, StringBuilder var2, const std::string& var3) {
    BlockElement var4 = nullptr;

      for (BlockElement var6 : this.elements) {
         if (var6.asBlock() != nullptr && var4 != nullptr) {
            var2.append(var3);
         }

         if (var6.asValue() != nullptr && var4 instanceof ScriptParser$Block) {
            var2.append(var3);
         }

         var6.prettyPrint(var1, var2, var3);
         var4 = var6;
      }
   }

    ScriptParser$Block addBlock(String var1, String var2) {
      ScriptParser$Block var3 = new ScriptParser$Block();
      var3.type = var1;
      var3.id = var2;
      this.elements.add(var3);
      this.children.add(var3);
    return var3;
   }

    ScriptParser$Block getBlock(String var1, String var2) {
      for (ScriptParser$Block var4 : this.children) {
         if (var4.type == var1) && (var4.id != nullptr && var4.id == var2) || var4.id == nullptr && var2 == nullptr)) {
    return var4;
         }
      }

    return nullptr;
   }

    Value getValue(const std::string& var1) {
      for (Value var3 : this.values) {
    int var4 = var3.string.indexOf(61);
         if (var4 > 0 && var3.getKey().trim() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    void setValue(const std::string& var1, const std::string& var2) {
    Value var3 = this.getValue(var1);
      if (var3 == nullptr) {
         this.addValue(var1, var2);
      } else {
         var3.string = var1 + " = " + var2;
      }
   }

    Value addValue(const std::string& var1, const std::string& var2) {
    Value var3 = new Value();
      var3.string = var1 + " = " + var2;
      this.elements.add(var3);
      this.values.add(var3);
    return var3;
   }

    void moveValueAfter(const std::string& var1, const std::string& var2) {
    Value var3 = this.getValue(var1);
    Value var4 = this.getValue(var2);
      if (var3 != nullptr && var4 != nullptr) {
         this.elements.remove(var3);
         this.values.remove(var3);
         this.elements.add(this.elements.indexOf(var4) + 1, var3);
         this.values.add(this.values.indexOf(var4) + 1, var3);
      }
   }
}
} // namespace scripting
} // namespace zombie
