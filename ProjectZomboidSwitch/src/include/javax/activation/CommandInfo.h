#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/activation/CommandInfo/Beans.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class CommandInfo {
public:
    std::string verb;
    std::string className;

    public CommandInfo(const std::string& verb, const std::string& className) {
      this.verb = verb;
      this.className = className;
   }

    std::string getCommandName() {
      return this.verb;
   }

    std::string getCommandClass() {
      return this.className;
   }

    void* getCommandObject(DataHandler dh, ClassLoader loader) {
    void* new_bean = nullptr;
      new_bean = Beans.instantiate(loader, this.className);
      if (new_bean != nullptr) {
         if (dynamic_cast<CommandObject*>(new_bean) != nullptr) {
            ((CommandObject)new_bean).setCommandContext(this.verb, dh);
         } else if (dynamic_cast<Externalizable*>(new_bean) != nullptr && dh != nullptr) {
    InputStream is = dh.getInputStream();
            if (is != nullptr) {
               ((Externalizable)new_bean).readExternal(std::make_shared<ObjectInputStream>(is));
            }
         }
      }

    return new_bean;
   }
}
} // namespace activation
} // namespace javax
