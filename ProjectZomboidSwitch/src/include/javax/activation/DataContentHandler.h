#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/datatransfer/DataFlavor.h"
#include "java/awt/datatransfer/UnsupportedFlavorException.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class DataContentHandler {
public:
    virtual ~DataContentHandler() = default;
   DataFlavor[] getTransferDataFlavors();

    void* getTransferData(DataFlavor var1, DataSource var2);

    void* getContent(DataSource var1);

    void writeTo(void* var1, const std::string& var2, OutputStream var3);
}
} // namespace activation
} // namespace javax
