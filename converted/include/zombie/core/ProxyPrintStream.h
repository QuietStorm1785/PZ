#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ProxyPrintStream : public PrintStream {
public:
  PrintStream fileStream = null;
  PrintStream systemStream = null;

public
  ProxyPrintStream(PrintStream printStream0, PrintStream printStream1) {
    super(printStream0);
    this.systemStream = printStream0;
    this.fileStream = printStream1;
  }

  void print(const std::string &string) {
    this.systemStream.print(string);
    this.fileStream.print(string);
    this.fileStream.flush();
  }

  void println(const std::string &string) {
    this.systemStream.println(string);
    this.fileStream.println(string);
    this.fileStream.flush();
  }

  void println(void *object) {
    this.systemStream.println(object);
    this.fileStream.println(object);
    this.fileStream.flush();
  }

  void write(byte[] bytes, int int0, int int1) {
    this.systemStream.write(bytes, int0, int1);
    this.fileStream.write(bytes, int0, int1);
    this.fileStream.flush();
  }

  void flush() {
    this.systemStream.flush();
    this.fileStream.flush();
  }
}
} // namespace core
} // namespace zombie
