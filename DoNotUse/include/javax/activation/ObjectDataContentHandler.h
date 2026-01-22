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


class ObjectDataContentHandler {
public:
   private DataFlavor[] transferFlavors = nullptr;
    void* obj;
    std::string mimeType;
    DataContentHandler dch = nullptr;

    public ObjectDataContentHandler(DataContentHandler dch, void* obj, const std::string& mimeType) {
      this.obj = obj;
      this.mimeType = mimeType;
      this.dch = dch;
   }

    DataContentHandler getDCH() {
      return this.dch;
   }

   public /* synchronized - TODO: add std::mutex */ DataFlavor[] getTransferDataFlavors() {
      if (this.transferFlavors == nullptr) {
         if (this.dch != nullptr) {
            this.transferFlavors = this.dch.getTransferDataFlavors();
         } else {
            this.transferFlavors = new DataFlavor[1];
            this.transferFlavors[0] = std::make_shared<ActivationDataFlavor>(this.obj.getClass(), this.mimeType, this.mimeType);
         }
      }

      return this.transferFlavors;
   }

    void* getTransferData(DataFlavor df, DataSource ds) {
      if (this.dch != nullptr) {
         return this.dch.getTransferData(df, ds);
      } else if (df == this.getTransferDataFlavors()[0])) {
         return this.obj;
      } else {
         throw UnsupportedFlavorException(df);
      }
   }

    void* getContent(DataSource ds) {
      return this.obj;
   }

    void writeTo(void* obj, const std::string& mimeType, OutputStream os) {
      if (this.dch != nullptr) {
         this.dch.writeTo(obj, mimeType, os);
      } else if (dynamic_cast<byte*>(obj) != nullptr[]) {
         os.write((byte[])obj);
      } else {
         if (!(dynamic_cast<std*>(obj) != nullptr::string)) {
            throw UnsupportedDataTypeException("no object DCH for MIME type " + this.mimeType);
         }

    OutputStreamWriter osw = std::make_shared<OutputStreamWriter>(os);
         osw.write((std::string)obj);
         osw.flush();
      }
   }
}
} // namespace activation
} // namespace javax
