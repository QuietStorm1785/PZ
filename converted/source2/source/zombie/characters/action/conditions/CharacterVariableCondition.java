package zombie.characters.action.conditions;

import org.w3c.dom.Element;
import zombie.characters.action.ActionContext;
import zombie.characters.action.IActionCondition;
import zombie.characters.action.conditions.CharacterVariableCondition.1;
import zombie.characters.action.conditions.CharacterVariableCondition.CharacterVariableLookup;
import zombie.characters.action.conditions.CharacterVariableCondition.Operator;
import zombie.core.skinnedmodel.advancedanimation.IAnimatable;
import zombie.core.skinnedmodel.advancedanimation.IAnimationVariableSource;
import zombie.util.StringUtils;

public final class CharacterVariableCondition implements IActionCondition {
   private Operator op;
   private Object lhsValue;
   private Object rhsValue;

   private static Object parseValue(String var0, boolean var1) {
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
                  return new CharacterVariableLookup(var0);
               } else {
                  StringBuilder var3 = new StringBuilder(var0.length() - 2);

                  for (int var4 = 1; var4 < var0.length(); var4++) {
                     char var5 = var0.charAt(var4);
                     switch (var5) {
                        case '"':
                        case '\'':
                           if (var5 == var2) {
                              return var3.toString();
                           }
                        default:
                           var3.append(var5);
                           break;
                        case '\\':
                           var3.append(var0.charAt(var4));
                     }
                  }

                  return var3.toString();
               }
            } else {
               return var0;
            }
         } else {
            return false;
         }
      }
   }

   private boolean load(Element var1) {
      String var2 = var1.getNodeName();
      switch (var2) {
         case "isTrue":
            this.op = Operator.Equal;
            this.lhsValue = new CharacterVariableLookup(var1.getTextContent().trim());
            this.rhsValue = true;
            return true;
         case "isFalse":
            this.op = Operator.Equal;
            this.lhsValue = new CharacterVariableLookup(var1.getTextContent().trim());
            this.rhsValue = false;
            return true;
         case "compare":
            String var4 = var1.getAttribute("op").trim();
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

   private void loadCompareValues(Element var1) {
      String var2 = var1.getAttribute("a").trim();
      String var3 = var1.getAttribute("b").trim();
      this.lhsValue = parseValue(var2, true);
      this.rhsValue = parseValue(var3, false);
   }

   private static Object resolveValue(Object var0, IAnimationVariableSource var1) {
      if (var0 instanceof CharacterVariableLookup) {
         String var2 = var1.getVariableString(((CharacterVariableLookup)var0).variableName);
         return var2 != null ? parseValue(var2, false) : null;
      } else {
         return var0;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private boolean resolveCompareTo(int var1) {
      switch (1.$SwitchMap$zombie$characters$action$conditions$CharacterVariableCondition$Operator[this.op.ordinal()]) {
         case 1:
            return var1 == 0;
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

   public boolean passes(ActionContext var1, int var2) {
      IAnimatable var3 = var1.getOwner();
      Object var4 = resolveValue(this.lhsValue, var3);
      Object var5 = resolveValue(this.rhsValue, var3);
      if (var4 == null && var5 instanceof String && StringUtils.isNullOrEmpty((String)var5)) {
         if (this.op == Operator.Equal) {
            return true;
         }

         if (this.op == Operator.NotEqual) {
            return false;
         }

         boolean var6 = true;
      }

      if (var4 != null && var5 != null) {
         if (var4.getClass().equals(var5.getClass())) {
            if (var4 instanceof String) {
               return this.resolveCompareTo(((String)var4).compareTo((String)var5));
            }

            if (var4 instanceof Integer) {
               return this.resolveCompareTo(((Integer)var4).compareTo((Integer)var5));
            }

            if (var4 instanceof Float) {
               return this.resolveCompareTo(((Float)var4).compareTo((Float)var5));
            }

            if (var4 instanceof Boolean) {
               return this.resolveCompareTo(((Boolean)var4).compareTo((Boolean)var5));
            }
         }

         boolean var14 = var4 instanceof Integer;
         boolean var7 = var4 instanceof Float;
         boolean var8 = var5 instanceof Integer;
         boolean var9 = var5 instanceof Float;
         if ((var14 || var7) && (var8 || var9)) {
            boolean var10 = this.lhsValue instanceof CharacterVariableLookup;
            boolean var11 = this.rhsValue instanceof CharacterVariableLookup;
            if (var10 == var11) {
               float var18 = var7 ? (Float)var4 : ((Integer)var4).intValue();
               float var22 = var9 ? (Float)var5 : ((Integer)var5).intValue();
               return this.resolveCompareTo(Float.compare(var18, var22));
            } else if (var10) {
               if (var9) {
                  float var17 = var7 ? (Float)var4 : ((Integer)var4).intValue();
                  float var21 = (Float)var5;
                  return this.resolveCompareTo(Float.compare(var17, var21));
               } else {
                  int var16 = var7 ? (int)((Float)var4).floatValue() : (Integer)var4;
                  int var20 = (Integer)var5;
                  return this.resolveCompareTo(Integer.compare(var16, var20));
               }
            } else if (var7) {
               float var15 = (Float)var4;
               float var19 = var9 ? (Float)var5 : ((Integer)var5).intValue();
               return this.resolveCompareTo(Float.compare(var15, var19));
            } else {
               int var12 = (Integer)var4;
               int var13 = var9 ? (int)((Float)var5).floatValue() : (Integer)var5;
               return this.resolveCompareTo(Integer.compare(var12, var13));
            }
         } else {
            return false;
         }
      } else {
         return false;
      }
   }

   public IActionCondition clone() {
      return this;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private static String getOpString(Operator var0) {
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

   private static String valueToString(Object var0) {
      return var0 instanceof String ? "\"" + (String)var0 + "\"" : var0.toString();
   }

   public String getDescription() {
      return valueToString(this.lhsValue) + getOpString(this.op) + valueToString(this.rhsValue);
   }
}
