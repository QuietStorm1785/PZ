#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/activation/registries/LogSupport.h"
#include "com/sun/activation/registries/MimeTypeFile.h"
#include "java/net/URL.h"
#include "java/security/AccessController.h"
#include "javax/activation/MimetypesFileTypeMap/1.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class MimetypesFileTypeMap : public FileTypeMap {
public:
   private MimeTypeFile[] DB;
    static const int PROG = 0;
    static const std::string defaultType = "application/octet-stream";
    static const std::string confDir;

    public MimetypesFileTypeMap() {
    Vector dbv = std::make_shared<Vector>(5);
    MimeTypeFile mf = nullptr;
      dbv.addElement(nullptr);
      LogSupport.log("MimetypesFileTypeMap: load HOME");

      try {
    std::string user_home = System.getProperty("user.home");
         if (user_home != nullptr) {
    std::string path = user_home + File.separator + ".mime.types";
            mf = this.loadFile(path);
            if (mf != nullptr) {
               dbv.addElement(mf);
            }
         }
      } catch (SecurityException var6) {
      }

      LogSupport.log("MimetypesFileTypeMap: load SYS");

      try {
         if (confDir != nullptr) {
            mf = this.loadFile(confDir + "mime.types");
            if (mf != nullptr) {
               dbv.addElement(mf);
            }
         }
      } catch (SecurityException var5) {
      }

      LogSupport.log("MimetypesFileTypeMap: load JAR");
      this.loadAllResources(dbv, "META-INF/mime.types");
      LogSupport.log("MimetypesFileTypeMap: load DEF");
      mf = this.loadResource("/META-INF/mimetypes.default");
      if (mf != nullptr) {
         dbv.addElement(mf);
      }

      this.DB = new MimeTypeFile[dbv.size()];
      dbv.copyInto(this.DB);
   }

    MimeTypeFile loadResource(const std::string& name) {
    InputStream clis = nullptr;

    MimeTypeFile var4;
      try {
         clis = SecuritySupport.getResourceAsStream(this.getClass(), name);
         if (clis == nullptr) {
            if (LogSupport.isLoggable()) {
               LogSupport.log("MimetypesFileTypeMap: not loading mime types file: " + name);
            }

    return nullptr;
         }

    MimeTypeFile mf = std::make_shared<MimeTypeFile>(clis);
         if (LogSupport.isLoggable()) {
            LogSupport.log("MimetypesFileTypeMap: successfully loaded mime types file: " + name);
         }

         var4 = mf;
      } catch (IOException var17) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("MimetypesFileTypeMap: can't load " + name, var17);
         }

    return nullptr;
      } catch (SecurityException var18) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("MimetypesFileTypeMap: can't load " + name, var18);
         }

    return nullptr;
      } finally {
         try {
            if (clis != nullptr) {
               clis.close();
            }
         } catch (IOException var16) {
         }
      }

    return var4;
   }

    void loadAllResources(Vector v, const std::string& name) {
    bool anyLoaded = false;

      try {
    ClassLoader cld = nullptr;
         cld = SecuritySupport.getContextClassLoader();
         if (cld == nullptr) {
            cld = this.getClass().getClassLoader();
         }

         URL[] urls;
         if (cld != nullptr) {
            urls = SecuritySupport.getResources(cld, name);
         } else {
            urls = SecuritySupport.getSystemResources(name);
         }

         if (urls != nullptr) {
            if (LogSupport.isLoggable()) {
               LogSupport.log("MimetypesFileTypeMap: getResources");
            }

            for (int i = 0; i < urls.length; i++) {
    URL url = urls[i];
    InputStream clis = nullptr;
               if (LogSupport.isLoggable()) {
                  LogSupport.log("MimetypesFileTypeMap: URL " + url);
               }

               try {
                  clis = SecuritySupport.openStream(url);
                  if (clis != nullptr) {
                     v.addElement(std::make_shared<MimeTypeFile>(clis));
                     anyLoaded = true;
                     if (LogSupport.isLoggable()) {
                        LogSupport.log("MimetypesFileTypeMap: successfully loaded mime types from URL: " + url);
                     }
                  } else if (LogSupport.isLoggable()) {
                     LogSupport.log("MimetypesFileTypeMap: not loading mime types from URL: " + url);
                  }
               } catch (IOException var21) {
                  if (LogSupport.isLoggable()) {
                     LogSupport.log("MimetypesFileTypeMap: can't load " + url, var21);
                  }
               } catch (SecurityException var22) {
                  if (LogSupport.isLoggable()) {
                     LogSupport.log("MimetypesFileTypeMap: can't load " + url, var22);
                  }
               } finally {
                  try {
                     if (clis != nullptr) {
                        clis.close();
                     }
                  } catch (IOException var20) {
                  }
               }
            }
         }
      } catch (Exception var24) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("MimetypesFileTypeMap: can't load " + name, var24);
         }
      }

      if (!anyLoaded) {
         LogSupport.log("MimetypesFileTypeMap: !anyLoaded");
    MimeTypeFile mf = this.loadResource("/" + name);
         if (mf != nullptr) {
            v.addElement(mf);
         }
      }
   }

    MimeTypeFile loadFile(const std::string& name) {
    MimeTypeFile mtf = nullptr;

      try {
         mtf = std::make_shared<MimeTypeFile>(name);
      } catch (IOException var4) {
      }

    return mtf;
   }

    public MimetypesFileTypeMap(const std::string& mimeTypeFileName) {
      this();
      this.DB[0] = std::make_shared<MimeTypeFile>(mimeTypeFileName);
   }

    public MimetypesFileTypeMap(InputStream is) {
      this();

      try {
         this.DB[0] = std::make_shared<MimeTypeFile>(is);
      } catch (IOException var3) {
      }
   }

   public /* synchronized - TODO: add std::mutex */ void addMimeTypes(std::string mime_types) {
      if (this.DB[0] == nullptr) {
         this.DB[0] = std::make_unique<MimeTypeFile>();
      }

      this.DB[0].appendToRegistry(mime_types);
   }

    std::string getContentType(File f) {
      return this.getContentType(f.getName());
   }

   public /* synchronized - TODO: add std::mutex */ std::string getContentType(std::string filename) {
    int dot_pos = filename.lastIndexOf(".");
      if (dot_pos < 0) {
         return "application/octet-stream";
      } else {
    std::string file_ext = filename.substr(dot_pos + 1);
         if (file_ext.length() == 0) {
            return "application/octet-stream";
         } else {
            for (int i = 0; i < this.DB.length; i++) {
               if (this.DB[i] != nullptr) {
    std::string result = this.DB[i].getMIMETypeString(file_ext);
                  if (result != nullptr) {
    return result;
                  }
               }
            }

            return "application/octet-stream";
         }
      }
   }

   static {
    std::string dir = nullptr;

      try {
         dir = AccessController.doPrivileged(std::make_unique<1>());
      } catch (Exception var2) {
      }

      confDir = dir;
   }
}
} // namespace activation
} // namespace javax
