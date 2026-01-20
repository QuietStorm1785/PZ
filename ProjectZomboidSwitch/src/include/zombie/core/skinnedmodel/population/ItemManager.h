#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Rand.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ItemManager {
public:
   public std::vector<CarriedItem> m_Items = std::make_unique<std::vector<>>();
    static ItemManager instance;

    static void init() {
    File var0 = ZomboidFileSystem.instance.getMediaFile("items" + File.separator + "items.xml");
      instance = Parse(var0.getPath());
   }

    CarriedItem GetRandomItem() {
    int var1 = Rand.Next(this.m_Items.size() + 1);
      return var1 < this.m_Items.size() ? this.m_Items.get(var1) : nullptr;
   }

    static ItemManager Parse(const std::string& var0) {
      try {
    return parse();
      } catch (JAXBException var2) {
         var2.printStackTrace();
      } catch (IOException var3) {
         var3.printStackTrace();
      }

    return nullptr;
   }

    static ItemManager parse(const std::string& var0) {
    ItemManager var5;
      try (FileInputStream var1 = std::make_shared<FileInputStream>(var0)) {
    JAXBContext var2 = JAXBContext.newInstance(new Class[]{ItemManager.class});
    Unmarshaller var3 = var2.createUnmarshaller();
    ItemManager var4 = (ItemManager)var3.unmarshal(var1);
         var5 = var4;
      }

    return var5;
   }

    static void Write(ItemManager var0, const std::string& var1) {
      try {
         write(var0, var1);
      } catch (JAXBException var3) {
         var3.printStackTrace();
      } catch (IOException var4) {
         var4.printStackTrace();
      }
   }

    static void write(ItemManager var0, const std::string& var1) {
      try (FileOutputStream var2 = std::make_shared<FileOutputStream>(var1)) {
    JAXBContext var3 = JAXBContext.newInstance(new Class[]{ItemManager.class});
    Marshaller var4 = var3.createMarshaller();
         var4.setProperty("jaxb.formatted.output", bool.TRUE);
         var4.marshal(var0, var2);
      }
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
