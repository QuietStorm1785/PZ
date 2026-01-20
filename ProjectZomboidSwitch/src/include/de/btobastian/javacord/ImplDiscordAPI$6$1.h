#pragma once
#include <mutex>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI/6.h"
#include "de/btobastian/javacord/listener/user/UserChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
public:
   ImplDiscordAPI$6$1(ImplDiscordAPI$6& parent, const std::string& oldName)
      : parent_(parent), oldName_(oldName) {}

   void run() {
      static std::mutex mtx;
      std::lock_guard<std::mutex> lock(mtx);
      auto listeners = parent_.parent_.getListeners<UserChangeNameListener>();
      for (auto& listener : listeners) {
         listener->onUserChangeName(parent_.parent_, parent_.parent_.getYourself(), oldName_);
      }
   }
private:
   ImplDiscordAPI$6& parent_;
   std::string oldName_;
}
} // namespace javacord
} // namespace btobastian
} // namespace de
