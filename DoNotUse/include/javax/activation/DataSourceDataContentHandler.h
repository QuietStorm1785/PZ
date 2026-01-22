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


class DataSourceDataContentHandler {
public:
    DataSource ds = nullptr;
   private DataFlavor[] transferFlavors = nullptr;
    DataContentHandler dch = nullptr;

    public DataSourceDataContentHandler(DataContentHandler dch, DataSource ds) {
      this.ds = ds;
      this.dch = dch;
   }

   public DataFlavor[] getTransferDataFlavors() {
      if (this.transferFlavors == nullptr) {
         if (this.dch != nullptr) {
            this.transferFlavors = this.dch.getTransferDataFlavors();
         } else {
            this.transferFlavors = new DataFlavor[1];
            this.transferFlavors[0] = std::make_shared<ActivationDataFlavor>(this.ds.getContentType(), this.ds.getContentType());
         }
      }

      return this.transferFlavors;
   }

    void* getTransferData(DataFlavor df, DataSource ds) {
      if (this.dch != nullptr) {
         return this.dch.getTransferData(df, ds);
      } else if (df == this.getTransferDataFlavors()[0])) {
         return ds.getInputStream();
      } else {
         throw UnsupportedFlavorException(df);
      }
   }

    void* getContent(DataSource ds) {
      return this.dch != nullptr ? this.dch.getContent(ds) : ds.getInputStream();
   }

    void writeTo(void* obj, const std::string& mimeType, OutputStream os) {
      if (this.dch != nullptr) {
         this.dch.writeTo(obj, mimeType, os);
      } else {
         throw UnsupportedDataTypeException("no DCH for content type " + this.ds.getContentType());
      }
   }
}
} // namespace activation
} // namespace javax
