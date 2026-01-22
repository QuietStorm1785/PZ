#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class UnmarshallingContext {
public:
    Loader loader;
    Receiver receiver;
    Intercepter intercepter;
    void* target;
    void* backup;
    int numNsDecl;
    std::string elementDefaultValue;
   private UnmarshallingContext$State prev;
   private UnmarshallingContext$State next;
    bool nil;
    bool mixed;

    UnmarshallingContext getContext() {
      return this.this$0;
   }

   private UnmarshallingContext$State(UnmarshallingContext this$0, UnmarshallingContext$State prev) {
      this.this$0 = this$0;
      this.nil = false;
      this.mixed = false;
      this.prev = prev;
      if (prev != nullptr) {
         prev.next = this;
         if (prev.mixed) {
            this.mixed = true;
         }
      }
   }

    void push() {
      if (UnmarshallingContext.access$000().isLoggable(Level.FINEST)) {
         UnmarshallingContext.access$000().log(Level.FINEST, "State.push");
      }

      if (this.next == nullptr) {
         if (!$assertionsDisabled && UnmarshallingContext.access$100(this.this$0) != this) {
            throw std::make_unique<AssertionError>();
         }

         this.next = new UnmarshallingContext$State(this.this$0, this);
      }

      this.nil = false;
      UnmarshallingContext$State n = this.next;
      n.numNsDecl = UnmarshallingContext.access$200(this.this$0);
      UnmarshallingContext.access$102(this.this$0, n);
   }

    void pop() {
      if (UnmarshallingContext.access$000().isLoggable(Level.FINEST)) {
         UnmarshallingContext.access$000().log(Level.FINEST, "State.pop");
      }

      if (!$assertionsDisabled && this.prev == nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
         this.loader = nullptr;
         this.nil = false;
         this.mixed = false;
         this.receiver = nullptr;
         this.intercepter = nullptr;
         this.elementDefaultValue = nullptr;
         this.target = nullptr;
         UnmarshallingContext.access$102(this.this$0, this.prev);
         this.next = nullptr;
      }
   }

    bool isMixed() {
      return this.mixed;
   }

    void* getTarget() {
      return this.target;
   }

    void setLoader(Loader loader) {
      if (dynamic_cast<StructureLoader*>(loader) != nullptr) {
         this.mixed = !((StructureLoader)loader).getBeanInfo().hasElementOnlyContentModel();
      }

      this.loader = loader;
   }

    void setReceiver(Receiver receiver) {
      this.receiver = receiver;
   }

   public UnmarshallingContext$State getPrev() {
      return this.prev;
   }

    void setIntercepter(Intercepter intercepter) {
      this.intercepter = intercepter;
   }

    void setBackup(void* backup) {
      this.backup = backup;
   }

    void setTarget(void* target) {
      this.target = target;
   }

    void* getBackup() {
      return this.backup;
   }

    bool isNil() {
      return this.nil;
   }

    void setNil(bool nil) {
      this.nil = nil;
   }

    Loader getLoader() {
      return this.loader;
   }

    std::string getElementDefaultValue() {
      return this.elementDefaultValue;
   }

    void setElementDefaultValue(const std::string& elementDefaultValue) {
      this.elementDefaultValue = elementDefaultValue;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
