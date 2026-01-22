#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace mashape {
namespace unirest {
namespace http {

// $VF: synthetic class
class HttpClientHelper {
public:
   static {
      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.GET.ordinal()] = 1;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.POST.ordinal()] = 2;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.PUT.ordinal()] = 3;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.DELETE.ordinal()] = 4;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.PATCH.ordinal()] = 5;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.OPTIONS.ordinal()] = 6;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$mashape$unirest$http$HttpMethod[HttpMethod.HEAD.ordinal()] = 7;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
