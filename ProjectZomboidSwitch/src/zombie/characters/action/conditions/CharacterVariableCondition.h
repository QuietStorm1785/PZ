#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/IActionCondition.h"
#include "zombie/characters/action/conditions/CharacterVariableCondition/1.h"
#include "zombie/characters/action/conditions/CharacterVariableCondition/CharacterVariableLookup.h"
#include "zombie/characters/action/conditions/CharacterVariableCondition/Operator.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimatable.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSource.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {


class CharacterVariableCondition {
public:
    Operator op;
    void* lhsValue;
    void* rhsValue;

    static void* parseValue(const std::string& var0, bool var1) {
      if (var0.length() <= 0) {
    return var0;
      } else {
    char var2 = var0.charAt(0);
         if (var2 == '-' || var2 == '+' || var2 >= '0' && var2 <= '9') {
    int var8 = 0;
            if (var2 >= '0' && var2 <= '9') {
               var8 = var2 - '0';
            }

    int var9;
            for (var9 = 1; var9 < var0.length(); var9++) {
    char var10 = var0.charAt(var9);
               if (var10 >= '0' && var10 <= '9') {
                  var8 = var8 * 10 + (var10 - '0');
               } else if (var10 != ',') {
                  if (var10 != '.') {
    return var0;
                  }

                  var9++;
                  break;
               }
            }

            if (var9 == var0.length()) {
    return var8;
            } else {
    float var11 = var8;

               for (float var6 = 10.0F; var9 < var0.length(); var9++) {
    char var7 = var0.charAt(var9);
                  if (var7 >= '0' && var7 <= '9') {
                     var11 += (var7 - '0') / var6;
                     var6 *= 10.0F;
                  } else if (var7 != ',') {
    return var0;
                  }
               }

               if (var2 == '-') {
                  var11 *= -1.0F;
               }

    return var11;
            }
         } else if (var0.equalsIgnoreCase("true") || var0.equalsIgnoreCase("yes")) {
    return true;
         } else if (!var0.equalsIgnoreCase("false") && !var0.equalsIgnoreCase("no")) {
            if (var1) {
               if (var2 != '\'' && var2 != '"') {
                  return std::make_shared<CharacterVariableLookup>(var0);
               } else {
    std::stringstream var3 = new std::stringstream(var0.length() - 2);

                  for (int var4 = 1; var4 < var0.length(); var4++) {
    char var5 = var0.charAt(var4);
                     switch (var5) {
                        case '"':
                        case '\'':
                           if (var5 == var2) {
                              return var3;
                           }
                        default:
                           var3.append(var5);
                           break;
                        case '\\':
                           var3.append(var0.charAt(var4));
                     }
                  }

                  return var3;
               }
            } else {
    return var0;
            }
         } else {
    return false;
         }
      }
   }

    bool load(Element var1) {
    std::string var2 = var1.getNodeName();
      switch (var2) {
         case "isTrue":
            this.op = Operator.Equal;
            this.lhsValue = std::make_shared<CharacterVariableLookup>(var1.getTextContent().trim());
            this.rhsValue = true;
    return true;
         case "isFalse":
            this.op = Operator.Equal;
            this.lhsValue = std::make_shared<CharacterVariableLookup>(var1.getTextContent().trim());
            this.rhsValue = false;
    return true;
         case "compare":
    std::string var4 = var1.getAttribute("op").trim();
            switch (var4) {
               case "=":
               case "==":
                  this.op = Operator.Equal;
                  break;
               case "!=":
               case "<>":
                  this.op = Operator.NotEqual;
                  break;
               case "<":
                  this.op = Operator.Less;
                  break;
               case ">":
                  this.op = Operator.Greater;
                  break;
               case "<=":
                  this.op = Operator.LessEqual;
                  break;
               case ">=":
                  this.op = Operator.GreaterEqual;
                  break;
               default:
    return false;
            }

            this.loadCompareValues(var1);
    return true;
         case "gtr":
            this.op = Operator.Greater;
            this.loadCompareValues(var1);
    return true;
         case "less":
            this.op = Operator.Less;
            this.loadCompareValues(var1);
    return true;
         case "equals":
            this.op = Operator.Equal;
            this.loadCompareValues(var1);
    return true;
         case "notEquals":
            this.op = Operator.NotEqual;
            this.loadCompareValues(var1);
    return true;
         case "lessEqual":
            this.op = Operator.LessEqual;
            this.loadCompareValues(var1);
    return true;
         case "gtrEqual":
            this.op = Operator.GreaterEqual;
            this.loadCompareValues(var1);
    return true;
         default:
    return false;
      }
   }

    void loadCompareValues(Element var1) {
    std::string var2 = var1.getAttribute("a").trim();
    std::string var3 = var1.getAttribute("b").trim();
      this.lhsValue = parseValue(var2, true);
      this.rhsValue = parseValue(var3, false);
   }

    static void* resolveValue(void* var0, IAnimationVariableSource var1) {
      if (dynamic_cast<CharacterVariableLookup*>(var0) != nullptr) {
    std::string var2 = var1.getVariableString(((CharacterVariableLookup)var0).variableName);
         return var2 != nullptr ? parseValue(var2, false) : nullptr;
      } else {
    return var0;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool resolveCompareTo(int var1) {
      switch (1.$SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[this.op.ordinal()]) {
         case 1:
    return var1 = = 0;
         case 2:
            return var1 != 0;
         case 3:
            return var1 < 0;
         case 4:
            return var1 <= 0;
         case 5:
            return var1 > 0;
         case 6:
            return var1 >= 0;
         default:
    return false;
      }
   }

    bool passes(ActionContext var1, int var2) {
    IAnimatable var3 = var1.getOwner();
    void* var4 = resolveValue(this.lhsValue, var3);
    void* var5 = resolveValue(this.rhsValue, var3);
      if (var4 == nullptr && dynamic_cast<std*>(var5) != nullptr::string && StringUtils.isNullOrEmpty((std::string)var5)) {
         if (this.op == Operator.Equal) {
    return true;
         }

         if (this.op == Operator.NotEqual) {
    return false;
         }

    bool var6 = true;
      }

      if (var4 != nullptr && var5 != nullptr) {
         if (var4.getClass() == var5.getClass())) {
            if (dynamic_cast<std*>(var4) != nullptr::string) {
               return this.resolveCompareTo(((std::string)var4).compareTo((std::string)var5));
            }

            if (dynamic_cast<int*>(var4) != nullptr) {
               return this.resolveCompareTo(((int)var4).compareTo((int)var5));
            }

            if (dynamic_cast<float*>(var4) != nullptr) {
               return this.resolveCompareTo(((float)var4).compareTo((float)var5));
            }

            if (dynamic_cast<bool*>(var4) != nullptr) {
               return this.resolveCompareTo(((bool)var4).compareTo((bool)var5));
            }
         }

    bool var14 = dynamic_cast<int*>(var4) != nullptr;
    bool var7 = dynamic_cast<float*>(var4) != nullptr;
    bool var8 = dynamic_cast<int*>(var5) != nullptr;
    bool var9 = dynamic_cast<float*>(var5) != nullptr;
         if ((var14 || var7) && (var8 || var9)) {
    bool var10 = this.dynamic_cast<CharacterVariableLookup*>(lhsValue) != nullptr;
    bool var11 = this.dynamic_cast<CharacterVariableLookup*>(rhsValue) != nullptr;
            if (var10 == var11) {
    float var18 = var7 ? (float)var4 : ((int)var4).intValue();
    float var22 = var9 ? (float)var5 : ((int)var5).intValue();
               return this.resolveCompareTo(float.compare(var18, var22));
            } else if (var10) {
               if (var9) {
    float var17 = var7 ? (float)var4 : ((int)var4).intValue();
    float var21 = (float)var5;
                  return this.resolveCompareTo(float.compare(var17, var21));
               } else {
    int var16 = var7 ? (int)((float)var4).floatValue() : (int)var4;
    int var20 = (int)var5;
                  return this.resolveCompareTo(int.compare(var16, var20));
               }
            } else if (var7) {
    float var15 = (float)var4;
    float var19 = var9 ? (float)var5 : ((int)var5).intValue();
               return this.resolveCompareTo(float.compare(var15, var19));
            } else {
    int var12 = (int)var4;
    int var13 = var9 ? (int)((float)var5).floatValue() : (int)var5;
               return this.resolveCompareTo(int.compare(var12, var13));
            }
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    IActionCondition clone() {
    return this;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static std::string getOpString(Operator var0) {
      switch (1.$SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[var0.ordinal()]) {
         case 1:
            return " == ";
         case 2:
            return " != ";
         case 3:
            return " < ";
         case 4:
            return " <= ";
         case 5:
            return " > ";
         case 6:
            return " >=";
         default:
            return " ?? ";
      }
   }

    static std::string valueToString(void* var0) {
      return dynamic_cast<std*>(var0) != nullptr::string ? "\"" + (std::string)var0 + "\"" : var0;
   }

    std::string getDescription() {
    return valueToString();
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
