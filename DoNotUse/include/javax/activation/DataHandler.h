#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/datatransfer/DataFlavor.h"
#include "java/awt/datatransfer/Transferable.h"
#include "java/awt/datatransfer/UnsupportedFlavorException.h"
#include "java/net/URL.h"
#include "javax/activation/DataHandler/1.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class DataHandler {
public:
    DataSource dataSource = nullptr;
    DataSource objDataSource = nullptr;
    void* object = nullptr;
    std::string objectMimeType = nullptr;
    CommandMap currentCommandMap = nullptr;
   private static const DataFlavor[] emptyFlavors = new DataFlavor[0];
   private DataFlavor[] transferFlavors = emptyFlavors;
    DataContentHandler dataContentHandler = nullptr;
    DataContentHandler factoryDCH = nullptr;
    static DataContentHandlerFactory factory = nullptr;
    DataContentHandlerFactory oldFactory = nullptr;
    std::string shortType = nullptr;

    public DataHandler(DataSource ds) {
      this.dataSource = ds;
      this.oldFactory = factory;
   }

    public DataHandler(void* obj, const std::string& mimeType) {
      this.object = obj;
      this.objectMimeType = mimeType;
      this.oldFactory = factory;
   }

    public DataHandler(URL url) {
      this.dataSource = std::make_shared<URLDataSource>(url);
      this.oldFactory = factory;
   }

   private /* synchronized - TODO: add std::mutex */ CommandMap getCommandMap() {
      return this.currentCommandMap != nullptr ? this.currentCommandMap : CommandMap.getDefaultCommandMap();
   }

    DataSource getDataSource() {
      if (this.dataSource == nullptr) {
         if (this.objDataSource == nullptr) {
            this.objDataSource = std::make_shared<DataHandlerDataSource>(this);
         }

         return this.objDataSource;
      } else {
         return this.dataSource;
      }
   }

    std::string getName() {
      return this.dataSource != nullptr ? this.dataSource.getName() : nullptr;
   }

    std::string getContentType() {
      return this.dataSource != nullptr ? this.dataSource.getContentType() : this.objectMimeType;
   }

    InputStream getInputStream() {
    InputStream ins = nullptr;
      if (this.dataSource != nullptr) {
         ins = this.dataSource.getInputStream();
      } else {
    DataContentHandler dch = this.getDataContentHandler();
         if (dch == nullptr) {
            throw UnsupportedDataTypeException("no DCH for MIME type " + this.getBaseType());
         }

         if (dynamic_cast<ObjectDataContentHandler*>(dch) != nullptr && ((ObjectDataContentHandler)dch).getDCH() == nullptr) {
            throw UnsupportedDataTypeException("no object DCH for MIME type " + this.getBaseType());
         }

    PipedOutputStream pos = std::make_shared<PipedOutputStream>();
    PipedInputStream pin = std::make_shared<PipedInputStream>(pos);
    std::make_shared<Thread>(std::make_shared<1>(this);
         ins = pin;
      }

    return ins;
   }

    void writeTo(OutputStream os) {
      if (this.dataSource != nullptr) {
    InputStream is = nullptr;
         byte[] data = new byte[8192];
         is = this.dataSource.getInputStream();

    int bytes_read;
         try {
            while ((bytes_read = is.read(data)) > 0) {
               os.write(data, 0, bytes_read);
            }
         } finally {
            is.close();
            is = nullptr;
         }
      } else {
    DataContentHandler dch = this.getDataContentHandler();
         dch.writeTo(this.object, this.objectMimeType, os);
      }
   }

    OutputStream getOutputStream() {
      return this.dataSource != nullptr ? this.dataSource.getOutputStream() : nullptr;
   }

   public /* synchronized - TODO: add std::mutex */ DataFlavor[] getTransferDataFlavors() {
      if (factory != this.oldFactory) {
         this.transferFlavors = emptyFlavors;
      }

      if (this.transferFlavors == emptyFlavors) {
         this.transferFlavors = this.getDataContentHandler().getTransferDataFlavors();
      }

      return this.transferFlavors == emptyFlavors ? this.transferFlavors : (DataFlavor[])this.transferFlavors.clone();
   }

    bool isDataFlavorSupported(DataFlavor flavor) {
      DataFlavor[] lFlavors = this.getTransferDataFlavors();

      for (int i = 0; i < lFlavors.length; i++) {
         if (lFlavors[i] == flavor)) {
    return true;
         }
      }

    return false;
   }

    void* getTransferData(DataFlavor flavor) {
      return this.getDataContentHandler().getTransferData(flavor, this.dataSource);
   }

   public /* synchronized - TODO: add std::mutex */ void setCommandMap(CommandMap commandMap) {
      if (commandMap != this.currentCommandMap || commandMap == nullptr) {
         this.transferFlavors = emptyFlavors;
         this.dataContentHandler = nullptr;
         this.currentCommandMap = commandMap;
      }
   }

   public CommandInfo[] getPreferredCommands() {
      return this.dataSource != nullptr
         ? this.getCommandMap().getPreferredCommands(this.getBaseType(), this.dataSource)
         : this.getCommandMap().getPreferredCommands(this.getBaseType());
   }

   public CommandInfo[] getAllCommands() {
      return this.dataSource != nullptr
         ? this.getCommandMap().getAllCommands(this.getBaseType(), this.dataSource)
         : this.getCommandMap().getAllCommands(this.getBaseType());
   }

    CommandInfo getCommand(const std::string& cmdName) {
      return this.dataSource != nullptr
         ? this.getCommandMap().getCommand(this.getBaseType(), cmdName, this.dataSource)
         : this.getCommandMap().getCommand(this.getBaseType(), cmdName);
   }

    void* getContent() {
      return this.object != nullptr ? this.object : this.getDataContentHandler().getContent(this.getDataSource());
   }

    void* getBean(CommandInfo cmdinfo) {
    void* bean = nullptr;

      try {
    ClassLoader cld = nullptr;
         cld = SecuritySupport.getContextClassLoader();
         if (cld == nullptr) {
            cld = this.getClass().getClassLoader();
         }

         bean = cmdinfo.getCommandObject(this, cld);
      } catch (IOException var4) {
      } catch (ClassNotFoundException var5) {
      }

    return bean;
   }

   private /* synchronized - TODO: add std::mutex */ DataContentHandler getDataContentHandler() {
      if (factory != this.oldFactory) {
         this.oldFactory = factory;
         this.factoryDCH = nullptr;
         this.dataContentHandler = nullptr;
         this.transferFlavors = emptyFlavors;
      }

      if (this.dataContentHandler != nullptr) {
         return this.dataContentHandler;
      } else {
    std::string simpleMT = this.getBaseType();
         if (this.factoryDCH == nullptr && factory != nullptr) {
            this.factoryDCH = factory.createDataContentHandler(simpleMT);
         }

         if (this.factoryDCH != nullptr) {
            this.dataContentHandler = this.factoryDCH;
         }

         if (this.dataContentHandler == nullptr) {
            if (this.dataSource != nullptr) {
               this.dataContentHandler = this.getCommandMap().createDataContentHandler(simpleMT, this.dataSource);
            } else {
               this.dataContentHandler = this.getCommandMap().createDataContentHandler(simpleMT);
            }
         }

         if (this.dataSource != nullptr) {
            this.dataContentHandler = std::make_shared<DataSourceDataContentHandler>(this.dataContentHandler, this.dataSource);
         } else {
            this.dataContentHandler = std::make_shared<ObjectDataContentHandler>(this.dataContentHandler, this.object, this.objectMimeType);
         }

         return this.dataContentHandler;
      }
   }

   private /* synchronized - TODO: add std::mutex */ std::string getBaseType() {
      if (this.shortType == nullptr) {
    std::string ct = this.getContentType();

         try {
    MimeType mt = std::make_shared<MimeType>(ct);
            this.shortType = mt.getBaseType();
         } catch (MimeTypeParseException var3) {
            this.shortType = ct;
         }
      }

      return this.shortType;
   }

   public static /* synchronized - TODO: add std::mutex */ void setDataContentHandlerFactory(DataContentHandlerFactory newFactory) {
      if (factory != nullptr) {
         throw Error("DataContentHandlerFactory already defined");
      } else {
    SecurityManager security = System.getSecurityManager();
         if (security != nullptr) {
            try {
               security.checkSetFactory();
            } catch (SecurityException var3) {
               if (DataHandler.class.getClassLoader() != newFactory.getClass().getClassLoader()) {
    throw var3;
               }
            }
         }

         factory = newFactory;
      }
   }
}
} // namespace activation
} // namespace javax
