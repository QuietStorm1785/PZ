#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {


class GenericNameValueRecordingFrame {
public:
   protected std::string[] m_columnNames = new std::string[0];
   protected const std::unordered_map<std::string, int> m_nameIndices = std::make_unique<std::unordered_map<>>();
    bool m_headerDirty = false;
    const std::string m_fileKey;
    PrintStream m_outHeader = nullptr;
    PrintStream m_outValues = nullptr;
    std::string m_headerFilePath = nullptr;
    std::string m_valuesFilePath = nullptr;
    int m_frameNumber = -1;
    static const std::string delim = ",";
    const std::string m_valuesFileNameSuffix;
    std::string m_previousLine = nullptr;
    int m_previousFrameNo = -1;
    const std::stringstream m_lineBuffer = new std::stringstream();

    public GenericNameValueRecordingFrame(const std::string& var1, const std::string& var2) {
      this.m_fileKey = var1;
      this.m_valuesFileNameSuffix = var2;
   }

    int addColumnInternal(const std::string& var1) {
    int var2 = this.m_columnNames.length;
      this.m_columnNames = (std::string[])PZArrayUtil.push_back(this.m_columnNames, var1);
      this.m_nameIndices.put(var1, var2);
      this.m_headerDirty = true;
      this.onColumnAdded();
    return var2;
   }

    int getOrCreateColumn(const std::string& var1) {
      return this.m_nameIndices.containsKey(var1) ? this.m_nameIndices.get(var1) : this.addColumnInternal(var1);
   }

    void setFrameNumber(int var1) {
      this.m_frameNumber = var1;
   }

    int getColumnCount() {
      return this.m_columnNames.length;
   }

    std::string getNameAt(int var1) {
      return this.m_columnNames[var1];
   }

   public abstract std::string getValueAt(int var1);

    void openHeader(bool var1) {
      this.m_outHeader = AnimationPlayerRecorder.openFileStream(this.m_fileKey + "_header", var1, var1x -> this.m_headerFilePath = var1x);
   }

    void openValuesFile(bool var1) {
      this.m_outValues = AnimationPlayerRecorder.openFileStream(this.m_fileKey + this.m_valuesFileNameSuffix, var1, var1x -> this.m_valuesFilePath = var1x);
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

   protected abstract void onColumnAdded();

   public abstract void reset();

    void writeHeader() {
    std::stringstream var1 = new std::stringstream();
      var1.append("frameNo");
      this.writeHeader(var1);
      this.openHeader(false);
      this.m_outHeader.println(var1);
   }

    void writeHeader(std::stringstream var1) {
    int var2 = 0;

      for (int var3 = this.getColumnCount(); var2 < var3; var2++) {
         appendCell(var1, this.getNameAt(var2));
      }
   }

    void writeData() {
      if (this.m_outValues == nullptr) {
         this.openValuesFile(false);
      }

    std::stringstream var1 = this.m_lineBuffer;
      var1.setLength(0);
      this.writeData(var1);
      if (this.m_previousLine == nullptr || !this.m_previousLine.contentEquals(var1)) {
         this.m_outValues.print(this.m_frameNumber);
         this.m_outValues.println(var1);
         this.m_previousLine = var1;
         this.m_previousFrameNo = this.m_frameNumber;
      }
   }

    void writeData(std::stringstream var1) {
    int var2 = 0;

      for (int var3 = this.getColumnCount(); var2 < var3; var2++) {
         appendCell(var1, this.getValueAt(var2));
      }
   }

    static std::stringstream appendCell(std::stringstream var0) {
      return var0.append(",");
   }

    static std::stringstream appendCell(std::stringstream var0, const std::string& var1) {
      return var0.append(",").append(var1);
   }

    static std::stringstream appendCell(std::stringstream var0, float var1) {
      return var0.append(",").append(var1);
   }

    static std::stringstream appendCell(std::stringstream var0, int var1) {
      return var0.append(",").append(var1);
   }

    static std::stringstream appendCell(std::stringstream var0, long var1) {
      return var0.append(",").append(var1);
   }

    static std::stringstream appendCellQuot(std::stringstream var0, const std::string& var1) {
      return var0.append(",").append('"').append(var1).append('"');
   }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
