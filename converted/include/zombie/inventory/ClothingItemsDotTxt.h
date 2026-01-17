#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClothingItemsDotTxt {
public:
  static const ClothingItemsDotTxt instance = new ClothingItemsDotTxt();
  const StringBuilder buf = new StringBuilder();

  int readBlock(const std::string &string0, int int1,
                ClothingItemsDotTxt.Block block1) {
    int int0;
    for (int0 = int1; int0 < string0.length(); int0++) {
      if (string0.charAt(int0) == '{') {
        ClothingItemsDotTxt.Block block0 = new ClothingItemsDotTxt.Block();
        block1.children.add(block0);
        block1.elements.add(block0);
        std::string string1 = string0.substring(int1, int0).trim();
        int int2 = string1.indexOf(32);
        int int3 = string1.indexOf(9);
        int int4 = Math.max(int2, int3);
        if (int4 == -1) {
          block0.type = string1;
        } else {
          block0.type = string1.substring(0, int4);
          block0.id = string1.substring(int4).trim();
        }

        int0 = this.readBlock(string0, int0 + 1, block0);
        int1 = int0;
      } else {
        if (string0.charAt(int0) == '}') {
          std::string string2 = string0.substring(int1, int0).trim();
          if (!string2.isEmpty()) {
            ClothingItemsDotTxt.Value value0 = new ClothingItemsDotTxt.Value();
            value0.string = string0.substring(int1, int0).trim();
            block1.values.add(value0.string);
            block1.elements.add(value0);
          }

          return int0 + 1;
        }

        if (string0.charAt(int0) == ',') {
          ClothingItemsDotTxt.Value value1 = new ClothingItemsDotTxt.Value();
          value1.string = string0.substring(int1, int0).trim();
          block1.values.add(value1.string);
          block1.elements.add(value1);
          int1 = int0 + 1;
        }
      }
    }

    return int0;
  }

  void LoadFile() {
    std::string string0 =
        ZomboidFileSystem.instance.getString("media/scripts/clothingItems.txt");
    File file = new File(string0);
    if (file.exists()) {
      try(FileReader fileReader = new FileReader(string0);
          BufferedReader bufferedReader = new BufferedReader(fileReader);) {
        this.buf.setLength(0);

        std::string string1;
        while ((string1 = bufferedReader.readLine()) != nullptr) {
          this.buf.append(string1);
        }
      }
      catch (Throwable throwable0) {
        ExceptionLogger.logException(throwable0);
        return;
      }

      int int0 = this.buf.lastIndexOf("*/");

      while (int0 != -1) {
        int int1 = this.buf.lastIndexOf("/*", int0 - 1);
        if (int1 == -1) {
          break;
        }

        int int2 = this.buf.lastIndexOf("*/", int0 - 1);

        while (int2 > int1) {
          int int3 = int1;
          std::string string2 = this.buf.substring(int1, int2 + 2);
          int1 = this.buf.lastIndexOf("/*", int1 - 2);
          if (int1 == -1) {
            break;
          }

          int2 = this.buf.lastIndexOf("*/", int3 - 2);
        }

        if (int1 == -1) {
          break;
        }

        std::string string3 = this.buf.substring(int1, int0 + 2);
        this.buf.replace(int1, int0 + 2, "");
        int0 = this.buf.lastIndexOf("*/", int1);
      }

      ClothingItemsDotTxt.Block block = new ClothingItemsDotTxt.Block();
      this.readBlock(this.buf.toString(), 0, block);
      Path path0 =
          FileSystems.getDefault().getPath("media/clothing/clothingItems");

      try(DirectoryStream directoryStream = Files.newDirectoryStream(path0)) {
        for (auto &path1 : directoryStream)
          if (!Files.isDirectory(path1)) {
            std::string string4 = path1.getFileName().toString();
            if (string4.endsWith(".xml")) {
              std::string string5 = StringUtils.trimSuffix(string4, ".xml");
              System.out.println(string4 + " -> " + string5);
              this.addClothingItem(string5, block.children.get(0));
            }
          }
      }
    }
    catch (Exception exception) {
      exception.printStackTrace();
    }

    try(FileWriter fileWriter = new FileWriter(file)) {
      fileWriter.write(block.children.get(0).toString());
    }
    catch (Throwable throwable1) {
      ExceptionLogger.logException(throwable1);
    }

    System.out.println(block.children.get(0));
  }
}

    void addClothingItem(const std::string& string, ClothingItemsDotTxt.Block block1) {
  if (!string.startsWith("FemaleHair_")) {
    if (!string.startsWith("MaleBeard_")) {
      if (!string.startsWith("MaleHair_")) {
        if (!string.startsWith("ZedDmg_")) {
          if (!string.startsWith("Bandage_")) {
            if (!string.startsWith("Zed_Skin")) {
              for (ClothingItemsDotTxt.Block block0 : block1.children) {
                if ("item" == block0.type) && string == block0.id)) {
                                        return;
                                    }
              }

              ClothingItemsDotTxt.Block block2 =
                  new ClothingItemsDotTxt.Block();
              block2.type = "item";
              block2.id = string;
              ClothingItemsDotTxt.Value value = new ClothingItemsDotTxt.Value();
              value.string = "Type = Clothing";
              block2.elements.add(value);
              block2.values.add(value.string);
              value = new ClothingItemsDotTxt.Value();
              value.string = "DisplayName = " + string;
              block2.elements.add(value);
              block2.values.add(value.string);
              value = new ClothingItemsDotTxt.Value();
              value.string = "ClothingItem = " + string;
              block2.elements.add(value);
              block2.values.add(value.string);
              block1.elements.add(block2);
              block1.children.add(block2);
            }
          }
        }
      }
    }
  }
}

private
static class Block implements ClothingItemsDotTxt.BlockElement {
  std::string type;
  std::string id;
public
  ArrayList<ClothingItemsDotTxt.BlockElement> elements =
      std::make_unique<ArrayList<>>();
public
  ArrayList<String> values = std::make_unique<ArrayList<>>();
public
  ArrayList<ClothingItemsDotTxt.Block> children =
      std::make_unique<ArrayList<>>();

public
  ClothingItemsDotTxt.Block asBlock() { return this; }

public
  ClothingItemsDotTxt.Value asValue() { return null; }

  std::string toString() {
    StringBuilder stringBuilder = new StringBuilder();
    stringBuilder.append(this.type + (this.id == nullptr ? "" : " " + this.id) +
                         "\n");
    stringBuilder.append("{\n");

    for (ClothingItemsDotTxt.BlockElement blockElement : this.elements) {
      std::string string0 = blockElement.toString();

      for (String string1 : string0.split("\n")) {
        stringBuilder.append("\t" + string1 + "\n");
      }
    }

    stringBuilder.append("}\n");
    return stringBuilder.toString();
  }

  std::string toXML() {
    StringBuilder stringBuilder = new StringBuilder();
    stringBuilder.append("<Block type=\"" + this.type + "\" id=\"" + this.id +
                         "\">\n");

    for (ClothingItemsDotTxt.BlockElement blockElement : this.elements) {
      std::string string0 = blockElement.toXML();

      for (String string1 : string0.split("\n")) {
        stringBuilder.append("    " + string1 + "\n");
      }
    }

    stringBuilder.append("</Block>\n");
    return stringBuilder.toString();
  }
}

private
interface BlockElement {
  ClothingItemsDotTxt.Block asBlock();

  ClothingItemsDotTxt.Value asValue();

  std::string toXML();
}

private
static class Value implements ClothingItemsDotTxt.BlockElement {
  std::string string;

public
  ClothingItemsDotTxt.Block asBlock() { return null; }

public
  ClothingItemsDotTxt.Value asValue() { return this; }

  std::string toString() { return this.string + ",\n"; }

  std::string toXML() { return "<Value>" + this.string + "</Value>\n"; }
}
}
} // namespace inventory
} // namespace zombie
