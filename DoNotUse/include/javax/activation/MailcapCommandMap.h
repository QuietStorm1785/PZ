#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/activation/registries/LogSupport.h"
#include "com/sun/activation/registries/MailcapFile.h"
#include "java/net/URL.h"
#include "java/security/AccessController.h"
#include "javax/activation/MailcapCommandMap/1.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace javax {
namespace activation {


class MailcapCommandMap : public CommandMap {
public:
   private MailcapFile[] DB;
    static const int PROG = 0;
    static const std::string confDir;

    public MailcapCommandMap() {
    std::vector dbv = new std::vector(5);
    MailcapFile mf = nullptr;
      dbv.push_back(nullptr);
      LogSupport.log("MailcapCommandMap: load HOME");

      try {
    std::string user_home = System.getProperty("user.home");
         if (user_home != nullptr) {
    std::string path = user_home + File.separator + ".mailcap";
            mf = this.loadFile(path);
            if (mf != nullptr) {
               dbv.push_back(mf);
            }
         }
      } catch (SecurityException var6) {
      }

      LogSupport.log("MailcapCommandMap: load SYS");

      try {
         if (confDir != nullptr) {
            mf = this.loadFile(confDir + "mailcap");
            if (mf != nullptr) {
               dbv.push_back(mf);
            }
         }
      } catch (SecurityException var5) {
      }

      LogSupport.log("MailcapCommandMap: load JAR");
      this.loadAllResources(dbv, "META-INF/mailcap");
      LogSupport.log("MailcapCommandMap: load DEF");
      mf = this.loadResource("/META-INF/mailcap.default");
      if (mf != nullptr) {
         dbv.push_back(mf);
      }

      this.DB = new MailcapFile[dbv.size()];
      this.DB = dbv.toArray(this.DB);
   }

    MailcapFile loadResource(const std::string& name) {
    InputStream clis = nullptr;

    MailcapFile var4;
      try {
         clis = SecuritySupport.getResourceAsStream(this.getClass(), name);
         if (clis == nullptr) {
            if (LogSupport.isLoggable()) {
               LogSupport.log("MailcapCommandMap: not loading mailcap file: " + name);
            }

    return nullptr;
         }

    MailcapFile mf = std::make_shared<MailcapFile>(clis);
         if (LogSupport.isLoggable()) {
            LogSupport.log("MailcapCommandMap: successfully loaded mailcap file: " + name);
         }

         var4 = mf;
      } catch (IOException var17) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("MailcapCommandMap: can't load " + name, var17);
         }

    return nullptr;
      } catch (SecurityException var18) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("MailcapCommandMap: can't load " + name, var18);
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

    void loadAllResources(const std::vector& v, const std::string& name) {
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
               LogSupport.log("MailcapCommandMap: getResources");
            }

            for (int i = 0; i < urls.length; i++) {
    URL url = urls[i];
    InputStream clis = nullptr;
               if (LogSupport.isLoggable()) {
                  LogSupport.log("MailcapCommandMap: URL " + url);
               }

               try {
                  clis = SecuritySupport.openStream(url);
                  if (clis != nullptr) {
                     v.push_back(std::make_shared<MailcapFile>(clis));
                     anyLoaded = true;
                     if (LogSupport.isLoggable()) {
                        LogSupport.log("MailcapCommandMap: successfully loaded mailcap file from URL: " + url);
                     }
                  } else if (LogSupport.isLoggable()) {
                     LogSupport.log("MailcapCommandMap: not loading mailcap file from URL: " + url);
                  }
               } catch (IOException var21) {
                  if (LogSupport.isLoggable()) {
                     LogSupport.log("MailcapCommandMap: can't load " + url, var21);
                  }
               } catch (SecurityException var22) {
                  if (LogSupport.isLoggable()) {
                     LogSupport.log("MailcapCommandMap: can't load " + url, var22);
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
            LogSupport.log("MailcapCommandMap: can't load " + name, var24);
         }
      }

      if (!anyLoaded) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("MailcapCommandMap: !anyLoaded");
         }

    MailcapFile mf = this.loadResource("/" + name);
         if (mf != nullptr) {
            v.push_back(mf);
         }
      }
   }

    MailcapFile loadFile(const std::string& name) {
    MailcapFile mtf = nullptr;

      try {
         mtf = std::make_shared<MailcapFile>(name);
      } catch (IOException var4) {
      }

    return mtf;
   }

    public MailcapCommandMap(const std::string& fileName) {
      this();
      if (LogSupport.isLoggable()) {
         LogSupport.log("MailcapCommandMap: load PROG from " + fileName);
      }

      if (this.DB[0] == nullptr) {
         this.DB[0] = std::make_shared<MailcapFile>(fileName);
      }
   }

    public MailcapCommandMap(InputStream is) {
      this();
      LogSupport.log("MailcapCommandMap: load PROG");
      if (this.DB[0] == nullptr) {
         try {
            this.DB[0] = std::make_shared<MailcapFile>(is);
         } catch (IOException var3) {
         }
      }
   }

   public /* synchronized - TODO: add std::mutex */ CommandInfo[] getPreferredCommands(std::string mimeType) {
    std::vector cmdList = new std::vector();
      if (mimeType != nullptr) {
         mimeType = mimeType.toLowerCase(Locale.ENGLISH);
      }

      for (int i = 0; i < this.DB.length; i++) {
         if (this.DB[i] != nullptr) {
    std::unordered_map cmdMap = this.DB[i].getMailcapList(mimeType);
            if (cmdMap != nullptr) {
               this.appendPrefCmdsToList(cmdMap, cmdList);
            }
         }
      }

      for (int ix = 0; ix < this.DB.length; ix++) {
         if (this.DB[ix] != nullptr) {
    std::unordered_map cmdMap = this.DB[ix].getMailcapFallbackList(mimeType);
            if (cmdMap != nullptr) {
               this.appendPrefCmdsToList(cmdMap, cmdList);
            }
         }
      }

      CommandInfo[] cmdInfos = new CommandInfo[cmdList.size()];
      return cmdList.toArray(cmdInfos);
   }

    void appendPrefCmdsToList(std::unordered_map cmdHash, const std::vector& cmdList) {
      for (std::string verb : cmdHash.keySet()) {
         if (!this.checkForVerb(cmdList, verb)) {
    std::vector cmdList2 = (List)cmdHash.get(verb);
    std::string className = (std::string)cmdList2.get(0);
            cmdList.push_back(std::make_shared<CommandInfo>(verb, className));
         }
      }
   }

    bool checkForVerb(const std::vector& cmdList, const std::string& verb) {
    Iterator ee = cmdList.iterator();

      while (ee.hasNext()) {
    std::string enum_verb = ((CommandInfo)ee.next()).getCommandName();
         if (enum_verb == verb)) {
    return true;
         }
      }

    return false;
   }

   public /* synchronized - TODO: add std::mutex */ CommandInfo[] getAllCommands(std::string mimeType) {
    std::vector cmdList = new std::vector();
      if (mimeType != nullptr) {
         mimeType = mimeType.toLowerCase(Locale.ENGLISH);
      }

      for (int i = 0; i < this.DB.length; i++) {
         if (this.DB[i] != nullptr) {
    std::unordered_map cmdMap = this.DB[i].getMailcapList(mimeType);
            if (cmdMap != nullptr) {
               this.appendCmdsToList(cmdMap, cmdList);
            }
         }
      }

      for (int ix = 0; ix < this.DB.length; ix++) {
         if (this.DB[ix] != nullptr) {
    std::unordered_map cmdMap = this.DB[ix].getMailcapFallbackList(mimeType);
            if (cmdMap != nullptr) {
               this.appendCmdsToList(cmdMap, cmdList);
            }
         }
      }

      CommandInfo[] cmdInfos = new CommandInfo[cmdList.size()];
      return cmdList.toArray(cmdInfos);
   }

    void appendCmdsToList(std::unordered_map typeHash, const std::vector& cmdList) {
      for (std::string verb : typeHash.keySet()) {
         for (std::string cmd : (List)typeHash.get(verb)) {
            cmdList.push_back(std::make_shared<CommandInfo>(verb, cmd));
         }
      }
   }

   public /* synchronized - TODO: add std::mutex */ CommandInfo getCommand(std::string mimeType, std::string cmdName) {
      if (mimeType != nullptr) {
         mimeType = mimeType.toLowerCase(Locale.ENGLISH);
      }

      for (int i = 0; i < this.DB.length; i++) {
         if (this.DB[i] != nullptr) {
    std::unordered_map cmdMap = this.DB[i].getMailcapList(mimeType);
            if (cmdMap != nullptr) {
    std::vector v = (List)cmdMap.get(cmdName);
               if (v != nullptr) {
    std::string cmdClassName = (std::string)v.get(0);
                  if (cmdClassName != nullptr) {
                     return std::make_shared<CommandInfo>(cmdName, cmdClassName);
                  }
               }
            }
         }
      }

      for (int ix = 0; ix < this.DB.length; ix++) {
         if (this.DB[ix] != nullptr) {
    std::unordered_map cmdMap = this.DB[ix].getMailcapFallbackList(mimeType);
            if (cmdMap != nullptr) {
    std::vector v = (List)cmdMap.get(cmdName);
               if (v != nullptr) {
    std::string cmdClassName = (std::string)v.get(0);
                  if (cmdClassName != nullptr) {
                     return std::make_shared<CommandInfo>(cmdName, cmdClassName);
                  }
               }
            }
         }
      }

    return nullptr;
   }

   public /* synchronized - TODO: add std::mutex */ void addMailcap(std::string mail_cap) {
      LogSupport.log("MailcapCommandMap: add to PROG");
      if (this.DB[0] == nullptr) {
         this.DB[0] = std::make_unique<MailcapFile>();
      }

      this.DB[0].appendToMailcap(mail_cap);
   }

   public /* synchronized - TODO: add std::mutex */ DataContentHandler createDataContentHandler(std::string mimeType) {
      if (LogSupport.isLoggable()) {
         LogSupport.log("MailcapCommandMap: createDataContentHandler for " + mimeType);
      }

      if (mimeType != nullptr) {
         mimeType = mimeType.toLowerCase(Locale.ENGLISH);
      }

      for (int i = 0; i < this.DB.length; i++) {
         if (this.DB[i] != nullptr) {
            if (LogSupport.isLoggable()) {
               LogSupport.log("  search DB #" + i);
            }

    std::unordered_map cmdMap = this.DB[i].getMailcapList(mimeType);
            if (cmdMap != nullptr) {
    std::vector v = (List)cmdMap.get("content-handler");
               if (v != nullptr) {
    std::string name = (std::string)v.get(0);
    DataContentHandler dch = this.getDataContentHandler(name);
                  if (dch != nullptr) {
    return dch;
                  }
               }
            }
         }
      }

      for (int ix = 0; ix < this.DB.length; ix++) {
         if (this.DB[ix] != nullptr) {
            if (LogSupport.isLoggable()) {
               LogSupport.log("  search fallback DB #" + ix);
            }

    std::unordered_map cmdMap = this.DB[ix].getMailcapFallbackList(mimeType);
            if (cmdMap != nullptr) {
    std::vector v = (List)cmdMap.get("content-handler");
               if (v != nullptr) {
    std::string name = (std::string)v.get(0);
    DataContentHandler dch = this.getDataContentHandler(name);
                  if (dch != nullptr) {
    return dch;
                  }
               }
            }
         }
      }

    return nullptr;
   }

    DataContentHandler getDataContentHandler(const std::string& name) {
      if (LogSupport.isLoggable()) {
         LogSupport.log("    got content-handler");
      }

      if (LogSupport.isLoggable()) {
         LogSupport.log("      class " + name);
      }

      try {
    ClassLoader cld = nullptr;
         cld = SecuritySupport.getContextClassLoader();
         if (cld == nullptr) {
            cld = this.getClass().getClassLoader();
         }

    Class cl = nullptr;

         try {
            cl = cld.loadClass(name);
         } catch (Exception var5) {
            cl = Class.forName(name);
         }

         if (cl != nullptr) {
            return (DataContentHandler)cl.newInstance();
         }
      } catch (IllegalAccessException var6) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("Can't load DCH " + name, var6);
         }
      } catch (ClassNotFoundException var7) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("Can't load DCH " + name, var7);
         }
      } catch (InstantiationException var8) {
         if (LogSupport.isLoggable()) {
            LogSupport.log("Can't load DCH " + name, var8);
         }
      }

    return nullptr;
   }

   public /* synchronized - TODO: add std::mutex */ std::string[] getMimeTypes() {
    std::vector mtList = new std::vector();

      for (int i = 0; i < this.DB.length; i++) {
         if (this.DB[i] != nullptr) {
            std::string[] ts = this.DB[i].getMimeTypes();
            if (ts != nullptr) {
               for (int j = 0; j < ts.length; j++) {
                  if (!mtList.contains(ts[j])) {
                     mtList.push_back(ts[j]);
                  }
               }
            }
         }
      }

      std::string[] mts = new std::string[mtList.size()];
      return mtList.toArray(mts);
   }

   public /* synchronized - TODO: add std::mutex */ std::string[] getNativeCommands(std::string mimeType) {
    std::vector cmdList = new std::vector();
      if (mimeType != nullptr) {
         mimeType = mimeType.toLowerCase(Locale.ENGLISH);
      }

      for (int i = 0; i < this.DB.length; i++) {
         if (this.DB[i] != nullptr) {
            std::string[] cmds = this.DB[i].getNativeCommands(mimeType);
            if (cmds != nullptr) {
               for (int j = 0; j < cmds.length; j++) {
                  if (!cmdList.contains(cmds[j])) {
                     cmdList.push_back(cmds[j]);
                  }
               }
            }
         }
      }

      std::string[] cmds = new std::string[cmdList.size()];
      return cmdList.toArray(cmds);
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
