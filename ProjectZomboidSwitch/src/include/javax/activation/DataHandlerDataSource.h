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


class DataHandlerDataSource {
public:
    DataHandler dataHandler = nullptr;

    public DataHandlerDataSource(DataHandler dh) {
      this.dataHandler = dh;
   }

    InputStream getInputStream() {
      return this.dataHandler.getInputStream();
   }

    OutputStream getOutputStream() {
      return this.dataHandler.getOutputStream();
   }

    std::string getContentType() {
      return this.dataHandler.getContentType();
   }

    std::string getName() {
      return this.dataHandler.getName();
   }
}
} // namespace activation
} // namespace javax
