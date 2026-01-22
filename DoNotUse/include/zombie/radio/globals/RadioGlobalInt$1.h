#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {

// $VF: synthetic class
class RadioGlobalInt {
public:
   static {
      try {
         $SwitchMap$zombie$radio$globals$EditGlobalOps[EditGlobalOps.set.ordinal()] = 1;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$radio$globals$EditGlobalOps[EditGlobalOps.add.ordinal()] = 2;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$radio$globals$EditGlobalOps[EditGlobalOps.sub.ordinal()] = 3;
      } catch (NoSuchFieldError var7) {
      }

      $SwitchMap$zombie$radio$globals$CompareMethod = new int[CompareMethod.values().length];

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.equals.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.notequals.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.lessthan.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.morethan.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.lessthanorequals.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$radio$globals$CompareMethod[CompareMethod.morethanorequals.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace globals
} // namespace radio
} // namespace zombie
