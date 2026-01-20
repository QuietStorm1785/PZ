#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace sandbox {


class CustomSandboxOptions {
public:
    static const int VERSION1 = 1;
    static const int VERSION = 1;
    static const CustomSandboxOptions instance = std::make_shared<CustomSandboxOptions>();
   private const std::vector<CustomSandboxOption> m_options = std::make_unique<std::vector<>>();

    void init() {
    std::vector var1 = ZomboidFileSystem.instance.getModIDs();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    std::string var3 = (std::string)var1.get(var2);
    Mod var4 = ChooseGameInfo.getAvailableModDetails(var3);
         if (var4 != nullptr) {
    File var5 = std::make_shared<File>(var4.getDir() + File.separator + "media" + File.separator + "sandbox-options.txt");
            if (var5.exists() && !var5.isDirectory()) {
               this.readFile(var5.getAbsolutePath());
            }
         }
      }
   }

    static void Reset() {
      instance.m_options.clear();
   }

    void initInstance(SandboxOptions var1) {
      for (int var2 = 0; var2 < this.m_options.size(); var2++) {
    CustomSandboxOption var3 = this.m_options.get(var2);
         var1.newCustomOption(var3);
      }
   }

    bool readFile(const std::string& var1) {
      try {
    bool var6;
         try (
    FileReader var2 = std::make_shared<FileReader>(var1);
    BufferedReader var3 = std::make_shared<BufferedReader>(var2);
         ) {
    std::stringstream var4 = new std::stringstream();

            for (std::string var5 = var3.readLine(); var5 != nullptr; var5 = var3.readLine()) {
               var4.append(var5);
            }

            this.parse(var4);
            var6 = true;
         }

    return var6;
      } catch (FileNotFoundException var11) {
    return false;
      } catch (Exception var12) {
         ExceptionLogger.logException(var12);
    return false;
      }
   }

    void parse(const std::string& var1) {
      var1 = ScriptParser.stripComments(var1);
    Block var2 = ScriptParser.parse(var1);
    int var3 = -1;
    Value var4 = var2.getValue("VERSION");
      if (var4 != nullptr) {
         var3 = PZMath.tryParseInt(var4.getValue(), -1);
      }

      if (var3 >= 1 && var3 <= 1) {
         for (Block var6 : var2.children) {
            if (!var6.type.equalsIgnoreCase("option")) {
               throw RuntimeException("unknown block type \"" + var6.type + "\"");
            }

    CustomSandboxOption var7 = this.parseOption(var6);
            if (var7 == nullptr) {
               DebugLog.General.warn("failed to parse custom sandbox option \"%s\"", new Object[]{var6.id});
            } else {
               this.m_options.push_back(var7);
            }
         }
      } else {
         throw RuntimeException("invalid or missing VERSION");
      }
   }

    CustomSandboxOption parseOption(Block var1) {
      if (StringUtils.isNullOrWhitespace(var1.id)) {
         DebugLog.General.warn("missing or empty option id");
    return nullptr;
      } else {
    Value var2 = var1.getValue("type");
         if (var2 != nullptr && !StringUtils.isNullOrWhitespace(var2.getValue())) {
    std::string var3 = var2.getValue().trim();
            switch (var3) {
               case "boolean":
                  return CustomBooleanSandboxOption.parse(var1);
               case "double":
                  return CustomDoubleSandboxOption.parse(var1);
               case "enum":
                  return CustomEnumSandboxOption.parse(var1);
               case "integer":
                  return CustomIntegerSandboxOption.parse(var1);
               case "string":
                  return CustomStringSandboxOption.parse(var1);
               default:
                  DebugLog.General.warn("unknown option type \"%s\"", new Object[]{var2.getValue().trim()});
    return nullptr;
            }
         } else {
            DebugLog.General.warn("missing or empty value \"type\"");
    return nullptr;
         }
      }
   }
}
} // namespace sandbox
} // namespace zombie
