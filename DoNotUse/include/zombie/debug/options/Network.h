#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/options/Network/Client.h"
#include "zombie/debug/options/Network/PublicServerUtil.h"
#include "zombie/debug/options/Network/Server.h"

namespace zombie {
namespace debug {
namespace options {


class Network : public OptionGroup {
public:
    const Client Client = std::make_shared<Client>(this, this.Group);
    const Server Server = std::make_shared<Server>(this, this.Group);
    const PublicServerUtil PublicServerUtil = std::make_shared<PublicServerUtil>(this, this.Group);

    public Network() {
      super("Network");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
