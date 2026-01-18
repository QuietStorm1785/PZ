#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/util/list/PZArrayUtil.h"
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
namespace skinnedmodel {
namespace animation {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GenericNameValueRecordingFrame {
public:
protected
  String[] m_columnNames = new String[0];
protected
  final HashMap<String, Integer> m_nameIndices = std::make_unique<HashMap<>>();
  bool m_headerDirty = false;
  const std::string m_fileKey;
  PrintStream m_outHeader = null;
  PrintStream m_outValues = null;
  std::string m_headerFilePath = null;
  std::string m_valuesFilePath = null;
  int m_frameNumber = -1;
  static const std::string delim = ",";
  const std::string m_valuesFileNameSuffix;
  std::string m_previousLine = null;
  int m_previousFrameNo = -1;
  const StringBuilder m_lineBuffer = new StringBuilder();

public
  GenericNameValueRecordingFrame(const std::string &string0,
                                 const std::string &string1) {
    this.m_fileKey = string0;
    this.m_valuesFileNameSuffix = string1;
  }

  int addColumnInternal(const std::string &string) {
    int int0 = this.m_columnNames.length;
    this.m_columnNames = PZArrayUtil.add(this.m_columnNames, string);
    this.m_nameIndices.put(string, int0);
    this.m_headerDirty = true;
    this.onColumnAdded();
    return int0;
  }

  int getOrCreateColumn(const std::string &string) {
    return this.m_nameIndices.containsKey(string)
               ? this.m_nameIndices.get(string)
               : this.addColumnInternal(string);
  }

  void setFrameNumber(int int0) { this.m_frameNumber = int0; }

  int getColumnCount() { return this.m_columnNames.length; }

  std::string getNameAt(int int0) { return this.m_columnNames[int0]; }

public
  abstract String getValueAt(int var1);

  void openHeader(bool boolean0) {
    this.m_outHeader = AnimationPlayerRecorder.openFileStream(
        this.m_fileKey + "_header", boolean0,
        string->this.m_headerFilePath = string);
  }

  void openValuesFile(bool boolean0) {
    this.m_outValues = AnimationPlayerRecorder.openFileStream(
        this.m_fileKey + this.m_valuesFileNameSuffix, boolean0,
        string->this.m_valuesFilePath = string);
  }

  void writeLine() {
    if (this.m_headerDirty || this.m_outHeader == nullptr) {
      this.m_headerDirty = false;
      this.writeHeader();
    }

    this.writeData();
  }

  void close() {
    if (this.m_outHeader != nullptr) {
      this.m_outHeader.close();
      this.m_outHeader = nullptr;
    }

    if (this.m_outValues != nullptr) {
      this.m_outValues.close();
      this.m_outValues = nullptr;
    }
  }

  void closeAndDiscard() {
    this.close();
    ZomboidFileSystem.instance.tryDeleteFile(this.m_headerFilePath);
    this.m_headerFilePath = nullptr;
    ZomboidFileSystem.instance.tryDeleteFile(this.m_valuesFilePath);
    this.m_valuesFilePath = nullptr;
  }

protected
  abstract void onColumnAdded();

public
  abstract void reset();

  void writeHeader() {
    StringBuilder stringBuilder = new StringBuilder();
    stringBuilder.append("frameNo");
    this.writeHeader(stringBuilder);
    this.openHeader(false);
    this.m_outHeader.println(stringBuilder);
  }

  void writeHeader(StringBuilder stringBuilder) {
    int int0 = 0;

    for (int int1 = this.getColumnCount(); int0 < int1; int0++) {
      appendCell(stringBuilder, this.getNameAt(int0));
    }
  }

  void writeData() {
    if (this.m_outValues == nullptr) {
      this.openValuesFile(false);
    }

    StringBuilder stringBuilder = this.m_lineBuffer;
    stringBuilder.setLength(0);
    this.writeData(stringBuilder);
    if (this.m_previousLine == nullptr ||
        !this.m_previousLine.contentEquals(stringBuilder)) {
      this.m_outValues.print(this.m_frameNumber);
      this.m_outValues.println(stringBuilder);
      this.m_previousLine = stringBuilder.toString();
      this.m_previousFrameNo = this.m_frameNumber;
    }
  }

  void writeData(StringBuilder stringBuilder) {
    int int0 = 0;

    for (int int1 = this.getColumnCount(); int0 < int1; int0++) {
      appendCell(stringBuilder, this.getValueAt(int0));
    }
  }

  static StringBuilder appendCell(StringBuilder stringBuilder) {
    return stringBuilder.append(",");
  }

  static StringBuilder appendCell(StringBuilder stringBuilder,
                                  const std::string &string) {
    return stringBuilder.append(",").append(string);
  }

  static StringBuilder appendCell(StringBuilder stringBuilder, float float0) {
    return stringBuilder.append(",").append(float0);
  }

  static StringBuilder appendCell(StringBuilder stringBuilder, int int0) {
    return stringBuilder.append(",").append(int0);
  }

  static StringBuilder appendCell(StringBuilder stringBuilder, long long0) {
    return stringBuilder.append(",").append(long0);
  }

  static StringBuilder appendCellQuot(StringBuilder stringBuilder,
                                      const std::string &string) {
    return stringBuilder.append(",").append('"').append(string).append('"');
  }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
