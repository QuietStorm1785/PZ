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


class FileDataSource {
public:
    File _file = nullptr;
    FileTypeMap typeMap = nullptr;

    public FileDataSource(File file) {
      this._file = file;
   }

    public FileDataSource(const std::string& name) {
      this(std::make_shared<File>(name));
   }

    InputStream getInputStream() {
      return std::make_shared<FileInputStream>(this._file);
   }

    OutputStream getOutputStream() {
      return std::make_shared<FileOutputStream>(this._file);
   }

    std::string getContentType() {
      return this.typeMap == nullptr ? FileTypeMap.getDefaultFileTypeMap().getContentType(this._file) : this.typeMap.getContentType(this._file);
   }

    std::string getName() {
      return this._file.getName();
   }

    File getFile() {
      return this._file;
   }

    void setFileTypeMap(FileTypeMap map) {
      this.typeMap = map;
   }
}
} // namespace activation
} // namespace javax
