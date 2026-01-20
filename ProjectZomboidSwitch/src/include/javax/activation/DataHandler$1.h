#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class DataHandler {
public:
   DataHandler$1(DataHandler this$0, DataContentHandler var2, PipedOutputStream var3) {
      this.this$0 = this$0;
      this.val$fdch = var2;
      this.val$pos = var3;
   }

    void run() {
      try {
         this.val$fdch.writeTo(DataHandler.access$000(this.this$0), DataHandler.access$100(this.this$0), this.val$pos);
      } catch (IOException var10) {
      } finally {
         try {
            this.val$pos.close();
         } catch (IOException var9) {
         }
      }
   }
}
} // namespace activation
} // namespace javax
