#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {


class ProxyPrintStream : public PrintStream {
public:
    PrintStream fileStream = nullptr;
    PrintStream systemStream = nullptr;

    public ProxyPrintStream(PrintStream var1, PrintStream var2) {
      super(var1);
      this.systemStream = var1;
      this.fileStream = var2;
   }

    void print(const std::string& var1) {
      this.systemStream.print(var1);
      this.fileStream.print(var1);
      this.fileStream.flush();
   }

    void println(const std::string& var1) {
      this.systemStream.println(var1);
      this.fileStream.println(var1);
      this.fileStream.flush();
   }

    void println(void* var1) {
      this.systemStream.println(var1);
      this.fileStream.println(var1);
      this.fileStream.flush();
   }

    void write(byte[] var1, int var2, int var3) {
      this.systemStream.write(var1, var2, var3);
      this.fileStream.write(var1, var2, var3);
      this.fileStream.flush();
   }

    void flush() {
      this.systemStream.flush();
      this.fileStream.flush();
   }
}
} // namespace core
} // namespace zombie
